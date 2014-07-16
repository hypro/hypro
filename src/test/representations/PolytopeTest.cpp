/**
 * Test for the wrapper of the PPL Polytope.
 * @file PolytopeTest.cpp
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 * 
 * @since       2014-04-02
 * @version     2014-04-08
 */

#include "gtest/gtest.h"
#include "../defines.h"

#include "../../lib/representations/Polytope/Polytope.h"

using namespace hypro;
using namespace carl;

class PolytopeTest : public ::testing::Test
{
protected:
    virtual void SetUp()
    {
        // p1
        Point<number_t>::coordinateMap coordinates1;
        coordinates1.insert( std::make_pair(x, FLOAT_T<number_t>(4.34)) );
        coordinates1.insert( std::make_pair(y, FLOAT_T<number_t>(4)) );
        p1 = Point<number_t>(coordinates1);

        // p2
        Point<number_t>::coordinateMap coordinates2;
        coordinates2.insert( std::make_pair(x, FLOAT_T<number_t>(5)) );
        coordinates2.insert( std::make_pair(y, FLOAT_T<number_t>(7)) );
        p2 = Point<number_t>(coordinates2);

        // p3
        Point<number_t>::coordinateMap coordinates3;
        coordinates3.insert( std::make_pair(x, FLOAT_T<number_t>(7)) );
        coordinates3.insert( std::make_pair(y, FLOAT_T<number_t>(7)) );
        p3 = Point<number_t>(coordinates3);
        
        // p4
        Point<number_t>::coordinateMap coordinates4;
        coordinates4.insert( std::make_pair(x, FLOAT_T<number_t>(8)) );
        coordinates4.insert( std::make_pair(y, FLOAT_T<number_t>(4)) );
        p4 = Point<number_t>(coordinates4);
        
        // p5
        Point<number_t>::coordinateMap coordinates5;
        coordinates5.insert( std::make_pair(x, FLOAT_T<number_t>(3)) );
        coordinates5.insert( std::make_pair(y, FLOAT_T<number_t>(3)) );
        p5 = Point<number_t>(coordinates5);
        
        // p6
        Point<number_t>::coordinateMap coordinates6;
        coordinates6.insert( std::make_pair(x, FLOAT_T<number_t>(4)) );
        coordinates6.insert( std::make_pair(y, FLOAT_T<number_t>(5)) );
        p6 = Point<number_t>(coordinates6);
        
        // p7
        Point<number_t>::coordinateMap coordinates7;
        coordinates7.insert( std::make_pair(x, FLOAT_T<number_t>(5)) );
        coordinates7.insert( std::make_pair(y, FLOAT_T<number_t>(3)) );
        p7 = Point<number_t>(coordinates7);
    }

    virtual void TearDown()
    {
        hypro::VariablePool::getInstance().clear();
    }
	
    carl::VariablePool& pool = carl::VariablePool::getInstance();
    carl::Variable x = pool.getFreshVariable("x");
    carl::Variable y = pool.getFreshVariable("y");
	
    Point<number_t> p1;
    Point<number_t> p2;
    Point<number_t> p3;
    Point<number_t> p4;
    Point<number_t> p5;
    Point<number_t> p6;
    Point<number_t> p7;
};

/**
 * @covers polytope::constructor
 * @covers polytope::pointToGenerator
 */
TEST_F(PolytopeTest, Constructor)
{
    hypro::Polytope<number_t> p0;
    
    Point<number_t>::pointSet ps;
    ps.insert(p1);
    ps.insert(p2);
    ps.insert(p3);
    ps.insert(p4);
    hypro::Polytope<number_t> p1 = Polytope<number_t>(ps);
    std::cout << "P1" << std::endl;
    p1.print();
    EXPECT_EQ(p1.dimension(), 2);
    EXPECT_FALSE(p1.rawPolyhedron().is_empty());
    hypro::Polytope<number_t> p3 = Polytope<number_t>(ps);
    
    hypro::Polytope<number_t> p2 = Polytope<number_t>(2);
    EXPECT_EQ(p2.dimension(), 2);
    
    Eigen::Matrix<FLOAT_T<number_t>, Eigen::Dynamic, Eigen::Dynamic> A = Eigen::Matrix<FLOAT_T<number_t>, Eigen::Dynamic, Eigen::Dynamic>(2,2);
    A(0,0) = 1;
    A(0,1) = 2;
    A(1,0) = 1;
    A(1,1) = 3;
    
    Eigen::Matrix<FLOAT_T<number_t>, Eigen::Dynamic, 1> b = Eigen::Matrix<FLOAT_T<number_t>, Eigen::Dynamic, 1>(2,1);
    b(0,0) = 4;
    b(1,0) = 5;
    
    hypro::VariablePool::getInstance().print();
    
    hypro::Polytope<number_t> p4 = Polytope<number_t>(A,b);
    
    p4.print();
    
    EXPECT_EQ(p4.dimension(), 2);
    
    SUCCEED();
}

TEST_F(PolytopeTest, Access)
{
    Point<number_t>::pointSet ps1;
    ps1.insert(p1);
    ps1.insert(p2);
    ps1.insert(p3);
    ps1.insert(p4);
    hypro::Polytope<number_t> p1 = Polytope<number_t>(ps1);
    EXPECT_EQ(p1.dimension(), 2);
    
    carl::Variable a = pool.getFreshVariable("a");
    carl::Variable b = pool.getFreshVariable("b");
    Point<number_t>::pointSet ps2;
    Point<number_t>::coordinateMap coordinates;
    coordinates.insert( std::make_pair(a, FLOAT_T<number_t>(7)) );
    coordinates.insert( std::make_pair(b, FLOAT_T<number_t>(8)) );
    Point<number_t> p5 = Point<number_t>(coordinates);
    coordinates.clear();
    coordinates.insert( std::make_pair(a, FLOAT_T<number_t>(1)) );
    coordinates.insert( std::make_pair(b, FLOAT_T<number_t>(2)) );
    Point<number_t> p6 = Point<number_t>(coordinates);
    coordinates.clear();
    coordinates.insert( std::make_pair(a, FLOAT_T<number_t>(4)) );
    coordinates.insert( std::make_pair(b, FLOAT_T<number_t>(3)) );
    Point<number_t> p7 = Point<number_t>(coordinates);
    ps2.insert(p5);
    ps2.insert(p6);
    ps2.insert(p7);
    
    std::cout << "---" << std::endl;
    hypro::VariablePool::getInstance().print();
    
    hypro::Polytope<number_t> p2 = Polytope<number_t>(ps2);
    
    std::cout << "---" << std::endl;
    hypro::VariablePool::getInstance().print();

    EXPECT_EQ(p2.dimension(), 2);
    
    hypro::Point<number_t>::pointSet points = p2.points();
}

TEST_F(PolytopeTest, PointToGenerator)
{
    Generator gs = polytope::pointToGenerator(p1);
    std::cout << "Generator: ";
    gs.print();
    std::cout << std::endl;
    gs = polytope::pointToGenerator(p2);
    std::cout << "Generator: ";
    gs.print();
    std::cout << std::endl;
    gs = polytope::pointToGenerator(p3);
    std::cout << "Generator: ";
    gs.print();
    std::cout << std::endl;
    gs = polytope::pointToGenerator(p4);
    std::cout << "Generator: ";
    gs.print();
    std::cout << std::endl;
    
    SUCCEED();
}

TEST_F(PolytopeTest, Intersection)
{
    Point<number_t>::pointSet ps1;
    ps1.insert(p1);
    ps1.insert(p2);
    ps1.insert(p3);
    ps1.insert(p4);
    hypro::Polytope<number_t> pt1;
    pt1.print();
    pt1 = Polytope<number_t>(ps1);
    pt1.print();
    EXPECT_FALSE(pt1.rawPolyhedron().is_universe());
    EXPECT_TRUE(pt1.rawPolyhedron().is_topologically_closed());
    
    Point<number_t>::pointSet ps2;
    ps2.insert(p5);
    ps2.insert(p6);
    ps2.insert(p7);
    hypro::Polytope<number_t> pt2 = Polytope<number_t>(ps2);
    pt2.print();
    
    hypro::Polytope<number_t> res;
    pt1.intersect(res, pt2);
    res.print();
    res.hull(res);
    res.print();
}

TEST_F(PolytopeTest, Union)
{
    Point<number_t>::pointSet ps1;
    ps1.insert(p1);
    ps1.insert(p2);
    ps1.insert(p3);
    ps1.insert(p4);
    hypro::Polytope<number_t> pt1;
    pt1 = Polytope<number_t>(ps1);
    EXPECT_FALSE(pt1.rawPolyhedron().is_universe());
    EXPECT_TRUE(pt1.rawPolyhedron().is_topologically_closed());
    
    Point<number_t>::pointSet ps2;
    ps2.insert(p5);
    ps2.insert(p6);
    ps2.insert(p7);
    hypro::Polytope<number_t> pt2 = Polytope<number_t>(ps2);
    
    hypro::Polytope<number_t> res;
    pt1.unite(res, pt2);
    res.hull(res);
}

TEST_F(PolytopeTest, LinearTransformation)
{
    Point<number_t> pt1;
    Point<number_t> pt2;
    Point<number_t> pt3;
    Point<number_t> pt4;
    
    Point<number_t>::coordinateMap c1;
    c1.insert( std::make_pair(x, FLOAT_T<number_t>(0)) );
    c1.insert( std::make_pair(y, FLOAT_T<number_t>(0)) );
    pt1 = Point<number_t>(c1);
    Point<number_t>::coordinateMap c2;
    c2.insert( std::make_pair(x, FLOAT_T<number_t>(0)) );
    c2.insert( std::make_pair(y, FLOAT_T<number_t>(4)) );
    pt2 = Point<number_t>(c2);
    Point<number_t>::coordinateMap c3;
    c3.insert( std::make_pair(x, FLOAT_T<number_t>(4)) );
    c3.insert( std::make_pair(y, FLOAT_T<number_t>(4)) );
    pt3 = Point<number_t>(c3);
    Point<number_t>::coordinateMap c4;
    c4.insert( std::make_pair(x, FLOAT_T<number_t>(4)) );
    c4.insert( std::make_pair(y, FLOAT_T<number_t>(0)) );
    pt4 = Point<number_t>(c4);
    
    Point<number_t>::pointSet ps1;
    ps1.insert(pt1);
    ps1.insert(pt2);
    ps1.insert(pt3);
    ps1.insert(pt4);
    hypro::Polytope<number_t> poly1;
    poly1 = Polytope<number_t>(ps1);
    EXPECT_FALSE(poly1.rawPolyhedron().is_universe());
    EXPECT_TRUE(poly1.rawPolyhedron().is_topologically_closed());
    
    matrix A = matrix(2,2);
    //vector b = vector(2,1);
    
    A(0,0) = FLOAT_T<number_t>(0);
    A(1,0) = FLOAT_T<number_t>(1);
    A(0,1) = FLOAT_T<number_t>(-1);
    A(1,1) = FLOAT_T<number_t>(0);
    //b(0,0) = FLOAT_T<number_t>(0);
    //b(1,0) = FLOAT_T<number_t>(0);
    
    hypro::Polytope<number_t> result;
    poly1.linearTransformation(result,A);
    result.print();
}

TEST_F(PolytopeTest, MinkowskiSum)
{
    Point<number_t>::pointSet ps1;
    ps1.insert(p1);
    ps1.insert(p2);
    ps1.insert(p3);
    ps1.insert(p4);
    hypro::Polytope<number_t> ptpe1 = Polytope<number_t>(ps1);
    
    Point<number_t>::pointSet ps2;
    ps2.insert(p5);
    ps2.insert(p6);
    ps2.insert(p7);
    hypro::Polytope<number_t> ptpe2 = Polytope<number_t>(ps2);
    
    hypro::Polytope<number_t> result;
    ptpe1.minkowskiSum(result,ptpe2);
    
    result.print();
    
    Point<number_t>::coordinateMap c1;
    c1.insert( std::make_pair(x, FLOAT_T<number_t>(9)) );
    c1.insert( std::make_pair(y, FLOAT_T<number_t>(12)) );
    p1 = Point<number_t>(c1);
    
    Point<number_t>::coordinateMap c2;
    c2.insert( std::make_pair(x, FLOAT_T<number_t>(11)) );
    c2.insert( std::make_pair(y, FLOAT_T<number_t>(12)) );
    p2 = Point<number_t>(c2);
    
    Point<number_t>::coordinateMap c3;
    c3.insert( std::make_pair(x, FLOAT_T<number_t>(8)) );
    c3.insert( std::make_pair(y, FLOAT_T<number_t>(10)) );
    p3 = Point<number_t>(c3);
    
    Point<number_t>::coordinateMap c4;
    c4.insert( std::make_pair(x, FLOAT_T<number_t>(12)) );
    c4.insert( std::make_pair(y, FLOAT_T<number_t>(10)) );
    p4 = Point<number_t>(c4);
    
    Point<number_t>::coordinateMap c5;
    c5.insert( std::make_pair(x, FLOAT_T<number_t>(7)) );
    c5.insert( std::make_pair(y, FLOAT_T<number_t>(7)) );
    p5 = Point<number_t>(c5);
    
    Point<number_t>::coordinateMap c6;
    c6.insert( std::make_pair(x, FLOAT_T<number_t>(13)) );
    c6.insert( std::make_pair(y, FLOAT_T<number_t>(7)) );
    p6 = Point<number_t>(c6);
    
    Point<number_t>::coordinateMap c7;
    c7.insert( std::make_pair(x, FLOAT_T<number_t>(13)) );
    c7.insert( std::make_pair(y, FLOAT_T<number_t>(8)) );
    p7 = Point<number_t>(c7);
    
    EXPECT_TRUE(result.contains(p1));
    EXPECT_TRUE(result.contains(p2));
    EXPECT_TRUE(result.contains(p3));
    EXPECT_TRUE(result.contains(p4));
    EXPECT_TRUE(result.contains(p5));
    EXPECT_TRUE(result.contains(p6));
    
    EXPECT_FALSE(result.contains(p7));
    //EXPECT_FALSE(result.contains(p8));
}

TEST_F(PolytopeTest, ConvexHull)
{
    
}

TEST_F(PolytopeTest, Membership)
{
    
}