/*
 * Leaf.h
 *
 * A RootGrowNode that represents a leaf node in the tree of operations representing a SupportFunction.
 * Each tree has a pointer to a Representation: Box, H-Polytope, etc.
 *
 * @author Stefan Schupp
 * @author Phillip Tse
 */

#pragma once

#include "RootGrowNode.h"

namespace hypro {

//Subclass of RootGrowNode, is a node with a representation of a state
template<typename Number, typename Setting, typename Representation> 
class Leaf : public RootGrowNode<Number,Setting> {
  
  private:
	
	////// General Interface

	SFNEW_TYPE type = SFNEW_TYPE::LEAF;
	unsigned originCount = 0;				//A leaf cannot have children

	////// Members for this class

	Representation* rep = nullptr;
	
  public:

	////// Constructors & Destructors

	Leaf(){}

	Leaf(Representation* r) : rep(r) {}//std::cout << "Leaf::Leaf(r)" << std::endl; }

	~Leaf(){} //std::cout << "Leaf::~Leaf" << std::endl; }

	////// Getters & Setters

	SFNEW_TYPE getType() const { return type; }
	unsigned getOriginCount() const { return originCount; }
	Representation* getRepresentation() const { return rep; }
	void setRepresentation(Representation* r){ rep = r; }

	////// RootGrowNode Interface

	//Leaves usually do not transform
	matrix_t<Number> transform(const matrix_t<Number>&) const {
		assert(false && "Leaf::transform should never be called\n"); 
		return matrix_t<Number>::Zero(1,1); 
	}

	//Evaluate leaf via multiEvaluate function of the representation
	std::vector<EvaluationResult<Number>> compute(const matrix_t<Number>& param, bool useExact) const { 
		assert(rep != nullptr);
		return rep->multiEvaluate(param, useExact);
	}

	//Leaves do not aggregate
	std::vector<EvaluationResult<Number>> aggregate(std::vector<std::vector<EvaluationResult<Number>>>& , const matrix_t<Number>& ) const {
		assert(false && "Leaf::aggregate should never be called\n");
		return std::vector<EvaluationResult<Number>>();
	}

	bool hasTrafo(std::shared_ptr<const LinTrafoParameters<Number,Setting>>& , const matrix_t<Number>& , const vector_t<Number>& ){
		assert(false && "Leaf::hasTrafo should never be called\n");
		return false;
	}

	bool empty() const { return rep->empty(); }

};

} //namespace hypro
