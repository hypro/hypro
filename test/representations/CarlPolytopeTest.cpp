
#include "test/defines.h"

#include "gtest/gtest.h"
#include <hypro/representations/GeometricObjectBase.h>

template <typename Number>
class CarlPolytopeTest : public ::testing::Test {
  protected:
	virtual void SetUp() {}

	virtual void TearDown() {}
};

TYPED_TEST( CarlPolytopeTest, Constructor ) {
	hypro::CarlPolytope<TypeParam> p1{};

	carl::Interval<TypeParam> i1{ 1, 2 };
	carl::Interval<TypeParam> i2{ 2, 3 };
	std::vector<carl::Interval<TypeParam>> intervals;
	intervals.emplace_back( i1 );
	intervals.emplace_back( i2 );

	hypro::CarlPolytope<TypeParam> p2{ intervals };

	hypro::matrix_t<TypeParam> constraints = hypro::matrix_t<TypeParam>( 4, 2 );
	hypro::vector_t<TypeParam> constants = hypro::vector_t<TypeParam>( 4 );
	constraints << 1, 0, -1, 0, 0, 1, 0, -1;
	constants << 1, 2, 2, 2;

	hypro::CarlPolytope<TypeParam> p3{ constraints, constants };
}

TYPED_TEST( CarlPolytopeTest, Intersection ) {
	carl::Interval<TypeParam> i1{ 1, 2 };
	carl::Interval<TypeParam> i2{ 2, 3 };
	std::vector<carl::Interval<TypeParam>> intervals;
	intervals.emplace_back( i1 );
	intervals.emplace_back( i2 );

	hypro::CarlPolytope<TypeParam> p1{ intervals };

	carl::Interval<TypeParam> i3{ 1, 1 };
	carl::Interval<TypeParam> i4{ 2, 5 };
	intervals.clear();
	intervals.emplace_back( i3 );
	intervals.emplace_back( i4 );

	hypro::CarlPolytope<TypeParam> p2{ intervals };

	hypro::CarlPolytope<TypeParam> result = p1.intersect( p2 );
	hypro::CarlPolytope<TypeParam> result2 = p2.intersect( p1 );

	EXPECT_EQ( result.getFormula(), result2.getFormula() );
}

TYPED_TEST( CarlPolytopeTest, GetHalfspaces ) {
	carl::Interval<TypeParam> i1 = carl::Interval<TypeParam>{ 1, 2 };
	carl::Interval<TypeParam> i2 = carl::Interval<TypeParam>{ 1, 2 };
	std::vector<carl::Interval<TypeParam>> intervals;
	intervals.push_back( i1 );
	intervals.push_back( i2 );

	hypro::CarlPolytope<TypeParam> c1{ intervals };

	auto hspVector = c1.getHalfspaces();

	EXPECT_EQ( std::size_t( 4 ), hspVector.size() );
	EXPECT_TRUE( std::find( hspVector.begin(), hspVector.end(), hypro::Halfspace<TypeParam>( { 1, 0 }, 2 ) ) !=
				 hspVector.end() );
	EXPECT_TRUE( std::find( hspVector.begin(), hspVector.end(), hypro::Halfspace<TypeParam>( { -1, 0 }, -1 ) ) !=
				 hspVector.end() );
	EXPECT_TRUE( std::find( hspVector.begin(), hspVector.end(), hypro::Halfspace<TypeParam>( { 0, 1 }, 2 ) ) !=
				 hspVector.end() );
	EXPECT_TRUE( std::find( hspVector.begin(), hspVector.end(), hypro::Halfspace<TypeParam>( { 0, -1 }, -1 ) ) !=
				 hspVector.end() );
}

TYPED_TEST( CarlPolytopeTest, AddConstraint ) {
	carl::Interval<TypeParam> i1 = carl::Interval<TypeParam>{ 1, 2 };
	carl::Interval<TypeParam> i2 = carl::Interval<TypeParam>{ 1, 2 };
	std::vector<carl::Interval<TypeParam>> intervals;
	intervals.push_back( i1 );
	intervals.push_back( i2 );

	hypro::CarlPolytope<TypeParam> c1{ intervals };

	auto hspVector = c1.getHalfspaces();

	EXPECT_EQ( std::size_t( 4 ), hspVector.size() );
	EXPECT_TRUE( std::find( hspVector.begin(), hspVector.end(), hypro::Halfspace<TypeParam>( { 1, 0 }, 2 ) ) !=
				 hspVector.end() );
	EXPECT_TRUE( std::find( hspVector.begin(), hspVector.end(), hypro::Halfspace<TypeParam>( { -1, 0 }, -1 ) ) !=
				 hspVector.end() );
	EXPECT_TRUE( std::find( hspVector.begin(), hspVector.end(), hypro::Halfspace<TypeParam>( { 0, 1 }, 2 ) ) !=
				 hspVector.end() );
	EXPECT_TRUE( std::find( hspVector.begin(), hspVector.end(), hypro::Halfspace<TypeParam>( { 0, -1 }, -1 ) ) !=
				 hspVector.end() );
	EXPECT_EQ( std::size_t( 2 ), c1.dimension() );

	// add constraints which introduce a new variable - the dimension should be increased.
	carl::Variable t = carl::freshRealVariable( "t" );
	c1.addConstraint( hypro::ConstraintT<TypeParam>( hypro::PolyT<TypeParam>( t ), carl::Relation::GEQ ) );
	EXPECT_EQ( std::size_t( 3 ), c1.dimension() );

	hspVector = c1.getHalfspaces();

	EXPECT_EQ( std::size_t( 5 ), hspVector.size() );
	EXPECT_TRUE( std::find( hspVector.begin(), hspVector.end(), hypro::Halfspace<TypeParam>( { 1, 0, 0 }, 2 ) ) !=
				 hspVector.end() );
	EXPECT_TRUE( std::find( hspVector.begin(), hspVector.end(), hypro::Halfspace<TypeParam>( { -1, 0, 0 }, -1 ) ) !=
				 hspVector.end() );
	EXPECT_TRUE( std::find( hspVector.begin(), hspVector.end(), hypro::Halfspace<TypeParam>( { 0, 1, 0 }, 2 ) ) !=
				 hspVector.end() );
	EXPECT_TRUE( std::find( hspVector.begin(), hspVector.end(), hypro::Halfspace<TypeParam>( { 0, -1, 0 }, -1 ) ) !=
				 hspVector.end() );
	EXPECT_TRUE( std::find( hspVector.begin(), hspVector.end(), hypro::Halfspace<TypeParam>( { 0, 0, -1 }, 0 ) ) !=
				 hspVector.end() );
}

TYPED_TEST( CarlPolytopeTest, Substitution ) {
	carl::Interval<TypeParam> i1 = carl::Interval<TypeParam>{ 1, 2 };
	carl::Interval<TypeParam> i2 = carl::Interval<TypeParam>{ 1, 2 };
	std::vector<carl::Interval<TypeParam>> intervals;
	intervals.push_back( i1 );
	intervals.push_back( i2 );

	hypro::CarlPolytope<TypeParam> c1{ intervals };

	auto hspVector = c1.getHalfspaces();

	EXPECT_EQ( std::size_t( 4 ), hspVector.size() );
	EXPECT_TRUE( std::find( hspVector.begin(), hspVector.end(), hypro::Halfspace<TypeParam>( { 1, 0 }, 2 ) ) !=
				 hspVector.end() );
	EXPECT_TRUE( std::find( hspVector.begin(), hspVector.end(), hypro::Halfspace<TypeParam>( { -1, 0 }, -1 ) ) !=
				 hspVector.end() );
	EXPECT_TRUE( std::find( hspVector.begin(), hspVector.end(), hypro::Halfspace<TypeParam>( { 0, 1 }, 2 ) ) !=
				 hspVector.end() );
	EXPECT_TRUE( std::find( hspVector.begin(), hspVector.end(), hypro::Halfspace<TypeParam>( { 0, -1 }, -1 ) ) !=
				 hspVector.end() );
	EXPECT_EQ( std::size_t( 2 ), c1.dimension() );

	c1.substituteVariable( hypro::VariablePool::getInstance().carlVarByIndex( 0 ),
						   hypro::VariablePool::getInstance().carlVarByIndex( 2 ) );

	EXPECT_EQ( std::size_t( 3 ), c1.dimension() );

	hspVector = c1.getHalfspaces();

	EXPECT_EQ( std::size_t( 4 ), hspVector.size() );
	EXPECT_TRUE( std::find( hspVector.begin(), hspVector.end(), hypro::Halfspace<TypeParam>( { 0, 0, 1 }, 2 ) ) !=
				 hspVector.end() );
	EXPECT_TRUE( std::find( hspVector.begin(), hspVector.end(), hypro::Halfspace<TypeParam>( { 0, 0, -1 }, -1 ) ) !=
				 hspVector.end() );
	EXPECT_TRUE( std::find( hspVector.begin(), hspVector.end(), hypro::Halfspace<TypeParam>( { 0, 1, 0 }, 2 ) ) !=
				 hspVector.end() );
	EXPECT_TRUE( std::find( hspVector.begin(), hspVector.end(), hypro::Halfspace<TypeParam>( { 0, -1, 0 }, -1 ) ) !=
				 hspVector.end() );
}

TYPED_TEST( CarlPolytopeTest, TimeElapse ) {
	using Pol = hypro::PolyT<TypeParam>;
	using Constr = hypro::ConstraintT<TypeParam>;
	using Intv = carl::Interval<TypeParam>;
	using Var = carl::Variable;

	auto& vpool = hypro::VariablePool::getInstance();

	// original variables
	Var x = vpool.carlVarByIndex( 0 );
	Var y = vpool.carlVarByIndex( 1 );

	// initial constraints
	Intv i1 = Intv{ 1, 2 };
	Intv i2 = Intv{ 1, 2 };
	std::vector<Intv> intervals;
	intervals.push_back( i1 );
	intervals.push_back( i2 );
	// create initial set represented as a carlPolytope
	hypro::CarlPolytope<TypeParam> c1{ intervals };

	// let time pass: substitute original variables by ^pre-versions, add constraints for time being positive, the flow
	// and the invariants.
	Var t = vpool.newCarlVariable( "t" );
	Var xp = vpool.newCarlVariable( "xpre" );
	Var yp = vpool.newCarlVariable( "ypre" );

	// substitute
	c1.substituteVariable( vpool.carlVarByIndex( 0 ), xp );
	c1.substituteVariable( vpool.carlVarByIndex( 1 ), yp );

	// add new constraints
	// t >= 0
	c1.addConstraint( Constr( Pol( t ), carl::Relation::GEQ ) );
	// flow: x' = [2,3], y' = [1,2]
	// -x + xp + 2t <= 0, -x + xp +3t >= 0
	c1.addConstraint( Constr( -Pol( x ) + Pol( xp ) + Pol( 2 ) * t, carl::Relation::LEQ ) );
	c1.addConstraint( Constr( -Pol( x ) + Pol( xp ) + Pol( 3 ) * t, carl::Relation::GEQ ) );
	// -y + yp + t <= 0, -y + yp +2t >= 0
	c1.addConstraint( Constr( -Pol( y ) + Pol( yp ) + Pol( t ), carl::Relation::LEQ ) );
	c1.addConstraint( Constr( -Pol( y ) + Pol( yp ) + Pol( 2 ) * t, carl::Relation::GEQ ) );
	// invariants: x <= 10, y <= 10
	c1.addConstraint( Constr( Pol( x ) - Pol( 10 ), carl::Relation::LEQ ) );
	c1.addConstraint( Constr( Pol( y ) - Pol( 10 ), carl::Relation::LEQ ) );

	// eliminate ^pre-variables to obtain polytope after having let time pass
	c1.eliminateVariable( xp );
	c1.eliminateVariable( yp );
	c1.eliminateVariable( t );

	EXPECT_EQ( std::size_t( 2 ), c1.dimension() );
}

TYPED_TEST( CarlPolytopeTest, RedundantConstraints ) {
	using Pol = hypro::PolyT<TypeParam>;
	using Constr = hypro::ConstraintT<TypeParam>;
	using Intv = carl::Interval<TypeParam>;
	using Var = carl::Variable;

	auto& vpool = hypro::VariablePool::getInstance();

	// original variables
	Var x = vpool.carlVarByIndex( 0 );
	Var y = vpool.carlVarByIndex( 1 );

	// initial constraints
	Intv i1 = Intv{ 1, 2 };
	Intv i2 = Intv{ 1, 2 };
	std::vector<Intv> intervals;
	intervals.push_back( i1 );
	intervals.push_back( i2 );
	// create initial set represented as a carlPolytope
	hypro::CarlPolytope<TypeParam> c1{ intervals };

	EXPECT_EQ( std::size_t( 4 ), c1.size() );

	c1.addConstraint( Constr( Pol( x ) - Pol( 5 ), carl::Relation::LEQ ) );
	c1.addConstraint( Constr( Pol( x ) + Pol( y ) - Pol( 20 ), carl::Relation::LEQ ) );

	EXPECT_EQ( std::size_t( 6 ), c1.size() );

	c1.removeRedundancy();

	EXPECT_EQ( std::size_t( 4 ), c1.size() );

	auto hspVector = c1.getHalfspaces();

	EXPECT_EQ( std::size_t( 4 ), hspVector.size() );
	EXPECT_TRUE( std::find( hspVector.begin(), hspVector.end(), hypro::Halfspace<TypeParam>( { 1, 0 }, 2 ) ) !=
				 hspVector.end() );
	EXPECT_TRUE( std::find( hspVector.begin(), hspVector.end(), hypro::Halfspace<TypeParam>( { -1, 0 }, -1 ) ) !=
				 hspVector.end() );
	EXPECT_TRUE( std::find( hspVector.begin(), hspVector.end(), hypro::Halfspace<TypeParam>( { 0, 1 }, 2 ) ) !=
				 hspVector.end() );
	EXPECT_TRUE( std::find( hspVector.begin(), hspVector.end(), hypro::Halfspace<TypeParam>( { 0, -1 }, -1 ) ) !=
				 hspVector.end() );
	EXPECT_EQ( std::size_t( 2 ), c1.dimension() );
}

TYPED_TEST( CarlPolytopeTest, PointContainment ) {
	using Intv = carl::Interval<TypeParam>;

	// initial constraints
	Intv i1 = Intv{ 1, 2 };
	Intv i2 = Intv{ 1, 2 };
	std::vector<Intv> intervals;
	intervals.push_back( i1 );
	intervals.push_back( i2 );
	// create initial set represented as a carlPolytope
	hypro::CarlPolytope<TypeParam> c1{ intervals };

	EXPECT_TRUE( c1.contains( hypro::Point<TypeParam>{ 1, 1 } ) );
	EXPECT_TRUE( c1.contains( hypro::Point<TypeParam>{ 1, 2 } ) );
	EXPECT_TRUE( c1.contains( hypro::Point<TypeParam>{ 2, 1 } ) );
	EXPECT_TRUE( c1.contains( hypro::Point<TypeParam>{ 2, 2 } ) );
	EXPECT_TRUE( c1.contains( hypro::Point<TypeParam>{ 1.5, 1.5 } ) );

	EXPECT_FALSE( c1.contains( hypro::Point<TypeParam>{ 0, 0 } ) );
	EXPECT_FALSE( c1.contains( hypro::Point<TypeParam>{ 0, 1 } ) );
	EXPECT_FALSE( c1.contains( hypro::Point<TypeParam>{ 1, 0 } ) );
	EXPECT_FALSE( c1.contains( hypro::Point<TypeParam>{ 2.1, 2 } ) );
}