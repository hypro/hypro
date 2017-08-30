

namespace hypro {
namespace reachability {

	/*
	template<typename Number, typename Representation, typename R = Representation, carl::DisableIf< std::is_same<R, Zonotope<Number>> > = carl::dummy >
Representation bloatBox( const Representation& in, const Box<Number>& bloatBox ) {
	return in.minkowskiSum(Representation(bloatBox.matrix(), bloatBox.vector()));
}

template<typename Number, typename Representation, typename R = Representation, carl::EnableIf< std::is_same<R, Zonotope<Number>> > = carl::dummy >
Zonotope<Number> bloatBox( const Zonotope<Number>& in, const Box<Number>& bloatBox ) {
	return in.minkowskiSum(Converter<Number>::toZonotope(bloatBox));
}
	*/

	template<typename Number>
State_t<Number> bloatBox( const State_t<Number>& in, const Box<Number>& bloatBox ) {
	State_t<Number> bloatState;
	switch(in.getSetType(0)) {
		case representation_name::box: {
			bloatState.setSet(Converter<Number>::toBox(bloatBox), 0);
			break;
		}
		case representation_name::polytope_h: {
			bloatState.setSet(Converter<Number>::toHPolytope(bloatBox), 0);
			break;
		}
		case representation_name::polytope_v: {
			bloatState.setSet(Converter<Number>::toVPolytope(bloatBox), 0);
			break;
		}
		case representation_name::support_function: {
			bloatState.setSet(Converter<Number>::toSupportFunction(bloatBox), 0);
			break;
		}
		case representation_name::zonotope: {
			bloatState.setSet(Converter<Number>::toZonotope(bloatBox), 0);
			break;
		}
		default: {
			bloatState.setSet(Converter<Number>::toBox(bloatBox), 0);
			break;
		}
	}
	return in.partiallyMinkowskiSum(bloatState, 0);
}

	template<typename Number>
	boost::tuple<bool, State_t<Number>, matrix_t<Number>, vector_t<Number>> Reach<Number>::computeFirstSegment( const State_t<Number>& _state ) const {
		assert(!_state.getTimestamp().isUnbounded());
		// check if initial Valuation fulfills Invariant
		State_t<Number> validState = _state;

		// approximate R_[0,delta](X0)
		// R_0(X0) is just the initial Polytope X0, since t=0 -> At is zero matrix -> e^(At) is unit matrix.
		matrix_t<Number> trafoMatrix = computeTrafoMatrix(validState.getLocation());

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

		// if the.getLocation() has no flow, stop computation and exit.
		if(trafoMatrix == matrix_t<Number>::Identity(trafoMatrix.rows(), trafoMatrix.cols()) &&
			translation == vector_t<Number>::Zero(translation.rows()) ) {

			std::pair<bool,State_t<Number>> fullSegment = _state.satisfies(_state.getLocation()->getInvariant());
			validState.setSetDirect(fullSegment.second.getSet());
			return boost::tuple<bool, State_t<Number>, matrix_t<Number>, vector_t<Number>>(fullSegment.first, validState, trafoMatrixResized, translation);
		}

		// Representation deltaValuation = initialPair.second.linearTransformation( trafoMatrixResized, translation );
		State_t<Number> deltaValuation = _state.applyTransformation(ConstraintSet<Number>(trafoMatrixResized, translation));

		//Plotter<Number>::getInstance().addObject(boost::get<Representation>(_state.set).vertices());
		//Plotter<Number>::getInstance().addObject(deltaValuation.vertices());

		//std::cout << "Initial set vertices: " << boost::get<Representation>(_state.set).vertices() << std::endl;
		//std::cout << "Delta Valuation vertices: " << deltaValuation.vertices() << std::endl;

		#ifdef REACH_DEBUG
		std::cout << "Set at t=delta: " << deltaValuation << std::endl;
		#endif

		State_t<Number> firstSegment;
		// different approaches towards bloating
		if(mSettings.uniformBloating){ // GirardBloating
			// R_0(X0) U R_delta(X0)
			State_t<Number> unitePolytope = _state.aggregate( deltaValuation );
			//assert(unitePolytope.contains(initialPair.second));
			//assert(unitePolytope.contains(deltaValuation));
			#ifdef REACH_DEBUG
			std::cout << "Set after unite with R0: " << std::endl;
			std::cout << unitePolytope << std::endl;
			#endif
			// bloat hullPolytope (Hausdorff distance)
			// TODO: This will not work, we need the hausdorf error.
			Number radius = hausdorffError( Number( mSettings.timeStep ), _state.getLocation()->getFlow(), _state.getSupremum(0) );
			#ifdef REACH_DEBUG
			std::cout << "\n";
			std::cout << "Hausdorff Approximation: ";
			std::cout << radius << std::endl;
			#endif
			firstSegment = unitePolytope;
			if(radius > 0){
				State_t<Number> hausPoly;
				switch(unitePolytope.getSetType(0)) {
					case representation_name::box: {
						hausPoly = computePolytope<Number,representation_name::box>( unitePolytope.getDimension(0), radius );
						break;
					}
					case representation_name::polytope_h: {
						hausPoly = computePolytope<Number,representation_name::polytope_h>( unitePolytope.getDimension(0), radius );
						break;
					}
					case representation_name::polytope_v: {
						hausPoly = computePolytope<Number,representation_name::polytope_v>( unitePolytope.getDimension(0), radius );
						break;
					}
					case representation_name::support_function: {
						hausPoly = computePolytope<Number,representation_name::support_function>( unitePolytope.getDimension(0), radius );
						break;
					}
					case representation_name::zonotope: {
						hausPoly = computePolytope<Number,representation_name::zonotope>( unitePolytope.getDimension(0), radius );
						break;
					}
					default: {
						hausPoly = computePolytope<Number,representation_name::box>( unitePolytope.getDimension(0), radius );
						break;
					}
				}
				//State_t<Number> hausPoly = computePolytope<Number,unitePolytope.getSetType(0)>( unitePolytope.getDimension(0), radius );
				#ifdef REACH_DEBUG
				std::cout << "Hausdorff Box: " << std::endl;
				std::cout << hausPoly << std::endl;
				#endif
				// hullPolytope +_minkowski hausPoly
				firstSegment = unitePolytope.minkowskiSum(hausPoly);
			}
		} else {
			Box<Number> externalInput(std::make_pair(Point<Number>(vector_t<Number>::Zero(_state.getDimension(0))), Point<Number>(vector_t<Number>::Zero(_state.getDimension(0)))));
			std::vector<Box<Number>> errorBoxVector = errorBoxes( Number(mSettings.timeStep), _state.getLocation()->getFlow(), _state, trafoMatrix, externalInput);

			//Representation tmp = bloatBox<Number>(deltaValuation, errorBoxVector[1]);
			//std::cout << "Errorbox1: " << convert<Number,double>(errorBoxVector[1]) << std::endl;

			firstSegment = deltaValuation.aggregate(_state);
			//Box<Number> differenceBox = errorBoxVector[2];
			//differenceBox = Number(Number(1)/Number(4)) * differenceBox;

			//std::cout << "DifferenceBox: " << convert<Number,double>(differenceBox) << std::endl;
			//std::cout << "1/4 * X_0 box: " << convert<Number,double>(Number(Number(1)/Number(4)) * errorBoxVector[0]) << std::endl;

			//firstSegment = bloatBox<Number>(firstSegment, differenceBox);
			// We directly use the errorBox for X_0, as in our setup, all systems are autonomous.
			if(!errorBoxVector.empty()){
				firstSegment = bloatBox<Number>(firstSegment, Number(Number(1)/Number(4)) * errorBoxVector[0]);
			} else {
				// in the current setup, the errorboxVector is empty, when the initial set was empty - we can directly skip this.
				return boost::tuple<bool, State_t<Number>, matrix_t<Number>, vector_t<Number>>(false);
			}
		}

		#ifdef REACH_DEBUG
		std::cout << "first Flowpipe Segment (after bloating): " << std::endl;
		std::cout << firstSegment << std::endl;
		#endif

		//Plotter<Number>::getInstance().addObject(firstSegment.vertices());

		//assert(firstSegment.contains(unitePolytope));
		//assert(firstSegment.contains(boost::get<Representation>(_state.set)));
		//assert(firstSegment.contains(deltaValuation));

		firstSegment.removeRedundancy();

		// set the last segment of the flowpipe. Note that intersection with the invariants cannot result in an empty set due to previous checks.
		std::pair<bool, State_t<Number>> fullSegment = firstSegment.satisfies( _state.getLocation()->getInvariant());
		#ifdef REACH_DEBUG
		std::cout << "Valuation fulfills Invariant?: ";
		std::cout << fullSegment.first << std::endl;
		#endif
		if(fullSegment.first) {
			validState.setSets(fullSegment.second.getSets());
			validState.setTimestamp(carl::Interval<Number>(Number(0),mSettings.timeStep));
			return boost::tuple<bool, State_t<Number>, matrix_t<Number>, vector_t<Number>>(true, validState, trafoMatrixResized, translation);
		} else {
			return boost::tuple<bool, State_t<Number>, matrix_t<Number>, vector_t<Number>>(false);
		}
	}

	template<typename Number>
	matrix_t<Number> Reach<Number>::computeTrafoMatrix( const Location<Number>* _loc ) const {
		matrix_t<Number> deltaMatrix( _loc->getFlow().rows(), _loc->getFlow().cols() );
		deltaMatrix = _loc->getFlow() * mSettings.timeStep;

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
