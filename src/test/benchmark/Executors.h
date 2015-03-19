#pragma once

#include "Generators.h"
#include "Result.h"

namespace hypro {
	template<typename Representation, typename Number>
	struct ContainsExecutor {
		Result run(typename ContainsGenerator<Representation,Number>::type _in) {
			std::get<0>(_in).contains(std::get<1>(_in));
			return Result();
		}
	};
} // namespace