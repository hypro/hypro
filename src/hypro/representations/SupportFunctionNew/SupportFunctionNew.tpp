#pragma once

#include "SupportFunctionNew.h"

namespace hypro {

	/***************************************************************************
	 * Constructors
	 **************************************************************************/

	template<typename Number, typename Converter, typename Setting>
	SupportFunctionNewT<Number,Converter,Setting>::SupportFunctionNewT() {

	}

	template<typename Number, typename Converter, typename Setting>
	SupportFunctionNewT<Number,Converter,Setting>::SupportFunctionNewT( const SupportFunctionNewT<Number,Converter,Setting>& orig ) {

	}

	template<typename Number, typename Converter, typename Setting>
	SupportFunctionNewT<Number,Converter,Setting>::SupportFunctionNewT( SupportFunctionNewT<Number,Converter,Setting>&& orig ) {

	}

	/***************************************************************************
	 * Getters & setters
	 **************************************************************************/

	template<typename Number, typename Converter, typename Setting>
	SupportFunctionNewT<Number,Converter,Setting>* SupportFunctionNewT<Number,Converter,Setting>::addUnaryOp(RootGrowNode<Number>* unary){
		assert(unary->getOriginCount() == 1);
			
		//Make a copy of the root ptr
		RootGrowNode<Number>* copyOfRootPtr = mRoot;

		//Add current root as child of given unary node
		unary->addToChildren(copyOfRootPtr);

		//set unary as parent of root
		copyOfRootPtr->setAsParent(unary);

		//set unary as the root
		mRoot = unary;

		return this;
	}

	template<typename Number, typename Converter, typename Setting>
	SupportFunctionNewT<Number,Converter,Setting>* SupportFunctionNewT<Number,Converter,Setting>::addBinaryOp(RootGrowNode<Number>* binary, SupportFunctionNewT<Number,Converter,Setting>* rhs){
		assert(binary->getOriginCount() == 2);
		RootGrowNode<Number>* lhsRootPtr = mRoot;
		RootGrowNode<Number>* rhsRootPtr = rhs->getRoot();
		binary->addToChildren(lhsRootPtr);
		binary->addToChildren(rhsRootPtr);
		lhsRootPtr->setAsParent(binary);
		rhsRootPtr->setAsParent(binary);
		mRoot = binary;
		rhs->setRoot(binary);
		return this;
	}
/*
	template<typename Number, typename Converter, typename Setting>
	SupportFunctionNewT<Number,Converter,Setting>* SupportFunctionNewT<Number,Converter,Setting>::addOperation(
		SupportFunctionNewT<Number,Converter,Setting>* newParent, 
		std::vector<SupportFunctionNewT<Number,Converter,Setting>*> newSiblings)
	{
		assert(newParent->getOriginCount() == newSiblings.size());
		RootGrowNode<Number>* copyOfRootPtr = mRoot;
		newParent->addToChildren(copyOfRootPtr);
		copyOfRootPtr->setAsParent(newParent);
		for(auto s : newSiblings){
			newParent->addToChildren(s);
			s->setAsParent(newParent);
		}
		return this;
	}
*/
	template<typename Number, typename Converter, typename Setting>
	SupportFunctionNewT<Number,Converter,Setting>* SupportFunctionNewT<Number,Converter,Setting>::setAsOnlyChild(RootGrowNode<Number>* child){
		mRoot->clearChildren();
		mRoot->addToChildren(child);
		child->setAsParent(mRoot);
		//Does not set mRoot as original parent
		return this;
	}

	/***************************************************************************
	 * Tree Traversal
	 **************************************************************************/

	//When Result type and Param type = void
	template<typename Number, typename Converter, typename Setting>
	void SupportFunctionNewT<Number,Converter,Setting>::traverse( 	
		std::function<void(RootGrowNode<Number>*)>& transform,
		std::function<void(RootGrowNode<Number>*)>& compute, 	
		std::function<void(RootGrowNode<Number>*)>& aggregate) const 
	{
		std::function<Parameters<>(RootGrowNode<Number>*, Parameters<>)> tNotVoid = [&](RootGrowNode<Number>* n, Parameters<> p) -> Parameters<> { transform(n); return Parameters<>(); };
		std::function<Parameters<>(RootGrowNode<Number>*, Parameters<>)> cNotVoid = [&](RootGrowNode<Number>* n, Parameters<> p) -> Parameters<> { compute(n); return Parameters<>(); };
		std::function<Parameters<>(RootGrowNode<Number>*, std::vector<Parameters<>>, Parameters<>)> aNotVoid = [&](RootGrowNode<Number>* n, std::vector<Parameters<>> v, Parameters<> p) -> Parameters<> { aggregate(n); return Parameters<>(); };
		traverse(tNotVoid, cNotVoid, aNotVoid, Parameters<>());
	}

	//When Param type = void, but Result type not
	template<typename Number, typename Converter, typename Setting>
	template<typename Result>
	Result SupportFunctionNewT<Number,Converter,Setting>::traverse(	
		std::function<void(RootGrowNode<Number>*)>& transform,
		std::function<Result(RootGrowNode<Number>*)>& compute, 
		std::function<Result(RootGrowNode<Number>*, std::vector<Result>)>& aggregate) const 
	{	
		std::function<Parameters<>(RootGrowNode<Number>*, Parameters<>)> tNotVoid = [&](RootGrowNode<Number>* n, Parameters<> ) -> Parameters<> { transform(n); return Parameters<>(); };
		std::function<Result(RootGrowNode<Number>*, Parameters<>)> cNotVoid = [&](RootGrowNode<Number>* n, Parameters<> ) -> Result { return compute(n); };
		std::function<Result(RootGrowNode<Number>*, std::vector<Result>, Parameters<>)> aWithParams = [&](RootGrowNode<Number>* n, std::vector<Result> v, Parameters<> ) -> Result { return aggregate(n,v); };
		Parameters<> noInitParams = Parameters<>();
		return traverse(tNotVoid, cNotVoid, aWithParams, noInitParams);
	}

	//When Result type = void, but Param type not
	template<typename Number, typename Converter, typename Setting>
	template<typename ...Rargs>
	void SupportFunctionNewT<Number,Converter,Setting>::traverse(	
		std::function<Parameters<Rargs...>(RootGrowNode<Number>*, Parameters<Rargs...>)>& transform,
		std::function<void(RootGrowNode<Number>*, Parameters<Rargs...>)>& compute, 
		std::function<void(RootGrowNode<Number>*, Parameters<Rargs...>)>& aggregate,
		Parameters<Rargs...>& initParams) const 
	{
		std::function<Parameters<>(RootGrowNode<Number>*, Parameters<Rargs...>)> cNotVoid = [&](RootGrowNode<Number>* n, Parameters<Rargs...> p) -> Parameters<>{ compute(n,p); return Parameters<>(); };
		std::function<Parameters<>(RootGrowNode<Number>*, std::vector<Parameters<>>, Parameters<Rargs...>)> aNotVoid = [&](RootGrowNode<Number>* n, std::vector<Parameters<>> v, Parameters<Rargs...> p) -> Parameters<> { aggregate(n,p); return Parameters<>(); };
		traverse(transform, cNotVoid, aNotVoid, initParams);
	}

	//Actual traverse function. Result type and Param type not void
	template<typename Number, typename Converter, typename Setting>
	template<typename Result, typename ...Rargs>
	Result SupportFunctionNewT<Number,Converter,Setting>::traverse(
		std::function<Parameters<Rargs...>(RootGrowNode<Number>*, Parameters<Rargs...>)>& transform,
		std::function<Result(RootGrowNode<Number>*, Parameters<Rargs...>)>& compute, 
		std::function<Result(RootGrowNode<Number>*, std::vector<Result>, Parameters<Rargs...>)>& aggregate, 
		Parameters<Rargs...>& initParams) const
	{ 
		//Usings
		using Node = RootGrowNode<Number>*;
		using Param = Parameters<Rargs...>;
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

	/***************************************************************************
	 * Evaluation
	 **************************************************************************/

	template<typename Number, typename Converter, typename Setting>
	bool SupportFunctionNewT<Number,Converter,Setting>::empty() const {
		return true;
	}

	template<typename Number, typename Converter, typename Setting>
	Number SupportFunctionNewT<Number,Converter,Setting>::supremum() const {

	}

	template<typename Number, typename Converter, typename Setting>
	std::vector<Point<Number>> SupportFunctionNewT<Number,Converter,Setting>::vertices( const matrix_t<Number>& m ) const {

	}

	template<typename Number, typename Converter, typename Setting>
	EvaluationResult<Number> SupportFunctionNewT<Number,Converter,Setting>::evaluate( const vector_t<Number>& _direction, bool ) const {

	}

	template<typename Number, typename Converter, typename Setting>
	std::vector<EvaluationResult<Number>> SupportFunctionNewT<Number,Converter,Setting>::multiEvaluate( const matrix_t<Number>& _directions, bool useExact ) const {

		//Define lambda functions that will call the functions transform, compute and aggregate dependent on the current node type
		std::function<Parameters<matrix_t<Number>>(RootGrowNode<Number>*, Parameters<matrix_t<Number>>)> trans = 
			[](RootGrowNode<Number>* n, Parameters<matrix_t<Number>> param) -> Parameters<matrix_t<Number>> { 
				return Parameters<matrix_t<Number>>(n->transform(std::get<0>(param.args))); 
			};

		std::function<std::vector<EvaluationResult<Number>>(RootGrowNode<Number>*, Parameters<matrix_t<Number>>)> comp = 
			[](RootGrowNode<Number>* n, Parameters<matrix_t<Number>> dir) -> std::vector<EvaluationResult<Number>> { 
				return n->compute(std::get<0>(dir.args)); 
			};

		std::function<std::vector<EvaluationResult<Number>>(RootGrowNode<Number>*, std::vector<std::vector<EvaluationResult<Number>>>, Parameters<matrix_t<Number>>)> agg = 
			[](RootGrowNode<Number>* n, std::vector<std::vector<EvaluationResult<Number>>> resultStackBack, Parameters<matrix_t<Number>> currentParam) -> std::vector<EvaluationResult<Number>> { 
				return n->aggregate(resultStackBack, std::get<0>(currentParam.args)); 
			};

		//Check if the functions are invocable (if not, something went wrong)
		//std::cout << "trans invocable? " << std::is_invocable_r<Parameters<matrix_t<Number>>, decltype(trans), RootGrowNode<Number>*, Parameters<matrix_t<Number>>>::value << std::endl;
		//std::cout << "comp invocable? " << std::is_invocable_r<std::vector<EvaluationResult<Number>>, decltype(comp), RootGrowNode<Number>*, Parameters<matrix_t<Number>>>::value << std::endl;
		//std::cout << "agg invocable? " << std::is_invocable_r<std::vector<EvaluationResult<Number>>, decltype(agg), RootGrowNode<Number>*, std::vector<std::vector<EvaluationResult<Number>>>, Parameters<matrix_t<Number>>>::value << std::endl;

		//Traverse the underlying SupportFunctionNewT with the three functions and given directions as initial parameters.
		Parameters<matrix_t<Number>> params = Parameters<matrix_t<Number>>(_directions);
		return traverse(trans, comp, agg, params);
	}

	//Find out if tree has at least one trafoOp and if yes, update the linTrafoParameters
	template<typename Number, typename Converter, typename Setting>
	bool SupportFunctionNewT<Number,Converter,Setting>::hasTrafo(std::shared_ptr<const LinTrafoParameters<Number>>& ltParam, const matrix_t<Number>& A, const vector_t<Number>& b){

		//first function - parameters are not transformed
		std::function<void(RootGrowNode<Number>*)> doNothing = [](RootGrowNode<Number>* ){ };

		//second function - leaves cannot be operations
		std::function<bool(RootGrowNode<Number>*)> leavesAreNotTrafoOps =
			[](RootGrowNode<Number>* ) -> bool {
				return false;
			};

		//third function - if current node type or given result is TRAFO, then update and return true
		std::function<bool(RootGrowNode<Number>*, std::vector<bool>)> checkAndUpdateTrafo =
			[&](RootGrowNode<Number>* n, std::vector<bool> haveSubtreesTrafo) -> bool {
				if(n->getType() == SFNEW_TYPE::TRAFO){
					return n->hasTrafo(ltParam, A, b);
				} else {
					for(auto hasSubTreeTrafo : haveSubtreesTrafo){
						if(hasSubTreeTrafo){
							return true;	
						} 
					}
				}
				return false;
			};

		return traverse(doNothing, leavesAreNotTrafoOps, checkAndUpdateTrafo);
	}

	/***************************************************************************
	 * General Interface
	 **************************************************************************/

	template<typename Number, typename Converter, typename Setting>
	std::size_t SupportFunctionNewT<Number,Converter,Setting>::dimension() const {
		return std::size_t(1);
	}

	template<typename Number, typename Converter, typename Setting>
	void SupportFunctionNewT<Number,Converter,Setting>::removeRedundancy() {

	}

	template<typename Number, typename Converter, typename Setting>
	std::size_t SupportFunctionNewT<Number,Converter,Setting>::size() const {
		return std::size_t(1);
	}

	template<typename Number, typename Converter, typename Setting>
	const SupportFunctionNewT<Number,Converter,Setting>& SupportFunctionNewT<Number,Converter,Setting>::reduceNumberRepresentation() {

	}

	template<typename Number, typename Converter, typename Setting>
	std::pair<CONTAINMENT, SupportFunctionNewT<Number,Converter,Setting>> SupportFunctionNewT<Number,Converter,Setting>::satisfiesHalfspace( const Halfspace<Number>& rhs ) const {

	}

	template<typename Number, typename Converter, typename Setting>
	std::pair<CONTAINMENT, SupportFunctionNewT<Number,Converter,Setting>> SupportFunctionNewT<Number,Converter,Setting>::satisfiesHalfspaces( const matrix_t<Number>& _mat, const vector_t<Number>& _vec ) const {

	}

	template<typename Number, typename Converter, typename Setting>
	SupportFunctionNewT<Number,Converter,Setting> SupportFunctionNewT<Number,Converter,Setting>::project(const std::vector<std::size_t>& dimensions) const {

	}

	template<typename Number, typename Converter, typename Setting>
	SupportFunctionNewT<Number,Converter,Setting> SupportFunctionNewT<Number,Converter,Setting>::linearTransformation( const matrix_t<Number>& A ) const {

	}

	template<typename Number, typename Converter, typename Setting>
	SupportFunctionNewT<Number,Converter,Setting> SupportFunctionNewT<Number,Converter,Setting>::affineTransformation( const matrix_t<Number>& A, const vector_t<Number>& b ) const {

	}

	template<typename Number, typename Converter, typename Setting>
	SupportFunctionNewT<Number,Converter,Setting> SupportFunctionNewT<Number,Converter,Setting>::minkowskiSum( const SupportFunctionNewT<Number,Converter,Setting>& rhs ) const {

	}

	template<typename Number, typename Converter, typename Setting>
	SupportFunctionNewT<Number,Converter,Setting> SupportFunctionNewT<Number,Converter,Setting>::intersect( const SupportFunctionNewT<Number,Converter,Setting>& rhs ) const {

	}

	template<typename Number, typename Converter, typename Setting>
	SupportFunctionNewT<Number,Converter,Setting> SupportFunctionNewT<Number,Converter,Setting>::intersectHalfspace( const Halfspace<Number>& hspace ) const {

	}

	template<typename Number, typename Converter, typename Setting>
	SupportFunctionNewT<Number,Converter,Setting> SupportFunctionNewT<Number,Converter,Setting>::intersectHalfspaces( const matrix_t<Number>& _mat, const vector_t<Number>& _vec ) const {

	}

	template<typename Number, typename Converter, typename Setting>
	bool SupportFunctionNewT<Number,Converter,Setting>::contains( const Point<Number>& point ) const {
		return true;
	}

	template<typename Number, typename Converter, typename Setting>
	bool SupportFunctionNewT<Number,Converter,Setting>::contains( const SupportFunctionNewT<Number,Converter,Setting>& SupportFunctionNew ) const {
		return true;
	}

	template<typename Number, typename Converter, typename Setting>
	SupportFunctionNewT<Number,Converter,Setting> SupportFunctionNewT<Number,Converter,Setting>::unite( const SupportFunctionNewT<Number,Converter,Setting>& rhs ) const {

	}

	template<typename Number, typename Converter, typename Setting>
	SupportFunctionNewT<Number,Converter,Setting> SupportFunctionNewT<Number,Converter,Setting>::unite( const std::vector<SupportFunctionNewT<Number,Converter,Setting>>& SupportFunctionNewes ) {

	}

	template<typename Number, typename Converter, typename Setting>
	void SupportFunctionNewT<Number,Converter,Setting>::reduceRepresentation() {

	}

	template<typename Number, typename Converter, typename Setting>
	void SupportFunctionNewT<Number,Converter,Setting>::clear() {

	}

} // namespace hypro
