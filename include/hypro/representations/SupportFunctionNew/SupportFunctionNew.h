/*
 * SupportFunctionNew.h
 *
 * Class representing a SupportFunction.
 * Here, a SupportFunction is a tree where a new node is set as the parent of the current root, thus growing at the root.
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
static_assert( false, "This file may only be included indirectly by GeometricObjectBase.h" );
#endif

#include "../../util/linearOptimization/Optimizer.h"
#include "../../util/logging/Logger.h"
#include "../../util/templateDirections.h"
#include "../helperMethods/isBox.h"
#include "RootGrowNode.h"
#include "SupportFunctionNewSetting.h"

#include <memory>

namespace hypro {

// Needed as a filler class to turn Parameters<> into Parameters<Dummy>
struct Dummy {
	friend std::ostream& operator<<( std::ostream& str, const Dummy& ) {
		str << "Dummy struct!";
		return str;
	}
};

// A struct for the parameters.
// All parameters for a std::function must be placed inside a Parameters object.
// Ensures that traversal() gets only one argument instead of 20 or 30!
// If no parameter should be inside, please insert the dummy struct, as empty parameters are broken.
template <typename... Rargs>
struct Parameters {
  public:
	std::tuple<Rargs...> args;

	Parameters() {}
	Parameters( Rargs... r )
		: args( std::make_tuple( r... ) ) {}
	Parameters( const std::tuple<Rargs...>& r )
		: args( r ) {}
	//~Parameters(){}

	std::size_t size() const {
		return std::tuple_size<std::tuple<Rargs...>>::value;
	}

	friend std::ostream& operator<<( std::ostream& str, const Parameters<Rargs...>& param ) {
		str << "Param << operator, ";
		if ( param.size() > 0 ) {
			str << "size is: " << param.size() << std::endl;
			str << std::get<0>( param.args ) << std::endl;
		} else {
			str << "param.args is empty" << std::endl;
		}
		return str;
	}
};

/**
 * @brief      The class which represents a SupportFunctionNew.
 * @tparam     Number     The used number type.
 * @tparam     Converter  The used converter.
 * @tparam	   Settings   The used settings.
 * \ingroup geoState @{
 */
template <typename Number, typename Converter, class Setting>
class SupportFunctionNewT : private GeometricObjectBase {
	/***************************************************************************
	 * Friends, Usings, typedefs
	 **************************************************************************/

	friend class SumOp<Number, Converter, Setting>;
	friend class TrafoOp<Number, Converter, Setting>;
	friend class ScaleOp<Number, Converter, Setting>;
	friend class ProjectOp<Number, Converter, Setting>;
	friend class IntersectOp<Number, Converter, Setting>;
	friend class UnionOp<Number, Converter, Setting>;
	friend class IntersectHalfspaceOp<Number, Converter, Setting>;

  public:
	// Needed for Converter.h
	typedef Setting Settings;
	typedef Number NumberType;
	static constexpr auto type_enum = representation_name::SFN;

	/***************************************************************************
	 * Members
	 **************************************************************************/

  protected:
	// A pointer of shared ownership pointing to a node in the whole tree. This node is the root for this supportfunction, the nodes above root are not known.
	mutable std::shared_ptr<RootGrowNode<Number, Converter, Setting>> mRoot = nullptr;

	// The matrix and the vector that represent the SupportFunction
	mutable matrix_t<Number> mMatrix;
	mutable vector_t<Number> mVector;

	// A flag indicating whether the template evaluation to gain mMatrix and mVector has already been used
	mutable bool mTemplateSet = false;

	/***************************************************************************
	 * Constructors
	 **************************************************************************/

  private:
	// constructor for adding a new node
	SupportFunctionNewT( const std::shared_ptr<RootGrowNode<Number, Converter, Setting>>& root );

  public:
	// Halfspace constructor
	SupportFunctionNewT( const Halfspace<Number>& hspace );

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
	 * @brief      Move constructor.
	 * @param[in]  orig  The original.
	 */
	SupportFunctionNewT( SupportFunctionNewT&& orig );

	/**
	 * @brief      Settings conversion constructor.
	 * @param[in]  orig  The original.
	 */
	template <typename SettingRhs, carl::DisableIf<std::is_same<Setting, SettingRhs>> = carl::dummy>
	SupportFunctionNewT( const SupportFunctionNewT<Number, Converter, SettingRhs>& orig );

	/**
	 * @brief      Generic Leaf constructor.
	 * @param[in]  r 	A pointer to a GeometricObject, i.e. Boxes, HPolytopes, etc.
	 */
	template <typename Representation>
	SupportFunctionNewT( const Representation& r );

	/**
	 * @brief      Matrix vector constructor
	 * @param[in]  mat 	The given matrix
	 * @param[in]  vec  The given vector
	 */
	SupportFunctionNewT( const matrix_t<Number>& mat, const vector_t<Number>& vec );

	/**
	 * @brief      Vector of halfspaces constructor
	 * @param[in]  hspaces  The vector of halfspaces
	 */
	SupportFunctionNewT( const std::vector<Halfspace<Number>>& hspaces );

	/**
	 * @brief Destructor.
	 */
	~SupportFunctionNewT() {}

	/***************************************************************************
	 * Getters & setters
	 **************************************************************************/

  public:
	/**
	 * @brief 	   Returns the Settings
	 * @return    The current settings of the SupportFunctionNew.
	 */
	inline Setting getSettings() const { return Setting{}; }

	/**
	 * @brief 	   Returns a shared pointer reference to the current root
	 * @return    A shared pointer reference to the root
	 */
	inline std::shared_ptr<RootGrowNode<Number, Converter, Setting>>& getRoot() const { return mRoot; }

	inline bool isTemplateSet() const { return mTemplateSet; }

	/**
	 * @brief Static method for the construction of an empty SupportFunctionNew of required dimension.
	 * @param dimension Required dimension.
	 * @return Empty SupportFunctionNew.
	 */
	static SupportFunctionNewT<Number, Converter, Setting> Empty() {
		return SupportFunctionNewT<Number, Converter, Setting>();
	}

	/***************************************************************************
	 * Tree Traversal
	 **************************************************************************/

  private:
	/**
	 * @brief      Connects a given node with the current root. mRoot stays the same.
	 * @param[in]  newRoot  The node to connect the current root with.
	 * @param[in]  rhs 		Possible siblings of the current root that should also be connected to newRoot
	 */
	void addOperation( RootGrowNode<Number, Converter, Setting>* newRoot ) const;
	void addOperation( RootGrowNode<Number, Converter, Setting>* newRoot, const std::vector<SupportFunctionNewT<Number, Converter, Setting>>& rhs ) const;

  public:
	/*
	 * traverse() explores all nodes beginning from the root and performs the given functions while going down/up.
	 * Three functions are needed: transform, compute and aggregate.
	 * - transform: will be called by every node and mainly transforms additional parameters
	 * - compute: will only be called once by leaf nodes and computes a result for unmodified representations such as box, V-polytope, etc.
	 * - aggregate: will only be called once by all non leaf nodes and accumulates the results of its children
	 *
	 * Order of calling:
	 * 1) From top to bottom, all nodes call transform
	 * 2) When arriving at the lowest level, leaf nodes first call transform, then call compute
	 * 3) From bottom to top, each node that is not a leaf node calls aggregate
	 *
	 * There are only four possibilities of how void functions and / or functions without parameters can be combined, such that the stack operations
	 * made during the actual traversal still remain valid:
	 * - Result = void,	Params = void:	"void transform()" 		&& "void compute()" 	&& "void aggregate()" 					&& no initParams
	 * - Result = int, 	Params = void: 	"void transform()" 		&& "int compute()"		&& "int aggregate(vector<int>)" 		&& no initParams
	 * - Result = void, Params = int:	"int transform(int)" 	&& "void compute(int)" 	&& "void aggregate(int)"				&& initParams
	 * - Result = int, 	Params = int: 	"int transform(int)" 	&& "int compute(int)" 	&& "int aggregate(vector<int>, int)" 	&& initParams
	 * If the parameter type does not exist (so, Rargs... = empty set), then additional parameters can be left out in all three functions,
	 * and if parameters would be returned, void is returned instead (i.e. transform).
	 * If the result type is void, then the vector to be aggregated for the aggregate function can be left out.
	 * Below, the four possibilites are implemented, functions returning void or having no additional parameters are wrapped into functions that return
	 * empty parameters & receive one additional parameter.
	 */

	// When Result type and Param type = void
	// Wrap given functions into other functions that take Parameter (or smth else) additionally as input
	void traverse( std::function<void( RootGrowNode<Number, Converter, Setting>* )>&& transform,
				   std::function<void( RootGrowNode<Number, Converter, Setting>* )>&& compute,
				   std::function<void( RootGrowNode<Number, Converter, Setting>* )>&& aggregate ) const;

	// When Param type = void, but Result type not
	// Wrap transform and compute into other functions that take Parameter (or smth else) additionally as input
	template <typename Result>
	Result traverse( std::function<void( RootGrowNode<Number, Converter, Setting>* )>&& transform,
					 std::function<Result( RootGrowNode<Number, Converter, Setting>* )>&& compute,
					 std::function<Result( RootGrowNode<Number, Converter, Setting>*, std::vector<Result>& )>&& aggregate ) const;

	// When Result type = void, but Param type not
	// Wrap aggregate and compute into other functions that take Parameter (or smth else) additionally as input
	template <typename... Rargs>
	void traverse( std::function<Parameters<Rargs...>( RootGrowNode<Number, Converter, Setting>*, Parameters<Rargs...>& )>&& transform,
				   std::function<void( RootGrowNode<Number, Converter, Setting>*, Parameters<Rargs...>& )>&& compute,
				   std::function<void( RootGrowNode<Number, Converter, Setting>*, Parameters<Rargs...>& )>&& aggregate,
				   Parameters<Rargs...>&& initParams ) const;

	// Actual traverse function
	// Since all cases where Result or Rargs are void / empty are handled by the overloaded versions of this function above,
	// we can assume that we do not get functions returning void / that have no parameters
	template <typename Result, typename... Rargs>
	Result traverse( std::function<Parameters<Rargs...>( RootGrowNode<Number, Converter, Setting>*, Parameters<Rargs...>& )>&& transform,
					 std::function<Result( RootGrowNode<Number, Converter, Setting>*, Parameters<Rargs...>& )>&& compute,
					 std::function<Result( RootGrowNode<Number, Converter, Setting>*, std::vector<Result>&, Parameters<Rargs...>& )>&& aggregate,
					 Parameters<Rargs...>&& initParams ) const;

	/***************************************************************************
	 * General Interface
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
	std::vector<Point<Number>> vertices( const matrix_t<Number>& = matrix_t<Number>::Zero( 0, 0 ) ) const;

	/**
	 * @brief      Evaluation function (convex linear optimization).
	 * @param[in]  _direction  The direction/cost function.
	 * @return     Maximum towards _direction.
	 */
	EvaluationResult<Number> evaluate( const vector_t<Number>& _direction, bool useExact = true ) const;

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
	bool hasTrafo( std::shared_ptr<const LinTrafoParameters<Number, Setting>>& ltParam, const matrix_t<Number>& A, const vector_t<Number>& b ) const;

	/***************************************************************************
	 * Operators
	 **************************************************************************/

	/**
	 * @brief Checks if two SupportFunctionNews are equal.
	 * @param b1 Contains the first SupportFunctionNew.
	 * @param b2 Contains the second SupportFunctionNew.
	 * @return True, if they are equal.
	 */
	template <class SettingRhs>
	friend bool operator==( const SupportFunctionNewT<Number, Converter, Setting>& b1, const SupportFunctionNewT<Number, Converter, SettingRhs>& b2 ) {
		return b1.getRoot() == b2.getRoot();
	}

	/**
	 * @brief Determines inequality of two SupportFunctionNewes.
	 * @param b1 A SupportFunctionNew.
	 * @param b2 A SupportFunctionNew.
	 * @return False, if both SupportFunctionNewes are equal.
	 */
	friend bool operator!=( const SupportFunctionNewT<Number, Converter, Setting>& b1, const SupportFunctionNewT<Number, Converter, Setting>& b2 ) { return !( b1 == b2 ); }

	/**
	 * @brief Assignment operator.
	 * @param rhs A SupportFunctionNew.
	 */
	SupportFunctionNewT<Number, Converter, Setting>& operator=( const SupportFunctionNewT<Number, Converter, Setting>& rhs ) = default;

	/**
	 * @brief Move assignment operator.
	 * @param rhs A SupportFunctionNew.
	 */
	SupportFunctionNewT<Number, Converter, Setting>& operator=( SupportFunctionNewT<Number, Converter, Setting>&& rhs ) = default;

	/**
	 * @brief Outstream operator.
	 * @param ostr Outstream.
	 * @param b A SupportFunctionNew.
	 */
	friend std::ostream& operator<<( std::ostream& ostr, const SupportFunctionNewT<Number, Converter, Setting>& b ) {
		ostr << *( b.getRoot() ) << std::endl;
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
	 * @brief      Getter for the constraint matrix
	 * @return     The constraint matrix
	 */
	matrix_t<Number> matrix() const;

	/**
	 * @brief      Getter for the offset vector
	 * @return     The offset vector
	 */
	vector_t<Number> vector() const;

	/**
	 * @brief      Removes redundancy.
	 */
	inline void removeRedundancy() {}

	/**
	 * @brief      Storage size determination.
	 * @return     Size of the required memory.
	 */
	std::size_t size() const;

	/**
	 * @brief      Getter for the class name
	 * @return     The value "SFN" of the representation_name enum
	 */
	static representation_name type() { return representation_name::SFN; }

	/**
	 * @brief      Function to reduce the number representation (over-approximate).
	 * @param[in]  limit      The limit
	 */
	inline const SupportFunctionNewT<Number, Converter, Setting>& reduceNumberRepresentation() { return *this; }

	/**
	 * @brief      Computes the region of the SupportFunction that is contained in the halfspace and how much is contained
	 * @param[in]  rhs   The halfspace to intersect with
	 * @return     How much of the current SupportFunction is contained and the resulting SupportFunctionNew
	 */
	std::pair<CONTAINMENT, SupportFunctionNewT> satisfiesHalfspace( const Halfspace<Number>& rhs ) const;
	std::pair<CONTAINMENT, SupportFunctionNewT> satisfiesHalfspaces( const matrix_t<Number>& _mat, const vector_t<Number>& _vec ) const;

	/**
	 * @brief	   Computes the projection of the SupportFunction onto the given dimensions
	 * @param[in]  dimensions  The dimensions to project onto, all other dimensions will be ignored
	 * @return 	   The projected SupportFunction
	 */
	SupportFunctionNewT<Number, Converter, Setting> projectOn( const std::vector<std::size_t>& dimensions ) const;

	SupportFunctionNewT<Number, Converter, Setting> assignIntervals( const std::map<std::size_t, carl::Interval<Number>>& ) const {
		WARN( "hypro", "Not implemented." );
		return *this;
	}

	/**
	 * @brief	   Computes a affine transformation of the SupportFunction
	 * @param[in]  A 	The transformation matrix
	 * @param[in]  b 	The transformation vector
	 * @return 	   The transformed SupportFunction
	 */
	SupportFunctionNewT<Number, Converter, Setting> linearTransformation( const matrix_t<Number>& A ) const;
	SupportFunctionNewT<Number, Converter, Setting> affineTransformation( const matrix_t<Number>& A, const vector_t<Number>& b ) const;

	/**
	 * @brief	   Computes the minkowskiSum with one or more SupportFunctionNew
	 * @param[in]  rhs   The right had side SupportFunctionNew
	 * @return 	   The resulting minkowskiSum
	 */
	SupportFunctionNewT<Number, Converter, Setting> minkowskiSum( const SupportFunctionNewT<Number, Converter, Setting>& rhs ) const;
	SupportFunctionNewT<Number, Converter, Setting> minkowskiSum( const std::vector<SupportFunctionNewT<Number, Converter, Setting>>& rhs ) const;

	/**
	 * @brief	   Scales the SupportFunctionNew by the given factor
	 * @param[in]  factor  The scaling factor
	 * @return 	   The scaled SupportFunction
	 */
	SupportFunctionNewT<Number, Converter, Setting> scale( const Number& _factor = 1 ) const;

	/**
	 * @brief      Computes the intersection of two SupportFunctionNewes.
	 * @param[in]  rhs   The right hand side SupportFunctionNew.
	 * @return     The resulting SupportFunctionNew.
	 */
	SupportFunctionNewT<Number, Converter, Setting> intersect( const SupportFunctionNewT<Number, Converter, Setting>& rhs ) const;
	SupportFunctionNewT<Number, Converter, Setting> intersect( const std::vector<SupportFunctionNewT<Number, Converter, Setting>>& rhs ) const;

	/**
	 * @brief      Computes the intersection of a SupportFunctionNew with a Halfspace.
	 * @param[in]  hspace   The Halfspace to intersect with
	 * @return     The resulting SupportFunctionNew.
	 */
	SupportFunctionNewT<Number, Converter, Setting> intersectHalfspace( const Halfspace<Number>& hspace ) const;
	SupportFunctionNewT<Number, Converter, Setting> intersectHalfspaces( const matrix_t<Number>& _mat, const vector_t<Number>& _vec ) const;

	/**
	 * @brief      Containment check for a point.
	 * @param[in]  point 	The point to check containment for.
	 * @return     True, if the given point is contained in the current SupportFunctionNew, false otherwise.
	 */
	bool contains( const vector_t<Number>& point ) const;
	bool contains( const Point<Number>& point ) const;

	/**
	 * @brief      Checks whether a given SupportFunction is fully contained in the current SupportFunctionNew
	 * @param[in]  SupportFunctionNew   The SupportFunctionNew.
	 * @return     True, if the given SupportFunctionNew is contained in the current SupportFunctionNew, false otherwise.
	 */
	bool contains( const SupportFunctionNewT<Number, Converter, Setting>& rhs ) const;
	bool contains( const SupportFunctionNewT<Number, Converter, Setting>& rhs, std::size_t directions ) const;

	/**
	 * @brief      Computes the union of two SupportFunctionNewes.
	 * @param[in]  rhs   The right hand side SupportFunctionNew.
	 * @return     The resulting SupportFunctionNew.
	 */
	SupportFunctionNewT<Number, Converter, Setting> unite( const SupportFunctionNewT<Number, Converter, Setting>& rhs ) const;

	/**
	 * @brief      Computes the union of the current SupportFunctionNew with a set of SupportFunctionNewes.
	 * @param[in]  SupportFunctionNewes  The SupportFunctionNewes.
	 * @return     The resulting SupportFunctionNew.
	 */
	SupportFunctionNewT<Number, Converter, Setting> unite( const std::vector<SupportFunctionNewT<Number, Converter, Setting>>& rhs ) const;

	/**
	 * @brief      Reduces the representation of the current SupportFunctionNew.
	 */
	void reduceRepresentation();

	/**
	 * @brief      Makes this SupportFunctionNew equal to the empty SupportFunctionNew.
	 */
	inline void clear();

	/**
	 * @brief	   Traverses the tree and computes dimensions remaining after all projection operations considered.
	 * @return 	   A vector containing the indices of the dimensions remaining
	 */
	std::vector<std::size_t> collectProjections() const;

	/**
	 * @brief	   Get the matrix vector representation of the current SupportFunctionNew
	 * @param[in]  directionCount  Number of directions to be evaluated
	 * @param[in]  force  		   Whether this should be done although a matrix vector representation is already cached
	 */
	void evaluateTemplate( std::size_t directionCount = defaultTemplateDirectionCount, bool force = false ) const;
};
/** @} */

}  // namespace hypro

#include "SupportFunctionNew.tpp"
