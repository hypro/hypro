/**
 *
 */

#pragma once

#include <random>
#include "../../hypro/datastructures/Point.h"
#include "../../hypro/types.h"

namespace hypro {
	template<typename Representation, typename Number>
	 class ObjectGenerator {
	private:
		//typedef typename Representation::type Number;

		BenchmarkSetup<Number> mSetup;
		mutable std::mt19937 mRand;
		mutable std::uniform_real_distribution<double> mDistr;

	public:
		ObjectGenerator(BenchmarkSetup<Number> _setup) :
			mSetup(_setup),
			mRand(4) // chosen by fair dice roll. Guaranteed to be random.
		{}

		Representation createSet() const{

		}

		Representation createSet(BenchmarkSetup<Number> _setup) const{
			std::vector<Point<Number>> pointVector;
			//std::uniform_real_distribution<double> distr (double(_setup.minValue), double(_setup.maxValue));
			std::uniform_real_distribution<double> distr (carl::toDouble(_setup.minValue), carl::toDouble(_setup.maxValue));
			for(unsigned i = 0; i < _setup.vertices; ++i) {
				vector_t<Number> coordinates(_setup.dimension);
				for(unsigned j = 0; j < _setup.dimension; ++j) {
					coordinates(j) = Number(distr(mRand));
					//std::cout << "coordinates(" << j << ") = " << coordinates(j) << std::endl;
				}
				pointVector.push_back(Point<Number>(coordinates));
			}
			return Representation(pointVector);
		}

		vector_t<Number> createVector(BenchmarkSetup<Number> _setup) const{
			//std::uniform_real_distribution<double> distr (double(_setup.minValue), double(_setup.maxValue));
			std::uniform_real_distribution<double> distr (carl::toDouble(_setup.minValue), carl::toDouble(_setup.maxValue));
			vector_t<Number> coordinates(_setup.dimension);
			for(unsigned j = 0; j < _setup.dimension; ++j) {
				coordinates(j) = Number(distr(mRand));
			}
			return coordinates;
		}

		Point<Number> createPoint(BenchmarkSetup<Number> _setup) const{
			return Point<Number>(createVector(_setup));
		}

		matrix_t<Number> createMatrix(BenchmarkSetup<Number> _setup) const{
			std::uniform_real_distribution<double> distr (0.0, 1.0); // Todo: Check if this is sufficient.
			matrix_t<Number> res(_setup.dimension, _setup.dimension);
			for(unsigned i = 0; i < _setup.dimension; ++i) {
				for(unsigned j = 0; j < _setup.dimension; ++j) {
					res(i,j) = Number(distr(mRand));
				}
			}
			return res;
		}

	private:
	 };

	template<typename Representation, typename Number>
	struct BaseGenerator {
	protected:
	 	//BenchmarkSetup<typename Representation::type> mSetup;
	 	BenchmarkSetup<Number> mSetup;
	 	ObjectGenerator<Representation,Number> mGenerator;
	 public:
	 	typedef void type;
	 	//BaseGenerator(const BenchmarkSetup<typename Representation::type>& _setup) : mSetup(_setup), mGenerator(_setup) {}
	 	BaseGenerator(const BenchmarkSetup<Number>& _setup) : mSetup(_setup), mGenerator(_setup) {}
	 	void operator()() const {}
	 };
} // namespace
