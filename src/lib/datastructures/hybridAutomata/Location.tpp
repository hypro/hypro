#include "Location.h"

namespace hypro {

	template<typename Number>
	Location<Number>::Location(const Location& _loc) : mLocation(_loc.mLocation){
	}

	template<typename Number>
	Location<Number>::Location(const matrix_t* _mat, const vector_t _vec, const invariant_t _inv){
		mMatrixAct = _mat;
		mVecAct = _vec;
		mInvariant = _inv;

		//TODO
		//mLocation.addToMap(mVecAct,mMatrixAct,mInvariant);
	}

	vector_t getActivityVec() {
		return mVecAct;
	}

	matrix_t* getActivityMat() {
		return mMatrixAct;
	}

	invariant_t getInvariant() {
		return mInvariant;
	}

	location_t getLocation() {
		return mLocation;
	}

	void setActivityVec(vector_t _vec) {
		mVecAct = _vec;
	}

	void setActivityMat(matrix_t* _mat) {
		mMatrixAct = _mat;
	}

	void setInvariant(invariant_t _inv) {
		mInvariant = _inv;
	}

	void setLocation(location_t _loc) {
		mLocation = _loc;
	}

	bool checkInvariant(valuation_t _val) {
		//TODO
		//return mMatrixInv * _val <mOperatorInv> mVectorInv
	}

}
