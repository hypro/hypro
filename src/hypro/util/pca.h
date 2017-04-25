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
class PrincipalComponentAnalysis{
	private:
		mutable Point<Number> mMean;
		std::vector<Point<Number>> mSamples;
		mutable std::vector<Halfspace<Number>> mBoxConstraints;
		mutable bool mBoxComputed = false;
		mutable bool mMeanComputed = false;

    public:

    	PrincipalComponentAnalysis() = default;
    	PrincipalComponentAnalysis( const std::vector<Point<Number>>& samples ) :
    		mMean(),
    		mSamples(samples),
    		mBoxConstraints(),
    		mBoxComputed(false),
    		mMeanComputed(false)
    	{}

    	PrincipalComponentAnalysis(const PrincipalComponentAnalysis<Number>& orig) = default;

        const Point<Number>& mean() const;
        const std::vector<Point<Number>>& samples() const { return mSamples; }
        const std::vector<Halfspace<Number>> box() const;

        void setSamples(const std::vector<Point<Number>>& samples);

        void computeMean() const;
        void computeOrientedBox() const;
};

} //namespace

#include "pca.tpp"
