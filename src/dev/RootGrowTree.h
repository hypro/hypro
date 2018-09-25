#include <functional>
#include <cassert>
#include "RootGrowNode.h"

template<typename ...Rargs>
struct Parameters {
	
	std::tuple<Rargs...> args;

	Parameters(Rargs... r) : args(std::make_tuple(r...)) {}
	Parameters(std::tuple<Rargs...> r) : args(r) {}
	~Parameters(){}

	static bool size(){ return std::size_t(std::tuple_size<Rargs...>::value); }
};

//This class will later model a SFC
//Assuming we start with some unconnected nodes as leaves
class RootGrowTree {
protected:

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

	////// TRAVERSAL
/*
	- TURN std::function TO GENERAL LATER
	- OPTIMIZE WRT CONST AND &
	
	ResultStack Build: 1.Layer: Stack, 2.Layer: Für m operationen, 3.Layer für n operanden pro child
	    -> 1.Layer necessary, 2.Layer bestimmt ob baum eher breit ist oder länglich 
	    	-> länglich vllt besser für bestehende optimierung, breit für eine horizontale optimierung (zwei sumOp nebeneinander zusammenfassen)	
	    	-> horizontale optimierung geht nur wenn bei beiden nodes die Werte aller children bekannt sind (kommt nicht so häufig vor? nicht sicher ob sich lohnt)
	    	-> also lieber längliche optimierung
	    	-> dann lieber statt vector beim 2.Layer std::pair nehmen?
	    -> Vllt lieber ganz auf 2.Layer verzichten?
	    	-> statt m operationen mit jeweils n operanden hätte man dann m*n operanden direkt
*/
/*
	VOID THINGS

	Assume transform has returntype void, so void transform(blub)
	-> transform does not return anything
	-> If something happened, none of this will be saved, since nothing is returned
	-> not saved = not on Parameterstack

	-> For this to make sense, compute should not be able to access the parameter stack
	-> compute must have the signature: int / void compute()
	-> compute can still push results into result stack, if returntype not void
	-> So "void transform(int)" -> "int /void compute()"

	Assume compute has returntype void, so "void compute()"
	-> No results can be pushed into resultStack
	-> aggregate does not need to access resultStack then
	-> signature: "void aggregate()"

	So only possibilities:
	- Result = void, Params = void :	"void transform()" 		&& "void compute()" 	&& "void aggregate()" 			&& no initParams
	- Result = int, Params = void: 		"void transform()" 		&& "int compute()"		&& "int aggregate(vector<int>)" && no initParams
	- Result = void, Params = int:		"int transform(int)" 	&& "void compute(int)" && "void aggregate()"			&& initParams
	- Result = int, Params = int: 		"int transform(int)" 	&& "int compute(int)" 	&& "int aggregate(vector<int>)" && initParams
*/

	//When Result type and Param type = void
	//Wrap given functions into other functions that take Parameter (or smth else) additionally as input
	auto traverse(	std::function<void(RootGrowNode*)> transform,
					std::function<void(RootGrowNode*)> compute, 	
					std::function<void(RootGrowNode*)> aggregate){

		std::function<Parameters<>(RootGrowNode*, Parameters<>)> tNotVoid = [&](RootGrowNode* n, Parameters<> p) -> Parameters<> { transform(n); return Parameters<>(); };
		std::function<Parameters<>(RootGrowNode*, Parameters<>)> cNotVoid = [&](RootGrowNode* n, Parameters<> p) -> Parameters<> { compute(n); return Parameters<>(); };
		std::function<Parameters<>(RootGrowNode*, std::vector<Parameters<>>)> aNotVoid = [&](RootGrowNode* n, std::vector<Parameters<>> p) -> Parameters<> { aggregate(n); return Parameters<>(); };
		traverse(tNotVoid, cNotVoid, aNotVoid, Parameters<>());
		//traverse(tNotVoid, cNotVoid, aNotVoid, emptyParameterSet);
	}	

	//When Param type = void, but Result type not
	//Wrap transform and compute into other functions that take Parameter (or smth else) additionally as input
	template<typename Result>
	auto traverse(	std::function<void(RootGrowNode*)> transform,
					std::function<Result(RootGrowNode*)> compute, 
					std::function<Result(RootGrowNode*, std::vector<Result>)> aggregate){
		
		std::function<Parameters<>(RootGrowNode*, Parameters<>)> tNotVoid = [&](RootGrowNode* n, Parameters<> p) -> Parameters<> { transform(n); return Parameters<>(); };
		std::function<Result(RootGrowNode*, Parameters<>)> cNotVoid = [&](RootGrowNode* n, Parameters<> p) -> Result { return compute(n); };
		return traverse(tNotVoid, cNotVoid, aggregate, Parameters<>());
	}

	//When Result type = void, but Param type not
	//Wrap aggregate and compute into other functions that take Parameter (or smth else) additionally as input
	template<typename ...Rargs>
	auto traverse(	std::function<Parameters<Rargs...>(RootGrowNode*, Parameters<Rargs...>)> transform,
					std::function<void(RootGrowNode*, Parameters<Rargs...>)> compute, 
					std::function<void(RootGrowNode*)> aggregate,
					Parameters<Rargs...> initParams){

		std::function<Parameters<>(RootGrowNode*, Parameters<Rargs...>)> cNotVoid = [&](RootGrowNode* n, Parameters<Rargs...> p) -> Parameters<>{ compute(n,p); return Parameters<>(); };
		std::function<Parameters<>(RootGrowNode*, std::vector<Parameters<>>)> aNotVoid = [&](RootGrowNode* n, std::vector<Parameters<>> p) -> Parameters<> { aggregate(n); return Parameters<>(); };
		traverse(transform, cNotVoid, aNotVoid, initParams);
	}


	//Actual traverse function
	template<typename Result, typename ...Rargs>
	Result traverse(std::function<Parameters<Rargs...>(RootGrowNode*, Parameters<Rargs...>)> transform,
					std::function<Result(RootGrowNode*, Parameters<Rargs...>)> compute, 
					std::function<Result(RootGrowNode*, std::vector<Result>)> aggregate, 
					Parameters<Rargs...> initParams){ 

		std::cout << "RGT::traverse\n";

		constexpr bool isResultVoid = std::is_void<Result>::value;
		
		//Usings
		using Node = RootGrowNode*;
		using Param = Parameters<Rargs...>;
		using Res = typename std::conditional<isResultVoid,unsigned,Result>::type; //Result itself can already be a vector

		std::cout << "isResultVoid: " << isResultVoid << std::endl;		

		//Prepare Stacks
		std::vector<Node> callStack;
		std::vector<Param> paramStack;
		std::vector<std::pair<int,std::vector<Res>>> resultStack;  
		callStack.push_back(mRoot);
		paramStack.push_back(initParams);
		resultStack.push_back(std::make_pair(-1, std::vector<Res>()));

		//Traversal loop
		while(!callStack.empty()){

			Node cur = callStack.back();
			Param currentParam = paramStack.back();

			if(cur->getOriginCount() == 0){

				std::pair<int,std::vector<Res>> currentResult = resultStack.back();

				//If leaf and end of stack is reached
				if(currentResult.first == -1){

					if(isResultVoid){
						std::apply(compute, std::make_tuple(cur, currentParam));
					} else {
						return std::apply(compute, std::make_tuple(cur, currentParam));
					}
					
				//If leaf and not end of stack is reached	
				} else {

					if(isResultVoid){
						std::apply(compute, std::make_tuple(cur, currentParam.args));
					} else {
						resultStack.at(currentResult.first).second.emplace_back(std::apply(compute, std::make_tuple(cur, currentParam)));
					}

				}

				// delete result frame and close recursive call
				callStack.pop_back();
				paramStack.pop_back();
				resultStack.pop_back();

			} else {

				//If enough arguments for operation of node and #arguments != 0
				if(resultStack.back().second.size() == cur->getOriginCount()) {

					//Res accumulatedResult = cur->accumulate(resultStack.back().second);
					Res accumulatedResult;

					if(!isResultVoid){
						accumulatedResult = std::apply(aggregate, std::make_pair(cur, resultStack.back().second));
					}

					// we reached the top, exit
					if(resultStack.back().first == -1) {
						return accumulatedResult;
					}

					// forward result.
					resultStack.at(resultStack.back().first).second.emplace_back(accumulatedResult);

					// delete result frame and close recursive call
					callStack.pop_back();
					paramStack.pop_back();
					resultStack.pop_back();

				//Every other case (recursive call)
				} else {

					// here we create the new stack levels.
					std::size_t callingFrame = callStack.size() - 1;
					for(auto c : cur->getChildren()){
						callStack.push_back(c);
						if(isResultVoid){
							std::apply(transform, std::make_tuple(cur, currentParam));
						} else {
							paramStack.push_back(std::apply(transform, std::make_tuple(cur, currentParam)));	
						}
						resultStack.push_back(std::make_pair(callingFrame, std::vector<Res>()));
					}
				}
			}
		}
		std::cout << "THIS SHOULD NOT HAPPEN." << std::endl;
		return Res();
	}
};


