/*
 * IntersectOp.h
 *
 * A RootGrowNode that represents a intersection operation in the tree of operations representing a SupportFunction.
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
class IntersectOp : public RootGrowNode<Number,Setting> {

	using PointerVec = typename RootGrowNode<Number,Setting>::PointerVec;
  
  private:
	
	////// General Interface

	SFNEW_TYPE type = SFNEW_TYPE::INTERSECTOP;
	unsigned originCount = 2;
	PointerVec mChildren;
	std::size_t mDimension = 0;

	////// Special members of this class

  public:

	////// Constructors & Destructors

	IntersectOp() = delete;

	IntersectOp(const SupportFunctionNewT<Number,Converter,Setting>& lhs, const SupportFunctionNewT<Number,Converter,Setting>& rhs){ 
		assert(lhs.dimension() == rhs.dimension());
		mDimension = lhs.dimension();
		lhs.addOperation(this, std::vector<SupportFunctionNewT<Number,Converter,Setting>>{rhs}); 
	}

	IntersectOp(const SupportFunctionNewT<Number,Converter,Setting>& lhs, const std::vector<SupportFunctionNewT<Number,Converter,Setting>>& rhs){ 
		for(const auto& sf : rhs){
			assert(lhs.dimension() == sf.dimension());
		}
		mDimension = lhs.dimension();
		lhs.addOperation(this, rhs); 
	}

	~IntersectOp(){}

	////// Getters and Setters

	SFNEW_TYPE getType() const override { return type; }
	unsigned getOriginCount() const { return originCount; }
	std::size_t getDimension() const { return mDimension; }

	////// RootGrowNode Interface

	//Does nothing
	matrix_t<Number> transform(const matrix_t<Number>& param) const {
		return param;
	}

	//Should not be reached
	std::vector<EvaluationResult<Number>> compute(const matrix_t<Number>& , bool ) const { 
		assert(false && "IntersectOp::compute should never be called"); 
		return std::vector<EvaluationResult<Number>>();
	}

	//Given two result vecs, sum them coefficientwise
	std::vector<EvaluationResult<Number>> aggregate(std::vector<std::vector<EvaluationResult<Number>>>& resultStackBack, const matrix_t<Number>& ) const {
		
		TRACE("hypro.representations.supportFunction", ": INTERSECT, accumulate results.")
		assert(resultStackBack.size() >= 2);
		std::vector<EvaluationResult<Number>> accumulatedResult;

		// in case one of the results is infeasible (the set is empty), return this result.
		for(const auto& res : resultStackBack){
			if(res.begin()->errorCode == SOLUTION::INFEAS){
				accumulatedResult = res;
				return accumulatedResult;
			}
		}
		
		//For all coordinates of all results in resultStackBack, take the iteratively look for the smallest evaluation result
		for ( unsigned i = 0; i < resultStackBack.at(0).size(); ++i ) {		
			
			//Init r with some large numbers or else the loop doesn't start
			EvaluationResult<Number> r;
			r.errorCode = SOLUTION::FEAS;
			r.supportValue = Number(10000000);
			r.optimumValue = vector_t<Number>::Zero(resultStackBack.at(0).size());
			for(int j = 0; j < r.optimumValue.rows(); ++j){
				r.optimumValue[j] = Number(10000000);
			}

			//actual aggregation loop
			for(const auto& res : resultStackBack){
				assert(res[i].errorCode != SOLUTION::INFEAS);
				std::cout << "res[" << i << "] = " << res[i] << "r = " << r << std::endl;
				if(r.errorCode == SOLUTION::FEAS && res[i].errorCode == SOLUTION::INFTY){
					r.supportValue = res[i].supportValue;
					r.optimumValue = res[i].optimumValue;
				} else {
					if(r.errorCode == SOLUTION::FEAS && res[i].errorCode == SOLUTION::FEAS){
						r.supportValue = res[i].supportValue < r.supportValue ? res[i].supportValue : r.supportValue; 
						r.optimumValue = res[i].optimumValue < r.optimumValue ? res[i].optimumValue : r.optimumValue; 	
					} 
				}
			}
			accumulatedResult.emplace_back(r);
		}
		return accumulatedResult;
	}

	//Select smallest supremum of given suprema
	Point<Number> supremumPoint(std::vector<Point<Number>>& points) const {
		Point<Number> smallestInftyNorm = points.front();
		for(auto& p : points){
			if(p.dimension() == 0) return p;
			smallestInftyNorm = Point<Number>::inftyNorm(smallestInftyNorm) < Point<Number>::inftyNorm(p) ? smallestInftyNorm : p;
		}
		return smallestInftyNorm;
	}
};

} //namespace hypro

