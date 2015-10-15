#include "Reach.h"

namespace hypro {
namespace reachability {

	template<typename Number, typename Representation>
	Reach<Number,Representation>::Reach( const HybridAutomaton<Number, Representation>& _automaton, const ReachabilitySettings<Number> _settings)
		: mAutomaton( _automaton ), mSettings(_settings), mFlowpipes(), mReach() {
		std::size_t initId = addFlowpipe( std::move( flowpipe_t<Representation>( {_automaton.initialValuation()} ) ) );
		for ( const auto loc : _automaton.initialLocations() ) {
			// use insert here as we assume that every location is only put in once. TODO: Extend for more flexibility.
			mReach.insert( std::make_pair( loc, std::vector<std::size_t>( {initId} ) ) );
			mFlowToLocation.insert( std::make_pair( initId, loc ) );
		}
		// at this point every initial location is assigned the valuation.
	}

	template<typename Number, typename Representation>
	std::size_t Reach<Number,Representation>::addFlowpipe( const flowpipe_t<Representation>& _flowpipe ) {
		mFlowpipes.insert( std::make_pair( id++, _flowpipe ) );
		return id - 1;
	}

	template<typename Number, typename Representation>
	const flowpipe_t<Representation>& Reach<Number,Representation>::getFlowpipe( std::size_t _index ) const {
		assert( mFlowpipes.find( _index ) != mFlowpipes.end() );
		return mFlowpipes.at( _index );
	}

	template<typename Number, typename Representation>
	std::set<std::size_t> Reach<Number,Representation>::computeForwardReachability() {
		std::size_t depth = 0;
		std::set<std::size_t> R_new;
		std::set<std::size_t> R;

		// R_new := flowpipe for the initial location, computed based on input valuation
		for ( const auto& locPair : mReach ) {
			std::cout << "Compute time-step in initial states." << std::endl;
			// TODO: Somehow catch error case where no forwardTimeClosure could be computed.
			std::size_t flowPipeIndex = mReach.at( locPair.first ).back();
			std::size_t init = computeForwardTimeClosure( locPair.first, *( mFlowpipes.at( flowPipeIndex ).begin() ) );
			std::cout << "Computed flowpipe: " << std::endl;
			printFlowpipeReduced( init );
			mReach.at( locPair.first ).push_back( init );
			R_new.insert( init );
		}

		std::cout << "R_new: ";
		for ( const auto& item : R_new ) std::cout << item << " ";
		std::cout << std::endl;

		while ( !R_new.empty() && depth < mSettings.iterationDepth ) {
			std::cout << "Main loop, depth " << depth << std::endl;
			// R = R U R_new
			if ( !R.empty() ) {
				std::set_union( R.begin(), R.end(), R_new.begin(), R_new.end(), std::inserter( R, R.begin() ) );
			} else {
				R = R_new;
			}
			std::cout << "R_new U R = ";
			for ( const auto& item : R ) std::cout << item << " ";
			std::cout << std::endl;

			// R_new = Reach(R_new)\R
			std::set<std::size_t> R_temp = computeReach( R_new );

			std::set_difference( R_temp.begin(), R_temp.end(), R.begin(), R.end(),
								 std::inserter( R_new, R_new.begin() ) );

			++depth;
		}
		return R;
	}

	template<typename Number, typename Representation>
	std::size_t Reach<Number,Representation>::computeForwardTimeClosure( hypro::Location<Number>* _loc, const Representation& _val ) {
		// hypro::Plotter<Number>& plotter = hypro::Plotter<Number>::getInstance();
		//[0,T] = [0,delta1] U [delta1, delta2] ...
		// note: interval size is constant
		Number timeInterval = mSettings.timebound / mSettings.discretization;

// plotter.addObject(_val.vertices());

#ifdef REACH_DEBUG
		std::cout << "Time Interval: " << timeInterval << std::endl;

		std::cout << "Initial valuation: " << std::endl;
		_val.print();

#endif

		// Polytope that is defined by the invariant
		Representation poly = Representation( _loc->invariant().mat, _loc->invariant().vec );

#ifdef REACH_DEBUG
		std::cout << "invariant Polytope: ";
		poly.print();
#endif

		// new empty Flowpipe
		flowpipe_t<Representation> flowpipe;
		// add initial valuation
		flowpipe.push_back( _val );

// check if initial Valuation fulfills Invariant
#ifdef REACH_DEBUG
		std::cout << "Valuation fulfills Invariant?: ";
		std::cout << !poly.intersect( _val ).empty() << std::endl;
		//std::cout << poly.contains( _val ) << std::endl;
#endif

		if ( poly.contains( _val ) ) {
			// approximate R_[0,delta](X0)
			// rest is acquired by linear Transformation
			// R_0(X0) is just the initial Polytope X0, since t=0 -> At is zero matrix -> e^(At) is 'Einheitsmatrix'
			hypro::matrix_t<Number> deltaMatrix( _loc->activityMat().rows(), _loc->activityMat().cols() );
			deltaMatrix = _loc->activityMat() * timeInterval;

#ifdef REACH_DEBUG
			std::cout << "delta Matrix: " << std::endl;
			std::cout << deltaMatrix << std::endl;
			std::cout << "------" << std::endl;
#endif

			// e^(At) = resultMatrix
			hypro::matrix_t<Number> resultMatrix( deltaMatrix.rows(), deltaMatrix.cols() );

			//---
			// Workaround for:
			// resultMatrix = deltaMatrix.exp();
			//-> convert FLOAT_T to double, compute .exp(), then convert back to FLOAT_T
			Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> doubleMatrix( deltaMatrix.rows(),
																				deltaMatrix.cols() );
			Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> expMatrix( deltaMatrix.rows(), deltaMatrix.cols() );
			doubleMatrix = hypro::convertMatToDouble( deltaMatrix );
			expMatrix = doubleMatrix.exp();
			resultMatrix = hypro::convertMatToFloatT<Number>( expMatrix );

#ifdef REACH_DEBUG
			std::cout << "e^(deltaMatrix): " << std::endl;
			std::cout << resultMatrix << std::endl;
			std::cout << "------" << std::endl;
#endif

			//---

			// e^(At)*X0 = polytope at t=delta
			unsigned rows = resultMatrix.rows();
			unsigned cols = resultMatrix.cols();
			vector_t<Number> translation = resultMatrix.col( cols - 1 );
			translation.conservativeResize( rows - 1 );
			resultMatrix.conservativeResize( rows - 1, cols - 1 );
			std::cout << "A: " << resultMatrix << ", b: " << translation << std::endl;
			//plotter.addObject(_val.vertices());

			std::cout << "Linear transformation." << std::endl;
			Representation deltaValuation = _val.linearTransformation( resultMatrix, translation );
			//plotter.addObject(deltaValuation.vertices());

#ifdef REACH_DEBUG
			std::cout << "Polytope at t=delta: ";
			deltaValuation.print();
#endif

			// R_0(X0) U R_delta(X0)
			Representation unitePolytope = _val.unite( deltaValuation );

#ifdef REACH_DEBUG
			std::cout << "Polytope after unite with R0: ";
			unitePolytope.print();
#endif

			// bloat hullPolytope (Hausdorff distance)
			Representation firstSegment;
			Number radius;
			// TODO: This is a temporary fix!
			// matrix_t<Number> updatedActivityMatrix = _loc->activityMat();
			// updatedActivityMatrix.conservativeResize(rows-1, cols-1);
			// radius = hausdorffError(Number(timeInterval), updatedActivityMatrix, _val.supremum());
			radius = hausdorffError( Number( timeInterval ), _loc->activityMat(), _val.supremum() );
// radius = _val.hausdorffError(timeInterval, _loc->activityMat());

#ifdef REACH_DEBUG
			std::cout << "\n";
			std::cout << "Hausdorff Approximation: ";
			std::cout << radius << std::endl;
#endif

			unsigned int dim;
			dim = unitePolytope.dimension();

			Representation hausPoly = hypro::computePolytope<Number, Representation>( dim, radius );

#ifdef REACH_DEBUG
			std::cout << "Hausdorff dimension: " << hausPoly.dimension() << std::endl;
			std::cout << "hullPolytope dimension: " << unitePolytope.dimension() << std::endl;
			std::cout << "Hausdorff Polytope (Box): ";
			hausPoly.print();
			std::cout << std::endl;
#endif

			// hullPolytope +_minkowski hausPoly
			firstSegment = unitePolytope.minkowskiSum( hausPoly );
// firstSegment = firstSegment.unite(firstSegment);

#ifdef REACH_DEBUG
			std::cout << "first Flowpipe Segment (after minkowski Sum): ";
			firstSegment.print();
			//plotter.addObject(firstSegment.vertices());
			//plotter.plot2d();
#endif

			// insert first Segment into the empty flowpipe
			flowpipe.push_back( firstSegment );

			// set the last segment of the flowpipe
			Representation lastSegment;
			lastSegment = firstSegment;

			// Polytope after linear transformation
			Representation resultPolytope;

#ifdef REACH_DEBUG
			std::cout << "--- Loop entered ---" << std::endl;
#endif

			// for each time interval perform linear Transformation
			for ( std::size_t i = 2; i <= mSettings.discretization; ++i ) {
				std::cout << "\rTime: \t" << i*timeInterval << std::flush;

				// perform linear transformation on the last segment of the flowpipe
				// lastSegment.linearTransformation(resultPolytope, tempResult);
				resultPolytope = lastSegment.linearTransformation( resultMatrix, translation );
				resultPolytope.reduce();
// resultPolytope = resultPolytope.hull();

#ifdef REACH_DEBUG
				std::cout << "Next Flowpipe Segment: ";
				resultPolytope.print();
				std::cout << "Empty: " << resultPolytope.empty() << std::endl;

				std::cout << "still within Invariant?: ";
				std::cout << !(poly.intersect( resultPolytope )).empty() << std::endl;
				std::cout << "Invariant: " << poly << std::endl;
				std::cout << "Intersection result: " << poly.intersect( resultPolytope ) << std::endl;
#endif

				// extend flowpipe (only if still within Invariant of location)
				if ( !(poly.intersect( resultPolytope )).empty() ) {
					flowpipe.push_back( resultPolytope );

					// update lastSegment
					lastSegment = resultPolytope;
				} else {
					break;
				}
			}
			std::cout << std::endl;

#ifdef REACH_DEBUG
			std::cout << "--- Loop left ---" << std::endl;
#endif

			std::size_t fpIndex = addFlowpipe( flowpipe );
			mFlowToLocation[fpIndex] = _loc;
			return fpIndex;

		} else {
			// return an empty flowpipe
			std::size_t fpIndex = addFlowpipe( flowpipe );
			mFlowToLocation[fpIndex] = _loc;
			return fpIndex;
		}
	}

	template<typename Number, typename Representation>
	std::set<std::size_t> Reach<Number,Representation>::computeReach( const std::set<std::size_t>& _init ) {
		std::set<std::size_t> reach;

		std::cout << __func__ << std::endl;

		// for each flowpipe in _init
		for ( auto it_pipe = _init.begin(); it_pipe != _init.end(); ++it_pipe ) {
			// get the location that belongs to the flowpipe
			hypro::Location<Number>* loc = mFlowToLocation[*it_pipe];

			std::cout << "Consider transitions for location " << *loc << std::endl;

			// for each outgoing transition of the location
			std::set<Transition<Number>*> loc_transSet = loc->transitions();
			for ( typename std::set<Transition<Number>*>::iterator it_trans = loc_transSet.begin();
				  it_trans != loc_transSet.end(); ++it_trans ) {
				hypro::Transition<Number> trans = *( *it_trans );

				std::cout << "Consider transition " << trans << std::endl;

				// resulting Polytope in new location
				Representation targetValuation;
				bool transitionEnabled = false;

				// for each polytope that is part of the flowpipe
				for ( typename flowpipe_t<Representation>::iterator it_val = mFlowpipes.at( *it_pipe ).begin();
					  it_val != mFlowpipes.at( *it_pipe ).end(); ++it_val ) {
					Representation postAssign;
					// check if guard of transition is enabled (if yes compute Post Assignment Valuation)
					if ( computePostCondition( trans, *it_val, postAssign ) ) {
						transitionEnabled = true;
						//std::cout << "Take transition " << trans << std::endl;

						std::cout << "Vertices: " << std::endl;
						for(const auto& vertex : postAssign.vertices() ) {
							std::cout << vertex << std::endl;
						}

						// targetValuation = targetValuation U postAssign
						if ( !targetValuation.empty() ) {
							targetValuation = targetValuation.unite( postAssign );
						} else {
							targetValuation = postAssign;
						}
					}
				}
				if ( transitionEnabled ) {
					// compute new Flowpipe
					hypro::Location<Number>* tarLoc = trans.target();

					std::cout << "Compute time-step in new location " << *tarLoc << " starting with initial valuation "
							  << targetValuation << std::endl;

					//std::cout << "Vertices: " << std::endl;
					//for(const auto& vertex : targetValuation.vertices() ) {
					//	std::cout << vertex << std::endl;
					//}

					Plotter<Number>::getInstance().plot2d();

					exit(0);

					// flowpipe_t<Representation> newPipe = computeForwardTimeClosure(tarLoc, hullPoly);
					std::size_t newPipe = computeForwardTimeClosure( tarLoc, targetValuation );

					// if new Flowpipe is not empty
					if ( !mFlowpipes.at( newPipe ).empty() ) {
						// expand reach
						reach.insert( newPipe );
					}
				}
			}
		}
		std::cout << __func__ << " end." << std::endl;
		return reach;
	}

	template<typename Number, typename Representation>
	bool Reach<Number,Representation>::computePostCondition( const hypro::Transition<Number>& _trans, const Representation& _val,
							   Representation& result ) {
		//std::cout << __func__ << std::endl;
		// intersection between valuation polytope and guard hyperplanes

		hypro::Plotter<Number>& plotter = hypro::Plotter<Number>::getInstance();

		Representation intersectionPoly = _val.intersectHyperplanes( _trans.guard().mat, _trans.guard().vec );

		// check if the intersection is empty
		if ( !intersectionPoly.empty() ) {
			std::cout << "Transition enabled!" << std::endl;

			plotter.addObject(_val.vertices());
			//plotter.addObject(intersectionPoly.vertices());
			//plotter.addObject(_val.constraints());


			hypro::vector_t<Number> translateVec = _trans.reset().translationVec;
			hypro::matrix_t<Number> transformMat = _trans.reset().transformMat;

			//std::cout << "Valuation enabling transition: " << std::endl << _val << std::endl;
			//std::cout << "Vertices: " << std::endl;
			//for(const auto& vertex : _val.vertices()) {
			//	std::cout << vertex.rawCoordinates().transpose() << std::endl;
			//}

			// perform translation + transformation on intersection polytope
			result = intersectionPoly.linearTransformation( transformMat, translateVec );

			//plotter.addObject(result.vertices());
			//plotter.plot2d();

			return true;
		} else {
			//std::cout << "Transition disabled!" << std::endl;
			return false;
		}
	}

	template<typename Number, typename Representation>
	void Reach<Number,Representation>::printFlowpipe( std::size_t _flowpipe ) const {
		for ( const auto& segment : mFlowpipes.at( _flowpipe ) ) {
			std::cout << segment << ", " << std::endl;
		}
	}

	template<typename Number, typename Representation>
	void Reach<Number,Representation>::printFlowpipeReduced( std::size_t _flowpipe ) const {
		std::cout << *mFlowpipes.at( _flowpipe ).begin() << ", " << std::endl;
		std::cout << "(...)" << std::endl;
		std::cout << mFlowpipes.at( _flowpipe ).back() << std::endl;
	}
}
}