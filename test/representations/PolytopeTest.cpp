/**
 * Test for the wrapper of the PPL Polytope.
 * @file PolytopeTest.cpp
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 *
 * @since       2014-04-02
 * @version     2014-04-08
 */

#include "test/defines.h"
#include "gtest/gtest.h"

#include <hypro/representations/GeometricObjectBase.h>

using namespace hypro;
using namespace carl;

template <typename Number>
class PolytopeTest : public ::testing::Test {
  protected:
	virtual void SetUp() {
		pool.clear();
		x = pool.newCarlVariable();
		y = pool.newCarlVariable();

		// p1
		typename Point<Number>::coordinateMap coordinates1;
		coordinates1.insert( std::make_pair( x, Number( 4 ) ) );
		coordinates1.insert( std::make_pair( y, Number( 4 ) ) );
		p1 = Point<Number>( { 4, 4 } );

		// p2
		typename Point<Number>::coordinateMap coordinates2;
		coordinates2.insert( std::make_pair( x, Number( 5 ) ) );
		coordinates2.insert( std::make_pair( y, Number( 7 ) ) );
		p2 = Point<Number>( { 5, 7 } );

		// p3
		typename Point<Number>::coordinateMap coordinates3;
		coordinates3.insert( std::make_pair( x, Number( 7 ) ) );
		coordinates3.insert( std::make_pair( y, Number( 7 ) ) );
		p3 = Point<Number>( { 7, 7 } );

		// p4
		typename Point<Number>::coordinateMap coordinates4;
		coordinates4.insert( std::make_pair( x, Number( 8 ) ) );
		coordinates4.insert( std::make_pair( y, Number( 4 ) ) );
		p4 = Point<Number>( { 8, 4 } );

		// p5
		typename Point<Number>::coordinateMap coordinates5;
		coordinates5.insert( std::make_pair( x, Number( 3 ) ) );
		coordinates5.insert( std::make_pair( y, Number( 3 ) ) );
		p5 = Point<Number>( { 3, 3 } );

		// p6
		typename Point<Number>::coordinateMap coordinates6;
		coordinates6.insert( std::make_pair( x, Number( 4 ) ) );
		coordinates6.insert( std::make_pair( y, Number( 5 ) ) );
		p6 = Point<Number>( { 4, 5 } );

		// p7
		typename Point<Number>::coordinateMap coordinates7;
		coordinates7.insert( std::make_pair( x, Number( 5 ) ) );
		coordinates7.insert( std::make_pair( y, Number( 3 ) ) );
		p7 = Point<Number>( { 5, 3 } );
	}

	virtual void TearDown() { hypro::VariablePool::getInstance().clear(); }

	hypro::VariablePool& pool = hypro::VariablePool::getInstance();
	carl::Variable x;
	carl::Variable y;

	Point<Number> p1;
	Point<Number> p2;
	Point<Number> p3;
	Point<Number> p4;
	Point<Number> p5;
	Point<Number> p6;
	Point<Number> p7;
};

/**
 * @covers polytope::constructor
 * @covers polytope::pointToGenerator
 */
TYPED_TEST( PolytopeTest, Constructor ) {
	hypro::Polytope<TypeParam> p0;

	std::vector<Point<TypeParam>> ps;
	ps.push_back( this->p1 );
	ps.push_back( this->p2 );
	ps.push_back( this->p3 );
	ps.push_back( this->p4 );
	Polytope<TypeParam> p1 = Polytope<TypeParam>( ps );
	//    std::cout << "P1" << std::endl;
	//    p1.print();
	EXPECT_EQ( p1.dimension(), unsigned( 2 ) );
	EXPECT_FALSE( p1.rawPolyhedron().is_empty() );
	Polytope<TypeParam> p3 = Polytope<TypeParam>( ps );

	Polytope<TypeParam> p2 = Polytope<TypeParam>( 2 );
	EXPECT_EQ( p2.dimension(), unsigned( 2 ) );

	Eigen::Matrix<TypeParam, Eigen::Dynamic, Eigen::Dynamic> A =
		  Eigen::Matrix<TypeParam, Eigen::Dynamic, Eigen::Dynamic>( 2, 2 );
	A( 0, 0 ) = 1;
	A( 0, 1 ) = 2;
	A( 1, 0 ) = 1;
	A( 1, 1 ) = 3;

	Eigen::Matrix<TypeParam, Eigen::Dynamic, 1> b = Eigen::Matrix<TypeParam, Eigen::Dynamic, 1>( 2, 1 );
	b( 0, 0 ) = 4;
	b( 1, 0 ) = 5;

	//    hypro::VariablePool::getInstance().print();

	Polytope<TypeParam> p4 = Polytope<TypeParam>( A, b );

	//    p4.print();

	EXPECT_EQ( p4.dimension(), unsigned( 2 ) );

	SUCCEED();
}

TYPED_TEST( PolytopeTest, Access ) {
	std::vector<Point<TypeParam>> ps1;
	ps1.push_back( this->p1 );
	ps1.push_back( this->p2 );
	ps1.push_back( this->p3 );
	ps1.push_back( this->p4 );
	hypro::Polytope<TypeParam> p1 = Polytope<TypeParam>( ps1 );
	EXPECT_EQ( p1.dimension(), unsigned( 2 ) );

	std::vector<Point<TypeParam>> ps2;
	Point<TypeParam> p5 = Point<TypeParam>( { TypeParam( 7 ), TypeParam( 8 ) } );
	Point<TypeParam> p6 = Point<TypeParam>( { TypeParam( 1 ), TypeParam( 2 ) } );
	Point<TypeParam> p7 = Point<TypeParam>( { TypeParam( 4 ), TypeParam( 3 ) } );
	ps2.push_back( p5 );
	ps2.push_back( p6 );
	ps2.push_back( p7 );

	//    std::cout << "---" << std::endl;
	//    hypro::VariablePool::getInstance().print();

	Polytope<TypeParam> p2 = Polytope<TypeParam>( ps2 );

	//    std::cout << "---" << std::endl;
	//    hypro::VariablePool::getInstance().print();

	EXPECT_EQ( p2.dimension(), unsigned( 2 ) );

	std::vector<Point<TypeParam>> points = p2.vertices();
}

TYPED_TEST( PolytopeTest, PointToGenerator ) {
	Parma_Polyhedra_Library::Generator gs = polytope::pointToGenerator( this->p1 );
	//    std::cout << "Generator: ";
	//    gs.print();
	//    std::cout << std::endl;
	gs = polytope::pointToGenerator( this->p2 );
	//    std::cout << "Generator: ";
	//    gs.print();
	//    std::cout << std::endl;
	gs = polytope::pointToGenerator( this->p3 );
	//    std::cout << "Generator: ";
	//    gs.print();
	//    std::cout << std::endl;
	gs = polytope::pointToGenerator( this->p4 );
	//    std::cout << "Generator: ";
	//    gs.print();
	//    std::cout << std::endl;

	SUCCEED();
}

TYPED_TEST( PolytopeTest, Intersection ) {
	std::vector<Point<TypeParam>> ps1;
	ps1.push_back( this->p1 );
	ps1.push_back( this->p2 );
	ps1.push_back( this->p3 );
	ps1.push_back( this->p4 );
	hypro::Polytope<TypeParam> pt1;
	pt1.print();
	pt1 = Polytope<TypeParam>( ps1 );
	pt1.print();
	EXPECT_FALSE( pt1.rawPolyhedron().is_universe() );
	EXPECT_TRUE( pt1.rawPolyhedron().is_topologically_closed() );

	std::vector<Point<TypeParam>> ps2;
	ps2.push_back( this->p5 );
	ps2.push_back( this->p6 );
	ps2.push_back( this->p7 );
	hypro::Polytope<TypeParam> pt2 = Polytope<TypeParam>( ps2 );
	pt2.print();

	hypro::Polytope<TypeParam> res;
	res = pt1.intersect( pt2 );
	res.print();
	res = res.hull();
	res.print();

	std::cout << "Part 2 starting: " << std::endl;
	std::vector<Point<TypeParam>> ps3;
	vector_t<TypeParam> v01 = vector_t<TypeParam>( 3 );
	v01( 0 ) = 1;
	v01( 1 ) = 1;
	v01( 2 ) = 1;
	Point<TypeParam> p01 = Point<TypeParam>( v01 );
	vector_t<TypeParam> v02 = vector_t<TypeParam>( 3 );
	v02( 0 ) = 1;
	v02( 1 ) = 3;
	v02( 2 ) = 1;
	Point<TypeParam> p02 = Point<TypeParam>( v02 );
	vector_t<TypeParam> v03 = vector_t<TypeParam>( 3 );
	v03( 0 ) = 3;
	v03( 1 ) = 1;
	v03( 2 ) = 1;
	Point<TypeParam> p03 = Point<TypeParam>( v03 );
	vector_t<TypeParam> v04 = vector_t<TypeParam>( 3 );
	v04( 0 ) = 3;
	v04( 1 ) = 3;
	v04( 2 ) = 1;
	Point<TypeParam> p04 = Point<TypeParam>( v04 );
	vector_t<TypeParam> v05 = vector_t<TypeParam>( 3 );
	v05( 0 ) = 1;
	v05( 1 ) = 1;
	v05( 2 ) = 3;
	Point<TypeParam> p05 = Point<TypeParam>( v05 );
	vector_t<TypeParam> v06 = vector_t<TypeParam>( 3 );
	v06( 0 ) = 1;
	v06( 1 ) = 3;
	v06( 2 ) = 3;
	Point<TypeParam> p06 = Point<TypeParam>( v06 );
	vector_t<TypeParam> v07 = vector_t<TypeParam>( 3 );
	v07( 0 ) = 3;
	v07( 1 ) = 1;
	v07( 2 ) = 3;
	Point<TypeParam> p07 = Point<TypeParam>( v07 );
	vector_t<TypeParam> v08 = vector_t<TypeParam>( 3 );
	v08( 0 ) = 3;
	v08( 1 ) = 3;
	v08( 2 ) = 3;
	Point<TypeParam> p08 = Point<TypeParam>( v08 );

	ps3.push_back( p01 );
	ps3.push_back( p02 );
	ps3.push_back( p03 );
	ps3.push_back( p04 );
	ps3.push_back( p05 );
	ps3.push_back( p06 );
	ps3.push_back( p07 );
	ps3.push_back( p08 );

	hypro::Polytope<TypeParam> pt3 = Polytope<TypeParam>( ps3 );

	std::vector<Point<TypeParam>> ps4;
	vector_t<TypeParam> v09 = vector_t<TypeParam>( 3 );
	v09( 0 ) = 2;
	v09( 1 ) = 2;
	v09( 2 ) = 1;
	Point<TypeParam> p09 = Point<TypeParam>( v09 );
	vector_t<TypeParam> v10 = vector_t<TypeParam>( 3 );
	v10( 0 ) = 2;
	v10( 1 ) = 4;
	v10( 2 ) = 1;
	Point<TypeParam> p10 = Point<TypeParam>( v10 );
	vector_t<TypeParam> v11 = vector_t<TypeParam>( 3 );
	v11( 0 ) = 4;
	v11( 1 ) = 2;
	v11( 2 ) = 1;
	Point<TypeParam> p11 = Point<TypeParam>( { 4, 2, 1 } );
	vector_t<TypeParam> v12 = vector_t<TypeParam>( 3 );
	v12( 0 ) = 4;
	v12( 1 ) = 4;
	v12( 2 ) = 1;
	Point<TypeParam> p12 = Point<TypeParam>( v12 );
	vector_t<TypeParam> v13 = vector_t<TypeParam>( 3 );
	v13( 0 ) = 2;
	v13( 1 ) = 2;
	v13( 2 ) = 3;
	Point<TypeParam> p13 = Point<TypeParam>( v13 );
	vector_t<TypeParam> v14 = vector_t<TypeParam>( 3 );
	v14( 0 ) = 2;
	v14( 1 ) = 4;
	v14( 2 ) = 3;
	Point<TypeParam> p14 = Point<TypeParam>( v14 );
	vector_t<TypeParam> v15 = vector_t<TypeParam>( 3 );
	v15( 0 ) = 4;
	v15( 1 ) = 2;
	v15( 2 ) = 3;
	Point<TypeParam> p15 = Point<TypeParam>( v15 );
	vector_t<TypeParam> v16 = vector_t<TypeParam>( 3 );
	v16( 0 ) = 4;
	v16( 1 ) = 4;
	v16( 2 ) = 3;
	Point<TypeParam> p16 = Point<TypeParam>( v16 );

	ps4.push_back( p09 );
	ps4.push_back( p10 );
	ps4.push_back( p11 );
	ps4.push_back( p12 );
	ps4.push_back( p13 );
	ps4.push_back( p14 );
	ps4.push_back( p15 );
	ps4.push_back( p16 );

	hypro::Polytope<TypeParam> pt4 = Polytope<TypeParam>( ps4 );

	std::cout << __func__ << ":" << __LINE__ << " dimensions : " << pt3.dimension() << " and " << pt4.dimension()
			  << std::endl;

	hypro::Polytope<TypeParam> res2 = pt3.intersect( pt4 );

	res2 = res2.hull();

	for ( auto& vertex : res2.vertices() ) {
		EXPECT_TRUE( pt3.contains( vertex ) );
		EXPECT_TRUE( pt4.contains( vertex ) );
	}

	hypro::Polytope<TypeParam> res3 = res2.intersect( Polytope<TypeParam>() );

	EXPECT_TRUE( res3.dimension() == 0 );
}

TYPED_TEST( PolytopeTest, Union ) {
	std::vector<Point<TypeParam>> ps1;
	ps1.push_back( this->p1 );
	ps1.push_back( this->p2 );
	ps1.push_back( this->p3 );
	ps1.push_back( this->p4 );
	hypro::Polytope<TypeParam> pt1;
	pt1 = Polytope<TypeParam>( ps1 );
	EXPECT_FALSE( pt1.rawPolyhedron().is_universe() );
	EXPECT_TRUE( pt1.rawPolyhedron().is_topologically_closed() );

	std::vector<Point<TypeParam>> ps2;
	ps2.push_back( this->p5 );
	ps2.push_back( this->p6 );
	ps2.push_back( this->p7 );
	hypro::Polytope<TypeParam> pt2 = Polytope<TypeParam>( ps2 );

	hypro::Polytope<TypeParam> res;
	res = pt1.unite( pt2 );
	res = res.hull();

	std::cout << "Part 2 starting: " << std::endl;
	std::vector<Point<TypeParam>> ps3;
	vector_t<TypeParam> v01 = vector_t<TypeParam>( 3 );
	v01( 0 ) = 1;
	v01( 1 ) = 1;
	v01( 2 ) = 1;
	Point<TypeParam> p01 = Point<TypeParam>( v01 );
	vector_t<TypeParam> v02 = vector_t<TypeParam>( 3 );
	v02( 0 ) = 1;
	v02( 1 ) = 3;
	v02( 2 ) = 1;
	Point<TypeParam> p02 = Point<TypeParam>( v02 );
	vector_t<TypeParam> v03 = vector_t<TypeParam>( 3 );
	v03( 0 ) = 3;
	v03( 1 ) = 1;
	v03( 2 ) = 1;
	Point<TypeParam> p03 = Point<TypeParam>( v03 );
	vector_t<TypeParam> v04 = vector_t<TypeParam>( 3 );
	v04( 0 ) = 3;
	v04( 1 ) = 3;
	v04( 2 ) = 1;
	Point<TypeParam> p04 = Point<TypeParam>( v04 );
	vector_t<TypeParam> v05 = vector_t<TypeParam>( 3 );
	v05( 0 ) = 1;
	v05( 1 ) = 1;
	v05( 2 ) = 3;
	Point<TypeParam> p05 = Point<TypeParam>( v05 );
	vector_t<TypeParam> v06 = vector_t<TypeParam>( 3 );
	v06( 0 ) = 1;
	v06( 1 ) = 3;
	v06( 2 ) = 3;
	Point<TypeParam> p06 = Point<TypeParam>( v06 );
	vector_t<TypeParam> v07 = vector_t<TypeParam>( 3 );
	v07( 0 ) = 3;
	v07( 1 ) = 1;
	v07( 2 ) = 3;
	Point<TypeParam> p07 = Point<TypeParam>( v07 );
	vector_t<TypeParam> v08 = vector_t<TypeParam>( 3 );
	v08( 0 ) = 3;
	v08( 1 ) = 3;
	v08( 2 ) = 3;
	Point<TypeParam> p08 = Point<TypeParam>( v08 );

	ps3.push_back( p01 );
	ps3.push_back( p02 );
	ps3.push_back( p03 );
	ps3.push_back( p04 );
	ps3.push_back( p05 );
	ps3.push_back( p06 );
	ps3.push_back( p07 );
	ps3.push_back( p08 );

	hypro::Polytope<TypeParam> pt3 = Polytope<TypeParam>( ps3 );

	std::vector<Point<TypeParam>> ps4;

	vector_t<TypeParam> v09 = vector_t<TypeParam>( 3 );
	v09( 0 ) = 3;
	v09( 1 ) = 5;
	v09( 2 ) = 1;
	Point<TypeParam> p09 = Point<TypeParam>( v09 );
	vector_t<TypeParam> v10 = vector_t<TypeParam>( 3 );
	v10( 0 ) = 5;
	v10( 1 ) = 3;
	v10( 2 ) = 1;
	Point<TypeParam> p10 = Point<TypeParam>( v10 );
	vector_t<TypeParam> v11 = vector_t<TypeParam>( 3 );
	v11( 0 ) = 5;
	v11( 1 ) = 5;
	v11( 2 ) = 1;
	Point<TypeParam> p11 = Point<TypeParam>( v11 );
	vector_t<TypeParam> v12 = vector_t<TypeParam>( 3 );
	v12( 0 ) = 3;
	v12( 1 ) = 5;
	v12( 2 ) = 3;
	Point<TypeParam> p12 = Point<TypeParam>( v12 );
	vector_t<TypeParam> v13 = vector_t<TypeParam>( 3 );
	v13( 0 ) = 5;
	v13( 1 ) = 3;
	v13( 2 ) = 3;
	Point<TypeParam> p13 = Point<TypeParam>( v13 );
	vector_t<TypeParam> v14 = vector_t<TypeParam>( 3 );
	v14( 0 ) = 5;
	v14( 1 ) = 5;
	v14( 2 ) = 3;
	Point<TypeParam> p14 = Point<TypeParam>( v14 );

	ps4.push_back( p04 );
	ps4.push_back( p08 );
	ps4.push_back( p09 );
	ps4.push_back( p10 );
	ps4.push_back( p11 );
	ps4.push_back( p12 );
	ps4.push_back( p13 );
	ps4.push_back( p14 );

	hypro::Polytope<TypeParam> pt4 = Polytope<TypeParam>( ps4 );

	hypro::Polytope<TypeParam> res2 = pt3.unite( pt4 );

	// res2 = res2.hull();

	/* for(auto& vertex : pt3.vertices()) {
		 EXPECT_TRUE(res2.contains(vertex));
	 }

	 for(auto& vertex : pt4.vertices()) {
		 EXPECT_TRUE(res2.contains(vertex));
	 }*/

	// EXPECT_TRUE(res2.contains(pt3));
	// EXPECT_TRUE(res2.contains(pt4));

	hypro::Polytope<TypeParam> res3 = res2.unite( Polytope<TypeParam>() );
	// res3 = res3.hull();

	for ( auto& vertex : res3.vertices() ) {
		EXPECT_TRUE( res2.contains( vertex ) );
	}

	for ( auto& vertex : res2.vertices() ) {
		EXPECT_TRUE( res3.contains( vertex ) );
	}
}

TYPED_TEST( PolytopeTest, LinearTransformation ) {
	Point<TypeParam> pt1;
	Point<TypeParam> pt2;
	Point<TypeParam> pt3;
	Point<TypeParam> pt4;

	pt1 = Point<TypeParam>( { TypeParam( 0 ), TypeParam( 0 ) } );
	pt2 = Point<TypeParam>( { TypeParam( 0 ), TypeParam( 4 ) } );
	pt3 = Point<TypeParam>( { TypeParam( 4 ), TypeParam( 4 ) } );
	pt4 = Point<TypeParam>( { TypeParam( 4 ), TypeParam( 0 ) } );

	std::vector<Point<TypeParam>> ps1;
	ps1.push_back( pt1 );
	ps1.push_back( pt2 );
	ps1.push_back( pt3 );
	ps1.push_back( pt4 );
	hypro::Polytope<TypeParam> poly1;
	poly1 = Polytope<TypeParam>( ps1 );
	EXPECT_FALSE( poly1.rawPolyhedron().is_universe() );
	EXPECT_TRUE( poly1.rawPolyhedron().is_topologically_closed() );

	matrix_t<TypeParam> A = matrix_t<TypeParam>( 2, 2 );
	// vector b = vector(2,1);

	A( 0, 0 ) = TypeParam( 0 );
	A( 1, 0 ) = TypeParam( 1 );
	A( 0, 1 ) = TypeParam( -1 );
	A( 1, 1 ) = TypeParam( 0 );
	// b(0,0) = TypeParam(0);
	// b(1,0) = TypeParam(0);

	hypro::Polytope<TypeParam> result;
	result = poly1.affineTransformation( A, vector_t<TypeParam>::Zero( A.rows() ) );  // what kind of result is
																					  // expected?
																					  //    result.print();
}

TYPED_TEST( PolytopeTest, MinkowskiSum ) {
	std::vector<Point<TypeParam>> ps1;
	ps1.push_back( this->p1 );
	ps1.push_back( this->p2 );
	ps1.push_back( this->p3 );
	ps1.push_back( this->p4 );
	hypro::Polytope<TypeParam> ptpe1 = Polytope<TypeParam>( ps1 );

	std::vector<Point<TypeParam>> ps2;
	ps2.push_back( this->p5 );
	ps2.push_back( this->p6 );
	ps2.push_back( this->p7 );
	hypro::Polytope<TypeParam> ptpe2 = Polytope<TypeParam>( ps2 );

	hypro::Polytope<TypeParam> result;
	result = ptpe1.minkowskiSum( ptpe2 );

	//    result.print();

	this->p1 = Point<TypeParam>( { TypeParam( 9 ), TypeParam( 12 ) } );
	this->p2 = Point<TypeParam>( { TypeParam( 11 ), TypeParam( 12 ) } );
	this->p3 = Point<TypeParam>( { TypeParam( 8 ), TypeParam( 10 ) } );
	this->p4 = Point<TypeParam>( { TypeParam( 10 ), TypeParam( 12 ) } );
	this->p5 = Point<TypeParam>( { TypeParam( 7 ), TypeParam( 7 ) } );
	this->p6 = Point<TypeParam>( { TypeParam( 13 ), TypeParam( 7 ) } );
	this->p7 = Point<TypeParam>( { TypeParam( 13 ), TypeParam( 8 ) } );

	EXPECT_TRUE( result.contains( this->p1 ) );
	EXPECT_TRUE( result.contains( this->p2 ) );
	EXPECT_TRUE( result.contains( this->p3 ) );
	EXPECT_TRUE( result.contains( this->p4 ) );
	EXPECT_TRUE( result.contains( this->p5 ) );
	EXPECT_TRUE( result.contains( this->p6 ) );

	EXPECT_FALSE( result.contains( this->p7 ) );
	// EXPECT_FALSE(result.contains(p8));
}

/*
TYPED_TEST(PolytopeTest, Neighborhood)
{
	vector_t<TypeParam> v01 = vector_t<TypeParam>(3);
	v01(0) = 0;
	v01(1) = 0;
	v01(2) = 0;
	Point<TypeParam> p01 = Point<TypeParam>(v01);

	vector_t<TypeParam> v02 = vector_t<TypeParam>(3);
	v02(0) = 0;
	v02(1) = 2;
	v02(2) = 0;
	Point<TypeParam> p02 = Point<TypeParam>(v02);

	vector_t<TypeParam> v03 = vector_t<TypeParam>(3);
	v03(0) = 2;
	v03(1) = 0;
	v03(2) = 0;
	Point<TypeParam> p03 = Point<TypeParam>(v03);

	vector_t<TypeParam> v04 = vector_t<TypeParam>(3);
	v04(0) = 0;
	v04(1) = 0;
	v04(2) = 2;
	Point<TypeParam> p04= Point<TypeParam>(v04);

	vector_t<TypeParam> v05 = vector_t<TypeParam>(3);
	v04(0) = 0.5;
	v04(1) = 0.5;
	v04(2) = 0.5;
	Point<TypeParam> p05= Point<TypeParam>(v05);

	std::vector<Point<TypeParam>> ps3;
	ps3.push_back(p01);
	ps3.push_back(p02);
	ps3.push_back(p03);
	ps3.push_back(p04);
	ps3.push_back(p05);

	hypro::Polytope<TypeParam> pt3 = Polytope<TypeParam>(ps3);

	hypro::Polytope<TypeParam> result;
	result = pt3.hull();

	std::vector<Point<TypeParam>> ps = result.vertices();

	for(unsigned i = 0; i<ps.size(); i++) {
		if(ps.at(i) == p01){
			EXPECT_TRUE(ps.at(i).isNeighbor(p02));
			EXPECT_TRUE(ps.at(i).isNeighbor(p03));
			EXPECT_TRUE(ps.at(i).isNeighbor(p04));
			EXPECT_FALSE(ps.at(i).isNeighbor(p05));
		}
		else if(ps.at(i) == p02){
			EXPECT_TRUE(ps.at(i).isNeighbor(p01));
			EXPECT_TRUE(ps.at(i).isNeighbor(p03));
			EXPECT_TRUE(ps.at(i).isNeighbor(p04));
			EXPECT_FALSE(ps.at(i).isNeighbor(p05));
		}
		else if(ps.at(i) == p03){
			EXPECT_TRUE(ps.at(i).isNeighbor(p01));
			EXPECT_TRUE(ps.at(i).isNeighbor(p02));
			EXPECT_TRUE(ps.at(i).isNeighbor(p04));
			EXPECT_FALSE(ps.at(i).isNeighbor(p05));
				}
		else if(ps.at(i) == p04){
			EXPECT_TRUE(ps.at(i).isNeighbor(p01));
			EXPECT_TRUE(ps.at(i).isNeighbor(p02));
			EXPECT_TRUE(ps.at(i).isNeighbor(p03));
			EXPECT_FALSE(ps.at(i).isNeighbor(p05));
		}
	}
}*/

TYPED_TEST( PolytopeTest, Membership ) {
	vector_t<TypeParam> v01 = vector_t<TypeParam>( 2 );
	v01( 0 ) = 4;
	v01( 1 ) = 4;
	Point<TypeParam> p01 = Point<TypeParam>( v01 );

	vector_t<TypeParam> v02 = vector_t<TypeParam>( 2 );
	v02( 0 ) = 5;
	v02( 1 ) = 6;
	Point<TypeParam> p02 = Point<TypeParam>( v02 );

	vector_t<TypeParam> v03 = vector_t<TypeParam>( 2 );
	v03( 0 ) = 6;
	v03( 1 ) = 4;
	Point<TypeParam> p03 = Point<TypeParam>( v03 );

	vector_t<TypeParam> v04 = vector_t<TypeParam>( 2 );
	v04( 0 ) = 10;
	v04( 1 ) = 0;
	Point<TypeParam> p04 = Point<TypeParam>( v04 );

	std::vector<Point<TypeParam>> v1;
	v1.push_back( p01 );
	v1.push_back( p02 );
	v1.push_back( p03 );

	Polytope<TypeParam> ptpe1 = Polytope<TypeParam>( v1 );

	Polytope<TypeParam> pt2 = Polytope<TypeParam>( v1 );

	EXPECT_TRUE( ptpe1.contains( pt2 ) );

	v1.push_back( p04 );

	Polytope<TypeParam> pt3 = Polytope<TypeParam>( v1 );

	EXPECT_FALSE( ptpe1.contains( pt3 ) );
}
