/**
 * This file holds the vertex enumeration algorithm presented by Avis and Fukuda.
 * @file vertexEnumeration.h
 *
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 *
 * @since	2015-10-29
 * @version	2015-10-29
 */

#pragma once;

#include "../config.h"
#include "../datastructures/Point.h"

namespace hypro {

template<typename Number>
struct dictionary {
	matrix_t<Number> 	mMatrix;
	std::size_t			mF;
	std::size_t			mG;

	dictionary (const matrix_t<Number>& A, std::size_t f, std::size_t g) :
		mMatrix(A),
		mF(f),
		mG(g)
	{}

	Point<Number> vertex() const;
}

}