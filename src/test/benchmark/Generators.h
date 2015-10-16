#pragma once

#include "ObjectGenerator.h"

namespace hypro {

	enum operation : int {LINEARTRAFO = 0, MINKOWSKISUM = 1, INTERSECTION = 2, CONTAINS = 3, UNION = 4};

	template<typename Representation, int operation>
	struct Generator : public BaseGenerator<Representation> {
		typedef void type;
		std::string name;

		Generator(const BenchmarkSetup<typename Representation::type>& _setup) {}
		void operator()() const {}
	};

	template<typename Representation>
	struct Generator<Representation, operation::LINEARTRAFO>: public BaseGenerator<Representation> {
		typedef std::tuple<Representation, matrix_t<typename Representation::type>, vector_t<typename Representation::type>> type;
		std::string name;

		Generator(const BenchmarkSetup<typename Representation::type>& _setup) : BaseGenerator<Representation>(_setup), name("linear transformation") {}

		type operator()() const {
			return std::make_tuple(this->mGenerator.createSet(this->mSetup), this->mGenerator.createMatrix(this->mSetup), this->mGenerator.createVector(this->mSetup));
		}
	};

	template<typename Representation>
	struct Generator<Representation, operation::MINKOWSKISUM> : public BaseGenerator<Representation> {
		typedef std::tuple<Representation, Representation> type;
		std::string name;

		Generator(const BenchmarkSetup<typename Representation::type>& _setup) : BaseGenerator<Representation>(_setup), name("Minkowski sum") {}

		type operator()() const {
			return std::make_tuple(this->mGenerator.createSet(this->mSetup), this->mGenerator.createSet(this->mSetup));
		}
	};

	template<typename Representation>
	struct Generator<Representation, operation::INTERSECTION> : public BaseGenerator<Representation> {
		typedef std::tuple<Representation, Representation> type;
		std::string name;

		Generator(const BenchmarkSetup<typename Representation::type>& _setup) : BaseGenerator<Representation>(_setup), name("intersect") {}

		type operator()() const {
			return std::make_tuple(this->mGenerator.createSet(this->mSetup), this->mGenerator.createSet(this->mSetup));
		}
	};

	template<typename Representation>
	struct Generator<Representation, operation::CONTAINS> : public BaseGenerator<Representation> {
		typedef std::tuple<Representation, Point<typename Representation::type>> type;
		std::string name;

		Generator(const BenchmarkSetup<typename Representation::type>& _setup) : BaseGenerator<Representation>(_setup), name("contains") {}

		type operator()() const {
			return std::make_tuple(this->mGenerator.createSet(this->mSetup), this->mGenerator.createPoint(this->mSetup));
		}
	};

	template<typename Representation>
	struct Generator<Representation, operation::UNION> : public BaseGenerator<Representation> {
		typedef std::tuple<Representation, Representation> type;
		std::string name;

		Generator(const BenchmarkSetup<typename Representation::type>& _setup) : BaseGenerator<Representation>(_setup), name("unite") {}

		type operator()() const {
			return std::make_tuple(this->mGenerator.createSet(this->mSetup), this->mGenerator.createSet(this->mSetup));
		}
	};

} // namespace