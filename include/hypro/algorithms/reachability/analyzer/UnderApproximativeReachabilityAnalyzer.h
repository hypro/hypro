//
// Created by kai on 12.06.23.
//


#ifndef HYPRO_UNDERAPPROXIMATIVEREACHABILITYANALYZER_H
#define HYPRO_UNDERAPPROXIMATIVEREACHABILITYANALYZER_H
#include "hypro/types.h"
#include "Eigen/Core"
#include "hypro/util/linearFractionalProgramming/charnesCooperTransformation.h"

using namespace hypro;

template <typename number>
class UnderApproximativeReachabilityAnalyzer {
	std::tuple<bool,vector_t<number>, number> combine_cases(vector_t<number> low, number low_b, vector_t<number> up, number up_b, matrix_t<number> rate_factors, vector_t<number> rate_b) {
		matrix_t<number> opt_factors = rate_factors;
		vector_t<number> opt_b = rate_b;
		vector_t<number> lower_factors = low;
		vector_t<number> upper_factors = vector_t<number>(up.size());
		for (int i = 0; i < up.size() - 1; i++) {
			upper_factors[i] = -up[i];
		}
		opt_factors.conservativeResize(opt_factors.rows()+2, opt_factors.cols());
		opt_b.conservativeResize(opt_b.size()+2);
		opt_factors.row(opt_factors.rows()-2) = lower_factors;
		opt_factors.row(opt_factors.rows()-1) = upper_factors;
		opt_b(opt_b.size()-2) = 0;
		opt_b(opt_b.size()-1) = 0;

		auto [found, optimum] = solveOptimization(low, up, opt_factors, opt_b);
		if (found) {
			number b = optimum * low_b - up_b;
			vector_t<number> factors = vector_t<number>(rate_factors.cols());
			bool nonZero = false;
			for (int i = 0; i < rate_factors.cols(); i++) {
				number current = up[i] - optimum * low[i];
				factors(i) = up[i] - optimum * low[i];
				if (current != 0) {
					nonZero = true;
				}
			}
			if (nonZero) {
				return {true,factors , b};
			}
		}
		return {false, vector_t<number>(), 0};
	}

	//this should just be Charnes-Cooper transformation
	std::pair<bool, number> solveOptimization(vector_t<number> low, vector_t<number> up, matrix_t<number> opt_factors, vector_t<number> opt_b) {

		opt_factors.conservativeResize(opt_factors.rows()+2, opt_factors.cols());
		opt_b.conservativeResize(opt_b.size()+2);
		opt_factors.row(opt_factors.rows()-2) = low;
		opt_b(opt_b.size()-2) = 0;
		opt_factors.row(opt_factors.rows()-2) = -up;
		opt_b(opt_b.size()-2) = 0;
		vector_t<number> inverted_low = -1 * low;
		auto [found, opt]  = charnesCooperTransformation(up,number(0),inverted_low,number(0),opt_factors,opt_b);
		if (not found){
			return {false,0};
		}
		return {true,opt.dot(- up)/ opt.dot(inverted_low)};
	}

  public:
	std::pair<matrix_t<number>, vector_t<number>> solve(const matrix_t<mpq_class>& factors, const vector_t<number>& b,const vector_t<carl::Interval<number>>& rates) {
		auto [rate_factors, rate_b] = generate_rate_box(rates);
		auto [constraints, result_factors, result_b] = generate_cases(factors, b, rates);
		for (int i = 0; i < constraints.size(); i++) {
			auto [isFirstLower, isFirstUpper, first, first_b] = constraints[i];
			for (int j = i + 1; j < constraints.size(); j++) {
				auto[isSecondLower, isSecondUpper, second, second_b] = constraints[j];
				if (isFirstLower && isFirstUpper && isSecondLower && isSecondUpper) {
					continue;
				}
				if (isFirstLower && isSecondUpper) {
					auto [found, combinedFactors, combinedB]  = combine_cases(first, first_b, second, second_b, rate_factors, rate_b);
					if (found) {
						result_factors.conservativeResize(result_factors.rows()+1,Eigen::NoChange);

						result_factors.row(result_factors.rows()-1) = combinedFactors;

						result_b.conservativeResize(result_b.size()+1);
						result_b(result_b.size() - 1) =  combinedB;
					}
				}
				if (isFirstUpper && isSecondLower) {
					auto [found, combinedFactors, combinedB] = combine_cases(second,second_b, first, first_b, rate_factors, rate_b);
					if ( found) {
						result_factors.conservativeResize(result_factors.rows()+1,Eigen::NoChange);
						result_factors.row(result_factors.rows()-1) = combinedFactors;

						result_b.conservativeResize(result_b.size()+1);
						result_b(result_b.size() - 1) =  combinedB;
					}
				}
			}
		}
		return {result_factors, result_b };
	}


	std::pair<matrix_t<number>, vector_t<number>> generate_rate_box(const vector_t<carl::Interval<number>>& rates) {
		matrix_t<number> rate_factors = matrix_t<number>::Zero(rates.size() * 2, rates.size());
		vector_t<number> rate_b = vector_t<number>(rates.size() * 2);
		for (int index = 0; index < rates.size(); index++) {
			carl::Interval<number> rate = rates[index];
			rate_factors(2 * index, index) = -1;
			rate_b(2 * index) = -rate.lower();
			rate_factors(2 * index + 1, index) = 1;
			rate_b(2 * index + 1) = rate.upper();
		}
		return { rate_factors, rate_b };
	}
	std::tuple<vector_t<std::tuple<bool, bool, vector_t<number>, number>>, matrix_t<number>, vector_t<number>> generate_cases(const matrix_t<mpq_class>& factors,const vector_t<number> &b,const vector_t<carl::Interval<number>> &rates) {
		vector_t<std::tuple<bool, bool, vector_t<number>, number>> constraints;
		matrix_t<number> result_factors  = matrix_t<number>(0,rates.size());
		vector_t<number> result_b;
		for (int row_index = 0; row_index < rates.size();row_index++) {
			carl::Interval<number> row_interval{0, 0};
			for (int rate_index = 0; rate_index < rates.size(); rate_index++) {
				row_interval += factors(row_index, rate_index ) * rates[rate_index];
			}
			if (row_interval.upper() > 0 || row_interval.contains(0)) {
				result_factors.conservativeResize(result_factors.rows() + 1, result_factors.cols());

				result_factors.row(result_factors.rows() - 1) = factors.row(row_index);
				result_b.conservativeResize(result_b.size() + 1);
				result_b(result_b.size() - 1) = -b(row_index);
			}

			if (row_interval.lower() < 0 && 0 <row_interval.upper()) {

				vector_t<number> row = factors.row(row_index);
				constraints.conservativeResize(constraints.size() + 1);
				constraints(constraints.size()-1) =  std::make_tuple(true, true, row,b[row_index]);
				continue;
			}
			if (row_interval.lower() < 0) {

				vector_t<number> row = factors.row(row_index);
				constraints.conservativeResize(constraints.size() + 1);
				constraints(constraints.size()-1) =  std::make_tuple(true, false, row,b[row_index]);
			} else if (row_interval.upper() > 0) {

				vector_t<number> row = factors.row(row_index);
				constraints.conservativeResize(constraints.size() + 1);
				constraints(constraints.size()-1) = std::make_tuple(false, true, row,b[row_index]);
			}
		}
		return {constraints, result_factors,result_b};
	}
};

#endif	// HYPRO_UNDERAPPROXIMATIVEREACHABILITYANALYZER_H
