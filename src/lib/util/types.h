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

static matrix createMatrix(const std::vector<std::vector<double> >& _in)
{
	assert(!_in.empty());
	matrix result(_in.size(), (*_in.begin()).size());
	for(unsigned lineId = 0; lineId != _in.size(); ++lineId)
	{
		for(unsigned rowId = 0; rowId != _in[lineId].size(); ++rowId)
		{
			result(lineId, rowId) = number(_in[lineId][rowId]);
		}
	}
	return result;
}

static vector createVector(const std::vector<double>& _in)
{
	assert(!_in.empty());
	vector result(_in.size());
	for(unsigned rowId = 0; rowId != _in.size(); ++rowId)
	{
		result(rowId) = number(_in[rowId]);
	}
	return result;
}

} // namespace

