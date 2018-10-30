#pragma once

#include "RootGrowNode.h"
#include "SupportFunctionNew.h"

namespace hypro {

//Forward Declaration
template<typename Number, typename Converter, typename Setting>
class SupportFunctionNewT;	

//Specialized subclass for sums as example of a binary operator
template<typename Number, typename Converter, typename Setting>
class SumOp : public RootGrowNode<Number> {
private:
	
	////// General Interface

	SFNEW_TYPE type = SFNEW_TYPE::SUMOP;
	unsigned originCount = 2;
	std::vector<RootGrowNode<Number>*> mChildren = std::vector<RootGrowNode<Number>*>(2,nullptr);

	////// Special members of this class

public:

	////// Constructors & Destructors

	SumOp() = delete;
	SumOp(SupportFunctionNewT<Number,Converter,Setting>* lhs, SupportFunctionNewT<Number,Converter,Setting>* rhs){ lhs->addBinaryOp(this, rhs); }
	//SumOp(SupportFunctionNewT<Number,Converter,Setting>* lhs, SupportFunctionNewT<Number,Converter,Setting>* rhs){ 
	//	RootGrowNode<Number>* lhsRootPtr = mRoot;
	//	RootGrowNode<Number>* rhsRootPtr = rhs->getRoot();
	//	binary->addToChildren(lhsRootPtr);
	//	binary->addToChildren(rhsRootPtr);
	//	lhsRootPtr->setAsParent(binary);
	//	rhsRootPtr->setAsParent(binary);
	//	lhs->addBinaryOp(this, rhs); 
	//}
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
	std::vector<EvaluationResult<Number>> compute(const matrix_t<Number>& ) const { 
		std::cout << "USED COMPUTE FROM SUMOP SUBCLASS.\n"; 
		assert(false); 
		return std::vector<EvaluationResult<Number>>();
	}

	//Given two result vecs, sum them coefficientwise
	std::vector<EvaluationResult<Number>> aggregate(std::vector<std::vector<EvaluationResult<Number>>>& resultStackBack, const matrix_t<Number>& currentParam) const {
		assert(resultStackBack.size() == 2);
		assert(resultStackBack.at(0).size() == resultStackBack.at(1).size());
		assert(resultStackBack.at(0).size() == std::size_t(currentParam.rows()));

		std::vector<EvaluationResult<Number>>& resA = resultStackBack.at(0);
		std::vector<EvaluationResult<Number>>& resB = resultStackBack.at(1);
		std::vector<EvaluationResult<Number>> accumulatedResult;

		// only process if both are feasible. If one result is infeasible, the others will be too, so stop processing.
		if(resA.begin()->errorCode != SOLUTION::INFEAS && resB.begin()->errorCode != SOLUTION::INFEAS) {
			for(unsigned index = 0; index < resA.size(); ++index){
				assert(resA.at(index).errorCode != SOLUTION::INFEAS && resB.at(index).errorCode != SOLUTION::INFEAS);
				EvaluationResult<Number> r;
				if(resA[index].errorCode == SOLUTION::INFTY || resB[index].errorCode == SOLUTION::INFTY){
					r.errorCode = SOLUTION::INFTY;
					r.supportValue = 1;
				} else {
					r.errorCode = SOLUTION::FEAS;
					r.supportValue = resA[index].supportValue + resB[index].supportValue;
					r.optimumValue = resA[index].optimumValue + resB[index].optimumValue;
				}
				accumulatedResult.emplace_back(r);
			}
		}
		//for(auto& e : accumulatedResult){
		//	std::cout << e << std::endl;
		//}
		return accumulatedResult;
	}

	//Should not be called
	bool hasTrafo(std::shared_ptr<const LinTrafoParameters<Number>>& , const matrix_t<Number>& , const vector_t<Number>& ){
		assert(false && "SumOp::hasTrafo should never be called\n");
		return false;
	}
};

} //namespace hypro