#pragma once

#include "RootGrowNode.h"
//#include "Leaf.h"
//#include "TrafoOp.h"
//#include "SumOp.h"

namespace hypro {

//A struct for the parameters.
//All parameters for a function must be placed inside a parameter object.
//Ensures that traversal() gets only one argument instead of 20 or 30!
template<typename ...Rargs>
struct Parameters {
	
	std::tuple<Rargs...> args;

	Parameters(Rargs... r) : args(std::make_tuple(r...)) {}
	Parameters(std::tuple<Rargs...> r) : args(r) {}
	~Parameters(){}

	//static std::size_t size(){ return std::size_t(std::tuple_size<Rargs...>::value); }
};

//This class will later model a SFC
//Assuming we start with some unconnected nodes as leaves
template<typename Number>
class RootGrowTree {
protected:

	//ptr to most upper node in tree
	RootGrowNode<Number>* mRoot = nullptr;					

public:

	////// Constructor & Destructor 

	RootGrowTree(){}
	RootGrowTree(RootGrowNode<Number>* r) : mRoot(r) {}
	~RootGrowTree(){}								//Not sure how to define deletion mechanics	

	////// Getter & Setter

	RootGrowNode<Number>* getRoot() const { return mRoot; }
	void setRoot(RootGrowNode<Number>* r){ mRoot = r; }

	////// Modifier

	//Add node "unary" that can only have one child as parent of current root.
	RootGrowTree* addUnaryOp(RootGrowNode<Number>* unary);

	//Add node "binary" that can only have two children as parent of current root. "rhs" is a tree that will be
	//the second child of "binary".
	RootGrowTree* addBinaryOp(RootGrowNode<Number>* binary, RootGrowTree* rhs);

	//Remove all pointers to current children of mRoot. Set "child" as the only child of mRoot
	RootGrowTree* setAsOnlyChild(RootGrowNode<Number>* child);

	////// Displaying

	friend std::ostream& operator<<(std::ostream& ostr, const RootGrowTree& t){
		ostr << *(t.getRoot()) << std::endl;
		return ostr;
	}

	////// TRAVERSAL
/*
	There are only four possibilities of how void functions and / or functions without parameters can be combined, such that the stack operations 
	made during the actual traversal still remain valid:
	- Result = void,	Params = void:	"void transform()" 		&& "void compute()" 	&& "void aggregate()" 					&& no initParams
	- Result = int, 	Params = void: 	"void transform()" 		&& "int compute()"		&& "int aggregate(vector<int>)" 		&& no initParams
	- Result = void, 	Params = int:	"int transform(int)" 	&& "void compute(int)" 	&& "void aggregate(int)"				&& initParams
	- Result = int, 	Params = int: 	"int transform(int)" 	&& "int compute(int)" 	&& "int aggregate(vector<int>, int)" 	&& initParams
	If the parameter type does not exist (so, Rargs... = empty set), then additional parameters can be left out in all three functions, 
	and if parameters would be returned, void is returned instead (i.e. transform).
	If the result type is void, then the vector to be aggregated for the aggregate function can be left out.
	Below, the four possibilites are implemented, functions returning void or having no additional parameters are wrapped into functions that return 
	empty parameters & receive one additional parameter.
*/

	//When Result type and Param type = void
	//Wrap given functions into other functions that take Parameter (or smth else) additionally as input
	void traverse(	std::function<void(RootGrowNode<Number>*)> transform,
					std::function<void(RootGrowNode<Number>*)> compute, 	
					std::function<void(RootGrowNode<Number>*)> aggregate);

	//When Param type = void, but Result type not
	//Wrap transform and compute into other functions that take Parameter (or smth else) additionally as input
	template<typename Result>
	Result traverse(std::function<void(RootGrowNode<Number>*)> transform,
					std::function<Result(RootGrowNode<Number>*)> compute, 
					std::function<Result(RootGrowNode<Number>*, std::vector<Result>)> aggregate);

	//When Result type = void, but Param type not
	//Wrap aggregate and compute into other functions that take Parameter (or smth else) additionally as input
	template<typename ...Rargs>
	void traverse(	std::function<Parameters<Rargs...>(RootGrowNode<Number>*, Parameters<Rargs...>)> transform,
					std::function<void(RootGrowNode<Number>*, Parameters<Rargs...>)> compute, 
					std::function<void(RootGrowNode<Number>*, Parameters<Rargs...>)> aggregate,
					Parameters<Rargs...> initParams);

	//Actual traverse function
	//Since all cases where Result or Rargs are void / empty are handled by the overloaded versions of this function above,
	//we can assume that we do not get functions returning void / that have no parameters
	template<typename Result, typename ...Rargs>
	Result traverse(std::function<Parameters<Rargs...>(RootGrowNode<Number>*, Parameters<Rargs...>)> transform,
					std::function<Result(RootGrowNode<Number>*, Parameters<Rargs...>)> compute, 
					std::function<Result(RootGrowNode<Number>*, std::vector<Result>, Parameters<Rargs...>)> aggregate, 
					Parameters<Rargs...> initParams);
};

} //namespace hypro

#include "RootGrowTree.tpp"