#include "Reach.h"
#include <chrono>

namespace hypro {
namespace reachability {

	using clock = std::chrono::high_resolution_clock;
	using timeunit = std::chrono::microseconds;

	template<typename Number, typename Representation>
	Reach<Number,Representation>::Reach( const HybridAutomaton<Number>& _automaton, const ReachabilitySettings<Number>& _settings)
		: mAutomaton( _automaton ), mSettings(_settings), mCurrentLevel(0), mIntersectedBadStates(false) {
		}

    template<typename Number, typename Representation>
	std::vector<flowpipe_t<Representation>> Reach<Number,Representation>::computeForwardReachability() {
		// set up working queue
		for ( const auto& state : mAutomaton.initialStates() ) {
			if(mCurrentLevel <= mSettings.jumpDepth){
				// Convert representation in state from matrix and vector to used representation type.
				State<Number> s = state.second;
				cPair<Number> set = boost::get<cPair<Number>>(state.second.set);
				s.set = Representation(set.first, set.second);
				assert(s.discreteAssignment.size() == state.second.discreteAssignment.size());
				mWorkingQueue.emplace(initialSet<Number,Representation>(mCurrentLevel, s));
			}
		}

		while ( !mWorkingQueue.empty() ) {
			initialSet<Number,Representation> nextInitialSet = mWorkingQueue.front();
			mWorkingQueue.pop();

			mCurrentLevel = boost::get<0>(nextInitialSet);
			assert(mCurrentLevel <= mSettings.jumpDepth);
			flowpipe_t<Representation> newFlowpipe = computeForwardTimeClosure(boost::get<1>(nextInitialSet));

			// TODO: Check for fixed point.
			if(mReachableStates.find(boost::get<1>(nextInitialSet).location) == mReachableStates.end())
				mReachableStates[boost::get<1>(nextInitialSet).location] = std::vector<flowpipe_t<Representation>>();

			mReachableStates[boost::get<1>(nextInitialSet).location].push_back(newFlowpipe);
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
	flowpipe_t<Representation> Reach<Number,Representation>::computeForwardTimeClosure( const hypro::State<Number>& _state ) {
#ifdef REACH_DEBUG
		std::cout << "Time Interval: " << mSettings.timeStep << std::endl;
		std::cout << "Initial valuation: " << std::endl;
		boost::get<Representation>(_state.set).print();
#endif
		// new empty Flowpipe
		flowpipe_t<Representation> flowpipe;
		boost::tuple<bool, State<Number>, matrix_t<Number>, vector_t<Number>> initialSetup = computeFirstSegment(_state);
#ifdef REACH_DEBUG
		std::cout << "Valuation fulfills Invariant?: ";
		std::cout << boost::get<0>(initialSetup) << std::endl;
#endif
		if ( boost::get<0>(initialSetup) ) {
			std::vector<boost::tuple<Transition<Number>*, State<Number>>> nextInitialSets;
			// insert first Segment into the empty flowpipe
			Representation currentSegment = boost::get<Representation>(boost::get<1>(initialSetup).set);
			flowpipe.push_back( currentSegment );
			// Check for bad states intersection. The first segment is validated against the invariant, already.
			if(intersectBadStates(_state, currentSegment)){
				// clear queue to stop whole algorithm
				while(!mWorkingQueue.empty()){
					mWorkingQueue.pop();
				}
				return flowpipe;
			}

			// Set after linear transformation
			Representation nextSegment;

#ifdef REACH_DEBUG
			std::cout << "--- Loop entered ---" << std::endl;
#endif
			// for each time interval perform linear Transformation
			// the first segment covers one time step.
			Number currentTime = mSettings.timeStep;
			// intersection of bad states and violation of invariant is handled inside the loop
			while( currentTime <= mSettings.timeBound ) {
				std::cout << "\rTime: \t" << carl::toDouble(currentTime) << std::flush;

				// perform linear transformation on the last segment of the flowpipe
				assert(currentSegment.linearTransformation(boost::get<2>(initialSetup), boost::get<3>(initialSetup)).size() == currentSegment.size());
				nextSegment = currentSegment.linearTransformation( boost::get<2>(initialSetup), boost::get<3>(initialSetup) );

				// extend flowpipe (only if still within Invariant of location)
				std::pair<bool, Representation> newSegment = nextSegment.satisfiesHalfspaces( _state.location->invariant().mat, _state.location->invariant().vec );
#ifdef REACH_DEBUG
				std::cout << "Next Flowpipe Segment: ";
				nextSegment.print();
				std::cout << "still within Invariant?: ";
				std::cout << newSegment.first << std::endl;
#endif
#ifdef USE_REDUCTION
				// clustering CONVEXHULL_CONST and reduction with directions generated before
				unsigned CONVEXHULL_CONST = 20, REDUCE_CONST=8;
				std::vector<vector_t<Number>> directions = computeTemplate<Number>(2, REDUCE_CONST);

				bool use_reduce_memory=false, use_reduce_time=true;
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
					if(intersectBadStates(_state, newSegment.second)){
						// clear queue to stop whole algorithm
						while(!mWorkingQueue.empty()){
							mWorkingQueue.pop();
						}
						return flowpipe;
					}
					// Collect potential new initial states from discrete behaviour.
					if(mCurrentLevel < mSettings.jumpDepth) {
						State<Number> guardSatisfyingState;
						State<Number> currentState = _state;
						currentState.set = newSegment.second;
						bool fireTimeTriggeredTransition = false;
						for( auto transition : _state.location->transitions() ){
							// handle time-triggered transitions
							if(transition->isTimeTriggered()){
								if(currentTime-mSettings.timeStep <= transition->triggerTime() && transition->triggerTime() <= currentTime){
									if(intersectGuard(transition, currentState, guardSatisfyingState)){
										nextInitialSets.emplace_back(transition, guardSatisfyingState);
										fireTimeTriggeredTransition = true;
									}
								}
							} // handle normal transitions
							else if(intersectGuard(transition, currentState, guardSatisfyingState)){
								nextInitialSets.emplace_back(transition, guardSatisfyingState);
							}
						}
						if(fireTimeTriggeredTransition){
							// quit loop after firing time triggered transition -> time triggered transitions are handled as urgent.
							#ifdef REACH_DEBUG
							std::cout << "Fired time triggered transition." << std::endl;
							#endif
							break;
						}
					}
					// update currentSegment
					currentSegment = newSegment.second;
				} else {
					// the flowpipe does not longer satisfy the invariant -> quit loop
					break;
				}
				currentTime += mSettings.timeStep;
			}
#ifdef REACH_DEBUG
			std::cout << "--- Loop left ---" << std::endl;
			std::cout << "flowpipe: " << flowpipe.size() << " Segments computed." << std::endl;
#endif
			// The loop terminated correctly (i.e. no bad states were hit), process discrete behavior.
			processDiscreteBehaviour(nextInitialSets);

			return flowpipe;
		} else {
			// return an empty flowpipe
			return flowpipe;
		}
	}

	template<typename Number, typename Representation>
	void Reach<Number,Representation>::processDiscreteBehaviour( const std::vector<boost::tuple<Transition<Number>*, State<Number>>>& _newInitialSets ) {
		std::map<Transition<Number>*, std::vector<State<Number>>> toAggregate;
		VariablePool& vpool = VariablePool::getInstance();

		for(const auto& tuple : _newInitialSets ) {
			if(boost::get<0>(tuple)->aggregation() == Aggregation::none){
				State<Number> s = boost::get<1>(tuple);
				s.location = boost::get<0>(tuple)->target();
				// handle discrete reset assignment
				typename Transition<Number>::Reset reset = boost::get<0>(tuple)->reset();
				assert(reset.discreteMat.rows() == s.discreteAssignment.size());
				for(unsigned rowIndex = 0; rowIndex < reset.discreteMat.rows(); ++rowIndex) {
					carl::Interval<Number> newAssignment(0);
					for(unsigned colIndex = 0; colIndex < reset.discreteMat.cols(); ++colIndex) {
						newAssignment += reset.discreteMat(rowIndex,colIndex) * boost::get<1>(tuple).discreteAssignment.at(vpool.carlVarByIndex(colIndex+reset.discreteOffset));
					}
					newAssignment += carl::Interval<Number>(reset.discreteVec(rowIndex));
					s.discreteAssignment[vpool.carlVarByIndex(rowIndex+reset.discreteOffset)] = newAssignment;
				}

				mWorkingQueue.emplace(mCurrentLevel+1, s);
			} else { // aggregate all
				// TODO: Note that all sets are collected for one transition, i.e. currently, if we intersect the guard for one transition twice with
				// some sets in between not satisfying the guard, we still collect all guard satisfying sets for that transition.
				if(toAggregate.find(boost::get<0>(tuple)) == toAggregate.end()){
					toAggregate[boost::get<0>(tuple)] = std::vector<State<Number>>();
				}
				toAggregate[boost::get<0>(tuple)].push_back(boost::get<1>(tuple));
			}
		}

		// aggregation - TODO: add options for clustering.
		for(const auto& aggregationPair : toAggregate){
			assert(!aggregationPair.second.empty());
			// TODO: Currently aggregation is done by collecting vertices - future: use multi-unite.
			// collect vertices.
			std::vector<Point<Number>> collectedVertices;
			for(const auto& state : aggregationPair.second){
				std::vector<Point<Number>> tmpVertices = boost::get<Representation>(state.set).vertices();
				collectedVertices.insert(collectedVertices.end(), tmpVertices.begin(), tmpVertices.end());
			}
			State<Number> s;
			s.location = aggregationPair.first->target();
			s.set = Representation(collectedVertices);
			// handle discrete reset assignment
			// ASSUMPTION: All discrete assignments are the same for this transition.
			typename Transition<Number>::Reset reset = aggregationPair.first->reset();
			std::cout << "Discrete assignment size: " << aggregationPair.second.begin()->discreteAssignment.size() << " and reset matrix " << reset.discreteMat << std::endl;
			assert(reset.discreteMat.rows() == aggregationPair.second.begin()->discreteAssignment.size());
			for(unsigned rowIndex = 0; rowIndex < reset.discreteMat.rows(); ++rowIndex) {
				carl::Interval<Number> newAssignment(0);
				for(unsigned colIndex = 0; colIndex < reset.discreteMat.cols(); ++colIndex) {
					// ATTENTION: Here the assumption takes place that every state for that transition has the same discrete assignment.
					newAssignment += reset.discreteMat(rowIndex,colIndex) * aggregationPair.second.begin()->discreteAssignment.at(vpool.carlVarByIndex(colIndex+reset.discreteOffset));
				}
				newAssignment += carl::Interval<Number>(reset.discreteVec(rowIndex));
				s.discreteAssignment[vpool.carlVarByIndex(rowIndex+reset.discreteOffset)] = newAssignment;
			}
			std::cout << "Discrete assignment size: " << s.discreteAssignment.size() << " and reset matrix " << reset.discreteMat << std::endl;
			assert(reset.discreteMat.rows() == s.discreteAssignment.size());
			mWorkingQueue.emplace(mCurrentLevel+1, s);
		}
	}

	template<typename Number, typename Representation>
	bool Reach<Number,Representation>::intersectGuard( hypro::Transition<Number>* _trans, const State<Number>& _state,
							   State<Number>& result ) {
		result = _state;
		// check discrete guard intersection.
		unsigned dOffset = _trans->guard().discreteOffset;
		for(const auto& guardPair : _trans->guard().discreteGuard){
			carl::Interval<Number> guardInterval(0);
			// insert all current discrete assignments except the constrained one.
			for(unsigned colIndex = 0; colIndex < guardPair.second.cols(); ++colIndex){
				if(colIndex != VariablePool::getInstance().id(guardPair.first)-dOffset) {
					if(_state.discreteAssignment.find(VariablePool::getInstance().carlVarByIndex(colIndex+dOffset)) == _state.discreteAssignment.end() ){
						guardInterval += guardPair.second(0, colIndex) * carl::Interval<Number>::unboundedInterval();
					} else {
						guardInterval += guardPair.second(0, colIndex) * _state.discreteAssignment.at(VariablePool::getInstance().carlVarByIndex(colIndex+dOffset));
					}
				}
			}
			if(_state.discreteAssignment.find(guardPair.first) != _state.discreteAssignment.end()) {
				result.discreteAssignment[guardPair.first] = _state.discreteAssignment.at(guardPair.first).intersect(guardInterval);
			} else {
				// set discrete assignment to match invariant.
				result.discreteAssignment[guardPair.first] = guardInterval;
			}
			if(result.discreteAssignment[guardPair.first].isEmpty()){
				#ifdef REACH_DEBUG
				std::cout << "Valuation violates discrete guard." << std::endl;
				#endif
				return false;
			}
		}

		// check for continuous set guard intersection
		std::pair<bool, Representation> guardSatisfyingSet = boost::get<Representation>(_state.set).satisfiesHalfspaces( _trans->guard().mat, _trans->guard().vec );
		// check if the intersection is empty
		if ( guardSatisfyingSet.first ) {
			#ifdef REACH_DEBUG
			std::cout << "Transition enabled!" << std::endl;
			#endif
			// apply reset function to guard-satisfying set.
			result.set = guardSatisfyingSet.second.linearTransformation( _trans->reset().mat, _trans->reset().vec );
			return true;
		} else {
			return false;
		}
	}

	template<typename Number, typename Representation>
	matrix_t<Number> Reach<Number,Representation>::computeTrafoMatrix( hypro::Location<Number>* _loc ) const {
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
		return resultMatrix;
	}

	template<typename Number, typename Representation>
	boost::tuple<bool, State<Number>, matrix_t<Number>, vector_t<Number>> Reach<Number,Representation>::computeFirstSegment( const State<Number>& _state ) const {
#ifdef REACH_DEBUG
		std::cout << "Time Interval: " << mSettings.timeStep << std::endl;
		std::cout << "Initial valuation: " << std::endl;
		boost::get<Representation>(_state.set).print();
#endif
		// check if initial Valuation fulfills Invariant
		// check discrete invariant first
		State<Number> validState = _state;
		const typename Location<Number>::Invariant& i = _state.location->invariant();
		for(const auto& invariantPair : i.discreteInvariant) {
			carl::Interval<Number> invariantInterval(0);
			std::cout << "Invariant row: " << invariantPair.second << std::endl;
			// insert all current discrete assignments except the constrained one.
			std::cout << "insert all except col " << VariablePool::getInstance().id(invariantPair.first)-i.discreteOffset << std::endl;
			for(unsigned colIndex = 0; colIndex < invariantPair.second.cols()-1; ++colIndex){
				if(colIndex != VariablePool::getInstance().id(invariantPair.first)-i.discreteOffset) {
					if(invariantPair.second(0, colIndex) != 0){
						std::cout << "search for variable in dimension " << colIndex+i.discreteOffset << std::endl;
						if(validState.discreteAssignment.find(VariablePool::getInstance().carlVarByIndex(colIndex+i.discreteOffset)) == validState.discreteAssignment.end() ){
							validState.discreteAssignment[VariablePool::getInstance().carlVarByIndex(colIndex+i.discreteOffset)] = carl::Interval<Number>::unboundedInterval();
							std::cout << "Not found." << std::endl;
						}
						invariantInterval += invariantPair.second(0, colIndex) * validState.discreteAssignment.at(VariablePool::getInstance().carlVarByIndex(colIndex+i.discreteOffset));
						std::cout << "Invariant Interval: " << invariantInterval << std::endl;
					}
				}
			}
			// add constant term
			carl::Interval<Number> constPart = carl::Interval<Number>::unboundedInterval();
			std::cout << "Const part in col " << invariantPair.second.cols()-1 << std::endl;
			if(invariantPair.second(0,VariablePool::getInstance().id(invariantPair.first)-i.discreteOffset) > 0){
				assert(invariantPair.second(0,VariablePool::getInstance().id(invariantPair.first)-i.discreteOffset) == 1);
				constPart = carl::Interval<Number>(-invariantPair.second(0,invariantPair.second.cols()-1));

			} else {
				assert(invariantPair.second(0,VariablePool::getInstance().id(invariantPair.first)-i.discreteOffset) == -1);
				constPart = carl::Interval<Number>(invariantPair.second(0,invariantPair.second.cols()-1));
			}
			std::cout << "const part interval: " << constPart << std::endl;
			invariantInterval += constPart;

			std::cout << "Invariant Interval: " << invariantInterval << std::endl;
			std::cout << "Current assignment: " << validState.discreteAssignment[invariantPair.first] << std::endl;
			std::cout << "Intersected: " << validState.discreteAssignment[invariantPair.first].intersect(invariantInterval) << std::endl;
			if(validState.discreteAssignment.find(invariantPair.first) != validState.discreteAssignment.end()) {
				validState.discreteAssignment[invariantPair.first] = validState.discreteAssignment[invariantPair.first].intersect(invariantInterval);
			} else {
				// set discrete assignment to match invariant.
				validState.discreteAssignment[invariantPair.first] = invariantInterval;
			}
			if(validState.discreteAssignment[invariantPair.first].isEmpty()){
				#ifdef REACH_DEBUG
				std::cout << "Valuation violates discrete invariant." << std::endl;
				#endif
				return boost::tuple<bool, State<Number>, matrix_t<Number>, vector_t<Number>>(false);
			}
		}

		// check continuous set for invariant
		std::pair<bool, Representation> initialPair = boost::get<Representation>(_state.set).satisfiesHalfspaces(_state.location->invariant().mat, _state.location->invariant().vec);
#ifdef REACH_DEBUG
		std::cout << "Valuation fulfills Invariant?: ";
		std::cout << initialPair.first << std::endl;
#endif
		if ( initialPair.first ) {
			// approximate R_[0,delta](X0)
			// R_0(X0) is just the initial Polytope X0, since t=0 -> At is zero matrix -> e^(At) is unit matrix.
			matrix_t<Number> trafoMatrix = computeTrafoMatrix(_state.location);

#ifdef REACH_DEBUG
			std::cout << "e^(deltaMatrix): " << std::endl;
			std::cout << trafoMatrix << std::endl;
			std::cout << "------" << std::endl;
#endif

			// e^(At)*X0 = polytope at t=delta
			unsigned rows = trafoMatrix.rows();
			unsigned cols = trafoMatrix.cols();
			vector_t<Number> translation = trafoMatrix.col( cols - 1 );
			translation.conservativeResize( rows - 1 );
			trafoMatrix.conservativeResize( rows - 1, cols - 1 );
			Representation deltaValuation = initialPair.second.linearTransformation( trafoMatrix, translation );

#ifdef REACH_DEBUG
			std::cout << "Polytope at t=delta: ";
			deltaValuation.print();
#endif

			// R_0(X0) U R_delta(X0)
			Representation unitePolytope = initialPair.second.unite( deltaValuation );
			//assert(unitePolytope.contains(initialPair.second));
			//assert(unitePolytope.contains(deltaValuation));

#ifdef REACH_DEBUG
			std::cout << "Polytope after unite with R0: ";
			unitePolytope.print();
#endif
			// bloat hullPolytope (Hausdorff distance)
			Number radius = hausdorffError( Number( mSettings.timeStep ), _state.location->flow(), initialPair.second.supremum() );
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
			Representation firstSegment = unitePolytope.minkowskiSum( hausPoly );

			//plotter.plot2d();
			//assert(firstSegment.contains(unitePolytope));
			//assert(firstSegment.contains(initialPair.second));
			//assert(firstSegment.contains(deltaValuation));

#ifdef REACH_DEBUG
			std::cout << "first Flowpipe Segment (after minkowski Sum): ";
			firstSegment.print();
#endif

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

				//for(auto transition: _state.location->transitions()){	// reduction memory guard mode
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

			// set the last segment of the flowpipe. Note that intersection with the invariants cannot result in an empty set due to previous checks.
			Representation fullSegment = firstSegment.intersectHalfspaces( _state.location->invariant().mat, _state.location->invariant().vec );
			assert(firstSegment.satisfiesHalfspaces(_state.location->invariant().mat, _state.location->invariant().vec).first);
			validState.set = fullSegment;
			return boost::tuple<bool, State<Number>, matrix_t<Number>, vector_t<Number>>(initialPair.first, validState, trafoMatrix, translation);
		} // if satisfies invariant
		else {
			return boost::tuple<bool, State<Number>, matrix_t<Number>, vector_t<Number>>(false);
		}
	}

	template<typename Number, typename Representation>
	bool Reach<Number,Representation>::intersectBadStates( const State<Number>& _state, const Representation& _segment ) const {
		// check local bad states TODO: Note, we currently allow only one bad state per location -> allow multiple bad states!
		auto badStateIterator = mAutomaton.localBadStates().find(_state.location);
		if(badStateIterator != mAutomaton.localBadStates().end()){
			// check discrete variables first -> faster.
			for(const auto& assignmentPair : _state.discreteAssignment) {
				// check if there is a constraint on the variable
				if(badStateIterator->second.discreteAssignment.find(assignmentPair.first) != badStateIterator->second.discreteAssignment.end() ){
					std::cout << "Discrete guard: " << assignmentPair.first << " in " << badStateIterator->second.discreteAssignment.at(assignmentPair.first) << " Current assignment: " << assignmentPair.second << std::endl;
					if(!badStateIterator->second.discreteAssignment.at(assignmentPair.first).intersectsWith(assignmentPair.second)){
						// If one intersection is empty, the whole set does not intersect -> return false.
						return false;
					}
				}
				// if there is no constraint on the variable, the bad state is always satisfied for that dimension.
			}
			#ifdef REACH_DEBUG
			std::cout << "Intersection with local, discrete bad states" << std::endl;
			#endif
			// at this point all discrete bad states were already satisfied -> check continuous bad states.
			if(_segment.satisfiesHalfspaces(boost::get<cPair<Number>>(badStateIterator->second.set).first, boost::get<cPair<Number>>(badStateIterator->second.set).second).first == true){
				#ifdef REACH_DEBUG
				std::cout << "Intersection with all local bad states" << std::endl;
				#endif
				mIntersectedBadStates = true;
				return true;
			}
			#ifdef REACH_DEBUG
			std::cout << "No intersection with local, continuous bad states" << std::endl;
			#endif
		}

		// check global bad states
		if(!mAutomaton.globalBadStates().empty()){
			for(const auto& set : mAutomaton.globalBadStates() ) {
				// bad state intersection
				if(_segment.satisfiesHalfspaces(set.first, set.second).first){
					#ifdef REACH_DEBUG
					std::cout << "Intersection with global bad states" << std::endl;
					#endif
					mIntersectedBadStates = true;
					return true;
				}
			}
		}
		return false;
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
