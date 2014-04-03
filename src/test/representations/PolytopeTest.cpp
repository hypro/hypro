/**
 * Test for the wrapper of the PPL Polytope.
 * @file PolytopeTest.cpp
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 * 
 * @since       2014-04-02
 * @version     2014-04-03
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
        Point<number_t>::vector_t coordinates1;
		//VariablePool& pool = VariablePool::getInstance();
		//Variable x = pool.getFreshVariable("x");
		//Variable y = pool.getFreshVariable("y");
        coordinates1.insert( std::make_pair(x, FLOAT_T<number_t>(2)) );
        coordinates1.insert( std::make_pair(y, FLOAT_T<number_t>(5)) );
        p1 = Point<number_t>(coordinates1);

        // p2
        Point<number_t>::vector_t coordinates2;
        coordinates2.insert( std::make_pair(x, FLOAT_T<number_t>(7)) );
        coordinates2.insert( std::make_pair(y, FLOAT_T<number_t>(8)) );
        p2 = Point<number_t>(coordinates2);

        // p3
        Point<number_t>::vector_t coordinates3;
        coordinates3.insert( std::make_pair(x, FLOAT_T<number_t>(9)) );
        coordinates3.insert( std::make_pair(y, FLOAT_T<number_t>(-13)) );
        p3 = Point<number_t>(coordinates3);
        
        // p4
        Point<number_t>::vector_t coordinates4;
        coordinates4.insert( std::make_pair(x, FLOAT_T<number_t>(5)) );
        coordinates4.insert( std::make_pair(y, FLOAT_T<number_t>(8)) );
        p4 = Point<number_t>(coordinates4);
    }

    virtual void TearDown()
    {
    }
	
    carl::VariablePool& pool = VariablePool::getInstance();
    carl::Variable x = pool.getFreshVariable("x");
    carl::Variable y = pool.getFreshVariable("y");
	
    Point<number_t> p1;
    Point<number_t> p2;
    Point<number_t> p3;
    Point<number_t> p4;
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
    EXPECT_EQ(p1.dimension(), 2);
    EXPECT_FALSE(p1.rawPolyhedron().is_empty());
    p1.rawPolyhedron().print();
    
    hypro::Polytope<number_t> p2 = Polytope<number_t>(2);
    EXPECT_EQ(p2.dimension(), 2);
    
    SUCCEED();
}

TEST_F(PolytopeTest, Access)
{
    Point<number_t>::pointSet ps;
    ps.insert(p1);
    ps.insert(p2);
    ps.insert(p3);
    ps.insert(p4);
    hypro::Polytope<number_t> p1 = Polytope<number_t>(ps);
    EXPECT_EQ(p1.dimension(), 2);
    
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
    
}

TEST_F(PolytopeTest, Union)
{
    
}

TEST_F(PolytopeTest, LinearTransformation)
{
    
}

TEST_F(PolytopeTest, MinkowskiSum)
{
    
}

TEST_F(PolytopeTest, ConvexHull)
{
    
}

TEST_F(PolytopeTest, Membership)
{
    
}