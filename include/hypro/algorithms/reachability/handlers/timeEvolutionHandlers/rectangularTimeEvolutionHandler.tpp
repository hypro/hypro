/*
 * Copyright (c) 2022.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "rectangularTimeEvolutionHandler.h"
#include "hypro/algorithms/reachability/analyzer/UnderApproximativeReachabilityAnalyzer.h"

namespace hypro {
template <typename State>
State rectangularApplyTimeEvolution( const State& initialSet, const rectangularFlow<typename State::NumberType>& flow ) {
	using Number = typename State::NumberType;
	auto& vpool = hypro::VariablePool::getInstance();
	// get initial state
	CarlPolytope<Number> initial = Converter<Number>::toCarlPolytope( initialSet );
	// storage to build elimination query
	std::vector<carl::Variable> variablesToEliminate;
	// add variable for time elapse
	carl::Variable t = vpool.newCarlVariable("__t");
	// add constraint t >= 0
	initial.addConstraint( ConstraintT<hypro::tNumber>( PolyT<hypro::tNumber>( t ), carl::Relation::GEQ ) );

	// introduce pre-/primed variables and substitute
	for ( const auto& v : initial.getVariables() ) {
		if ( v != t ) {
			// create primed var
			std::stringstream ss;
			ss << v.name() << "_pre";
			std::string s = ss.str();
			auto newV = vpool.newCarlVariable( s );
			// substitute to create precondition
			initial.substituteVariable( v, newV );
			// store var to eliminate later
			variablesToEliminate.push_back( newV );
			// add flow conditions for new variables, we use the variable mapping provided by the flow
			std::vector<ConstraintT<hypro::tNumber>> flowConstraints = createFlowConstraints<hypro::tNumber, typename State::NumberType>( v, newV, t, flow.getFlowIntervalForDimension( v ) );

			TRACE( "hydra.worker", "Use flow constraints: " );
#ifdef HYPRO_LOGGING
			for ( const auto& c : flowConstraints ) {
				TRACE( "hydra.worker", c );
			}
#endif

			initial.addConstraints( flowConstraints );
		}
	}

	// add t to eliminate at latest
	variablesToEliminate.push_back( t );

	// create variables to eliminate
	QEQuery quOrder;
	quOrder.push_back( std::make_pair( QuantifierType::EXISTS, variablesToEliminate ) );
	// allow for some heuristics on how to eliminate
	initial.choseOrder( quOrder );

	// eliminate vars
	initial.eliminateVariables( quOrder );

	DEBUG( "hydra.worker", "State set after time elapse: " << initial );

	State res;
	convert( initial, res );
	return res;
}

template <typename Number, class... Reps>
State<Number, Reps...> rectangularApplyReverseTimeEvolution( const State<Number, Reps...>& badSet, const Location<Number>* loc ) {
	auto flow = loc->getRectangularFlow();
	auto& vpool = hypro::VariablePool::getInstance();
	// get bad state
	CarlPolytope<Number> bad = std::get<CarlPolytope<Number>>( badSet.getSet() );
	// storage to build elimination query
	std::vector<carl::Variable> variablesToEliminate;
	// add variable for time elapse
    carl::Variable t = vpool.newCarlVariable("__t");
	// add constraint t >= 0
	bad.addConstraint( ConstraintT<hypro::tNumber>( PolyT<hypro::tNumber>( t ), carl::Relation::GEQ ) );

	// introduce post variables and substitute
	for ( const auto& v : bad.getVariables() ) {
		if ( v != t ) {
			// create post var
			std::stringstream ss;
			ss << v.name() << "_post";
			std::string s = ss.str();
			auto newV = vpool.newCarlVariable( s );
			// substitute to create postcondition
			bad.substituteVariable( v, newV );
			// store var to eliminate later
			variablesToEliminate.push_back( newV );
			// add flow conditions for new variables, we use the variable mapping provided by the flow
			std::vector<ConstraintT<hypro::tNumber>> flowConstraints = createFlowConstraints<hypro::tNumber, typename State<Number, Reps...>::NumberType>( newV, v, t, flow.getFlowIntervalForDimension( v ) );

			TRACE( "hydra.worker", "Use flow constraints: " );
#ifdef HYPRO_LOGGING
			for ( const auto& c : flowConstraints ) {
				TRACE( "hydra.worker", c );
			}
#endif

			bad.addConstraints( flowConstraints );
		}
	}

	// add invariant constraints
	auto invariantConstraints = halfspacesToConstraints( loc->getInvariant().getMatrix(), loc->getInvariant().getVector() );
	bad.addConstraints( invariantConstraints );

	// add t to eliminate at latest
	variablesToEliminate.push_back( t );

	// create variables to eliminate
	QEQuery quOrder;
	quOrder.push_back( std::make_pair( QuantifierType::EXISTS, variablesToEliminate ) );
	// allow for some heuristics on how to eliminate
	bad.choseOrder( quOrder );

	// eliminate vars
	bad.eliminateVariables( quOrder );

	DEBUG( "hydra.worker", "State set after time elapse: " << bad );

	State res( badSet );
	res.setSet( bad );

	return res;
}

template <template <typename, typename, typename> typename PolyhedralRepresentation, typename Number, typename Converter, typename Setting>
PolyhedralRepresentation<Number, Converter, Setting> rectangularApplyTimeEvolution( const PolyhedralRepresentation<Number, Converter, Setting>& initialSet, const rectangularFlow<Number>& flow ) {
	VPolytope<Number> initSetPolytope = hypro::Converter<Number>::toVPolytope( initialSet );
	assert( flow.dimension() == initialSet.dimension() );

	VPolytope<Number> flowSetPolytope{ flow.vertices() };
	VPolytope<Number> timeElapsePolytope{ initSetPolytope.vertices() };
	// set rays
	auto combinedRays = initSetPolytope.rays();
	// add rays from flow set
	combinedRays.insert( flowSetPolytope.rays().begin(), flowSetPolytope.rays().end() );
	// add rays originating to vertices of the flow set
	std::for_each( flowSetPolytope.vertices().begin(), flowSetPolytope.vertices().end(), [&]( const auto& point ) {
		combinedRays.insert( point.rawCoordinates() );
	} );

	timeElapsePolytope.setRays( combinedRays );

	// Convert back
	PolyhedralRepresentation<Number, Converter, Setting> timeElapse;
	convert( timeElapsePolytope, timeElapse );
	return timeElapse;
}

template <template <typename, typename, typename> typename PolyhedralRepresentation, typename Number, typename Converter, typename Setting>
PolyhedralRepresentation<Number, Converter, Setting> rectangularApplyBoundedTimeEvolution( const PolyhedralRepresentation<Number, Converter, Setting>& initialSet, const rectangularFlow<Number>& flow, tNumber timeBound ) {
	DEBUG( "hypro.reachability.rectangular", "Compute bounded time successors (polyhedral version)." );
	VPolytope<Number> initSetPolytope = hypro::Converter<Number>::toVPolytope( initialSet );
	assert( flow.dimension() == initialSet.dimension() );

	VPolytope<Number> flowSetPolytope{ flow.vertices() };
	VPolytope<Number> timeElapsePolytope{ initSetPolytope.vertices() };
	// set rays
	auto combinedRays = initSetPolytope.rays();
	// add rays originating from vertices of the flow set
	auto flowVertices = flowSetPolytope.vertices();
	std::for_each( std::begin( flowVertices ), std::end( flowVertices ), [&]( const auto& point ) {
		combinedRays.insert( point.rawCoordinates() );
	} );
	TRACE( "hypro.reachability.rectangular", "Flow cone is " << combinedRays );
	// compute vertices from bounded rays
	for ( const auto& vertex : initSetPolytope.vertices() ) {
		for ( const auto& ray : combinedRays ) {
			timeElapsePolytope.emplace_back( Point<Number>{ vector_t<Number>( vertex.rawCoordinates() + carl::convert<tNumber, Number>( timeBound ) * ray ) } );
		}
	}
	assert( timeElapsePolytope.rays().empty() );
	timeElapsePolytope.removeRedundancy();
	DEBUG( "hypro.reachability.rectangular", "Computed time successor: " << timeElapsePolytope );
	// Convert back
	PolyhedralRepresentation<Number, Converter, Setting> timeElapse;
	convert( timeElapsePolytope, timeElapse );
	return timeElapse;
}

/*
template <template <typename, typename, typename> typename PolyhedralRepresentation, typename Number, typename Converter, typename Setting>
PolyhedralRepresentation<Number, Converter, Setting> rectangularApplyReverseTimeEvolution( const PolyhedralRepresentation<Number, Converter, Setting>& badSet, const rectangularFlow<Number>& flow ) {
	auto convertedSet = Converter::toCarlPolytope( badSet );
	auto convertedResult = rectangularApplyReverseTimeEvolution( convertedSet, flow );
	PolyhedralRepresentation<Number, Converter, Setting> res;
	convert( convertedResult, res );
	return res;
}
*/

template <typename Number>
CarlPolytope<Number> rectangularApplyTimeEvolution( const CarlPolytope<Number>& initialSet, const rectangularFlow<Number>& flow ) {
	auto& vpool = hypro::VariablePool::getInstance();
	// get initial state
	CarlPolytope<Number> initial = initialSet;
	// storage to build elimination query
	std::vector<carl::Variable> variablesToEliminate;
	// add variable for time elapse
        carl::Variable t = vpool.newCarlVariable("__t");
	// add constraint t >= 0
	initial.addConstraint( ConstraintT<hypro::tNumber>( PolyT<hypro::tNumber>( t ), carl::Relation::GEQ ) );

	// introduce pre-/primed variables and substitute
	for ( const auto& v : initial.getVariables() ) {
		if ( v != t ) {
			// create primed var
			std::stringstream ss;
			ss << v.name() << "_pre";
			std::string s = ss.str();
			auto newV = vpool.newCarlVariable( s );
			// substitute to create precondition
			initial.substituteVariable( v, newV );
			// store var to eliminate later
			variablesToEliminate.push_back( newV );
			// add flow conditions for new variables, we use the variable mapping provided by the flow
			std::vector<ConstraintT<hypro::tNumber>> flowConstraints = createFlowConstraints<hypro::tNumber, Number>( v, newV, t, flow.getFlowIntervalForDimension( v ) );

			TRACE( "hydra.worker", "Use flow constraints: " );
#ifdef HYPRO_LOGGING
			for ( const auto& c : flowConstraints ) {
				TRACE( "hydra.worker", c );
			}
#endif

			initial.addConstraints( flowConstraints );
		}
	}

	// add t to eliminate at latest
	variablesToEliminate.push_back( t );

	// create variables to eliminate
	QEQuery quOrder;
	quOrder.push_back( std::make_pair( QuantifierType::EXISTS, variablesToEliminate ) );
	// allow for some heuristics on how to eliminate
	initial.choseOrder( quOrder );

	// eliminate vars
	initial.eliminateVariables( quOrder );

	DEBUG( "hydra.worker", "State set after time elapse: " << initial );

	return initial;
}

template <typename Number>
CarlPolytope<Number> rectangularApplyReverseTimeEvolution( const CarlPolytope<Number>& badSet, const Location<Number>* loc ) {
	auto& vpool = hypro::VariablePool::getInstance();
	auto flow = loc->getRectangularFlow();
	// get bad state
	CarlPolytope<Number> bad = badSet;
	// storage to build elimination query
	std::vector<carl::Variable> variablesToEliminate;
	// add variable for time elapse
    carl::Variable t = vpool.newCarlVariable("__t");
	// add constraint t <= 0
	bad.addConstraint( ConstraintT<hypro::tNumber>( PolyT<hypro::tNumber>( t ), carl::Relation::GEQ ) );

	// introduce post variables and substitute
	for ( const auto& v : bad.getVariables() ) {
		if ( v != t ) {
			// create pre var
			std::stringstream ss;
			ss << v.name() << "_prime";
			std::string s = ss.str();
			auto newV = vpool.newCarlVariable( s );
			// substitute to create precondition
			bad.substituteVariable( v, newV );
			// store var to eliminate later
			variablesToEliminate.push_back( newV );
			// add flow conditions for new variables, we use the variable mapping provided by the flow
			std::vector<ConstraintT<hypro::tNumber>> flowConstraints = createReverseFlowConstraints<hypro::tNumber, Number>( v, newV, t, flow.getFlowIntervalForDimension( v ) );

#ifdef HYPRO_LOGGING
			TRACE( "hypro.worker", "Use flow constraints: " );
			for ( const auto& c : flowConstraints ) {
				TRACE( "hypro.worker", c );
			}
#endif

			bad.addConstraints( flowConstraints );
		}
	}
	// add invariant constraints, if the invariant is specified and does not represent the empty set
	if ( !loc->getInvariant().isTrue() ) {
		if ( loc->getInvariant().isFalse() ) {
			return CarlPolytope<Number>::Empty();
		} else {
			auto invariantConstraints = halfspacesToConstraints<Number, hypro::tNumber>( loc->getInvariant().getMatrix(), loc->getInvariant().getVector() );
			bad.addConstraints( invariantConstraints );
		}
	}

	TRACE( "hypro.worker", "Full constraint set describing the dynamic behavior: \n"
								 << bad );

	// add t to eliminate at latest
	variablesToEliminate.push_back( t );

	// create variables to eliminate
	QEQuery quOrder;
	quOrder.push_back( std::make_pair( QuantifierType::EXISTS, variablesToEliminate ) );
	// allow for some heuristics on how to eliminate
	bad.choseOrder( quOrder );

	// eliminate vars
	bad.eliminateVariables( quOrder );

	DEBUG( "hydra.worker", "State set after reverse time elapse: " << bad );

	return bad;
}




template <typename Number>
CarlPolytope<Number> rectangularUnderapproximateReverseTimeEvolution( const CarlPolytope<Number>& badSet, const rectangularFlow<Number>& flow ) {
	UnderApproximativeReachabilityAnalyzer<Number> analyzer = UnderApproximativeReachabilityAnalyzer<Number>();
	auto vars = badSet.getVariables();
	vector_t<carl::Interval<Number>> rates = vector_t<carl::Interval<Number>>(vars.size());
	auto flowMap = flow.getFlowIntervals();
	int i = 0;
	for (auto var: vars){
		rates(i) = flowMap.at(var);
		i++;
	}

    auto [matrix, constants] = analyzer.solve(badSet.matrix(), badSet.vector(),rates);
	CarlPolytope<Number> result = CarlPolytope<Number>(matrix,constants);
	result.matrix() = matrix;
	result.vector() = constants;
	return result;
}

}  // namespace hypro
