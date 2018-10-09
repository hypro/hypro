#pragma once

#include "RootGrowTree.h"

namespace hypro {

template<typename Number>
class SupportFunctionContentNew : public RootGrowTree<Number> {

  public: 

  	////// Constructors & Destructors

  	SupportFunctionContentNew(){}
  	SupportFunctionContentNew(RootGrowNode<Number>* r) : RootGrowTree<Number>(r) { }
  	~SupportFunctionContentNew(){}

  	////// Needed for GeometricObject Interface

  	std::vector<EvaluationResult<Number>> evaluate(const matrix_t<Number>& directions);

};


} //namespace hypro

#include "SupportFunctionContentNew.tpp"