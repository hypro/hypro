#pragma once
#include "../../util.h"

namespace hypro {
template <typename State>
class ltiFirstSegmentHandler : public IFirstSegmentHandler<State> {
	using Number = typename State::NumberType;

  protected:
	State* mState;  // A state containing the first segment for each subspace
	matrix_t<typename State::NumberType> mTrafo;
	vector_t<typename State::NumberType> mTranslation;
	flowVariant<Number> mFlow;

	size_t mIndex;
	tNumber mTimeStep;

  public:
	ltiFirstSegmentHandler() = delete;
	ltiFirstSegmentHandler( State* state ) {
		mState = state;
	}
	ltiFirstSegmentHandler( State* state, size_t index, tNumber timeStep ) {
		mState = state;
		mIndex = index;
		mTimeStep = timeStep;
	}

	void handle();
	const char* handlerName() { return "ltiFirstSegmentHandler"; }
	State operator()( State initialStateSet, tNumber timeStep );
	matrix_t<typename State::NumberType> computeTrafoMatrix( const Location<typename State::NumberType>* _loc ) const;

	const matrix_t<typename State::NumberType>& getTrafo() const { return std::get<affineFlow<Number>>( mFlow ).getTranslation(); }
	const vector_t<typename State::NumberType>& getTranslation() const { return std::get<affineFlow<Number>>( mFlow ).getFlowMatrix(); }
	const flowVariant<typename State::NumberType>& getTransformation() const { return mFlow; }
};
// class ltiFirstSegmentHandler {
// 	using Number = typename State::NumberType;

//   protected:
// 	matrix_t<typename State::NumberType> mTrafo;
// 	vector_t<typename State::NumberType> mTranslation;

// 	size_t mIndex;
// 	tNumber mTimeStep;

//   public:
// 	State operator()( State initialStateSet, tNumber timeStep );
// 	matrix_t<typename State::NumberType> computeTrafoMatrix( const Location<typename State::NumberType>* _loc ) const;

// 	const matrix_t<typename State::NumberType>& getTrafo() const { return mTrafo; }
// 	const vector_t<typename State::NumberType>& getTranslation() const { return mTranslation; }
// };

}  // namespace hypro

#include "ltiFirstSegmentHandler.tpp"
