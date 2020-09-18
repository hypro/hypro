/* This file holds all type utils such as convenient constructors.
 * @file   types.h
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 *
 * @since	2014-11-25
 * @version	2014-11-25
 */

#pragma once
#include <cassert>
#include <hypro/types.h>
#include <hypro/util/VariablePool.h>
#include <vector>

namespace hypro {

template <typename Number>
class Point;

template <typename Number>
static matrix_t<Number> createMatrix( const std::vector<std::vector<Number> >& _in ) {
	assert( !_in.empty() );
	matrix_t<Number> result( _in.size(), ( *_in.begin() ).size() );
	for ( unsigned lineId = 0; lineId != _in.size(); ++lineId ) {
		for ( unsigned rowId = 0; rowId != _in[lineId].size(); ++rowId ) {
			result( lineId, rowId ) = Number( _in[lineId][rowId] );
		}
	}
	return result;
}

template <typename Number>
static vector_t<Number> createVector( const std::vector<Number>& _in ) {
	assert( !_in.empty() );
	vector_t<Number> result( _in.size() );
	for ( unsigned rowId = 0; rowId != _in.size(); ++rowId ) {
		result( rowId ) = Number( _in[rowId] );
	}
	return result;
}

template <typename Number>
static vector_t<Number> createVector( const Point<Number>& _in ) {
	vector_t<Number> result( _in.dimension() );
	for ( unsigned rowId = 0; rowId != _in.dimension(); ++rowId ) {
		result( rowId ) = Number( _in.at( VariablePool::getInstance().carlVarByIndex( rowId ) ) );
	}
	return result;
}

template <typename Number>
static vector_t<Number> createVector( std::initializer_list<Number> _coordinates ) {
	vector_t<Number> res = vector_t<Number>( _coordinates.size() );
	unsigned count = 0;
	for ( auto& coordinate : _coordinates ) {
		res( count ) = Number( coordinate );
		++count;
	}
	return res;
}

}  // namespace hypro
