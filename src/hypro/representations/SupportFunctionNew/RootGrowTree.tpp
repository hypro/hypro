/*
#include "RootGrowTree.h"

namespace hypro {	

	template<typename Number>
	RootGrowTree<Number>* RootGrowTree<Number>::addUnaryOp(RootGrowNode<Number>* unary){
		assert(unary->getOriginCount() == 1);
			
		//Make a copy of the root ptr
		RootGrowNode<Number>* copyOfRootPtr = mRoot;

		//Add current root as child of given unary node
		unary->addToChildren(copyOfRootPtr);

		//set unary as parent of root
		copyOfRootPtr->setAsParent(unary);

		//set unary also as original parent of root
		//copyOfRootPtr->setAsOriginalParent(unary);

		//set unary as the root
		mRoot = unary;

		return this;
	}

	template<typename Number>
	RootGrowTree<Number>* RootGrowTree<Number>::addBinaryOp(RootGrowNode<Number>* binary, RootGrowTree<Number>* rhs){
		assert(binary->getOriginCount() == 2);
		RootGrowNode<Number>* lhsRootPtr = mRoot;
		RootGrowNode<Number>* rhsRootPtr = rhs->getRoot();
		binary->addToChildren(lhsRootPtr);
		binary->addToChildren(rhsRootPtr);
		lhsRootPtr->setAsParent(binary);
		rhsRootPtr->setAsParent(binary);
		//lhsRootPtr->setAsOriginalParent(binary);
		//rhsRootPtr->setAsOriginalParent(binary);
		mRoot = binary;
		rhs->setRoot(binary);
		return this;
	}

	template<typename Number>
	RootGrowTree<Number>* RootGrowTree<Number>::setAsOnlyChild(RootGrowNode<Number>* child){
		mRoot->clearChildren();
		mRoot->addToChildren(child);
		child->setAsParent(mRoot);
		//Does not set mRoot as original parent
		return this;
	}

	//When Result type and Param type = void
	template<typename Number>
	void RootGrowTree<Number>::traverse( 	
		std::function<void(RootGrowNode<Number>*)> transform,
		std::function<void(RootGrowNode<Number>*)> compute, 	
		std::function<void(RootGrowNode<Number>*)> aggregate)
	{
		std::function<Parameters<>(RootGrowNode<Number>*, Parameters<>)> tNotVoid = [&](RootGrowNode<Number>* n, Parameters<> p) -> Parameters<> { transform(n); return Parameters<>(); };
		std::function<Parameters<>(RootGrowNode<Number>*, Parameters<>)> cNotVoid = [&](RootGrowNode<Number>* n, Parameters<> p) -> Parameters<> { compute(n); return Parameters<>(); };
		std::function<Parameters<>(RootGrowNode<Number>*, std::vector<Parameters<>>, Parameters<>)> aNotVoid = [&](RootGrowNode<Number>* n, std::vector<Parameters<>> v, Parameters<> p) -> Parameters<> { aggregate(n); return Parameters<>(); };
		traverse(tNotVoid, cNotVoid, aNotVoid, Parameters<>());
	}

	//When Param type = void, but Result type not
	template<typename Number>
	template<typename Result>
	Result RootGrowTree<Number>::traverse(	
		std::function<void(RootGrowNode<Number>*)> transform,
		std::function<Result(RootGrowNode<Number>*)> compute, 
		std::function<Result(RootGrowNode<Number>*, std::vector<Result>)> aggregate)
	{	
		std::function<Parameters<>(RootGrowNode<Number>*, Parameters<>)> tNotVoid = [&](RootGrowNode<Number>* n, Parameters<> ) -> Parameters<> { transform(n); return Parameters<>(); };
		std::function<Result(RootGrowNode<Number>*, Parameters<>)> cNotVoid = [&](RootGrowNode<Number>* n, Parameters<> ) -> Result { return compute(n); };
		std::function<Result(RootGrowNode<Number>*, std::vector<Result>, Parameters<>)> aWithParams = [&](RootGrowNode<Number>* n, std::vector<Result> v, Parameters<> ) -> Result { return aggregate(n,v); };
		return traverse(tNotVoid, cNotVoid, aWithParams, Parameters<>());
	}

	//When Result type = void, but Param type not
	template<typename Number>
	template<typename ...Rargs>
	void RootGrowTree<Number>::traverse(	
		std::function<Parameters<Rargs...>(RootGrowNode<Number>*, Parameters<Rargs...>)> transform,
		std::function<void(RootGrowNode<Number>*, Parameters<Rargs...>)> compute, 
		std::function<void(RootGrowNode<Number>*, Parameters<Rargs...>)> aggregate,
		Parameters<Rargs...> initParams){

		std::function<Parameters<>(RootGrowNode<Number>*, Parameters<Rargs...>)> cNotVoid = [&](RootGrowNode<Number>* n, Parameters<Rargs...> p) -> Parameters<>{ compute(n,p); return Parameters<>(); };
		std::function<Parameters<>(RootGrowNode<Number>*, std::vector<Parameters<>>, Parameters<Rargs...>)> aNotVoid = [&](RootGrowNode<Number>* n, std::vector<Parameters<>> v, Parameters<Rargs...> p) -> Parameters<> { aggregate(n,p); return Parameters<>(); };
		traverse(transform, cNotVoid, aNotVoid, initParams);
	}

	//Actual traverse function. Result type and Param type not void
	template<typename Number>
	template<typename Result, typename ...Rargs>
	Result RootGrowTree<Number>::traverse(
		std::function<Parameters<Rargs...>(RootGrowNode<Number>*, Parameters<Rargs...>)> transform,
		std::function<Result(RootGrowNode<Number>*, Parameters<Rargs...>)> compute, 
		std::function<Result(RootGrowNode<Number>*, std::vector<Result>, Parameters<Rargs...>)> aggregate, 
		Parameters<Rargs...> initParams)
	{ 

		//constexpr bool isResultVoid = std::is_void<Result>::value;		

		//Usings
		using Node = RootGrowNode<Number>*;
		using Param = Parameters<Rargs...>;
		//using Res = typename std::conditional<isResultVoid,unsigned,Result>::type; //Result itself can already be a vector
		using Res = Result;

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
					return std::apply(compute, std::make_pair(cur, currentParam));
					
				//If leaf and not end of stack is reached	
				} else {

					resultStack.at(currentResult.first).second.emplace_back(std::apply(compute, std::make_pair(cur, currentParam)));

				}

				// delete result frame and close recursive call
				callStack.pop_back();
				paramStack.pop_back();
				resultStack.pop_back();

			} else {

				//If enough arguments for operation of node and #arguments != 0
				if(resultStack.back().second.size() == cur->getOriginCount()) {

					Res accumulatedResult = std::apply(aggregate, std::make_tuple(cur, resultStack.back().second, currentParam));

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
						paramStack.push_back(std::apply(transform, std::make_pair(cur, currentParam)));
						resultStack.push_back(std::make_pair(callingFrame, std::vector<Res>()));
					}
				}
			}
		}
		std::cout << "THIS SHOULD NOT HAPPEN." << std::endl;
		return Res();
	}
}
*/
