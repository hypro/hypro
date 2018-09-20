#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <cassert>
#include "RootGrowTree.h"

//Specialized subclass for transformations as example of a unary operator
class TrafoOp : public RootGrowNode {
private:
	////// General Interface

	SF_TYPE type = SF_TYPE::TRAFO;
	bool isUnary = true;
	unsigned originCount = 1;

	////// Members for this class

	int factor = 5;
	int translation = -10;

public:
	TrafoOp() {}
	~TrafoOp(){}
	SF_TYPE getType() const override { return type; }
	bool isItUnary() const override { return isUnary; }
	unsigned getOriginCount() const { return originCount; }

	//Given the results, return vector of evaluation results (here only first place needed, since unary op), here, we also modify
	std::vector<EvalResult> aggregate(std::vector<std::vector<EvalResult>>& resultStackBack){ 
		//Make sure only one vector of parameters here
		assert(resultStackBack.size() == 1); 
		for(unsigned i = 0; i < resultStackBack.at(0).size(); i++){
			resultStackBack.at(0).at(i) = EvalResult(factor*resultStackBack.at(0).at(i).res + translation);	
		}
		return resultStackBack.at(0);
	}

	//Test with void functions
	Matrix transform(Matrix& param){
		return Matrix(factor*param.entry + translation);
	}


};


//Specialized subclass for sums as example of a binary operator
class SumOp : public RootGrowNode {
private:
	////// General Interface

	SF_TYPE type = SF_TYPE::SUM;
	bool isUnary = false;
	unsigned originCount = 2;

	////// Members for this class: uses the children of the Node

public:
	SumOp(){}
	~SumOp(){}
	bool isItUnary() const override { return isUnary; }
	SF_TYPE getType() const override { return type; }
	unsigned getOriginCount() const { return originCount; }

	//Given two result vecs, sum them coefficientwise
	std::vector<EvalResult> aggregate(std::vector<std::vector<EvalResult>>& resultStackBack) {
		assert(resultStackBack.size() == 2);
		assert(resultStackBack.at(0).size() == resultStackBack.at(1).size());
		std::vector<EvalResult> r;
		for(unsigned i=0; i < resultStackBack.at(0).size(); i++){
			EvalResult e;
			e.res = resultStackBack.at(0).at(i).res + resultStackBack.at(1).at(i).res;
			r.emplace_back(e);
		}
		return r;
	}

	Matrix transform(Matrix& param){
		return param;
	}
};

//Another still templated subclass of RootGrowNode
template<typename Rep> 
class Leaf : public RootGrowNode {
private:
	Rep member = Rep();
	SF_TYPE type = SF_TYPE::LEAF;
	bool isUnary = true;
	unsigned originCount = 0;
	int mem = 2;
public:
	Leaf(){}
	Leaf(Rep r) : member(r) {}
	~Leaf(){}
	bool isItUnary() const override { return isUnary; }
	SF_TYPE getType() const override { return type; }
	unsigned getOriginCount() const { return originCount; }
	Rep say(){ return member; }

	//Evaluate leaf. Just return a vector of length m, filled with mem
	std::vector<EvalResult> compute(Matrix m){ 
		return std::vector<EvalResult>(mem, m.entry); 
	}

	Matrix transform(Matrix&){ assert(false); return Matrix(-1); }

};

//Support Function Content
class SFC : public RootGrowTree {
//private:
	//Inherited:
	//RootGrowNode* root
public:
	SFC() {}
	SFC(RootGrowNode* root) : RootGrowTree(root) {}

	std::vector<RootGrowNode*> getChildren(){
		return this->getRoot()->getChildren();
	}

	friend std::ostream& operator<< (std::ostream& ostr, const SFC& rhs){
		ostr << *(rhs.getRoot()) << std::endl;
		return ostr;
	}
/*
	std::vector<EvalResult> evaluate(Matrix directions){
		std::cout << "SFC::evaluate\n";
		//If ptr caught as reference in traverse(), then dangling references, avoid somehow
		//auto eval = [](RootGrowNode* n, Matrix dir) -> std::vector<EvalResult> { return n->evaluate(dir); };
		std::function<std::vector<EvalResult>(RootGrowNode*, Matrix)> eval = [](RootGrowNode* n, Matrix dir) -> std::vector<EvalResult> { return n->evaluate(dir); };
		std::cout << "SFC::evaluate made eval\n";
		//auto trans = [](RootGrowNode* n, Matrix param) -> Matrix { return n->transform(param); };
		std::function<Matrix(RootGrowNode*,Matrix)> trans = [](RootGrowNode* n, Matrix param) -> Matrix { return n->transform(param); };
		std::cout << "SFC::evaluate made trans\n";
		std::tuple<Matrix> dir = std::make_tuple(directions);
		std::cout << "SFC::evaluate made dir\n";
		std::tuple<Matrix> empty = std::make_tuple(Matrix(0));
		std::cout << "SFC::evaluate made empty\n";
		return traverse(eval, dir, trans, empty);
	}
*/
/*
	std::vector<EvalResult> evaluate(Matrix directions){
		std::cout << "SFC::evaluate\n";
		std::function<Matrix(RootGrowNode*,Matrix)> trans = [](RootGrowNode* n, Matrix param) -> Matrix { return n->transform(param); };
		std::function<std::vector<EvalResult>(RootGrowNode*, Matrix)> comp = [](RootGrowNode* n, Matrix dir) -> std::vector<EvalResult> { return n->compute(dir); };
		std::function<std::vector<EvalResult>(RootGrowNode*, std::vector<std::vector<Matrix>>)> agg = 
			[](RootGrowNode* n, std::vector<std::vector<Matrix>> resultStackBack) -> std::vector<EvalResult> { return n->aggregate(resultStackBack); };
		std::cout << "SFC::evaluate made funcs\n";
		std::tuple<Matrix> dir = std::make_tuple(directions);
		std::cout << "SFC::evaluate made dir\n";
		std::cout << "traverse invocable? " << std::is_invocable<decltype(traverse(trans, comp, agg, dir))>::value << std::endl;
		return std::vector<EvalResult>();
		//return traverse(trans, comp, agg, dir);
	}
*/
	void travTest(Matrix directions){
		std::cout << "SFC::travTest\n";
/*
		std::function<int(RootGrowNode*, int)> testing = [](RootGrowNode* n, int dir) -> int { return RootGrowTree::f(dir); };
		std::cout << "testing invocable? " << std::is_invocable_r<int, decltype(testing), RootGrowNode*, int>::value << std::endl;
		std::function<void(RootGrowNode*, int)> testing2 = [](RootGrowNode* n, int dir) { RootGrowTree::prepareStack(dir); };
		std::cout << "testing2 invocable? " << std::is_invocable_r<void, decltype(testing2), RootGrowNode*, int>::value << std::endl;
		std::function<void(RootGrowNode*, float)> testing3 = [](RootGrowNode* n, float dir) { return RootGrowTree::accumulate(dir); };
		std::cout << "testing3 invocable? " << std::is_invocable_r<void, decltype(testing3), RootGrowNode*, float>::value << std::endl;
*/
		//traverseTest(testing, directions, testing2, directions, testing3, 0.0f);
		//traverseTest(testing, testing2, testing3, directions);
		//traverseTest(testing, directions);

		std::function<Matrix(RootGrowNode*, Matrix)> trans = [](RootGrowNode* n, Matrix param) -> Matrix { return n->transform(param); };
		std::cout << "trans invocable? " << std::is_invocable_r<Matrix, decltype(trans), RootGrowNode*, Matrix>::value << std::endl;

		std::function<std::vector<EvalResult>(RootGrowNode*, Matrix)> comp = [](RootGrowNode* n, Matrix dir) -> std::vector<EvalResult> { return n->compute(dir); };
		std::cout << "comp invocable? " << std::is_invocable_r<std::vector<EvalResult>, decltype(comp), RootGrowNode*, Matrix>::value << std::endl;

		std::function<std::vector<EvalResult>(RootGrowNode*, std::vector<std::vector<EvalResult>>)> agg = 
			[](RootGrowNode* n, std::vector<std::vector<EvalResult>> resultStackBack) -> std::vector<EvalResult> { return n->aggregate(resultStackBack); };
		std::cout << "agg invocable? " << std::is_invocable_r<std::vector<EvalResult>, decltype(agg), RootGrowNode*, std::vector<std::vector<EvalResult>>>::value << std::endl;

		traverseTest(trans, comp, agg, directions);
		//traverseTest(trans, testing2, testing3, directions);
	}	

};

//Support Function
class SF {
private:
	SFC* content;
public:
	SF(){}
	SF(SFC* c) : content(c) {}

	SFC* getContent() const { return content; }

	void listAllDirectChildren(){
		for(auto ch : content->getRoot()->getChildren()){
			std::cout << ch->getType() << "," << std::endl;
		}
	}

	void listUnderlyingTree(){
		std::cout << *(content->getRoot()) << std::endl;
	}

	friend std::ostream& operator<< (std::ostream& ostr, const SF& rhs){
		ostr << *(rhs.getContent()) << std::endl;
		return ostr;
	}
};

/* WAS IN SFC
	//Here: function evaluate, that calls traverse on the root node to start the traversing process
	std::vector<EvalResult> evaluate(Matrix directions){

		//Usings
		using Node = RootGrowNode*;
		using Param = Matrix;
		using Res = std::vector<EvalResult>;
		
		//Prepare Stacks
		std::vector<Node> callStack;
		std::vector<Param> paramStack;
		std::vector<std::pair<int,std::vector<Res>>> resultStack;  
		callStack.push_back(mRoot);
		paramStack.push_back(directions);
		resultStack.push_back(std::make_pair(-1, std::vector<Res>()));

		while(!callStack.empty()){

			Node cur = callStack.back();
			Param currentParam = paramStack.back();

			//Only printing stuff
			std::cout << "=== START EVALUATION\n";
			std::cout << "callStack size: " << callStack.size() << std::endl;
			std::cout << "paramStack size: " << paramStack.size() << std::endl;
			std::cout << "paramStack content: \n";
			for(auto p : paramStack){
				std::cout << "\t" << p.entry << std::endl;
			}
			std::cout << "resultStack size: " << resultStack.size() << std::endl;
			std::cout << "resultStack content: \n";
			for(auto r : resultStack){
				std::cout << "\t" << r.first;
				for(auto operands : r.second){
					std::cout << "\t" << "[";
					for(auto args : operands){
						std::cout << args.res << ","; 
					}
					std::cout << "]";
				}
				std::cout << "\n";
			}
			std::cout << "\n";
			std::cout << "cur type is: " << cur->getType() << std::endl;

			if(cur->getOriginCount() == 0){

				std::pair<int,std::vector<Res>> currentResult = resultStack.back();
				assert(cur->getType() == 3);

				//If leaf and end of stack is reached
				if(currentResult.first == -1){

					return cur->evaluate(currentParam);

				//If leaf and not end of stack is reached	
				} else {

					auto tmp = cur->evaluate(currentParam);
					resultStack.at(currentResult.first).second.emplace_back(tmp);

				}

				// delete result frame and close recursive call
				callStack.pop_back();
				paramStack.pop_back();
				resultStack.pop_back();

			} else {

				//If enough arguments for operation of node and #arguments != 0
				if(resultStack.back().second.size() == cur->getOriginCount()) {

					Res accumulatedResult = cur->accumulate(resultStack.back().second);

					// we reached the top, exit
					if(resultStack.back().first == -1) {
						
						std::cout << "accumulatedResult: ["; 
						for(unsigned i=0; i<accumulatedResult.size(); i++){
							std::cout << accumulatedResult.at(i).res << ",";	
						}
						std::cout << "]\n";
						
						return accumulatedResult;
					}

					// forward result.
					resultStack.at(resultStack.back().first).second.emplace_back(accumulatedResult);

					// delete result frame and close recursive call
					callStack.pop_back();
					paramStack.pop_back();
					resultStack.pop_back();

				//Every other case (recursive call)
				} else {

					// here we create the new stack levels.
					std::size_t callingFrame = callStack.size() - 1;
					cur->pushToStacks(callStack, paramStack, resultStack, currentParam, callingFrame);
				}
			}
		}

		std::cout << "THIS SHOULD NOT HAPPEN." << std::endl;
		return std::vector<EvalResult>();
	}
*/
