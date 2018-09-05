#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <functional>
#include <type_traits>
#include <tuple>

//Type of nodes. Needed to fast determine which node subclass is actually calling a function. 
enum SF_TYPE { NONE = 0, TRAFO, SUM, LEAF };

//Pseudo EvaluationResult
struct EvalResult
{
	int res;
	EvalResult(int r) : res(r) {}

	friend std::ostream& operator<<(std::ostream& ostr, const EvalResult& e){
		ostr << e.res << std::endl;
		return ostr;
	}

	friend EvalResult operator+ (const EvalResult& lhs, const EvalResult& rhs){
		int tmp = lhs.res + rhs.res;
		return EvalResult(tmp); 
	}
};

//Pseudo matrix_t
struct Matrix
{
	int entry;
	Matrix(int m) : entry(m) {}
};

//A node in the tree. Knows its children and its height in the tree.
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

/*	
	////// Hidden Structs for Evaluation (needed since virtual templated functions like evaluate not possible)

	//Abstract class that knows that there is an evaluate function
	struct EvalConcept {
		virtual ~EvalConcept() = default;
		virtual EvalResult evaluate() = 0;
		//Possibly other virtual functions here
	}

	//Class that connects the possible different types via templates
	//with the virtual functions defined in EvalConcept
	template<typename Node>
	struct EvalModel : EvalConcept {
		Node evaluatable;
		EvalModel(Node n) : evaluatable(std::move(n)) {}
		EvalResult evaluate(Marix param){ n.evaluate(param); }
	}

	//RootGrowNode holds a pointer to EvalConcept
	std::unique_ptr<EvalConcept> mSelf;
*/
public:

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

	unsigned getHeight() const { return mHeight; }
	std::vector<RootGrowNode*> getChildren() const { return mChildren; }
	bool isItUnary() const { return mUnary; }
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

	template<typename Ret, typename ...Param>
	auto execute(std::function<Ret(Param...)> pre, std::tuple<Param...> param){
		if(std::is_void<Ret>::value){
			std::apply(pre, param);
		} else {
			return std::apply(pre, param);
		}
	}

	template<typename RetPre, typename ...ParamPre, typename RetIn, typename ...ParamIn, typename RetPost, typename ...ParamPost>
	auto traverse(	std::function<RetPre(ParamPre...)> pre,		std::tuple<ParamPre...> paramPre, 
					std::function<RetIn(ParamIn...)> in, 		std::tuple<ParamIn...> paramIn,
					std::function<RetPost(ParamPost...)> post, 	std::tuple<ParamPost...> paramPost){
		execute<RetPre,ParamPre...>(pre, paramPre);
		execute<RetIn,ParamIn...>(in, paramIn);
		execute<RetPost,ParamPost...>(post, paramPost);
	}

	virtual EvalResult evaluate(Matrix m) { return EvalResult(m.entry); }
	
};