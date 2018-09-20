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

	////// TRAVERSAL
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
	auto traverse(	std::function<Params(RootGrowNode*, Params)> transform,
					std::function<Result(RootGrowNode*, Params)> compute, 
					std::function<Result(RootGrowNode*, std::vector<Result>)> aggregate, 
					Params initParams){ 
/*
		- TEST VOID RETURN TYPES LATER
		- PARAM PACKS FOR LATER
		- TURN std::function TO GENERAL LATER
		- INTRODUCE STD::TUPLE LATER 
		- EXTRA PARAMS FOR OTHER FUNC LATER (COMES WITH STD::TUPLE)
		- SPECIALIZE FUNCS TO USE WITH ROOTGROWNODE* LATER <DONE>
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
		std::cout << "RGT::traverse\n";

		constexpr bool isResultVoid = std::is_void<Result>::value;
		
		//Usings
		using Node = RootGrowNode*;
		using Param = Params;
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
						std::invoke(compute, cur, currentParam);
					} else {
						return std::invoke(compute, cur, currentParam);
					}
					
				//If leaf and not end of stack is reached	
				} else {

					if(isResultVoid){
						std::invoke(compute, cur, currentParam);
						//std::apply(compute, std::tuple_cat(std::make_tuple(cur), currentParam));
					} else {
						resultStack.at(currentResult.first).second.emplace_back(std::invoke(compute, cur, currentParam)); 
						//resultStack.at(currentResult.first).second.emplace_back(std::apply(compute, std::tuple_cat(std::make_tuple(cur), currentParam)));
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
						//accumulatedResult = std::apply(aggregate, std::make_pair(cur, resultStack.back().second));
						accumulatedResult = std::invoke(aggregate, cur, resultStack.back().second);
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
						if(isResultVoid){
							std::invoke(transform, cur, currentParam);
							//std::apply(transform, std::tuple_cat(std::make_tuple(cur), currentParam));
						} else {
							paramStack.push_back(std::invoke(transform, cur, currentParam));
							//paramStack.push_back(std::apply(transform, std::tuple_cat(std::make_tuple(cur), currentParam)));	
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


