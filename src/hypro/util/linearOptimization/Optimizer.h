#pragma once

#define USE_PRESOLUTION
#define RECREATE_SOLVER
//#define VERIFY_RESULT
//#define DEBUG_MSG

#include "../../datastructures/Point.h"
#include "../../flags.h"
#include "../../types.h"
#include "EvaluationResult.h"
#include "Strategy.h"
#ifdef HYPRO_USE_SMTRAT
#include "smtrat/adaptions_smtrat.h"
#endif
#ifdef HYPRO_USE_Z3
#include "z3/adaptions_z3.h"
#endif
#ifdef HYPRO_USE_SOPLEX
#include "soplex/adaptions_soplex.h"
#endif
#ifdef HYPRO_USE_CLP
#include "clp/adaptions_clp.h"
#endif

#include "glpk/adaptions_glpk.h"
#include "glpk_context.h"

#include <carl/core/Relation.h>
#include <carl/util/Singleton.h>
#include <glpk.h>
#include <mutex>
#include <thread>

#ifdef VERIFY_RESULT
#include <sys/stat.h>
#endif

#include "../logging/Logger.h"
#include "../statistics/statistics.h"

namespace hypro {

/**
	 * @brief      Wrapper class for linear optimization.
	 * @tparam     Number  The used number type.
	 */
template <typename Number>
class Optimizer {
  private:
	matrix_t<Number> mConstraintMatrix;
	vector_t<Number> mConstraintVector;

	mutable bool mConsistencyChecked = false;
	mutable SOLUTION mLastConsistencyAnswer = SOLUTION::UNKNOWN;
	static bool warnInexact;
	bool maximize = true;
	mutable std::vector<carl::Relation> mRelationSymbols;

	// dependent members, all mutable
#ifdef HYPRO_USE_SMTRAT
	mutable smtrat::SimplexSolver mSmtratSolver;
	mutable smtrat::FormulaT mCurrentFormula;
	mutable std::unordered_map<smtrat::FormulaT, std::size_t> mFormulaMapping;
#ifdef VERIFY_RESULT
	mutable unsigned fileCounter;
	std::string filenamePrefix = "optimizer_error_out_";
#endif
#endif
	mutable std::mutex mContextLock;
#ifdef HYPRO_USE_GLPK
	// Glpk as a presolver
	mutable std::map<std::thread::id, glpk_context> mGlpkContexts;
#endif
#ifdef HYPRO_USE_CLP
	// CLP as a solver
	mutable std::map<std::thread::id, clp_context> mClpContexts;
#endif

  public:
	/**
	 * @brief      Default constructor.
	 */
	explicit Optimizer( bool max = true )
		: mConstraintMatrix()
		, mConstraintVector()
		, mConsistencyChecked( false )
		, maximize( max )
		, mRelationSymbols() {
#ifdef HYPRO_USE_GLPK
		glp_term_out( GLP_OFF );
#endif
#ifdef VERIFY_RESULT
		struct stat buffer;
		unsigned cnt = 0;
		while ( true ) {
			std::string name = filenamePrefix + std::to_string( cnt ) + ".smt2";
			if ( stat( name.c_str(), &buffer ) != 0 ) {
				break;
			}
			++cnt;
		}
		fileCounter = cnt;
#endif
#if !defined HYPRO_USE_SMTRAT && !defined HYPRO_USE_Z3 && !defined HYPRO_USE_SOPLEX
		if ( !Optimizer<Number>::warnInexact && carl::is_rational<Number>().value ) {
			// only warn once
			Optimizer<Number>::warnInexact = true;
			WARN( "hypro.optimizer", "Attention, using exact arithmetic with inexact linear optimization setup (glpk only, no exact backend)." );
		}
#endif
	}

	Optimizer( Optimizer<Number>&& orig );
	Optimizer( const Optimizer<Number>& orig );

	/**
		 * @brief      Constructor which sets the problem.
		 * @param[in]  constraints  The constraints.
		 * @param[in]  constants    The constants.
		 */
	Optimizer( const matrix_t<Number>& constraints, const vector_t<Number>& constants, bool max = true )
		: mConstraintMatrix( constraints )
		, mConstraintVector( constants )
		, mConsistencyChecked( false )
		, maximize( max )
		, mRelationSymbols( std::vector<carl::Relation>( constraints.rows(), carl::Relation::LEQ ) ) {
#ifdef HYPRO_USE_GLPK
		glp_term_out( GLP_OFF );
#endif
		assert( constraints.rows() > 0 );
		assert( constraints.cols() > 0 );
		assert( constants.rows() > 0 );
		assert( constraints.rows() == constants.rows() );
	}

	/**
		 * @brief      Destroys the object.
		 */
	~Optimizer() {
		//this->cleanContexts();
	}

	void cleanContexts();

#ifndef NDEBUG
	inline SOLUTION getLastConsistencyAnswer() const { return mLastConsistencyAnswer; }
	inline bool getConsistencyChecked() const { return mConsistencyChecked; }
#endif
#ifdef HYPRO_USE_GLPK
	inline const std::map<std::thread::id, glpk_context>& getGLPContexts() const {
		return mGlpkContexts;
	}
#endif
#ifdef HYPRO_USE_CLP
	inline const std::map<std::thread::id, clp_context>& getCLPContexts() const {
		return mClpContexts;
	}
#endif

	friend void swap( Optimizer<Number>& lhs, Optimizer<Number>& rhs ) {
		std::swap( lhs.mConstraintMatrix, rhs.mConstraintMatrix );
		std::swap( lhs.mConstraintVector, rhs.mConstraintVector );
		std::swap( lhs.mConsistencyChecked, rhs.mConsistencyChecked );
		std::swap( lhs.mRelationSymbols, rhs.mRelationSymbols );
#ifdef HYPRO_USE_GLPK
		std::swap( lhs.mGlpkContexts, rhs.mGlpkContexts );
#endif
#ifdef HYPRO_USE_CLP
		std::swap( lhs.mClpContexts, rhs.mClpContexts );
#endif
		std::swap( lhs.mLastConsistencyAnswer, rhs.mLastConsistencyAnswer );
		std::swap( lhs.maximize, rhs.maximize );
		assert( lhs.isSane() && rhs.isSane() );
	}

	/**
		 * @brief      Copy Assign operator.
		 * @param[in]  orig  The right-hand-side object.
		 * @return     A reference to the the current object with the values of orig.
		 */
	Optimizer<Number>& operator=( const Optimizer<Number>& orig );

	/**
		 * @brief      Returns the problem matrix.
		 * @return     The problem matrix (row-wise constraints).
		 */
	const matrix_t<Number>& matrix() const;

	/**
		 * @brief      Returns the problem constants as a vector.
		 * @return     The vector of constants.
		 */
	const vector_t<Number>& vector() const;

	/**
		 * @brief      Sets the problem matrix.
		 * @param[in]  _matrix  The matrix.
		 */
	void setMatrix( const matrix_t<Number>& _matrix );

	/**
		 * @brief      Sets the problem vector.
		 * @param[in]  _vector  The vector.
		 */
	void setVector( const vector_t<Number>& _vector );

	/**
		 * @brief Set the Relations for all constraints.
		 *
		 * @param rels
		 */
	void setRelations( const std::vector<carl::Relation>& rels );

	/**
		 * @brief Set the Maximize flag to new value to switch between maximizing and minimizing
		 *
		 * @param max The new flag value (true = maximize, false = minimize).
		 */
	void setMaximize( bool max );

	/**
		 * @brief 		Add an equality constraint.
		 *
		 * @param constraint
		 * @param constantPart
		 */
	void addConstraint( const vector_t<Number>& constraint, Number constantPart, carl::Relation rel );

	/**
		 * @brief Set the Relation for the constraint at position pos
		 *
		 * @param pos
		 */
	void setRelation( carl::Relation rel, std::size_t pos );

	/**
		 * @brief      Clears the problem instance.
		 */
	void clear();

	/**
		 * @brief      Performs linear optimization in the given direction.
		 * @param[in]  _direction    The direction.
		 * @param[in]  useExactGlpk  The use exact glpk property. If set, glpk is used in its exact mode.
		 * @return     A struct holding the linear optimization result.
		 */
	EvaluationResult<Number> evaluate( const vector_t<Number>& _direction, bool useExactGlpk ) const;

	/**
		 * @brief      Checks consistency (i.e. existence of a solution) of the current problem instance.
		 * @return     True, if there exists a solution, false otherwise.
		 */
	bool checkConsistency() const;

	/**
		 * @brief      Checks whether the given point lies inside the satisfiable solution space of the current problem.
		 * @param[in]  _point  The point.
		 * @return     True, if the point satisfies all constraints, false otherwise.
		 */
	bool checkPoint( const Point<Number>& _point ) const;

	/**
		 * @brief      Gets some point being a possible solution.
		 * @return     The internal point.
		 */
	EvaluationResult<Number> getInternalPoint() const;

	/**
		 * @brief      Determines the set of redundant constraints.
		 * @details    A constraint is redundant, whenever the removal of this constraint does not modify the set of possible solutions.
		 * @return     A vector of row-indices which represent redundant constraints.
		 */
	std::vector<std::size_t> redundantConstraints() const;

  private:
	bool isSane() const;

	/**
		 * @brief      Calls required initialization methods.
		 */
	void initialize() const;

	/**
		 * @brief      Updates problem instances.
		 */
	void updateConstraints() const;

	/**
		 * @brief 		clears the cache of computed solutions.
		 */
	void clearCache() const;
};
}  // namespace hypro

template <typename Number>
bool hypro::Optimizer<Number>::warnInexact = false;

#ifdef USE_CLN_NUMBERS
#include <cln/cln.h>
extern template class hypro::Optimizer<cln::cl_RA>;
#else
#include <gmp.h>
#include <gmpxx.h>
extern template class hypro::Optimizer<mpq_class>;
#endif

#include "Optimizer.tpp"
