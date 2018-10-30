/*#pragma once

#include "RootGrowTree.h"
#include "Leaf.h"
#include "SumOp.h"
#include "TrafoOp.h"

namespace hypro {

//Forward declaration
//template<typename Number>
//class TrafoOp;	

template<typename Number>
class SupportFunctionContentNew : public RootGrowTree<Number> {

  public: 

  	////// Constructors & Destructors

  	SupportFunctionContentNew(){}
  	SupportFunctionContentNew(RootGrowNode<Number>* r) : RootGrowTree<Number>(r) { }
  	~SupportFunctionContentNew(){}

  	////// Needed for GeometricObject Interface

  	//Directly multievaluate from mRoot as the starting point, given the directions to evaluate
  	std::vector<EvaluationResult<Number>> evaluate(const matrix_t<Number>& directions);

  	//Answers whether the tree has TrafoOps with the given parameters inside and updates ltParam if needed
  	bool hasTrafo(std::shared_ptr<const LinTrafoParameters<Number>>& ltParam, const matrix_t<Number>& A, const vector_t<Number>& b);


};


} //namespace hypro

#include "SupportFunctionContentNew.tpp"
*/