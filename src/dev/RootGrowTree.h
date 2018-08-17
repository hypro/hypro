#include "RootGrowNode.h"

//This class will later model a SFC
//Assuming we start with some unconnected nodes as leaves
class RootGrowTree {
private:

	//ptr to most upper node in tree
	RootGrowNode* mRoot = nullptr;					

public:
	RootGrowTree(){}
	RootGrowTree(RootGrowNode* r) : mRoot(r) {}
	~RootGrowTree(){}								//Not sure how to define deletion mechanics	

	RootGrowNode* getRoot() const { return mRoot; }

	void setRoot(RootGrowNode* r){ mRoot = r; }

	//Add node "unary" that can only have one child as parent of current root.
	void addUnaryOp(RootGrowNode* unary);

	//Add node "binary" that can only have two children as parent of current root. "rhs" is a tree that will be
	//the second child of "binary".
	void addBinaryOp(RootGrowNode* binary, RootGrowTree* rhs);

	friend std::ostream& operator<<(std::ostream& ostr, const RootGrowTree& t){
		ostr << *(t.getRoot()) << std::endl;
		return ostr;
	}
};

