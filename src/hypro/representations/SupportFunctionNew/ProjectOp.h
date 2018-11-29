/*
 * ProjectOp.h
 *
 * A RootGrowNode that represents a projection operation in the tree of operations representing a SupportFunction.
 * Every ProjectOp knows the dimensions that should be kept. 
 *
 * @author Stefan Schupp
 * @author Phillip Tse
 */

#pragma once

#include "RootGrowNode.h"
#include "SupportFunctionNew.h"

namespace hypro {

//Forward Declaration
template<typename Number, typename Converter, typename Setting>
class SupportFunctionNewT;	

template<typename Number, typename Converter, typename Setting>
class ProjectOp : public RootGrowNode<Number,Setting> {

  private:

  	////// Usings

	using PointerVec = typename RootGrowNode<Number,Setting>::PointerVec;

	////// General Interface

	SFNEW_TYPE type = SFNEW_TYPE::PROJECTOP;
	unsigned originCount = 1;
	PointerVec mChildren = PointerVec(1,nullptr);

	////// Members for this class

	std::vector<std::size_t> dimensions;

  public: 

  	////// Constructors & Destructors

  	ProjectOp() = delete;

  	ProjectOp(const SupportFunctionNewT<Number,Converter,Setting>& origin, const std::vector<std::size_t>& dims) : dimensions(dims) { 
  		origin.addOperation(this); 
  	}

  	~ProjectOp(){}

  	////// Getters & Setters

	SFNEW_TYPE getType() const { return type; }
	unsigned getOriginCount() const { return originCount; }
	std::vector<std::size_t> getDimensions() const { return dimensions; }

	////// RootGrowNode Interface

	//Unwantend dimensions are set to 0, keep all other entries in param
	matrix_t<Number> transform(const matrix_t<Number>& param) const {
		matrix_t<Number> projectedParameters = matrix_t<Number>::Zero(param.rows(), param.cols());
		Eigen::Index entryIndex = 0;
		for(const auto& entry : dimensions) {
			TRACE("hypro.representations.supportFunction","Entry: " << entry)
			if(int(entry) < param.cols()){ 
				projectedParameters.col(entry) = param.col(entry);
				++entryIndex;
			}
		}
		assert(std::size_t(entryIndex) == dimensions.size());
		return projectedParameters;
	}

	//should not be reachable
	std::vector<EvaluationResult<Number>> compute(const matrix_t<Number>& , bool ) const { 
		assert(false && "ProjectOp::compute should not be called"); 
		return std::vector<EvaluationResult<Number>>();
	}

	//Given the results, return vector of evaluation results (here only first place needed, since unary op), here, we also modify
	std::vector<EvaluationResult<Number>> aggregate(std::vector<std::vector<EvaluationResult<Number>>>& resultStackBack, const matrix_t<Number>&) const {
		assert(resultStackBack.size() == 1);
		return resultStackBack.front();
	}

	//Is handled in TrafoOp::hasTrafo() and SFNew::hasTrafo()
	bool hasTrafo(std::shared_ptr<const LinTrafoParameters<Number,Setting>>& , const matrix_t<Number>& , const vector_t<Number>& ){
		assert(false && "ProjectOp::hasTrafo should never be called\n");
		return false;
	}

	//Is handled in SFNew::empty()
	bool empty() const { 
		assert(false && "TrafoOp::empty should never be called\n"); 
		return false; 
	}

};

} //namespace hypro