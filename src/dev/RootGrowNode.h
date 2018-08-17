#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <functional>

//Type of nodes. Needed to fast determine which node subclass is actually calling a function. 
enum SF_TYPE { NONE = 0, TRAFO, SUM, LEAF };

//Pseudo EvaluationResult
struct EvalResult
{
	int res;
};

//Pseudo matrix_t
struct Matrix
{
	int entry;
};

//A node in the tree. Knows its children and its height in the tree.
//Base class for operations and leaves
class RootGrowNode {
private:
	SF_TYPE mType = NONE;													//NONE since RootGrowNode should later be an abstract class
	std::vector<RootGrowNode*> mChildren = std::vector<RootGrowNode*>();	//vector of all current children
	bool mUnary;															//is this a unary node(has one child) or is it binary (has two children)
	unsigned mHeight = 0;  													//Leaves have height 0, here height of node is stored

public:

	////// Usings and typedefs

	//Needed for delegating evaluation results to the corresponding subclasses
	//Every possible result of a function with one input parameter can be remodelled here.
	//template<typename Result, typename Param1>
	//using FunctionPtr = std::function<Result(Param1)>;

	////// Constructors

	RootGrowNode(){}

	RootGrowNode(bool u)
		: mChildren(), mUnary(u) {}

	RootGrowNode(bool u, SF_TYPE t)
		: mChildren(), mUnary(u), mType(t) {}	

	RootGrowNode(std::vector<RootGrowNode*> c, bool u, SF_TYPE t)
		: mChildren(c), mUnary(u), mType(t) {}

	~RootGrowNode(){}	//not sure how to define deletion mechanics

	////// Getters and Setters

	bool isUnary() const { return mUnary; }
	unsigned getHeight() const { return mHeight; }
	std::vector<RootGrowNode*> getChildren() const { return mChildren; }
	virtual SF_TYPE evaluate() const { return mType; }

	void setHeight(unsigned h){ mHeight = h; }

	////// Modifiers

	void addToChildren(RootGrowNode* rhs){ mChildren.push_back(rhs); }

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

	////// Operations with Stack

	//void prepareStacks();
	//void cleanStacks();

	//void passToSubtype(SF_TYPE t, FunctionPtr f){
	//	switch(t){
	//		case SF_TYPE::NONE:
	//		case SF_TYPE::TRAFO:
	//		case SF_TYPE::SUM:
	//		case SF_TYPE::LEAF:
	//	}
	//}
	
};