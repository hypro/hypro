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
	std::vector<std::pair<unsigned, flowpipe_t<Representation>>> Reach<Number,Representation>::computeForwardReachability() {
		// set up working queue -> add initial states
		// collect all computed reachable states
		std::vector<std::pair<unsigned, flowpipe_t<Representation>>> collectedReachableStates;

		for ( const auto& state : mAutomaton.initialStates() ) {
			if(mCurrentLevel <= mSettings.jumpDepth){
				// Convert representation in state from matrix and vector to used representation type.
				State<Number> s;
				s.location = state.second.location;
				s.discreteAssignment = state.second.discreteAssignment;
				s.set = Representation(state.second.set.first, state.second.set.second);
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
			flowpipe_t<Representation> newFlowpipe = computeForwardTimeClosure(boost::get<1>(nextInitialSet));

			collectedReachableStates.emplace_back(std::make_pair(boost::get<1>(nextInitialSet).location->id(), newFlowpipe));
		}

		return collectedReachableStates;
	}


	template<typename Number, typename Representation>
	flowpipe_t<Representation> Reach<Number,Representation>::computeForwardTimeClosure( const State<Number>& _state ) {
		assert(!_state.timestamp.isUnbounded());
#ifdef REACH_DEBUG
		std::cout << "Location: " << _state.location->id() << std::endl;
		std::cout << "Location printed : " << *_state.location << std::endl;
		std::cout << "Time step size: " << mSettings.timeStep << std::endl;
		std::cout << "Initial valuation: " << std::endl;
		boost::get<Representation>(_state.set).print();
#endif
		// new empty Flowpipe
		flowpipe_t<Representation> flowpipe;
		std::vector<boost::tuple<Transition<Number>*, State<Number>>> nextInitialSets;

		// check for time triggered transitions once before any flowpipe is computed. TODO: put the check for transitions in the loop to the end?
		if(mCurrentLevel <= mSettings.jumpDepth) {
			bool locallyUrgent = checkTransitions(_state, carl::Interval<Number>(0), nextInitialSets);
			/*
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
								flowpipe.push_back(boost::get<Representation>(guardSatisfyingState.set));
							}
							locallyUrgent = true;
						}
					}
				}
			}
			*/
			if(locallyUrgent){
				if(mCurrentLevel < mSettings.jumpDepth) {
					processDiscreteBehaviour(nextInitialSets);
				}
				return flowpipe;
			}
		}

		boost::tuple<bool, State<Number>, matrix_t<Number>, vector_t<Number>> initialSetup = computeFirstSegment(_state);
#ifdef REACH_DEBUG
		std::cout << "Valuation fulfills Invariant?: ";
		std::cout << boost::get<0>(initialSetup) << std::endl;
#endif
		if ( boost::get<0>(initialSetup) ) {
			assert(!boost::get<1>(initialSetup).timestamp.isUnbounded());
			bool noFlow = false;

			// if the location does not have dynamic behaviour, check guards and exit loop.
			if(boost::get<2>(initialSetup) == matrix_t<Number>::Identity(boost::get<2>(initialSetup).rows(), boost::get<2>(initialSetup).cols()) &&
				boost::get<3>(initialSetup) == vector_t<Number>::Zero(boost::get<3>(initialSetup).rows())) {
				noFlow = true;
				// Collect potential new initial states from discrete behaviour.
				if(mCurrentLevel < mSettings.jumpDepth) {
					checkTransitions(_state, carl::Interval<Number>(Number(0),mSettings.timeBound), nextInitialSets);
				}
				/*
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
				*/
			}

			// insert first Segment into the empty flowpipe
			Representation currentSegment;
			if(noFlow) {
				currentSegment = boost::get<Representation>(_state.set);
			} else {
				currentSegment = boost::get<Representation>(boost::get<1>(initialSetup).set);
			}
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
#ifdef USE_SYSTEM_SEPARATION
			Representation autonomPart = currentSegment;
#ifdef USE_ELLIPSOIDS
			// Easy to addapt to any Representation use ellipsoid for the idea of my masterthesis here
			Ellipsoid<Number> nonautonomPart(mBloatingFactor, currentSegment.dimension());
			Ellipsoid<Number> totalBloating = nonautonomPart;
#else
			Ellipsoid<Number> nonautonomPartAsEllispsoid(mBloatingFactor, currentSegment.dimension());
			Representation nonautonomPart = Representation(nonautonomPartAsEllispsoid);
			std::cout << nonautonomPart << std::endl;
			Representation totalBloating = nonautonomPart;
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
			while( !noFlow && currentLocalTime <= mSettings.timeBound ) {
				std::cout << "\rTime: \t" << std::setprecision(4) << std::setw(8) << fixed << carl::toDouble(currentLocalTime) << std::flush;
				// Verify transitions on the current set.
				if(mCurrentLevel <= mSettings.jumpDepth) {
					State<Number> guardSatisfyingState;
					State<Number> currentState = _state;
					currentState.set = currentSegment;
					currentState.timestamp += carl::Interval<Number>(currentLocalTime-mSettings.timeStep,currentLocalTime);
					currentState.timestamp = currentState.timestamp.intersect(carl::Interval<Number>(Number(0), mSettings.timeBound));
					bool fireTimeTriggeredTransition = checkTransitions(currentState, currentState.timestamp, nextInitialSets);
					/*
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
							assert(guardSatisfyingState.timestamp == currentState.timestamp);
							//std::cout << "hybrid transition enabled" << std::endl;
							//std::cout << *transition << std::endl;
							nextInitialSets.emplace_back(transition, guardSatisfyingState);
						}
					}
					*/
					if(fireTimeTriggeredTransition){
						// quit loop after firing time triggered transition -> time triggered transitions are handled as urgent.
						#ifdef REACH_DEBUG
						std::cout << "Fired time triggered transition." << std::endl;
						#endif
						break;
					}
				}

				// perform linear transformation on the last segment of the flowpipe
				assert(currentSegment.linearTransformation(boost::get<2>(initialSetup), boost::get<3>(initialSetup)).size() == currentSegment.size());
#ifdef USE_SYSTEM_SEPARATION
				autonomPart = autonomPart.linearTransformation( boost::get<2>(initialSetup), boost::get<3>(initialSetup) );
#ifdef USE_ELLIPSOIDS
				if (mBloatingFactor != 0){
					Representation temp = Representation(totalBloating);
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
				nextSegment = currentSegment.linearTransformation( boost::get<2>(initialSetup), boost::get<3>(initialSetup) );
#endif
				// extend flowpipe (only if still within Invariant of location)
				std::pair<bool, Representation> newSegment = nextSegment.satisfiesHalfspaces( _state.location->invariant().mat, _state.location->invariant().vec );
#ifdef REACH_DEBUG
				std::cout << "Next Flowpipe Segment: " << nextSegment << std::endl;
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

					//unsigned tmp = plotter.addObject(newSegment.second.vertices());
					//plotter.setObjectColor(tmp, colors[_state.location->id()]);

					if(intersectBadStates(_state, newSegment.second)){
						// clear queue to stop whole algorithm
						while(!mWorkingQueue.empty()){
							mWorkingQueue.pop();
						}
						return flowpipe;
					}
					// update currentSegment
					currentSegment = newSegment.second;
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
			if(mCurrentLevel < mSettings.jumpDepth){
				processDiscreteBehaviour(nextInitialSets);
			}
			return flowpipe;
		} else {
			// return an empty flowpipe
			return flowpipe;
		}
	}

} // namespace reachability
} // namespace hypro
