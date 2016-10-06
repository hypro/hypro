#pragma once

//#define USE_PRESOLUTION
#define RECREATE_SOLVER
//#define VERIFY_RESULT
//#define DEBUG_MSG

#include "../../flags.h"
#include "Strategy.h"
#include "EvaluationResult.h"
#include "../../datastructures/Point.h"
#ifdef HYPRO_USE_SMTRAT
#include "smtrat/adaptions_smtrat.h"
#endif
#ifdef HYPRO_USE_Z3
#include "z3/adaptions_z3.h"
#endif
#ifdef HYPRO_USE_SOPLEX
#include "soplex/adaptions_soplex.h"
#endif
#include "glpk/adaptions_glpk.h"
#include <carl/util/Singleton.h>
#include <mutex>

#ifdef VERIFY_RESULT
#include <sys/stat.h>
#endif

#include <glpk.h>

namespace hypro {

	template<typename Number>
	class Optimizer {

	private:
		matrix_t<Number>	mConstraintMatrix;
		vector_t<Number> 	mConstraintVector;
		mutable bool		mInitialized;
		mutable bool		mConstraintsSet;

		mutable bool 				mConsistencyChecked;
		mutable SOLUTION 			mLastConsistencyAnswer;

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
			mConstraintsSet(false),
			mConsistencyChecked(false)
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

		Optimizer(Optimizer<Number>&& orig) = delete; // TODO

		Optimizer(const Optimizer<Number>& orig) :
			mConstraintMatrix(orig.matrix()),
			mConstraintVector(orig.vector()),
			mInitialized(false),
			mConstraintsSet(false),
			mConsistencyChecked(false)
		{	}

		Optimizer(const matrix_t<Number>& constraints, const vector_t<Number>& constants) :
			mConstraintMatrix(constraints),
			mConstraintVector(constants),
			mInitialized(false),
			mConstraintsSet(false),
			mConsistencyChecked(false)
		{	}

		~Optimizer() {
			if(mInitialized) {
				glp_delete_prob(lp);
			}
			deleteArrays();
		}

	public:
		Optimizer<Number>& operator=(const Optimizer<Number>& orig);

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

		void createArrays( unsigned size ) const;
		void deleteArrays() const;

	};
} // namespace hypro

#ifdef USE_CLN_NUMBERS
#include <cln/cln.h>
extern template class hypro::Optimizer<cln::cl_RA>;
#else
#include <gmp.h>
#include <gmpxx.h>
extern template class hypro::Optimizer<mpq_class>;
#endif

#include "Optimizer.tpp"
