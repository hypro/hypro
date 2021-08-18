/*
 * File:   Utility.h
 * Author: jongan
 *
 * Created on October 27, 2014, 11:53 AM
 *
 * Reviewed by Leonardo Winter Pereira (leonardowinterpereira@gmail.com)
 * version 1.1 on September 15, 2015
 */

#pragma once

#include "../../config.h"

#include <cmath>

namespace hypro {
namespace ZUtility {

// Options for checking for intersect
enum IntersectionMethod_t { ALAMO = 1,
							NDPROJECTION = 2,
							DICHOTOMIC2D = 3 };

template <typename Number>
bool compareVectors( const hypro::vector_t<Number>& v1, const hypro::vector_t<Number>& v2 ) {
	Number v1_sum = v1.array().abs().matrix().sum();
	Number v2_sum = v2.array().abs().matrix().sum();
	Number v1_inf = v1.array().abs().maxCoeff();
	Number v2_inf = v2.array().abs().maxCoeff();

	return ( v1_sum - v1_inf ) < ( v2_sum - v2_inf );
}

template <typename Number>
bool compareColumnVectors( const hypro::vector_t<Number>& colvec1, const hypro::vector_t<Number>& colvec2 ) {
	Number x1( colvec1( 0 ) ), x2( colvec2( 0 ) ), y1( colvec1( 1 ) ), y2( colvec2( 1 ) );

	Number ang1 = x1 / carl::sqrt( x1 * x1 + y1 * y1 );
	Number ang2 = x2 / carl::sqrt( x2 * x2 + y2 * y2 );

	return ( ang1 < ang2 );
}

template <typename Number>
std::vector<hypro::vector_t<Number>> getCornersRecursive( const hypro::matrix_t<Number> _remainingGenerators, hypro::vector_t<Number>& _current ) {
	// std::cout << __func__ << ": remainingGenerators: " << _remainingGenerators << " and current: " << _current << std::endl;
	std::vector<hypro::vector_t<Number>> res;
	if ( _remainingGenerators.cols() == 0 ) {
		if ( _current.rows() == 0 ) {
			return res;
		}
		res.emplace_back( _current );
		return res;
	}

	if ( _remainingGenerators.cols() == 1 ) {
		res.push_back( hypro::vector_t<Number>( _current + _remainingGenerators.col( 0 ) ) );
		res.push_back( hypro::vector_t<Number>( _current - _remainingGenerators.col( 0 ) ) );
	} else {
		std::vector<hypro::vector_t<Number>> res2;

		hypro::vector_t<Number> pos = hypro::vector_t<Number>( _current + _remainingGenerators.col( 0 ) );
		hypro::vector_t<Number> neg = hypro::vector_t<Number>( _current - _remainingGenerators.col( 0 ) );

		res = getCornersRecursive( hypro::matrix_t<Number>( _remainingGenerators.block( 0, 1, _remainingGenerators.rows(), _remainingGenerators.cols() - 1 ) ), pos );
		res2 = getCornersRecursive( hypro::matrix_t<Number>( _remainingGenerators.block( 0, 1, _remainingGenerators.rows(), _remainingGenerators.cols() - 1 ) ), neg );

		res.insert( res.end(), res2.begin(), res2.end() );
	}
	return res;
}

template <typename Number>
bool compareYVal( const hypro::vector_t<Number>& colvec1, const hypro::vector_t<Number>& colvec2 ) {
	return ( colvec1( 1 ) < colvec2( 1 ) );
}

template <typename Number>
bool compareXVal( const hypro::vector_t<Number>& colvec1, const hypro::vector_t<Number>& colvec2 ) {
	return ( colvec1( 0 ) < colvec2( 0 ) );
}

template <typename Number>
struct Line_t {
	Line_t(){};
	Line_t( Eigen::Matrix<Number, 2, 1> pt_, Eigen::Matrix<Number, 2, 1> direction_ ) {
		point = pt_;
		direction = direction_;
	}

	Eigen::Matrix<Number, 2, 1> point;
	Eigen::Matrix<Number, 2, 1> direction;
};

}  // namespace ZUtility
}  // namespace hypro
