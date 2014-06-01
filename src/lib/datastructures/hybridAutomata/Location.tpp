#include "Location.h"

namespace hypro {

	template<typename Number>
	Location<Number>::Location(const Location& _loc) : mLocation(_loc.mLocation){
	}

	template<typename Number>
	Location<Number>::Location(const hypro::matrix_t<Number>* _mat, const hypro::vector_t<Number> _vec, const transitionSet _trans, const struct invariant _inv){
		mMatrixAct = _mat;
		mVecAct = _vec;
		mInvariant = _inv;
		mTransitions = _trans;

		mLocation.vec = _vec;
		mLocation.mat = _mat;
		mLocation.inv = _inv;
		mLocation.trans = _trans;
	}

	template<typename Number>
	hypro::vector_t<Number> Location<Number>::activityVec() {
		return mVecAct;
	}

	template<typename Number>
	hypro::matrix_t<Number>* Location<Number>::activityMat() {
		return mMatrixAct;
	}

	template<typename Number>
	struct Location<Number>::invariant Location<Number>::invariant() {
		return mInvariant;
	}

	template<typename Number>
	struct Location<Number>::location Location<Number>::location() {
		return mLocation;
	}

	template<typename Number>
	std::set<Transition<Number>*> Location<Number>::transitions() {
		return mTransitions;
	}

	template<typename Number>
	void Location<Number>::setActivityVec(hypro::vector_t<Number> _vec) {
		mVecAct = _vec;
	}

	template<typename Number>
	void Location<Number>::setActivityMat(hypro::matrix_t<Number>* _mat) {
		mMatrixAct = _mat;
	}

	template<typename Number>
	void Location<Number>::setInvariant(struct invariant _inv) {
		mInvariant = _inv;
	}

	template<typename Number>
	void Location<Number>::setInvariant(hypro::matrix_t<Number>* _mat, hypro::vector_t<Number> _vec, hypro::operator_e _op) {
		mInvariant.vec = _vec;
		mInvariant.mat = _mat;
		mInvariant.op = _op;

		mLocation.inv.op = mInvariant.op;
	}

	template<typename Number>
	void Location<Number>::setLocation(struct location _loc) {
		mLocation = _loc;
	}

	template<typename Number>
	void Location<Number>::setTransitions(transitionSet _trans) {
		mTransitions = _trans;
	}

	/*
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

	*/

}
