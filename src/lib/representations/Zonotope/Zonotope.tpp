#include "Zonotope.h"
#include <assert.h>
#include <Eigen/src/Core/PlainObjectBase.h>
#include <Eigen/LU>
#include <cmath>
#include <algorithm>

using namespace Parma_Polyhedra_Library;

namespace hypro {

/*****************************************************************************
 *                                                                           *
 *                          Non-member functions                             *
 *                                                                           *
 *****************************************************************************/

template <typename Number>
bool comparePoint( Eigen::Matrix<Number, 2, 1> &p1, Eigen::Matrix<Number, 2, 1> &p2 ) {
	if ( p1( 0 ) != p2( 0 ) )
		return ( p1( 0 ) < p2( 0 ) );
	else
		return ( p1( 1 ) < p2( 1 ) );
}

template <typename Number>
void removeGenerator( unsigned colToRemove, hypro::matrix_t<Number> &matrix ) {
	unsigned numRows = matrix.rows();
	unsigned numCols = matrix.cols() - 1;
	assert( matrix.cols() > 1 && "cannot remove a generator from a one-generator generator" );
	if ( colToRemove < numCols ) {
		assert( numCols - colToRemove > 0 );
		assert( colToRemove + 1 <= matrix.cols() - 1 );
		matrix.block( 0, colToRemove, numRows, numCols - colToRemove ) =
			  matrix.block( 0, colToRemove + 1, numRows, numCols - colToRemove );
	}
	matrix.conservativeResize( Eigen::NoChange, numCols );
}

template <typename Number>
void removeEmptyGenerators( hypro::matrix_t<Number> &generatorMatrix ) {
	unsigned dim = generatorMatrix.rows();
	hypro::vector_t<Number> zero_vector;
	zero_vector.resize( dim, 1 );
	zero_vector.setZero();

	std::vector<unsigned> zeroIndex;
	for ( unsigned i = 0; i < generatorMatrix.cols(); i++ ) {
		if ( generatorMatrix.col( i ) == zero_vector ) {
			zeroIndex.push_back( i );
		}
	}

	for ( std::vector<unsigned>::reverse_iterator rit = zeroIndex.rbegin(); rit != zeroIndex.rend(); ++rit ) {
		removeGenerator<Number>( *rit, generatorMatrix );
	}
}

template <typename Number>
Eigen::Matrix<Number, 2, 1> computeLineIntersection( const ZUtility::Line_t<Number> &l1,
													 const ZUtility::Line_t<Number> &l2 ) {
	Eigen::Matrix<Number, 2, 2> concatDirections;
	Eigen::Matrix<Number, 2, 1> a, resPt;

	concatDirections << l1.direction, -l2.direction;
	a = concatDirections.inverse() * ( l2.point - l1.point );
	resPt = l1.point + a( 0 ) * l1.direction;
	return resPt;
}

/*****************************************************************************
 *                                                                           *
 *            `         Member functions - Constructors                      *
 *                                                                           *
 *****************************************************************************/

template <typename Number>
Zonotope<Number>::Zonotope()
	: mDimension( 0 ), mCenter( 0, 1 ), mGenerators( 0, 0 ) {
}

template <typename Number>
Zonotope<Number>::Zonotope( std::size_t dimension )
	: mDimension( dimension )
	, mCenter( hypro::vector_t<Number>::Zero( dimension ) )
	, mGenerators( hypro::matrix_t<Number>::Zero( dimension, 1 ) ) {
	assert( dimension != 0 && "Zonotope cannot have dimension 0." );
}

template <typename Number>
Zonotope<Number>::Zonotope( const hypro::vector_t<Number> &center, const hypro::matrix_t<Number> &generators )
	: mDimension( center.rows() ), mCenter( center ), mGenerators( generators ) {
	assert( center.rows() == generators.rows() && "Center and generators have to have same dimensionality." );
}

template <typename Number>
Zonotope<Number>::Zonotope( const Zonotope<Number> &other )
	: mDimension( other.mDimension ), mCenter( other.mCenter ), mGenerators( other.mGenerators ) {
}

template <typename Number>
Zonotope<Number>::Zonotope( const Zonotope<Number> &other, unsigned d1, unsigned d2 ) {
	assert( other.mDimension != 0 && d1 >= 0 && d1 < other.mDimension && d2 >= 0 && d1 < other.mDimension && d1 != d2 &&
			"d1 and d2 have to be in range of copied zonotope." );

	Eigen::Matrix<Number, 2, 1> center;
	Eigen::Matrix<Number, 2, Eigen::Dynamic> generators;
	center = {other.center()( d1 ), other.center()( d2 )};

	generators.resize( Eigen::NoChange, other.numGenerators() );
	generators << other.generators().row( d1 ), other.generators().row( d2 );

	mDimension = 2;
	mCenter = center;
	mGenerators = generators;
}

template <typename Number>
Zonotope<Number>::~Zonotope() {
}

/*****************************************************************************
 *                                                                           *
 *      Member functions - Getters, Setters and non-algorithm functions      *
 *                                                                           *
 *****************************************************************************/

template <typename Number>
std::size_t Zonotope<Number>::dimension() const {
	return mDimension;
}

template <typename Number>
bool Zonotope<Number>::empty() const {
	return ( mGenerators.cols() == 0 );
}

template <typename Number>
hypro::vector_t<Number> Zonotope<Number>::center() const {
	return mCenter;
}

template <typename Number>
hypro::matrix_t<Number> Zonotope<Number>::generators() const {
	return mGenerators;
}

template <typename Number>
void Zonotope<Number>::setCenter( const hypro::vector_t<Number> &center ) {
	if ( mDimension == 0 ) {
		mDimension = center.rows();
		mGenerators = hypro::matrix_t<Number>::Zero( mDimension, 1 );
	}
	assert( (std::size_t)center.rows() == mDimension && "Center has to have same dimensionality as zonotope." );
	mCenter = center;
}

template <typename Number>
void Zonotope<Number>::setGenerators( const hypro::matrix_t<Number> &new_generators ) {
	if ( mDimension == 0 ) {
		mDimension = new_generators.rows();
		mCenter = hypro::vector_t<Number>::Zero( mDimension );
	}
	assert( (std::size_t)new_generators.rows() == mDimension && "Generators have to have same dimensionality as zonotope" );
	mGenerators = new_generators;
}

template <typename Number>
bool Zonotope<Number>::addGenerators( const hypro::matrix_t<Number> &generators ) {
	if ( mDimension == 0 ) {
		mDimension = generators.rows();
	}

	assert( (std::size_t)generators.rows() == mDimension && "Added generators has to have same dimensionality as zonotope" );
	if ( mGenerators.rows() != generators.rows() ) {
		setGenerators( generators );
	} else {
		hypro::matrix_t<Number> tmp = mGenerators;
		mGenerators.resize( tmp.rows(), generators.cols() + tmp.cols() );
		mGenerators << tmp, generators;
	}
	removeEmptyGenerators();
	return true;
}

template <typename Number>
std::size_t Zonotope<Number>::numGenerators() const {
	return mGenerators.cols();
}

template <typename Number>
void Zonotope<Number>::removeGenerator( unsigned colToRemove ) {
	unsigned numRows = mGenerators.rows();
	unsigned numCols = mGenerators.cols() - 1;

	if ( colToRemove < numCols )
		mGenerators.block( 0, colToRemove, numRows, numCols - colToRemove ) =
			  mGenerators.block( 0, colToRemove + 1, numRows, numCols - colToRemove );

	mGenerators.conservativeResize( numRows, numCols );
}

template <typename Number>
void Zonotope<Number>::removeEmptyGenerators() {
	// TODO
	hypro::vector_t<Number> zero_vector = hypro::vector_t<Number>::Zero( mDimension );

	std::vector<unsigned> zeroIndex;
	for ( unsigned i = 0; i < mGenerators.cols(); i++ ) {
		if ( mGenerators.col( i ) == zero_vector ) {
			zeroIndex.push_back( i );
		}
	}

	for ( std::vector<unsigned>::reverse_iterator rit = zeroIndex.rbegin(); rit != zeroIndex.rend(); ++rit ) {
		removeGenerator( *rit );
	}
}

template <typename Number>
void Zonotope<Number>::uniteEqualVectors() {
	hypro::vector_t<Number> zero_vector = hypro::vector_t<Number>::Zero( mDimension );

	std::vector<unsigned> zeroIndex;

	for ( unsigned i = 0; i < mGenerators.cols(); i++ ) {
		for ( unsigned j = ( i + 1 ); j < mGenerators.cols(); j++ ) {
			if ( mGenerators.col( i ) == mGenerators.col( j ) ) {
				zeroIndex.push_back( j );
			}
		}
		for ( std::vector<unsigned>::reverse_iterator rit = zeroIndex.rbegin(); rit != zeroIndex.rend(); ++rit ) {
			mGenerators.col( i ) += mGenerators.col( *rit );

			removeGenerator( *rit );
		}
		zeroIndex.clear();
	}
}

template <typename Number>
bool Zonotope<Number>::changeDimension( std::size_t new_dim ) {
	assert( new_dim != 0 && "Cannot change dimensionality of zonotope to zero" );
	if ( new_dim == mDimension ) {
		return false;
	} else {
		mCenter.conservativeResize( new_dim, Eigen::NoChange );
		mGenerators.conservativeResize( new_dim, Eigen::NoChange );

		// If new dim > old dim, initialize all new rows to zero
		for ( unsigned i = mDimension; i < new_dim; i++ ) {
			mCenter.row( i ).setZero();
			mGenerators.row( i ).setZero();
		}

		mDimension = new_dim;
		return true;
	}
}

template <typename Number>
void Zonotope<Number>::clear() {
	mGenerators.resize( 0, 0 );
	mCenter.resize( 0, 1 );
	mDimension = 0;
}

/*****************************************************************************
*                                                                           *
*                           Algorithm Functions                             *
*                                                                           *
*****************************************************************************/

template <typename Number>
Zonotope<Number> Zonotope<Number>::minkowskiSum( const Zonotope<Number> &rhs ) const {
	assert( mDimension == rhs.dimension() && "Zonotope on RHS must have same dimensionality as current." );
	Zonotope<Number> result;
	result.setCenter( this->mCenter + rhs.mCenter );
	hypro::matrix_t<Number> tmp;
	tmp.resize( mDimension, rhs.numGenerators() + numGenerators() );
	tmp << mGenerators, rhs.generators();
	result.setGenerators( tmp );
	result.removeEmptyGenerators();
	return result;
}

template <typename Number>
Zonotope<Number> Zonotope<Number>::linearTransformation( const hypro::matrix_t<Number> &A ) const {
	assert( A.cols() == mCenter.rows() &&
			"Matrix's dimensionality is different "
			"from zonotope's center's "
			"dimensionality." );
	assert( A.cols() == mGenerators.rows() &&
			"Matrix's dimensionality is "
			"different from zonotope's "
			"generators' dimensionality." );
	Zonotope<Number> result;
	result.setCenter( A * this->mCenter );
	result.setGenerators( A * this->mGenerators );

	return result;
}

template <typename Number>
std::vector<hypro::vector_t<Number>> Zonotope<Number>::computeZonotopeBoundary() {
	assert( mDimension == 2 && "Computing Zonotope boundaries only possible for Dim 2" );

	this->removeEmptyGenerators();
	hypro::matrix_t<Number> generators = this->mGenerators;

	unsigned i;
	std::vector<hypro::vector_t<Number>> sortArray, verticesArray;

	// Reflect generators if y-value is negative
	Eigen::Matrix<Number, 1, Eigen::Dynamic> yValsRow = generators.row( 1 );

	for ( i = 0; i < yValsRow.cols(); i++ ) {
		if ( yValsRow( i ) < 0 ) {
			generators.col( i ) = -1 * generators.col( i );
		}
	}

	// Sort generators

	for ( i = 0; i < generators.cols(); i++ ) {
		sortArray.push_back( generators.col( i ) );
	}

	std::sort( sortArray.begin(), sortArray.end(), ZUtility::compareColumnVectors<Number> );

	hypro::vector_t<Number> pm = mCenter - generators.rowwise().sum();

	verticesArray.push_back( pm );

	// Finding vertices of Zonotope
	for ( i = 0; i < sortArray.size(); i++ ) {
		verticesArray.push_back( verticesArray.back() + 2 * sortArray[i] );
	}
	for ( i = 0; i < sortArray.size(); i++ ) {
		verticesArray.push_back( verticesArray.back() - 2 * sortArray[i] );
	}

	return verticesArray;
}

template <typename Number>
std::vector<hypro::vector_t<Number>> Zonotope<Number>::vertices() {
	uniteEqualVectors();

	removeEmptyGenerators();

	hypro::vector_t<Number> init = hypro::vector_t<Number>::Zero( this->dimension() );

	std::vector<hypro::vector_t<Number>> possibleCorners = ZUtility::getCornersRecursive( mGenerators, init );

	return possibleCorners;
}

template <typename Number>
Number intersect2d( const Zonotope<Number> &input, const Hyperplane<Number> &hp, int minOrMax ) {
	assert( input.dimension() == hp.dimension() && input.dimension() == 2 &&
			"zonotope dimension must be of same dimension (only dim 2 accepted) "
			"as hyperplane" );
	unsigned numGenerators = input.numGenerators();
	hypro::matrix_t<Number> g1, g2, generators = input.generators();
	Eigen::Matrix<Number, 2, 1> s, s1, pmNext, pm = input.center();

	for ( unsigned i = 0; i < numGenerators; i++ ) {
		if ( ( generators( 1, i ) > 0 || ( generators( 1, i ) == 0 && generators( 0, i ) > 0 ) ) && minOrMax == 1 )
			generators.col( i ) = -1 * generators.col( i );
		else if ( ( generators( 1, i ) < 0 || ( generators( 1, i ) == 0 && generators( 0, i ) < 0 ) ) && minOrMax == 0 )
			generators.col( i ) = -1 * generators.col( i );

		pm = pm - generators.col( i );
	}

	std::vector<unsigned> indexToRemove;
	if ( pm( 0 ) <= hp.offset() ) {
		for ( unsigned i = 0; i < generators.cols(); i++ ) {
			if ( generators.col( i )( 0 ) <= 0 ) indexToRemove.push_back( i );
		}
	} else {
		for ( unsigned i = 0; i < generators.cols(); i++ ) {
			if ( generators.col( i )( 0 ) >= 0 ) indexToRemove.push_back( i );
		}
	}

	for ( std::vector<unsigned>::reverse_iterator rit = indexToRemove.rbegin(); rit != indexToRemove.rend(); ++rit ) {
		removeGenerator<Number>( *rit, generators );
	}

	s = 2 * generators.rowwise().sum();

	std::vector<unsigned> idx_a1, idx_a2;
	while ( generators.cols() > 1 ) {
		// collecting indices to delete
		// TODO: check if atan is available for FLOAT_T types
		for ( unsigned i = 0; i < generators.cols(); i++ ) {
			Number angle = atan( (Number)generators( 1, i ) / (Number)generators( 0, i ) );
			if ( angle - atan( (Number)s( 1 ) / (Number)s( 0 ) ) <= 0 )
				idx_a1.push_back( i );
			else if ( angle - atan( (Number)s( 1 ) / (Number)s( 0 ) ) >= 0 )
				idx_a2.push_back( i );
		}

		// clear generators of certain rows
		for ( std::vector<unsigned>::reverse_iterator rit = idx_a1.rbegin(); rit != idx_a1.rend(); ++rit ) {
			g1 = generators;
			removeGenerator<Number>( *rit, g1 );
		}
		for ( std::vector<unsigned>::reverse_iterator rit = idx_a2.rbegin(); rit != idx_a2.rend(); ++rit ) {
			g2 = generators;
			removeGenerator<Number>( *rit, g2 );
		}

		if ( pm( 0 ) < hp.offset() )
			s1 = ( minOrMax == 1 ) ? 2 * g1.rowwise().sum() : 2 * g2.rowwise().sum();

		else
			s1 = ( minOrMax == 1 ) ? 2 * g2.rowwise().sum() : 2 * g1.rowwise().sum();

		pmNext = pm + s1;
		if ( ( pm( 0 ) <= hp.offset() && pmNext( 0 ) >= hp.offset() ) ||
			 ( pm( 0 ) >= hp.offset() && pmNext( 0 ) <= hp.offset() ) ) {
			generators = ( minOrMax == 1 ) ? g2 : g1;
			s = s1;
		} else {
			generators = ( minOrMax == 1 ) ? g1 : g2;
			s = s - s1;
			pm = pmNext;
		}
	}
	pmNext = pm + s;
	Number m = pm( 1 ) + ( hp.offset() - pm( 0 ) ) * ( pmNext( 1 ) - pm( 1 ) ) / ( pmNext( 0 ) - pm( 0 ) );
	return m;
}

template <typename Number>
Zonotope<Number> intersectZonotopeHyperplaneDSearch( Zonotope<Number> &inputZonotope, const Hyperplane<Number> &hp ) {
	assert( inputZonotope.dimension() == hp.dimension() && inputZonotope.dimension() == 2 &&
			"zonotope dimension must be of same "
			"dimension (only dim 2 accepted) as "
			"hyperplane" );
	Number p1 = intersect2d<Number>( inputZonotope, hp, 1 );
	Eigen::Matrix<Number, 2, 1> p1Vec = {0, p1};
	Number p2 = intersect2d<Number>( inputZonotope, hp, 0 );
	Eigen::Matrix<Number, 2, 1> p2Vec = {0, p2};

	Zonotope<Number> res( ( p1Vec + p2Vec ) / 2, ( p1Vec - p2Vec ) / 2 );
	return res;
}

template <typename Number>
static Zonotope<Number> intersectZonotopeHyperplane( Zonotope<Number> &inputZonotope, const Hyperplane<Number> &hp,
													 hypro::matrix_t<Number> &minMaxOfLine ) {
	assert( inputZonotope.dimension() == hp.dimension() && "Zonotope and Hyperplane have to be of similar dimensions" );
	std::vector<hypro::vector_t<Number>> vertices = inputZonotope.computeZonotopeBoundary();
	vertices.pop_back();

	unsigned numPts = vertices.size();
	Eigen::Matrix<Number, 2, 2> xhp;

	// Compute hyperplane points xhp
	if ( hp.normal()( 1 ) == 0 ) {
		Eigen::Matrix<Number, 2, 1> minVecY, maxVecY;
		minVecY = *std::min_element( vertices.begin(), vertices.end(), ZUtility::compareYVal<Number> );
		maxVecY = *std::max_element( vertices.begin(), vertices.end(), ZUtility::compareYVal<Number> );

		xhp.row( 1 ) << ( minVecY( 1 ) - carl::abs( maxVecY( 1 ) - minVecY( 1 ) ) / 10 ),
			  ( maxVecY( 1 ) + carl::abs( maxVecY( 1 ) - minVecY( 1 ) ) / 10 );
		Eigen::Matrix<Number, 1, 2> eVec = {hp.offset(), hp.offset()};
		xhp.row( 0 ) = ( eVec - hp.normal()( 1 ) * xhp.row( 1 ) ) / hp.normal()( 0 );
	} else {
		Eigen::Matrix<Number, 2, 1> minVecX, maxVecX;
		minVecX = *std::min_element( vertices.begin(), vertices.end(), ZUtility::compareXVal<Number> );
		maxVecX = *std::max_element( vertices.begin(), vertices.end(), ZUtility::compareXVal<Number> );

		xhp.row( 0 ) << ( minVecX( 0 ) - carl::abs( maxVecX( 0 ) - minVecX( 0 ) ) / 10 ),
			  ( maxVecX( 0 ) + carl::abs( maxVecX( 0 ) - minVecX( 0 ) ) / 10 );
		Eigen::Matrix<Number, 1, 2> eVec = {hp.offset(), hp.offset()};
		xhp.row( 1 ) = ( eVec - hp.normal()( 0 ) * xhp.row( 0 ) ) / hp.normal()( 1 );
	}
	// Real algorithm starts here

	ZUtility::Line_t<Number> lnhp( xhp.col( 0 ), ( xhp.col( 1 ) - xhp.col( 0 ) ) );

	// Naming variables: dzbme is used for sorting vertices nearest to the line
	//                   dzb is used to keep track of d'*zb values
	std::valarray<Number> dzbme( vertices.size() ), dzb( vertices.size() );
	unsigned minIdx = 0, i;
	for ( i = 0; i < vertices.size(); i++ ) {
		dzbme[i] = ( hp.normal().transpose() * vertices[i] - hp.offset() );
		dzb[i] = ( hp.normal().transpose() * vertices[i] );
	}

	std::vector<int> ltZeroIdxArray, mtZeroIdxArray;
	for ( i = 0; i < dzbme.size(); i++ ) {
		if ( carl::abs( dzbme[i] ) < carl::abs( dzbme[minIdx] ) ) {
			minIdx = i;
		}
		if ( dzbme[i] < 0 ) ltZeroIdxArray.push_back( i );
		if ( dzbme[i] > 0 ) mtZeroIdxArray.push_back( i );
	}

	// TODO: circshift vertices vector
	dzb = dzb.cshift( minIdx );
	dzbme = dzbme.cshift( minIdx );

	// Essentially create a temporary val array to do cshift operation
	// and copy back value into vertices std::vector
	std::valarray<hypro::vector_t<Number>> verticesValArray( vertices.data(), vertices.size() );
	verticesValArray = verticesValArray.cshift( minIdx );
	vertices.assign( std::begin( verticesValArray ), std::end( verticesValArray ) );

	unsigned nil, il1p2, il2p1, il2p2;
	if ( dzbme[0] < 0 ) {
		nil = ltZeroIdxArray.size();
		if ( dzbme[1] < 0 ) {
			il1p2 = numPts;
			il2p1 = nil;
		} else {
			il1p2 = 2;
			il2p1 = numPts - nil + 1;
		}
	} else {
		nil = mtZeroIdxArray.size();
		if ( dzbme[1] > 0 ) {
			il1p2 = numPts;
			il2p1 = nil;
		} else {
			il1p2 = 2;
			il2p1 = numPts - nil + 1;
		}
	}

	if ( nil == 1 )
		il2p2 = 1;
	else
		il2p2 = il2p1 + 1;

	ZUtility::Line_t<Number> ln( vertices[0], vertices[il1p2 - 1] - vertices[0] );
	// TODO: compute line intersection
	Eigen::Matrix<Number, 2, 1> p1 = computeLineIntersection( ln, lnhp );

	ln.point = vertices[il2p1 - 1];
	ln.direction = vertices[il2p2 - 1] - vertices[il2p1 - 1];
	// TODO: compute line intersection
	Eigen::Matrix<Number, 2, 1> p2 = computeLineIntersection( ln, lnhp );

	Zonotope<Number> resZonotope( ( p1 + p2 ) / 2, ( p1 - p2 ) / 2 );

	minMaxOfLine.resize( 2, 2 );
	minMaxOfLine.row( 0 ) = ( comparePoint( p1, p2 ) ) ? p1.transpose() : p2.transpose();  // min [x,y] here
	minMaxOfLine.row( 1 ) = ( comparePoint( p1, p2 ) ) ? p2.transpose() : p1.transpose();  // max [x,y] here

	return resZonotope;
}

template <typename Number>
Zonotope<Number> intersectAlamo( const Zonotope<Number> &inputZonotope, const Hyperplane<Number> &hp ) {
	assert( inputZonotope.dimension() == hp.dimension() );
	// Determine intersect as Zonotope, according to Tabatabaeipour et al., 2013
	Number sgm = 0;  // could be redundant
	hypro::matrix_t<Number> H = inputZonotope.generators();
	hypro::matrix_t<Number> HHT = H * H.transpose();
	hypro::vector_t<Number> center = inputZonotope.center();
	hypro::vector_t<Number> lambda =
		  ( HHT * hp.normal() ) / ( hp.normal().transpose() * HHT * hp.normal() + sgm * sgm );

	hypro::matrix_t<Number> new_gen, identity;
	Zonotope<Number> zg( inputZonotope.dimension() );

	zg.setCenter( center + lambda * ( hp.offset() - hp.normal().transpose() * center ) );

	identity.resize( inputZonotope.dimension(), inputZonotope.dimension() );

	identity.setIdentity();

	new_gen = ( identity - lambda * ( hp.normal().transpose() ) ) * H;
	zg.setGenerators( new_gen );

	return zg;
}

template <typename Number>
Zonotope<Number> intersectNDProjection( const Zonotope<Number> &inputZonotope, const Hyperplane<Number> &hp,
										hypro::matrix_t<Number> &minMaxOfLine ) {
	assert( hp.dimension() == inputZonotope.dimension() &&
			"Intersect ND: input zonotope and input hyperplane must have same "
			"dimensionality" );
	Zonotope<Number> resultZonotope;
	hypro::vector_t<Number> dVec;
	hypro::matrix_t<Number> kernel;
	dVec = hp.normal();
	Eigen::JacobiSVD<hypro::matrix_t<Number>> svd( dVec.transpose(), Eigen::ComputeFullU | Eigen::ComputeFullV );
	// Using SVD to calculate nullspace (kernel)
	kernel = svd.matrixV().block( 0, 1, svd.matrixV().rows(), svd.matrixV().cols() - 1 );

	unsigned nd, dim;
	nd = kernel.cols();
	dim = inputZonotope.dimension();

	hypro::matrix_t<Number> dpQg, resultGenerators;
	Number dpQc;
	minMaxOfLine.resize( 2, nd );
	resultGenerators.resize( dim, nd );
	dpQc = dVec.dot( inputZonotope.center() );
	dpQg = dVec.transpose() * inputZonotope.generators();

	for ( unsigned i = 0; i < nd; i++ ) {
		// construct 2 dimensional Zonotope
		Eigen::Matrix<Number, 2, 1> projCenter;
		Eigen::Matrix<Number, 2, Eigen::Dynamic> projGenerators;

		projCenter << dpQc, kernel.col( i ).dot( inputZonotope.center() );
		projGenerators.resize( 2, dpQg.cols() );
		projGenerators << dpQg, kernel.col( i ).transpose() * inputZonotope.generators();

		Zonotope<Number> projZonotope( projCenter, projGenerators ), tempResZonotope;

		// Upon projection, the hyperplane now has a d vector of [1;0] but retains
		// its e scalar
		Eigen::Matrix<Number, 2, 1> lgDVector( 1, 0 );
		Hyperplane<Number> lg( lgDVector, hp.offset() );

		//        hypro::matrix_t<Number> dummyMinMax;
		tempResZonotope = intersectZonotopeHyperplaneDSearch( projZonotope, lg );

		Eigen::Matrix<Number, 2, 1> p1, p2;
		p1 = tempResZonotope.center() + tempResZonotope.generators();
		p2 = tempResZonotope.center() - tempResZonotope.generators();

		// find min and max points of intersect between zonogone and hyperplane
		// we only consider the y axis owing to the [1;0] property of the projected
		// space as mentioned earlier
		minMaxOfLine( 0, i ) = ( p1( 1 ) < p2( 1 ) ) ? p1( 1 ) : p2( 1 );
		minMaxOfLine( 1, i ) = ( p1( 1 ) > p2( 1 ) ) ? p1( 1 ) : p2( 1 );

		resultGenerators.conservativeResize( dim, i + 1 );
		resultGenerators.col( i ) << ( ( minMaxOfLine( 1, i ) - minMaxOfLine( 0, i ) ) / 2 ) * kernel.col( i );
	}

	resultZonotope.setCenter( kernel * ( ( minMaxOfLine.row( 1 ) + minMaxOfLine.row( 0 ) ) / 2 ).transpose() +
							  hp.offset() * dVec );
	resultZonotope.setGenerators( resultGenerators );

	return resultZonotope;
}

template <typename Number>
Zonotope<Number> Zonotope<Number>::intersect( const Hyperplane<Number> &hp, int method ) {
	hypro::matrix_t<Number> EMPTY_MATRIX( 0, 0 );
	return this->intersect( hp, EMPTY_MATRIX, method );
}

template <typename Number>
Zonotope<Number> Zonotope<Number>::intersect( const Hyperplane<Number> &hp, hypro::matrix_t<Number> &minMaxOfLine,
											  int method ) {
	assert( hp.dimension() == mDimension && "Zonotope's dimensionality must be same as Hyperplane's dimensionality." );

	Zonotope<Number> result;

	// Determine if intersection is found, according to Girard, Guernic, 2008
	Number emdc = hp.offset() - hp.normal().transpose() * mCenter;
	Number zs = ( hp.normal().transpose() * mGenerators ).array().abs().sum();

	bool hasIntersect = ( emdc > -zs && zs > emdc );
	if ( hasIntersect ) {
		switch ( method ) {
			case ZUtility::ALAMO:
				//                std::cout << "Using Alamo's method with dimension " <<
				//                mDimension << std::endl;
				result = intersectAlamo( *this, hp );
				break;
			case ZUtility::NDPROJECTION: {
				if ( mDimension == 2 ) {
					//                    std::cout << "Using Girard's method with dimension
					//                    2 " << std::endl;
					result = intersectZonotopeHyperplane( *this, hp, minMaxOfLine );

				} else {
					//                    std::cout << "Using Girard's method with dimension
					//                    " << mDimension <<
					//                    std::endl;
					result = intersectNDProjection<Number>( *this, hp, minMaxOfLine );
				}
				break;
			}
			//            case DICHOTOMIC2D:
			//                assert(mDimension==2);
			//                result = intersectZonotopeHyperplaneDSearch(*this, hp);
			//                break;
			default:
				break;
		}
	}

	return result;
}

template <typename Number>
Zonotope<Number> Zonotope<Number>::intersect( const Constraint &halfspace ) const {
	assert( halfspace.space_dimension() == this->mDimension );
	Number e = halfspace.inhomogeneous_term().get_d();
	hypro::vector_t<Number> dVec;

	dVec.resize( halfspace.space_dimension(), Eigen::NoChange );

	for ( unsigned i = 0; i < halfspace.space_dimension(); i++ ) {
		dVec( i ) = -1 * halfspace.coefficient( Variable( i ) ).get_d();
	}

	return this->intersectWithHalfspace( dVec, e );
}

template <typename Number>
Zonotope<Number> Zonotope<Number>::intersectWithHalfspace( const hypro::vector_t<Number> &d_vec,
														   Number e_scalar ) const {
	Zonotope<Number> result;
	/* zs holds the 1-norm (Manhattan-Norm) of the direction projected onto the
	 * generators
	 *  -> we sum the projections of the direction onto the generators (take only
	 * positive ones to prevent from
	 * canceling)
	 * -> this holds the farest we can go without leaving the zonotope
	 */
	Number zs = ( d_vec.transpose() * this->mGenerators ).array().abs().sum();
	// projection of d_vec on center
	Number dc = d_vec.dot( this->mCenter );
	// qu holds the maximal value one can go into direction of the hyperplane ->
	// if this is less than the scalar, the
	// zonotope is fully contained
	Number qu = dc + zs, qd = dc - zs;  // qd holds the minimal value of the zonotope generators
										// evaluated into the direction of the
										// hyperplane (with respect to the center)
	if ( qd <= e_scalar ) {				// the zonotope is below the hyperplane -> there is an
										// intersection
		if ( qu <= e_scalar ) {			// the zonotopes maximal evaluation is also below the
										// hyperplane -> it is fully contained
			result = *this;
		} else {  // partly contained
			// sigma is half the distance between the hyperplane and the "lowest"
			// point of the zonotope.
			Number sigma = ( e_scalar - qd ) / 2, d = ( qd + e_scalar ) / 2;  // d holds ?
			hypro::matrix_t<Number> HHT = this->mGenerators * this->mGenerators.transpose();
			hypro::vector_t<Number> lambda = HHT * d_vec / ( ( d_vec.transpose() * HHT * d_vec ) + sigma * sigma );
			result.setCenter( this->mCenter + lambda * ( d - dc ) );
			hypro::matrix_t<Number> identity;
			identity.resize( mDimension, mDimension );
			identity.setIdentity();
			result.setGenerators( ( identity - lambda * d_vec.transpose() ) * this->mGenerators );
			result.addGenerators( sigma * lambda );
		}
	}
	return result;
}

template <typename Number>
Zonotope<Number> Zonotope<Number>::intersect( const C_Polyhedron &rhs ) const {
	// Get set of half spaces
	const Constraint_System &cs = rhs.constraints();
	Zonotope<Number> curZonotope( *this );

	// Iterate through all constraints of the polyhedron
	for ( Constraint constr : cs ) {
		//        hypro::vector_t<Number> d_vector;
		//        Number e;
		//        d_vector.resize(dim,1);
		//
		//        // PPL represents constraints in the form of a*x1 + b*x2 + ...
		//        {>,>=} q
		//        // Note: e does not need to be negated 'cause PPL returns value of
		//        inhomogenous_term on the LHS of
		//        inequality
		//        e = constr.inhomogeneous_term().get_d();
		//        for (unsigned i=0; i<constr.space_dimension(); i++) {
		//            // each coefficient has to be negated due to >= in PPL instead
		//            of <=
		//            d_vector(i) = -1*constr.coefficient(Variable(i)).get_d();
		//        }
		//
		//        // zs is ||H^t * n || _ 1
		//        Number zs =
		//        (d_vector.transpose()*cur_zonotope.generators()).array().abs().sum();
		//        Number dc = d_vector.transpose()*cur_zonotope.center();
		//        Number qu = dc + zs, qd = dc - zs;
		//
		//        if (qd<=e) {
		//            if (qu<=e) {
		//                // do nothing
		//            }
		//            else {
		//                Number sgm = (e-qd)/2, d = (qd+e)/2;
		//                hypro::vector_t<Number> lambda =
		//                ((cur_zonotope.generators()*cur_zonotope.generators().transpose())*d_vector)/
		//                                (d_vector.transpose()*(cur_zonotope.generators()*cur_zonotope.generators().transpose())*d_vector+sgm*sgm);
		//
		//                Zonotope<Number> new_zonotope;
		//                new_zonotope.setCenter(cur_zonotope.center()+lambda*(d-dc));
		//
		//                hypro::matrix_t<Number> new_gen1, new_gen2, identity;
		//                identity.resize(dim, dim);
		//                identity.setIdentity();
		//                new_gen1 =
		//                (identity-lambda*d_vector.transpose())*cur_zonotope.generators();
		//                new_gen2 = sgm*lambda;
		//                new_zonotope.setGenerators(new_gen1);
		//                new_zonotope.addGenerators(new_gen2);
		//                cur_zonotope = new_zonotope;
		//            }
		//        }
		//        else {
		//            return false;
		//        }
		curZonotope = curZonotope.intersect( constr );

		bool intersectFound = curZonotope.empty();
		if ( !intersectFound ) return curZonotope;
	}
	return curZonotope;
	// TODO: QUESTION! If one iteration yields empty set, should we break out of
	// loop?
}

template <typename Number>
Zonotope<Number> Zonotope<Number>::unite( const Zonotope<Number> &other ) const {
	assert( mDimension == other.mDimension &&
			"Zonotopes must be of same "
			"dimension in order to carry out "
			"convex hull operations." );
	unsigned numGenCurrent, numGenOther;
	Zonotope<Number> temp;
	numGenCurrent = this->numGenerators();
	numGenOther = other.numGenerators();
	hypro::matrix_t<Number> R1, R2;
	hypro::vector_t<Number> c1, c2;
	R1 = this->mGenerators;
	R2 = other.mGenerators;
	c1 = this->mCenter;
	c2 = other.mCenter;

	// common traits of center and generators for all two zonotopes
	temp.setCenter( ( c1 + c2 ) * 0.5 );

	if ( numGenCurrent > numGenOther ) {
		hypro::matrix_t<Number> R11, R12;
		R11 = R1.block( 0, 0, mDimension, numGenOther );
		R12 = R1.block( 0, numGenOther, mDimension, numGenCurrent - numGenOther );

		temp.setGenerators( ( R2 + R11 ) * 0.5 );
		temp.addGenerators( ( c1 - c2 ) * 0.5 );
		temp.addGenerators( ( R11 - R2 ) * 0.5 );
		temp.addGenerators( R12 );
	} else if ( numGenCurrent < numGenOther ) {
		hypro::matrix_t<Number> R21, R22;

		R21 = R2.block( 0, 0, mDimension, numGenCurrent );
		R22 = R2.block( 0, numGenCurrent, mDimension, numGenOther - numGenCurrent );

		temp.setGenerators( ( R1 + R21 ) * 0.5 );
		temp.addGenerators( ( c2 - c1 ) * 0.5 );
		temp.addGenerators( ( R21 - R1 ) * 0.5 );
		temp.addGenerators( R22 );
	} else {
		temp.setGenerators( ( R1 + R2 ) * 0.5 );
		temp.addGenerators( ( c1 - c2 ) * 0.5 );
		temp.addGenerators( ( R1 - R2 ) * 0.5 );
	};
	return temp;
}

template <typename Number>
Zonotope<Number> Zonotope<Number>::intervalHull() const {
	Zonotope<Number> result;
	hypro::vector_t<Number> imax, imin, sumOfGenerators, center = this->mCenter;
	hypro::matrix_t<Number> generators = this->mGenerators;
	Zonotope<Number> temp;

	sumOfGenerators = generators.cwiseAbs().rowwise().sum();

	imax = center + sumOfGenerators;
	imin = center - sumOfGenerators;

	temp.setCenter( ( imax + imin ) * 0.5 );

	temp.setGenerators( ( ( imax - imin ) * 0.5 ).cwiseAbs().asDiagonal() );

	result = temp;
	return result;
}

}  // namespace
