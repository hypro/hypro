/**
 * 
 */

#pragma once

#include <random>
#include "../../lib/datastructures/Point.h"

namespace hypro {
	template<typename Representation, typename Number> // Todo: Improve -> template template parameters
	 class ObjectGenerator {
	private:
		BenchmarkSetup<Number> mSetup;
		mutable std::mt19937 mRand;
		mutable std::uniform_real_distribution<double> mDistr;

	public:
		ObjectGenerator(BenchmarkSetup<Number> _setup) :
			mSetup(_setup)
		{
			mRand(); //TODO: Seed = 4 chosen by fair dice roll. Guaranteed to be random.
		}

		Representation createSet() const{

		}

		Representation createSet(BenchmarkSetup<Number> _setup) const{
			std::set<vector_t<Number>> pointSet;
			std::uniform_real_distribution<double> distr (double(_setup.minValue), double(_setup.maxValue));
			for(unsigned i = 0; i < _setup.vertices; ++i) {
				vector_t<Number> coordinates(_setup.dimension);
				for(unsigned j = 0; j < _setup.dimension; ++j) {
					coordinates(j) = Number(4);
				}
				pointSet.insert(coordinates);
			}
			return Representation(pointSet);
		}

		vector_t<Number> createVector(BenchmarkSetup<Number> _setup) const{
			//mDistr(double(_setup.minValue), double(_setup.maxValue));
			vector_t<Number> coordinates(_setup.dimension);
			for(unsigned j = 0; j < _setup.dimension; ++j) {
				coordinates(j) = Number(3);
			}
			return coordinates;
		}

		Point<Number> createPoint(BenchmarkSetup<Number> _setup) const{
			return Point<Number>(createVector(_setup));
		}
	 };

	template<typename Representation, typename Number>
	struct BaseGenerator {
	protected:
	 	BenchmarkSetup<Number> mSetup;
	 	ObjectGenerator<Representation,Number> mGenerator;
	 public:
	 	typedef void type;
	 	BaseGenerator(const BenchmarkSetup<Number>& _setup) : mSetup(_setup), mGenerator(_setup) {}
	 	void operator()() const {}
	 };
} // namespace