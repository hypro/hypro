/*
 * TemplatePolyhedron.h
 *
 * Class representing a bounded template polyhedron.
 * Each polyhedron made from this class will have the same constraint matrix, until it is explicitly changed.
 * However, the offsets can be shifted around freely.
 * In this general version, each constraint can be a linear constraint.
 *
 * @author Phillip Tse
 * @date 1.4.2019
 */

#pragma once

#ifndef INCL_FROM_GOHEADER
static_assert( false, "This file may only be included indirectly by GeometricObjectBase.h" );
#endif

#include "../../util/linearOptimization/Optimizer.h"
#include "../../util/logging/Logger.h"
#include "../../util/templateDirections.h"
#include "TemplatePolyhedronSetting.h"

#include <iostream>
#include <memory>

namespace hypro {

/**
 * @brief      The class which represents a TemplatePolyhedron.
 * @tparam     Number     The used number type.
 * @tparam     Converter  The used converter.
 * @tparam	   Settings   The used settings.
 * \ingroup geoState @{
 */
template <typename Number, typename Converter, class Setting>
class TemplatePolyhedronT : private GeometricObjectBase {
  private:
  public:
	// Needed for Converter
	typedef Setting Settings;
	typedef Number NumberType;
	static constexpr auto type_enum = representation_name::polytope_t;

  protected:
	/***************************************************************************
	 * Members
	 **************************************************************************/

	// The constraint matrix which is the same for every polyhedron until explicitly changed.
	std::shared_ptr<const matrix_t<Number>> mMatrixPtr = nullptr;

	// The offset vector, different for each instance of this class
	vector_t<Number> mVector;

	// Optimizer as member since needed in different functions
	Optimizer<Number> mOptimizer;

	// Flag whether current TPoly has no unnecessary constraints - saves computation time
	bool mNonRedundant = false;

	// Flag whether emptiness has been tested and if it was empty or not
	// mutable TRIBOOL mEmpty = TRIBOOL::NSET;

	/***************************************************************************
	 * Constructors
	 **************************************************************************/

  private:
	/**
	 * @brief      Shared ptr to matrix and Vector constructor.
	 * @param[in]  matPtr 	The shared ptr to the matrix
	 * @param[in]  vec  	The vector
	 * @details    Constructs a copy of the shared ptr to the matrix, so all TemplatePolyhedra can share the same matrix
	 */
	TemplatePolyhedronT( const std::shared_ptr<const matrix_t<Number>>& matPtr, const vector_t<Number>& vec, const bool isNonRedundant );

  public:
	/**
	 * @brief      Creates an empty TemplatePolyhedron.
	 */
	TemplatePolyhedronT();

	/**
	 * @brief      Regular template polyhedron constructor.
	 * @param[in]  dimension  Dimension of the space the template polyhedron will reside in
	 * @param[in]  noOfSides  amount of constraints the polyhedron should consist of.
	 * 			   Must be at least dimension+1 .
	 */
	TemplatePolyhedronT( const std::size_t dimension, const std::size_t noOfSides, const vector_t<Number>& vec = vector_t<Number>::Zero( 1 ) );

	/**
	 * @brief      Matrix Vector constructor.
	 * @param[in]  mat 	The matrix
	 * @param[in]  vec  The vector
	 * @details    Constructs a shared_ptr to a copy of the matrix allocated on the heap
	 */
	TemplatePolyhedronT( const matrix_t<Number>& mat, const vector_t<Number>& vec );

	/**
	 * @brief      Vector of matrices and vectors constructor.
	 * @param[in]  matVecPairs  The vector of pairs of matrices and vectors
	 * @details    Used to construct a template polyhedron using initial constraints, location invariants and guards
	 */
	TemplatePolyhedronT( const std::vector<std::pair<matrix_t<Number>, vector_t<Number>>>& matVecPairs );

	/**
	 * @brief      Copy constructor.
	 * @param[in]  orig  The original.
	 */
	TemplatePolyhedronT( const TemplatePolyhedronT& orig );

	/**
	 * @brief      Settings conversion constructor.
	 * @param[in]  orig  The original.
	 */
	template <typename SettingRhs, carl::DisableIf<std::is_same<Setting, SettingRhs>> = carl::dummy>
	TemplatePolyhedronT( const TemplatePolyhedronT<Number, Converter, SettingRhs>& orig );

	/**
	 * @brief      Move constructor.
	 * @param[in]  orig  The original.
	 */
	TemplatePolyhedronT( TemplatePolyhedronT&& orig );

	/**
	 * @brief Destructor.
	 */
	~TemplatePolyhedronT() {}

	/***************************************************************************
	 * Getters & setters
	 **************************************************************************/

	/**
	 * @brief Getter for constraint matrix
	 * @return The constraint matrix
	 */
	inline matrix_t<Number> matrix() const { return *mMatrixPtr; }

	std::shared_ptr<const matrix_t<Number>> rGetMatrixPtr() const { return mMatrixPtr; }

	SETSTATE getEmptyFlag() const { return mEmptyState; }

	bool getNonRedundant() const { return mNonRedundant; }

	Optimizer<Number>& getOptimizer() { return mOptimizer; }

	/**
	 * @brief Getter for offset vecor
	 * @return The offset vector
	 */
	inline vector_t<Number> vector() const { return mVector; }

	void setVector( const vector_t<Number>& vec ) {
		assert( ( ( vec.rows() == mMatrixPtr->rows() ) && mMatrixPtr != nullptr ) || mMatrixPtr == nullptr );
		mNonRedundant = false;
		mEmptyState = SETSTATE::UNKNOWN;
		mVector = vec;
		mOptimizer.setVector( vec );
	}

	/**
	 * @brief Getter for the settings
	 * @return The settings
	 */
	inline Setting getSettings() const { return Setting{}; }

	/***************************************************************************
	 * Geometric Object Interface
	 **************************************************************************/

	/**
	 * @brief Static method for the construction of an empty TemplatePolyhedron of required dimension.
	 * @param dimension Required dimension.
	 * @return Empty TemplatePolyhedron, with empty meaning it is an unfeasible inequation set.
	 */
	static TemplatePolyhedronT<Number, Converter, Setting> Empty( std::size_t dimension = 1 ) {
		if ( dimension == 0 ) return TemplatePolyhedronT<Number, Converter, Setting>();
		matrix_t<Number> zeroMat = matrix_t<Number>::Zero( 1, dimension );
		vector_t<Number> zeroVec = -1 * vector_t<Number>::Ones( 1 );
		return TemplatePolyhedronT<Number, Converter, Setting>( std::move( zeroMat ), std::move( zeroVec ) );
	}

	/**
	 * @brief Determines if the current TemplatePolyhedron is empty.
	 * @return True, if TemplatePolyhedron is empty. False otherwise.
	 */
	bool empty() const;

	/**
	 * @brief Method returning the supremum point of the TemplatePolyhedron, i.e. the maximal point.
	 * @return A point representing the supremum of the current TemplatePolyhedron.
	 */
	Number supremum() const;

	/**
	 * @brief Getter for a vertex-representation of the current TemplatePolyhedron.
	 * @return A vector of points.
	 */
	std::vector<Point<Number>> vertices( const matrix_t<Number>& = matrix_t<Number>::Zero( 0, 0 ) ) const;

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
	 * @brief Checks if two TemplatePolyhedrons are equal.
	 * @param b1 Contains the first TemplatePolyhedron.
	 * @param b2 Contains the second TemplatePolyhedron.
	 * @return True, if they are equal.
	 */
	template <class SettingRhs>
	friend bool operator==( const TemplatePolyhedronT<Number, Converter, Setting>& b1, const TemplatePolyhedronT<Number, Converter, SettingRhs>& b2 ) {
		return ( b1.rGetMatrixPtr() == nullptr && b2.rGetMatrixPtr() == nullptr ) || ( b1.matrix() == b2.matrix() && b1.vector() == b2.vector() );
	}

	/**
	 * @brief Determines inequality of two TemplatePolyhedrones.
	 * @param b1 A TemplatePolyhedron.
	 * @param b2 A TemplatePolyhedron.
	 * @return False, if both TemplatePolyhedrones are equal.
	 */
	friend bool operator!=( const TemplatePolyhedronT<Number, Converter, Setting>& b1, const TemplatePolyhedronT<Number, Converter, Setting>& b2 ) {
		return !( b1 == b2 );
	}

	/**
	 * @brief Assignment operator.
	 * @param rhs A TemplatePolyhedron.
	 */
	TemplatePolyhedronT<Number, Converter, Setting>& operator=( const TemplatePolyhedronT<Number, Converter, Setting>& rhs ) = default;

	/**
	 * @brief Move assignment operator.
	 * @param rhs A TemplatePolyhedron.
	 */
	TemplatePolyhedronT<Number, Converter, Setting>& operator=( TemplatePolyhedronT<Number, Converter, Setting>&& rhs ) = default;

	/**
	 * @brief Outstream operator.
	 * @param ostr Outstream.
	 * @param b A TemplatePolyhedron.
	 */
#ifdef HYPRO_LOGGING
	friend std::ostream& operator<<( std::ostream& out_stream, const TemplatePolyhedronT<Number, Converter, Setting>& b ) {
		out_stream << "Mat Addr: " << b.rGetMatrixPtr() << "\n";
		out_stream << "Mat:\n"
				   << b.matrix();
		out_stream << "Vec:\n"
				   << b.vector();
#else
	friend std::ostream& operator<<( std::ostream& out_stream, const TemplatePolyhedronT<Number, Converter, Setting>& ) {
#endif
		return out_stream;
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
	 * @brief      Removes redundancy. Removes all constraints that do not help in defining the set of satisfying points.
	 */
	void removeRedundancy();

	/**
	 * @brief      Storage size determination.
	 * @return     Size of the required memory.
	 */
	std::size_t size() const;

	static representation_name type() { return representation_name::polytope_t; }

	/**
	 * @brief      Function to reduce the number representation (over-approximate).
	 * @param[in]  limit      The limit
	 */
	const TemplatePolyhedronT<Number, Converter, Setting>& reduceNumberRepresentation();

	std::pair<CONTAINMENT, TemplatePolyhedronT> satisfiesHalfspace( const Halfspace<Number>& rhs ) const;
	std::pair<CONTAINMENT, TemplatePolyhedronT> satisfiesHalfspaces( const matrix_t<Number>& _mat, const vector_t<Number>& _vec ) const;

	// NOTE: Probably changes the template matrix
	TemplatePolyhedronT<Number, Converter, Setting> projectOn( const std::vector<std::size_t>& dimensions ) const;

	TemplatePolyhedronT<Number, Converter, Setting> linearTransformation( const matrix_t<Number>& A ) const;
	TemplatePolyhedronT<Number, Converter, Setting> affineTransformation( const matrix_t<Number>& A, const vector_t<Number>& b ) const;
	TemplatePolyhedronT<Number, Converter, Setting> minkowskiSum( const TemplatePolyhedronT<Number, Converter, Setting>& rhs ) const;

	/**
	 * @brief      Computes the intersection of two TemplatePolyhedrones.
	 * @param[in]  rhs   The right hand side TemplatePolyhedron.
	 * @return     The resulting TemplatePolyhedron.
	 */
	TemplatePolyhedronT<Number, Converter, Setting> intersect( const TemplatePolyhedronT<Number, Converter, Setting>& rhs ) const;

	TemplatePolyhedronT<Number, Converter, Setting> intersectHalfspace( const Halfspace<Number>& hspace ) const;
	TemplatePolyhedronT<Number, Converter, Setting> intersectHalfspaces( const matrix_t<Number>& _mat, const vector_t<Number>& _vec ) const;
	bool contains( const Point<Number>& point ) const;

	/**
	 * @brief      Containment check for a TemplatePolyhedron.
	 * @param[in]  TemplatePolyhedron   The TemplatePolyhedron.
	 * @return     True, if the given TemplatePolyhedron is contained in the current TemplatePolyhedron, false otherwise.
	 */
	bool contains( const TemplatePolyhedronT<Number, Converter, Setting>& TemplatePolyhedron ) const;

	/**
	 * @brief      Computes the union of two TemplatePolyhedrones.
	 * @param[in]  rhs   The right hand side TemplatePolyhedron.
	 * @return     The resulting TemplatePolyhedron.
	 */
	TemplatePolyhedronT<Number, Converter, Setting> unite( const TemplatePolyhedronT<Number, Converter, Setting>& rhs ) const;

	/**
	 * @brief      Computes the union of the current TemplatePolyhedron with a set of TemplatePolyhedrones.
	 * @param[in]  TemplatePolyhedrones  The TemplatePolyhedrones.
	 * @return     The resulting TemplatePolyhedron.
	 */
	// static TemplatePolyhedronT<Number,Converter,Setting> unite( const std::vector<TemplatePolyhedronT<Number,Converter,Setting>>& TemplatePolyhedrones );
	TemplatePolyhedronT<Number, Converter, Setting> unite( const std::vector<TemplatePolyhedronT<Number, Converter, Setting>>& TemplatePolyhedrones );

	/**
	 * @brief      Reduces the representation of the current TemplatePolyhedron. Removes all doubled normal directions,
	 */
	void reduceRepresentation();

	/**
	 * @brief      Makes this TemplatePolyhedron equal to the empty TemplatePolyhedron.
	 */
	void clear();

	TemplatePolyhedronT<Number, Converter, Setting> assignIntervals( const std::map<std::size_t, carl::Interval<Number>>& /*assignments*/ ) const {
		WARN( "hypro", "Not implemented." );
		return *this;
	}

	/**
	 * @brief      Overapproximates the current TemplatePolyhedron with the given directions and returns the resulting TemplatePolyhedron
	 * @param[in]  dirs The directions in which the current TemplatePolyhedron should be overapproximated.
	 * @return 	   The overapproximated TemplatePolyhedron with dirs as its matrix.
	 */
	TemplatePolyhedronT<Number, Converter, Setting> overapproximate( const matrix_t<Number>& dirs ) const;

	/**
	 * @brief      Checks whether the TemplatePolyhedron is bounded.
	 */
	bool isBounded() const;

  private:
	/**
	 * @brief	   Checks if the current TemplatePolyhedron lies fully within a given halfspace or fully outside
	 * @detail     IMPORTANT: Only sound on bounded TemplatePolyhedra.
	 * @param[in]  The normal and the offset of the halfspace to check with
	 * @return 	   The first bool whether the this is fully inside and the second bool whether this is fully outside the halfspace.
	 */
	std::pair<bool, bool> checkFullInsideFullOutside( const vector_t<Number>& normal, const Number& offset ) const;
};
/** @} */

}  // namespace hypro

#include "TemplatePolyhedron.tpp"
