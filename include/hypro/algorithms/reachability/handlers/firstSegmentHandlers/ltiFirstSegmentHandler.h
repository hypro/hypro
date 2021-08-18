#pragma once
#include "../../util.h"

namespace hypro {
template <typename State>
class ltiFirstSegmentHandler {
	using Number = typename State::NumberType;

  protected:
	matrix_t<typename State::NumberType> mTrafo;
	vector_t<typename State::NumberType> mTranslation;

	size_t mIndex;
	tNumber mTimeStep;

  public:
	State operator()( State initialStateSet, tNumber timeStep );
	matrix_t<typename State::NumberType> computeTrafoMatrix( const Location<typename State::NumberType>* _loc ) const;

	const matrix_t<typename State::NumberType>& getTrafo() const { return mTrafo; }
	const vector_t<typename State::NumberType>& getTranslation() const { return mTranslation; }
};

}  // namespace hypro

#include "ltiFirstSegmentHandler.tpp"
