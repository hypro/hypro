#include "Reset.h"

namespace hypro {
	template<typename Number>
	void Reset<Number>::setVector(const vector_t<Number>& in, std::size_t I) {
		while (mResets.size() < I+1) {
			mResets.push_back(ConstraintSet<Number>());
		}
		mResets[I].rVector() = in;
	}

	template<typename Number>
	void Reset<Number>::setMatrix(const matrix_t<Number>& in, std::size_t I) {
		while (mResets.size() < I+1) {
			mResets.push_back(ConstraintSet<Number>());
		}
		mResets[I].rMatrix() = in;
	}

	template<typename Number>
	template<typename Representation, typename ...Rargs>
	State<Number,Representation, Rargs...> Reset<Number>::applyReset(const State<Number,Representation,Rargs...>& inState) const {
		//TRACE("hydra.datastructures","Apply reset on " << inState);
		assert(inState.getNumberSets() == this->size());
		return inState.applyTransformation(mResets);
	}

} // namespace