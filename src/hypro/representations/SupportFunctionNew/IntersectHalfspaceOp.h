/*
 * IntersectHalfspaceOp.h
 *
 * A RootGrowNode that represents a scaling operation in the tree of operations representing a SupportFunction.
 * Every IntersectHalfspaceOp knows its scaling factor 
 *
 * @author Stefan Schupp
 * @author Phillip Tse
 */

#pragma once

#include "RootGrowNode.h"
#include "../../config.h"

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
	Halfspace<Number> getHalfspace() const { return hspace; }
	RGNData* getData() const { return new IntersectHalfspaceData<Number>(hspace); }
	void setDimension(const std::size_t d) { mDimension = d; }

	////// RootGrowNode Interface

	//does nothing
	matrix_t<Number> transform(const matrix_t<Number>& param) const {
		//std::cout << "INTERSECTHSPACEOP transform" << std::endl;
		return param;
	}

	//should not be reachable
	std::vector<EvaluationResult<Number>> compute(const matrix_t<Number>& , bool ) const { 
		assert(false && "IntersectHalfspaceOp::compute should not be called"); 
		return std::vector<EvaluationResult<Number>>();
	}

	//Method described in LeGuernic's and Girard's paper about support functions
	std::vector<EvaluationResult<Number>> aggregate(std::vector<std::vector<EvaluationResult<Number>>>& resultStackBack, const matrix_t<Number>& directions) const {
		TRACE("hypro.representations.supportFunction", ": INTERSECT HSPACE, accumulate results.")
		//std::cout << "INTERSECTHSPACEOP aggregate" << std::endl;
		assert(resultStackBack.size() == 1);
		std::vector<EvaluationResult<Number>> accumulatedRes;
		for(int i=0; i < directions.rows(); ++i){
			//Optimization: If direction not similar to halfspace normal, then use halfspace evaluate
			if(hspace.normal().dot(directions.row(i)) < 0){
				accumulatedRes.push_back(resolveEvaluationResults(resultStackBack.front().at(i), directions.row(i)));
			} else {
				//std::cout << "evaluation result is: " << evalRes << std::endl;
				accumulatedRes.push_back(leGuernic(vector_t<Number>(directions.row(i).transpose())));	
			}
		}
		return accumulatedRes;
	}

	EvaluationResult<Number> resolveEvaluationResults(const EvaluationResult<Number>& other, const vector_t<Number>& dir) const {
		auto hspaceEval = hspace.evaluate(dir, true);
		std::cout << "other: " << other << " hspaceEval: " << hspaceEval << std::endl;
		if(other.errorCode == SOLUTION::FEAS){
			//Since the first result we compare with can still be infty
			if(hspaceEval.errorCode == SOLUTION::INFTY){
				hspaceEval.errorCode = SOLUTION::FEAS;
				hspaceEval.supportValue = other.supportValue;
				hspaceEval.optimumValue = other.optimumValue;
			} else {
				hspaceEval.errorCode = SOLUTION::FEAS;
				hspaceEval.supportValue = other.supportValue < hspaceEval.supportValue ? other.supportValue : hspaceEval.supportValue; 
				hspaceEval.optimumValue = other.optimumValue < hspaceEval.optimumValue ? other.optimumValue : hspaceEval.optimumValue; 
			}
		}
		return hspaceEval;
	}

	//Computes the support value of the intersection between our child and the member halfspace in direction "direction"
	EvaluationResult<Number> leGuernic(const vector_t<Number>& direction) const {
		//Projection matrix - normalize columns then put them into matrix
		//NOTE: This is the already transposed matrix M^T
		matrix_t<Number> projMat = matrix_t<Number>::Zero(direction.rows(),2);
		projMat.col(0) = hspace.normal().transpose();
		projMat.col(1) = direction.transpose();
		//projMat.col(0) = (hspace.normal() / norm<Number>(hspace.normal())).transpose();
		//projMat.col(1) = (direction.row(i) / norm<Number>(direction.row(i))).transpose(); 
		//std::cout << "make proj mat: \n" << projMat << std::endl;

		//Wiggle vector and wiggle angle
		Number wiggleAngle = 0.0;
		vector_t<Number> wiggleVec = vector_t<Number>::Zero(2);
		wiggleVec(0) = Number(std::cos(carl::toDouble(wiggleAngle)));
		wiggleVec(1) = Number(std::sin(carl::toDouble(wiggleAngle)));
		//std::cout << "initially wiggle vec is: \n" << wiggleVec << std::endl;

		//Golden section search for the value f
		Number maximumAngle = PI_UP;
		Number tolerance = 0.001;
		Number goldenRatio = (std::sqrt(5) + 1) / 2;
		Number upper = maximumAngle - ((maximumAngle - wiggleAngle)/goldenRatio);
		Number lower = wiggleAngle + ((maximumAngle - wiggleAngle)/goldenRatio);
		EvaluationResult<Number> evalInProjectedWiggleDir;
		SupportFunctionNewT<Number,Converter,Setting> childSF(this->getChildren().at(0));
		//std::cout << "childSF is: \n" << childSF << std::endl;
		//std::cout << "is upper = " << upper << " minus lower = " << lower << " bigger than " << tolerance << "?" << std::endl;
		Number absDiff = upper - lower;
		if(absDiff <= 0){
			absDiff *= Number(-1);
		}
		while(absDiff > tolerance){

			//std::cout << "was greater!" << std::endl;
			wiggleVec(0) = Number(std::cos(carl::toDouble(upper)));
			wiggleVec(1) = Number(std::sin(carl::toDouble(upper)));
			//std::cout << "wiggle vec for upper is: \n" << wiggleVec << std::endl;
			vector_t<Number> tmp = projMat*wiggleVec;
			//std::cout << "projMat*wiggleVec = " << tmp << std::endl;
			evalInProjectedWiggleDir = childSF.evaluate(projMat*wiggleVec, true);
			//std::cout << "evalInProjectedWiggleDir for upper is: " << evalInProjectedWiggleDir << "hspace offset: " << hspace.offset() << " cos(upper) = " << std::cos(carl::toDouble(upper)) << " sin(upper) = " << std::sin(carl::toDouble(upper)) << std::endl;
			Number heightOfUpper = (evalInProjectedWiggleDir.supportValue - hspace.offset()*Number(std::cos(carl::toDouble(upper)))) / Number(std::sin(carl::toDouble(upper)));
			
			wiggleVec(0) = Number(std::cos(carl::toDouble(lower)));
			wiggleVec(1) = Number(std::sin(carl::toDouble(lower)));
			//std::cout << "wiggle vec for lower is: \n" << wiggleVec << std::endl;
			tmp = projMat*wiggleVec;
			//std::cout << "projMat*wiggleVec = " << tmp << std::endl;
			evalInProjectedWiggleDir = childSF.evaluate(projMat*wiggleVec, true);
			//std::cout << "evalInProjectedWiggleDir for lower is: " << evalInProjectedWiggleDir << "hspace offset: " << hspace.offset() << " cos(lower) = " << std::cos(carl::toDouble(lower)) << " sin(lower) = " << std::sin(carl::toDouble(lower)) << std::endl;
			Number heightOfLower = (evalInProjectedWiggleDir.supportValue - hspace.offset()*Number(std::cos(carl::toDouble(lower)))) / Number(std::sin(carl::toDouble(lower)));
			
			//std::cout << "heightOfUpper = " << heightOfUpper << " >= heightOfLower = " << heightOfLower << "?" << std::endl;
			if(heightOfLower < heightOfUpper){
				wiggleAngle = upper;
			} else {
				maximumAngle = lower;
			}

			upper = maximumAngle - ((maximumAngle - wiggleAngle)/goldenRatio);
			lower = wiggleAngle + ((maximumAngle - wiggleAngle)/goldenRatio);
			absDiff = upper - lower;
			if(absDiff <= 0){
				absDiff *= Number(-1);
			}

			//std::cout << "upper is now: " << upper << " lower is now: " << lower << std::endl;
		}
		Number resultAngle = (maximumAngle + wiggleAngle) / 2;
		//std::cout << "resultAngle is: " << resultAngle << std::endl;
		assert(0 <= resultAngle && resultAngle <= PI_UP);

		wiggleVec(0) = Number(std::cos(carl::toDouble(resultAngle)));
		wiggleVec(1) = Number(std::sin(carl::toDouble(resultAngle)));
		evalInProjectedWiggleDir = childSF.evaluate(projMat*wiggleVec, true);
		Number heightOfResult = (evalInProjectedWiggleDir.supportValue - hspace.offset()*Number(std::cos(carl::toDouble(resultAngle)))) / Number(std::sin(carl::toDouble(resultAngle)));
		//EvaluationResult<Number> evalRes(heightOfResult, SOLUTION::FEAS);	
		return EvaluationResult<Number>(heightOfResult, SOLUTION::FEAS);	
	}

	//Checks emptiness
	bool empty(const std::vector<bool>& childrenEmpty) const {
		std::cout << "INTERSECTHSPACEOP::empty" << std::endl;
		assert(childrenEmpty.size() == 1);
		if(childrenEmpty.front()) return true;
		SupportFunctionNewT<Number,Converter,Setting> child(this->getChildren().at(0));
		std::cout << "child is: \n" << child << std::endl;
		auto posNormalEval = child.evaluate(hspace.normal(), true);
		auto negNormalEval = child.evaluate(-hspace.normal(), true);
		std::cout << "-negNormalEval " << -negNormalEval.supportValue << " <= offset: " << hspace.offset() << " <= posNormalEval: " << posNormalEval.supportValue << std::endl;
		if(-negNormalEval.supportValue <= hspace.offset() && hspace.offset() <= posNormalEval.supportValue) return false;
		return true;
	}

	//TODO: Needs to be fixed. How to compute supremum point if it was cut off?
	Point<Number> supremumPoint(std::vector<Point<Number>>& points) const {
		assert(points.size() == 1);
		std::cout << "INTERSECTHSPACEOP::supremumPoint" << std::endl;
		if(hspace.contains(points.front())) {
			std::cout << "point contained in halfspace!" << std::endl;
			return points.front();
		}
		//vector_t<Number> supremumDirection = vector_t<Number>::Ones(this->getDimension());
		SupportFunctionNewT<Number,Converter,Setting> child(this->getChildren().at(0));
		std::cout << "child is: \n" << child << std::endl;
		auto childEval = child.evaluate(hspace.normal(), true);
		auto hspaceEval = resolveEvaluationResults(childEval, hspace.normal());
		if(hspaceEval.errorCode == SOLUTION::FEAS) {
			std::cout << "optimum point is: " << hspaceEval << std::endl;
			return Point<Number>(hspaceEval.optimumValue);
		}
		return Point<Number>::Zero(points.front().dimension());

		//vector_t<Number> supremumDirection = vector_t<Number>::Ones(this->getDimension());
		//auto evalRes = leGuernic(supremumDirection);
		//if(evalRes.errorCode == SOLUTION::FEAS) {
		//	std::cout << "optimum point is: " << evalRes << std::endl;
		//	return Point<Number>(evalRes.optimumValue);
		//}
		//return Point<Number>::Zero(points.front().dimension());

		//SupportFunctionNewT<Number,Converter,Setting> child(this->getChildren().at(0));
		//std::cout << "child is: \n" << child << std::endl;
		//auto normalEval = child.evaluate(hspace.normal(), true);
		//if(normalEval.errorCode == SOLUTION::FEAS) {
		//	std::cout << "optimum point is: " << normalEval << std::endl;
		//	return Point<Number>(normalEval.optimumValue);
		//}
		//return Point<Number>::Zero(points.front().dimension());
	}

	vector_t<Number> reverseOp(const vector_t<Number>& point) const { 
		return point;
	} 

	//TODO:: NEEDS THE POINT 
	bool contains(const std::vector<bool>& v) const {
		assert(v.size() == 1);
		if(v.front()) return true;
		return false;
	}
};

} //namespace hypro
