
#pragma once

#include "../../util/eigenTypetraits.h"
#include "carl/interval/Interval.h"
#include "carl/numbers/FLOAT_T.h"
#include "../../representations/Polytope/Polytope.h"
#include "../../config.h"

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
}
