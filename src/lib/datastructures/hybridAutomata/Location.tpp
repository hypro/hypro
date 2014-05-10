#include "Location.h"

namespace hypro {

	template<typename Number>
	Location<Number>::Location(const Location& _loc) : mLocation(_loc.mLocation){
	}

	template<typename Number>
	Location<Number>::Location(const hypro::matrix_t* _mat, const hypro::vector_t _vec, const invariant _inv){
		mMatrixAct = _mat;
		mVecAct = _vec;
		mInvariant = _inv;

		mLocation.vec = _vec;
		mLocation.mat = _mat;
		mLocation.inv = _inv;
	}

	hypro::vector_t activityVec() {
		return mVecAct;
	}

	hypro::matrix_t* activityMat() {
		return mMatrixAct;
	}

	invariant invariant() {
		return mInvariant;
	}

	location location() {
		return mLocation;
	}

	void setActivityVec(hypro::vector_t _vec) {
		mVecAct = _vec;
	}

	void setActivityMat(hypro::matrix_t* _mat) {
		mMatrixAct = _mat;
	}

	void setInvariant(invariant _inv) {
		mInvariant = _inv;
	}

	void setLocation(location _loc) {
		mLocation = _loc;
	}

	template<typename Number>
	bool checkInvariant(hypro::valuation_t _val) {
		//return mInvariant.mat * _val mInvariant.op mInvariant.vec
		//shorter? for (auto varIt : _val)

		auto vecIt = mInvariant.vec.begin();

		for (int currentRow=0; currentRow != mInvariant.mat.rows(); ++currentRow) {  //iterate over all matrix rows
			carl::FLOAT_T<Number> upperSum = 0;										// one matrix row * valuation vector = sum
			carl::FLOAT_T<Number> lowerSum = 0;
			int currentColumn = 0;

			for (auto varIt=_val.begin(); varIt !=_val.end(); ++varIt) {		// for each row iterate over all variables
				carl::FLOAT_T<Number> upperBound = varIt->second.upper();       // upper & lower bounds of the valuation interval for one variable
				carl::FLOAT_T<Number> lowerBound = varIt->second.lower();

				upperSum += mInvariant.mat(currentRow,currentColumn) * upperBound;   //add (matrix entry * var valuation) to the sums
				lowerSum += mInvariant.mat(currentRow,currentColumn) * lowerBound;

				currentColumn++; 												//next variable corresponds to next column
			}
			bool tempResult_up = hypro::compare(upperSum,vecIt->second,mInvariant.op); // compare upperSum with the value stored in the vector with respect to the operator
			bool tempResult_low = hypro::compare(lowerSum,vecIt->second,mInvariant.op);  //TODO can the vector contain intervals?

			if (!tempResult_up || !tempResult_low) {return false;}               //return false if a boundary is ever violated TODO possibly add information
		}
		return true;   // a boundary was never violated
	}

	//TODO mehrere Intervalle -> std::pair oder map (evtl. hier nur für eine Var ausrechnen, dann in anderer Fkt. zusammenfassen)
	template<typename Number>
	carl::Interval<FLOAT_T<Number>> computeForwardTimeClosure(hypro::valuation_t _val) {
		//TODO
		//idea: create new valuation set, add _val initially
		//then check invariant for upper bounds for variables -> FUNCTION: rückgabe jeweils ein t für eine var -> min suchen! -> obere grenze des intervals gegeben!
		//compute all reachable valuations up to these bounds (details? script -> solve set of linear constraints)
		//add to set, return set
	}

}
