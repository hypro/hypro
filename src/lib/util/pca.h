/**
 * Implementation of principal component analysis for a set of sample points.
 * @file  pca.h
 * @author Simon Froitzheim
 *
 * @since       2015-02-15
 * @version     2015-02-15
 */

#pragma once

#include "../datastructures/Point.h"
#include "../datastructures/Halfspace.h"


namespace hypro {

template <typename Number>
class pca{
    public:

        static std::vector<Halfspace<Number>> computeOrientedBox(const std::vector<Point<Number>>& samples);

};






} //namespace

#include "pca.tpp"
