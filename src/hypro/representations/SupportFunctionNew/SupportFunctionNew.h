/*
 * SupportFunctionNew.h
 *
 * Class representing a SupportFunction.
 * Here, a SupportFunction is a tree where a new node is set above the new root, thus growing at the root.
 * The SupportFunction itself knows and owns the root node, which in turn knows its children and so on.
 * Note that the pointer to the root node will not be shifted when a new node is added. 
 * Through this, it is possible to query an evaluation of the operations from each node in the tree.
 * Each leaf node in this tree holds a representation of a state, i.e. a box, a V-polytope, etc.
 * Each node that is not a leaf represents an operation that is performed on its children.
 *
 * @author Stefan Schupp
 * @author Phillip Tse
 */

#pragma once

#ifndef INCL_FROM_GOHEADER
	static_assert(false, "This file may only be included indirectly by GeometricObject.h");
#endif

#include <memory>
#include "SupportFunctionNewSetting.h"
#include "../../util/linearOptimization/Optimizer.h"
#include "../../util/logging/Logger.h"
#include "Leaf.h"
#include "SumOp.h"
#include "TrafoOp.h"

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

/**
 * @brief      The class which represents a SupportFunctionNew.
 * @tparam     Number     The used number type.
 * @tparam     Converter  The used converter.
 * @tparam	   Settings   The used settings.
 * \ingroup geoState @{
 */
template <typename Number, typename Converter, class Setting>
class SupportFunctionNewT : public GeometricObject<Number, SupportFunctionNewT<Number,Converter,Setting>> {

  friend class TrafoOp<Number,Converter,Setting>;
  friend class SumOp<Number,Converter,Setting>;

  protected:

	/***************************************************************************
	 * Members
	 **************************************************************************/

  	mutable std::shared_ptr<RootGrowNode<Number>> mRoot = nullptr;

	/***************************************************************************
	 * Constructors
	 **************************************************************************/

  private:

  	//constructor for adding a new node
  	SupportFunctionNewT( const std::shared_ptr<RootGrowNode<Number>>& root ) : mRoot(root) {
  		std::cout << "SupportFunctionNewT::shared_RGN constructor, address: " << this << std::endl;
  		//mRoot->setThis(mRoot);
  	}

  public:
	/**
	 * @brief      Creates an empty SupportFunctionNew.
	 */
	SupportFunctionNewT();

	/**
	 * @brief      Copy constructor.
	 * @param[in]  orig  The original.
	 */
	SupportFunctionNewT( const SupportFunctionNewT& orig );

	/**
	 * @brief      Settings conversion constructor.
	 * @param[in]  orig  The original.
	 */
	template<typename SettingRhs, carl::DisableIf< std::is_same<Setting, SettingRhs> > = carl::dummy>
	SupportFunctionNewT(const SupportFunctionNewT<Number,Converter,SettingRhs>& orig) {

	}

	/**
	 * @brief      Move constructor.
	 * @param[in]  orig  The original.
	 */
	SupportFunctionNewT( SupportFunctionNewT&& orig );

	//leaf constructor
	template<typename Representation>
	SupportFunctionNewT( GeometricObject<Number,Representation>* r) : mRoot(std::make_shared<Leaf<Number,Representation>>(dynamic_cast<Representation*>(r))) { 
	//SupportFunctionNewT( GeometricObject<Number,Representation>* r) { 
		//Leaf<Number,Representation>* leaf = new Leaf<Number,Representation>(dynamic_cast<Representation*>(r));
		//leaf->setThis(std::shared_ptr<Leaf<Number,Representation>>(leaf));
		//mRoot = leaf->getThis();
		//std::shared_ptr<Leaf<Number,Representation>> tmp = std::make_shared<Leaf<Number,Representation>>(dynamic_cast<Representation*>(r));
		//mRoot->setThis(tmp);
		//mRoot = getThis();
		std::cout << "SupportFunctionNewT::Leaf constructor, address " << this << std::endl;
		//mRoot->setThis(mRoot);
	}

	/**
	 * @brief Destructor.
	 */
	~SupportFunctionNewT() {
		std::cout << "SupportFunctionNewT::~SupportFunctionNewT, address: " << this << std::endl;
		std::cout << "Ref count of mRoot: " << mRoot.use_count() << std::endl;	
		//mRoot ptr deleted via unique_ptr	
		//mRoot itself deleted via unique_ptr
		//mRoot->children deleted as member of mRoot
	}

	/***************************************************************************
	 * Getters & setters
	 **************************************************************************/

  private:

  	void addUnaryOp(RootGrowNode<Number>* unary) const;

  	void addBinaryOp(RootGrowNode<Number>* binary, const SupportFunctionNewT<Number,Converter,Setting>& rhs) const;

  public:

	Setting getSettings() const { return Setting{}; }

	std::shared_ptr<RootGrowNode<Number>> getRoot() const { return mRoot; }

	 /**
	  * @brief Static method for the construction of an empty SupportFunctionNew of required dimension.
	  * @param dimension Required dimension.
	  * @return Empty SupportFunctionNew.
	  */
	static SupportFunctionNewT<Number,Converter,Setting> Empty(std::size_t dimension = 1) {
		return SupportFunctionNewT<Number,Converter,Setting>();
	}

	/***************************************************************************
	 * Tree Traversal
	 **************************************************************************/
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
	void traverse(	std::function<void(RootGrowNode<Number>*)>& transform,
					std::function<void(RootGrowNode<Number>*)>& compute, 	
					std::function<void(RootGrowNode<Number>*)>& aggregate) const;

	//When Param type = void, but Result type not
	//Wrap transform and compute into other functions that take Parameter (or smth else) additionally as input
	template<typename Result>
	Result traverse(std::function<void(RootGrowNode<Number>*)>& transform,
					std::function<Result(RootGrowNode<Number>*)>& compute, 
					std::function<Result(RootGrowNode<Number>*, std::vector<Result>)>& aggregate) const;

	//When Result type = void, but Param type not
	//Wrap aggregate and compute into other functions that take Parameter (or smth else) additionally as input
	template<typename ...Rargs>
	void traverse(	std::function<Parameters<Rargs...>(RootGrowNode<Number>*, Parameters<Rargs...>)>& transform,
					std::function<void(RootGrowNode<Number>*, Parameters<Rargs...>)>& compute, 
					std::function<void(RootGrowNode<Number>*, Parameters<Rargs...>)>& aggregate,
					Parameters<Rargs...>& initParams) const;

	//Actual traverse function
	//Since all cases where Result or Rargs are void / empty are handled by the overloaded versions of this function above,
	//we can assume that we do not get functions returning void / that have no parameters
	template<typename Result, typename ...Rargs>
	Result traverse(std::function<Parameters<Rargs...>(RootGrowNode<Number>*, Parameters<Rargs...>)>& transform,
					std::function<Result(RootGrowNode<Number>*, Parameters<Rargs...>)>& compute, 
					std::function<Result(RootGrowNode<Number>*, std::vector<Result>, Parameters<Rargs...>)>& aggregate, 
					Parameters<Rargs...>& initParams) const;

	/***************************************************************************
	 * Evaluation
	 **************************************************************************/

	/**
	 * @brief Determines if the current SupportFunctionNew is empty.
	 * @return True, if SupportFunctionNew is empty. False otherwise.
	 */
	bool empty() const;

	/**
	 * @brief Method returning the supremum point of the SupportFunctionNew, i.e. the maximal point.
	 * @return A point representing the supremum of the current SupportFunctionNew.
	 */
	Number supremum() const;

	/**
	 * @brief Getter for a vertex-representation of the current SupportFunctionNew.
	 * @return A vector of points.
	 */
	std::vector<Point<Number>> vertices( const matrix_t<Number>& = matrix_t<Number>::Zero(0,0) ) const;

	/**
	 * @brief      Evaluation function (convex linear optimization).
	 * @param[in]  _direction  The direction/cost function.
	 * @return     Maximum towards _direction.
	 */
	EvaluationResult<Number> evaluate( const vector_t<Number>& _direction, bool ) const;

	/**
	 * @brief      Multi-evaluation function (convex linear optimization).
	 * @param[in]  _directions  The directions/cost functions.
	 * @return     A set of maxima towards the respective directions.
	 */
	std::vector<EvaluationResult<Number>> multiEvaluate( const matrix_t<Number>& _directions, bool useExact = true ) const;

	/**
	 * @brief 		Answers whether the tree has at least one TrafoOp with the given parameters inside and updates ltParam if needed
	 * @param[in]	ltParam 	Actually used parameters which A and b are compared to 
	 * @param[in]	A 			Matrix to compare to ltParam
	 * @param[in]	b 			Vector to compare to ltParam
	 * @return 		True if at least one TrafoOp is found in the whole subtree, else false. 
	 *				ltParam gets updated to the parameters of the found TrafoOp if A and b are the parameters of the found TrafoOp.
	 */
  	bool hasTrafo(std::shared_ptr<const LinTrafoParameters<Number>>& ltParam, const matrix_t<Number>& A, const vector_t<Number>& b) const;

	/***************************************************************************
	 * Operators
	 **************************************************************************/

	/**
	 * @brief Checks if two SupportFunctionNews are equal.
	 * @param b1 Contains the first SupportFunctionNew.
	 * @param b2 Contains the second SupportFunctionNew.
	 * @return True, if they are equal.
	 */
	template<class SettingRhs>
	friend bool operator==( const SupportFunctionNewT<Number,Converter,Setting>& b1, const SupportFunctionNewT<Number,Converter,SettingRhs>& b2 ) {
		return false;
	}

	/**
	 * @brief Determines inequality of two SupportFunctionNewes.
	 * @param b1 A SupportFunctionNew.
	 * @param b2 A SupportFunctionNew.
	 * @return False, if both SupportFunctionNewes are equal.
	 */
	friend bool operator!=( const SupportFunctionNewT<Number,Converter,Setting>& b1, const SupportFunctionNewT<Number,Converter,Setting>& b2 ) { return !( b1 == b2 ); }

	/**
	 * @brief Assignment operator.
	 * @param rhs A SupportFunctionNew.
	 */
	SupportFunctionNewT<Number,Converter,Setting>& operator=( const SupportFunctionNewT<Number,Converter,Setting>& rhs ) = default;

	/**
	 * @brief Move assignment operator.
	 * @param rhs A SupportFunctionNew.
	 */
	SupportFunctionNewT<Number,Converter,Setting>& operator=(SupportFunctionNewT<Number,Converter,Setting>&& rhs) = default;

	/**
	 * @brief Outstream operator.
	 * @param ostr Outstream.
	 * @param b A SupportFunctionNew.
	 */
#ifdef HYPRO_LOGGING
	friend std::ostream& operator<<( std::ostream& ostr, const SupportFunctionNewT<Number,Converter,Setting>& b ) {
		ostr << *(b.getRoot()) << std::endl;
#else
	friend std::ostream& operator<<( std::ostream& ostr, const SupportFunctionNewT<Number,Converter,Setting>& ) {
#endif
		return ostr;
	}

	/***************************************************************************
	 * General interface
	 **************************************************************************/

	 /**
	  * @brief      Getter for the space dimension.
	  * @return     The dimension of the space.
	  */
	std::size_t dimension() const;

	/**
	 * @brief      Removes redundancy.
	 */
	void removeRedundancy();

	/**
	 * @brief      Storage size determination.
	 * @return     Size of the required memory.
	 */
	std::size_t size() const;

	static representation_name type() { return representation_name::SFN; }

	/**
	 * @brief      Function to reduce the number representation (over-approximate).
	 * @param[in]  limit      The limit
	 */
	const SupportFunctionNewT<Number,Converter,Setting>& reduceNumberRepresentation();


	std::pair<CONTAINMENT, SupportFunctionNewT> satisfiesHalfspace( const Halfspace<Number>& rhs ) const;
	std::pair<CONTAINMENT, SupportFunctionNewT> satisfiesHalfspaces( const matrix_t<Number>& _mat, const vector_t<Number>& _vec ) const;
	SupportFunctionNewT<Number,Converter,Setting> project(const std::vector<std::size_t>& dimensions) const;
	SupportFunctionNewT<Number,Converter,Setting> linearTransformation( const matrix_t<Number>& A ) const;
	SupportFunctionNewT<Number,Converter,Setting> affineTransformation( const matrix_t<Number>& A, const vector_t<Number>& b ) const;
	SupportFunctionNewT<Number,Converter,Setting> minkowskiSum( const SupportFunctionNewT<Number,Converter,Setting>& rhs ) const;

	/**
	 * @brief      Computes the intersection of two SupportFunctionNewes.
	 * @param[in]  rhs   The right hand side SupportFunctionNew.
	 * @return     The resulting SupportFunctionNew.
	 */
	SupportFunctionNewT<Number,Converter,Setting> intersect( const SupportFunctionNewT<Number,Converter,Setting>& rhs ) const;

	SupportFunctionNewT<Number,Converter,Setting> intersectHalfspace( const Halfspace<Number>& hspace ) const;
	SupportFunctionNewT<Number,Converter,Setting> intersectHalfspaces( const matrix_t<Number>& _mat, const vector_t<Number>& _vec ) const;
	bool contains( const Point<Number>& point ) const;

	/**
	 * @brief      Containment check for a SupportFunctionNew.
	 * @param[in]  SupportFunctionNew   The SupportFunctionNew.
	 * @return     True, if the given SupportFunctionNew is contained in the current SupportFunctionNew, false otherwise.
	 */
	bool contains( const SupportFunctionNewT<Number,Converter,Setting>& SupportFunctionNew ) const;

	/**
	 * @brief      Computes the union of two SupportFunctionNewes.
	 * @param[in]  rhs   The right hand side SupportFunctionNew.
	 * @return     The resulting SupportFunctionNew.
	 */
	SupportFunctionNewT<Number,Converter,Setting> unite( const SupportFunctionNewT<Number,Converter,Setting>& rhs ) const;

	/**
	 * @brief      Computes the union of the current SupportFunctionNew with a set of SupportFunctionNewes.
	 * @param[in]  SupportFunctionNewes  The SupportFunctionNewes.
	 * @return     The resulting SupportFunctionNew.
	 */
	static SupportFunctionNewT<Number,Converter,Setting> unite( const std::vector<SupportFunctionNewT<Number,Converter,Setting>>& SupportFunctionNewes );

	/**
	 * @brief      Reduces the representation of the current SupportFunctionNew.
	 */
	void reduceRepresentation();

	/**
	 * @brief      Makes this SupportFunctionNew equal to the empty SupportFunctionNew.
	 */
	void clear();

};
/** @} */


} // namespace hypro

#include "SupportFunctionNew.tpp"
