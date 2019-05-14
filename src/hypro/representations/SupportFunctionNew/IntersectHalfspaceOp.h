/*
 * IntersectHalfspaceOp.h
 *
 * A RootGrowNode that represents an intersection with a halfspace operation in the tree of operations representing a SupportFunction.
 *
 * @author Stefan Schupp
 * @author Phillip Tse
 * @date 8.5.2019
 */
/*
#pragma once

#include "RootGrowNode.h"

namespace hypro {

//Forward Declaration
template<typename Number, typename Converter, typename Setting>
class SupportFunctionNewT;	

//A data struct for IntersectHalfspaceOp, containing all needed info to construct a IntersectHalfspaceOp from it. No child info is saved.
template<typename Number>
struct IntersectHalfspaceData : public RGNData {
	Halfspace<Number> hspace;
	IntersectHalfspaceData(const Halfspace<Number>& h) : hspace(h) {}
};

template<typename Number, typename Converter, typename Setting>
class IntersectHalfspaceOp : public RootGrowNode<Number,Converter,Setting> {

  private:

  	////// Usings

	using PointerVec = typename RootGrowNode<Number,Converter,Setting>::PointerVec;

	////// General Interface

	SFNEW_TYPE type = SFNEW_TYPE::INTERSECTHSPACEOP;
	unsigned originCount;
	PointerVec mChildren;
	std::size_t mDimension;
	

	////// Members for this class

	Halfspace<Number> hspace;

  public: 

  	////// Constructors & Destructors

  	IntersectHalfspaceOp() = delete;

  	IntersectHalfspaceOp(const SupportFunctionNewT<Number,Converter,Setting>& origin, const Halfspace<Number>& h) 
  		: originCount(1)
  		, mChildren(PointerVec(1,nullptr))
  		, mDimension(origin.dimension())
  		, hspace(h) 
  	{ 
  		origin.addOperation(this); 
  	}

  	IntersectHalfspaceOp(const IntersectHalfspaceData<Number>& d) 
  		: originCount(1)
  		, mChildren(PointerVec({1,nullptr}))
  		//, mDimension(d.origin->getDimension())
  		, hspace(d.hspace)
  	{}

  	~IntersectHalfspaceOp(){}

  	////// Getters & Setters

	SFNEW_TYPE getType() const { return type; }
	unsigned getOriginCount() const { return originCount; }
	std::size_t getDimension() const { return mDimension; }
	Number getFactor() const { return factor; }
	RGNData* getData() const { return new IntersectHalfspaceData<Number>(factor); }
	void setDimension(const std::size_t d) { mDimension = d; }

	SupportFunctionNewT<Number,Converter,Setting> addHalfspaceToSF(SupportFunctionNewT<Number,Converter,Setting>& sf){

	}

	////// RootGrowNode Interface

	//does nothing
	matrix_t<Number> transform(const matrix_t<Number>& param) const {
		return param;
	}

	//should not be reachable
	std::vector<EvaluationResult<Number>> compute(const matrix_t<Number>& , bool ) const { 
		assert(false && "IntersectHalfspaceOp::compute should not be called"); 
		return std::vector<EvaluationResult<Number>>();
	}

	//Given evaluation results, 
	std::vector<EvaluationResult<Number>> aggregate(std::vector<std::vector<EvaluationResult<Number>>>& resultStackBack, const matrix_t<Number>& currentParam) const {
		TRACE("hypro.representations.supportFunction", ": INTERSECTHSPACEOP, accumulate results.")
		assert(resultStackBack.size() == 1);
		assert(resultStackBack.front().begin()->errorCode != SOLUTION::INFTY);
		if(resultStackBack.front().begin()->errorCode == SOLUTION::FEAS){
			if(hspace.contains(resultStackBack.front().begin()->optimumValue)){
				//Hspace does not cut off the optimumValue, so it stays the optimumValue
				return resultStackBack.front();
			} else {
				//TODO: This is expensive af - do it somehow else
				//Get matrix representation of child, add halfspace to it
				auto child = SupportFunctionNewT<Number,Converter,Setting>(this->getChildren().front());
				if(!child.isTemplateSet()){
					child.reduceRepresentation();
				}
				matrix_t<Number> childConstraints(child.matrix());
				childConstraints.conservativeResize(childConstraints.rows()+1, childConstraints.cols());
				childConstraints.row(childConstraints.rows()-1) = hspace.normal();
				vector_t<Number> childConstants(child.vector());
				childConstants.conservativeResize(childConstants.rows()+1);
				childConstants(childConstants.rows()-1) = hspace.offset();

				//Evaluate all this in subtree
				SupportFunctionNewT<Number,Converter,Setting> childExtended(childConstraints, childConstants);
				return childExtended->multiEvaluate(currentParam);
			}
		} 
		// if one result is infeasible, the others will be too -> do not process.
		return resultStackBack.front();
	}

	//Checks emptiness
	bool empty(const std::vector<bool>& childrenEmpty) const {
		assert(resultStackBack.size() == 1);
		if(childrenEmpty.front()) return true;
		SupportFunctionNewT<Number,Converter,Setting> child(this->getChildren().front());
		Number childPosEvalValue = child->evaluate(hspace.normal(), true).supportValue;
		Number childNegEvalValue = -1*child->evaluate(-hspace.normal(), true).supportValue;
		if(childNegEvalValue <= hspace.offset() && hspace.offset() <= childPosEvalValue){
			return false;
		}
		return true;
	}

	//Determine supremum given supremum for child and halfspace to intersect with
	Point<Number> supremumPoint(std::vector<Point<Number>>& points) const {
		assert(points.size() == 1);
		if(hspace.contains(points.front())){
			return points.front();
		} else {
			SupportFunctionNewT<Number,Converter,Setting> child(this->getChildren().front());
			if(!child.isTemplateSet()){
				child.reduceRepresentation();
			}

		}
	}

	//Parameters are backtransformed into the domain space of the given operation - do nothing since point has not been modified
	vector_t<Number> reverseOp(const vector_t<Number>& point) const { 
		return point;
	} 

	//If child does not contain p, then intersection will also not contain it, else check if p also lies within halfspace
	bool contains(const std::vector<bool>& v, const vector_t<Number>& point) const {
		assert(v.size() == 1);
		if(!v.front()) return false;
		return hspace.contains(point);
	}
};


} //namespace hypro
*/