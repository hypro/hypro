#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <functional>
#include <type_traits>
#include <tuple>
#include <cassert>

//Type of nodes. Needed to fast determine which node subclass is actually calling a function. 
//NOTE: is actually redundant
enum SF_TYPE { NONE = 0, TRAFO, SUM, LEAF };

//Pseudo EvaluationResult
struct EvalResult
{
	int res;
	EvalResult() : res(0) {}
	EvalResult(int r) : res(r) {}
	~EvalResult() { }

	friend std::ostream& operator<<(std::ostream& ostr, const EvalResult& e){
		ostr << e.res;
		return ostr;
	}

	friend EvalResult operator+ (const EvalResult& lhs, const EvalResult& rhs){
		int tmp = lhs.res + rhs.res;
		return EvalResult(tmp); 
	}

	friend EvalResult operator* (const EvalResult& lhs, const EvalResult& rhs){
		int tmp = lhs.res * rhs.res;
		return EvalResult(tmp); 
	}
};

//Pseudo matrix_t
struct Matrix
{
	int entry;
	Matrix(int m) : entry(m) {}
};

//A node in the tree. Knows its children and its height in the tree. (Height only needed for printing)
//Base class for operations and leaves
class RootGrowNode {
private:

	////// Members

	SF_TYPE mType = NONE;													//NONE since RootGrowNode should later be an abstract class
	bool mUnary;															//is this a unary node(has one child) or is it binary (has two children)
	unsigned mHeight = 0;  													//Leaves have height 0, here height of node is stored
	unsigned originCount;

protected:
	std::vector<RootGrowNode*> mChildren = std::vector<RootGrowNode*>();	//vector of all current children

public:

	////// Constructors

	RootGrowNode(){}

	RootGrowNode(bool u)
		: mChildren(), mUnary(u) {}

	RootGrowNode(bool u, SF_TYPE t)
		: mChildren(), mUnary(u), mType(t) {}	

	RootGrowNode(std::vector<RootGrowNode*> c, bool u, SF_TYPE t)
		: mChildren(c), mUnary(u), mType(t) {}

	virtual ~RootGrowNode(){}	//not sure how to define deletion mechanics

	////// Getters and Setters

	unsigned getHeight() const { return mHeight; }
	std::vector<RootGrowNode*> getChildren() const { return mChildren; }
	virtual bool isItUnary() const { return mUnary; }
	virtual SF_TYPE getType() const { return mType; }
	virtual unsigned getOriginCount() const { return originCount; }

	void setHeight(unsigned h){ mHeight = h; }

	////// Modifiers

	void addToChildren(RootGrowNode* rhs){ mChildren.push_back(rhs); }

	////// Displaying

	friend std::ostream& operator<<(std::ostream& ostr, const RootGrowNode& r){
		for(unsigned i=0; i < r.getHeight(); i++){
			ostr << "--";
		} 
		ostr << r.getType() << std::endl;
		if(r.getChildren().size() > 0){
			for(auto c : r.getChildren()){
				ostr << *c << std::endl;
			}	
		}
		return ostr;
	}

	////// Traversal

	// The needed functions for evaluate. Virtual s.t. they can be implemented in the Operation/Leaf classes
	// Three functions are needed: call, compute and aggregate.
	// - call will be called by every node
	// - compute will only be called by leaf nodes
	// - aggregate will only be called by all non leaf nodes
	//
	// NOTE: 	All functions used as the call must have the signature A name(A param)
	//			All functions used as the compute must have the signature B name(A param)
	//			All functions used as the aggregate must have the signature std::vector<B> name(B param)

	//For pseudo evaluate

	//For everyone - call
	virtual Matrix transform(Matrix& param){ std::cout << "USED TRANSFORM FROM NODE SUPERCLASS.\n"; assert(false); }
	//For leaves - compute
	virtual std::vector<EvalResult> compute(Matrix& m) = 0; //{ std::cout << "USED COMPUTE FROM NODE SUPERCLASS.\n"; assert(false); }
	//For operations - aggregate
	virtual std::vector<EvalResult> aggregate(std::vector<std::vector<EvalResult>>& resultStackBack) { std::cout << "USED AGGREGATE FROM NODE SUPERCLASS.\n"; assert(false); }

	//For pseudo size

	
};

