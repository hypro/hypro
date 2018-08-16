#include <iostream>
#include <vector>
#include <memory>
#include <string>

//A node in the tree: Contains only information about itself
//Base class for operations and leaves
class RootGrowNode {
private:
	int m = 100;
public:
	RootGrowNode(){}
	virtual ~RootGrowNode(){}								//not sure how to define deletion mechanics
	virtual int evaluate(){ return m; }
}

//This class will later model a SFC
//Assuming we start with some unconnected nodes as leaves
class RootGrowTree {
private:
	RootGrowNode* mRoot;							//ptr to most upper node in tree
	std::vector<RootGrowTree*> mChildren;			//content
	//std::vector<RootGrowNode*> mLeaves;				//Lowest level of nodes
public:
	RootGrowTree() : mRoot(), mChildren() {}
	RootGrowTree(RootGrowTree* r) : mRoot(r), mChildren() {}
	RootGrowTree(RootGrowNode* r, std::vector<RootGrowTree*> c) : mRoot(r), mChildren(c) {}
	~RootGrowTree(){}								//Not sure how to define deletion mechanics	

	void addToChildren(RootGrowTree* rhs){
		mChildren.push_back(rhs);
	}

	void addUnaryOp(RootGrowNode* unary){
		unary->addToChildren(target);
		//NOT FINISHED YET
	}

	//void addBinaryOp(){}
};

