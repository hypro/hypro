
#pragma once

#include "../../util/eigenTypetraits.h"
#include "carl/interval/Interval.h"
#include "carl/numbers/FLOAT_T.h"
#include "../../representations/Polytope/Polytope.h"


namespace hypro
{
		enum operator_e {
			EQ,
			GEQ,
			LEQ,
			NEQ,
			LESS,
			GREATER
		};

		template<typename Number>
		using valuation_t = hypro::Polytope<Number>;

		template<typename Number>
		using vector_t = Eigen::Matrix<carl::FLOAT_T<Number>, Eigen::Dynamic, 1>;

		template<typename Number>
		using matrix_t = Eigen::Matrix<carl::FLOAT_T<Number>, Eigen::Dynamic, Eigen::Dynamic>;

}
