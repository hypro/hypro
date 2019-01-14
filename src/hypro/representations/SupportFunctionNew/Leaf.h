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
	std::size_t mDimension = 0;

	////// Members for this class

	Representation* rep = nullptr;
	mutable bool isNotRedundant = false; 	//A flag that tells us if removeRedundancy() been used on the representation
	
  public:

	////// Constructors & Destructors

	Leaf() : mDimension(std::size_t(0)) {}

	Leaf(Representation* r) : mDimension(r->dimension()), rep(r) {}

	~Leaf(){} 

	////// Getters & Setters

	SFNEW_TYPE getType() const { return type; }
	unsigned getOriginCount() const { return originCount; }
	std::size_t getDimension() const { return mDimension; }
	Representation* getRepresentation() const { return rep; }
	//void setRepresentation(Representation* r){ rep = r; mDimension = r->dimension(); }

	////// RootGrowNode Interface

	//Leaves usually do not transform
	matrix_t<Number> transform(const matrix_t<Number>&) const {
		assert(false && "Leaf::transform should never be called\n"); 
		return matrix_t<Number>::Zero(1,1); 
	}

	//Evaluate leaf via multiEvaluate function of the representation
	std::vector<EvaluationResult<Number>> compute(const matrix_t<Number>& param, bool useExact) const { 
		assert(rep != nullptr);
		//Optimization: Remove redundancy only when rep is being evaluated the first time
		if(!isNotRedundant){
			rep->removeRedundancy();
			isNotRedundant = true;
		}
		return rep->multiEvaluate(param, useExact);
	}

	//Leaves do not aggregate
	std::vector<EvaluationResult<Number>> aggregate(std::vector<std::vector<EvaluationResult<Number>>>& , const matrix_t<Number>& ) const {
		assert(false && "Leaf::aggregate should never be called\n");
		return std::vector<EvaluationResult<Number>>();
	}

	//Leaves call empty function of the representation
	bool empty() const { return rep->empty(); }

	//Compute the point that is the supremum of the representation
	Point<Number> supremumPoint() const { 
		Point<Number> max = Point<Number>::Zero(rep->dimension());
		for(auto& point : rep->vertices()){
			max = Point<Number>::inftyNorm(max) > Point<Number>::inftyNorm(point) ? max : point;
		}
		return max;
	}

	//Calls contains function of given representation
	bool contains(const vector_t<Number>& point) const { return rep->contains(Point<Number>(point)); }

};

} //namespace hypro
