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
	std::size_t mDimension = 0;
	

	////// Members for this class

	Number factor;

  public: 

  	////// Constructors & Destructors

  	ScaleOp() = delete;

  	ScaleOp(const SupportFunctionNewT<Number,Converter,Setting>& origin, const Number& scale) : mDimension(origin.dimension()), factor(scale) { 
  		origin.addOperation(this); 
  	}

  	~ScaleOp(){}

  	////// Getters & Setters

	SFNEW_TYPE getType() const { return type; }
	unsigned getOriginCount() const { return originCount; }
	std::size_t getDimension() const { return mDimension; }
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

	//Checks emptiness
	bool empty(const std::vector<bool>& childrenEmpty) const {
		assert(childrenEmpty.size() == 1);
		if(childrenEmpty.front()) return true;
		return false;
	}

	//Multiply supremumPoint by factor
	Point<Number> supremumPoint(std::vector<Point<Number>>& points) const {
		assert(points.size() == 1);
		if(factor == 0){
			return Point<Number>::Zero(points.front().dimension());
		} else {
			if(points.front().dimension() == 0) return points.front();
			return factor * points.front();
		}		
	}

	//divide by factor
	vector_t<Number> reverseOp(const vector_t<Number>& point) const { 
		if(factor == 0) return vector_t<Number>::Zero(point.rows());
		return point / factor;
	} 

	//If child contains p, then scaled version will contain it too
	bool contains(const std::vector<bool>& v) const {
		assert(v.size() == 1);
		if(v.front()) return true;
		return false;
	}

};

} //namespace hypro