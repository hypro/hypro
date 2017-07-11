#include "Condition.h"

namespace hypro {

template<typename Number>
std::pair<bool,State<Number>> Condition<Number>::isSatisfiedBy(const State& inState) const {
	State<Number> res(inState);

#ifdef HYDRA_USE_LOGGING
	DEBUG("hydra.datastructures","Checking condition.");
	DEBUG("hydra.datastructures","State: " << inState);
	DEBUG("hydra.datastructures","Continuous constraint matrix: " << mat << " and continuous constraint vector: " << vec);
#endif

	bool empty = true;
	if(mat.rows() == 0) {
		assert(vec.rows() == 0);
		empty = false;
	} else {
		std::pair<bool, RepresentationVariant> contSet = boost::apply_visitor(genericSatisfiesHalfspacesVisitor<RepresentationVariant, Number>(mat,vec), res.getSet());
		if(contSet.first) {
			//TRACE("hydra.datastructures","Continuous condition satisfied.");
			empty = false;
			res.setSet(contSet.second);
			//TRACE("hydra.datastructures","Resulting set after continuous intersection: " << res);
		} else {
			//TRACE("hydra.datastructures","Continuous condition fails.");
		}
	}

	if(hasDiscreteConstraints && !empty) {
		//TRACE("hydra.datastructures","Check discrete condition.");
		std::pair<bool, RepresentationVariant> discSet = boost::apply_visitor(genericSatisfiesHalfspacesVisitor<RepresentationVariant, Number>(discreteMat,discreteVec), res.getDiscreteAssignment());
		if(discSet.first) {
			//TRACE("hydra.datastructures","Discrete condition satisfied.");
			res.setDiscreteAssignment(discSet.second);
			empty = false;
		} else {
			//TRACE("hydra.datastructures","Discrete condition fails.");
			empty = true;
		}
	}
	if(hasClockConstraints && !empty) {
		//TRACE("hydra.datastructures","Check clock condition.");
		std::pair<bool, RepresentationVariant> clkSet = boost::apply_visitor(genericSatisfiesHalfspacesVisitor<RepresentationVariant, Number>(clockMat,clockVec), res.getClockAssignment());
		if(clkSet.first) {
			//TRACE("hydra.datastructures","Clock condition satisfied.");
			res.setClockAssignment(clkSet.second);
			empty = false;
		} else {
			//TRACE("hydra.datastructures","Clock condition fails.");
			empty = true;
		}
	}
	//DEBUG("hydra.datastructures","Condition is satisfied: " << !empty);
	return std::make_pair(!empty,res);
}

template<typename Number>
std::pair<bool,State<Number>> Condition<Number>::continuousIsSatisfiedBy(const State<Number>& inState) const {
	if(mat.rows() == 0) {
		assert(vec.rows() == 0);
		return std::make_pair(true,inState);
	}
	State<Number> res(inState);

	bool empty = true;
	//TRACE("hydra.datastructures","Check continuous condition, mat: " << mat << " and vector " << vec << " of state " << inState);
	std::pair<bool, RepresentationVariant> contSet = boost::apply_visitor(genericSatisfiesHalfspacesVisitor<RepresentationVariant, Number>(mat,vec), res.getSet());
	if(contSet.first) {
		//TRACE("hydra.datastructures","Not empty, resulting set: ");
		empty = false;
		res.setSet(contSet.second);
		//TRACE("hydra.datastructures",res);
	}
	return std::make_pair(!empty,res);
}

template<typename Number>
std::pair<bool,State<Number>> Condition<Number>::discreteIsSatisfiedBy(const State<Number>& inState) const {
	if(!hasDiscreteConstraints) {
		return std::make_pair(true,inState);
	}
	State<Number> res(inState);
	bool empty = true;
	//TRACE("hydra.datastructures","Check discrete condition.");
	std::pair<bool, RepresentationVariant> discSet = boost::apply_visitor(genericSatisfiesHalfspacesVisitor<RepresentationVariant, Number>(discreteMat,discreteVec), res.getDiscreteAssignment());
	if(discSet.first) {
		//TRACE("hydra.datastructures","Not empty.");
		res.setDiscreteAssignment(discSet.second);
		empty = false;
	}
	return std::make_pair(!empty,res);
}

template<typename Number>
std::pair<bool,State<Number>> Condition<Number>::clockIsSatisfiedBy(const State<Number>& inState) const {
	if(!hasClockConstraints) {
		return std::make_pair(true,inState);
	}
	State<Number> res(inState);
	bool empty = true;
	//TRACE("hydra.datastructures","Check clock condition.");
	std::pair<bool, RepresentationVariant> clkSet = boost::apply_visitor(genericSatisfiesHalfspacesVisitor<RepresentationVariant, Number>(clockMat,clockVec), res.getClockAssignment());
	if(clkSet.first) {
		//TRACE("hydra.datastructures","Not empty.");
		res.setClockAssignment(clkSet.second);
		empty = false;
	}
	return std::make_pair(!empty,res);
}


} // namespace
