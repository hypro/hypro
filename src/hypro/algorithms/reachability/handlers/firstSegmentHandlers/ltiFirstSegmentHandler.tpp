#include "ltiFirstSegmentHandler.h"

namespace hypro
{
    template<typename State>
    void ltiFirstSegmentHandler<State>::handle() {
		assert(!mState->getTimestamp().isEmpty());
	    // check if initial Valuation fulfills Invariant
	    assert(mState->getLocation() != nullptr);

        std::size_t dim = getFlowDimension(mState->getLocation()->getFlow(mIndex));

    	// if the location has no flow, stop computation and exit.
        if (isDiscrete(mState->getLocation()->getFlow(mIndex))) {
            // TRACE("Avoid further computation as the flow is zero." << std::endl);
            mTrafo = matrix_t<Number>::Identity(dim-1,dim-1);
            mTranslation = vector_t<Number>::Zero(dim-1);
            return ;
        }

        // approximate R_[0,delta](X0)
        // R_0(X0) is just the initial Polytope X0, since t=0 -> At is zero matrix -> e^(At) is unit matrix.
        matrix_t<Number> trafoMatrix = computeTrafoMatrix(mState->getLocation());

        #ifdef HYDRA_USE_LOGGING
        TRACE("hydra.worker", "e^(deltaMatrix): " << std::endl);
        TRACE("hydra.worker", trafoMatrix << std::endl);
        TRACE("hydra.worker", "------" << std::endl);
        #endif

        // e^(At)*X0 = polytope at t=delta
        unsigned rows = trafoMatrix.rows();
        unsigned cols = trafoMatrix.cols();
        vector_t<Number> translation = trafoMatrix.col(cols - 1);
        matrix_t<Number> trafoMatrixResized = matrix_t<Number>(rows - 1, cols - 1);
        trafoMatrixResized = trafoMatrix.block(0, 0, rows - 1, cols - 1);
        translation.conservativeResize(rows - 1);

        mTrafo = trafoMatrixResized;
        mTranslation = translation;
        // update flow type
        //mState->rGetLocation()->setFlow(mIndex,affineFlow<Number>(mTrafo,mTranslation));

        State deltaValuation = mState->partiallyApplyTimeStep(ConstraintSet<Number>(mTrafo, mTranslation), mTimeStep,mIndex);

        #ifdef HYDRA_USE_LOGGING
        TRACE("hydra.worker", "Polytope at t=delta: " << deltaValuation);
        #endif

        State firstSegment{mState->getLocation()};
        unsigned dimension = mState->getDimension(mIndex);
        Box<Number> externalInput(std::make_pair(Point<Number>(vector_t<Number>::Zero(dimension)),
                                                       Point<Number>(vector_t<Number>::Zero(dimension))));

        std::vector<Box<Number>> errorBoxVector =
              errorBoxes(carl::convert<tNumber,Number>(mTimeStep), boost::get<affineFlow<Number>>(mState->getLocation()->getFlow(mIndex)), *mState, trafoMatrix, externalInput);

        firstSegment = deltaValuation.unite(*(mState));

    	#ifdef HYDRA_USE_LOGGING
        TRACE("hydra.worker", "Errorbox X_0: " << errorBoxVector[0] << " with dimension " << errorBoxVector[0].dimension() << " and d: " << dimension);
        #endif

		firstSegment = bloatBox(firstSegment, Number(Number(1) / Number(4)) * errorBoxVector[2], mIndex);

        TRACE("hydra.worker","Epsilon errorbox: " << errorBoxVector[2]);

        #ifdef HYDRA_USE_LOGGING
        TRACE("hydra.worker", "first Flowpipe Segment (after minkowski Sum): " << firstSegment);
        #endif

        firstSegment.partiallyRemoveRedundancy(mIndex);
        mState->setSet(firstSegment.getSet(mIndex),mIndex);
	}

    template <typename State>
	matrix_t<typename State::NumberType> ltiFirstSegmentHandler<State>::computeTrafoMatrix(const Location<Number>* _loc) const
	{
	   matrix_t<Number> deltaMatrix(getFlowDimension(_loc->getFlow()), getFlowDimension(_loc->getFlow()));
	    deltaMatrix = boost::get<linearFlow<Number>>(_loc->getFlow(mIndex)).getFlowMatrix() * carl::convert<tNumber,Number>(mTimeStep);
	#ifdef REACH_DEBUG
	    TRACE("hydra.worker", "Flowmatrix:\n" << _loc->getFlow(mIndex) << "\nmultiplied with time step: " << mTimeStep);
	    TRACE("hydra.worker", "delta matrix_t<Number>: " << std::endl);
	    TRACE("hydra.worker", deltaMatrix << std::endl);
	    TRACE("hydra.worker", "------" << std::endl);
	#endif


	    // e^(At) = resultMatrix
	   matrix_t<Number> resultMatrix(deltaMatrix.rows(), deltaMatrix.cols());

	    //---
	    // Workaround for:
	    // resultMatrix = deltaMatrix.exp();
	    //-> convert FLOAT_T to double, compute .exp(), then convert back to FLOAT_T
	   matrix_t<double> doubleMatrix(deltaMatrix.rows(), deltaMatrix.cols());
	   matrix_t<double> expMatrix(deltaMatrix.rows(), deltaMatrix.cols());
	    doubleMatrix =convert<Number, double>(deltaMatrix);

	    TRACE("hydra.worker","transformed matrix: " << doubleMatrix);

	    expMatrix = doubleMatrix.exp();

	    TRACE("hydra.worker","exp matrix: " << expMatrix);

	    resultMatrix =convert<double, Number>(expMatrix);

		TRACE("hydra.worker","transformed matrix: " << resultMatrix);

	    return resultMatrix;

	}
} // hypro
