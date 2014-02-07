#include "gtest/gtest.h"
#include "../defines.h"
#include "datastructures/Vertex.h"
#include <carl/core/VariablePool.h>


using namespace hypro;
using namespace carl;

class VertexTest : public ::testing::Test
{
protected:
    virtual void SetUp()
    {
		// p1
        Point<number_t>::vector_t coordinates1;
		VariablePool& pool = VariablePool::getInstance();
		Variable x = pool.getFreshVariable(carl::VT_INT);
		Variable y = pool.getFreshVariable(carl::VT_INT);
        coordinates1.insert( std::make_pair(x, FLOAT_T<number_t>(2)) );
        coordinates1.insert( std::make_pair(y, FLOAT_T<number_t>(5)) );
        p1 = Point<number_t>(coordinates1);
		
        // p2
        Point<number_t>::vector_t coordinates2;
		Variable a = pool.getFreshVariable(carl::VT_INT);
		Variable b = pool.getFreshVariable(carl::VT_INT);
        coordinates2.insert( std::make_pair(a, FLOAT_T<number_t>(7)) );
        coordinates2.insert( std::make_pair(b, FLOAT_T<number_t>(8)) );
        p2 = Point<number_t>(coordinates2);
		
        // p3
        Point<number_t>::vector_t coordinates3;
		Variable c = pool.getFreshVariable(carl::VT_INT);
		Variable d = pool.getFreshVariable(carl::VT_INT);
        coordinates3.insert( std::make_pair(c, FLOAT_T<number_t>(-9)) );
		coordinates3.insert( std::make_pair(d, FLOAT_T<number_t>(13)) );
        p3 = Point<number_t>(coordinates3);
    }
	
    virtual void TearDown()
    {
    }
	
    Point<number_t> p1;
    Point<number_t> p2;
    Point<number_t> p3;
};


TEST_F(VertexTest, ColorTest)
{
    Vertex<number_t> v;
    v.setColor(true);
    ASSERT_TRUE(v.color());
    v.invertColor();
    ASSERT_FALSE(v.color());
}

TEST_F(VertexTest, Constructor)
{ 
    Vertex<number_t> vertex1;
    ASSERT_FALSE(vertex1.color());
    
    Vertex<number_t> vertex2(p1, true);
    ASSERT_EQ(vertex2.dimension(), (unsigned) 2);
    ASSERT_TRUE(vertex2.color());
}