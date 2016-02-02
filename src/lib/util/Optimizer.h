#pragma once

#include <carl/util/Singleton.h>
#include "../config.h"
#include "smtrat/SimplexSolver.h"
#include "VariablePool.h"

#define USE_PRESOLUTION
#define RECREATE_SOLVER

namespace hypro {

	// Solution types
	enum SOLUTION { FEAS = 0, INFEAS, INFTY, UNKNOWN };

	template<typename Number>
	class Optimizer : public carl::Singleton<Optimizer<Number>> {
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

		void setMatrix(const matrix_t<Number> _matrix);
		void setVector(const vector_t<Number> _vector);
		void clear();

		std::pair<Number,SOLUTION> evaluate(const vector_t<Number>& _direction, bool overapproximate = false) const;
		bool checkConsistency() const;

	private:
		void initialize() const;
		void updateConstraints() const;

		void createArrays( unsigned size ) const;
		void deleteArrays() const;

	};
} // namespace

#include "Optimizer.tpp"