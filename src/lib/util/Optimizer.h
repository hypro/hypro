#pragma once

#include "../config.h"
#include "smtrat/SimplexSolver.h"
#include "z3/util.h"

namespace hypro {

	// Solution types
	enum SOLUTION { FEAS = 0, INFEAS, INFTY };

	template<typename Number>
	class Optimizer {
	private:
		matrix_t<Number>	mConstraintMatrix;
		vector_t<Number> 	mConstraintVector;
		mutable bool		mInitialized;

		// dependent members, all mutable
		#ifdef USE_SMTRAT
		mutable smtrat::SimplexSolver mSmtratSolver;
		#elif defined USE_Z3
		mutable z3::context c;
	    mutable z3::solver z3solver(c);
		#else // Fallback: Glpk
		mutable glp_prob* lp;
		mutable int* ia;
		mutable int* ja;
		mutable double* ar;
		#endif

	public:
		Optimizer() = default;
		Optimizer(const matrix_t<Number>& _matrix, const vector_t<Number>& _vector) :
			mConstraintMatrix(_matrix),
			mConstraintVector(_vector),
			mInitialized(false)
		{}

		const matrix_t<Number>& matrix() const;
		const vector_t<Number>& vector() const;

		void setMatrix(const matrix_t<Number> _matrix);
		void setVector(const vector_t<Number> _vector);
		void clear();

		std::pair<Number,SOLUTION> evaluate(const vector_t<Number>& _direction) const;
		bool checkConsistency() const;

	private:
		void initialize() const;

		#ifdef USE_SMTRAT
		#elif defined USE_Z3
		#else
		void createArrays( unsigned size ) const;
		void deleteArrays
		#endif

	};
} // namespace

#include "Optimizer.tpp"