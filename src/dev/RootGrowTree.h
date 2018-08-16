#include <iostream>
#include <vector>
#include <memory>
#include <string>

//A node in the tree: Contains only information about itself
//Base class for operations and leaves
class RootGrowNode {
private:
	
	int m = 100;							//just some test identifier
	std::vector<RootGrowNode*> mChildren;	//vector of all current children
	bool mUnary;							//is this a unary node(has one child) or is it binary (has two children)
	unsigned mHeight;  						//Leaves have height 0, here height of node is stored

public:

	////// Constructors

	RootGrowNode(){}
	RootGrowNode(bool u)
		: mChildren(), mUnary(u) {}
	RootGrowNode(int something, std::vector<RootGrowNode*> c, bool u, unsigned height) 
		: m(something), mChildren(c), mUnary(u), mHeight(height) {}
	~RootGrowNode(){}								//not sure how to define deletion mechanics

	////// Getters and Setters

	int evaluate() const { return m; }
	bool isUnary() const { return mUnary; }
	unsigned getHeight() const { return mHeight; }
	std::vector<RootGrowNode*> getChildren() const { return mChildren; }

	void setHeight(unsigned h){ mHeight = h; }

	////// Modifiers

	void addToChildren(RootGrowNode* rhs){
		mChildren.push_back(rhs);
	}

	////// Displaying

	friend std::ostream& operator<<(std::ostream& ostr, const RootGrowNode& r){
		for(unsigned i=0; i < r.getHeight(); i++){
			ostr << "--";
		} 
		ostr << r.evaluate() << std::endl;
		if(r.getChildren().size() > 0){
			for(auto c : r.getChildren()){
				ostr << *c << std::endl;
			}	
		}
		return ostr;
	}
};

//This class will later model a SFC
//Assuming we start with some unconnected nodes as leaves
class RootGrowTree {
private:
	RootGrowNode* mRoot = nullptr;					//ptr to most upper node in tree
	//std::vector<RootGrowTree*> mChildren;			//content
	//std::vector<RootGrowNode*> mLeaves;			//Lowest level of nodes
public:
	RootGrowTree(){}
	RootGrowTree(RootGrowNode* r) : mRoot(r) {}
	~RootGrowTree(){}								//Not sure how to define deletion mechanics	

	RootGrowNode* getRoot() const { return mRoot; }

	void setRoot(RootGrowNode* r){ mRoot = r; }

	void addUnaryOp(RootGrowNode* unary){
		if(unary->isUnary()){

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

	void addBinaryOp(RootGrowNode* binary, RootGrowTree* rhs){
		if(!binary->isUnary()){
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


	friend std::ostream& operator<<(std::ostream& ostr, const RootGrowTree& t){
		ostr << *(t.getRoot()) << std::endl;
		return ostr;
	}
};

