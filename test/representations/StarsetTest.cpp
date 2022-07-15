#include "test/defines.h"

#include "gtest/gtest.h"
#include <hypro/representations/GeometricObjectBase.h>
#include <hypro/representations/sampling/sampling.h>
#include <hypro/util/plotting/Plotter.h>

template <typename Number>
class StarsetTest : public ::testing::Test {
  protected:
	virtual void SetUp() {
		// create some number of stars

		// create a star using the default constructor
		this->default_star = hypro::Starset<Number>();

		int star_dim = 2;

		// a simple rectangle [_]
		hypro::vector_t<Number> center1 = hypro::vector_t<Number>( 2 );
		hypro::matrix_t<Number> basis1 = hypro::matrix_t<Number>( 2, 2 );
		hypro::matrix_t<Number> constr1 = hypro::matrix_t<Number>( 4, 2 );
		hypro::vector_t<Number> limits1 = hypro::vector_t<Number>( 4 );
		center1 << 0, 0;
		basis1 << 1, 0, 0, 1;
		constr1 << 1, 0, -1, 0, 0, 1, 0, -1;
		limits1 << 2, 1, 1, 1;
		this->star_2d_rect = hypro::Starset<Number>( center1, constr1, limits1, basis1 );

		// a triangle:  |>
		hypro::vector_t<Number> center2 = hypro::vector_t<Number>( 2 );
		hypro::matrix_t<Number> basis2 = hypro::matrix_t<Number>( 2, 2 );
		hypro::matrix_t<Number> constr2 = hypro::matrix_t<Number>( 3, 2 );
		hypro::vector_t<Number> limits2 = hypro::vector_t<Number>( 3 );
		center2 << 0, 0;
		basis2 << 1, 0, 0, 1;
		constr2 << -1, 0, 1, 1, 1, -1;
		limits2 << 1, 1, 1;
		this->star_2d_triang1 = hypro::Starset<Number>( center2, constr2, limits2, basis2 );

		// another triangle: /_|   (reversed, scaled)
		hypro::vector_t<Number> center3 = hypro::vector_t<Number>( 2 );
		hypro::matrix_t<Number> basis3 = hypro::matrix_t<Number>( 2, 2 );
		hypro::matrix_t<Number> constr3 = hypro::matrix_t<Number>( 3, 2 );
		hypro::vector_t<Number> limits3 = hypro::vector_t<Number>( 3 );
		center3 << 0, 0;
		basis3 << -2, 0, 0, 1;
		constr3 << -1, 0, 0, -1, 1, 1;
		limits3 << 1, 2, 1;
		this->star_2d_triang2 = hypro::Starset<Number>( center3, constr3, limits3, basis3 );

		star_dim = 5;
		// 5d box
		hypro::vector_t<Number> center4 = hypro::vector_t<Number>::Zero( star_dim );
		hypro::matrix_t<Number> basis4 = hypro::matrix_t<Number>::Identity( star_dim, star_dim );

		hypro::matrix_t<Number> upper_bounds = hypro::matrix_t<Number>::Identity( star_dim, star_dim );
		hypro::matrix_t<Number> lower_bounds = hypro::matrix_t<Number>::Identity( star_dim, star_dim ) * ( -1 );

		hypro::matrix_t<Number> constr4 = hypro::matrix_t<Number>( 2 * star_dim, star_dim );
		constr4 << lower_bounds, upper_bounds;
		hypro::vector_t<Number> limits4 = hypro::vector_t<Number>::Ones( 2 * star_dim );
		this->star_5d_box = hypro::Starset<Number>( center4, constr4, limits4, basis4 );
	}

	virtual void TearDown() {}

	hypro::Starset<Number> default_star;
	hypro::Starset<Number> star_2d_rect;
	hypro::Starset<Number> star_2d_triang1;
	hypro::Starset<Number> star_2d_triang2;
	hypro::Starset<Number> star_5d_box;
};

TYPED_TEST( StarsetTest, Constructor ) {
	// test default constructor  (not working yet for some reason)
	// EXPECT_EQ(this->default_star, hypro::Starset<TypeParam>());

	// test initializing constructors with 2d and 5d stars
	int star_dim = 2;

	// a simple rectangle [_]
	hypro::vector_t<TypeParam> center1 = hypro::vector_t<TypeParam>( 2 );
	hypro::matrix_t<TypeParam> basis1 = hypro::matrix_t<TypeParam>( 2, 2 );
	hypro::matrix_t<TypeParam> constr1 = hypro::matrix_t<TypeParam>( 4, 2 );
	hypro::vector_t<TypeParam> limits1 = hypro::vector_t<TypeParam>( 4 );
	center1 << 0, 0;
	basis1 << 1, 0, 0, 1;
	constr1 << 1, 0, -1, 0, 0, 1, 0, -1;
	limits1 << 2, 1, 1, 1;
	EXPECT_EQ( this->star_2d_rect, hypro::Starset<TypeParam>( constr1, limits1 ) );

	// a triangle:  |>
	hypro::vector_t<TypeParam> center2 = hypro::vector_t<TypeParam>( 2 );
	hypro::matrix_t<TypeParam> basis2 = hypro::matrix_t<TypeParam>( 2, 2 );
	hypro::matrix_t<TypeParam> constr2 = hypro::matrix_t<TypeParam>( 3, 2 );
	hypro::vector_t<TypeParam> limits2 = hypro::vector_t<TypeParam>( 3 );
	center2 << 0, 0;
	basis2 << 1, 0, 0, 1;
	constr2 << -1, 0, 1, 1, 1, -1;
	limits2 << 1, 1, 1;
	hypro::HPolytope<TypeParam> polytope2 = hypro::HPolytope<TypeParam>( constr2, limits2 );
	EXPECT_EQ( this->star_2d_triang1, hypro::Starset<TypeParam>( center2, basis2, polytope2 ) );

	// another triangle: /_|   (reversed, scaled)
	hypro::vector_t<TypeParam> center3 = hypro::vector_t<TypeParam>( 2 );
	hypro::matrix_t<TypeParam> basis3 = hypro::matrix_t<TypeParam>( 2, 2 );
	hypro::matrix_t<TypeParam> constr3 = hypro::matrix_t<TypeParam>( 3, 2 );
	hypro::vector_t<TypeParam> limits3 = hypro::vector_t<TypeParam>( 3 );
	center3 << 0, 0;
	basis3 << -2, 0, 0, 1;
	constr3 << -1, 0, 0, -1, 1, 1;
	limits3 << 1, 2, 1;
	EXPECT_EQ( this->star_2d_triang2, hypro::Starset<TypeParam>( center3, constr3, limits3, basis3 ) );

	star_dim = 5;
	// 5d box
	hypro::vector_t<TypeParam> center4 = hypro::vector_t<TypeParam>::Zero( star_dim );
	hypro::matrix_t<TypeParam> basis4 = hypro::matrix_t<TypeParam>::Identity( star_dim, star_dim );

	hypro::matrix_t<TypeParam> upper_bounds = hypro::matrix_t<TypeParam>::Identity( star_dim, star_dim );
	hypro::matrix_t<TypeParam> lower_bounds = hypro::matrix_t<TypeParam>::Identity( star_dim, star_dim ) * ( -1 );

	hypro::matrix_t<TypeParam> constr4 = hypro::matrix_t<TypeParam>( 2 * star_dim, star_dim );
	constr4 << lower_bounds, upper_bounds;
	hypro::vector_t<TypeParam> limits4 = hypro::vector_t<TypeParam>::Ones( 2 * star_dim );
	hypro::HPolytope<TypeParam> polytope4 = hypro::HPolytope<TypeParam>( constr4, limits4 );
	EXPECT_EQ( this->star_5d_box, hypro::Starset<TypeParam>( polytope4 ) );

	// test copy-constructor
	EXPECT_EQ( this->star_2d_triang2, hypro::Starset<TypeParam>( this->star_2d_triang2 ) );

	// test assignment operator
	hypro::Starset<TypeParam> tmp_triang1 = this->star_2d_triang1;
	EXPECT_EQ( this->star_2d_triang1, tmp_triang1 );
}

TYPED_TEST( StarsetTest, Dimension ) {
	EXPECT_EQ( 1, this->default_star.dimension() );
	EXPECT_EQ( 2, this->star_2d_rect.dimension() );
	EXPECT_EQ( 2, this->star_2d_triang1.dimension() );
	EXPECT_EQ( 2, this->star_2d_triang2.dimension() );
	EXPECT_EQ( 5, this->star_5d_box.dimension() );
}

TYPED_TEST( StarsetTest, LinearTransformation ) {
	hypro::matrix_t<TypeParam> transmat = hypro::matrix_t<TypeParam>( 2, 2 );
	transmat << cos( 45 ), -sin( 45 ), sin( 45 ), cos( 45 );

	hypro::Starset<TypeParam> transformed_rect = this->star_2d_rect.linearTransformation( transmat );
	EXPECT_EQ( transmat * this->star_2d_rect.generator(), transformed_rect.generator() );
	EXPECT_EQ( transmat * this->star_2d_rect.center(), transformed_rect.center() );
}

TYPED_TEST( StarsetTest, AffineTransformation ) {
	hypro::matrix_t<TypeParam> transmat = hypro::matrix_t<TypeParam>( 2, 2 );
	transmat << cos( 45 ), -sin( 45 ), sin( 45 ), cos( 45 );

	hypro::vector_t<TypeParam> offset = hypro::vector_t<TypeParam>( 2 );
	offset << 1, 1;

	hypro::Starset<TypeParam> transformed_rect = this->star_2d_rect.affineTransformation( transmat, offset );
	EXPECT_EQ( transmat * this->star_2d_rect.generator(), transformed_rect.generator() );
	EXPECT_EQ( transmat * this->star_2d_rect.center() + offset, transformed_rect.center() );
}

TYPED_TEST( StarsetTest, ContainsPoint ) {
	hypro::Point<TypeParam> p1( { -6, -2 } );
	EXPECT_TRUE( this->star_2d_triang2.contains( p1 ) );

	hypro::Point<TypeParam> p2( { 2, 2 } );
	EXPECT_TRUE( this->star_2d_triang2.contains( p2 ) );

	hypro::Point<TypeParam> p3( { 2, -2 } );
	EXPECT_TRUE( this->star_2d_triang2.contains( p3 ) );

	hypro::Point<TypeParam> p4( { -7, -2 } );
	EXPECT_FALSE( this->star_2d_triang2.contains( p4 ) );
}

TYPED_TEST( StarsetTest, ContainsStar ) {
	hypro::matrix_t<TypeParam> transform = hypro::matrix_t<TypeParam>( 2, 2 );
	transform << -2, 0, 0, 1;
	hypro::Starset<TypeParam> transformed_triang1 = this->star_2d_triang1.linearTransformation( transform );
	EXPECT_TRUE( this->star_2d_triang2.contains( transformed_triang1 ) );
}

TYPED_TEST( StarsetTest, GetSetOfSamplesAndContains ) {
	int n = 100;
	std::set<hypro::Point<TypeParam>> setOfSamples = uniform_sampling( this->star_2d_triang2, n );
	for ( auto sample : setOfSamples ) {
		EXPECT_TRUE( this->star_2d_triang2.contains( sample ) );
	}
}

TYPED_TEST( StarsetTest, Vertices ) {
	std::vector<hypro::Point<TypeParam>> v = this->star_2d_triang2.vertices();
	hypro::Point<TypeParam> p1( { -6, -2 } );
	hypro::Point<TypeParam> p2( { 2, 2 } );
	hypro::Point<TypeParam> p3( { 2, -2 } );
	EXPECT_EQ( 3, v.size() );
	ASSERT_NE( std::find( v.begin(), v.end(), p1 ), v.end() );	// check if the vertices vector contains p1
	ASSERT_NE( std::find( v.begin(), v.end(), p2 ), v.end() );
	ASSERT_NE( std::find( v.begin(), v.end(), p3 ), v.end() );
}

TYPED_TEST( StarsetTest, MinkowskiSum ) {
	// use sampling to check if for a p1 from Star1 and for a p2 from Star2 is p1+p2 in Star1+Star2
	// check the vertices instead
	int n = 100;
	std::set<hypro::Point<TypeParam>> setOfSamples1 = uniform_sampling( this->star_2d_triang1, n );
	std::set<hypro::Point<TypeParam>> setOfSamples2 = uniform_sampling( this->star_2d_triang2, n );

	hypro::Starset<TypeParam> sum_star = this->star_2d_triang1.minkowskiSum( this->star_2d_triang2 );
	EXPECT_EQ( this->star_2d_triang1.dimension(), sum_star.dimension() );
	EXPECT_EQ( this->star_2d_triang2.dimension(), sum_star.dimension() );

	typename std::set<hypro::Point<TypeParam>>::iterator it1 = setOfSamples1.begin();
	typename std::set<hypro::Point<TypeParam>>::iterator it2 = setOfSamples2.begin();

	for ( int i = 0; i < n; i++ ) {
		EXPECT_TRUE( sum_star.contains( ( *it1 ) + ( *it2 ) ) );
		it1++;
		it2++;
	}

	std::vector<hypro::Point<TypeParam>> vertices1 = this->star_2d_triang1.vertices();
	std::vector<hypro::Point<TypeParam>> vertices2 = this->star_2d_triang2.vertices();
	for ( auto vertex1 : vertices1 ) {
		for ( auto vertex2 : vertices2 ) {
			EXPECT_TRUE( sum_star.contains( vertex1 + vertex2 ) );
		}
	}
}

TYPED_TEST( StarsetTest, Empty ) {
	EXPECT_FALSE( this->star_2d_rect.empty() );
}

TYPED_TEST( StarsetTest, IntersectHalfspaceEmpty ) {
	hypro::Halfspace<TypeParam> halfplane = hypro::Halfspace<TypeParam>( { 1, 0 }, -2 );
	hypro::Starset<TypeParam> sliced_star = this->star_2d_rect.intersectHalfspace( halfplane );
	EXPECT_TRUE( sliced_star.empty() );

	double ang = 45 * (PI / 180);
	// std::cout << "Rotation matrix with radians: " << ang << std::endl;
	hypro::matrix_t<TypeParam> transmat = hypro::matrix_t<TypeParam>( 2, 2 );
	transmat << cos( ang ), -sin( ang ), sin( ang ), cos( ang );

	hypro::vector_t<TypeParam> offset = hypro::vector_t<TypeParam>( 2 );
	offset << -0.5, -0.5;

	hypro::Starset<TypeParam> new_star = this->star_2d_rect.affineTransformation( transmat, offset );

	hypro::Halfspace<TypeParam> halfplane2 = hypro::Halfspace<TypeParam>( { 1, 1 }, 1 );
	hypro::Starset<TypeParam> intersection1 = new_star.intersectHalfspace( halfplane2 );
	// std::cout << "vertices1: " << intersection1.vertices() << std::endl;

	EXPECT_TRUE( intersection1.contains( hypro::Point<TypeParam>( { 0.4, 0.4 } ) ) );
	EXPECT_FALSE( intersection1.contains( hypro::Point<TypeParam>( { 0.7, 0.7 } ) ) );

	hypro::Halfspace<TypeParam> halfplane3 = hypro::Halfspace<TypeParam>( { 2, 1 }, 1 );
	hypro::Starset<TypeParam> intersection2 = new_star.intersectHalfspace( halfplane3 );
	// std::cout << "vertices2: " << intersection2.vertices() << std::endl;

	EXPECT_TRUE( intersection2.contains( hypro::Point<TypeParam>( { 0.3, 0.0 } ) ) );
	EXPECT_FALSE( intersection2.contains( hypro::Point<TypeParam>( { 0.7, 0.0 } ) ) );
}

// TYPED_TEST( StarsetTest, Union ) {
//   // the result of the union could be non-convex, so overapproximation is needed (is it already implemented?)
//   // hypro::Starset<TypeParam> the_same = this->star_2d_triang2.unite( this->star_2d_triang2 );
//   // EXPECT_EQ(this->star_2d_triang2, the_same);
// }
