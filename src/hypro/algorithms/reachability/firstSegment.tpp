

namespace hypro {
namespace reachability {

	template<typename Number, typename Representation, typename R = Representation, carl::DisableIf< std::is_same<R, Zonotope<Number>> > = carl::dummy >
	Representation bloatBox( const Representation& in, const Box<Number>& bloatBox ) {
		return in.minkowskiSum(Representation(bloatBox.matrix(), bloatBox.vector()));
	}

	template<typename Number, typename Representation, typename R = Representation, carl::EnableIf< std::is_same<R, Zonotope<Number>> > = carl::dummy >
	Zonotope<Number> bloatBox( const Zonotope<Number>& in, const Box<Number>& bloatBox ) {
		return in.minkowskiSum(Converter<Number>::toZonotope(bloatBox));
	}

	template<typename Number, typename Representation>
	boost::tuple<bool, State<Number>, matrix_t<Number>, vector_t<Number>> Reach<Number,Representation>::computeFirstSegment( const State<Number>& _state ) const {
		assert(!_state.timestamp.isUnbounded());
		// check if initial Valuation fulfills Invariant
		// check discrete invariant first
		State<Number> validState = _state;
		const typename Location<Number>::Invariant& i = _state.location->invariant();
		for(const auto& invariantPair : i.discreteInvariant) {
			carl::Interval<Number> invariantInterval = carl::Interval<Number>::unboundedInterval();
			carl::Interval<Number> substitution(0);
			// insert all current discrete assignments except the constrained one.
			for(unsigned colIndex = 0; colIndex < invariantPair.second.cols()-1; ++colIndex){
				if(colIndex != VariablePool::getInstance().id(invariantPair.first)-i.discreteOffset) {
					if(invariantPair.second(0, colIndex) != 0){
						substitution += invariantPair.second(0, colIndex) * validState.discreteAssignment.at(VariablePool::getInstance().carlVarByIndex(colIndex+i.discreteOffset));
					}
				}
			}
			// add constant term
			carl::Interval<Number> constPart(invariantPair.second(0,invariantPair.second.cols()-1));
			substitution += constPart;
			if(invariantPair.second(0,VariablePool::getInstance().id(invariantPair.first)-i.discreteOffset) > 0){
				assert(invariantPair.second(0,VariablePool::getInstance().id(invariantPair.first)-i.discreteOffset) == 1);
				invariantInterval.setUpperBound(-substitution.lower(),carl::BoundType::WEAK);
			} else {
				assert(invariantPair.second(0,VariablePool::getInstance().id(invariantPair.first)-i.discreteOffset) == -1);
				invariantInterval.setLowerBound(substitution.upper(), carl::BoundType::WEAK);
			}

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
			matrix_t<Number> trafoMatrixResized = matrix_t<Number>(rows - 1, cols - 1);
			trafoMatrixResized = trafoMatrix.block(0,0,rows -1 ,cols -1);
			translation.conservativeResize( rows - 1 );

			// if the location has no flow, stop computation and exit.
			if(trafoMatrix == matrix_t<Number>::Identity(trafoMatrix.rows(), trafoMatrix.cols()) &&
				translation == vector_t<Number>::Zero(translation.rows()) ) {
				validState.set = initialPair.second;
				return boost::tuple<bool, State<Number>, matrix_t<Number>, vector_t<Number>>(initialPair.first, validState, trafoMatrixResized, translation);
			}

			Representation deltaValuation = initialPair.second.linearTransformation( trafoMatrixResized, translation );
			#ifdef REACH_DEBUG
			std::cout << "Set at t=delta: " << deltaValuation << std::endl;
			#endif
			Representation firstSegment;
			// different approaches towards bloating
			if(mSettings.uniformBloating){ // GirardBloating
				// R_0(X0) U R_delta(X0)
				Representation unitePolytope = initialPair.second.unite( deltaValuation );
				//assert(unitePolytope.contains(initialPair.second));
				//assert(unitePolytope.contains(deltaValuation));
				#ifdef REACH_DEBUG
				std::cout << "Set after unite with R0: ";
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
					Representation hausPoly = computePolytope<Number, Representation>( unitePolytope.dimension(), radius );
					#ifdef REACH_DEBUG
					std::cout << "Hausdorff Box: ";
					hausPoly.print();
					std::cout << std::endl;
					#endif
					// hullPolytope +_minkowski hausPoly
					firstSegment = unitePolytope.minkowskiSum( hausPoly );
				}
			} else {
				Box<Number> externalInput(std::make_pair(Point<Number>(vector_t<Number>::Zero(initialPair.second.dimension())), Point<Number>(vector_t<Number>::Zero(initialPair.second.dimension()))));
				std::vector<Box<Number>> errorBoxVector = errorBoxes( Number(mSettings.timeStep), _state.location->flow(), initialPair.second, trafoMatrix, externalInput);

				Representation tmp = bloatBox<Number,Representation>(deltaValuation, errorBoxVector[1]);

				firstSegment = tmp.unite(initialPair.second);
				Box<Number> differenceBox = errorBoxVector[2];
				differenceBox = Number(Number(1)/Number(4)) * differenceBox;
				//assert(firstSegment.contains(initialPair.second));
				//assert(firstSegment.contains(deltaValuation));

				firstSegment = bloatBox<Number,Representation>(firstSegment, differenceBox);
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
			Representation fullSegment = firstSegment.intersectHalfspaces( _state.location->invariant().mat, _state.location->invariant().vec );
			assert(fullSegment.satisfiesHalfspaces(_state.location->invariant().mat, _state.location->invariant().vec).first);
			validState.set = fullSegment;
			validState.timestamp = carl::Interval<Number>(Number(0),mSettings.timeStep);
			return boost::tuple<bool, State<Number>, matrix_t<Number>, vector_t<Number>>(initialPair.first, validState, trafoMatrixResized, translation);
		} // if set does not satisfy the invariant, return false
		else {
			return boost::tuple<bool, State<Number>, matrix_t<Number>, vector_t<Number>>(false);
		}
	}

	template<typename Number, typename Representation>
	matrix_t<Number> Reach<Number,Representation>::computeTrafoMatrix( Location<Number>* _loc ) const {
		matrix_t<Number> deltaMatrix( _loc->flow().rows(), _loc->flow().cols() );
		deltaMatrix = _loc->flow() * mSettings.timeStep;

		#ifdef REACH_DEBUG
		std::cout << "delta Matrix: " << std::endl;
		std::cout << deltaMatrix << std::endl;
		std::cout << "------" << std::endl;
		#endif

		// e^(At) = resultMatrix
		matrix_t<Number> resultMatrix( deltaMatrix.rows(), deltaMatrix.cols() );

		//---
		// Workaround for:
		// resultMatrix = deltaMatrix.exp();
		//-> convert FLOAT_T to double, compute .exp(), then convert back to FLOAT_T
		Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> doubleMatrix( deltaMatrix.rows(),
																			deltaMatrix.cols() );
		Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> expMatrix( deltaMatrix.rows(), deltaMatrix.cols() );
		doubleMatrix = convert<Number,double>( deltaMatrix );
		expMatrix = doubleMatrix.exp();
		resultMatrix = convert<double,Number>( expMatrix );
		return resultMatrix;
	}

} // namespace reachability
} // namespace hypro
