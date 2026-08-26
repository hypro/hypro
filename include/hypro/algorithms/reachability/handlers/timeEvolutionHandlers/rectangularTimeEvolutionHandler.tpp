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
        //TODO initSetPolytope.removeRedundancy(); ?
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
    CarlPolytope<Number> rectangularApplyReverseTimeEvolution( const CarlPolytope<Number> &badSet, const rectangularFlow<Number> &flow, const Condition<Number> &invariant, std::optional<std::pair<size_t,size_t>> stochJumpAndMappedDim, std::optional<std::pair<size_t,size_t>> firstEnabledIndex, std::optional<std::vector<std::pair<size_t, carl::Interval<Number>>>> initialConditions ) {
#ifdef HYPRO_USE_QE_REDUNDANCY_CHECKS
        constexpr bool REMOVE_REDUNDANDY_IN_QE = true;
#else
        constexpr bool REMOVE_REDUNDANDY_IN_QE = false;
#endif

        auto& vpool = hypro::VariablePool::getInstance();

        // get bad state
        CarlPolytope<Number> bad = badSet;
        auto dim = badSet.dimension();
        // vpool is a single, monotonically growing pool shared by everything that has ever created a
        // carl variable (e.g. callers that keep other, unrelated variables registered for later re-use,
        // such as realyst's REUSE_INTEGRATION instance variables). badSet's own dimension() only reflects
        // the variables it actually uses and can therefore be smaller than vpool's current size, i.e.
        // there can be a "gap" of pool indices already in use by variables badSet never references. The
        // post/time variables created below always get indices at the *current end* of vpool, not
        // necessarily right after `dim`, so track that gap to size bad correctly instead of assuming
        // vpool was exactly `dim` entries large.
        auto poolGap = vpool.size() - dim;
        // storage to build elimination query
        std::vector<carl::Variable> variablesToEliminate;
        // add variable for time elapse
        carl::Variable t = vpool.newCarlVariable( "__t" );
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

                std::cout << "bad: \n" << bad << std::endl;
                std::cout << "bad variables:" << std::endl;
                for (carl::Variable& carlVar : bad.getVariables()) std::cout << carlVar << ", " << std::endl;
                std::cout << "find flow interval for dimension v: " << v.name() << " flow interval: " << flow.getFlowIntervalForDimension( v ) << std::endl;

                std::vector<ConstraintT<hypro::tNumber>> flowConstraints = createReverseFlowConstraints<hypro::tNumber, Number>( v, newV, t, flow.getFlowIntervalForDimension( v ) );
                for ( const auto& c : flowConstraints ) {
                    std::cout << c << std::endl;
                }

#ifdef HYPRO_LOGGING
                TRACE( "hypro.worker", "Use flow constraints: " );
			for ( const auto& c : flowConstraints ) {
				TRACE( "hypro.worker", c );
			}
#endif

                bad.addConstraints( flowConstraints );

                if (initialConditions.has_value()) {
                    for(auto& condition : initialConditions.value()) {
                        std::cout << "condition: " << condition.first << " " << condition.second << std::endl;
                        auto carlvar = vpool.carlVarByIndex(condition.first);
                        auto interval = condition.second;
                        std::cout << "carlvar: " << carlvar << ", interval: [" << interval.lower() << ", " << interval.upper() << "], v: " << v << std::endl;
                        if (v == carlvar) {
                            ConstraintT<hypro::tNumber> lower_bound = ConstraintT<hypro::tNumber>( PolyT<hypro::tNumber>( v ) - interval.upper(), carl::Relation::LEQ );
                            ConstraintT<hypro::tNumber> upper_bound = ConstraintT<hypro::tNumber>( PolyT<hypro::tNumber>( v ) - interval.lower(), carl::Relation::GEQ );
                            std::cout << "lower_bound: " << lower_bound << " upper_bound: " << upper_bound << std::endl;
                            bad.addConstraint(lower_bound);
                            bad.addConstraint(upper_bound);
                        }
                    }
                }

                 if (stochJumpAndMappedDim.has_value()) {
                     std::cout << "stochJumpAndMappedDim: " << stochJumpAndMappedDim.value().first << ", " << stochJumpAndMappedDim.value().second << std::endl;
                     auto carlvarbyindexJump = vpool.carlVarByIndex(stochJumpAndMappedDim.value().first);
                     auto carlvarbyindexMappedDim = vpool.carlVarByIndex(stochJumpAndMappedDim.value().second);
                     std::cout << "carlvarbyindexJump: " << carlvarbyindexJump << ", carlvarbyindexMappedDim: " << carlvarbyindexMappedDim << ", v: " << v << std::endl;
                     if (v == carlvarbyindexJump) {
                         // ConstraintT<hypro::tNumber> zeroConstraint_lower = ConstraintT<hypro::tNumber>( PolyT<hypro::tNumber>( v ), carl::Relation::LEQ );
                         // ConstraintT<hypro::tNumber> zeroConstraint_upper = ConstraintT<hypro::tNumber>( PolyT<hypro::tNumber>( v ), carl::Relation::GEQ );
                         // std::cout << "zeroConstraintLower: " << zeroConstraint_lower << " zeroConstraintUpper: " << zeroConstraint_upper << std::endl;
                         // bad.addConstraint(zeroConstraint_lower);
                         // bad.addConstraint(zeroConstraint_upper);
                         std::cout << "as v == carlvarbyindexJump holds, add zero constraint for v" << std::endl;
                         ConstraintT<hypro::tNumber> zeroConstraint = ConstraintT<hypro::tNumber>( PolyT<hypro::tNumber>( v ), carl::Relation::EQ );
                         std::cout << "zeroConstraint: " << zeroConstraint << std::endl;
                         bad.addConstraint(zeroConstraint);
                     }
                 }

            }
        }

        if (firstEnabledIndex.has_value()) {
            std::cout << "firstEnabledIndex: " << firstEnabledIndex.value().first << ", " << firstEnabledIndex.value().second << std::endl;
            auto carlvarbyindex = vpool.carlVarByIndex(firstEnabledIndex.value().first);
            std::cout << "carlvarbyindex: " << carlvarbyindex << std::endl;
            auto carlvarbyindex2 = vpool.carlVarByIndex(firstEnabledIndex.value().second);
            std::cout << "carlvarbyindex2: " << carlvarbyindex2 << std::endl;


            std::optional<carl::Variable> current_var;
            std::optional<carl::Variable> current_var_instance;

            for (const auto& v : bad.getVariables()) {
                std::string vname = v.name();
                std::string carlvarname = carlvarbyindex.name();
                std::string carlvarnameprime = carlvarname.append("_prime");

                std::string carlvarname2 = carlvarbyindex2.name();
                std::string carlvarname2prime = carlvarname2.append("_prime");

                if (vname == carlvarnameprime) {
                    std::cout << "vname == carlvarnameprime: " << vname << ", " << carlvarnameprime << std::endl;
                    current_var = v;
                } else if (vname == carlvarname2prime) {
                    std::cout << "vname == carlvarname2prime: " << vname << ", " << carlvarname2prime << std::endl;
                    current_var_instance = v;
                }
            }

            if (current_var.has_value() && current_var_instance.has_value()) {
                // std::cout << "found firstEnabledIndex and firstEnabledIndexPrime, "
                ConstraintT<hypro::tNumber> saveInstanceValueConstraint = ConstraintT<hypro::tNumber>( PolyT<hypro::tNumber>( current_var.value() ) - PolyT<hypro::tNumber>( current_var_instance.value() ), carl::Relation::EQ );
                std::cout << "saveInstanceValueConstraint: " << saveInstanceValueConstraint << std::endl;
                bad.addConstraint(saveInstanceValueConstraint);
            }


        }

        // add invariant constraints, if the invariant is specified and does not represent the empty set
        if ( !invariant.isTrue() ) {
            if ( invariant.isFalse() ) {
                return CarlPolytope<Number>::Empty();
            } else {
                auto invariantConstraints = halfspacesToConstraints<Number, hypro::tNumber>( invariant.getMatrix(), invariant.getVector() );
                bad.addConstraints( invariantConstraints );
            }
        }

        TRACE( "hypro.worker", "Full constraint set describing the dynamic behavior: \n"
                << bad );

        std::cout << "Full constraint set describing the dynamic behavior: \n" << bad << std::endl;

        if(REMOVE_REDUNDANDY_IN_QE) {
            TRACE("qe.redundancy_check", "number of constraints during elimination: ");
            // reverse order to for detectDimension() to work properly.
            // If ordering of elimination is changed, dimension has to be set manually.
            std::reverse(variablesToEliminate.begin(),variablesToEliminate.end());

            // create variables to eliminate
            QEQuery quOrder;
            quOrder.push_back( std::make_pair( QuantifierType::EXISTS, variablesToEliminate ) );

            // vpool.size() at this point already reflects t and all post/prime variables just created
            // above, so it is always large enough to index any variable referenced in bad, regardless of
            // poolGap (unlike the previous `dim + variablesToEliminate.size() + 1`, which assumed no gap).
            bad.setDimension( vpool.size() );
            std::cout << "dimension of bad: \n" << bad << "\n set to: " << vpool.size() << std::endl;

            //TODO removed redundancy for now because of s_r=0 could cause problems.
            // bad.removeRedundancy();
            bad.eliminateVariablesSuccessivelyWithRedundancyCheck( quOrder );

            quOrder.at(0).second = std::vector<carl::Variable>{t};

            assert(bad.dimension() == dim + poolGap + 1);

            bad.eliminateVariablesSuccessivelyWithRedundancyCheck( quOrder );
            TRACE("qe.redundancy_check", "\n");
        } else {
            TRACE("qe.redundancy_check", "number of constraints during elimination: ");
            // create variables to eliminate
            variablesToEliminate.push_back(t);

            QEQuery quOrder;
            quOrder.push_back( std::make_pair( QuantifierType::EXISTS, variablesToEliminate ) );
            bad.eliminateVariables( quOrder );
            TRACE("qe.redundancy_check", "\n");
        }
        assert(bad.dimension() == dim + poolGap);
        // the poolGap dimensions were never referenced by bad (they belong to variables some other,
        // unrelated part of the pool is using) and were only carried along so intermediate elimination
        // steps had enough room to index into; strip them back off so the result has the same dimension
        // as badSet, as callers expect.
        bad.setDimension( dim );

        DEBUG( "hydra.worker", "State set after reverse time elapse: " << bad );

        std::cout << "State set after reverse time elapse: \n" << bad << std::endl;

        return bad;
    }

    template <typename Number>
    CarlPolytope<Number> rectangularApplyReverseTimeEvolution( const CarlPolytope<Number>& badSet, const Location<Number>* loc ) {
        auto flow = loc->getRectangularFlow();
        auto invariant = loc->getInvariant();
        return rectangularApplyReverseTimeEvolution(badSet, flow, invariant);
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
