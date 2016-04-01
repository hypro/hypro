#pragma once

#include "EvaluationResult.h"
#include "smtrat/SimplexSolver.h"
#include <carl/util/Singleton.h>

#define USE_PRESOLUTION
#define RECREATE_SOLVER

namespace hypro {

	template<typename Number>
	class Optimizer : public carl::Singleton<Optimizer<Number>> {
		using Poly = carl::MultivariatePolynomial<Number>;

		friend carl::Singleton<Optimizer<Number>>;

	private:
		matrix_t<Number>	mConstraintMatrix;
		vector_t<Number> 	mConstraintVector;
		mutable bool		mInitialized;
		mutable bool		mConstraintsSet;

		mutable bool 				mConsistencyChecked;
		mutable SOLUTION 			mLastConsistencyAnswer;

		// dependent members, all mutable
		#ifdef USE_SMTRAT
		mutable smtrat::SimplexSolver mSmtratSolver;
		mutable smtrat::FormulaT mCurrentFormula;
		mutable std::unordered_map<smtrat::FormulaT, std::size_t> mFormulaMapping;
		#endif
		// Glpk as a presolver
		mutable glp_prob* lp;
		mutable int* ia;
		mutable int* ja;
		mutable double* ar;

	protected:

		Optimizer() :
			mConstraintMatrix(),
			mConstraintVector(),
			mInitialized(false),
			mConstraintsSet(false)
		{}

	public:

		const matrix_t<Number>& matrix() const;
		const vector_t<Number>& vector() const;

		void setMatrix(const matrix_t<Number>& _matrix);
		void setVector(const vector_t<Number>& _vector);
		void clear();

		EvaluationResult<Number> evaluate(const vector_t<Number>& _direction, bool overapproximate = false) const;
		bool checkConsistency() const;
		bool checkPoint(const Point<Number>& _point) const;
		EvaluationResult<Number> getInternalPoint() const;
		std::vector<std::size_t> redundantConstraints() const;

	private:
		void initialize() const;
		void updateConstraints() const;
		#ifdef USE_SMTRAT
		void addPresolution(smtrat::SimplexSolver& solver, const EvaluationResult<Number>& glpkResult, const vector_t<Number>& direction, const smtrat::Poly& objective) const;
		EvaluationResult<Number> extractSolution(const smtrat::SimplexSolver& solver, const smtrat::Poly& objective) const;
		#endif

		void createArrays( unsigned size ) const;
		void deleteArrays() const;

	};
} // namespace hypro

#include "Optimizer.tpp"
