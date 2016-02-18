#include "Reach.h"
#include <chrono>


namespace hypro {
namespace reachability {

	typedef std::chrono::high_resolution_clock clock;
	typedef std::chrono::microseconds timeunit;

	template<typename Number, typename Representation>
	Reach<Number,Representation>::Reach( const HybridAutomaton<Number, Representation>& _automaton, const ReachabilitySettings<Number> _settings)
		: mAutomaton( _automaton ), mSettings(_settings), mFlowpipes(), mReach() {}

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
        //    #ifdef FORWARD_REACHABILITY_METHOD_2
		//return computeForwardReachabilityWithMethod2();
        //    #endif

		std::cout << mSettings;

        return computeForwardReachabilityWithMethod1();
	}

        template<typename Number, typename Representation>
	std::set<std::size_t> Reach<Number,Representation>::computeForwardReachabilityWithMethod1() {
		std::size_t depth = 0;
		std::set<std::size_t> R_new;
		std::set<std::size_t> R;

		// R_new := flowpipe for the initial location, computed based on input valuation
		for ( const auto& locationPtr : mAutomaton.initialLocations() ) {
			//std::cout << "Compute time-step in initial states." << std::endl;
			// TODO: Somehow catch error case where no forwardTimeClosure could be computed.
			std::size_t init = computeForwardTimeClosure( locationPtr, mAutomaton.initialValuation() );
			//std::cout << "Computed flowpipe: " << std::endl;
			//printFlowpipeReduced( init );
			std::vector<std::size_t> fp;
			fp.push_back(init);
			mReach.insert( std::make_pair(locationPtr, std::move(fp) ));
			R_new.insert( init );
			R.insert( init );
		}

		//std::cout << "R_new: ";
		//for ( const auto& item : R_new ) std::cout << item << " ";
		//std::cout << std::endl;

		while ( !R_new.empty() && depth < mSettings.jumpDepth ) {

			std::set<std::size_t> R_temp = computeReach( R_new );

			//std::cout << "Newly generated flowpipes = ";
			//for ( const auto& item : R_temp ) std::cout << item << " ";
			//std::cout << std::endl;

			R_new.clear();
			std::set_difference( R_temp.begin(), R_temp.end(), R.begin(), R.end(),
								 std::inserter( R_new, R_new.begin() ) );

			// R = R U R_new
			if ( !R.empty() ) {
				std::set_union( R.begin(), R.end(), R_new.begin(), R_new.end(), std::inserter( R, R.begin() ) );
			} else {
				R = R_new;
			}

			++depth;
		}
		return R;
	}

        template<typename Number, typename Representation>
	std::set<std::size_t> Reach<Number,Representation>::computeForwardReachabilityWithMethod2() {
            std::size_t depth = 0;
            std::set<std::size_t> R_new;
            std::set<std::size_t> R;

            return R;
        }

	template<typename Number, typename Representation>
	std::size_t Reach<Number,Representation>::computeForwardTimeClosure( hypro::Location<Number>* _loc, const Representation& _val ) {
#ifdef REACH_DEBUG
		std::cout << "Time Interval: " << mSettings.timestep << std::endl;

		std::cout << "Initial valuation: " << std::endl;
		_val.print();

#endif
		// new empty Flowpipe
		flowpipe_t<Representation> flowpipe;
		// add initial valuation

// check if initial Valuation fulfills Invariant
#ifdef REACH_DEBUG
		std::cout << "Valuation fulfills Invariant?: ";
		std::cout << !_val.intersectHyperplanes( _loc->invariant().mat, _loc->invariant().vec ).empty() << std::endl;
#endif
		Representation initial = _val.intersectHyperplanes( _loc->invariant().mat, _loc->invariant().vec );

		//initial = initial.reduce_directed(computeTemplate<Number>(2, 5), HPolytope<Number>::REDUCTION_STRATEGY::DIRECTED_TEMPLATE);

		if ( !initial.empty() ) {
			// approximate R_[0,delta](X0)
			// rest is acquired by linear Transformation
			// R_0(X0) is just the initial Polytope X0, since t=0 -> At is zero matrix -> e^(At) is 'Einheitsmatrix'
			hypro::matrix_t<Number> deltaMatrix( _loc->activityMat().rows(), _loc->activityMat().cols() );
			deltaMatrix = _loc->activityMat() * mSettings.timestep;

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

			// e^(At)*X0 = polytope at t=delta
			unsigned rows = resultMatrix.rows();
			unsigned cols = resultMatrix.cols();
			vector_t<Number> translation = resultMatrix.col( cols - 1 );
			translation.conservativeResize( rows - 1 );
			resultMatrix.conservativeResize( rows - 1, cols - 1 );

			Representation deltaValuation = initial.linearTransformation( resultMatrix, translation );

#ifdef REACH_DEBUG
			std::cout << "Polytope at t=delta: ";
			deltaValuation.print();
#endif

			// R_0(X0) U R_delta(X0)
			Representation unitePolytope = initial.unite( deltaValuation );

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
			// radius = hausdorffError(Number(mSettings.timestep), updatedActivityMatrix, _val.supremum());
			radius = hausdorffError( Number( mSettings.timestep ), _loc->activityMat(), initial.supremum() );
// radius = _val.hausdorffError(mSettings.timestep, _loc->activityMat());

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

			// insert first Segment into the empty flowpipe
			flowpipe.push_back( firstSegment.intersectHyperplanes( _loc->invariant().mat, _loc->invariant().vec ) );

			// set the last segment of the flowpipe
			Representation lastSegment = firstSegment;

			// Polytope after linear transformation
			Representation resultPolytope;

#ifdef REACH_DEBUG
			std::cout << "--- Loop entered ---" << std::endl;
#endif

			// for each time interval perform linear Transformation
			std::size_t steps = carl::toInt<std::size_t>(carl::ceil(Number(mSettings.timebound / mSettings.timestep)));
			for ( std::size_t i = 2; i <= steps ; ++i ) {
				std::cout << "\rTime: \t" << carl::toDouble(i*mSettings.timestep) << std::flush;

				// perform linear transformation on the last segment of the flowpipe
				// lastSegment.linearTransformation(resultPolytope, tempResult);
				assert(lastSegment.linearTransformation(resultMatrix, translation).size() == lastSegment.size());
				resultPolytope = lastSegment.linearTransformation( resultMatrix, translation );

				// extend flowpipe (only if still within Invariant of location)
				Representation tmp = resultPolytope.intersectHyperplanes( _loc->invariant().mat, _loc->invariant().vec );

#ifdef REACH_DEBUG
				std::cout << "Next Flowpipe Segment: ";
				resultPolytope.print();
				std::cout << "Empty: " << resultPolytope.empty() << std::endl;

				std::cout << "still within Invariant?: ";
				std::cout << !(tmp.empty()) << std::endl;
				std::cout << "Intersection result: " << tmp << std::endl;
#endif
#ifdef USE_REDUCTION
				// clustering CONVEXHULL_CONST and reduction with directions generated before
				if(use_reduce_memory){
					if(CONVEXHULL_CONST==1){ // if no clustering is required
						if(!tmp.empty()){
							Representation poly_smoothed = tmp.reduce_directed(directions, HPolytope<Number>::REDUCTION_STRATEGY::DIRECTED_TEMPLATE);
							flowpipe.insert(flowpipe.begin(), poly_smoothed);
						}
					}
					else{
						if(!tmp.empty()){
							// collect points
							for(auto vertex: tmp.vertices()){
								if(std::find(points_convexHull.begin(),points_convexHull.end(), vertex)==points_convexHull.end()){
									points_convexHull.push_back(vertex);
								}
							}
							segment_count++;
						}

						// compute convexHull and reduction of clustered segments
						if(!points_convexHull.empty() && (segment_count==CONVEXHULL_CONST || tmp.empty())){
							auto facets = convexHull(points_convexHull);

							std::vector<Hyperplane<Number>> hyperplanes;
							for(unsigned i = 0; i<facets.first.size(); i++){
								hyperplanes.push_back(facets.first.at(i)->hyperplane());
							}
							Representation convexHull = Representation(hyperplanes);

							convexHull = convexHull.reduce_directed(directions, HPolytope<Number>::REDUCTION_STRATEGY::DIRECTED_TEMPLATE);
							convexHull.removeRedundancy();
							flowpipe.insert(flowpipe.begin(), convexHull);

							points_convexHull.clear();
							segment_count = 0;
						}
					}
				}
#endif

				if ( !tmp.empty() ) {
#ifdef USE_REDUCTION
					if(i>3 && use_reduce_memory) flowpipe.erase(flowpipe.end()-2); // keep segments necessary to compute a precise jump and delete others
#endif
					flowpipe.push_back( tmp );

					// update lastSegment
					lastSegment = tmp;
				} else {
					break;
				}
			}
			//double timeOfReachReduction = (double) std::chrono::duration_cast<timeunit>( clock::now() - start ).count()/1000;
			//std::cout << std::endl << "Total time for loop(HYPRO): " << timeOfReachReduction << std::endl;
			//std::cout << std::endl;

			std::size_t fpIndex = addFlowpipe( flowpipe );
			mFlowToLocation[fpIndex] = _loc;

#ifdef REACH_DEBUG
			std::cout << "--- Loop left ---" << std::endl;
			std::cout << "flowpipe " << fpIndex << ", " << flowpipe.size() << " Segments computed." << std::endl;
#endif

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

		// for each flowpipe in _init
		for ( auto it_pipe = _init.begin(); it_pipe != _init.end(); ++it_pipe ) {
			// get the location that belongs to the flowpipe
			hypro::Location<Number>* loc = mFlowToLocation[*it_pipe];

			//std::cout << "Consider transitions for location " << *loc << std::endl;

			// for each outgoing transition of the location
			std::set<Transition<Number>*> loc_transSet = loc->transitions();
			for ( typename std::set<Transition<Number>*>::iterator it_trans = loc_transSet.begin();
				  it_trans != loc_transSet.end(); ++it_trans ) {
				hypro::Transition<Number> trans = *( *it_trans );

				#ifdef REACH_DEBUG
				std::cout << "Consider transition " << trans << std::endl;
				#endif

				// resulting Polytope in new location
				Representation targetValuation;
				std::vector<Point<Number>> targetVertices;
				bool transitionEnabled = false;

				// for each polytope that is part of the flowpipe
				for ( typename flowpipe_t<Representation>::iterator it_val = mFlowpipes.at( *it_pipe ).begin();
					  it_val != mFlowpipes.at( *it_pipe ).end(); ++it_val ) {
					Representation postAssign;
					// check if guard of transition is enabled (if yes compute Post Assignment Valuation)
					if ( computePostCondition( trans, *it_val, postAssign ) ) {
						transitionEnabled = true;

						for(const auto& vertex : postAssign.vertices() ) {
							targetVertices.emplace_back(vertex);
						}
					}
				}
				if ( transitionEnabled ) {
					assert(!targetVertices.empty());

					targetValuation = Representation(targetVertices);
					// compute new Flowpipe
					hypro::Location<Number>* tarLoc = trans.target();

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
		//std::cout << __func__ << " end." << std::endl;
		return reach;
	}

	template<typename Number, typename Representation>
	bool Reach<Number,Representation>::computePostCondition( const hypro::Transition<Number>& _trans, const Representation& _val,
							   Representation& result ) {

		Representation intersectionPoly = _val.intersectHyperplanes( _trans.guard().mat, _trans.guard().vec );

		// check if the intersection is empty
		if ( !intersectionPoly.empty() ) {
			#ifdef REACH_DEBUG
			std::cout << "Transition enabled!" << std::endl;
			#endif

			hypro::vector_t<Number> translateVec = _trans.reset().translationVec;
			hypro::matrix_t<Number> transformMat = _trans.reset().transformMat;

			// perform translation + transformation on intersection polytope
			result = intersectionPoly.linearTransformation( transformMat, translateVec );

			return true;
		} else {
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
