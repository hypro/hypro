/*
 * ScaleOp.h
 *
 * A RootGrowNode that represents a scaling operation in the tree of operations representing a SupportFunction.
 * Every ScaleOp knows its scaling factor 
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
class ScaleOp : public RootGrowNode<Number,Setting> {

  private:

  	////// Usings

	using PointerVec = typename RootGrowNode<Number,Setting>::PointerVec;

	////// General Interface

	SFNEW_TYPE type = SFNEW_TYPE::SCALEOP;
	unsigned originCount = 1;
	PointerVec mChildren = PointerVec(1,nullptr);

	////// Members for this class

	Number factor;

  public: 

  	////// Constructors & Destructors

  	ScaleOp() = delete;

  	ScaleOp(const SupportFunctionNewT<Number,Converter,Setting>& origin, const Number& scale) : factor(scale) { 
  		origin.addUnaryOp(this); 
  	}

  	~ScaleOp(){}

  	////// Getters & Setters

	SFNEW_TYPE getType() const { return type; }
	unsigned getOriginCount() const { return originCount; }
	Number getFactor() const { return factor; }

	////// RootGrowNode Interface

	//does nothing
	matrix_t<Number> transform(const matrix_t<Number>& param) const {
		return param;
	}

	//should not be reachable
	std::vector<EvaluationResult<Number>> compute(const matrix_t<Number>& , bool ) const { 
		assert(false && "ScaleOp::compute should not be called"); 
		return std::vector<EvaluationResult<Number>>();
	}

	//Given the results, return vector of evaluation results (here only first place needed, since unary op), here, we also modify
	std::vector<EvaluationResult<Number>> aggregate(std::vector<std::vector<EvaluationResult<Number>>>& resultStackBack, const matrix_t<Number>&) const {
		TRACE("hypro.representations.supportFunction", ": SCALE, accumulate results.")
		assert(resultStackBack.size() == 1);
		// if one result is infeasible, the others will be too -> do not process.
		if(resultStackBack.front().begin()->errorCode != SOLUTION::INFEAS){
			for(auto& singleRes : resultStackBack.front()){
				assert(singleRes.errorCode != SOLUTION::INFEAS);
				if(singleRes.errorCode == SOLUTION::FEAS){
					singleRes.supportValue *= factor;
					singleRes.optimumValue *= factor;
				}
			}
		}
		return resultStackBack.front();
	}

	//Is handled in TrafoOp::hasTrafo() and SFNew::hasTrafo()
	bool hasTrafo(std::shared_ptr<const LinTrafoParameters<Number,Setting>>& ltParam, const matrix_t<Number>& A, const vector_t<Number>& b){
		assert(false && "ScaleOp::hasTrafo should never be called\n");
		return false;
	}

	//Is handled in SFNew::empty()
	bool empty() const { 
		assert(false && "TrafoOp::empty should never be called\n"); 
		return false; 
	}

};

} //namespace hypro