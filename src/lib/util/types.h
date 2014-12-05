/* This file holds all type utils such as convenient constructors.
 * @file   types.h
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 *
 * @since	2014-11-25
 * @version	2014-11-25
 */

#pragma once
#include <vector>
#include <cassert>
#include "../config.h"

namespace hypro{

template<typename Number>
static hypro::matrix_t<Number> createMatrix(const std::vector<std::vector<Number> >& _in)
{
	assert(!_in.empty());
	hypro::matrix_t<Number> result(_in.size(), (*_in.begin()).size());
	for(unsigned lineId = 0; lineId != _in.size(); ++lineId)
	{
		for(unsigned rowId = 0; rowId != _in[lineId].size(); ++rowId)
		{
			result(lineId, rowId) = Number(_in[lineId][rowId]);
		}
	}
	return result;
}

template<typename Number>
static hypro::vector_t<Number> createVector(const std::vector<Number>& _in)
{
	assert(!_in.empty());
	hypro::vector_t<Number> result(_in.size());
	for(unsigned rowId = 0; rowId != _in.size(); ++rowId)
	{
		result(rowId) = Number(_in[rowId]);
	}
	return result;
}

} // namespace

