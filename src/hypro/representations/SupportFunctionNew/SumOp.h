/*
 * SumOp.h
 *
 * A RootGrowNode that represents a Minkowski Sum operation in the tree of operations representing a SupportFunction.
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

//Specialized subclass for sums as example of a binary operator
template<typename Number, typename Converter, typename Setting>
class SumOp : public RootGrowNode<Number,Setting> {

	using PointerVec = typename RootGrowNode<Number,Setting>::PointerVec;
  
  private:
	
	////// General Interface

	SFNEW_TYPE type = SFNEW_TYPE::SUMOP;
	unsigned originCount = 2;
	PointerVec mChildren;

	////// Special members of this class

  public:

	////// Constructors & Destructors

	SumOp() = delete;

	SumOp(const SupportFunctionNewT<Number,Converter,Setting>& lhs, const SupportFunctionNewT<Number,Converter,Setting>& rhs){ 
		lhs.addOperation(this, std::vector<SupportFunctionNewT<Number,Converter,Setting>>{rhs}); 
	}

	SumOp(const SupportFunctionNewT<Number,Converter,Setting>& lhs, const std::vector<SupportFunctionNewT<Number,Converter,Setting>>& rhs){ 
		lhs.addOperation(this, rhs); 
	}	

	~SumOp(){}

	////// Getters and Setters

	SFNEW_TYPE getType() const override { return type; }
	unsigned getOriginCount() const { return originCount; }

	////// RootGrowNode Interface

	//Does nothing
	matrix_t<Number> transform(const matrix_t<Number>& param) const {
		return param;
	}

	//Should not be reached
	std::vector<EvaluationResult<Number>> compute(const matrix_t<Number>& , bool ) const { 
		std::cout << "USED COMPUTE FROM SUMOP SUBCLASS.\n"; 
		assert(false); 
		return std::vector<EvaluationResult<Number>>();
	}

	//Given two or more result vecs, sum them coefficientwise
	std::vector<EvaluationResult<Number>> aggregate(std::vector<std::vector<EvaluationResult<Number>>>& resultStackBack, const matrix_t<Number>& currentParam) const {
		
		assert(resultStackBack.size() >= 2);
		assert(resultStackBack.at(0).size() == resultStackBack.at(1).size());
		assert(resultStackBack.at(0).size() == std::size_t(currentParam.rows()));

		std::vector<EvaluationResult<Number>> accumulatedResult;

		for(const auto& res : resultStackBack){
			if(res.begin()->errorCode == SOLUTION::INFEAS) return accumulatedResult;
		}

		for(unsigned index = 0; index < resultStackBack.front().size(); ++index){
			EvaluationResult<Number> r;
			r.optimumValue = vector_t<Number>::Zero(resultStackBack.front().front().optimumValue.rows());
			for(const auto& res : resultStackBack){
				assert(res[index].errorCode != SOLUTION::INFEAS);
				if(res[index].errorCode == SOLUTION::INFTY){
					r.errorCode = SOLUTION::INFTY;
					r.supportValue = 1;
					break;
				} else {
					r.errorCode = SOLUTION::FEAS;
					r.supportValue += res[index].supportValue;
					r.optimumValue += res[index].optimumValue;
				}
			}
			accumulatedResult.emplace_back(r);
		}
		return accumulatedResult;
	}

	//Sum all suprema together
	Point<Number> supremumPoint(std::vector<Point<Number>>& points) const {
		Point<Number> res = Point<Number>::Zero(points.front().dimension());
		for(const auto& p : points){
			if(p.dimension() == 0) return p;
			res += p;
		}
		return res;
	}
};

} //namespace hypro