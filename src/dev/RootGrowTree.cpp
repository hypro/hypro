#include "RootGrowTree.h"

//Experimental test file

int main(){

	//Make a unary node r with standard index 100
	bool unary = true;
	RootGrowNode r(unary);
	r.setHeight(0);
	RootGrowNode* rPtr = &r;

	//Make a tree with only r as its root node
	RootGrowTree t(rPtr);

	//Insert a new unary node with index 50
	RootGrowNode r2(50, std::vector<RootGrowNode*>(), unary, 0);
	RootGrowNode* r2Ptr = &r2;	
	t.addUnaryOp(r2Ptr);

	//Insert a third unary node with index 40 via binary operator 30
	RootGrowNode r3(40, std::vector<RootGrowNode*>(), unary, 0);
	RootGrowNode* r3Ptr = &r3;

	RootGrowNode binary(30, std::vector<RootGrowNode*>(), !unary, 0);
	RootGrowNode* binaryPtr = &binary;

	//Build second tree
	RootGrowTree t2(r3Ptr);
	RootGrowTree* t2Ptr = &t2;

	//Stick trees together
	t.addBinaryOp(binaryPtr, t2Ptr);

	std::cout << "Tree t is:\n" << t << std::endl;
	std::cout << "Tree t2 is:\n" << t2 << std::endl;


}