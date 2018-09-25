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

	std::vector<EvalResult> compute(Matrix& m){ 
		std::cout << "USED COMPUTE FROM TRAFOOP SUBCLASS.\n"; 
		assert(false); 
		return std::vector<EvalResult>();
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

	std::vector<EvalResult> compute(Matrix& m){ 
		std::cout << "USED COMPUTE FROM SUMOP SUBCLASS.\n"; 
		assert(false); 
		return std::vector<EvalResult>();
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
	std::vector<EvalResult> compute(Matrix& m) { 
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

	std::vector<EvalResult> evaluate(Matrix directions){
		
		std::cout << "SFC::evaluate\n";

		//Real evaluate
		std::function<Parameters<Matrix>(RootGrowNode*, Parameters<Matrix>)> trans = 
			[](RootGrowNode* n, Parameters<Matrix> param) -> Parameters<Matrix> { 
				return Parameters<Matrix>(n->transform(std::get<0>(param.args))); 
			};

		std::function<std::vector<EvalResult>(RootGrowNode*, Parameters<Matrix>)> comp = 
			[](RootGrowNode* n, Parameters<Matrix> dir) -> std::vector<EvalResult> { 
				return n->compute(std::get<0>(dir.args)); 
			};

		std::function<std::vector<EvalResult>(RootGrowNode*, std::vector<std::vector<EvalResult>>)> agg = 
			[](RootGrowNode* n, std::vector<std::vector<EvalResult>> resultStackBack) -> std::vector<EvalResult> { 
				return n->aggregate(resultStackBack); 
			};

		std::cout << "trans invocable? " << std::is_invocable_r<Parameters<Matrix>, decltype(trans), RootGrowNode*, Parameters<Matrix>>::value << std::endl;
		std::cout << "comp invocable? " << std::is_invocable_r<std::vector<EvalResult>, decltype(comp), RootGrowNode*, Parameters<Matrix>>::value << std::endl;
		std::cout << "agg invocable? " << std::is_invocable_r<std::vector<EvalResult>, decltype(agg), RootGrowNode*, std::vector<std::vector<EvalResult>>>::value << std::endl;
		return traverse(trans, comp, agg, Parameters<Matrix>(directions));
	}

	//Testing of each overloaded version of traverse.
	void functionTest(){

		//three different functions
		std::cout << "====== TESTING FUNCS WITH NO PARAMETERS\n";
		std::function<Parameters<>(RootGrowNode*, Parameters<>)> fTrafo = 
			[](RootGrowNode* n, Parameters<> par){ 
				std::cout << "fTrafo executed! Current node type: " << n->getType() << std::endl; 
				return par;
			};
		std::function<EvalResult(RootGrowNode*, Parameters<>)> gComp = 
			[](RootGrowNode* n, Parameters<> par){ 
				std::cout << "gComp executed! Current node type: " << n->getType() << std::endl; 
				return EvalResult(1);
			};
		std::function<EvalResult(RootGrowNode*, std::vector<EvalResult>)> hAgg = 
			[](RootGrowNode* n, std::vector<EvalResult> v){ 
				EvalResult res(0);
				for(auto e : v){
					res = res + e;
				}
				std::cout << "hAgg executed! Current node type: " << n->getType() << std::endl; 
				return res;
			};
		Parameters<> p;
		traverse(fTrafo, gComp, hAgg, p);
	

		//only void functions
		std::cout << "====== TESTING FUNCS WITH NO PARAMETERS RETURNING VOID\n";
		std::function<void(RootGrowNode*)> i = 
			[](RootGrowNode* n){ 
				std::cout << "i executed! Current node type: " << n->getType() << std::endl; 
			};
		traverse(i,i,i);
		

		//only parameter type = void
		std::cout << "====== TESTING FUNCS WHERE PARAM TYPE = VOID \n";
		std::function<int(RootGrowNode*)> jComp = 
			[](RootGrowNode* n){ 
				std::cout << "jComp executed! returning: " << 1000 << std::endl;
				return 1000; 
			};
		std::function<int(RootGrowNode*, std::vector<int>)> kAgg = 
			[](RootGrowNode* n, std::vector<int> v){ 
				int tmp = 0;
				for(auto res : v){
					tmp += res;
				}
				std::cout << "kAgg executed! returning: " << tmp << std::endl; 
				return tmp;
			};
		traverse(i,jComp,kAgg);


		//only return type = void
		std::cout << "====== TESTING FUNCS WHERE RESULT TYPE = VOID\n";
		std::function<Parameters<int>(RootGrowNode*, Parameters<int>)> lTrafo =
			[](RootGrowNode* n, Parameters<int> m){
				std::cout << "lTrafo executed! got: " << std::get<0>(m.args) << std::endl; 
				return m;
			};
		std::function<void(RootGrowNode*,Parameters<int>)> mComp =
			[](RootGrowNode* n, Parameters<int> blub){
				std::cout << "gotcha" << std::endl;
			};
		traverse(lTrafo, mComp, i, Parameters<int>(-12));


		//multiple parameters
		std::cout << "====== TESTING FUNCS WITH MULTIPLE PARAMETERS\n";

		//For two parameters of type int and float, double the value of the one of type float
		std::function<Parameters<int,float>(RootGrowNode*, Parameters<int,float>)> trafoWithMoreParams =
			[](RootGrowNode* n, Parameters<int,float> p) -> Parameters<int,float> {
				auto tmp = Parameters<int,float>(std::get<0>(p.args), 2.0f*std::get<1>(p.args));
				std::cout << "trafoWithMoreParams executed! new values are: [" << std::get<0>(p.args) << "," << 2.0f*std::get<1>(p.args) << "]\n";
				return tmp;
			};
		//Sum both the int and the float parameters. Add a bool flag that indicates that we have computed. Make a float,bool-pair
		std::function<std::pair<float,bool>(RootGrowNode*, Parameters<int,float>)> compWithMoreParams =
			[](RootGrowNode* n, Parameters<int,float> p) -> std::pair<float,bool> {
				auto tmp = std::make_pair(float(std::get<0>(p.args) + std::get<1>(p.args)), false);
				std::cout << "compWithMoreParams executed! new pair is: (" << tmp.first << "," << tmp.second << ")\n";
				return tmp;
			};
		//Sum up all floats in the vector of float-bool-pairs. Set bool flat to true to indicate that we have aggregated
		std::function<std::pair<float,bool>(RootGrowNode*, std::vector<std::pair<float,bool>>)> aggWithMoreParams =
			[](RootGrowNode* n, std::vector<std::pair<float,bool>> v) -> std::pair<float,bool> {
				float res = 0.0f;
				for(auto elem : v){
					res += elem.first;
				}
				auto tmp = std::make_pair(res, true);
				std::cout << "aggWithMoreParams executed! agg'd pair is: (" << tmp.first << "," << tmp.second << ")\n";	
				return tmp;
			};
		traverse(trafoWithMoreParams, compWithMoreParams, aggWithMoreParams, Parameters<int,float>(2,1.0f));
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

