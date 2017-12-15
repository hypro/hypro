#pragma once

#define USE_PRESOLUTION
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
#include <thread>

#ifdef VERIFY_RESULT
#include <sys/stat.h>
#endif

#include "../statistics/statistics.h"
#include "../logging/Logger.h"

#include "../../../resources/glpk-4.45/build/include/glpk.h"

namespace hypro {

	struct glpk_context{
		glp_prob* lp = nullptr;
		int* ia = nullptr;
		int* ja = nullptr;
		double* ar = nullptr;
		bool arraysCreated = false; 			// true if array variables have been created.
		mutable bool mInitialized = false;		// true if lp instance has been created.
		mutable bool mConstraintsSet = false;	// true if lp instance exists, arrays have been set and the lp instance is set up with the current constraints.

		glpk_context()
			: lp(nullptr)
			, ia(nullptr)
			, ja(nullptr)
			, ar(nullptr)
			, arraysCreated(false)
			, mInitialized(false)
			, mConstraintsSet(false)
		{
			TRACE("hypro.optimizer","Create glpk_context " << this);
		}

		void createArrays( unsigned size ) {
			TRACE("hypro.optimizer","");
			if(arraysCreated) {
				deleteArrays();
			}
			ia = new int[size + 1];
			ja = new int[size + 1];
			ar = new double[size + 1];
			arraysCreated = true;
		}

		void deleteArrays() {
			TRACE("hypro.optimizer","");
			if(arraysCreated) {
				delete[] ia;
				delete[] ja;
				delete[] ar;
				arraysCreated = false;
			}
		}

		void createLPInstance() {
			if(!mInitialized) {
				lp = glp_create_prob();
				glp_set_obj_dir( lp, GLP_MAX );
				glp_term_out( GLP_OFF );
				TRACE("hypro.optimizer", "Thread " << std::this_thread::get_id() << " creates its glp instance. (@" << this << ")");
				mInitialized = true;
				mConstraintsSet = false;
			}
		}

		void deleteLPInstance() {
			TRACE("hypro.optimizer","Start." << " instance @" << this);
			if(mInitialized){
				assert(lp != nullptr);
				glp_delete_prob(lp);
				mInitialized = false;
				mConstraintsSet = false;
				lp = nullptr;
			}
			TRACE("hypro.optimizer","Done." << " instance @" << this);
		}

		~glpk_context(){
			TRACE("hypro.optimizer","Arrays created: " << arraysCreated << " instance @" << this);
			deleteLPInstance();
			// assume that all fields are set at once so just check one.
			deleteArrays();
		}
	};

	/**
	 * @brief      Wrapper class for linear optimization.
	 * @tparam     Number  The used number type.
	 */
	template<typename Number>
	class Optimizer {

	private:
		matrix_t<Number>	mConstraintMatrix;
		vector_t<Number> 	mConstraintVector;

		mutable bool 				mConsistencyChecked;
		mutable SOLUTION 			mLastConsistencyAnswer;
		static bool			warnInexact;

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
		mutable std::map<std::thread::id, glpk_context> mGlpkContext;

	public:

		/**
		 * @brief      Default constructor.
		 */
		Optimizer() :
			mConstraintMatrix(),
			mConstraintVector(),
			mConsistencyChecked(false),
			mGlpkContext()
		{
			#ifdef VERIFY_RESULT
			struct stat buffer;
			unsigned cnt = 0;
			while(true){
				std::string name = filenamePrefix + std::to_string(cnt) + ".smt2";
				if(stat (name.c_str(), &buffer) != 0) {
					break;
				}
				++cnt;
			}
			fileCounter = cnt;
			#endif
			#if !defined HYPRO_USE_SMTRAT && !defined HYPRO_USE_Z3 && !defined HYPRO_USE_SOPLEX
			if(!Optimizer<Number>::warnInexact && carl::is_rational<Number>().value){
				// only warn once
				Optimizer<Number>::warnInexact = true;
				WARN("hypro.optimizer","Attention, using exact arithmetic with inexact linear optimization setup (glpk only, no exact backend).");
			}
			#endif
		}

		Optimizer(Optimizer<Number>&& orig) = delete;
		Optimizer(const Optimizer<Number>& orig) = delete;

		/**
		 * @brief      Constructor which sets the problem.
		 * @param[in]  constraints  The constraints.
		 * @param[in]  constants    The constants.
		 */
		Optimizer(const matrix_t<Number>& constraints, const vector_t<Number>& constants) :
			mConstraintMatrix(constraints),
			mConstraintVector(constants),
			mConsistencyChecked(false),
			mGlpkContext()
		{	}

		/**
		 * @brief      Destroys the object.
		 */
		~Optimizer() {
			TRACE("hypro.optimizer","Have " << mGlpkContext.size() << " instances left.");
			this->cleanGLPInstance();
		}

		void cleanGLPInstance();

		inline const std::map<std::thread::id, glpk_context>& getGLPContexts() const {
			return mGlpkContext;
		}

	public:
		/**
		 * @brief      Comparison operator.
		 * @param[in]  orig  The right-hand-side object.
		 * @return     True, if both problem instances are equal, false otherwise.
		 */
		Optimizer<Number>& operator=(const Optimizer<Number>& orig);

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
		void setMatrix(const matrix_t<Number>& _matrix);

		/**
		 * @brief      Sets the problem vector.
		 * @param[in]  _vector  The vector.
		 */
		void setVector(const vector_t<Number>& _vector);

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
		EvaluationResult<Number> evaluate(const vector_t<Number>& _direction, bool useExactGlpk) const;

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
		bool checkPoint(const Point<Number>& _point) const;

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
	};
} // namespace hypro

template<typename Number>
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
