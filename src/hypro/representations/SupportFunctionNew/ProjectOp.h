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
	std::size_t mDimension = 0;

	////// Members for this class

	std::vector<std::size_t> dimensions;		//Vector of all indices that should not be projected to 0

  public: 

  	////// Constructors & Destructors

  	ProjectOp() = delete;

  	ProjectOp(const SupportFunctionNewT<Number,Converter,Setting>& origin, const std::vector<std::size_t>& dims) : mDimension(origin.dimension()), dimensions(dims) { 
  		origin.addOperation(this); 
  	}

  	~ProjectOp(){}

  	////// Getters & Setters

	SFNEW_TYPE getType() const { return type; }
	unsigned getOriginCount() const { return originCount; }
	std::size_t getDimension() const { return mDimension; }
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

	//Set all unwanted dimensions to zero 
	Point<Number> supremumPoint(std::vector<Point<Number>>& points) const {
		assert(points.size() == 1);
		vector_t<Number> tmp = vector_t<Number>::Zero(points.front().dimension());
		for(const auto& entry : dimensions){
			if(entry < points.front().dimension()) {
				tmp(entry) = points.front().at(entry);
			}
		}
		return Point<Number>(tmp);
	}

	//TODO: if wildcard values in vectors avaiable, then implement smth correct here
	vector_t<Number> reverseOp(const vector_t<Number>& point) const { 
		return point;
	} 

	//If child contains p, then projected version will contain it too
	bool contains(const std::vector<bool>& v) const {
		assert(v.size() == 1);
		if(v.front()) return true;
		return false;
	}

};

} //namespace hypro