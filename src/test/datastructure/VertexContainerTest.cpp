/**
 * @file VertexContainerTest.cpp
 * 
 * @covers VertexContainer
 * 
 * @author Stefan Schupp
 * @author Benedikt Seidl
 */


#include "gtest/gtest.h"
#include "../defines.h"
#include "../../lib/datastructures/VertexContainer.h"
#include <carl/core/VariablePool.h>
#include <cstdio>

using namespace hypro;
using namespace carl;

class VertexContainerTest : public ::testing::Test
{
protected:
    virtual void SetUp()
    {
        
        // p1
        Point<number_t>::coordinateMap coordinates1;
        coordinates1.insert( std::make_pair(x, FLOAT_T<number_t>(2)) );
        coordinates1.insert( std::make_pair(y, FLOAT_T<number_t>(5)) );
        p1 = Point<number_t>(coordinates1);
		
        // p2
        Point<number_t>::coordinateMap coordinates2;
        coordinates2.insert( std::make_pair(x, FLOAT_T<number_t>(7)) );
        coordinates2.insert( std::make_pair(y, FLOAT_T<number_t>(8)) );
        p2 = Point<number_t>(coordinates2);
		
        // p3
        Point<number_t>::coordinateMap coordinates3;
        coordinates3.insert( std::make_pair(x, FLOAT_T<number_t>(-9)) );
        coordinates3.insert( std::make_pair(y, FLOAT_T<number_t>(13)) );
        p3 = Point<number_t>(coordinates3);
    }
	
    virtual void TearDown()
    {
    }
    
    VariablePool& pool = VariablePool::getInstance();
    Variable x = pool.getFreshVariable("x");
    Variable y = pool.getFreshVariable("y");
	
    Point<number_t> p1;
    Point<number_t> p2;
    Point<number_t> p3;
};

TEST_F(VertexContainerTest, Constructor)
{
	VertexContainer<number_t> test1;
	SUCCEED();
}

TEST_F(VertexContainerTest, Insertion)
{
	VertexContainer<number_t> test1 = VertexContainer<number_t>();
	std::cout << (test1.insert(Vertex<number_t>(p1, true))).second << std::endl;
        std::cout << test1.size() << std::endl; 
        std::cout << (test1.insert(Vertex<number_t>(p2, true))).second << std::endl;
        std::cout << test1.size() << std::endl; 
	std::cout << (test1.insert(Vertex<number_t>(p3, false))).second << std::endl;
        std::cout << test1.size() << std::endl; 
        std::cout << test1 << std::endl;
        
        std::cout << "ITEM: " << *test1.find(p3) << std::endl;
        
        std::cout << "Manual comparison: p1 < p3: " << ( Vertex<number_t>(p1, true) < Vertex<number_t>(p3, false) ) << ", p1 > p3: " << ( Vertex<number_t>(p3, false) < Vertex<number_t>(p1, true) ) << std::endl;
        std::cout << "Manual comparison: p1 == p3: " << ( Vertex<number_t>(p1, true) == Vertex<number_t>(p3, false) ) << std::endl;
        
	EXPECT_EQ(3, test1.size());
        EXPECT_EQ(2, test1.dimension());
	EXPECT_FALSE(test1.find(p1) != test1.end());
	EXPECT_FALSE(test1.find(p2) != test1.end());
	EXPECT_TRUE(test1.find(p3) != test1.end());
}

TEST_F(VertexContainerTest, Deletion)
{
	VertexContainer<number_t> test1 = VertexContainer<number_t>();
	test1.insert(Vertex<number_t>(p1, true));
	test1.insert(Vertex<number_t>(p2, true));
	test1.insert(Vertex<number_t>(p3, false));
	EXPECT_EQ(test1.size(), 3);
	test1.erase(p2);
	EXPECT_EQ(test1.size(), 2);
	EXPECT_EQ(test1.find(p2) != test1.end(), false);
}

TEST_F(VertexContainerTest, Destructor)
{
	VertexContainer<number_t> test1 = VertexContainer<number_t>();
	test1.insert(Vertex<number_t>(p1, true));
	test1.insert(Vertex<number_t>(p2, true));
	test1.insert(Vertex<number_t>(p3, false));
	SUCCEED();
}

TEST_F(VertexContainerTest, Assignment)
{
	VertexContainer<number_t> test1 = VertexContainer<number_t>();
	test1.insert(Vertex<number_t>(p1, true));
	test1.insert(Vertex<number_t>(p2, true));
	test1.insert(Vertex<number_t>(p3, false));
	VertexContainer<number_t> test2 = test1;
	EXPECT_EQ(test2.size(), 3);
	EXPECT_EQ(test2.find(p1) != test2.end(), false);
	EXPECT_EQ(test2.find(p2) != test2.end(), false);
	EXPECT_EQ(test2.find(p3) != test2.end(), true);
}

TEST_F(VertexContainerTest, Access)
{
	VertexContainer<number_t> test1 = VertexContainer<number_t>();
	test1.insert(Vertex<number_t>(p1, true));
	test1.insert(Vertex<number_t>(p2, true));
	test1.insert(Vertex<number_t>(p3, false));
        
        EXPECT_EQ(test1.end(), test1.find(p1));
        EXPECT_EQ(test1.end(), test1.find(p2));
        EXPECT_NE(test1.end(), test1.find(p3));
        
        EXPECT_EQ(test1.end(), test1.find(p1, false));
        EXPECT_EQ(test1.end(), test1.find(p2, false));
        EXPECT_EQ(test1.end(), test1.find(p3, true));
        
        EXPECT_NE(test1.end(), test1.find(Vertex<number_t>(p1, true)));
        EXPECT_NE(test1.end(), test1.find(Vertex<number_t>(p2, true)));
        EXPECT_NE(test1.end(), test1.find(Vertex<number_t>(p3, false)));
        
        EXPECT_EQ(test1.end(), test1.find(Vertex<number_t>(p1, false)));
        EXPECT_EQ(test1.end(), test1.find(Vertex<number_t>(p2, false)));
        EXPECT_EQ(test1.end(), test1.find(Vertex<number_t>(p3, true)));
        
        EXPECT_TRUE(test1.find(p1, true)->color());
        EXPECT_TRUE(test1.find(p2, true)->color());
        EXPECT_FALSE(test1.find(p3, false)->color());
        
        EXPECT_TRUE(test1.find(Vertex<number_t>(p1, true))->color());
        EXPECT_TRUE(test1.find(Vertex<number_t>(p2, true))->color());
        EXPECT_FALSE(test1.find(Vertex<number_t>(p3, false))->color());
}

TEST_F(VertexContainerTest, OriginIsVertex)
{
    VertexContainer<number_t> test1 = VertexContainer<number_t>();
    test1.insert(Vertex<number_t>(p1, true));
    test1.insert(Vertex<number_t>(p2, true));
    test1.insert(Vertex<number_t>(p3, false));
    
    EXPECT_FALSE(test1.originIsVertex());
    
    p1[x] = 0; p1[y] = 0;
    test1.insert(Vertex<number_t>(p1, true));
    
    EXPECT_TRUE(test1.originIsVertex());
    
    test1.erase(p1);
    test1.insert(Vertex<number_t>(p1, false));
    EXPECT_FALSE(test1.originIsVertex()); // @todo is this really false?
}