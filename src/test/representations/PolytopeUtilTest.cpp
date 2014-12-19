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
        Point<number>::coordinateMap coordinates1;
        coordinates1.insert( std::make_pair(x, carl::FLOAT_T<number_t>(4.34)) );
        coordinates1.insert( std::make_pair(y, carl::FLOAT_T<number_t>(4)) );
        p1 = Point<number>(coordinates1);

        // p2
        Point<number>::coordinateMap coordinates2;
        coordinates2.insert( std::make_pair(x, carl::FLOAT_T<number_t>(5)) );
        coordinates2.insert( std::make_pair(y, carl::FLOAT_T<number_t>(7)) );
        p2 = Point<number>(coordinates2);

        // p3
        Point<number>::coordinateMap coordinates3;
        coordinates3.insert( std::make_pair(x, carl::FLOAT_T<number_t>(7)) );
        coordinates3.insert( std::make_pair(y, carl::FLOAT_T<number_t>(7)) );
        p3 = Point<number>(coordinates3);
        
        // p4
        Point<number>::coordinateMap coordinates4;
        coordinates4.insert( std::make_pair(x, carl::FLOAT_T<number_t>(8)) );
        coordinates4.insert( std::make_pair(y, carl::FLOAT_T<number_t>(4)) );
        p4 = Point<number>(coordinates4);
        
        // p5
        Point<number>::coordinateMap coordinates5;
        coordinates5.insert( std::make_pair(x, carl::FLOAT_T<number_t>(3)) );
        coordinates5.insert( std::make_pair(y, carl::FLOAT_T<number_t>(3)) );
        p5 = Point<number>(coordinates5);
        
        // p6
        Point<number>::coordinateMap coordinates6;
        coordinates6.insert( std::make_pair(x, carl::FLOAT_T<number_t>(4)) );
        coordinates6.insert( std::make_pair(y, carl::FLOAT_T<number_t>(5)) );
        p6 = Point<number>(coordinates6);
        
        // p7
        Point<number>::coordinateMap coordinates7;
        coordinates7.insert( std::make_pair(x, carl::FLOAT_T<number_t>(5)) );
        coordinates7.insert( std::make_pair(y, carl::FLOAT_T<number_t>(3)) );
        p7 = Point<number>(coordinates7);
    }

    virtual void TearDown()
    {
        hypro::VariablePool::getInstance().clear();
    }
	
    carl::VariablePool& pool = carl::VariablePool::getInstance();
    carl::Variable x = pool.getFreshVariable("x");
    carl::Variable y = pool.getFreshVariable("y");
	
    Point<number> p1;
    Point<number> p2;
    Point<number> p3;
    Point<number> p4;
    Point<number> p5;
    Point<number> p6;
    Point<number> p7;
};

/**
 * @covers polytope::constructor
 * @covers polytope::pointToGenerator
 */
TEST_F(PolytopeUtilTest, HyperplaneConstructor)
{
    Hyperplane<number> constructor1;
    
    vector_t<number> norm = vector_t<number>(2);
    norm(0) = 1;
    norm(1) = 3;
    
    Hyperplane<number> constructor2(norm, 4.3);
    
    Hyperplane<number> constructor3({1,3}, 4.3);
    
    Hyperplane<number> constructor4(constructor1);
    SUCCEED();
}

TEST_F(PolytopeUtilTest, HyperplaneAccess)
{
    vector_t<number> norm = vector_t<number>(2);
    norm(0) = 1;
    norm(1) = 3;
    Hyperplane<number> access1(norm, 4.3);
    
    EXPECT_EQ(norm, access1.normal());
    EXPECT_EQ(4.3, access1.offset());
    EXPECT_EQ((unsigned) 2, access1.dimension());
}

TEST_F(PolytopeUtilTest, HyperplaneIntersection)
{
    Point<number> norm(x,1);
    norm.setCoordinate(y,3);
    Hyperplane<number> intersection1(norm, 4.3);
    
    vector_t<number> vec = vector_t<number>(2);
    vec(0) = 2;
    vec(1) = 2;
    
    number result = 0.0;
    intersection1.intersection(result, vec);
    
    std::cout << "Result: " << result << std::endl;
    
    EXPECT_EQ(1.075, vec(0)*result);
    EXPECT_EQ(1.075, vec(1)*result);
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