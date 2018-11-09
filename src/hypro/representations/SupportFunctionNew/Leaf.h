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

	Representation* rep = nullptr;
	
  public:

	////// Constructors & Destructors

	Leaf(){ }

	Leaf(Representation* r) : rep(r) { 
		std::cout << "Leaf::Leaf(r)" << std::endl;
	}

	~Leaf(){
		std::cout << "Leaf::~Leaf" << std::endl;
	}

	////// Getters & Setters

	SFNEW_TYPE getType() const { return type; }
	unsigned getOriginCount() const { return originCount; }
	Representation* getRepresentation() const { return rep; }
	void setRepresentation(Representation* r){ rep = r; }

	////// RootGrowNode Interface

	//Leaves usually do not transform
	matrix_t<Number> transform(const matrix_t<Number>&) const {
		std::cout << "calling Leaf::transform\n";
		assert(false); 
		return matrix_t<Number>::Zero(1,1); 
	}

	//Evaluate leaf via multiEvaluate function of the representation
	std::vector<EvaluationResult<Number>> compute(const matrix_t<Number>& param, bool useExact) const { 
		std::cout << "calling Leaf::compute" << std::endl;
		assert(rep != nullptr);
		return rep->multiEvaluate(param, useExact);
	}

	//Leaves do not aggregate
	std::vector<EvaluationResult<Number>> aggregate(std::vector<std::vector<EvaluationResult<Number>>>& , const matrix_t<Number>& ) const {
		std::cout << "calling Leaf::aggregate\n";
		assert(false);
		return std::vector<EvaluationResult<Number>>();
	}

	bool hasTrafo(std::shared_ptr<const LinTrafoParameters<Number>>& , const matrix_t<Number>& , const vector_t<Number>& ){
		assert(false && "Leaf::hasTrafo should never be called\n");
		return false;
	}

};

} //namespace hypro
