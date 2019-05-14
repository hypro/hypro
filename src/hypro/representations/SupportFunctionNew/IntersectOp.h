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
#include "../../datastructures/Halfspace.h"

namespace hypro {

//Forward Declaration
template<typename Number, typename Converter, typename Setting>
class SupportFunctionNewT;	

//Specialized subclass for sums as example of a binary operator
template<typename Number, typename Converter, typename Setting>
class IntersectOp : public RootGrowNode<Number,Converter,Setting> {

  private:
	
	////// General Interface

	SFNEW_TYPE type = SFNEW_TYPE::INTERSECTOP;
	unsigned originCount = 2;
	std::size_t mDimension = 0;
	std::vector<std::shared_ptr<RootGrowNode<Number,Converter,Setting>>> mChildren;

	////// Special members of this class

  public:

	////// Constructors & Destructors

	IntersectOp() = delete;

	//Single sibling constructor
	IntersectOp(const SupportFunctionNewT<Number,Converter,Setting>& lhs, const SupportFunctionNewT<Number,Converter,Setting>& rhs) : mDimension(lhs.dimension()) { 
		assert(lhs.dimension() == rhs.dimension());
		lhs.addOperation(this, std::vector<SupportFunctionNewT<Number,Converter,Setting>>{rhs}); 
	}

	//Multiple siblings constructor
	IntersectOp(const SupportFunctionNewT<Number,Converter,Setting>& lhs, const std::vector<SupportFunctionNewT<Number,Converter,Setting>>& rhs) : mDimension(lhs.dimension()) { 
		#ifndef NDEBUG
		for(const auto& sf : rhs){
			assert(lhs.dimension() == sf.dimension());
		}
		#endif
		lhs.addOperation(this, rhs); 
	}

	//Data constructor
	IntersectOp(const RGNData& ){}

	~IntersectOp(){}

	////// Getters and Setters

	SFNEW_TYPE getType() const override { return type; }
	unsigned getOriginCount() const { return originCount; }
	std::size_t getDimension() const { return mDimension; }
	RGNData* getData() const { return new RGNData(); }
	void setDimension(const std::size_t d) { mDimension = d; }

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

	//Given evaluation result vecs, take the smallest supportValues coefficientwise
	std::vector<EvaluationResult<Number>> aggregate(std::vector<std::vector<EvaluationResult<Number>>>& resultStackBack, const matrix_t<Number>& ) const {
		
		TRACE("hypro.representations.supportFunction", ": INTERSECT, accumulate results.")
		assert(resultStackBack.size() >= 2);
		std::vector<EvaluationResult<Number>> accumulatedResult;

		// in case one of the results is infeasible (the set is empty), return this result.
		//for(const auto& res : resultStackBack){
		//	if(res.begin()->errorCode == SOLUTION::INFEAS){
		//		return res;
		//	}
		//}

		//For all evaluation results in each direction in resultStackBack, iteratively look for the smallest evaluation result
		for ( unsigned i = 0; i < resultStackBack.front().size(); ++i ) {		
			EvaluationResult<Number> r = resultStackBack.front().at(i);
			for(const auto& res : resultStackBack){
				if(res[i].errorCode == SOLUTION::INFEAS) return res;
				//assert(res[i].errorCode != SOLUTION::INFEAS);
				//if(res[i].errorCode == SOLUTION::FEAS){
				//r.errorCode = res[i].errorCode < r.errorCode ? res[i].errorCode : r.errorCode;
				r.supportValue = res[i].supportValue < r.supportValue ? res[i].supportValue : r.supportValue; 
				r.optimumValue = res[i].optimumValue < r.optimumValue ? res[i].optimumValue : r.optimumValue; 		
				//} 
			}
			accumulatedResult.emplace_back(r);
		}
		return accumulatedResult;
	}

  public:

	/* Problem: Check emptiness of intersection of n convex objects
	 * Solution 1: Template Evaluation
	 *	- For each template direction, evaluate every object except one in that direction and the one into the -direction
	 *	- If -direction is bigger in absolute value, then intersection not empty
	 *	- Needs n*t*LP worst time, since every evaluate needs to solve a LP
	 *	- Can stop early if direction directly found -> best time possible time is n*LP
	 *	- Scales bad in dimension
	 * Solution 2: Template Evaluation +
	 *  - Like Solution 1, but parallel evaluation of 2 directions
	 *	- Needs 0.5*n*t*LP time
	 * Solution 3: Center of Gravity (COG)
	 *  - For each object, generate a point within the object
	 *		- Either on a halfspace (needs an LP, how to choose which halfspace?)
	 *		- Or the center of gravity ob the object (needs to compute vertices, then averaging -> expensive as hell)
	 *	- Compute the COG of all points and determine the direction as the vector from the COG to the points
	 *	- Evaluate all directions -> but how to determine emptiness from that?
	 *	- Needs n*LP to generate points and n*LPs for evaluation
	 *
     * All these solutions were not ideal for dealing with halfspaces. Algorithm now (for only 2 objects):
	 * - If both are not halfspaces: Use template evaluation: 2*#dir*LP
	 * - If one is a halfspace and the other not: Use satisfiesHalfspace: 2*LP
	 * - If none are halfspaces: Check linear dependency of halfspace normals: linear
	 */
	bool empty(const std::vector<bool>& childrenEmpty) const {

		//Current implementation uses Solution 1: template evaluation.
		//std::cout << "IntersectOp::empty. Has children: " << this->getChildren().size() << std::endl;

		//Quick check
		for(const auto& child : childrenEmpty){
			if(child){
				//std::cout << "One child was empty" << std::endl;
				return true;
			} 
		}
/*
		assert(this->getChildren().size() == 2);
		SupportFunctionNewT<Number,Converter,Setting> rhs(this->getChildren().at(0));
		SupportFunctionNewT<Number,Converter,Setting> lhs(this->getChildren().at(1));
		std::cout << "rhs matrix: \n" << rhs.matrix() << std::endl << "lhs matrix: \n" << lhs.matrix() << std::endl;
		if(rhs.matrix().rows() > 1 && lhs.matrix().rows() > 1){
			//Both should be closed convex objects - use templateEvaluation
			std::vector<vector_t<Number>> directions = computeTemplate<Number>(this->getDimension(), defaultTemplateDirectionCount);
			for(const auto& direction : directions){
				Number rhsPos = rhs.evaluate(direction, false).supportValue;
				Number lhsNeg = lhs.evaluate(-direction, false).supportValue;
				if(rhsPos < -lhsNeg) return true;
				Number rhsNeg = rhs.evaluate(-direction, false).supportValue;
				Number lhsPos = lhs.evaluate(direction, false).supportValue;
				if(-rhsNeg > lhsPos) return true;
			}
		} else if(rhs.matrix().rows() <= 1 && lhs.matrix().rows() > 1){
			//rhs is a halfspace - empty if lhs does not lie within rhs
			Halfspace<Number> hspace(vector_t<Number>(rhs.matrix().row(0).transpose()), rhs.vector()(0));
			auto lhsInHalfspace = lhs.satisfiesHalfspace(hspace);
			if(lhsInHalfspace.first == CONTAINMENT::NO){
				return true;
			} 
		} else if(rhs.matrix().rows() > 1 && lhs.matrix().rows() <= 1){
			//lhs is a halfspace - empty if rhs does not within lhs
			Halfspace<Number> hspace(vector_t<Number>(lhs.matrix().row(0).transpose()), lhs.vector()(0));
			auto rhsInHalfspace = rhs.satisfiesHalfspace(hspace);
			if(rhsInHalfspace.first == CONTAINMENT::NO){
				return true;
			}
		} else if(rhs.matrix().rows() <= 1 && lhs.matrix().rows() <= 1){
			//Both children are halfspaces - empty if one halfspace points to the exact inverse direction of the other
			std::cout << "We are here" << std::endl;
			vector_t<Number> rhsDir = vector_t<Number>(rhs.matrix().row(0).transpose());
			vector_t<Number> lhsDir = vector_t<Number>(lhs.matrix().row(0).transpose());
			auto bothHalfspacesLinDependent = linearDependent(rhsDir, lhsDir);
			if(bothHalfspacesLinDependent.first && bothHalfspacesLinDependent.second < 0){
				return true;
			}
		} else {
			std::cout << "This was not intended" << std::endl;
		}
		return false;

		//Check which children are halfspaces 

		//Add all their halfspaces to one matrix

		//Compute intersection 
*/
		//std::vector<vector_t<Number>> directions = computeTemplate<Number>(mDimension, defaultTemplateDirectionCount);
		//for(const auto& direction : directions){
		//	for(const auto& child : this->getChildren()){
		//		SupportFunctionNewT<Number,Converter,Setting> sfChild(child);
		//		
		//	}
		//}

		//First: select the most negative object - objects can be unbounded (like halfspaces)
		vector_t<Number> allNegativeDir = -1*vector_t<Number>::Ones(mDimension);
		std::size_t indexOfMostNegativeChild = 0;
		Number mostNegativeEvalValue = Number(100000000);
		std::vector<SupportFunctionNewT<Number,Converter,Setting>> sfChildren;
		//std::cout << "Finding most negative!" << std::endl;
		for(std::size_t i = 0; i < this->getChildren().size(); ++i){
			sfChildren.emplace_back(SupportFunctionNewT<Number,Converter,Setting>(this->getChildren().at(i)));
			EvaluationResult<Number> evalRes = sfChildren.back().evaluate(allNegativeDir,false);
			if(evalRes.errorCode != SOLUTION::INFTY){
				indexOfMostNegativeChild = evalRes.supportValue < mostNegativeEvalValue ? sfChildren.size()-1 : indexOfMostNegativeChild;
				mostNegativeEvalValue = evalRes.supportValue < mostNegativeEvalValue ? evalRes.supportValue : mostNegativeEvalValue;	
			}
			//std::cout << "eval res for allNegativeDir is: " << evalRes << std::endl;;
			//Number childEvalRes = evalRes.supportValue;
			//Number childEvalRes = evalRes.errorCode == SOLUTION::INFTY ? Number(100000000) : evalRes.supportValue;
			//Number childEvalRes = sfChildren.back().evaluate(allNegativeDir,false).supportValue;
			//indexOfMostNegativeChild = childEvalRes < mostNegativeEvalValue ? sfChildren.size()-1 : indexOfMostNegativeChild;
			//mostNegativeEvalValue = childEvalRes < mostNegativeEvalValue ? childEvalRes : mostNegativeEvalValue;	
			//std::cout << "Child " << i << " childEvalRes " << childEvalRes << " indexOfMostNegativeChild " << indexOfMostNegativeChild << " mostNegativeEvalValue " << mostNegativeEvalValue << std::endl;
		}
		assert(indexOfMostNegativeChild < sfChildren.size());

		//Erase most negative child from sfChildren
		SupportFunctionNewT<Number,Converter,Setting> mostNegative = sfChildren.at(indexOfMostNegativeChild);
		sfChildren.erase(sfChildren.begin() + indexOfMostNegativeChild);

		std::vector<vector_t<Number>> directions = computeTemplate<Number>(mDimension, defaultTemplateDirectionCount);

		for(const auto& direction : directions){
			
			//Determine reverse direction for mostNegative
			EvaluationResult<Number> mostNegEvalRes = mostNegative.evaluate(-direction, false);
			//if(mostNegEvalRes.errorCode == SOLUTION::INFTY) return false;
			//Number mostNegEvalRes = mostNegative.evaluate(-direction, false).supportValue;
			//Number mostNegEvalRes = evalRes.supportValue;
			//std::cout << "Current direction: \n" << direction;
			//std::cout << "most negative eval res: " << mostNegEvalRes << std::endl;

			//Fill evalResults
			for(const auto& child : sfChildren){
				EvaluationResult<Number> childEvalRes = child.evaluate(direction, false);
				//if(childEvalRes.errorCode == SOLUTION::INFTY) return false;
				//Number childEvalRes = child.evaluate(direction, false).supportValue;
				//std::cout << "child evaluated to: \n" << cEvalRes << std::endl;
				//cEvalRes.supportValue = cEvalRes.errorCode == SOLUTION::INFTY ? Number(100000000) : cEvalRes.supportValue;
				//Number childEvalRes = cEvalRes.errorCode == SOLUTION::INFTY ? Number(100000000) : cEvalRes.supportValue;
				//Number childEvalRes = cEvalRes.supportValue;
				//std::cout << "child eval suppport value: " << childEvalRes << " < " << -mostNegEvalRes << " ? " << (childEvalRes < -mostNegEvalRes) << " if yes then empty." << std::endl;
				//if(childEvalRes < -mostNegEvalRes) return true;
				if(childEvalRes.supportValue < -mostNegEvalRes.supportValue) return true;
			}
		}
		return false;

		//Brauchen wir die erste hälfte überhaupt?? Muss der negativste ausgesucht werden? 
		//
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

	//Only return true if all children contained the point before	
	bool contains(const std::vector<bool>& v) const {
		for(auto containedInChild : v){
			if(!containedInChild) return false;
		}
		return true;
	}

	//Erases all dimensions from a copy of dimensions that are denoted in dims
	std::vector<std::size_t> intersectDims(const std::vector<std::vector<std::size_t>>& dims) const {
		
		// we create the intersection of all results. Therefore we iterate over the first vector and check the other
		// result vectors, if the respective element is contained. Iterating over the first is sufficient, as elements
		// not in the first vector will not be in the intersection anyways.
		std::vector<std::size_t> accumulatedResult;
		for(unsigned pos = 0; pos < dims.begin()->size(); ++pos){
			std::size_t element = dims.begin()->at(pos);
			bool elementInAllVectors = true;
			for(unsigned resIndex = 1; resIndex < dims.size(); ++resIndex) {
				if(std::find(dims.at(resIndex).begin(), dims.at(resIndex).end(), element) == dims.at(resIndex).end()){
					elementInAllVectors = false;
					break;
				}
			}
			if(elementInAllVectors){
				// if this is a projection, we need to remove non-projected dimensions -> we could not have been in a projection since
				// since this part of the function was only executed if a node had more than 2 children
				accumulatedResult.emplace_back(element);
			}
		}
		return accumulatedResult;
	}

};

} //namespace hypro

