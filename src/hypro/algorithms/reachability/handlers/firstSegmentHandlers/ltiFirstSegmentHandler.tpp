#include "ltiFirstSegmentHandler.h"

namespace hypro
{
    template<typename Representation, typename Number>
    void ltiFirstSegmentHandler<Representation,Number>::handle() {
		assert(!mState->getTimestamp().isEmpty());
	    // check if initial Valuation fulfills Invariant
	    assert(mState->getLocation() != nullptr);

    	// if the location has no flow, stop computation and exit.
        if (mState->getLocation()->getFlow(mIndex) == matrix_t<Number>::Zero(mState->getLocation()->getFlow(mIndex).rows(), mState->getLocation()->getFlow(mIndex).cols())) {
            // TRACE("Avoid further computation as the flow is zero." << std::endl);
            int rows = mState->getLocation()->getFlow(mIndex).rows();
            mTrafo = matrix_t<Number>::Identity(rows-1,rows-1);
            mTranslation = vector_t<Number>::Zero(rows-1);
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
        State_t<Number> deltaValuation = mState->partiallyApplyTimeStep(ConstraintSet<Number>(mTrafo, mTranslation), mTimeStep,mIndex);
       
        #ifdef HYDRA_USE_LOGGING
        TRACE("hydra.worker", "Polytope at t=delta: " << deltaValuation);
        #endif

        State_t<Number> firstSegment(mState->getLocation());
        unsigned dimension = boost::get<Representation>(mState->getSet(mIndex)).dimension();
       Box<Number> externalInput(std::make_pair(Point<Number>(vector_t<Number>::Zero(dimension+1)),
                                                       Point<Number>(vector_t<Number>::Zero(dimension+1))));

        std::vector<Box<Number>> errorBoxVector =
              errorBoxes(carl::convert<tNumber,Number>(mTimeStep), mState->getLocation()->getFlow(mIndex), *mState, trafoMatrix, externalInput);       

        firstSegment = deltaValuation.unite(*(mState));

    	#ifdef HYDRA_USE_LOGGING
        TRACE("hydra.worker", "Errorbox X_0: " << errorBoxVector[0] << " with dimension " << errorBoxVector[0].dimension() << " and d: " << dimension);
        #endif

		firstSegment = bloatBox<Number>(firstSegment, Number(Number(1) / Number(4)) * errorBoxVector[2], mIndex);     

        TRACE("hydra.worker","Epsilon errorbox: " << errorBoxVector[2]);

        #ifdef HYDRA_USE_LOGGING
        TRACE("hydra.worker", "first Flowpipe Segment (after minkowski Sum): " << firstSegment);
        #endif

        Representation set = boost::get<Representation>(firstSegment.getSet(mIndex));
        set.removeRedundancy();

        mState->setSet(set,mIndex);
	}

    template <typename Representation,typename Number>
	matrix_t<Number> ltiFirstSegmentHandler<Representation,Number>::computeTrafoMatrix(const Location<Number>* _loc) const
	{  
	   matrix_t<Number> deltaMatrix(_loc->getFlow(mIndex).rows(), _loc->getFlow(mIndex).cols());
	    deltaMatrix = _loc->getFlow(mIndex) * carl::convert<tNumber,Number>(mTimeStep);
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
