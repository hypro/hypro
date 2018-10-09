#pragma once

#include "RootGrowNode.h"

namespace hypro {

//Subclass of RootGrowNode, is a node with a representation of a state
template<typename Number, typename Representation> 
class Leaf : public RootGrowNode<Number> {
private:
	
	////// General Interface

	SFNEW_TYPE type = SFNEW_TYPE::LEAF;
	unsigned originCount = 0;

	////// Members for this class

	Representation* rep;
	
public:

	Leaf(){}
	Leaf(Representation* r) : rep(r) {}
	~Leaf(){}
	SFNEW_TYPE getType() const { return type; }
	unsigned getOriginCount() const { return originCount; }

	//Leaves usually do not transform
	matrix_t<Number> transform(const matrix_t<Number>&) const {
		std::cout << "calling Leaf::transform\n";
		assert(false); 
		return matrix_t<Number>::Zero(1,1); 
	}

	//Evaluate leaf via multiEvaluate function of the representation
	std::vector<EvaluationResult<Number>> compute(const matrix_t<Number>& param) const { 
		std::cout << "calling Leaf::compute, returns\n" << rep->multiEvaluate(param, true) << std::endl;
		return rep->multiEvaluate(param, true);
	}

	//Leaves do not aggregate
	std::vector<EvaluationResult<Number>> aggregate(std::vector<std::vector<EvaluationResult<Number>>>& , const matrix_t<Number>& ) const {
		std::cout << "calling Leaf::aggregate\n";
		assert(false);
		return std::vector<EvaluationResult<Number>>();
	}

};

} //namespace hypro
