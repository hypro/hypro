/**
 * Implementation of principal component analysis for a set of sample points.
 * @file  pca.h
 * @author Simon Froitzheim
 *
 * @since       2015-02-15
 * @version     2015-02-15
 */

#pragma once

#include "../datastructures/Halfspace.h"
#include "../datastructures/Point.h"

namespace hypro {

/**
 * @brief Class implementing principal component analysis
 * @tparam Number
 */
template <typename Number>
class PrincipalComponentAnalysis {
  private:
	mutable Point<Number> mMean;							 ///< mean value of sample set
	std::vector<Point<Number>> mSamples;					 ///< sample set
	mutable std::vector<Halfspace<Number>> mBoxConstraints;	 ///< oriented bounding box
	mutable bool mBoxComputed = false;						 ///< flag to indicate box has been computed
	mutable bool mMeanComputed = false;						 ///< flag to indicate mean has been computed

  public:
	/// default constructor
	PrincipalComponentAnalysis() = default;
	/**
	 * @brief Construct a new Principal Component Analysis object from a set of samples
	 * @param samples
	 */
	PrincipalComponentAnalysis( const std::vector<Point<Number>>& samples )
		: mMean()
		, mSamples( samples )
		, mBoxConstraints()
		, mBoxComputed( false )
		, mMeanComputed( false ) {}

	/// copy constructor
	PrincipalComponentAnalysis( const PrincipalComponentAnalysis<Number>& orig ) = default;

	/// returns the mean value over the sample set
	const Point<Number>& mean() const;
	/// getter for the sample set
	const std::vector<Point<Number>>& samples() const { return mSamples; }
	/// returns the oriented bounding box of the sample set
	const std::vector<Halfspace<Number>> box() const;

	/// setter for sample set
	void setSamples( const std::vector<Point<Number>>& samples );
	/// method to call mean-value computation
	void computeMean() const;
	/// method to call computation of oriented bounding box
	void computeOrientedBox() const;
};

}  // namespace hypro

#include "pca.tpp"
