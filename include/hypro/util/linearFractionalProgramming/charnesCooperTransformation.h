

#ifndef HYPRO_LINEARFRACTIONALPROGRAMMING_H
#define HYPRO_LINEARFRACTIONALPROGRAMMING_H
#include "Eigen/Core"
#include "hypro/types.h"
#include "hypro/util/linearOptimization/Optimizer.h"

namespace hypro {
template <typename number>
std::pair<bool,vector_t<number>> charnesCooperTransformation( vector_t<number> numerator, number numerator_b, vector_t<number> denominator, number denominator_b, matrix_t<number> constraints, vector_t<number> constraints_b ) {

	constraints.conservativeResize(constraints.rows(), constraints.cols()+1);
	constraints.col(constraints.cols()-1) =- constraints_b;
	numerator.conservativeResize(numerator.size()+1);
	numerator(numerator.size()-1)  = numerator_b;
	denominator.conservativeResize(denominator.size()+1);
	denominator(denominator.size()-1) = denominator_b;

	constraints.conservativeResize(constraints.rows()+3, constraints.cols());
	constraints.row(constraints.rows()-3) = denominator;
	constraints.row(constraints.rows()-2) = - denominator;

	vector_t<number> t_row = vector_t<number>::Zero(constraints.cols());
	t_row(t_row.size()-1) = -1;
	constraints.row(constraints.rows()-1) = t_row;

	vector_t<number> optimization_b = vector_t<number>::Zero( constraints.rows());

	optimization_b(optimization_b.size()-3) = 1;
	optimization_b(optimization_b.size()-2) = -1;

	Optimizer<number> opt = Optimizer<number>(constraints, optimization_b);
	EvaluationResult<mpq_class> res = opt.evaluate(numerator,true);
	if (res.errorCode != SOLUTION::FEAS and res.errorCode != SOLUTION::INFTY){
		return {false,vector_t<number>()};
	}
	number t = res.optimumValue(res.optimumValue.size() -1);
	vector_t<number> result = res.optimumValue / t;


	result.conservativeResize(result.size()-1);
	numerator.conservativeResize(numerator.size()-1);
	denominator.conservativeResize(denominator.size()-1);



	return {true,result};
}
}  // namespace hypro

#endif	// HYPRO_LINEARFRACTIONALPROGRAMMING_H