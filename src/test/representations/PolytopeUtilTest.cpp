/**
 * Test for the utility functions for polytopes.
 * @file PolytopeUtilTest.cpp
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 * 
 * @since       2014-08-22
 * @version     2014-08-22
 */

#include "gtest/gtest.h"
#include "../defines.h"

#include "../../lib/util/VariablePool.h"
#include "../../lib/representations/Polytopes/util.h"

using namespace hypro;
using namespace hypro::polytope;

class PolytopeUtilTest : public ::testing::Test
{
protected:
    virtual void SetUp()
    {
        // p1
        Point<number_t>::coordinateMap coordinates1;
        coordinates1.insert( std::make_pair(x, carl::FLOAT_T<number_t>(4.34)) );
        coordinates1.insert( std::make_pair(y, carl::FLOAT_T<number_t>(4)) );
        p1 = Point<number_t>(coordinates1);

        // p2
        Point<number_t>::coordinateMap coordinates2;
        coordinates2.insert( std::make_pair(x, carl::FLOAT_T<number_t>(5)) );
        coordinates2.insert( std::make_pair(y, carl::FLOAT_T<number_t>(7)) );
        p2 = Point<number_t>(coordinates2);

        // p3
        Point<number_t>::coordinateMap coordinates3;
        coordinates3.insert( std::make_pair(x, carl::FLOAT_T<number_t>(7)) );
        coordinates3.insert( std::make_pair(y, carl::FLOAT_T<number_t>(7)) );
        p3 = Point<number_t>(coordinates3);
        
        // p4
        Point<number_t>::coordinateMap coordinates4;
        coordinates4.insert( std::make_pair(x, carl::FLOAT_T<number_t>(8)) );
        coordinates4.insert( std::make_pair(y, carl::FLOAT_T<number_t>(4)) );
        p4 = Point<number_t>(coordinates4);
        
        // p5
        Point<number_t>::coordinateMap coordinates5;
        coordinates5.insert( std::make_pair(x, carl::FLOAT_T<number_t>(3)) );
        coordinates5.insert( std::make_pair(y, carl::FLOAT_T<number_t>(3)) );
        p5 = Point<number_t>(coordinates5);
        
        // p6
        Point<number_t>::coordinateMap coordinates6;
        coordinates6.insert( std::make_pair(x, carl::FLOAT_T<number_t>(4)) );
        coordinates6.insert( std::make_pair(y, carl::FLOAT_T<number_t>(5)) );
        p6 = Point<number_t>(coordinates6);
        
        // p7
        Point<number_t>::coordinateMap coordinates7;
        coordinates7.insert( std::make_pair(x, carl::FLOAT_T<number_t>(5)) );
        coordinates7.insert( std::make_pair(y, carl::FLOAT_T<number_t>(3)) );
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
TEST_F(PolytopeUtilTest, HyperplaneConstructor)
{
    Hyperplane<number_t> constructor1;
    
    Point<number_t> norm(x,1);
    norm.setCoordinate(y,3);
    
    Hyperplane<number_t> constructor2(norm, 4.3);
    Hyperplane<number_t> constructor3(constructor1);
    SUCCEED();
}

TEST_F(PolytopeUtilTest, HyperplaneAccess)
{
    Point<number_t> norm(x,1);
    norm.setCoordinate(y,3);
    Hyperplane<number_t> access1(norm, 4.3);
    
    EXPECT_EQ(norm, access1.normal());
    EXPECT_EQ(4.3, access1.offset());
    EXPECT_EQ(2, access1.dimension());
}

TEST_F(PolytopeUtilTest, HyperplaneIntersection)
{
    Point<number_t> norm(x,1);
    norm.setCoordinate(y,3);
    Hyperplane<number_t> intersection1(norm, 4.3);
    
    Point<number_t> vector(x,2);
    vector.setCoordinate(y,2);
    
    Point<number_t> result = intersection1.intersection(vector);
    
    EXPECT_EQ(1.075, result.at(x));
    EXPECT_EQ(1.075, result.at(y));
}

TEST_F(PolytopeUtilTest, ConeConstructor)
{
    SUCCEED();
}

TEST_F(PolytopeUtilTest, ConeAccess)
{
    
}

TEST_F(PolytopeUtilTest, ConeContains)
{
    
}

TEST_F(PolytopeUtilTest, FanConstructor)
{
    SUCCEED();
}

TEST_F(PolytopeUtilTest, FanAccess)
{
    
}

TEST_F(PolytopeUtilTest, FanContainingCone)
{
    
}