#pragma once

#include "Generators.h"
#include "Result.h"

namespace hypro {

	template<typename Representation, int operation>
	struct Executor {
		void run(typename Generator<Representation, operation>::type _in) {}
	};

	template<typename Representation>
	struct Executor<Representation, operation::LINEARTRAFO> {
		Result run(typename Generator<Representation, operation::LINEARTRAFO>::type _in) {
			std::get<0>(_in).linearTransformation(std::get<1>(_in), std::get<2>(_in));
			return Result();
		}
	};

	template<typename Representation>
	struct Executor<Representation, operation::MINKOWSKISUM> {
		Result run(typename Generator<Representation, operation::MINKOWSKISUM>::type _in) {
			std::get<0>(_in).minkowskiSum(std::get<1>(_in));
			return Result();
		}
	};

	template<typename Representation>
	struct Executor<Representation, operation::INTERSECTION> {
		Result run(typename Generator<Representation, operation::INTERSECTION>::type _in) {
			std::get<0>(_in).intersect(std::get<1>(_in));
			return Result();
		}
	};

	template<typename Representation>
	struct Executor<Representation, operation::CONTAINS> {
		Result run(typename Generator<Representation, operation::CONTAINS>::type _in) {
			std::get<0>(_in).contains(std::get<1>(_in));
			return Result();
		}
	};

	template<typename Representation>
	struct Executor<Representation, operation::UNION> {
		Result run(typename Generator<Representation, operation::UNION>::type _in) {
			std::get<0>(_in).unite(std::get<1>(_in));
			return Result();
		}
	};
} // namespace