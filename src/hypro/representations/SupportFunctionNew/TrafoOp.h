#pragma once

#include "RootGrowNode.h"

namespace hypro {

//Specialized subclass for transformations as example of a unary operator
template<typename Number>
class TrafoOp : public RootGrowNode<Number> {
private:
	////// General Interface

	SFNEW_TYPE type = SFNEW_TYPE::TRAFO;
	unsigned originCount = 1;

	////// Members for this class

	matrix_t<Number> mat;
	vector_t<Number> vec;

public:
	
	////// Constructors & Destructors

	TrafoOp() {}
	TrafoOp(matrix_t<Number> m, vector_t<Number> v) : mat(m), vec(v) {}
	~TrafoOp(){}

	////// Getters & Setters

	SFNEW_TYPE getType() const { return type; }
	unsigned getOriginCount() const { return originCount; }
	matrix_t<Number> getMatrix() const { return mat; }
	vector_t<Number> getVector() const { return vec; }
	void setMatrix(matrix_t<Number>& m){ mat = m; }
	void setVector(vector_t<Number>& v){ vec = v; }

	//transforms parameters
	matrix_t<Number> transform(const matrix_t<Number>& param) const {
		matrix_t<Number> tmp = param*mat;
		std::cout << "calling TrafoOp::transform, returns:\n" << tmp << std::endl;
		return param * mat;
	}

	//should not be reachable
	std::vector<EvaluationResult<Number>> compute(const matrix_t<Number>& ) const { 
		std::cout << "USED COMPUTE FROM TRAFOOP SUBCLASS.\n"; 
		assert(false); 
		return std::vector<EvaluationResult<Number>>();
	}

	//Given the results, return vector of evaluation results (here only first place needed, since unary op), here, we also modify
	std::vector<EvaluationResult<Number>> aggregate(std::vector<std::vector<EvaluationResult<Number>>>& resultStackBack, const matrix_t<Number>& currentParam) const {
		std::cout << "calling TrafoOp::aggregate\n";
		std::cout << "resultStackBack size: " << resultStackBack.size() << std::endl;
		std::cout << "resultStackBack front size: " << resultStackBack.front().size() << std::endl;
		//assert(resultStackBack.front().size() == 1); 
		assert(resultStackBack.size() == 1); 
		if(resultStackBack.front().begin()->errorCode != SOLUTION::INFEAS){
			unsigned directionCnt = 0;
			for(auto& entry : resultStackBack.front()){
				vector_t<Number> currentDir(currentParam.row(directionCnt));
				if(entry.errorCode == SOLUTION::INFTY) {
					entry.supportValue = 1;
				} else {
					//TRACE("hypro.representations.supportFunction", ": Entry val before trafo: " << entry.optimumValue);
					entry.optimumValue = mat * entry.optimumValue + vec;
					// As we know, that the optimal vertex lies on the supporting Halfspace, we can obtain the distance by dot product.
					entry.supportValue = entry.optimumValue.dot(currentDir);
				}
				//auto t = convert<Number,double>(currentParam.row(directionCnt));
				//TRACE("hypro.representations.supportFunction", "Direction: " << t << ", Entry value: " << entry.supportValue);
				++directionCnt;
			}
		}
		std::cout << "returns\n";
		for(auto& e : resultStackBack.front()){
			std::cout << e << std::endl;
		}
		return resultStackBack.front();
	}

};

} //namespace hypro