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
enum SF_TYPE { SUM, INTERSECT, LINTRAFO, SCALE, UNION, POLY, INFTY_BALL, TWO_BALL, ELLIPSOID, BOX, ZONOTOPE, PROJECTION, NONE };


	template<typename Number>
	struct lintrafoParameters {
		unsigned power = 2; // 2^power operations are collected
		mutable std::map<unsigned, std::pair<matrix_t<Number>, vector_t<Number>>> parameters;

		lintrafoParameters() = delete;
		lintrafoParameters(const matrix_t<Number>& _A, const vector_t<Number>& _b, unsigned _power = 2) :
			power(_power)
		{
			assert(_A.rows() == _b.rows());
			parameters[1] = std::make_pair(_A, _b);
		}

		matrix_t<Number> matrix() const {
			assert(parameters.begin().first == 1);
			return parameters.begin()->second.first;
		}

		vector_t<Number> vector() const {
			assert(parameters.begin().first == 1);
			return parameters.begin()->second.second;
		}

		const std::pair<matrix_t<Number>, vector_t<Number>>& getParameterSet(unsigned exponent) const {
			//std::cout << this << " Request parameter set for exponent " << exponent << std::endl;
			if(parameters.find(exponent) != parameters.end()){
				return parameters.at(exponent);
			}
			// create new parameters
			while((--parameters.end())->first < exponent) {
				createNextReduct();
			}
			assert(parameters.find(exponent) != parameters.end());
			return parameters.at(exponent);
		};

		void createNextReduct() const {
			// the last created reduction pair is at the back, as a std::map is per default sorted ascending
			assert(parameters.size() > 0);
			std::size_t powerOfTwo = carl::pow(2, power);
			// first compute the new b
			vector_t<Number> bTrans = (--parameters.end())->second.second;
			matrix_t<Number> aTrans = (--parameters.end())->second.first;
			//std::cout << "Starting from exponent " << (--matrices.end())->first << std::endl;
			unsigned exponent = ((--parameters.end())->first) * powerOfTwo;
			//std::cout << "New exponent: " << exponent << std::endl;
			// accumulate b
			for (std::size_t i = 1; i < powerOfTwo ; i++){
				// Note: aTrans hasn't changed yet -> we can use it for transformation.
				bTrans = aTrans*bTrans + (--parameters.end())->second.second;
			}
			// accumulate A
			for (std::size_t i = 0; i < power; i++){
				aTrans = aTrans*aTrans;
			}
			parameters[exponent] = std::make_pair(aTrans, bTrans);
		}

		bool operator== (const lintrafoParameters<Number>& rhs) const {
			return (this->parameters.begin()->second == rhs.parameters.begin()->second);
		}

	};

}
