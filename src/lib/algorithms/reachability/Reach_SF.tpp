#include "Reach_SF.h"
#include "Settings.h"
#include <chrono>

namespace hypro {
	namespace reachability {

		using clock = std::chrono::high_resolution_clock;
		using timeunit = std::chrono::microseconds;

		template<typename Number>
		Reach<Number,SupportFunction<Number>>::Reach( const HybridAutomaton<Number>& _automaton, const ReachabilitySettings<Number>& _settings)
				: mAutomaton( _automaton ), mSettings(_settings), mCurrentLevel(0), mIntersectedBadStates(false) {
		}

		/*
		 *  TO-DO:
		 *      - Substitute state by node
		 */

		template<typename Number>
		std::vector<std::pair<unsigned, flowpipe_t<SupportFunction<Number>>>> Reach<Number,SupportFunction<Number>>::computeForwardReachability() {
			// set up working queue -> add initial states
			/*
			 *  TO-DO:
			 *     - initialize NodeManager
			 *     - Assign first 'real level' of the reachability tree with the initial states
			 *       (including information about the location, current time step, first segment (probably later) and
			 *       the used representation)
			 */
			// collect all computed reachable states
			std::vector<std::pair<unsigned, flowpipe_t<SupportFunction<Number>>>> collectedReachableStates;

			for ( const auto& state : mAutomaton.initialStates() ) {
				if(mCurrentLevel <= mSettings.jumpDepth){
					// Convert representation in state from matrix and vector to used representation type.
					State<Number> s;
					s.location = state.second.location;
					s.discreteAssignment = state.second.discreteAssignment;
					s.set = SupportFunction<Number>(state.second.set.first, state.second.set.second);
					s.timestamp = carl::Interval<Number>(0);
					assert(s.discreteAssignment.size() == state.second.discreteAssignment.size());
					mWorkingQueue.emplace(initialSet<Number>(mCurrentLevel, s));
				}
			}

			while ( !mWorkingQueue.empty() ) {
				initialSet<Number> nextInitialSet = mWorkingQueue.front();
				mWorkingQueue.pop();

				mCurrentLevel = boost::get<0>(nextInitialSet);
				assert(mCurrentLevel <= mSettings.jumpDepth);
				std::cout << "Depth " << mCurrentLevel << ", Location: " << boost::get<1>(nextInitialSet).location->id() << std::endl;
				flowpipe_t<SupportFunction<Number>> newFlowpipe = computeForwardTimeClosure(boost::get<1>(nextInitialSet));

				/*
							 *  TO-DO:
							 *      - Check for fixed-points here using the overapproximations stored in the tree
							 */
				collectedReachableStates.emplace_back(std::make_pair(boost::get<1>(nextInitialSet).location->id(), newFlowpipe));
			}

			return collectedReachableStates;
		}

		/*
		 *  TO-DO:
		 *      - Modify the following method such that it does not return the explicit flowpipe
		 */

		template<typename Number>
		flowpipe_t<SupportFunction<Number>> Reach<Number,SupportFunction<Number>>::computeForwardTimeClosure( const hypro::State<Number>& _state ) {
			assert(!_state.timestamp.isUnbounded());
#ifdef REACH_DEBUG
			std::cout << "Location: " << _state.location->id() << std::endl;
		std::cout << "Location printed : " << *_state.location << std::endl;
 		std::cout << "Time step size: " << mSettings.timeStep << std::endl;
		std::cout << "Initial valuation: " << std::endl;
		boost::get<SupportFunction<Number>>(_state.set).print();
#endif
			// new empty Flowpipe
			flowpipe_t<SupportFunction<Number>> flowpipe;
			std::vector<boost::tuple<Transition<Number>*, State<Number>>> nextInitialSets;
			/*
			 *  TO-DO:
			 *     - Insert first segment into the current node
			 */

			// check for time triggered transitions once before any flowpipe is computed. TODO: put the check for transitions in the loop to the end?
			if(mCurrentLevel <= mSettings.jumpDepth) {
				State<Number> guardSatisfyingState;
				bool locallyUrgent = false;
				for( auto transition : _state.location->transitions() ){
					// handle time-triggered transitions
					if(transition->isTimeTriggered()){
#ifdef REACH_DEBUG
						std::cout << "Checking timed transition " << transition->source()->id() << " -> " << transition->target()->id() << " for time interval [0," << mSettings.timeBound << "]" << std::endl;
#endif
						// Check for direct urgent transitions
						if(transition->triggerTime() == 0){
							//std::cout << "Time trigger enabled" << std::endl;
							if(intersectGuard(transition, _state, guardSatisfyingState)){
								// when taking a timed transition, reset timestamp
								if(mCurrentLevel != mSettings.jumpDepth) {
									guardSatisfyingState.timestamp = carl::Interval<Number>(0);
									nextInitialSets.push_back(boost::tuple<Transition<Number>*, State<Number>>(transition, guardSatisfyingState));
									flowpipe.push_back(boost::get<SupportFunction<Number>>(guardSatisfyingState.set));
								}
								locallyUrgent = true;
							}
						}
					}
				}
				if(locallyUrgent){
					processDiscreteBehaviour(nextInitialSets);
					return flowpipe;
				}
			}

			boost::tuple<bool, State<Number>, std::shared_ptr<const lintrafoParameters<Number>>> initialSetup = computeFirstSegment(_state);
#ifdef REACH_DEBUG
			std::cout << "Valuation fulfills Invariant?: ";
		std::cout << boost::get<0>(initialSetup) << std::endl;
#endif
			if ( boost::get<0>(initialSetup) ) {
				assert(!boost::get<1>(initialSetup).timestamp.isUnbounded());
				bool noFlow = false;

				// if the location does not have dynamic behaviour, check guards and exit loop.
				if(boost::get<2>(initialSetup)->matrix() == matrix_t<Number>::Identity(boost::get<2>(initialSetup)->matrix().rows(), boost::get<2>(initialSetup)->matrix().cols()) &&
				   boost::get<2>(initialSetup)->vector() == vector_t<Number>::Zero(boost::get<2>(initialSetup)->vector().rows())) {
					noFlow = true;
					// Collect potential new initial states from discrete behaviour.
					if(mCurrentLevel < mSettings.jumpDepth) {
						State<Number> guardSatisfyingState;
						for( auto transition : _state.location->transitions() ){
							// handle time-triggered transitions
							if(transition->isTimeTriggered()){
#ifdef REACH_DEBUG
								std::cout << "Checking timed transition " << transition->source()->id() << " -> " << transition->target()->id() << " for time interval [0," << mSettings.timeBound << "]" << std::endl;
#endif
								// As there is no continuous behaviour, simply check guard for whole time horizon
								if(transition->triggerTime() <= mSettings.timeBound){
									//std::cout << "Time trigger enabled" << std::endl;
									if(intersectGuard(transition, _state, guardSatisfyingState)){
										// when taking a timed transition, reset timestamp
										guardSatisfyingState.timestamp = carl::Interval<Number>(0);
										nextInitialSets.emplace_back(transition, guardSatisfyingState);
									}
								}
							} // handle normal transitions
							else if(intersectGuard(transition, _state, guardSatisfyingState)){
								//std::cout << "hybrid transition enabled" << std::endl;
								//std::cout << *transition << std::endl;
								assert(guardSatisfyingState.timestamp == _state.timestamp);
								// when a guard is satisfied here, as we do not have dynamic behaviour, avoid calculation of flowpipe
								assert(!guardSatisfyingState.timestamp.isUnbounded());
								nextInitialSets.emplace_back(transition, guardSatisfyingState);
							}
						}
					}
				}

				// insert first Segment into the empty flowpipe
				SupportFunction<Number> currentSegment;
				if(noFlow) {
					currentSegment = boost::get<SupportFunction<Number>>(_state.set);
				} else {
					currentSegment = boost::get<SupportFunction<Number>>(boost::get<1>(initialSetup).set);
				}
				flowpipe.push_back( currentSegment );

				std::cout << "Current Set: " << std::endl << Converter<Number>::toHPolytope(currentSegment) << std::endl;

				// Check for bad states intersection. The first segment is validated against the invariant, already.
				if(intersectBadStates(_state, currentSegment)){
					// clear queue to stop whole algorithm
					while(!mWorkingQueue.empty()){
						mWorkingQueue.pop();
					}
					/*
					 * TO-DO.
					 *    - Employ backtracking here
					 */
					return flowpipe;
				}

				// Set after linear transformation
				SupportFunction<Number> nextSegment;
                                bool transitionSatisfied = false;
                                bool alreadyReduced = false;
#ifdef USE_SYSTEM_SEPARATION
				SupportFunction<Number> autonomPart = currentSegment;
    #ifdef USE_ELLIPSOIDS
                        // Easy to addapt to any SupportFunction<Number> use ellipsoid for the idea of my masterthesis here
                        Ellipsoid<Number> nonautonomPart(mBloatingFactor, currentSegment.dimension());
                        Ellipsoid<Number> totalBloating = nonautonomPart;
    #else
                        Ellipsoid<Number> nonautonomPartAsEllispsoid(mBloatingFactor, currentSegment.dimension());
                        SupportFunction<Number> nonautonomPart = SupportFunction<Number>(nonautonomPartAsEllispsoid);
                        SupportFunction<Number> totalBloating = nonautonomPart;
    #endif
#endif
#ifdef REACH_DEBUG
				if(!noFlow){
				std::cout << "--- Loop entered ---" << std::endl;
			}
#endif

				// the first segment covers one time step already
				Number currentLocalTime = mSettings.timeStep;
				// intersection of bad states and violation of invariant is handled inside the loop
				/*
				 *  TO-DO:
				 *    - Insert for each transition the guard satisfying intervals
				 */
				while( !noFlow && currentLocalTime <= mSettings.timeBound ) {
                                        transitionSatisfied = false;
					std::cout << "\rTime: \t" << std::setprecision(4) << std::setw(8) << fixed << carl::toDouble(currentLocalTime) << std::flush << std::endl;
					// Verify transitions on the current set.
					if(mCurrentLevel <= mSettings.jumpDepth) {
						State<Number> guardSatisfyingState;
						State<Number> currentState = _state;
						currentState.set = currentSegment;
						currentState.timestamp += carl::Interval<Number>(currentLocalTime-mSettings.timeStep,currentLocalTime);
						currentState.timestamp = currentState.timestamp.intersect(carl::Interval<Number>(0, mSettings.timeBound));
						bool fireTimeTriggeredTransition = false;
						for( auto transition : _state.location->transitions() ){
							// handle time-triggered transitions
							if(transition->isTimeTriggered()){
#ifdef REACH_DEBUG
								std::cout << "Checking timed transition " << transition->source()->id() << " -> " << transition->target()->id() << " for time interval " << currentState.timestamp << std::endl;
#endif
								if(currentState.timestamp.contains(transition->triggerTime())){
									std::cout << "Time trigger enabled" << std::endl;
									if(intersectGuard(transition, currentState, guardSatisfyingState)){
										// only insert new Sets into working queue, when the current level allows it.
											transitionSatisfied = true;
											if(!alreadyReduced) {
#ifdef USE_SYSTEM_SEPARATION
												autonomPart.forceLinTransReduction();
#endif
												currentSegment.forceLinTransReduction();
												currentState.set = currentSegment;
												intersectGuard(transition, currentState, guardSatisfyingState);
												alreadyReduced = true;
											}
											if(mCurrentLevel != mSettings.jumpDepth){
											// when taking a timed transition, reset timestamp
											guardSatisfyingState.timestamp = carl::Interval<Number>(0);
											nextInitialSets.emplace_back(transition, guardSatisfyingState);
										}
										fireTimeTriggeredTransition = true;
									}
								}
							} // handle normal transitions
							else if(intersectGuard(transition, currentState, guardSatisfyingState) && mCurrentLevel < mSettings.jumpDepth){
								transitionSatisfied = true;
								if(!alreadyReduced) {
#ifdef USE_SYSTEM_SEPARATION
									autonomPart.forceLinTransReduction();
#endif
									currentSegment.forceLinTransReduction();
									currentState.set = currentSegment;
									intersectGuard(transition, currentState, guardSatisfyingState);
									alreadyReduced = true;
								}
								assert(guardSatisfyingState.timestamp == currentState.timestamp);
								//std::cout << "hybrid transition enabled" << std::endl;
								//std::cout << *transition << std::endl;
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

					if (!transitionSatisfied) {
						alreadyReduced = false;
					}
					// perform linear transformation on the last segment of the flowpipe
					//assert(currentSegment.linearTransformation(boost::get<2>(initialSetup)).size() == currentSegment.size());
#ifdef USE_SYSTEM_SEPARATION
					autonomPart = autonomPart.linearTransformation( boost::get<2>(initialSetup), boost::get<3>(initialSetup) );
    #ifdef USE_ELLIPSOIDS
					if (mBloatingFactor != 0){
						SupportFunction<Number> temp = SupportFunction<Number>(totalBloating);
						nextSegment = autonomPart.minkowskiSum(temp);
					} else {
						nextSegment = autonomPart;
					}
#else
					if (mBloatingFactor != 0){
						nextSegment = autonomPart.minkowskiSum(totalBloating);
					} else {
						nextSegment = autonomPart;
					}
#endif
					//nonautonomPart = nonautonomPart.linearTransformation( boost::get<2>(initialSetup), vector_t<Number>::Zero(autonomPart.dimension()));
					totalBloating = totalBloating.minkowskiSum(nonautonomPart);
#else
					nextSegment = currentSegment.linearTransformation( boost::get<2>(initialSetup) );
#endif
					//nextSegment.forceLinTransReduction();
					//std::cout << "Current depth " << nextSegment.depth() << std::endl;
					//std::cout << "Current OpCount " << nextSegment.operationCount() << std::endl;
					// extend flowpipe (only if still within Invariant of location)
					std::pair<bool, SupportFunction<Number>> newSegment = nextSegment.satisfiesHalfspaces( _state.location->invariant().mat, _state.location->invariant().vec );
#ifdef REACH_DEBUG
					std::cout << "Next Flowpipe Segment: ";
				std::cout << nextSegment << std::endl;
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
							SupportFunction<Number> poly_smoothed = newSegment.reduce_directed(directions, HPolytope<Number>::REDUCTION_STRATEGY::DIRECTED_TEMPLATE);
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
							SupportFunction<Number> convexHull = SupportFunction<Number>(Halfspaces);

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

						//unsigned tmp = plotter.addObject(newSegment.second.vertices());
						//plotter.setObjectColor(tmp, hypro::colors[_state.location->id()]);

						if(intersectBadStates(_state, newSegment.second)){
							// clear queue to stop whole algorithm
							while(!mWorkingQueue.empty()){
								mWorkingQueue.pop();
							}
							return flowpipe;
						}
						// update currentSegment
						currentSegment = newSegment.second;

						std::cout << "Current Set: " << std::endl << Converter<Number>::toHPolytope(currentSegment) << std::endl;

					} else {
						// the flowpipe does not longer satisfy the invariant -> quit loop
						break;
					}
					currentLocalTime += mSettings.timeStep;
				}
				std::cout << std::endl;
#ifdef REACH_DEBUG
				if(!noFlow){
					std::cout << "--- Loop left ---" << std::endl;
				}
				std::cout << "flowpipe: " << flowpipe.size() << " Segments computed." << std::endl;
				std::cout << "Process " << nextInitialSets.size() << " new initial sets." << std::endl;
#endif
				// The loop terminated correctly (i.e. no bad states were hit), process discrete behavior.
				processDiscreteBehaviour(nextInitialSets);
				return flowpipe;
			} else {
				// return an empty flowpipe
				return flowpipe;
			}
		}

		template<typename Number>
		void Reach<Number,SupportFunction<Number>>::processDiscreteBehaviour( const std::vector<boost::tuple<Transition<Number>*, State<Number>>>& _newInitialSets ) {
			std::map<Transition<Number>*, std::vector<State<Number>>> toAggregate;
			VariablePool& vpool = VariablePool::getInstance();

			for(const auto& tuple : _newInitialSets ) {
				if(boost::get<0>(tuple)->aggregation() == Aggregation::none){
					// copy state - as there is no aggregation, the containing set and timestamp is already valid
					State<Number> s = boost::get<1>(tuple);
					assert(!s.timestamp.isUnbounded());
					s.location = boost::get<0>(tuple)->target();

					//std::cout << "Enqueue " << s << " for level " << mCurrentLevel+1 << std::endl;
					/*
					 *  TO-DO:
					 *       - Check whether for the current node and transition already a child-node
					 *         exists. If so, work on it. Otherwise, create a new child-node.
					 *          If the last segment for some transition arrives:
					 *              - Construct overapproximation
					 *              - Set last segment
					 *
					 */
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
				carl::Interval<Number> aggregatedTimestamp;
				//std::cout << "Aggregated timestamp before aggregation " << aggregatedTimestamp << std::endl;
				SupportFunction<Number> collectedSets = boost::get<SupportFunction<Number>>(aggregationPair.second.begin()->set);
				for(auto stateIt = ++aggregationPair.second.begin(); stateIt != aggregationPair.second.end(); ++stateIt){
					assert(!stateIt->timestamp.isUnbounded());
					aggregatedTimestamp = aggregatedTimestamp.convexHull(stateIt->timestamp);
					SupportFunction<Number> tmp = boost::get<SupportFunction<Number>>(stateIt->set);

					std::cout << "United hpoly: " << Converter<Number>::toHPolytope(tmp) << std::endl;

					collectedSets = collectedSets.unite(tmp);
				}

				State<Number> s;
				s.location = aggregationPair.first->target();
				//s.set = SupportFunction<Number>(collectedVertices);

				Number temp =mSettings.timeBound/mSettings.timeStep;
				unsigned long estimatedNumberOfEvaluations =  (aggregationPair.first->guard().mat.rows() + aggregationPair.first->target()->invariant().mat.rows()) * carl::toInt<carl::uint>(carl::ceil(temp));
				unsigned long estimatedCostWithoutReduction = estimatedNumberOfEvaluations * collectedSets.multiplicationsPerEvaluation();
				unsigned long hyperplanesForReduction = 4* collectedSets.dimension() * (collectedSets.dimension()-1);
				unsigned long estimatedCostWithReduction = hyperplanesForReduction + estimatedNumberOfEvaluations * carl::pow(hyperplanesForReduction, 2);
				//if (estimatedCostWithReduction < estimatedCostWithoutReduction) {
				if(true){
					std::cout << "conversion to hpoly." << std::endl;
					auto tmpHPoly = Converter<Number>::toHPolytope(collectedSets);
					std::cout << "conversion to hpoly done." << std::endl;
					SupportFunction<Number> newSet(tmpHPoly.matrix(), tmpHPoly.vector());
					s.set = newSet;
				} else {
					s.set = collectedSets;
				}
				s.timestamp = aggregatedTimestamp;
				//std::cout << "Aggregate " << aggregationPair.second.size() << " sets." << std::endl;

				//std::cout << "Aggregated representation: " << boost::get<SupportFunction<Number>>(s.set) << std::endl;

				// ASSUMPTION: All discrete assignments are the same for this transition.
				typename Transition<Number>::Reset reset = aggregationPair.first->reset();
				//std::cout << "Discrete assignment size: " << aggregationPair.second.begin()->discreteAssignment.size() << " and reset matrix " << reset.discreteMat << std::endl;
				assert(unsigned(reset.discreteMat.rows()) == aggregationPair.second.begin()->discreteAssignment.size());
				for(unsigned rowIndex = 0; rowIndex < reset.discreteMat.rows(); ++rowIndex) {
					carl::Interval<Number> newAssignment(0);
					for(unsigned colIndex = 0; colIndex < reset.discreteMat.cols(); ++colIndex) {
						// ATTENTION: Here the assumption takes place that every state for that transition has the same discrete assignment.
						newAssignment += reset.discreteMat(rowIndex,colIndex) * aggregationPair.second.begin()->discreteAssignment.at(vpool.carlVarByIndex(colIndex+reset.discreteOffset));
					}
					newAssignment += carl::Interval<Number>(reset.discreteVec(rowIndex));
					//std::cout << "Discrete Assignment: " << vpool.carlVarByIndex(rowIndex+reset.discreteOffset) << " set to " << newAssignment << std::endl;
					s.discreteAssignment[vpool.carlVarByIndex(rowIndex+reset.discreteOffset)] = newAssignment;
				}
				//std::cout << "Discrete assignment size: " << s.discreteAssignment.size() << " and reset matrix " << reset.discreteMat << std::endl;
				assert(unsigned(reset.discreteMat.rows()) == s.discreteAssignment.size());
				//std::cout << "Enqueue " << s << " for level " << mCurrentLevel+1 << std::endl;
				mWorkingQueue.emplace(mCurrentLevel+1, s);
			}
		}

		template<typename Number>
		bool Reach<Number,SupportFunction<Number>>::intersectGuard( hypro::Transition<Number>* _trans, const State<Number>& _state,
														   State<Number>& result ) {
			assert(!_state.timestamp.isUnbounded());
			result = _state;
			//std::cout << "check transition " << *_trans << std::endl;
			VariablePool& vpool = VariablePool::getInstance();

			// check discrete guard intersection.
			unsigned dOffset = _trans->guard().discreteOffset;
			for(const auto& guardPair : _trans->guard().discreteGuard){
				carl::Interval<Number> guardInterval = carl::Interval<Number>::unboundedInterval();
				carl::Interval<Number> substitution(0);
				//std::cout << "Guard row: " << guardPair.second << std::endl;
				// insert all current discrete assignments except the constrained one.
				for(unsigned colIndex = 0; colIndex < guardPair.second.cols()-1; ++colIndex){
					if(colIndex != VariablePool::getInstance().id(guardPair.first)-dOffset) {
						substitution += guardPair.second(0, colIndex) * _state.discreteAssignment.at(vpool.carlVarByIndex(colIndex+dOffset));
					}
				}
				carl::Interval<Number> constPart(guardPair.second(0,guardPair.second.cols()-1));
				substitution += constPart;
				//std::cout << "substitution interval " << substitution << std::endl;
				if(guardPair.second(0,vpool.id(guardPair.first)-dOffset) > 0){
					assert(guardPair.second(0,vpool.id(guardPair.first)-dOffset) == 1);
					guardInterval.setUpperBound(-substitution.lower(),carl::BoundType::WEAK);
					//std::cout << "After setting upper bound new: " << guardInterval << std::endl;
				} else {
					assert(guardPair.second(0,vpool.id(guardPair.first)-dOffset) == -1);
					guardInterval.setLowerBound(substitution.upper(), carl::BoundType::WEAK);
					//std::cout << "After setting lower bound new: " << guardInterval << std::endl;
				}

				//std::cout << "Guard Interval: " << guardInterval << std::endl;
				//std::cout << "Current assignment: " << _state.discreteAssignment.at(guardPair.first) << std::endl;
				//std::cout << "Intersected: " << _state.discreteAssignment.at(guardPair.first).intersect(guardInterval) << std::endl;

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

			// handle discrete reset assignment
			typename Transition<Number>::Reset reset = _trans->reset();
			assert(unsigned(reset.discreteMat.rows()) == result.discreteAssignment.size());
			std::map<carl::Variable, carl::Interval<Number>> guardSatisfyingDiscreteAssingment = result.discreteAssignment;
			for(unsigned rowIndex = 0; rowIndex < reset.discreteMat.rows(); ++rowIndex) {
				carl::Interval<Number> newAssignment(0);
				for(unsigned colIndex = 0; colIndex < reset.discreteMat.cols(); ++colIndex) {
					newAssignment += reset.discreteMat(rowIndex,colIndex) * guardSatisfyingDiscreteAssingment.at(vpool.carlVarByIndex(colIndex+reset.discreteOffset));
				}
				newAssignment += carl::Interval<Number>(reset.discreteVec(rowIndex));
				//std::cout << "Discrete Assignment: " << vpool.carlVarByIndex(rowIndex+reset.discreteOffset) << " set to " << newAssignment << std::endl;
				result.discreteAssignment[vpool.carlVarByIndex(rowIndex+reset.discreteOffset)] = newAssignment;
			}

			// At this point the discrete guard is satisfied and the result state contains all discrete assignments satisfying this guard -> verify against target location invariant.
			for(const auto& invariantPair : _trans->target()->invariant().discreteInvariant ) {
				carl::Interval<Number> invariant = carl::Interval<Number>::unboundedInterval();
				carl::Interval<Number> substitution(0);
				unsigned dOffset = _trans->target()->invariant().discreteOffset;
				//std::cout << "Guard row: " << guardPair.second << std::endl;
				// insert all current discrete assignments except the constrained one.
				for(unsigned colIndex = 0; colIndex < invariantPair.second.cols()-1; ++colIndex){
					if(colIndex != vpool.id(invariantPair.first)-dOffset) {
						substitution += invariantPair.second(0, colIndex) * result.discreteAssignment.at(vpool.carlVarByIndex(colIndex+dOffset));
					}
				}
				carl::Interval<Number> constPart(invariantPair.second(0,invariantPair.second.cols()-1));
				substitution += constPart;
				//std::cout << "substitution interval " << substitution << std::endl;
				if(invariantPair.second(0,vpool.id(invariantPair.first)-dOffset) > 0){
					assert(invariantPair.second(0,vpool.id(invariantPair.first)-dOffset) == 1);
					invariant.setUpperBound(-substitution.lower(),carl::BoundType::WEAK);
					//std::cout << "After setting upper bound new: " << invariant << std::endl;
				} else {
					assert(invariantPair.second(0,vpool.id(invariantPair.first)-dOffset) == -1);
					invariant.setLowerBound(substitution.upper(), carl::BoundType::WEAK);
					//std::cout << "After setting lower bound new: " << invariant << std::endl;
				}

				if(!invariant.intersectsWith(result.discreteAssignment.at(invariantPair.first))) {
#ifdef REACH_DEBUG
					std::cout << "Valuation invalidates discrete target location invariant." << std::endl;
#endif
					return false;
				}
			}

			// check for continuous set guard intersection
			std::pair<bool, SupportFunction<Number>> guardSatisfyingSet = boost::get<SupportFunction<Number>>(_state.set).satisfiesHalfspaces( _trans->guard().mat, _trans->guard().vec );
			// check if the intersection is empty
			if ( guardSatisfyingSet.first ) {
#ifdef REACH_DEBUG
				std::cout << "Transition enabled!" << std::endl;
#endif
				// apply reset function to guard-satisfying set.
				//std::cout << "Apply reset: " << _trans->reset().mat << " " << _trans->reset().vec << std::endl;
				std::shared_ptr<lintrafoParameters<Number>> parameters = std::make_shared<lintrafoParameters<Number>>(_trans->reset().mat, _trans->reset().vec);
				SupportFunction<Number> tmp = guardSatisfyingSet.second.linearTransformation( parameters );

				std::cout << "Set after reset function: " << std::endl << Converter<Number>::toHPolytope(tmp) << std::endl;

				std::pair<bool, SupportFunction<Number>> invariantSatisfyingSet = tmp.satisfiesHalfspaces(_trans->target()->invariant().mat, _trans->target()->invariant().vec);
				if(invariantSatisfyingSet.first){
					result.set = invariantSatisfyingSet.second;
					return true;
				}
#ifdef REACH_DEBUG
				std::cout << "Valuation invalidates continuous target location invariant." << std::endl;
#endif
				return false;
			} else {
#ifdef REACH_DEBUG
				std::cout << "Continuous guard invalidated." << std::endl;
#endif
				return false;
			}
		}

		template<typename Number>
		matrix_t<Number> Reach<Number,SupportFunction<Number>>::computeTrafoMatrix( hypro::Location<Number>* _loc ) const {
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

		template<typename Number>
		boost::tuple<bool, State<Number>, std::shared_ptr<const lintrafoParameters<Number>>> Reach<Number,SupportFunction<Number>>::computeFirstSegment( const State<Number>& _state ) const {
			assert(!_state.timestamp.isUnbounded());
			// check if initial Valuation fulfills Invariant
			// check discrete invariant first
			State<Number> validState = _state;
			const typename Location<Number>::Invariant& i = _state.location->invariant();
			for(const auto& invariantPair : i.discreteInvariant) {
				carl::Interval<Number> invariantInterval = carl::Interval<Number>::unboundedInterval();
				carl::Interval<Number> substitution(0);
				//std::cout << "Invariant row: " << invariantPair.second << std::endl;
				// insert all current discrete assignments except the constrained one.
				//std::cout << "insert all except col " << VariablePool::getInstance().id(invariantPair.first)-i.discreteOffset << std::endl;
				for(unsigned colIndex = 0; colIndex < invariantPair.second.cols()-1; ++colIndex){
					if(colIndex != VariablePool::getInstance().id(invariantPair.first)-i.discreteOffset) {
						if(invariantPair.second(0, colIndex) != 0){
							substitution += invariantPair.second(0, colIndex) * validState.discreteAssignment.at(VariablePool::getInstance().carlVarByIndex(colIndex+i.discreteOffset));
							//std::cout << "Invariant Interval: " << substitution << std::endl;
						}
					}
				}
				// add constant term
				carl::Interval<Number> constPart(invariantPair.second(0,invariantPair.second.cols()-1));
				substitution += constPart;
				//std::cout << "substitution interval " << substitution << std::endl;
				if(invariantPair.second(0,VariablePool::getInstance().id(invariantPair.first)-i.discreteOffset) > 0){
					assert(invariantPair.second(0,VariablePool::getInstance().id(invariantPair.first)-i.discreteOffset) == 1);
					invariantInterval.setUpperBound(-substitution.lower(),carl::BoundType::WEAK);
					//std::cout << "After setting upper bound new: " << invariantInterval << std::endl;
				} else {
					assert(invariantPair.second(0,VariablePool::getInstance().id(invariantPair.first)-i.discreteOffset) == -1);
					invariantInterval.setLowerBound(substitution.upper(), carl::BoundType::WEAK);
					//std::cout << "After setting lower bound new: " << invariantInterval << std::endl;
				}

				//std::cout << "Invariant Interval: " << invariantInterval << std::endl;
				//std::cout << "Current assignment: " << validState.discreteAssignment[invariantPair.first] << std::endl;
				//std::cout << "Intersected: " << validState.discreteAssignment[invariantPair.first].intersect(invariantInterval) << std::endl;
				if(validState.discreteAssignment.find(invariantPair.first) != validState.discreteAssignment.end()) {
					validState.discreteAssignment[invariantPair.first] = validState.discreteAssignment[invariantPair.first].intersect(invariantInterval);
				} else {
					// set discrete assignment to match invariant.
					validState.discreteAssignment[invariantPair.first] = invariantInterval;
				}
				if(validState.discreteAssignment[invariantPair.first].isEmpty()){
#ifdef REACH_DEBUG
					//std::cout << "Valuation violates discrete invariant." << std::endl;
#endif
					return boost::tuple<bool, State<Number>, std::shared_ptr<const lintrafoParameters<Number>>>(false);
				}
			}

			// check continuous set for invariant
			std::pair<bool, SupportFunction<Number>> initialPair = boost::get<SupportFunction<Number>>(_state.set).satisfiesHalfspaces(_state.location->invariant().mat, _state.location->invariant().vec);
#ifdef REACH_DEBUG
			std::cout << "Valuation fulfills Invariant?: ";
		std::cout << initialPair.first << std::endl;
#endif
			if ( initialPair.first ) {
				// approximate R_[0,delta](X0)
				// R_0(X0) is just the initial Polytope X0, since t=0 -> At is zero matrix -> e^(At) is unit matrix.
				matrix_t<Number> trafoMatrix = computeTrafoMatrix(validState.location);

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

				std::shared_ptr<const lintrafoParameters<Number>> parameters = std::make_shared<lintrafoParameters<Number>>(trafoMatrix, translation);

				// if the location has no flow, stop computation and exit.
				if(trafoMatrix == matrix_t<Number>::Identity(trafoMatrix.rows(), trafoMatrix.cols()) &&
				   translation == vector_t<Number>::Zero(translation.rows()) ) {
					//std::cout << "Avoid further computation as the flow is zero." << std::endl;
					validState.set = initialPair.second;
					return boost::tuple<bool, State<Number>, std::shared_ptr<const lintrafoParameters<Number>>>(initialPair.first, validState, parameters);
				}

				SupportFunction<Number> deltaValuation = initialPair.second.linearTransformation( parameters );
#ifdef REACH_DEBUG
				std::cout << "Polytope at t=delta: ";
			deltaValuation.print();
#endif
				SupportFunction<Number> firstSegment;
				// different approaches towards bloating
				if(mSettings.uniformBloating){
					// R_0(X0) U R_delta(X0)
					SupportFunction<Number> unitePolytope = initialPair.second.unite( deltaValuation );
					//assert(unitePolytope.contains(initialPair.second));
					//assert(unitePolytope.contains(deltaValuation));
#ifdef REACH_DEBUG
					std::cout << "Polytope after unite with R0: ";
				unitePolytope.print();
#endif
					// bloat hullPolytope (Hausdorff distance)
					Number radius = hausdorffError( Number( mSettings.timeStep ), _state.location->flow(), initialPair.second.supremum() );
#ifdef REACH_DEBUG
					std::cout << "\n";
				std::cout << "Hausdorff Approximation: ";
				std::cout << radius << std::endl;
#endif
					firstSegment = unitePolytope;
					if(radius > 0){
						SupportFunction<Number> hausPoly = hypro::computePolytope<Number, SupportFunction<Number>>( unitePolytope.dimension(), radius );
#ifdef REACH_DEBUG
						std::cout << "Hausdorff Polytope (Box): ";
					hausPoly.print();
					std::cout << std::endl;
#endif
						// hullPolytope +_minkowski hausPoly
						firstSegment = unitePolytope.minkowskiSum( hausPoly );
					}
				} else {
					Number radius = hausdorffError( Number( mSettings.timeStep ), _state.location->flow(), initialPair.second.supremum() );
					if(radius > 0) {
						SupportFunction<Number> hausPoly = hypro::computePolytope<Number, SupportFunction<Number>>( initialPair.second.dimension(), radius );
						deltaValuation = deltaValuation.minkowskiSum(hausPoly);
					}
					firstSegment = initialPair.second.unite(deltaValuation);
				}
				//assert(firstSegment.contains(unitePolytope));
				//assert(firstSegment.contains(initialPair.second));
				//assert(firstSegment.contains(deltaValuation));
#ifdef REACH_DEBUG
				std::cout << "first Flowpipe Segment (after minkowski Sum): " << std::endl;
			std::cout << firstSegment << std::endl;
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
				SupportFunction<Number> fullSegment = firstSegment.intersectHalfspaces( _state.location->invariant().mat, _state.location->invariant().vec );
				//std::cout << "Full final first segment: " << fullSegment << std::endl;
				assert(firstSegment.satisfiesHalfspaces(_state.location->invariant().mat, _state.location->invariant().vec).first);
				validState.set = fullSegment;
				validState.timestamp = carl::Interval<Number>(0,mSettings.timeStep);
				return boost::tuple<bool, State<Number>, std::shared_ptr<const lintrafoParameters<Number>>>(initialPair.first, validState, parameters);
			} // if set does not satisfy the invariant, return false
			else {
				return boost::tuple<bool, State<Number>, std::shared_ptr<const lintrafoParameters<Number>>>(false);
			}
		}

		template<typename Number>
		bool Reach<Number,SupportFunction<Number>>::intersectBadStates( const State<Number>& _state, const SupportFunction<Number>& _segment ) const {
			assert(!_state.timestamp.isUnbounded());
			// check local bad states TODO: Note, we currently allow only one bad state per location -> allow multiple bad states!
			auto badStateIterator = mAutomaton.localBadStates().find(_state.location);
			if(badStateIterator != mAutomaton.localBadStates().end()){
				// check discrete variables first -> faster.
				for(const auto& assignmentPair : _state.discreteAssignment) {
					// check if there is a constraint on the variable
					if(badStateIterator->second.discreteAssignment.find(assignmentPair.first) != badStateIterator->second.discreteAssignment.end() ){
						//std::cout << "Discrete guard: " << assignmentPair.first << " in " << badStateIterator->second.discreteAssignment.at(assignmentPair.first) << " Current assignment: " << assignmentPair.second << std::endl;
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
				if(_segment.satisfiesHalfspaces(badStateIterator->second.set.first, badStateIterator->second.set.second).first == true){
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

		template<typename Number>
		void Reach<Number,SupportFunction<Number>>::printFlowpipe( const flowpipe_t<SupportFunction<Number>>& _flowpipe ) const {
			for ( const auto& segment : _flowpipe ) {
				std::cout << segment << ", " << std::endl;
			}
		}

		template<typename Number>
		void Reach<Number,SupportFunction<Number>>::printFlowpipeReduced( const flowpipe_t<SupportFunction<Number>>& _flowpipe ) const {
			std::cout << *_flowpipe.begin() << ", " << std::endl;
			std::cout << "(...)" << std::endl;
			std::cout << *_flowpipe.back() << std::endl;
		}
	}
}
#include "Reach_SF.h"
#include <chrono>
