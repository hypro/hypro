#include "stochasticRectangularProbabilityHandler.h"

namespace hypro {

template <typename State, typename Number>
void stochasticRectangularProbabilityHandler<State, Number>::calculateProbability(  const State& preStateSet, StochasticTransition<Number>* transitionPtr, Number prob,  const StochasticHybridAutomaton<typename State::NumberType>& automaton  ) {
	// intervalCalculation( preStateSet, stateSet, transitionPtr );

	Number currentProb = 0;
	bool isUnbounded = false;
	for (auto interval : mStateInterval ) {
		if( interval.lowerBoundType() == carl::BoundType::INFTY || interval.upperBoundType() == carl::BoundType::INFTY ) {
			isUnbounded = true;
		}
	}

	Number intervalVolume = 0;
	Number expLambda = 0;
	DistributionType distrType;
	if ( !isUnbounded ) {
		// preStateSet.getLocation()->setLocationDistributionType( DistributionType::UNIFORMED );
		distrType = DistributionType::UNIFORMED;
		for (auto interval : mStateInterval ) {
			intervalVolume += interval.upper() - interval.lower();
		}
	} else {
		//preStateSet.getLocation()->setLocationDistributionType( DistributionType::EXPONENTIAL );
		distrType = DistributionType::EXPONENTIAL;
		// StochasticLocation<Number>* stoLoc = dynamic_cast<StochasticLocation<Number>*>( preStateSet.getLocation() );
		// if ( !stoLoc ) {
		// 	expLambda = 1;
		// } else {
		// 	std::cout<<"find sto expLambda is: " << expLambda << std::endl;
		// 	expLambda =  stoLoc->getExpLambda();
		// }
		// std::cout<<"expLambda is: 2" << std::endl;
		// StochasticLocation<Number>* stoLoc = dynamic_cast<StochasticLocation<Number>*>( preStateSet.getLocation()->get() );
		for (auto loc : automaton.getLocations() ){
			if(loc == preStateSet.getLocation()) {
				StochasticLocation<Number>* stoLoc = dynamic_cast<StochasticLocation<Number>*>( loc );
				expLambda = stoLoc->getExpLambda();
			}
		}
	}

	auto intervalPtr = mDisjIntervals.begin();
	auto transSetPtr = mDisjTransitionSets.begin();

	while ( intervalPtr != mDisjIntervals.end() ) {
		if ( (intervalPtr->upper()-intervalPtr->lower()) > 0 ) {
			Number res = gslIntegration( distrType, intervalVolume, expLambda, *intervalPtr );
			// std::cout<<"gsl probability " << res <<std::endl;
			if ( transitionPtr->getTransitionWeight() != 0 ) {
				Number totalWeight = 0;
				for ( auto tranPtr : *transSetPtr) {
					// std::cout << "stoTransition is: " << *tranPtr << ", weight is: " << tranPtr->getTransitionWeight() << std::endl;
					totalWeight += tranPtr->getTransitionWeight();
				}
				res = res * transitionPtr->getTransitionWeight() / totalWeight ;
			}
			// std::cout<<"after weight probability is: " << res <<std::endl;
			currentProb += res;
			// std::cout<<"current probability is: " << currentProb <<std::endl;
		}
		intervalPtr++;
		transSetPtr++;
	}

	mProbability = currentProb * prob;
}
template <typename State, typename Number>
carl::Interval<Number> stochasticRectangularProbabilityHandler<State, Number>::timeInterval( const State& preStateSet, State& state, const rectangularFlow<Number>& flow, StochasticTransition<Number>* transitionPtr, bool isToTargetState ) {
	auto& vpool = hypro::VariablePool::getInstance();
	// get initial state
	CarlPolytope<Number> initial = std::get<CarlPolytope<Number>>( preStateSet.getSet() );
	// storage to build elimination query
	std::vector<carl::Variable> variablesToEliminate;
	std::set<carl::Variable> addedVariable;
	// add variable for time elapse
	carl::Variable t = vpool.newCarlVariable( "t" );

	// std::cout<<"location flow is: " << flow <<std::endl
	// 		 <<"pre state is: " << preStateSet <<std::endl
	// 		 <<"current state is: " <<state << std::endl;

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
			variablesToEliminate.push_back( v );
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
	// std::cout<<"constraints add flow: "<<initial<<std::endl;

	// auto guard = CarlPolytope<typename State::NumberType>{ transitionPtr->getGuard().getMatrix(), transitionPtr->getGuard().getVector() };
	// for (auto f : guard.getFormula().subformulas() ) {
	// 	std::cout << "guard constraints are: " << f << std::endl;
	// }
	// if (transitionPtr->getTransitionWeight() != 0 ) {
		if ( !transitionPtr->getGuard().empty() ) {
			// std::cout<<"not empty guard"<<std::endl;
			CarlPolytope<Number> guard{ transitionPtr->getGuard().getMatrix(), transitionPtr->getGuard().getVector() };
			std::vector<ConstraintT<tNumber>> guardConstraints;
			guard.getFormula().getConstraints( guardConstraints );
			initial.addConstraints( guardConstraints );
		}
		// std::cout<<"constraints add guard: "<<initial<<std::endl;

		if ( !transitionPtr->getReset().empty() ) {
			// std::cout<<"not empty reset"<<std::endl;
			CarlPolytope<Number> reset{ transitionPtr->getReset().getMatrix(), transitionPtr->getReset().getVector() };
			for ( const auto& v : reset.getVariables() ) {
				if ( v != t ) {
					// create primed var
					std::stringstream ss;
					ss << v.name() << "_post";
					std::string s = ss.str();
					auto newV = vpool.newCarlVariable( s );
					// substitute to create precondition
					reset.substituteVariable( v, newV );
					// store var to eliminate later
					variablesToEliminate.push_back( newV );
					addedVariable.emplace( newV );
				}
			}
			std::vector<ConstraintT<tNumber>> resetConstraints;
			reset.getFormula().getConstraints( resetConstraints );
			initial.addConstraints( resetConstraints );
		} else if ( isToTargetState ) {
			CarlPolytope<Number> currentSet = std::get<CarlPolytope<Number>>( state.getSet() );
			std::vector<ConstraintT<tNumber>> currentSetConstraints;
			currentSet.getFormula().getConstraints( currentSetConstraints );
			initial.addConstraints( currentSetConstraints );
		}
		//std::cout<<"constraints add reset: "<<initial<<std::endl;

		if ( !state.getLocation()->getInvariant().empty() ) {
			// std::cout<<"not empty invariant"<<std::endl;
			CarlPolytope<Number> invariant{ state.getLocation()->getInvariant().getMatrix(), state.getLocation()->getInvariant().getVector() };
			for ( const auto& v : invariant.getVariables() ) {
				if ( v != t ) {
					// create primed var
					std::stringstream ss;
					ss << v.name() << "_post";
					std::string s = ss.str();
					auto newV = vpool.newCarlVariable( s );
					// substitute to create precondition
					invariant.substituteVariable( v, newV );
					// store var to eliminate later
					if ( addedVariable.find(newV) == addedVariable.end() ) {
						variablesToEliminate.push_back( newV );
						addedVariable.emplace( newV );
					}
				}
			}
			std::vector<ConstraintT<tNumber>> invariantConstraints;
			invariant.getFormula().getConstraints( invariantConstraints );
			initial.addConstraints( invariantConstraints );
		}
	// }
	// std::cout<<"constraints add invariant: "<<initial<<std::endl;


	// create variables to eliminate
	QEQuery quOrder;
	quOrder.push_back( std::make_pair( QuantifierType::EXISTS, variablesToEliminate ) );
	// allow for some heuristics on how to eliminate
	initial.choseOrder( quOrder );

	// eliminate vars
	initial.eliminateVariables( quOrder );
	// std::cout<<"constraints eliminate: "<<initial<<std::endl;

	// std::vector<ConstraintT<tNumber>> newConstraints;
	// initial.getFormula().getConstraints( newConstraints );
	// for (auto c : initial.getIntervals() ) {
	// 	std::cout << "constraints are: " << c << std::endl;
	// }

	// DEBUG( "hydra.worker", "State set after time elapse: " << initial );

	// State res(preStateSet);
	// res.setSet(initial);

	return initial.getIntervals().back();
}

template <typename State, typename Number>
void stochasticRectangularProbabilityHandler<State, Number>::intervalCalculation( const State& preStateSet, State& stateSet, StochasticTransition<Number>* transitionPtr ) {
	auto locFlow = preStateSet.getLocation()->getRectangularFlow();
	bool isToTargetState = true;
    mTargetInterval = timeInterval( preStateSet, stateSet, locFlow, transitionPtr, isToTargetState );
	
	if (transitionPtr != NULL ){
		// std::cout<<"transitionPtr is not null"<<std::endl;
		mIntervals.emplace_back( mTargetInterval );

		std::vector<StochasticTransition<Number>*> transitionSet;
		transitionSet.emplace_back( transitionPtr );
		// std::cout<<"mInterval begin position: " << *mIntervals.begin() << ", " << *mIntervals.begin() <<std::endl;
		
		mTransitionSets.emplace_back( transitionSet );
	}
	//mEnabledTransitions.emplace( std::make_pair( mTargetInterval, transitionSet ) );
	// carl::Interval<Number> interval = mTargetInterval;
	// mEnabledTransitions.emplace( std::make_pair( interval, transitionSet ) );
	// std::cout<<"before all transition mEnabledTransitions size is: " << &mTargetInterval << std::endl;
	// for ( auto iss:mIntervals){
	// 	std::cout<<"target interval is: " << iss << std::endl;
	// 	for (auto second : mTransitionSets){
	// 		for (auto ptr : second ){
	// 			std::cout<<"transition is: " << ptr << std::endl;
	// 		}
	// 	}
	// }

    mStateInterval.emplace_back( mTargetInterval );
	// for ( auto& interval : mStateInterval ) {
	// 	std::cout << "interval of state is: " << interval << std::endl;
	// }
	if (transitionPtr->getTransitionWeight() != 0 ){
		for ( auto& transPtr : preStateSet.getLocation()->getTransitions() ) {
			StochasticTransition<Number>* stoTrans = dynamic_cast<StochasticTransition<Number>*>( transPtr.get() );
			if ( stoTrans != transitionPtr ) {	
				isToTargetState = false;
				auto interval = timeInterval( preStateSet, stateSet, locFlow, stoTrans, isToTargetState );
				// std::cout << "current interval not target: " << interval << std::endl;
					
				auto res = intervalIntersect( interval, mTargetInterval );
				if ( !res.isEmpty() ){
					// std::cout << "intersected interval: " << res << std::endl;
					std::vector<StochasticTransition<Number>*> transitionSet;
					transitionSet.emplace_back( transitionPtr );
					transitionSet.emplace_back( stoTrans );
					mEnabledTransitions.emplace( std::make_pair( res, transitionSet ) );
					mIntervals.emplace_back( res );
					mTransitionSets.emplace_back( transitionSet );
					// std::cout<<"find new mEnabledTransitions size is: " << mEnabledTransitions.size() << std::endl;
				}
				
				// std::cout << "before mStateInterval sorting " << std::endl;
				// calculate I(s)
				for (auto i = mStateInterval.begin() ; i < mStateInterval.end() ; i++ ){
					// std::cout << "mStateInterval sorting " << std::endl;
					auto tmp = i;
					Number lower_current =  interval.lower();
					Number upper_current = interval.upper();
					Number lower_tmp = tmp->lower();
					Number upper_tmp = tmp->upper();

					if ( upper_current < lower_tmp ){
						mStateInterval.insert( i, res );
						// std::cout << " upper_current < lower_tmp " << std::endl;
						break;
					}

					if ( upper_tmp < lower_current ) {
						// std::cout << " upper_tmp < lower_current " << std::endl;
						continue;
					}

					if ( lower_current < lower_tmp ){
						// std::cout << " lower_current < lower_tmp " << std::endl;
						lower_tmp = lower_current;
						tmp->setLower( lower_tmp );
					}

					if ( upper_tmp < upper_current ) {
						// std::cout << " upper_tmp < upper_current " << std::endl;
						interval.setLower( lower_tmp );
						interval.setUpper( upper_current );
						mStateInterval.erase( i );
						mStateInterval.emplace( i, interval );
						// std::cout << " current interval value is: " << interval << std::endl;
					}
				}
			}	
		}
		// std::cout<<"before all transition mEnabledTransitions size is: " << mEnabledTransitions.size() << std::endl;
		// for ( auto iss:mIntervals){
		// 	std::cout<<"after target interval is: " << iss << std::endl;
		// }

		// for (auto second : mTransitionSets){
		// 	std::cout<<"vector position flag" <<std::endl;
		// 	for (auto ptr : second ){
		// 		std::cout<<"transition is: " << ptr << std::endl;
		// 	}
		// }
		calculateDisjointIntervals();
	}
}

template <typename State, typename Number>
carl::Interval<Number> stochasticRectangularProbabilityHandler<State, Number>::intervalIntersect(carl::Interval<Number> lhs, carl::Interval<Number> rhs) {
    if ( lhs.upper() < rhs.lower() || rhs.upper() < lhs.lower() ) {
        return carl::Interval<Number>();
    }

    if ( rhs.contains( lhs ) ) {
        return lhs;
    }

    if ( lhs.contains( rhs ) ) {
        return rhs;
    }

    if ( rhs.contains( lhs.lower() ) ) {
        return carl::Interval<Number>( lhs.lower(), rhs.upper() );
    }

    if ( rhs.contains( lhs.upper() ) ) {
        return carl::Interval<Number>( rhs.lower(), lhs.upper() );
    }

    return carl::Interval<Number>();
}

template <typename State, typename Number>
void stochasticRectangularProbabilityHandler<State, Number>::calculateDisjointIntervals() {
	// std::cout << "enter disjont calculation" << std::endl;

    std::map<carl::Interval<Number>, std::vector<StochasticTransition<Number>*>> enabledIntervalTransitions;
	std::vector<carl::Interval<Number>> disjI;
	while ( !mIntervals.empty() ){	
		
		carl::Interval<Number> currentI = mIntervals.front();
		// std::cout<<"currentI is: " << currentI << std::endl;
		std::vector<StochasticTransition<Number>*> transitionSet = mTransitionSets.front();
		
		mIntervals.erase( mIntervals.begin() );
		mTransitionSets.erase( mTransitionSets.begin() );
		auto tmp = mIntervals.begin();
		auto tmpTran = mTransitionSets.begin();
		
		// size_t i = 0;
		while ( tmp != mIntervals.end() ) {
			carl::Interval<Number> tmpI = *tmp;
			std::vector<StochasticTransition<Number>*> tmpTransitionSet = *tmpTran;
			auto intersectInterval = intervalIntersect( currentI, tmpI );
			// std::cout<<"interval sets intersection!!!"<< intersectInterval <<std::endl;
			if ( !intersectInterval.isEmpty() ) {
				// std::cout<<"intersection not empty" << std::endl;
				if ( !intersectInterval.contains( currentI ) ) {
					// std::cout<<"complement of currentI not empty" << std::endl;
					auto complement = calculateComplement( currentI, intersectInterval );
					for (auto c : complement ){
						bool isInSet = false;
						for ( auto interval : mIntervals ){
							if ( interval == c ){
								isInSet = true;
								break;
							}
						}
						if ( !isInSet ) {
							mIntervals.emplace_back( c );
							mTransitionSets.emplace_back( transitionSet );
						}
					}
					
				}
				if ( !intersectInterval.contains( tmpI ) ) {
					// std::cout<<"complement of tmI not empty" << std::endl;
					auto complement = calculateComplement( tmpI, intersectInterval );
					for (auto c : complement ){
						bool isInSet = false;
						for ( auto interval : mIntervals ){
							if ( interval == c ){
								isInSet = true;
								break;
							}
						}
						if ( !isInSet ) {
							mIntervals.emplace_back( c );
							mTransitionSets.emplace_back( tmpTransitionSet );
						}
					}
					
				}

				for ( auto ptr : tmpTransitionSet ){
					bool isInSet = false;
					for (auto ptr2 : transitionSet ){
						if ( ptr == ptr2 ){
							isInSet = true;
							break;
						}
					}

					if ( !isInSet ) {
						transitionSet.emplace_back( ptr );
					}
				}
				currentI = intersectInterval;

				tmp++;
				tmpTran++;
				mIntervals.erase( tmp - 1 );
				mTransitionSets.erase( tmpTran - 1 );
			} else {
				tmp++;
				tmpTran++;
			}
		}
		mDisjIntervals.emplace_back( currentI );
		mDisjTransitionSets.emplace_back( transitionSet );
	}
	// for ( auto ii : mDisjIntervals ) {
	// 	std::cout << "after disjoint intervals is: " << ii <<std::endl;
	// }
	// for ( auto ii : mDisjTransitionSets ) {
	// 	std::cout << "after disjoint transitionSets is: " <<std::endl;
	// 	for ( auto i : ii ) {
	// 		std::cout << "transition is: " << i <<std::endl;
			
	// 	}
	// 	std::cout << "next set!!!" << std::endl;
	// }
}

template <typename State, typename Number>
std::vector<carl::Interval<Number>> stochasticRectangularProbabilityHandler<State, Number>::calculateComplement(carl::Interval<Number> lhs, carl::Interval<Number> rhs) {
	auto lhsLowerType = lhs.lowerBoundType();
	auto lhsUpperType = lhs.upperBoundType();
	auto rhsLowerType = rhs.lowerBoundType();
	auto rhsUpperType = rhs.upperBoundType();
	auto lhsLower = lhs.lower();
	auto lhsUpper = lhs.upper();
	auto rhsLower = rhs.lower();
	auto rhsUpper = rhs.upper();
	std::vector<carl::Interval<Number>> res;
	if ( lhsLowerType == rhsLowerType ) {
		if ( lhsLower < rhsLower ) {
			if ( rhsLowerType == carl::BoundType::STRICT ) {
				res.emplace_back( carl::Interval<Number>( lhsLower, lhsLowerType, rhsLower, carl::BoundType::WEAK ));
			}
			if ( rhsLowerType == carl::BoundType::WEAK ) {
				res.emplace_back( carl::Interval<Number>( lhsLower, lhsLowerType, rhsLower, carl::BoundType::STRICT ));
			}
		}
	} else {
		if ( rhsLowerType == carl::BoundType::STRICT ) {
			res.emplace_back( carl::Interval<Number>( lhsLower, lhsLowerType, rhsLower, carl::BoundType::WEAK ));
		} else {
			res.emplace_back( carl::Interval<Number>( lhsLower, lhsLowerType, rhsLower, carl::BoundType::STRICT ));
		}
	}

	if ( lhsUpperType == rhsUpperType ) {
		if ( lhsUpper > rhsUpper ) {
			if ( rhsUpperType == carl::BoundType::STRICT ) {
				res.emplace_back( carl::Interval<Number>( rhsUpper, carl::BoundType::WEAK, lhsUpper, lhsUpperType ));
			}
			if ( rhsUpperType == carl::BoundType::WEAK ) {
				res.emplace_back( carl::Interval<Number>( rhsUpper, carl::BoundType::STRICT, lhsUpper, lhsUpperType ));
			}
		}
	} else {
		if ( rhsUpperType == carl::BoundType::STRICT ) {
			res.emplace_back( carl::Interval<Number>( rhsUpper, carl::BoundType::WEAK, lhsUpper, lhsUpperType ));
		} else {
			res.emplace_back( carl::Interval<Number>( rhsUpper, carl::BoundType::STRICT, lhsUpper, lhsUpperType ));
		}
	}
	return res;
}

template <typename State, typename Number>
Number stochasticRectangularProbabilityHandler<State, Number>::gslIntegration( DistributionType type, Number intervalVolume, Number expLambda, carl::Interval<Number> interval ) {
	struct distributionParams<Number> params;

	if ( type == DistributionType::UNIFORMED ) {
		// std::cout<<"intervalVolume is: "<<intervalVolume<<std::endl;
		params = { 0, intervalVolume, 0, 0, 0 };
	} else if ( type == DistributionType::EXPONENTIAL ) {
		// params = { 0, 0, preStateSet.getLocation()->getExpLambda(), 0, 0 };
		params = { 0, 0, 2, 0, 0 };
	} else {
		//params = { 0, 0, 0, preStateSet.getLocation()->getNormalSigma(), preStateSet.getLocation()->getNormalMu() };
	}
	Number res, err;

	// Stefan: Defines the boundaries of the hyperbox which is the integration domain
	// To get those bounds, convert the set to a box and read lower and upper bounds of the intervals.
	Number xl[1] = { interval.lower() };
	Number xu[1] = { interval.upper() };

	// Stefan: Random number generator - we can just use the same.
	const gsl_rng_type* T;
	gsl_rng* r;

	// Stefan: The function "g" as given above is important and needs to be adapted
	// std::cout<<"function ptr is: "<< &(this->computeIntergration) <<std::endl;
	gsl_monte_function G = { &(this->computeIntergration), 1, &params };

	// Stefan: The number of calls - the more calls the higher the precision
	size_t calls = 500000;

	// Stefan: Some initialization of the workspace
	gsl_rng_env_setup();

	T = gsl_rng_default;
	r = gsl_rng_alloc( T );

	// Stefan: Here three different algorithms are used - I think we can stick to the Monte-Carlo Vegas method.
	{
		gsl_monte_vegas_state* s = gsl_monte_vegas_alloc( 1 );

		gsl_monte_vegas_integrate( &G, xl, xu, 1, calls, r, s,
								   &res, &err );
		// display_results( "vegas warm-up", res, err );

		//printf( "converging...\n" );

		// do {
		// 	gsl_monte_vegas_integrate( &G, xl, xu, 1, calls / 5, r, s,
		// 							   &res, &err );
		// 	printf(
		// 		  "result = % .6f sigma = % .6f "
		// 		  "chisq/dof = %.1f\n",
		// 		  res, err, gsl_monte_vegas_chisq( s ) );
		// } while ( fabs( gsl_monte_vegas_chisq( s ) - 1.0 ) > 0.5 );

		//display_results( "vegas final", res, err );

		gsl_monte_vegas_free( s );
	}

	gsl_rng_free( r );

	return res;
}

template <typename State, typename Number>
static Number stochasticRectangularProbabilityHandler<State, Number>::computeIntergration( Number* k, size_t dim, void* params) {
        (void)( dim ); /* avoid unused parameter warnings */
        (void)( params );

        struct distributionParams<Number> * fp = (struct distributionParams<Number> *)params;

        if ( ( fp->uniformedUpper - fp->uniformedLower) != 0 ) {
            return ( 1 / (fp->uniformedUpper - fp->uniformedLower) );
        }

        if ( fp->expLambda != 0 ) {
            return ( fp->expLambda * std::pow( M_E, -1 * fp->expLambda * k[0] ) );
        }

        if ( fp->normalSigma != 0 ) {
            return ( ( 1 / ( fp->normalSigma * ( std::sqrt( 2 * M_PI ) ) ) ) * std::pow( M_E, ( -1 /2) * std::pow( ( k[0] - fp->normalMu) / fp->normalSigma, 2 ) ) );
        }
    }


}  // namespace hypro