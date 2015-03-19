#pragma once

#include "ObjectGenerator.h"

namespace hypro {

	template<typename Representation, typename Number>
	struct ContainsGenerator : public BaseGenerator<Representation,Number> {
		typedef std::tuple<Representation, Point<Number>> type;

		ContainsGenerator(const BenchmarkSetup<Number>& _setup) : BaseGenerator<Representation,Number>(_setup) {}

		type operator()() const {
			return std::make_tuple(this->mGenerator.createSet(this->mSetup), this->mGenerator.createPoint(this->mSetup));
		}	
	};

} // namespace