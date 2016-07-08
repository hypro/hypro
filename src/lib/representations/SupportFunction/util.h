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
		std::map<unsigned, matrix_t<Number>> matrices;
		std::map<unsigned, vector_t<Number>> vectors;


		void createNextReduct(){
			// the last created reduction pair is at the back, as a std::map is per default sorted ascending
			assert(matrices.size() == vectors.size());
			assert(matrices.size() > 0);
			std::size_t powerOfTwo = carl::pow(2, power);
			// first compute the new b
			vector_t<Number> bTrans = (--vectors.end())->second;
			matrix_t<Number> aTrans = (--matrices.end())->second;
			unsigned exponent = carl::pow(2, (--matrices.end())->first);
			// accumulate b
			for (std::size_t i = 1; i < powerOfTwo ; i++){
				// Note: aTrans hasn't changed yet.
				bTrans = aTrans*((--vectors.end())->second) + (--vectors.end())->second;
			}
			// accumulate A
			for (std::size_t i = 0; i < power; i++){
				aTrans = aTrans*aTrans;
			}
			matrices[exponent] = aTrans;
			vectors[exponent] = bTrans;
		}

	};

}
