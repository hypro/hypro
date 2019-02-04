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

#include "../../types.h"

namespace hypro {

//struct RGNData;
template<typename Number, typename Converter, typename Setting>
class RootGrowNode;

//A data struct for leaves, containing all needed info to construct a leaf from it
//The infos are the address to the representation as an actual number and the type of the representation.
struct LeafData : public RGNData {
	uintptr_t addressToRep;
	representation_name typeOfRep;
	bool isNotRedundant;
	LeafData(){};
	LeafData(const uintptr_t addr, const representation_name rep, const bool redundancy) 
		: addressToRep(addr), typeOfRep(rep), isNotRedundant(redundancy)
	{ }
};

//Subclass of RootGrowNode, is a node with a representation of a state
template<typename Number, typename Converter, typename Setting, typename Representation> 
class Leaf : public RootGrowNode<Number,Converter,Setting> {
  
  private:
	
	////// General Interface

	SFNEW_TYPE type = SFNEW_TYPE::LEAF;
	unsigned originCount = 0;				//A leaf cannot have children
	std::size_t mDimension = 0;

	////// Members for this class

	Representation* rep;
	mutable bool isNotRedundant = false; 	//A flag that tells us if removeRedundancy() has been used on the representation
	
  public:

	////// Constructors & Destructors

	Leaf() : mDimension(std::size_t(0)), rep(nullptr) {}

	Leaf(Representation* r) : mDimension(r->dimension()), rep(r) {}

	Leaf(const LeafData& d){
		assert(Representation::type() == d.typeOfRep);
		rep = reinterpret_cast<Representation*>(d.addressToRep);
		assert(rep != nullptr);
		mDimension = rep->dimension();
		isNotRedundant = d.isNotRedundant;
	}

	~Leaf(){} 

	////// Getters & Setters

	SFNEW_TYPE getType() const { return type; }
	unsigned getOriginCount() const { return originCount; }
	std::size_t getDimension() const { return mDimension; }
	Representation* getRepresentation() const { return rep; }
	bool isRedundant() const { return !isNotRedundant; }
	RGNData* getData() const { return nullptr; }
	LeafData getLeafData() const {
		return LeafData(reinterpret_cast<uintptr_t>(rep), rep->type(), isNotRedundant);
	}
	void setDimension(const std::size_t d) { mDimension = d; }
	
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
