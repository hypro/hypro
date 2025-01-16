/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

#include "Starset.h"

namespace hypro {

template <typename Number, typename Converter, typename Setting>
StarsetT<Number, Converter, Setting>::StarsetT()
	: mCenter( vector_t<Number>::Zero( 1 ) )
	, mGenerator( matrix_t<Number>::Zero( 1, 1 ) )
	, mConstraints() {
}

template <typename Number, typename Converter, typename Setting>
StarsetT<Number, Converter, Setting>::StarsetT( const vector_t<Number>& center, const matrix_t<Number>& shapematrix, const vector_t<Number>& limits, const matrix_t<Number>& generator )
	: mCenter( center )
	, mGenerator( generator )
	, mConstraints( shapematrix, limits ) {
		// std::cout << "Starset general constructor" << std::endl;
		// std::cout << "This center: " << this->center() << std::endl;
		// std::cout << "This generator: " << this->generator() << std::endl;
		// std::cout << "This constraints: " << this->constraints() << std::endl;
}

template <typename Number, typename Converter, typename Setting>
StarsetT<Number, Converter, Setting>::StarsetT( const vector_t<Number>& center, const matrix_t<Number>& generator, const HPolytopeT<Number, Converter, HPolytopeOptimizerCaching> Constraints )
	: mCenter( center )
	, mGenerator( generator )
	, mConstraints( Constraints ) {
}

template <typename Number, typename Converter, typename Setting>
StarsetT<Number, Converter, Setting>::StarsetT( const matrix_t<Number>& shapematrix, const vector_t<Number>& limits )
	: mCenter( vector_t<Number>::Zero( shapematrix.cols() ) )
	, mGenerator( matrix_t<Number>::Identity( shapematrix.cols(), shapematrix.cols() ) )
	, mConstraints( shapematrix, limits ) {
}

template <typename Number, typename Converter, typename Setting>
StarsetT<Number, Converter, Setting>::StarsetT( HPolytopeT<Number, Converter, HPolytopeOptimizerCaching> Constraints )
	: mCenter( vector_t<Number>::Zero( Constraints.matrix().cols() ) )
	, mGenerator( matrix_t<Number>::Identity( Constraints.matrix().cols(), Constraints.matrix().cols() ) )
	, mConstraints( Constraints ) {
}

template <typename Number, typename Converter, typename Setting>
StarsetT<Number, Converter, Setting>::StarsetT( const StarsetT<Number, Converter, Setting>& orig )
	: GeometricObjectBase( orig )
	, mCenter( orig.center() )
	, mGenerator( orig.generator() )
	, mConstraints( orig.constraints() ) {
}

template <typename Number, typename Converter, typename Setting>
StarsetT<Number, Converter, Setting>::StarsetT( StarsetT<Number, Converter, Setting>&& orig )
	: GeometricObjectBase( orig )
	, mCenter( orig.center() )
	, mGenerator( orig.generator() )
	, mConstraints( orig.constraints() ) {
}

// new getters
template <typename Number, typename Converter, typename Setting>
vector_t<Number> StarsetT<Number, Converter, Setting>::center() const {
	return mCenter;
}

template <typename Number, typename Converter, typename Setting>
vector_t<Number> StarsetT<Number, Converter, Setting>::limits() const {
	return mConstraints.vector();
}

template <typename Number, typename Converter, typename Setting>
matrix_t<Number> StarsetT<Number, Converter, Setting>::shape() const {
	return mConstraints.matrix();
}

template <typename Number, typename Converter, typename Setting>
matrix_t<Number> StarsetT<Number, Converter, Setting>::generator() const {
	return mGenerator;
}

template <typename Number, typename Converter, typename Setting>
HPolytopeT<Number, Converter, HPolytopeOptimizerCaching> StarsetT<Number, Converter, Setting>::constraints() const {
	return mConstraints;
}

template <typename Number, typename Converter, typename Setting>
HPolytopeT<Number, Converter, HPolytopeOptimizerCaching> StarsetT<Number, Converter, Setting>::eqvPolytope() const {
	if ( Settings::CACHE_EQV_POLYTOPE ) {
		if ( !mEqvPoly ) {
			updateEquivalentPolytope();
		}
		return ( *mEqvPoly );
	} else {
		HPolytopeT<Number, Converter, HPolytopeOptimizerCaching> poly = Converter::template toHPolytope<HPolytopeBoundingBoxCaching, Setting>( *this );
		return poly;
	}
}

template <typename Number, typename Converter, typename Setting>
bool StarsetT<Number, Converter, Setting>::empty() const {
	return mConstraints.empty();
}

template <typename Number, typename Converter, typename Setting>
void StarsetT<Number, Converter, Setting>::setCenter( const vector_t<Number>& center ) {
	mCenter = center;
}

template <typename Number, typename Converter, typename Setting>
void StarsetT<Number, Converter, Setting>::setGenerators( const matrix_t<Number>& generators ) {
	mGenerator = generators;
}

template <typename Number, typename Converter, typename Setting>
Number StarsetT<Number, Converter, Setting>::supremum() const {
}

template <typename Number, typename Converter, typename Setting>
std::vector<Point<Number>> StarsetT<Number, Converter, Setting>::vertices() const {
	std::vector<Point<Number>> res;

	if (mGenerator.isZero()) {
		res.push_back(Point<Number>(mCenter));
		return res;
	}

	auto placeholder = mConstraints.vertices();
	for ( auto point : placeholder ) {
		point = point.affineTransformation( mGenerator, mCenter );

		// should not add points to the results that are already in
		bool alreadyIn = false;
		for ( int i = 0; i < res.size(); i++ ) {
			// dependending on using floating point or exact arithmetic, this equality could be checked with a threshold
			if ( point == res[i] ) {
				alreadyIn = true;
				break;
			}
		}
		if ( !alreadyIn )
			res.push_back( point );
	}
	return removeRedundantPoints( res );
}

template <typename Number, typename Converter, typename Setting>
EvaluationResult<Number> StarsetT<Number, Converter, Setting>::evaluate( const vector_t<Number>& _direction ) const {
}

template <typename Number, typename Converter, typename Setting>
std::vector<EvaluationResult<Number>> StarsetT<Number, Converter, Setting>::multiEvaluate( const matrix_t<Number>& _directions, bool useExact ) const {
}

template <typename Number, typename Converter, typename Setting>
std::size_t StarsetT<Number, Converter, Setting>::dimension() const {
	return mGenerator.rows();
}

template <typename Number, typename Converter, typename Setting>
StarsetT<Number, Converter, Setting> StarsetT<Number, Converter, Setting>::removeRedundancy() {
	return StarsetT<Number, Converter, Setting>( mCenter, mGenerator, mConstraints.removeRedundancy() );
}

template <typename Number, typename Converter, typename Setting>
std::size_t StarsetT<Number, Converter, Setting>::size() const {
	return 1;
}

template <typename Number, typename Converter, typename Setting>
const StarsetT<Number, Converter, Setting>& StarsetT<Number, Converter, Setting>::reduceNumberRepresentation() {
}

template <typename Number, typename Converter, typename Setting>
std::pair<CONTAINMENT, StarsetT<Number, Converter, Setting>> StarsetT<Number, Converter, Setting>::satisfiesHalfspace( const Halfspace<Number>& rhs ) const {
	auto zz = this->calculateHalfspace( rhs );
	StarsetT<Number, Converter, Setting> star = this->intersectHalfspace( zz );
	// auto ans=(mConstraints.satisfiesHalfspace(zz));

	// why calling calculateHalfspace again, we already have zz
	return std::make_pair( std::get<0>( mConstraints.satisfiesHalfspace( calculateHalfspace( rhs ) ) ), std::move( star ) );
}

template <typename Number, typename Converter, typename Setting>
std::pair<CONTAINMENT, StarsetT<Number, Converter, Setting>> StarsetT<Number, Converter, Setting>::satisfiesHalfspaces( const matrix_t<Number>& _mat, const vector_t<Number>& _vec ) const {
	if ( this->empty() ) {
		return std::make_pair( CONTAINMENT::NO, std::move( *this ) );
	}
	// write halfspace using my basis and center
	std::pair<matrix_t<Number>, vector_t<Number>> zz = this->calculateHalfspaces( _mat, _vec );
	// check if mConstraints satisfy the halfspace
	auto ans = ( mConstraints.satisfiesHalfspaces( std::get<0>( zz ), std::get<1>( zz ) ) );

	// Create a star set which is intersected with the given halfspace half space
	StarsetT<Number, Converter, Setting> star = StarsetT<Number, Converter, Setting>( mCenter, mGenerator, std::get<1>( ans ) );

	if ( CONTAINMENT::PARTIAL == std::get<0>( ans ) ) {
		return std::make_pair( std::get<0>( ans ), star.removeRedundancy() );
	}

	return std::make_pair( std::get<0>( ans ), std::move( star ) );
}

template <typename Number, typename Converter, typename Setting>
StarsetT<Number, Converter, Setting> StarsetT<Number, Converter, Setting>::projectOn( const std::vector<std::size_t>& dimensions ) const {
}

template <typename Number, typename Converter, typename Setting>
StarsetT<Number, Converter, Setting> StarsetT<Number, Converter, Setting>::linearTransformation( const matrix_t<Number>& A ) const {
	matrix_t<Number> newGenerator = matrix_t<Number>( mGenerator.rows(), mGenerator.cols() );
	newGenerator = A * mGenerator;
	vector_t<Number> newCenter = A * mCenter;
	return StarsetT<Number, Converter, Setting>( newCenter, newGenerator, mConstraints );
}

template <typename Number, typename Converter, typename Setting>
StarsetT<Number, Converter, Setting> StarsetT<Number, Converter, Setting>::affineTransformation( const matrix_t<Number>& A, const vector_t<Number>& b ) const {
	if ( A.nonZeros() == 0 ) {
		std::vector<Point<Number>> points;
		points.emplace_back( b );
		return StarsetT<Number, Converter, Setting>( HPolytopeT<Number, Converter, HPolytopeOptimizerCaching>( points ) );
	}
	// if ( !this->empty() ) {
	// what is the reason behind checking if the star is empty? In the NNCS verification it slows down the process
	// In my opinion the affine transformation is fast enough,
	// especially in my case checking checking the emptiness takes much more time than applying the affine transformation
	return StarsetT<Number, Converter, Setting>( A * ( mCenter ) + b, A * mGenerator, mConstraints );
	// }
	return *this;
}

template <typename Number, typename Converter, typename Setting>
StarsetT<Number, Converter, Setting> StarsetT<Number, Converter, Setting>::minkowskiSum( const StarsetT<Number, Converter, Setting>& rhs ) const {
	assert( this->dimension() == rhs.dimension() );

	// assuming same dimension
	if ( mGenerator.cols() < 10 ) {
		auto intermediate1 = this->eqvPolytope();
		auto intermediate2 = rhs.eqvPolytope();
		return Converter::toStarset( intermediate1.minkowskiSum( intermediate2 ) );
	}

	if ( this->generator().rows() != rhs.generator().rows() ) {
		return *this;
	}

	if ( rhs.empty() ) {
		return *this;
	}

	if ( this->empty() ) {
		return rhs;
	}

	matrix_t<Number> newmGenerator = matrix_t<Number>::Zero( mGenerator.rows(), mGenerator.cols() + rhs.generator().cols() );
	matrix_t<Number> newmShapeMatrix = matrix_t<Number>::Zero( mConstraints.matrix().rows() + rhs.shape().rows(), mConstraints.matrix().cols() + rhs.shape().cols() );
	vector_t<Number> newmLimits = vector_t<Number>::Zero( mConstraints.vector().rows() + rhs.limits().rows() );

	newmGenerator.block( 0, 0, mGenerator.rows(), mGenerator.cols() ) = mGenerator;
	newmGenerator.block( 0, mGenerator.cols(), rhs.generator().rows(), rhs.generator().cols() ) = rhs.generator();

	// setting new shape Matrix
	newmShapeMatrix.topLeftCorner( mConstraints.matrix().rows(), mConstraints.matrix().cols() ) = mConstraints.matrix();
	newmShapeMatrix.bottomRightCorner( rhs.shape().rows(), rhs.shape().cols() ) = rhs.shape();

	// setting new limits vector
	newmLimits.head( mConstraints.vector().rows() ) = mConstraints.vector();
	newmLimits.tail( rhs.limits().rows() ) = rhs.limits();
	// setting new center
	vector_t<Number> newmCenter = mCenter + rhs.center();

	return StarsetT<Number, Converter, Setting>( newmCenter, newmGenerator, HPolytopeT<Number, Converter, HPolytopeOptimizerCaching>( newmShapeMatrix, newmLimits ).removeRedundancy() );
}

template <typename Number, typename Converter, typename Setting>
StarsetT<Number, Converter, Setting> StarsetT<Number, Converter, Setting>::intersect( const StarsetT<Number, Converter, Setting>& rhs ) const {
	auto intermediate = this->eqvPolytope();
	auto intermediate2 = rhs.eqvPolytope();
	return Converter::toStarset( intermediate.intersect( intermediate2 ) ).removeRedundancy();
}

template <typename Number, typename Converter, typename Setting>
StarsetT<Number, Converter, Setting> StarsetT<Number, Converter, Setting>::intersectHalfspace( const Halfspace<Number>& hspace ) const {
	// check if the dimension of the halfspace is the same as the dimension of the starset
	assert( hspace.normal.rows() == mGenerator.rows() );

	// get the attributes of the starset
	vector_t<Number> center = mCenter;
	matrix_t<Number> generator = mGenerator;
	matrix_t<Number> shape = this->shape();
	vector_t<Number> limits = this->limits();

	// get the attributes of the halfspace
	vector_t<Number> normal = hspace.normal();
	Number offset = hspace.offset();

	// using the result we will add one more new constraint, i.e. one more row to the shape matrix and one more element to the limits vector
	shape.conservativeResize( shape.rows() + 1, shape.cols() );
	limits.conservativeResize( shape.rows() + 1, 1 );

	// multiply each row of the generator with the corresponding element from the normal vector and then sum up each column individually
	shape.row( shape.rows() - 1 ) = normal.transpose() * generator;
	limits[shape.rows() - 1] = offset - normal.dot( center );

	return StarsetT<Number, Converter, Setting>( mCenter, shape, limits, mGenerator );
}

template <typename Number, typename Converter, typename Setting>
StarsetT<Number, Converter, Setting> StarsetT<Number, Converter, Setting>::intersectHalfspaces( const matrix_t<Number>& _mat, const vector_t<Number>& _vec ) const {
	// check if the number of  halfspace matrix and vector are consistent and the dimension of the halfspaces is the same as the dimension of the starset
	assert( _mat.rows() == _vec.rows() );
	assert( _mat.cols() == mGenerator.rows() );

	// get the attributes of the starset
	vector_t<Number> center = mCenter;
	matrix_t<Number> generator = mGenerator;
	matrix_t<Number> shape = this->shape();
	vector_t<Number> limits = this->limits();

	// we allocate n new entries in the shape and limit matrices for the new constraints
	shape.conservativeResize( shape.rows() + _mat.rows(), shape.cols() );
	limits.conservativeResize( shape.rows() + _mat.rows(), 1 );

	// this loop could be executed in parallel
	// #pragma omp parallel for
	for ( int i = 0; i < _mat.rows(); i++ ) {
		// get the attributes of the halfspace: normal vector and offset
		vector_t<Number> normal = _mat.row( i );
		Number offset = _vec[i];

		// add the new constraints to the shape matrix and limits vector
		shape.row( shape.rows() - _mat.rows() + i ) = normal.transpose() * generator;;
		limits[shape.rows() - _mat.rows() + i] = offset - normal.dot( center );
	}

	return StarsetT<Number, Converter, Setting>( mCenter, shape, limits, mGenerator );
}

// Starset.containts(point) method using the cached converted H-Polytope
template <typename Number, typename Converter, typename Setting>
bool StarsetT<Number, Converter, Setting>::containsCached( const Point<Number>& point ) const {
	if ( !Settings::CACHE_EQV_POLYTOPE )
		return this->contains( point );
	return eqvPolytope().contains( point );
}

// Starset.contains(point) method using SAT checking (y = c + Vx && P(x))
// template <typename Number, typename Converter, typename Setting>
// bool StarsetT<Number, Converter, Setting>::contains( const Point<Number>& point ) const {
// 	hypro::matrix_t<Number> shape_mat = mConstraints.matrix();
// 	hypro::vector_t<Number> limit_vec = mConstraints.vector();

// 	hypro::matrix_t<Number> new_basis_mat = mGenerator;
// 	hypro::matrix_t<Number> new_center_vec = point.rawCoordinates() - mCenter;

// 	int row_num = 2 * mGenerator.rows() + shape_mat.rows();
// 	int col_num = shape_mat.cols();
// 	hypro::matrix_t<Number> final_mat = hypro::matrix_t<Number>( row_num, col_num );
// 	hypro::vector_t<Number> final_vec = hypro::vector_t<Number>( row_num );

// 	final_mat << shape_mat, new_basis_mat, -new_basis_mat;
// 	final_vec << limit_vec, new_center_vec, -new_center_vec;

// 	hypro::Optimizer<Number> optimizer( final_mat, final_vec );
// 	return optimizer.checkConsistency();
// }

template <typename Number, typename Converter, typename Setting> 
hypro::EvaluationResult<Number> StarsetT<Number, Converter, Setting>::modelContains( const Point<Number>& point ) const {
#if defined(HYPRO_USE_Z3) && ( HYPRO_PRIMARY_SOLVER == SOLVER_ZTHREE || HYPRO_SECONDARY_SOLVER == SOLVER_ZTHREE )
	return hypro::z3GetInternalPoint(this->shape(), this->limits(), mGenerator, mCenter, point);
#else
	return hypro::glpkGetInternalPoint(this->shape(), this->limits(), mGenerator, mCenter, point);
#endif
}

template <typename Number, typename Converter, typename Setting>
bool StarsetT<Number, Converter, Setting>::contains( const Point<Number>& point ) const {
	// if(this->dimension() == 1) {
	// 	vector_t<Number> dir_vect = mGenerator.row(0);

	// 	auto eval_low_result = mConstraints.evaluate( -1.0 * dir_vect );
	// 	auto eval_high_result = mConstraints.evaluate( dir_vect );

	// 	Number lb = -eval_low_result.supportValue + mCenter[0];
	// 	Number ub = eval_high_result.supportValue + mCenter[0];

	// 	return (lb <= point[0] && point[0] <= ub);
	// }

#if defined(HYPRO_USE_Z3) && ( HYPRO_PRIMARY_SOLVER == SOLVER_ZTHREE || HYPRO_SECONDARY_SOLVER == SOLVER_ZTHREE )
	return hypro::z3CheckPoint(this->shape(), this->limits(), mGenerator, mCenter, point);
#else
	// std::cout << "Contains method" << std::endl;
	HPolytopeT<Number, Converter, HPolytopeOptimizerCaching> transformedStar = this->constraints().affineTransformation(mGenerator, mCenter);
	hypro::Optimizer<Number> optimizer( transformedStar.matrix(), transformedStar.vector() );
	return optimizer.checkPoint(point);
#endif
	


}


template <typename Number, typename Converter, typename Setting>
bool StarsetT<Number, Converter, Setting>::contains( const StarsetT<Number, Converter, Setting>& Starset ) const {
	auto intermediate = this->eqvPolytope();
	auto rhs = Starset.eqvPolytope();
	return intermediate.contains( rhs );
}

template <typename Number, typename Converter, typename Setting>
StarsetT<Number, Converter, Setting> StarsetT<Number, Converter, Setting>::unite( const StarsetT<Number, Converter, Setting>& rhs ) const {
	/*The method implemented here is similar to the method proposed by
	 * Prof. Girard for Zonotope.
	 * Reachability of Uncertain Linear Systems Using
	 *      Zonotopes, Antoin Girard, HSCC2005
	 * Output is an overapproximation of convex hull of two star sets
	 * Explanation for this method is written in Bachelor thesis of Dogu Tamgac*/

	if ( this->empty() ) {
		// if this is empty, the result is _rhs, even if _rhs is empty, too.
		return rhs;
	}
	// at this point *this is not empty.
	if ( rhs.empty() ) {
		return *this;
	}
	// Faster in small dimensions
	// option 1 in bachelor thesis
	if ( mGenerator.cols() < 10 ) {
		auto intermediate = this->eqvPolytope();
		auto intermediate2 = rhs.eqvPolytope();
		return Converter::toStarset( intermediate.unite( intermediate2 ) );
	}
	auto tmp1 = StarsetT<Number, Converter, Setting>( this->center(), this->generator(), this->constraints().removeRedundancy() );
	auto tmp2 = StarsetT<Number, Converter, Setting>( rhs.center(), rhs.generator(), rhs.constraints().removeRedundancy() );

	// option 2 in bachelor thesis
	if ( this->constraints() == rhs.constraints() ) {
		if ( this->generator() == matrix_t<Number>::Identity( this->generator().cols(), this->generator().cols() ) ) {
			if ( rhs.generator() == rhs.generator() * this->generator() ) {
				matrix_t<Number> m = matrix_t<Number>::Identity( this->generator().cols(), this->generator().cols() ) - rhs.generator();
				StarsetT<Number, Converter, Setting> S2 = this->affineTransformation( m, ( -rhs.center() ) );

				matrix_t<Number> newmGenerator = matrix_t<Number>::Zero( tmp1.generator().rows(), tmp1.generator().cols() + tmp2.generator().cols() + 1 );
				matrix_t<Number> newmShapeMatrix = matrix_t<Number>::Zero( tmp1.shape().rows() + tmp2.shape().rows() + 2, tmp1.shape().cols() + tmp2.shape().cols() + 1 );
				vector_t<Number> newmLimits = vector_t<Number>::Zero( tmp1.limits().rows() + tmp2.limits().rows() + 2 );

				newmGenerator.block( 0, 0, tmp1.generator().rows(), mGenerator.cols() ) = tmp2.generator();
				matrix_t<Number> cent( ( matrix_t<Number>::Identity( this->generator().cols(), this->generator().cols() ) ) * S2.center() );
				newmGenerator.block( 0, tmp1.generator().cols(), tmp1.generator().rows(), 1 ) = cent;
				newmGenerator.block( 0, tmp1.generator().cols() + 1, tmp2.generator().rows(), tmp2.generator().cols() ) = S2.generator();

				newmShapeMatrix.topLeftCorner( tmp1.shape().rows(), tmp1.shape().cols() ) = tmp2.shape();
				newmShapeMatrix( tmp1.shape().rows(), tmp1.shape().cols() ) = -1;
				newmShapeMatrix( tmp1.shape().rows() + 1, tmp1.shape().cols() ) = 1;
				newmShapeMatrix.bottomRightCorner( tmp2.shape().rows(), tmp2.shape().cols() ) = tmp2.shape();

				newmLimits.head( tmp1.limits().rows() ) = tmp2.limits();
				newmLimits( tmp1.limits().rows() ) = Number( 0 );
				newmLimits( tmp1.limits().rows() + 1 ) = Number( 1 );
				newmLimits.tail( tmp2.limits().rows() ) = tmp2.limits();

				return ( StarsetT<Number, Converter, Setting>( tmp2.center(), newmGenerator, HPolytopeT<Number, Converter, HPolytopeOptimizerCaching>( newmShapeMatrix, newmLimits ).removeRedundancy() ) );  //.removeRedundancy() ;
			}
		} else if ( rhs.generator() == matrix_t<Number>::Identity( rhs.generator().cols(), rhs.generator().cols() ) ) {
			if ( this->generator() == this->generator() * rhs.generator() ) {
				matrix_t<Number> m = matrix_t<Number>::Identity( this->generator().cols(), this->generator().cols() ) - this->generator();

				StarsetT<Number, Converter, Setting> S2 = rhs.affineTransformation( m, ( -this->center() ) );

				matrix_t<Number> newmGenerator = matrix_t<Number>::Zero( tmp1.generator().rows(), tmp1.generator().cols() + tmp2.generator().cols() + 1 );
				matrix_t<Number> newmShapeMatrix = matrix_t<Number>::Zero( tmp1.shape().rows() + tmp2.shape().rows() + 2, tmp1.shape().cols() + tmp2.shape().cols() + 1 );
				vector_t<Number> newmLimits = vector_t<Number>::Zero( tmp1.limits().rows() + tmp2.limits().rows() + 2 );

				newmGenerator.block( 0, 0, tmp1.generator().rows(), mGenerator.cols() ) = tmp1.generator();
				matrix_t<Number> cent( ( matrix_t<Number>::Identity( this->generator().cols(), this->generator().cols() ) ) * S2.center() );
				newmGenerator.block( 0, tmp1.generator().cols(), tmp1.generator().rows(), 1 ) = cent;
				newmGenerator.block( 0, tmp1.generator().cols() + 1, tmp2.generator().rows(), tmp2.generator().cols() ) = S2.generator();

				newmShapeMatrix.topLeftCorner( tmp1.shape().rows(), tmp1.shape().cols() ) = tmp1.shape();
				newmShapeMatrix( tmp1.shape().rows(), tmp1.shape().cols() ) = -1;
				newmShapeMatrix( tmp1.shape().rows() + 1, tmp1.shape().cols() ) = 1;
				newmShapeMatrix.bottomRightCorner( tmp2.shape().rows(), tmp2.shape().cols() ) = tmp1.shape();

				newmLimits.head( tmp1.limits().rows() ) = tmp1.limits();
				newmLimits( tmp1.limits().rows() ) = Number( 0 );
				newmLimits( tmp1.limits().rows() + 1 ) = Number( 1 );
				newmLimits.tail( tmp2.limits().rows() ) = tmp1.limits();

				return ( StarsetT<Number, Converter, Setting>( tmp1.center(), newmGenerator, HPolytopeT<Number, Converter, HPolytopeOptimizerCaching>( newmShapeMatrix, newmLimits ).removeRedundancy() ) );  //.removeRedundancy() ;
			}
		}
	}
	/*
	 matrix_t<Number> newmGenerator=matrix_t<Number>::Zero(tmp1.generator().rows(),tmp1.generator().cols()+tmp2.generator().cols());
	 matrix_t<Number> newmShapeMatrix=matrix_t<Number>::Zero(tmp1.shape().rows()+tmp2.shape().rows(),tmp1.shape().cols()+tmp2.shape().cols());
	 vector_t<Number> newmLimits=vector_t<Number>::Zero(tmp1.limits().rows()+tmp2.limits().rows());

	 vector_t<Number> newmCenter=tmp1.center()-tmp2.center();

	 newmGenerator.block(0,0,tmp1.generator().rows(),mGenerator.cols())=tmp1.generator();
	 newmGenerator.block(0, tmp1.generator().cols(), tmp2.generator().rows() , tmp2.generator().cols())=-tmp2.generator();

	 newmShapeMatrix.topLeftCorner(tmp1.shape().rows(),tmp1.shape().cols())=tmp1.shape();
	 newmShapeMatrix.bottomRightCorner(tmp2.shape().rows(),tmp2.shape().cols())=tmp2.shape();

	 newmLimits.head(tmp1.limits().rows())=tmp1.limits();
	 newmLimits.tail(tmp2.limits().rows())=tmp2.limits();
	 return tmp2.minkowskiSum( StarsetT<Number, Converter, Setting>(newmCenter,newmGenerator,HPolytopeT<Number,Converter, HPolytopeOptimizerCaching>(newmShapeMatrix,newmLimits).removeRedundancy()));//.removeRedundancy() ;
*/
	// option 3 in bachelor thesis
	matrix_t<Number> newmGenerator = matrix_t<Number>::Zero( tmp1.generator().rows(), tmp1.generator().cols() + tmp2.generator().cols() * 2 + 1 );
	matrix_t<Number> newmShapeMatrix = matrix_t<Number>::Zero( tmp1.shape().rows() + tmp2.shape().rows() * 2 + 2, tmp1.shape().cols() + tmp2.shape().cols() * 2 + 1 );
	vector_t<Number> newmLimits = vector_t<Number>::Zero( tmp1.limits().rows() + tmp2.limits().rows() * 2 + 2 );

	newmGenerator.block( 0, 0, tmp2.generator().rows(), mGenerator.cols() ) = tmp2.generator();
	matrix_t<Number> cent( ( matrix_t<Number>::Identity( this->generator().cols(), this->generator().cols() ) ) * ( tmp1.center() - tmp2.center() ) );
	newmGenerator.block( 0, tmp2.generator().cols(), tmp1.generator().rows(), 1 ) = cent;
	newmGenerator.block( 0, tmp2.generator().cols() + 1, tmp1.generator().rows(), tmp1.generator().cols() ) = tmp1.generator();
	newmGenerator.block( 0, tmp2.generator().cols() + tmp1.generator().cols() + 1, tmp2.generator().rows(), tmp2.generator().cols() ) = -tmp2.generator();

	newmShapeMatrix.topLeftCorner( tmp1.shape().rows(), tmp1.shape().cols() ) = tmp2.shape();
	newmShapeMatrix( tmp2.shape().rows(), tmp2.shape().cols() ) = -1;
	newmShapeMatrix( tmp2.shape().rows() + 1, tmp2.shape().cols() ) = 1;
	newmShapeMatrix.block( tmp2.shape().rows() + 2, tmp2.shape().cols() + 1, tmp1.shape().rows(), tmp1.shape().cols() ) = tmp1.shape();
	newmShapeMatrix.bottomRightCorner( tmp2.shape().rows(), tmp2.shape().cols() ) = tmp2.shape();

	newmLimits.head( tmp2.limits().rows() ) = tmp2.limits();
	newmLimits( tmp1.limits().rows() ) = Number( 0 );
	newmLimits( tmp1.limits().rows() + 1 ) = Number( 1 );
	newmLimits.segment( tmp2.limits().rows() + 2, tmp1.limits().rows() ) = tmp2.limits();

	newmLimits.tail( tmp2.limits().rows() ) = tmp2.limits();

	return ( StarsetT<Number, Converter, Setting>( tmp2.center(), newmGenerator, HPolytopeT<Number, Converter, HPolytopeOptimizerCaching>( newmShapeMatrix, newmLimits ).removeRedundancy() ) );  //.removeRedundancy() ;
}

template <typename Number, typename Converter, typename Setting>
StarsetT<Number, Converter, Setting> StarsetT<Number, Converter, Setting>::unite( const std::vector<StarsetT<Number, Converter, Setting>>& Starsets ) {
	StarsetT<Number, Converter, Setting> star = StarsetT<Number, Converter, Setting>( Starsets[0].center(), Starsets[0].generator(), Starsets[0].constraints() );
	for ( int i = 1; i < Starsets.size(); i++ ) {
		star = star.unite( Starsets[i] );
	}
	return star;
}

template <typename Number, typename Converter, typename Setting>
void StarsetT<Number, Converter, Setting>::reduceRepresentation() {
}

template <typename Number, typename Converter, typename Setting>
Halfspace<Number> StarsetT<Number, Converter, Setting>::calculateHalfspace( const Halfspace<Number>& hspace ) const {
	matrix_t<Number> temp = matrix_t<Number>( 1, 1 );
	temp( 0, 0 ) = hspace.offset();
	return Halfspace<Number>( ( hspace.normal().transpose() * this->generator() ), ( temp - ( hspace.normal().transpose() ) * ( this->center() ) )( 0, 0 ) );
}

template <typename Number, typename Converter, typename Setting>
std::pair<matrix_t<Number>, vector_t<Number>> StarsetT<Number, Converter, Setting>::calculateHalfspaces( const matrix_t<Number>& _mat, const vector_t<Number>& _vec ) const {
	return std::make_pair( _mat * this->generator(), _vec - vector_t<Number>( _mat * this->center() ) );
}

template <typename Number, typename Converter, typename Setting>
void StarsetT<Number, Converter, Setting>::clear() {
}

template <typename Number, typename Converter, class Setting>
void StarsetT<Number, Converter, Setting>::updateEquivalentPolytope() const {
	if ( Settings::CACHE_EQV_POLYTOPE ) {
		mEqvPoly = Converter::template toHPolytope<HPolytopeBoundingBoxCaching, Setting>( *this );
	}
}

template <typename Number, typename Converter, class Setting>
void StarsetT<Number, Converter, Setting>::updateCache() const {
	updateEquivalentPolytope();
}

template <typename Number, typename Converter, class Setting>
void StarsetT<Number, Converter, Setting>::invalidateCache() const {
	if ( Settings::CACHE_EQV_POLYTOPE ) {
		mEqvPoly = std::nullopt;
	}
}

}  // namespace hypro
