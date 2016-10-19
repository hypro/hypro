

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
	boost::tuple<bool, State<Number>, TrafoParameters<Number>> Reach<Number,Representation>::computeFirstSegment( const State<Number>& _state ) const {
		assert(!_state.timestamp.isUnbounded());
		// check if initial Valuation fulfills Invariant
		State<Number> validState = _state;

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
				return boost::tuple<bool, State<Number>, TrafoParameters<Number>>(initialPair.first, validState, TrafoParameters<Number>(trafoMatrixResized, translation));
			}

			// Representation deltaValuation = initialPair.second.linearTransformation( trafoMatrixResized, translation );
			Representation deltaValuation = applyLinearTransformation(initialPair.second, TrafoParameters<Number>(trafoMatrixResized, translation));

			//std::cout << "Vertices delta valuation: " << std::endl;
			//for(const auto& vertex : deltaValuation.vertices()) {
			//	std::cout << convert<Number,double>(vertex) << std::endl;
			//}

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

				/*

				//Representation tmp = bloatBox<Number,Representation>(deltaValuation, errorBoxVector[1]);
				//std::cout << "Errorbox1: " << convert<Number,double>(errorBoxVector[1]) << std::endl;

				firstSegment = deltaValuation.unite(initialPair.second);
				//Box<Number> differenceBox = errorBoxVector[2];
				//differenceBox = Number(Number(1)/Number(4)) * differenceBox;

				//std::cout << "DifferenceBox: " << convert<Number,double>(differenceBox) << std::endl;
				std::cout << "1/4 * X_0 box: " << convert<Number,double>(Number(Number(1)/Number(4)) * errorBoxVector[0]) << std::endl;

				//firstSegment = bloatBox<Number,Representation>(firstSegment, differenceBox);
				// We directly use the errorBox for X_0, as in our setup, all systems are autonomous.
				firstSegment = bloatBox<Number,Representation>(firstSegment, Number(Number(1)/Number(4)) * errorBoxVector[0]);

				*/
				// Experimental: We assume that there should be first a bloating and then a CH operation.
				std::cout << "1/4 * X_0 box: " << convert<Number,double>(Number(Number(1)/Number(4)) * errorBoxVector[0]) << std::endl;
				firstSegment = initialPair.second.unite(bloatBox<Number,Representation>(deltaValuation, Number(Number(1)/Number(4))*errorBoxVector[0]));
			}

			#ifdef REACH_DEBUG
			std::cout << "first Flowpipe Segment (after minkowski Sum): " << std::endl;
			std::cout << firstSegment << std::endl;
			#endif

			//assert(firstSegment.contains(unitePolytope));
			assert(firstSegment.contains(initialPair.second));
			assert(firstSegment.contains(deltaValuation));
			firstSegment.removeRedundancy();

			// set the last segment of the flowpipe. Note that intersection with the invariants cannot result in an empty set due to previous checks.
			Representation fullSegment = firstSegment.intersectHalfspaces( _state.location->invariant().mat, _state.location->invariant().vec );
			assert(fullSegment.satisfiesHalfspaces(_state.location->invariant().mat, _state.location->invariant().vec).first);
			validState.set = fullSegment;
			validState.timestamp = carl::Interval<Number>(Number(0),mSettings.timeStep);

			//std::cout << "Vertices first segment:" << std::endl;
			//for(const auto& vertex : fullSegment.vertices()) {
			//	std::cout << convert<Number,double>(vertex) << std::endl;
			//}

			return boost::tuple<bool, State<Number>, TrafoParameters<Number>>(initialPair.first, validState, TrafoParameters<Number>(trafoMatrixResized, translation));
		} // if set does not satisfy the invariant, return false
		else {
			return boost::tuple<bool, State<Number>, TrafoParameters<Number>>(false);
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
