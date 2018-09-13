#include <functional>
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
	static void prepareStack(int blub){ std::cout << "preparedStack!\n" << blub << std::endl; }
	static int accumulate(float test){ std::cout << "accumulated! test is: " << int(test) << "\n"; return test; }

	////// TRAVERSAL

	template<typename RetApply, typename ...ParamApply, typename RetOther, typename ...ParamOther>
	auto traverse(	std::function<RetApply(ParamApply...)> toApply, std::tuple<ParamApply...> paramForApply,
					std::function<RetOther(ParamOther...)> toOther, std::tuple<ParamOther...> paramForOther){

		//Check if return types are actually void
		//If yes at apply, then no resultStack needs to be initialized (optimization)
		//If yes at other, then nothing happens

		std::cout << "RGT::traverse\n";

		//Usings
		const bool isRetApplyVoid = std::is_void<RetApply>::value;
		const bool isRetOtherVoid = std::is_void<RetOther>::value;

		std::cout << "isRetApplyVoid: " << isRetApplyVoid << " isRetOtherVoid: " << isRetOtherVoid;

		using Node = RootGrowNode*;
		using Param = std::tuple<ParamApply...>;
		using Res = typename std::conditional< isRetApplyVoid, std::vector<unsigned>, std::vector<RetApply> >::type;
		
		//Declare Stacks
		std::vector<Node> callStack;
		std::vector<Param> paramStack;
		std::vector<std::pair<int,std::vector<Res>>> resultStack;  

		std::cout << "Before init stack\n";

		//Initialize stacks
		callStack.push_back(mRoot);
		for(auto p : paramForApply){
			paramStack.push_back(p);
		}
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
			std::cout << "paramStack content: \n";
			for(auto p : paramStack){
				std::cout << "\t" << p.entry << std::endl;
			}
			std::cout << "resultStack size: " << resultStack.size() << std::endl;
			std::cout << "resultStack content: \n";
			for(auto r : resultStack){
				std::cout << "\t" << r.first;
				for(auto operands : r.second){
					std::cout << "\t" << "[";
					for(auto args : operands){
						std::cout << args.res << ","; 
					}
					std::cout << "]";
				}
				std::cout << "\n";
			}
			std::cout << "\n";
			std::cout << "cur type is: " << cur->getType() << std::endl;

			if(cur->getOriginCount() == 0){

				std::pair<int,std::vector<Res>> currentResult = resultStack.back();

				//If leaf and end of stack is reached
				if(currentResult.first == -1){

					if(isRetApplyVoid){
						std::apply(toApply, cur, currentParam);
					} else {
						return std::apply(toApply, cur, currentParam);	
					}
					
				//If leaf and not end of stack is reached	
				} else {

					if(isRetApplyVoid){
						std::apply(toApply, cur, currentParam);
					} else {
						resultStack.at(currentResult.first).second.emplace_back(std::apply(toApply, cur, currentParam));
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
					if(isRetApplyVoid){
						accumulatedResult = std::apply(toApply, cur, resultStack.back().second);	
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
						if(isRetOtherVoid){
							std::apply(toOther, cur, currentParam, paramForOther);
						} else {
							paramStack.push_back(std::apply(toOther, cur, currentParam, paramForOther));	
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

