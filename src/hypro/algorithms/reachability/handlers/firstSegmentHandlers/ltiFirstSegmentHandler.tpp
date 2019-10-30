#include "ltiFirstSegmentHandler.h"

namespace hypro
{

    template<typename State>
    void ltiFirstSegmentHandler<State>::handle() {
        assert(!mState->getTimestamp().isEmpty());
        // check if initial Valuation fulfills Invariant
        assert(mState->getLocation() != nullptr);

        std::size_t dim = mState->getLocation()->getLinearFlow(mIndex).dimension();

        // if the location has no flow, stop computation and exit.
        if (mState->getLocation()->getLinearFlow(mIndex).isDiscrete()) {
            // TRACE("Avoid further computation as the flow is zero." << std::endl);
            mTrafo = matrix_t<Number>::Identity(dim-1,dim-1);
            mTranslation = vector_t<Number>::Zero(dim-1);
            mFlow = affineFlow<Number>{mTrafo,mTranslation};
            return ;
        }

        // approximate R_[0,delta](X0)
        // R_0(X0) is just the initial Polytope X0, since t=0 -> At is zero matrix -> e^(At) is unit matrix.
        matrix_t<Number> trafoMatrix = computeTrafoMatrix(mState->getLocation());

        TRACE("hypro.worker", "e^(deltaMatrix): " << std::endl);
        TRACE("hypro.worker", trafoMatrix << std::endl);
        TRACE("hypro.worker", "------" << std::endl);

        // e^(At)*X0 = polytope at t=delta
        unsigned rows = trafoMatrix.rows();
        unsigned cols = trafoMatrix.cols();
        vector_t<Number> translation = trafoMatrix.col(cols - 1);
        matrix_t<Number> trafoMatrixResized = matrix_t<Number>(rows - 1, cols - 1);
        trafoMatrixResized = trafoMatrix.block(0, 0, rows - 1, cols - 1);
        translation.conservativeResize(rows - 1);

        // update flow type
        mFlow = affineFlow<Number>{trafoMatrixResized, translation};
        //mState->rGetLocation()->setFlow(mIndex,affineFlow<Number>(mTrafo,mTranslation));

        State deltaValuation = mState->partiallyApplyTimeStep(ConstraintSet<Number>(trafoMatrixResized, translation), mTimeStep,mIndex);
        
        #ifdef HYDRA_USE_LOGGING
        TRACE("hypro.worker", "Polytope at t=delta: " << deltaValuation);
        #endif

        State firstSegment{mState->getLocation()};
        unsigned dimension = mState->getDimension(mIndex);
        Box<Number> externalInput(std::make_pair(Point<Number>(vector_t<Number>::Zero(dimension)),
                                                       Point<Number>(vector_t<Number>::Zero(dimension))));

        std::vector<Box<Number>> errorBoxVector =
              errorBoxes(carl::convert<tNumber,Number>(mTimeStep), mState->getLocation()->getLinearFlow(mIndex), *mState, trafoMatrix, externalInput);

        firstSegment = bloatBox(deltaValuation, Number(Number(1) / Number(4)) * errorBoxVector[2], mIndex);

        TRACE("hypro.worker","Epsilon errorbox: " << errorBoxVector[2]);

        firstSegment = firstSegment.unite(*(mState));

        TRACE("hypro.worker", "first Flowpipe Segment (after minkowski Sum): " << firstSegment);

        //This would usually be the first segment. However we need the backprojection from deltaValuation to the initial set to make the first segment smaller.
        firstSegment.partiallyRemoveRedundancy(mIndex);

        //Bloat initialState
        matrix_t<Number> trafoMatrixInverse = trafoMatrix.inverse();
        assert(trafoMatrix*trafoMatrixInverse == matrix_t<Number>::Identity(trafoMatrix.rows(), trafoMatrix.cols()));
        std::vector<Box<Number>> errorBoxVectorBackwards = errorBoxes(carl::convert<tNumber,Number>(-mTimeStep), mState->getLocation()->getLinearFlow(mIndex), *mState, trafoMatrixInverse, externalInput);
        State inverseFirstSegment = bloatBox(*mState, Number(Number(1) / Number(4)) * errorBoxVectorBackwards[2], mIndex);
        assert(inverseFirstSegment.contains(*mState));
        
        //Unite bloated initial and deltaValuation
        inverseFirstSegment = inverseFirstSegment.unite(deltaValuation);
        assert(inverseFirstSegment.contains(*mState));
        assert(inverseFirstSegment.contains(deltaValuation));
        
        //Intersect inverseFirstSegment and firstSegment
        firstSegment = firstSegment.intersect(inverseFirstSegment);
        assert(firstSegment.contains(*mState));
        assert(firstSegment.contains(deltaValuation));

        firstSegment.partiallyRemoveRedundancy(mIndex);
        assert(firstSegment.contains(*mState));
        assert(firstSegment.contains(deltaValuation));
        
        mState->setSet(firstSegment.getSet(mIndex),mIndex);
    }

    template <typename State>
	matrix_t<typename State::NumberType> ltiFirstSegmentHandler<State>::computeTrafoMatrix(const Location<Number>* _loc) const
	{
	   matrix_t<Number> deltaMatrix(_loc->getLinearFlow().dimension(), _loc->getLinearFlow().dimension());
	    deltaMatrix = _loc->getLinearFlow(mIndex).getFlowMatrix() * carl::convert<tNumber,Number>(mTimeStep);
	    TRACE("hypro.worker", "Flowmatrix:\n" << _loc->getLinearFlow(mIndex) << "\nmultiplied with time step: " << mTimeStep);
	    TRACE("hypro.worker", "delta matrix_t<Number>: " << std::endl);
	    TRACE("hypro.worker", deltaMatrix << std::endl);
	    TRACE("hypro.worker", "------" << std::endl);



	    // e^(At) = resultMatrix
	   matrix_t<Number> resultMatrix(deltaMatrix.rows(), deltaMatrix.cols());

	    //---
	    // Workaround for:
	    // resultMatrix = deltaMatrix.exp();
	    //-> convert FLOAT_T to double, compute .exp(), then convert back to FLOAT_T
	   matrix_t<double> doubleMatrix(deltaMatrix.rows(), deltaMatrix.cols());
	   matrix_t<double> expMatrix(deltaMatrix.rows(), deltaMatrix.cols());
	   doubleMatrix =convert<Number, double>(deltaMatrix);

	   TRACE("hypro.worker","transformed matrix: " << doubleMatrix);

	   expMatrix = doubleMatrix.exp();

	   TRACE("hypro.worker","exp matrix: " << expMatrix);

	   resultMatrix =convert<double, Number>(expMatrix);

	   TRACE("hypro.worker","transformed matrix: " << resultMatrix);

	   return resultMatrix;

	}
} // hypro
