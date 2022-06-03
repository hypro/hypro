#pragma once

#include "../../datastructures/Point.h"
#include "../GeometricObjectBase.h"

#include <random>
#include <set>

namespace hypro {
template <typename Number, typename Converter, typename Settings>
std::set<Point<Number>> uniform_sampling( const ZonotopeT<Number, Converter, Settings>& set, std::size_t num_samples, std::size_t max_trials = 10 ) {
    const int dim = set.generators().cols();

    std::set<Point<Number>> samples;

    if ( set.empty() ) {
		TRACE( "hypro.representations.sampling", "The specified set is empty." );
		return samples;
	}

	// declare random distributions
	std::random_device rd;	   // Will be used to obtain a seed for the random number engine
	std::mt19937 gen( rd() );  // Standard mersenne_twister_engine seeded with rd()
	std::vector<std::uniform_real_distribution<double>> distributions;

	// initialize the random distributions (n = dimension of the representation)
	for ( int j = 0; j < dim; j++ ) {
		distributions.push_back( std::uniform_real_distribution<>(-1.0, +1.0) );
	}

	// try to find the required number of samples
	std::size_t i = 0;
	while ( i < max_trials * num_samples ) {
		hypro::vector_t<Number> candidate_vector = hypro::vector_t<Number>( dim );

		for ( int j = 0; j < dim; j++ ) {
			candidate_vector[j] = carl::convert<double, Number>( distributions[j]( gen ) );
		}

        samples.insert( hypro::Point<Number>{ set.center() + set.generators() * candidate_vector } );

        if ( samples.size() == num_samples ) {
            return samples;
        }

		i++;
	}

	TRACE( "hypro.representations.sampling", "Could not find the required number of samples" );
	return samples;
}

template <typename Number, typename Converter, typename Settings>
std::set<Point<Number>> uniform_sampling( const StarsetT<Number, Converter, Settings>& set, std::size_t num_samples, std::size_t max_trials = 10 ) {
	const int dim = set.constraints().dimension();

	std::set<Point<Number>> samples;

	if ( set.empty() ) {
		TRACE( "hypro.representations.sampling", "The specified set is empty." );
		return samples;
	}

	// find the bounding box
	auto bounding_box = Converter::toBox( set.constraints() );

	// declare random distributions
	std::random_device rd;	   // Will be used to obtain a seed for the random number engine
	std::mt19937 gen( rd() );  // Standard mersenne_twister_engine seeded with rd()
	std::vector<std::uniform_real_distribution<double>> distributions;

	// initialize the random distributions (n = dimension of the representation)
	for ( int j = 0; j < dim; j++ ) {
		distributions.push_back( std::uniform_real_distribution<>(
			  carl::convert<Number, double>( bounding_box.interval( j ).lower() ),
			  carl::convert<Number, double>( bounding_box.interval( j ).upper() ) ) );
	}

	// try to find the required number of samples
	std::size_t i = 0;
	while ( i < max_trials * num_samples ) {
		hypro::vector_t<Number> candidate_vector = hypro::vector_t<Number>( dim );

		for ( int j = 0; j < dim; j++ ) {
			candidate_vector[j] = carl::convert<double, Number>( distributions[j]( gen ) );
		}

		if ( set.constraints().contains( candidate_vector ) ) {
			samples.insert( hypro::Point<Number>{ set.center() + set.generator() * candidate_vector } );

			if ( samples.size() == num_samples ) {
				return samples;
			}
		}

		i++;
	}

	TRACE( "hypro.representations.sampling", "Could not find the required number of samples" );
	return samples;
}

// template<template<typename, typename...> class Set, typename Number, typename... rest>
// std::set<Point<Number>> uniform_sampling(const Set<Number, rest...>& set, std::size_t num_samples, std::size_t max_trials = 10) {
template <typename Set>
std::set<Point<typename Set::NumberType>> uniform_sampling( const Set& set, std::size_t num_samples, std::size_t max_trials = 10 ) {
	using Number = typename Set::NumberType;
	const int dim = set.dimension();

	std::set<Point<Number>> samples;

	if ( set.empty() ) {
		TRACE( "hypro.representations.sampling", "The specified set is empty." );
		return samples;
	}

	// find the bounding box
	auto bounding_box = Converter<Number>::toBox( set );

	// declare random distributions
	std::random_device rd;	   // Will be used to obtain a seed for the random number engine
	std::mt19937 gen( rd() );  // Standard mersenne_twister_engine seeded with rd()
	std::vector<std::uniform_real_distribution<double>> distributions;

	// initialize the random distributions (n = dimension of the representation)
	for ( int j = 0; j < dim; j++ ) {
		distributions.push_back( std::uniform_real_distribution<>(
			  carl::convert<Number, double>( bounding_box.interval( j ).lower() ),
			  carl::convert<Number, double>( bounding_box.interval( j ).upper() ) ) );
	}

	// try to find the required number of samples
	std::size_t i = 0;
	while ( i < max_trials * num_samples ) {
		hypro::vector_t<Number> candidate_vector = hypro::vector_t<Number>( dim );

		for ( int j = 0; j < dim; j++ ) {
			candidate_vector[j] = carl::convert<double, Number>( distributions[j]( gen ) );
		}

		hypro::Point<Number> candidate{ candidate_vector };
		if ( set.contains( candidate ) ) {
			samples.insert( candidate );

			if ( samples.size() == num_samples ) {
				return samples;
			}
		}

		i++;
	}

	TRACE( "hypro.representations.sampling", "Could not find the required number of samples" );
	return samples;
}

// TODO:
// continue working on the CEGAR approach and use the already implemented sampling method
// implement starset.contains() in a better way
// have 2 methods for starset.contains(Point) 1. with converstion to HPolyTope + Caching / other with only simplex SAT-solving 
// sampling a set such that the samples are close to the bounderies:
// 1. sample a point uniformly
// 2. pick the closest halfplane
// 3. move the sample towards the halfplane
//      random number between r \in [0, eps]
//      move the point distance * (1 - r)

}  // namespace hypro
