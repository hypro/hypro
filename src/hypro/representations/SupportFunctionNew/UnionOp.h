/*
 * UnionOp.h
 *
 * A RootGrowNode that represents a Union operation in the tree of operations representing a SupportFunction.
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
class UnionOp : public RootGrowNode<Number,Setting> {

	using PointerVec = typename RootGrowNode<Number,Setting>::PointerVec;
  
  private:
	
	////// General Interface

	SFNEW_TYPE type = SFNEW_TYPE::UNIONOP;
	unsigned originCount = 2;
	PointerVec mChildren;

	////// Special members of this class

  public:

	////// Constructors & Destructors

	UnionOp() = delete;

	UnionOp(const SupportFunctionNewT<Number,Converter,Setting>& lhs, const SupportFunctionNewT<Number,Converter,Setting>& rhs){ 
		lhs.addOperation(this, std::vector<SupportFunctionNewT<Number,Converter,Setting>>{rhs}); 
	}

	UnionOp(const SupportFunctionNewT<Number,Converter,Setting>& lhs, const std::vector<SupportFunctionNewT<Number,Converter,Setting>>& rhs){ 
		lhs.addOperation(this, rhs); 
	}	

	~UnionOp(){}

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
		std::cout << "USED COMPUTE FROM UnionOp SUBCLASS.\n"; 
		assert(false); 
		return std::vector<EvaluationResult<Number>>();
	}

	//Given two or more result vecs, sum them coefficientwise
	std::vector<EvaluationResult<Number>> aggregate(std::vector<std::vector<EvaluationResult<Number>>>& resultStackBack, const matrix_t<Number>& ) const {
		TRACE("hypro.representations.supportFunction", ": UNITE, accumulate results.")
		assert(resultStackBack.size() >= 2);
		std::vector<EvaluationResult<Number>> accumulatedResult = resultStackBack.front();
		for(auto resIt = resultStackBack.begin(); resIt != resultStackBack.end(); ++resIt) {
			for( unsigned resultId = 0; resultId < accumulatedResult.size(); ++resultId ) {
				if((*resIt)[resultId].errorCode == SOLUTION::INFEAS) {
					accumulatedResult[resultId] = (*resIt)[resultId];
					break;
				} else if((*resIt)[resultId].errorCode == SOLUTION::INFTY) {
					(*resIt)[resultId].supportValue = 1;
					accumulatedResult[resultId] = (*resIt)[resultId];
				} else {
					assert((*resIt)[resultId].errorCode == SOLUTION::FEAS);
					accumulatedResult[resultId] = (*resIt)[resultId] > accumulatedResult[resultId] ? (*resIt)[resultId] : accumulatedResult[resultId];
					//assert(accumulatedResult[resultId].errorCode == SOLUTION::FEAS);
				}
			}
		}
		return accumulatedResult;
	}

	//Transform the supremum
	Point<Number> supremumPoint(std::vector<Point<Number>>& points) const {
		assert(points.size() > 0);
		Point<Number> biggestInftyNorm = points.front();
		for(const auto& p : points){
			if(p.dimension() == 0) return p;
			biggestInftyNorm = Point<Number>::inftyNorm(biggestInftyNorm) > Point<Number>::inftyNorm(p) ? biggestInftyNorm : p;
		}
		return biggestInftyNorm;
	}
};

} //namespace hypro