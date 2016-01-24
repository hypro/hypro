#include "../config.h"
#include "smtrat/SimplexSolver.h"
#include "z3/util.h"

namespace hypro {

	template<typename Number>
	class Optimizer {
	private:
		matrix_t<Number>	mConstraintMatrix;
		vector_t<Number> 	mConstraintVector;
		bool				mInitialized;

		// dependent members
		#ifdef USE_SMTRAT
		mutable smtrat::SimplexSolver mSmtratSolver;
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

		Number evaluate(const vector_t<Number> _direction) const;
		bool checkConsistency() const;

	private:
		void initialize() const;

	};
} // namespace