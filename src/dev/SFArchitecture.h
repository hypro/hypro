#include <iostream>
#include <string>
#include <vector>
#include "RootGrowTree.h"

//Specialized subclass for transformations as example of a unary operator
class TrafoOp : public RootGrowNode {
private:
	SF_TYPE type = SF_TYPE::TRAFO;
	bool isUnary = true;
public:
	TrafoOp(){}
	~TrafoOp(){}
	SF_TYPE evaluate() const override { return type; }
};


//Specialized subclass for sums as example of a binary operator
class SumOp : public RootGrowNode {
private:
	SF_TYPE type = SF_TYPE::SUM;
	bool isUnary = false;
public:
	SumOp(){}
	~SumOp(){}
	SF_TYPE evaluate() const override { return type; }
};

//Another still templated subclass of RootGrowNode
template<typename Rep> 
class Leaf : public RootGrowNode {
private:
	Rep member = Rep();
	SF_TYPE type = SF_TYPE::LEAF;
	bool isUnary = true;
public:
	Leaf(){}
	Leaf(Rep r) : member(r) {}
	~Leaf(){}
	SF_TYPE evaluate() const override { return type; }
	Rep say(){ return member; }
};

//Support Function Content, N = RootGrowNode
//template<typename N>
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
};

//Support Function
//template<typename N>
class SF {
private:
	//SFC<N>* content;
	SFC* content;
public:
	SF(){}
	SF(SFC* c) : content(c) {}

	SFC* getContent() const { return content; }

	void listAllDirectChildren(){
		for(auto ch : content->getRoot()->getChildren()){
			std::cout << ch->evaluate() << "," << std::endl;
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
