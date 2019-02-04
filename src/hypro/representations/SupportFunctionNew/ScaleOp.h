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

namespace hypro {

//Forward Declaration
template<typename Number, typename Converter, typename Setting>
class SupportFunctionNewT;	

//A data struct for ScaleOp, containing all needed info to construct a ScaleOp from it. No child info is saved.
template<typename Number>
struct ScaleData : public RGNData {
	Number factor;
	ScaleData(const Number& fac) : factor(fac) {}
};

template<typename Number, typename Converter, typename Setting>
class ScaleOp : public RootGrowNode<Number,Converter,Setting> {

  private:

  	////// Usings

	using PointerVec = typename RootGrowNode<Number,Converter,Setting>::PointerVec;

	////// General Interface

	SFNEW_TYPE type = SFNEW_TYPE::SCALEOP;
	unsigned originCount;
	PointerVec mChildren;
	std::size_t mDimension;
	

	////// Members for this class

	Number factor;

  public: 

  	////// Constructors & Destructors

  	ScaleOp() = delete;

  	ScaleOp(const SupportFunctionNewT<Number,Converter,Setting>& origin, const Number& scale) 
  		: originCount(1)
  		, mChildren(PointerVec(1,nullptr))
  		, mDimension(origin.dimension())
  		, factor(scale) 
  	{ 
  		origin.addOperation(this); 
  	}

  	ScaleOp(const ScaleData<Number>& d) 
  		: originCount(1)
  		, mChildren(PointerVec({1,nullptr}))
  		//, mDimension(d.origin->getDimension())
  		, factor(d.factor)
  	{}

  	~ScaleOp(){}

  	////// Getters & Setters

	SFNEW_TYPE getType() const { return type; }
	unsigned getOriginCount() const { return originCount; }
	std::size_t getDimension() const { return mDimension; }
	Number getFactor() const { return factor; }
	RGNData* getData() const { return new ScaleData<Number>(factor); }
	void setDimension(const std::size_t d) { mDimension = d; }

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