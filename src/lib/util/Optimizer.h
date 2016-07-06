#pragma once

//#define USE_PRESOLUTION
#define RECREATE_SOLVER
//#define VERIFY_RESULT
//#define DEBUG_MSG

#include "EvaluationResult.h"
#include "smtrat/SimplexSolver.h"
#include <carl/util/Singleton.h>

#ifdef VERIFY_RESULT
#include <sys/stat.h>
#endif

namespace hypro {

	template<typename Number>
	class Optimizer {
		using Poly = carl::MultivariatePolynomial<Number>;

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
		#ifdef VERIFY_RESULT
		mutable unsigned fileCounter;
		std::string filenamePrefix = "optimizer_error_out_";
		#endif
		#endif
		// Glpk as a presolver
		mutable bool arraysCreated=false;
		mutable glp_prob* lp;
		mutable int* ia;
		mutable int* ja;
		mutable double* ar;

	public:

		Optimizer() :
			mConstraintMatrix(),
			mConstraintVector(),
			mInitialized(false),
			mConstraintsSet(false)
		{
			#ifdef VERIFY_RESULT
			struct stat buffer;
			unsigned cnt = 0;
			while(true){
				std::string name = filenamePrefix + std::to_string(cnt) + ".smt2";
				if(stat (name.c_str(), &buffer) != 0) {
					break;
				}
				//std::cout << "File " << name << " exists." << std::endl;
				++cnt;
			}
			fileCounter = cnt;
			//std::cout << "Set file number to " << fileCounter << std::endl;
			#endif
		}

		~Optimizer() {
			deleteArrays();
		}

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
		EvaluationResult<Number> extractSolution(smtrat::SimplexSolver& solver, const smtrat::Poly& objective) const;
		#endif

		void createArrays( unsigned size ) const;
		void deleteArrays() const;

	};
} // namespace hypro

#include "Optimizer.tpp"
