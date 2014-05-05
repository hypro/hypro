#include "Location.h"

namespace hypro {

	template<typename Number>
	Location<Number>::Location(const Location& _loc) : mLocation(_loc.mLocation){
	}

	template<typename Number>
	Location<Number>::Location(const matrix_t* _mat, const vector_t _vec, const invariant _inv){
		mMatrixAct = _mat;
		mVecAct = _vec;
		mInvariant = _inv;

		mLocation.vec = _vec;
		mLocation.mat = _mat;
		mLocation.inv = _inv;
	}

	vector_t getActivityVec() {
		return mVecAct;
	}

	matrix_t* getActivityMat() {
		return mMatrixAct;
	}

	invariant getInvariant() {
		return mInvariant;
	}

	location getLocation() {
		return mLocation;
	}

	void setActivityVec(vector_t _vec) {
		mVecAct = _vec;
	}

	void setActivityMat(matrix_t* _mat) {
		mMatrixAct = _mat;
	}

	void setInvariant(invariant _inv) {
		mInvariant = _inv;
	}

	void setLocation(location _loc) {
		mLocation = _loc;
	}

	bool checkInvariant(valuation_t _val) {
		//TODO
		//return mMatrixInv * _val <mOperatorInv> mVectorInv
	}

}
