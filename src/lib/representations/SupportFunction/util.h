/*
 * @file   util.h
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 *
 * @since	February 24, 2015
 * @version	February 24, 2015
 */

#pragma once
#include "../../config.h"
#include "../../types.h"

namespace hypro {
// This enum represents the support function type and is used to identify support function without instanceof operations
enum SF_TYPE { SUM, INTERSECT, LINTRAFO, SCALE, UNION, POLY, INFTY_BALL, TWO_BALL, ELLIPSOID, BOX, ZONOTOPE, NONE };


	template<typename Number>
	struct lintrafoParameters {
		unsigned power = 2; // 2^power operations are collected
		mutable std::map<unsigned, matrix_t<Number>> matrices;
		mutable std::map<unsigned, vector_t<Number>> vectors;

		lintrafoParameters() = delete;
		lintrafoParameters(const matrix_t<Number>& _A, const vector_t<Number>& _b, unsigned _power = 2) :
			power(_power)
		{
			//std::cout << this << " Create Parameterset A: " << _A << " and b: " << _b << std::endl;
			assert(_A.rows() == _b.rows());
			matrices[1] = _A;
			vectors[1] = _b;
		}

		matrix_t<Number> matrix() const {
			return matrices.begin()->second;
		}

		vector_t<Number> vector() const {
			return vectors.begin()->second;
		}

		std::pair<matrix_t<Number>, vector_t<Number>> getParameterSet(unsigned exponent) const {
			//std::cout << this << " Request parameter set for exponent " << exponent << std::endl;
			if(matrices.find(exponent) != matrices.end()){
				return std::make_pair(matrices.at(exponent), vectors.at(exponent));
			}
			// create new parameters
			while((--matrices.end())->first < exponent) {
				createNextReduct();
			}
			assert(matrices.find(exponent) != matrices.end());
			return std::make_pair(matrices.at(exponent), vectors.at(exponent));
		};

		void createNextReduct() const {
			// the last created reduction pair is at the back, as a std::map is per default sorted ascending
			assert(matrices.size() == vectors.size());
			assert(matrices.size() > 0);
			std::size_t powerOfTwo = carl::pow(2, power);
			// first compute the new b
			vector_t<Number> bTrans = (--vectors.end())->second;
			matrix_t<Number> aTrans = (--matrices.end())->second;
			//std::cout << "Starting from exponent " << (--matrices.end())->first << std::endl;
			unsigned exponent = ((--matrices.end())->first) * powerOfTwo;
			//std::cout << "New exponent: " << exponent << std::endl;
			// accumulate b
			for (std::size_t i = 1; i < powerOfTwo ; i++){
				// Note: aTrans hasn't changed yet -> we can use it for transformation.
				bTrans = aTrans*bTrans + (--vectors.end())->second;
			}
			// accumulate A
			for (std::size_t i = 0; i < power; i++){
				aTrans = aTrans*aTrans;
			}
			matrices[exponent] = aTrans;
			vectors[exponent] = bTrans;
		}

		bool operator== (const lintrafoParameters<Number>& rhs) const {
			return (this->matrices.begin()->second == rhs.matrices.begin()->second && this->vectors.begin()->second == rhs.vectors.begin()->second);
		}

	};

}
