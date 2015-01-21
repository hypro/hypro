#include "gtest/gtest.h"
#include "../defines.h"
#include "datastructures/Vertex.h"
#include <carl/core/VariablePool.h>


using namespace hypro;
using namespace carl;

template<typename Number>
class VertexTest : public ::testing::Test
{
protected:
    virtual void SetUp()
    {
	// p1
        typename Point<Number>::coordinateMap coordinates1;
        coordinates1.insert( std::make_pair(x, Number(2)) );
        coordinates1.insert( std::make_pair(y, Number(5)) );
        p1 = Point<Number>(coordinates1);
		
        // p2
        typename Point<Number>::coordinateMap coordinates2;
        coordinates2.insert( std::make_pair(x, Number(7)) );
        coordinates2.insert( std::make_pair(y, Number(8)) );
        p2 = Point<Number>(coordinates2);
		
        // p3
        typename Point<Number>::coordinateMap coordinates3;
        coordinates3.insert( std::make_pair(x, Number(-9)) );
	coordinates3.insert( std::make_pair(y, Number(13)) );
        p3 = Point<Number>(coordinates3);
    }
	
    virtual void TearDown()
    {
    }

    carl::VariablePool& pool = carl::VariablePool::getInstance();
    Variable x = pool.getFreshVariable("x");
    Variable y = pool.getFreshVariable("y");
	
    Point<Number> p1;
    Point<Number> p2;
    Point<Number> p3;
};


TYPED_TEST(VertexTest, ColorTest)
{
    Vertex<TypeParam> v;
    v.setColor(true);
    ASSERT_TRUE(v.color());
    v.invertColor();
    ASSERT_FALSE(v.color());
}

TYPED_TEST(VertexTest, Constructor)
{ 
    Vertex<TypeParam> vertex1;
    ASSERT_FALSE(vertex1.color());
    
    Vertex<TypeParam> vertex2(this->p1, true);
    ASSERT_EQ(vertex2.dimension(), (unsigned) 2);
    ASSERT_TRUE(vertex2.color());
}

TYPED_TEST(VertexTest, Equality)
{
    Vertex<TypeParam> v1(this->p1, true);
    Vertex<TypeParam> v2(this->p1, false);
    Vertex<TypeParam> v3(this->p1, true);
    
    EXPECT_TRUE(v1 != v2);
    EXPECT_TRUE(v1 == v3);
}

TYPED_TEST(VertexTest, Order)
{
    Vertex<TypeParam> v1(this->p1, false);
    Vertex<TypeParam> v2(this->p1, true);
    Vertex<TypeParam> v3(this->p2, true);
    Vertex<TypeParam> v4(this->p3, false);
    
    EXPECT_TRUE(v1 < v2);
    EXPECT_TRUE(v2 < v3);
    EXPECT_TRUE(v3 < v4);

    EXPECT_TRUE(v4 > v3);
    EXPECT_TRUE(v3 > v2);
    EXPECT_TRUE(v2 > v1);
}