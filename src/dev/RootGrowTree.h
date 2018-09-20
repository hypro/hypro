#include <functional>
#include <cassert>
#include "RootGrowNode.h"



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

	////// IMPORTANT: These are not the actual stack handling functions. Only needed for testing  //////

	static void test(){ std::cout << "test successful\n"; }

	static void prepareStack(int blub){ std::cout << "preparedStack! received parameter: \n" << blub << std::endl; }
	static void accumulate(float test){ std::cout << "accumulated! test is: " << test << "\n"; }
	static int f(int blub){std::cout << "f! received parameter: \n" << blub << std::endl; return blub; }

	////// TRAVERSAL
/*
	template<typename RetTrafo, typename ParamTrafo>
	auto traverseTest(std::function<RetTrafo(ParamTrafo)> transform, ParamTrafo paramsForTrafo){
		std::cout << "in traverseTest with 2 params!\n";
		std::invoke(transform, paramsForTrafo);		
	}
*/
/*	
	template<typename RetTrafo, typename ParamTrafo,
			 typename RetComp, typename ParamComp,
			 typename RetAgg, typename ParamAgg>
	auto traverseTest(	std::function<RetTrafo(ParamTrafo)> transform, ParamTrafo paramsForTrafo,
						std::function<RetComp(ParamComp)> compute, ParamComp paramsForComp,
						std::function<RetAgg(ParamAgg)> aggregate, ParamAgg paramsForAgg){ }
*/
	template<typename A, typename B>
	bool isReturnTypeVoid(std::function<A(B)> ){
		return std::is_void<A(B)>::value;
	}

	template<typename A>
	bool isReturnTypeVoid(std::function<A()> ){
		return std::is_void<A()>::value;
	}
/*
	template<typename RetTrafo, typename ParamTrafo,
			 typename RetComp, typename ParamComp,
			 typename RetAgg, typename ParamAgg>
	auto traverseTest(	std::function<RetTrafo(ParamTrafo)> transform, ParamTrafo paramsForTrafo,
						std::function<RetComp(ParamComp)> compute, ParamComp paramsForComp,
						std::function<RetAgg(ParamAgg)> aggregate, ParamAgg paramsForAgg){
*/
/*
	template<typename RetTrafo, typename ParamTrafo,
			 typename RetComp, typename ParamComp,
			 typename RetAgg, typename ParamAgg, typename Params>
	auto traverseTest(	std::function<RetTrafo(RootGrowNode*, ParamTrafo)> transform,
						std::function<RetComp(RootGrowNode*, ParamComp)> compute, 
						std::function<RetAgg(RootGrowNode*, ParamAgg)> aggregate, 
						Params initParams){ 
*/
	template<typename Params, typename Result>
	auto traverseTest(	std::function<Params(RootGrowNode*, Params)> transform,
						std::function<Result(RootGrowNode*, Params)> compute, 
						std::function<Result(RootGrowNode*, std::vector<Result>)> aggregate, 
						Params initParams){ 
/*
		- IGNORE VOID RETURN TYPES FOR LATER
		- IGNORE PARAM PACKS FOR LATER
		- TURN std::function TO GENERAL LATER
		- INTRODUCE STD::TUPLE LATER
		- EXTRA PARAMS FOR OTHER FUNC LATER
		- SPECIALIZE FUNCS TO USE WITH ROOTGROWNODE* LATER

		//constexpr bool isRetTrafoVoid = std::is_void<RetTrafo>::value;
		//constexpr bool isRetCompVoid = std::is_void<RetComp>::value;
		//constexpr bool isRetAggVoid = std::is_void<RetAgg>::value;
		//constexpr bool isRetTrafoVoid = std::is_void<std::invoke_result<decltype(g)>::type>::value;
		constexpr bool isRetTrafoVoid = isReturnTypeVoid(transform);
		constexpr bool isRetCompVoid = isReturnTypeVoid(compute);
		constexpr bool isRetAggVoid = isReturnTypeVoid(aggregate);

		std::cout << "isRetCompVoid: " << isRetCompVoid << " isRetTrafoVoid: " << isRetTrafoVoid << " isRetAggVoid: " << isRetAggVoid << std::endl;
*/

		std::cout << "RGT::traverse\n";

		constexpr bool isResultVoid = std::is_void<Result>::value;
		
		//Usings
		using Node = RootGrowNode*;
		using Param = Params;
		using chooseResType = typename std::conditional<isResultVoid,unsigned,Result>::type;
		using Res = typename std::vector<chooseResType>; //std::vector<EvalResults>

		std::cout << "isResultVoid: " << isResultVoid << std::endl;		

		//Prepare Stacks
		std::vector<Node> callStack;
		std::vector<Param> paramStack;
		std::vector<std::pair<int,std::vector<Res>>> resultStack;  
		callStack.push_back(mRoot);
		paramStack.push_back(initParams);
		resultStack.push_back(std::make_pair(-1, std::vector<Res>()));
/*
		std::cout << "in traverseTest! with 4 params!\n";
		std::invoke(transform, callStack.back(), initParams);
		std::cout << "executed transform!\n";
		std::invoke(compute, callStack.back(), initParams);
		std::cout << "executed compute!\n";
		std::invoke(aggregate, callStack.back(), 0.0f);
*/

		//Traversal loop
		while(!callStack.empty()){

			Node cur = callStack.back();
			Param currentParam = paramStack.back();

			if(cur->getOriginCount() == 0){

				std::pair<int,std::vector<Res>> currentResult = resultStack.back();

				//If leaf and end of stack is reached
				if(currentResult.first == -1){

					if(isResultVoid){
						std::invoke(compute, cur, currentParam);
						//std::apply(compute, std::tuple_cat(std::make_tuple(cur), currentParam));
						//std::apply(toApply, cur, currentParam);
					} else {
						return std::invoke(compute, cur, currentParam);
						//return std::apply(compute, std::tuple_cat(std::make_tuple(cur), currentParam));
						//return std::apply(toApply, cur, currentParam);	
					}
					
				//If leaf and not end of stack is reached	
				} else {

					if(isResultVoid){
						std::invoke(compute, cur, currentParam);
						//std::apply(toApply, cur, currentParam);
						//std::apply(compute, std::tuple_cat(std::make_tuple(cur), currentParam));
					} else {
						resultStack.at(currentResult.first).second.emplace_back(std::invoke(compute, cur, currentParam));
						//resultStack.at(currentResult.first).second.emplace_back(std::apply(toApply, cur, currentParam));
						//resultStack.at(currentResult.first).second.emplace_back(std::apply(compute, std::tuple_cat(std::make_tuple(cur), currentParam)));
					}

				}

				// delete result frame and close recursive call
				callStack.pop_back();
				paramStack.pop_back();
				resultStack.pop_back();

			} //else {
		}

	}
/*
	template<typename RetTrafo, typename ParamTrafo,
			 typename RetComp, typename ParamComp,
			 typename RetAgg, typename ParamAgg>
	auto traverseTest( 	RetTrafo transform, ParamTrafo paramsForTrafo,
						RetComp compute, ParamComp paramsForComp,
						RetAgg aggregate, ParamAgg paramsForAgg ){
*/
/*
	template<typename RetTrafo, typename RetComp, typename RetAgg, typename Params>
	auto traverseTest( 	RetTrafo transform,
						RetComp compute, 
						RetAgg aggregate, Params initParams ){

		//Check if return types are actually void
		//If yes at aggregate and compute, then no resultStack needs to be initialized (optimization)
		//If yes at other, then nothing happens

		std::cout << "RGT::traverse\n";

		//Usings
		constexpr bool isRetTrafoVoid = std::is_void<RetTrafo>::value;
		constexpr bool isRetCompVoid = std::is_void<decltype(std::result_of<RetComp(Params)>::type)>::value;
		constexpr bool isRetAggVoid = std::is_void<RetAgg>::value;
		constexpr bool isRetCompFct = std::is_invocable<decltype(compute), Params>::value;

		std::cout << "isRetCompVoid: " << isRetCompVoid << " isRetTrafoVoid: " << isRetTrafoVoid << " isRetAggVoid: " << isRetAggVoid << std::endl;
		std::cout << "isRetCompFct: " << isRetCompFct << std::endl;

		using Node = RootGrowNode*;
		using Param = Params;
		using Res = typename std::conditional<isRetCompFct, std::vector<decltype(compute)>, std::vector<unsigned>>::type ; 
*/

/*
		if(std::is_void<RetTrafo>::value){
			std::invoke(transform, paramsForTrafo);
		} else {
			return std::invoke(transform, paramsForTrafo);	
		}

		std::cout << "executed transform!\n";
		if(std::is_void<RetComp>::value){
			std::invoke(compute, paramsForComp);
		} else {
			return std::invoke(compute, paramsForComp);	
		}
*/

/*
	//template<typename RetApply, typename ParamApply, typename RetOther, typename ParamOther>
	//auto traverse( RetApply toApply, std::tuple<ParamApply> paramForApply, RetOther toOther, std::tuple<ParamOther> paramForOther){

	template<	typename RetTrafo, typename ParamTrafo,
				typename RetComp, typename ParamComp, 
				typename RetAgg, typename ParamAgg,
				typename Params >
	//template<typename RetTrafo, typename RetComp, typename RetAgg, typename Params>
	auto traverse(	std::function<RetTrafo(RootGrowNode*, ParamTrafo)> transform, //transform gets no additional params for now
					std::function<RetComp(RootGrowNode*, ParamComp)> compute, //std::tuple<ParamComp>& paramForComp,
					std::function<RetAgg(RootGrowNode*, ParamAgg)> aggregate, //std::tuple<ParamAgg>& paramForAgg ){
					std::tuple<Params>& initParams){

		//Check if return types are actually void
		//If yes at aggregate and compute, then no resultStack needs to be initialized (optimization)
		//If yes at other, then nothing happens

		std::cout << "RGT::traverse\n";

		//Usings
		constexpr bool isRetTrafoVoid = std::is_void<RetTrafo>::value;
		constexpr bool isRetCompVoid = std::is_void<RetComp>::value;
		constexpr bool isRetAggVoid = std::is_void<RetAgg>::value;

		std::cout << "isRetCompVoid: " << isRetCompVoid << " isRetTrafoVoid: " << isRetTrafoVoid << " isRetAggVoid: " << isRetAggVoid << std::endl;

		using Node = RootGrowNode*;
		using Param = std::tuple<Params>;
		using Res = typename std::conditional<(isRetAggVoid && isRetCompVoid), std::vector<unsigned>, RetComp >::type; //oder isRetCompVoid?
		
		//Declare Stacks
		std::vector<Node> callStack;
		std::vector<Param> paramStack;
		std::vector<std::pair<int,std::vector<Res>>> resultStack;  

		std::cout << "Before init stack\n";

		//Initialize stacks
		callStack.push_back(mRoot);
		paramStack.push_back(initParams);
		resultStack.push_back(std::make_pair(-1, std::vector<Res>()));

		std::cout << "After init stack\n";

		//Traversal loop
		while(!callStack.empty()){

			Node cur = callStack.back();
			Param currentParam = paramStack.back();

			//Only printing stuff
			std::cout << "=== START EVALUATION\n";
			std::cout << "callStack size: " << callStack.size() << std::endl;
			std::cout << "paramStack size: " << paramStack.size() << std::endl;
			//std::cout << "paramStack content: \n";
			//for(auto p : paramStack){
			//	std::cout << "\t" << p.entry << std::endl;
			//}
			std::cout << "resultStack size: " << resultStack.size() << std::endl;
			//std::cout << "resultStack content: \n";
			//for(auto r : resultStack){
			//	std::cout << "\t" << r.first;
			//	for(auto operands : r.second){
			//		std::cout << "\t" << "[";
			//		for(auto args : operands){
			//			std::cout << args << ","; 
			//		}
			//		std::cout << "]";
			//	}
			//	std::cout << "\n";
			//}
			//std::cout << "\n";
			std::cout << "cur type is: " << cur->getType() << std::endl;

			if(cur->getOriginCount() == 0){

				std::pair<int,std::vector<Res>> currentResult = resultStack.back();

				//If leaf and end of stack is reached
				if(currentResult.first == -1){

					if(isRetCompVoid){
						std::apply(compute, std::tuple_cat(std::make_tuple(cur), currentParam));
						//std::apply(toApply, cur, currentParam);
					} else {
						return std::apply(compute, std::tuple_cat(std::make_tuple(cur), currentParam));
						//return std::apply(toApply, cur, currentParam);	
					}
					
				//If leaf and not end of stack is reached	
				} else {

					if(isRetCompVoid){
						//std::apply(toApply, cur, currentParam);
						std::apply(compute, std::tuple_cat(std::make_tuple(cur), currentParam));
					} else {
						//resultStack.at(currentResult.first).second.emplace_back(std::apply(toApply, cur, currentParam));
						resultStack.at(currentResult.first).second.emplace_back(std::apply(compute, std::tuple_cat(std::make_tuple(cur), currentParam)));
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

					if(!isRetAggVoid){
						//accumulatedResult = std::apply(toApply, cur, resultStack.back().second);	
						//accumulatedResult = std::apply(aggregate, std::make_pair(cur, resultStack.back().second));
						if(std::is_reference<decltype(cur)>::value){
							accumulatedResult = std::invoke(aggregate, static_cast<std::remove_reference<decltype(cur)>::type>(cur), resultStack.back().second);
						} else {
							std::cout << "is cur reference? " << std::is_reference<decltype(cur)>::value << std::endl;
						}	
					}

					// we reached the top, exit
					if(resultStack.back().first == -1) {
						std::cout << "accumulatedResult: ["; 
						for(unsigned i=0; i<accumulatedResult.size(); i++){
							std::cout << accumulatedResult.at(i).res << ",";	
						}
						std::cout << "]\n";
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
						if(isRetTrafoVoid){
							//std::apply(toOther, cur, currentParam, paramForOther);
							std::apply(transform, std::tuple_cat(std::make_tuple(cur), currentParam));
						} else {
							//paramStack.push_back(std::apply(toOther, cur, currentParam, paramForOther));
							paramStack.push_back(std::apply(transform, std::tuple_cat(std::make_tuple(cur), currentParam)));	
						}
						resultStack.push_back(std::make_pair(callingFrame, std::vector<Res>()));
					}
				}
			}
		}

		std::cout << "THIS SHOULD NOT HAPPEN." << std::endl;
		return Res();
	}

*/
};


