#include "Location.h"

namespace hypro {

	template<typename Number>
	Location<Number>::Location(unsigned _id) :
		mActivityVec(),
		mActivityMat(),
		mExternalInput(),
		mTransitions(),
		mInvariant(),
		mId(_id)
	{}

	template<typename Number>
	Location<Number>::Location(unsigned _id, const Location& _loc) :
		mActivityVec(_loc.activityVec()),
		mActivityMat(_loc.activityMat()),
		mExternalInput(_loc.externalInput()),
		mTransitions(_loc.transitions()),
		mInvariant(_loc.invariant()),
		mId(_id)
	{}

	template<typename Number>
	Location<Number>::Location(unsigned _id, const hypro::matrix_t<Number> _mat, const hypro::vector_t<Number> _vec, const transitionSet _trans, const Location<Number>::Invariant _inv) :
		mActivityVec(_vec),
		mActivityMat(_mat),
		mExternalInput(),
		mTransitions(_trans),
		mInvariant(_inv),
		mId(_id)
	{}

	template<typename Number>
	Location<Number>::Location(unsigned _id, const hypro::matrix_t<Number> _mat, const hypro::vector_t<Number> _vec,
			const transitionSet _trans, const Location<Number>::Invariant _inv, const hypro::matrix_t<Number> _extInputMat) :
				mActivityVec(_vec),
				mActivityMat(_mat),
				mExternalInput(_extInputMat),
				mTransitions(_trans),
				mInvariant(_inv),
				mId(_id)
	{}

	template<typename Number>
	const hypro::vector_t<Number>& Location<Number>::activityVec() const {
		return mActivityVec;
	}

	template<typename Number>
	const hypro::matrix_t<Number>& Location<Number>::activityMat() const {
		return mActivityMat;
	}

	template<typename Number>
	const hypro::matrix_t<Number>& Location<Number>::externalInput() const {
		return mExternalInput;
	}

	template<typename Number>
	const typename Location<Number>::Invariant& Location<Number>::invariant() const {
		return mInvariant;
	}

	template<typename Number>
	const std::set<Transition<Number>*>& Location<Number>::transitions() const {
		return mTransitions;
	}

	template<typename Number>
	void Location<Number>::setActivityVec(hypro::vector_t<Number> _vec) {
		mActivityVec = _vec;
	}

	template<typename Number>
	void Location<Number>::setActivityMat(hypro::matrix_t<Number> _mat) {
		mActivityMat = _mat;
	}

	template<typename Number>
	void Location<Number>::setExtInputMat(hypro::matrix_t<Number> _mat) {
		mExternalInput = _mat;
	}

	template<typename Number>
	void Location<Number>::setInvariant(hypro::Location<Number>::Invariant _inv) {
		mInvariant = _inv;
	}

	template<typename Number>
	void Location<Number>::setInvariant(hypro::matrix_t<Number> _mat, hypro::vector_t<Number> _vec, hypro::operator_e _op) {
		mInvariant.op = _op;
		mInvariant.vec = _vec;
		mInvariant.mat = _mat;
	}

	template<typename Number>
	void Location<Number>::setTransitions(transitionSet _trans) {
		mTransitions = _trans;
	}

}
