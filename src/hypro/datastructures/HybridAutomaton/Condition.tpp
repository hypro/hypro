#include "Condition.h"

namespace hypro {

template<typename Number>
template<typename Representation>
std::pair<bool,State<Number,Representation>> Condition<Number>::isSatisfiedBy(const State<Number,Representation>& inState) const {
#ifdef HYDRA_USE_LOGGING
	DEBUG("hydra.datastructures","Checking condition.");
	DEBUG("hydra.datastructures","State: " << inState);
	DEBUG("hydra.datastructures","Continuous constraint matrix: " << mat << " and continuous constraint vector: " << vec);
#endif

	// TODO: Overthink order here - it would be nice to test clocks first, then discrete assignments and continuous sets last.

	std::pair<bool,State<Number,Representation>> res = this->continuousIsSatisfiedBy(inState);

	if(hasDiscreteConstraints && res.first) {
		res = res.discreteIsSatisfiedBy(inState);
	}

	if(hasClockConstraints && res.first) {
		res = res.clockIsSatisfiedBy(inState);
	}
	//DEBUG("hydra.datastructures","Condition is satisfied: " << !empty);
	return res;
}

template<typename Number>
template<typename Representation>
std::pair<bool,State<Number,Representation>> Condition<Number>::continuousIsSatisfiedBy(const State<Number,Representation>& inState) const {
	if(mat.rows() == 0) {
		assert(vec.rows() == 0);
		return std::make_pair(true,inState);
	}
	State<Number,Representation> res(inState);

	bool empty = true;
	//TRACE("hydra.datastructures","Check continuous condition, mat: " << mat << " and vector " << vec << " of state " << inState);
	std::pair<bool, Representation> contSet = res.getSet().satisfiesHalfspaces(mat,vec);
	if(contSet.first) {
		//TRACE("hydra.datastructures","Not empty, resulting set: ");
		empty = false;
		res.setSet(contSet.second);
		//TRACE("hydra.datastructures",res);
	}
	return std::make_pair(!empty,res);
}

template<typename Number>
template<typename Representation>
std::pair<bool,State<Number,Representation>> Condition<Number>::discreteIsSatisfiedBy(const State<Number,Representation>& inState) const {
	if(!hasDiscreteConstraints) {
		return std::make_pair(true,inState);
	}
	State<Number,Representation> res(inState);
	bool empty = true;
	//TRACE("hydra.datastructures","Check discrete condition.");
	std::pair<bool, typename State<Number,Representation>::discreteSetRepresentation> discSet = res.getDiscreteAssignment().satisfiesHalfspaces(discreteMat,discreteVec);
	if(discSet.first) {
		//TRACE("hydra.datastructures","Not empty.");
		res.setDiscreteAssignment(discSet.second);
		empty = false;
	}
	return std::make_pair(!empty,res);
}

template<typename Number>
template<typename Representation>
std::pair<bool,State<Number,Representation>> Condition<Number>::clockIsSatisfiedBy(const State<Number,Representation>& inState) const {
	if(!hasClockConstraints) {
		return std::make_pair(true,inState);
	}
	State<Number,Representation> res(inState);
	bool empty = true;
	//TRACE("hydra.datastructures","Check clock condition.");
	std::pair<bool, typename State<Number,Representation>::clockSetRepresentation> clkSet = res.getClockAssignment().satisfiesHalfspaces(clockMat,clockVec);
	if(clkSet.first) {
		//TRACE("hydra.datastructures","Not empty.");
		res.setClockAssignment(clkSet.second);
		empty = false;
	}
	return std::make_pair(!empty,res);
}


} // namespace
