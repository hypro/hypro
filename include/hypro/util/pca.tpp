/**
 * Implementation of principal component analysis for a set of sample points.
 * @file  pca.tpp
 * @author Simon Froitzheim
 *
 * @since       2015-02-15
 * @version	2016-03-17
 */

#include "pca.h"

namespace hypro {

template <typename Number>
const std::vector<Halfspace<Number>> PrincipalComponentAnalysis<Number>::box() const {
	if ( mBoxComputed ) {
		return mBoxConstraints;
	}
	computeOrientedBox();
	return mBoxConstraints;
}

template <typename Number>
void PrincipalComponentAnalysis<Number>::setSamples( const std::vector<Point<Number>>& samples ) {
	mSamples = samples;
	mMeanComputed = false;
	mBoxComputed = false;
	mBoxConstraints.clear();
}

template <typename Number>
void PrincipalComponentAnalysis<Number>::computeMean() const {
	if ( !mSamples.empty() ) {
		mMean = Point<Number>( vector_t<Number>::Zero( mSamples.at( 0 ).dimension() ) );
		// computes the sum of all sample points
		for ( unsigned i = 0; i < mSamples.size(); ++i ) {
			mMean += mSamples[i];
		}
		// computes the arithmetic mean of the sample points
		mMean = mMean.rawCoordinates() * ( ( (Number)1 ) / Number( mSamples.size() ) );
	}
	mMeanComputed = true;
}

template <typename Number>
void PrincipalComponentAnalysis<Number>::computeOrientedBox() const {
	if ( !mSamples.empty() ) {
		// gets dimension of sample points
		long dim = mSamples.begin()->rawCoordinates().rows();
		// gets number of sample points
		long sSize = mSamples.size();

		computeMean();

		std::vector<Point<Number>> tSamples = mSamples;
		// computes the set of translated sample points
		for ( unsigned i = 0; i < sSize; ++i ) {
			tSamples[i] -= mMean;
		}
		matrix_t<Number> sMatrix = matrix_t<Number>::Zero( dim, sSize );

		// builds the sampling matrix
		for ( unsigned i = 0; i < sSize; ++i ) {
			sMatrix.col( i ) = tSamples[i].rawCoordinates();
		}

		// computes the sample covariance matrix (represents the distribution of the mSamples)
		matrix_t<Number> covMatrix;
		if ( sSize > 1 ) {
			covMatrix = ( ( (Number)1 ) / Number( ( sSize - 1 ) ) ) * sMatrix * sMatrix.transpose();
		} else {
			covMatrix = sMatrix * sMatrix.transpose();
		}

		// conversion from the covariance matrix to double in order for JacobiSVD to work
		Eigen::MatrixXd doubleCovMatrix = convert<Number, double>( covMatrix );

		// computes the singular value decomposition of the sample covariance matrix (only U component from U*Sigma*V^T needed)
		Eigen::JacobiSVD<Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>, Eigen::NoQRPreconditioner> svd = Eigen::JacobiSVD<Eigen::MatrixXd, Eigen::NoQRPreconditioner>( doubleCovMatrix, Eigen::ComputeThinU );
		Eigen::MatrixXd u = svd.matrixU();

		// conversion back to Number
		matrix_t<Number> numberU = convert<double, Number>( u );

		// computes halfspaces with the help of U in two steps
		// first step: compute the maximum/minimum product of transposed translated mSamples (tSamples) with the corresponding column of U
		vector_t<Number> max = vector_t<Number>( dim );
		vector_t<Number> min = vector_t<Number>( dim );
		for ( unsigned i = 0; i < dim; ++i ) {
			max( i ) = tSamples[0].rawCoordinates().dot( numberU.col( i ) );
			min( i ) = tSamples[0].rawCoordinates().dot( numberU.col( i ) );
			for ( unsigned j = 0; j < sSize; ++j ) {
				Number tmp = tSamples[j].rawCoordinates().dot( numberU.col( i ) );
				if ( tmp > max( i ) ) {
					max( i ) = tmp;
				}
				if ( tmp < min( i ) ) {
					min( i ) = tmp;
				}
			}
		}

		// second step: create Halfspaces with the given normals and maximum/minimum products
		mBoxConstraints = std::vector<Halfspace<Number>>( 2 * dim );
		for ( unsigned i = 0; i < dim; ++i ) {
			mBoxConstraints[2 * i] = Halfspace<Number>( numberU.col( i ), max( i ) + numberU.col( i ).dot( mMean.rawCoordinates() ) );
			mBoxConstraints[2 * i + 1] = Halfspace<Number>( -numberU.col( i ), -min( i ) - numberU.col( i ).dot( mMean.rawCoordinates() ) );
		}
	}
	mBoxComputed = true;
}

}  // namespace hypro
