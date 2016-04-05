#include "Reach.h"
#include <chrono>

namespace hypro {
namespace reachability {

	using clock = std::chrono::high_resolution_clock;
	using timeunit = std::chrono::microseconds;

	template<typename Number, typename Representation>
	Reach<Number,Representation>::Reach( const HybridAutomaton<Number>& _automaton, const ReachabilitySettings<Number>& _settings)
		: mAutomaton( _automaton ), mSettings(_settings) {
		}

    template<typename Number, typename Representation>
	std::vector<flowpipe_t<Representation>> Reach<Number,Representation>::computeForwardReachability() {
		// set up working queue
		for ( const auto& initialPair : mAutomaton.initialStates() ) {
			std::cout << "INITIAL SET " << Representation(initialPair.second.first, initialPair.second.second) << std::endl;
			std::cout << "INITIAL VERTICES " << std::endl;
			for(const auto& vertex : Representation(initialPair.second.first, initialPair.second.second).vertices())
				std::cout << vertex << std::endl;

			mWorkingQueue.emplace(initialSet<Number,Representation>(0, initialPair.first, Representation(initialPair.second.first, initialPair.second.second)));
		}

		while ( !mWorkingQueue.empty() ) {
			initialSet<Number,Representation> nextInitialSet = mWorkingQueue.front();
			mWorkingQueue.pop();

			flowpipe_t<Representation> newFlowpipe = computeForwardTimeClosure(boost::get<1>(nextInitialSet), boost::get<2>(nextInitialSet));

			// TODO: Check for fixed point.
			if(mReachableStates.find(boost::get<1>(nextInitialSet)) == mReachableStates.end())
				mReachableStates[boost::get<1>(nextInitialSet)] = std::vector<flowpipe_t<Representation>>();

			mReachableStates[boost::get<1>(nextInitialSet)].push_back(newFlowpipe);

			if(boost::get<0>(nextInitialSet) < mSettings.jumpDepth) {
				std::vector<initialSet<Number,Representation>> newInitialSets = computeDiscreteJump(boost::get<0>(nextInitialSet), boost::get<1>(nextInitialSet), newFlowpipe);
				for(const auto& item : newInitialSets)
					mWorkingQueue.push(item);
			}
		}

		// collect all computed reachable states
		std::vector<flowpipe_t<Representation>> collectedReachableStates;
		for(const auto& statePair : mReachableStates) {
			for(const auto& flowpipe : statePair.second){
				collectedReachableStates.push_back(flowpipe);
			}
		}
		return collectedReachableStates;
	}

	template<typename Number, typename Representation>
	flowpipe_t<Representation> Reach<Number,Representation>::computeForwardTimeClosure( hypro::Location<Number>* _loc, const Representation& _val ) {
#ifdef REACH_DEBUG
		hypro::Plotter<Number>& plotter = hypro::Plotter<Number>::getInstance();
		std::cout << "Time Interval: " << mSettings.timeStep << std::endl;
		std::cout << "Initial valuation: " << std::endl;
		_val.print();
#endif
		// new empty Flowpipe
		flowpipe_t<Representation> flowpipe;

		// check if initial Valuation fulfills Invariant
		std::pair<bool, Representation> initialPair = _val.satisfiesHalfspaces(_loc->invariant().mat, _loc->invariant().vec);
#ifdef REACH_DEBUG
		std::cout << "Valuation fulfills Invariant?: ";
		std::cout << initialPair.first << std::endl;
#endif

		//initial = initial.reduce_directed(computeTemplate<Number>(2, 5), HPolytope<Number>::REDUCTION_STRATEGY::DIRECTED_TEMPLATE);

		if ( initialPair.first ) {
			// approximate R_[0,delta](X0)
			// rest is acquired by linear Transformation
			// R_0(X0) is just the initial Polytope X0, since t=0 -> At is zero matrix -> e^(At) is 'Einheitsmatrix'
			hypro::matrix_t<Number> deltaMatrix( _loc->flow().rows(), _loc->flow().cols() );
			deltaMatrix = _loc->flow() * mSettings.timeStep;

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
			doubleMatrix = hypro::convert<Number,double>( deltaMatrix );
			expMatrix = doubleMatrix.exp();
			resultMatrix = hypro::convert<double,Number>( expMatrix );

#ifdef REACH_DEBUG
			std::cout << "e^(deltaMatrix): " << std::endl;
			std::cout << resultMatrix << std::endl;
			std::cout << "------" << std::endl;
#endif

			// e^(At)*X0 = polytope at t=delta
			unsigned rows = resultMatrix.rows();
			unsigned cols = resultMatrix.cols();
			vector_t<Number> translation = resultMatrix.col( cols - 1 );
			translation.conservativeResize( rows - 1 );
			resultMatrix.conservativeResize( rows - 1, cols - 1 );

			Representation deltaValuation = initialPair.second.linearTransformation( resultMatrix, translation );

			//unsigned deltaSet = plotter.addObject(deltaValuation.vertices());
			//plotter.setObjectColor(deltaSet, colors[lila]);

#ifdef REACH_DEBUG
			std::cout << "Polytope at t=delta: ";
			deltaValuation.print();
#endif

			// R_0(X0) U R_delta(X0)
			Representation unitePolytope = initialPair.second.unite( deltaValuation );
			assert(unitePolytope.contains(initialPair.second));
			assert(unitePolytope.contains(deltaValuation));

#ifdef REACH_DEBUG
			std::cout << "Polytope after unite with R0: ";
			unitePolytope.print();
#endif
			// bloat hullPolytope (Hausdorff distance)
			Representation firstSegment;
			Number radius;
			radius = hausdorffError( Number( mSettings.timeStep ), _loc->flow(), initialPair.second.supremum() );
			assert(radius > 0);

#ifdef REACH_DEBUG
			std::cout << "\n";
			std::cout << "Hausdorff Approximation: ";
			std::cout << radius << std::endl;
#endif

			Representation hausPoly = hypro::computePolytope<Number, Representation>( unitePolytope.dimension(), radius );

#ifdef REACH_DEBUG
			std::cout << "Hausdorff Polytope (Box): ";
			hausPoly.print();
			std::cout << std::endl;
#endif

			// hullPolytope +_minkowski hausPoly
			firstSegment = unitePolytope.minkowskiSum( hausPoly );

			//unsigned delt = plotter.addObject(deltaValuation.vertices());
			//plotter.setObjectColor(delt, colors[red]);
			//unsigned unite = plotter.addObject(unitePolytope.vertices());
			//plotter.setObjectColor(unite, colors[orange]);
			//unsigned hull = plotter.addObject(firstSegment.vertices());
			//plotter.setObjectColor(hull, colors[petrol]);
//
			//plotter.plot2d();
			assert(firstSegment.contains(unitePolytope));
			assert(firstSegment.contains(initialPair.second));
			assert(firstSegment.contains(deltaValuation));


#ifdef REACH_DEBUG
			std::cout << "first Flowpipe Segment (after minkowski Sum): ";
			firstSegment.print();


#endif

//clock::time_point start = clock::now();

// (use_reduce_memory==true) apply clustering and reduction on segments for memory reduction
// (use_reduce_time==true) apply reduction on firstSegment for time reduction
#ifdef USE_REDUCTION
			unsigned CONVEXHULL_CONST = 20, REDUCE_CONST=8;
			std::vector<vector_t<Number>> directions = computeTemplate<Number>(2, REDUCE_CONST);

			bool use_reduce_memory=false, use_reduce_time=true;

			// obejcts for use_reduce_memory
			unsigned segment_count=0;
			std::vector<Point<Number>> points_convexHull;

			for(auto vertex: firstSegment.vertices()){ // cover firstSegment in clustering
				if(std::find(points_convexHull.begin(),points_convexHull.end(), vertex)==points_convexHull.end()){
					points_convexHull.push_back(vertex);
				}
			}

			// option 1: use uniform distirbution of REDUCE_CONST directions in all dimension-pairs (use_reduce_memory or use_reduce_time)
			// option 2: use directions of guards and invariants (use_reduce_time)
			// option 3: use uniform distirbution of firstSegment.size/2 directions in all dimension-pairs (use_reduce_time)

			if(use_reduce_time){
				// option 2

				//for(auto transition: _loc->transitions()){	// reduction memory guard mode
				//	auto guard= transition->guard();
				//	for(unsigned i=0; i<guard.mat.rows(); i++){
				//		vector_t<Number> guard_vector = vector_t<Number>(2);
				//		guard_vector(0)=guard.mat(i,0);
				//		guard_vector(1)=guard.mat(i,1);
				//		directions.push_back(guard_vector);
				//	}
				//}
				//for(unsigned inv_index=0; inv_index<invariant.size(); ++inv_index){ // reduction memory invariant mode
				//	directions.push_back(invariant.constraints().at(inv_index).normal());
				//}

				firstSegment = firstSegment.reduce_directed(directions, HPolytope<Number>::REDUCTION_STRATEGY::DIRECTED_TEMPLATE);

				// option 3
				//int reduce_calculated = ceil(firstSegment.size()/2);
				//if(reduce_calculated>2){
				//	firstSegment = firstSegment.reduce_directed(computeTemplate<Number>(2, reduce_calculated), HPolytope<Number>::REDUCTION_STRATEGY::DIRECTED_TEMPLATE);
				//}
			}
#endif

			firstSegment.removeRedundancy();

			// set the last segment of the flowpipe
			Representation lastSegment = firstSegment.intersectHalfspaces( _loc->invariant().mat, _loc->invariant().vec );
			// insert first Segment into the empty flowpipe
			flowpipe.push_back( lastSegment );

			//{
			//	unsigned t = plotter.addObject(lastSegment.vertices());
			//	plotter.setObjectColor(t, colors[lila]);
			//}

			// Polytope after linear transformation
			Representation transformedSegment;

#ifdef REACH_DEBUG
			std::cout << "--- Loop entered ---" << std::endl;
#endif

			// for each time interval perform linear Transformation
			std::size_t steps = carl::toInt<std::size_t>(carl::ceil(Number(mSettings.timeBound / mSettings.timeStep)));
			for ( std::size_t i = 2; i <= steps ; ++i ) {
				std::cout << "\rTime: \t" << carl::toDouble(i*mSettings.timeStep) << std::flush;

				// perform linear transformation on the last segment of the flowpipe
				assert(lastSegment.linearTransformation(resultMatrix, translation).size() == lastSegment.size());
				transformedSegment = lastSegment.linearTransformation( resultMatrix, translation );

				// extend flowpipe (only if still within Invariant of location)
				std::pair<bool, Representation> newSegment = transformedSegment.satisfiesHalfspaces( _loc->invariant().mat, _loc->invariant().vec );

#ifdef REACH_DEBUG
				std::cout << "Next Flowpipe Segment: ";
				transformedSegment.print();

				std::cout << "still within Invariant?: ";
				std::cout << newSegment.first << std::endl;
				//std::cout << "Intersection result: " << newSegment.second << std::endl;
#endif
#ifdef USE_REDUCTION
				// clustering CONVEXHULL_CONST and reduction with directions generated before
				if(use_reduce_memory){
					if(CONVEXHULL_CONST==1){ // if no clustering is required
						if(newSegment.first){
							Representation poly_smoothed = newSegment.reduce_directed(directions, HPolytope<Number>::REDUCTION_STRATEGY::DIRECTED_TEMPLATE);
							flowpipe.insert(flowpipe.begin(), poly_smoothed);
						}
					}
					else{
						if(newSegment.first){
							// collect points
							for(auto vertex: newSegment.vertices()){
								if(std::find(points_convexHull.begin(),points_convexHull.end(), vertex)==points_convexHull.end()){
									points_convexHull.push_back(vertex);
								}
							}
							segment_count++;
						}

						// compute convexHull and reduction of clustered segments
						if(!points_convexHull.empty() && (segment_count==CONVEXHULL_CONST || !newSegment.first)){
							auto facets = convexHull(points_convexHull);

							std::vector<Halfspace<Number>> Halfspaces;
							for(unsigned i = 0; i<facets.first.size(); i++){
								Halfspaces.push_back(facets.first.at(i)->Halfspace());
							}
							Representation convexHull = Representation(Halfspaces);

							convexHull = convexHull.reduce_directed(directions, HPolytope<Number>::REDUCTION_STRATEGY::DIRECTED_TEMPLATE);
							convexHull.removeRedundancy();
							flowpipe.insert(flowpipe.begin(), convexHull);

							points_convexHull.clear();
							segment_count = 0;
						}
					}
				}
#endif

				if ( newSegment.first ) {
#ifdef USE_REDUCTION
					if(i>3 && use_reduce_memory) flowpipe.erase(flowpipe.end()-2); // keep segments necessary to compute a precise jump and delete others
#endif
					flowpipe.push_back( newSegment.second );

					// update lastSegment
					lastSegment = newSegment.second;
				} else {
					break;
				}
			}
			//double timeOfReachReduction = (double) std::chrono::duration_cast<timeunit>( clock::now() - start ).count()/1000;
			//std::cout << std::endl << "Total time for loop(HYPRO): " << timeOfReachReduction << std::endl;
			//std::cout << std::endl;
#ifdef REACH_DEBUG
			std::cout << "--- Loop left ---" << std::endl;
			std::cout << "flowpipe: " << flowpipe.size() << " Segments computed." << std::endl;
#endif

			return flowpipe;
		} else {
			// return an empty flowpipe
			return flowpipe;
		}
	}

	template<typename Number, typename Representation>
	std::vector<initialSet<Number,Representation>> Reach<Number,Representation>::computeDiscreteJump( unsigned _currentLevel, Location<Number>* _location, const flowpipe_t<Representation>& _flowpipe ) {
		std::vector<initialSet<Number,Representation>> newInitialStates;

		// for each outgoing transition of the location
		std::set<Transition<Number>*> loc_transSet = _location->transitions();
		for ( typename std::set<Transition<Number>*>::iterator transitionIt = loc_transSet.begin();
			  transitionIt != loc_transSet.end(); ++transitionIt ) {
			hypro::Transition<Number>* transition = *transitionIt;

			#ifdef REACH_DEBUG
			std::cout << "Consider transition " << *transition << std::endl;
			#endif

			// resulting Polytope in new location
			std::vector<Point<Number>> collectedVertices;
			bool transitionEnabled = false;

			// for each polytope that is part of the flowpipe
			for ( auto segmentIt = _flowpipe.begin(); segmentIt != _flowpipe.end(); ++segmentIt ) {
				// check if guard of transition is enabled (if yes compute Post Assignment Valuation)
				Representation postAssign;
				if ( intersectGuard( transition, *segmentIt, postAssign ) ) {
					transitionEnabled = true;
					// if no aggregation takes place, insert each new set independently
					if(transition->aggregation() == Aggregation::none){
						newInitialStates.emplace_back(_currentLevel+1, transition->target(), postAssign);
					} else {
						std::vector<Point<Number>> tmpVertices = postAssign.vertices();
						collectedVertices.insert(collectedVertices.end(), tmpVertices.begin(), tmpVertices.end());
					}
				}
			}
			if ( transitionEnabled && transition->aggregation() != Aggregation::none) {
				assert(!collectedVertices.empty());
				newInitialStates.emplace_back(_currentLevel+1, transition->target(), Representation(collectedVertices));
			}
		}
		return newInitialStates;
	}

	template<typename Number, typename Representation>
	bool Reach<Number,Representation>::intersectGuard( hypro::Transition<Number>* _trans, const Representation& _segment,
							   Representation& result ) {

		std::pair<bool, Representation> guardSatisfyingSegment = _segment.satisfiesHalfspaces( _trans->guard().mat, _trans->guard().vec );

		// check if the intersection is empty
		if ( guardSatisfyingSegment.first ) {
			#ifdef REACH_DEBUG
			std::cout << "Transition enabled!" << std::endl;
			#endif

			hypro::vector_t<Number> translateVec = _trans->reset().vec;
			hypro::matrix_t<Number> transformMat = _trans->reset().mat;

			// perform translation + transformation on intersection polytope
			result = guardSatisfyingSegment.second.linearTransformation( transformMat, translateVec );

			return true;
		} else {
			return false;
		}
	}

	template<typename Number, typename Representation>
	void Reach<Number,Representation>::printFlowpipe( const flowpipe_t<Representation>& _flowpipe ) const {
		for ( const auto& segment : _flowpipe ) {
			std::cout << segment << ", " << std::endl;
		}
	}

	template<typename Number, typename Representation>
	void Reach<Number,Representation>::printFlowpipeReduced( const flowpipe_t<Representation>& _flowpipe ) const {
		std::cout << *_flowpipe.begin() << ", " << std::endl;
		std::cout << "(...)" << std::endl;
		std::cout << *_flowpipe.back() << std::endl;
	}
}
}
