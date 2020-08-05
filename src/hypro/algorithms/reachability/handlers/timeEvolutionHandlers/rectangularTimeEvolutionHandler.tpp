#include "rectangularTimeEvolutionHandler.h"

namespace hypro {
template <typename State>
State rectangularApplyTimeEvolution( const State& initialSet, const rectangularFlow<typename State::NumberType>& flow ) {
	using Number = typename State::NumberType;
	auto& vpool = hypro::VariablePool::getInstance();
	// get initial state
	CarlPolytope<Number> initial = std::get<CarlPolytope<Number>>( initialSet.getSet() );
	// storage to build elimination query
	std::vector<carl::Variable> variablesToEliminate;
	// add variable for time elapse
	carl::Variable t = vpool.newCarlVariable( "t" );
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

	State res(initialSet);
	res.setSet(initial);

	return res;
}

template <typename State>
State rectangularApplyReverseTimeEvolution( const State& badSet, const rectangularFlow<typename State::NumberType>& flow ) {
	using Number = typename State::NumberType;
	auto& vpool = hypro::VariablePool::getInstance();
	// get bad state
	CarlPolytope<Number> bad = std::get<CarlPolytope<Number>>( badSet.getSet() );
	// storage to build elimination query
	std::vector<carl::Variable> variablesToEliminate;
	// add variable for time elapse
	carl::Variable t = vpool.newCarlVariable( "t" );
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
			std::vector<ConstraintT<hypro::tNumber>> flowConstraints = createFlowConstraints<hypro::tNumber, typename State::NumberType>( newV, v, t, flow.getFlowIntervalForDimension( v ) );

			TRACE( "hydra.worker", "Use flow constraints: " );
#ifdef HYPRO_LOGGING
			for ( const auto& c : flowConstraints ) {
				TRACE( "hydra.worker", c );
			}
#endif

			bad.addConstraints( flowConstraints );
		}
	}

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

	State res(badSet);
	res.setSet(bad);

	return res;
}
}  // namespace hypro
