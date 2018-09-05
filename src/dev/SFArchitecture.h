#include <iostream>
#include <string>
#include <vector>
#include <tuple>
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

public:
	TrafoOp(){}
	~TrafoOp(){}
	SF_TYPE getType() const override { return type; }
	unsigned getOriginCount() const { return originCount; }
	EvalResult evaluate(Matrix m) { 
		std::cout << "TrafoOp evaluate is factor: " << factor << " times m.entry: " << m.entry << std::endl;
		return factor*m.entry; 
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
	SF_TYPE getType() const override { return type; }
	unsigned getOriginCount() const { return originCount; }
	EvalResult evaluate(Matrix m) { 
		std::cout << "SumOp evaluate is: " << mChildren.at(0)->evaluate(m) << " and " << mChildren.at(0)->evaluate(m) << std::endl;
		return mChildren.at(0)->evaluate(m) + mChildren.at(1)->evaluate(m);
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
	SF_TYPE getType() const override { return type; }
	unsigned getOriginCount() const { return originCount; }
	Rep say(){ return member; }
	EvalResult evaluate(Matrix m){ 
		std::cout << "Leaf evaluate is: " << mem << std::endl;
		return mem; 
	}
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

	//Here: function evaluate, that calls traverse on the root node to start the traversing process
	int evaluate(Matrix directions){

		//Usings
		using Node = RootGrowNode*;
		using Param = Matrix;
		using Res = EvalResult;
		
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

			std::cout << "START EVALUATION\n";
			auto tmp = cur->evaluate(currentParam);
			std::cout << "RESULT OF EVALUATION: " << tmp.res << std::endl;
/*
			if(cur->getOriginCount() == 0){

				std::pair<int,std::vector<Res>> currentResult = resultStack.back();

				//If leaf and end of stack is reached
				if(currentResult.first == -1){

					return cur->evaluate();

				//If leaf and not end of stack is reached	
				//} else {

				}

				// delete result frame and close recursive call
				callStack.pop_back();
				paramStack.pop_back();
				resultStack.pop_back();

			}
*/
			//If enough arguments for operation of node and #arguments != 0

			//Every other case (recursive call)

			// delete result frame and close recursive call (DELETE LATER)
			callStack.pop_back();
			paramStack.pop_back();
			resultStack.pop_back();

		}

		//return Result
		return resultStack.back().second.front().res;
	}
	

	//NEXT: Implement evaluate in all node types and implement stack operations

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
