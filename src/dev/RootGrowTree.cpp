#include "RootGrowTree.h"

void RootGrowTree::addUnaryOp(RootGrowNode* unary){
	if(unary->isItUnary()){

		//Make a copy of the root ptr
		RootGrowNode* copyOfRootPtr = mRoot;

		//Save the Height of the current root
		unsigned tmp = mRoot->getHeight();

		//Add current root as child of given unary node
		unary->addToChildren(copyOfRootPtr);

		//set unary as the root
		mRoot = unary;

		//set Height of unary one up
		mRoot->setHeight(tmp+1);

	} else {
		std::cout << "WARNING: operation to add was not unary. Nothing added.\n";
	}
	
}

void RootGrowTree::addBinaryOp(RootGrowNode* binary, RootGrowTree* rhs){
	if(!binary->isItUnary()){
		RootGrowNode* lhsRootPtr = mRoot;
		RootGrowNode* rhsRootPtr = rhs->getRoot();
		unsigned tmp = mRoot->getHeight();
		binary->addToChildren(lhsRootPtr);
		binary->addToChildren(rhsRootPtr);
		mRoot = binary;
		mRoot->setHeight(tmp+1);
		rhs->setRoot(binary);
	} else {
		std::cout << "WARNING: operation to add was not binary. Nothing added.\n";	
	}
}
