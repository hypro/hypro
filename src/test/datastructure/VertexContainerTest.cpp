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

template<typename Number>
class VertexContainerTest : public ::testing::Test
{
protected:
	virtual void SetUp()
	{
		pool.clear();
		x = pool.newCarlVariable();
		y = pool.newCarlVariable();
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
	
	hypro::VariablePool& pool = hypro::VariablePool::getInstance();
	carl::Variable x;
	carl::Variable y;
	
	Point<Number> p1;
	Point<Number> p2;
	Point<Number> p3;
};

TYPED_TEST(VertexContainerTest, Constructor)
{
	VertexContainer<TypeParam> test1;
	VertexContainer<TypeParam> test2;
 	SUCCEED();
}

TYPED_TEST(VertexContainerTest, Insertion)
{
	VertexContainer<TypeParam> test1 = VertexContainer<TypeParam>();
	test1.insert(Vertex<TypeParam>(this->p1, true));
	test1.insert(Vertex<TypeParam>(this->p2, true));
	test1.insert(Vertex<TypeParam>(this->p3, false));
		
	EXPECT_EQ((unsigned) 3, test1.size());
	EXPECT_EQ((unsigned) 2, test1.dimension());
	EXPECT_FALSE(test1.find(this->p1) != test1.end());
	EXPECT_FALSE(test1.find(this->p2) != test1.end());
	EXPECT_TRUE(test1.find(this->p3) != test1.end());
}

TYPED_TEST(VertexContainerTest, Deletion)
{
	VertexContainer<TypeParam> test1 = VertexContainer<TypeParam>();
	test1.insert(Vertex<TypeParam>(this->p1, true));
	test1.insert(Vertex<TypeParam>(this->p2, true));
	test1.insert(Vertex<TypeParam>(this->p3, false));
	EXPECT_EQ(test1.size(), (unsigned) 3);
	test1.erase(Vertex<TypeParam>(this->p2, true));
	EXPECT_EQ(test1.size(), (unsigned) 2);
	EXPECT_EQ(test1.find(this->p2) != test1.end(), false);
	test1.erase(this->p3);
	EXPECT_EQ(test1.size(), (unsigned) 1);
	EXPECT_EQ(test1.find(this->p3) != test1.end(), false);
}

TYPED_TEST(VertexContainerTest, Destructor)
{
	VertexContainer<TypeParam> test1 = VertexContainer<TypeParam>();
	test1.insert(Vertex<TypeParam>(this->p1, true));
	test1.insert(Vertex<TypeParam>(this->p2, true));
	test1.insert(Vertex<TypeParam>(this->p3, false));
	SUCCEED();
}

TYPED_TEST(VertexContainerTest, Assignment)
{
	VertexContainer<TypeParam> test1 = VertexContainer<TypeParam>();
	test1.insert(Vertex<TypeParam>(this->p1, true));
	test1.insert(Vertex<TypeParam>(this->p2, true));
	test1.insert(Vertex<TypeParam>(this->p3, false));
	VertexContainer<TypeParam> test2 = test1;
	EXPECT_EQ(test2.size(), (unsigned) 3);
	EXPECT_EQ(test2.find(this->p1) != test2.end(), false);
	EXPECT_EQ(test2.find(this->p2) != test2.end(), false);
	EXPECT_EQ(test2.find(this->p3) != test2.end(), true);
}

TYPED_TEST(VertexContainerTest, Access)
{
	VertexContainer<TypeParam> test1 = VertexContainer<TypeParam>();
	test1.insert(Vertex<TypeParam>(this->p1, true));
	test1.insert(Vertex<TypeParam>(this->p2, true));
	test1.insert(Vertex<TypeParam>(this->p3, false));
		
	EXPECT_EQ(test1.end(), test1.find(this->p1));
	EXPECT_EQ(test1.end(), test1.find(this->p2));
	EXPECT_NE(test1.end(), test1.find(this->p3));

	EXPECT_EQ(test1.end(), test1.find(this->p1, false));
	EXPECT_EQ(test1.end(), test1.find(this->p2, false));
	EXPECT_EQ(test1.end(), test1.find(this->p3, true));

	EXPECT_NE(test1.end(), test1.find(Vertex<TypeParam>(this->p1, true)));
	EXPECT_NE(test1.end(), test1.find(Vertex<TypeParam>(this->p2, true)));
	EXPECT_NE(test1.end(), test1.find(Vertex<TypeParam>(this->p3, false)));

	EXPECT_EQ(test1.end(), test1.find(Vertex<TypeParam>(this->p1, false)));
	EXPECT_EQ(test1.end(), test1.find(Vertex<TypeParam>(this->p2, false)));
	EXPECT_EQ(test1.end(), test1.find(Vertex<TypeParam>(this->p3, true)));

	EXPECT_TRUE(test1.find(this->p1, true)->color());
	EXPECT_TRUE(test1.find(this->p2, true)->color());
	EXPECT_FALSE(test1.find(this->p3, false)->color());

	EXPECT_TRUE(test1.find(Vertex<TypeParam>(this->p1, true))->color());
	EXPECT_TRUE(test1.find(Vertex<TypeParam>(this->p2, true))->color());
	EXPECT_FALSE(test1.find(Vertex<TypeParam>(this->p3, false))->color());
}

TYPED_TEST(VertexContainerTest, OriginIsVertex)
{
	VertexContainer<TypeParam> test1 = VertexContainer<TypeParam>();
	test1.insert(Vertex<TypeParam>(this->p1, true));
	test1.insert(Vertex<TypeParam>(this->p2, true));
	test1.insert(Vertex<TypeParam>(this->p3, false));
	
	EXPECT_FALSE(test1.originIsVertex());
	
	this->p1[this->x] = 0; this->p1[this->y] = 0;
	test1.insert(Vertex<TypeParam>(this->p1, true));
	
	EXPECT_TRUE(test1.originIsVertex());
	
	test1.erase(Vertex<TypeParam>(this->p1, true));
	test1.insert(Vertex<TypeParam>(this->p1, false));
	EXPECT_FALSE(test1.originIsVertex()); // @todo is this really false?
}

TYPED_TEST(VertexContainerTest, OperatorTest) {
	VertexContainer<TypeParam> test1 = VertexContainer<TypeParam>();
	VertexContainer<TypeParam> test2 = VertexContainer<TypeParam>();
	VertexContainer<TypeParam> test3 = VertexContainer<TypeParam>();
	test1.insert(Vertex<TypeParam>(this->p1, true));
	test1.insert(Vertex<TypeParam>(this->p2, true));
	test1.insert(Vertex<TypeParam>(this->p3, false));

	test2.insert(Vertex<TypeParam>(this->p1, false));
	test2.insert(Vertex<TypeParam>(this->p2, true));
	test2.insert(Vertex<TypeParam>(this->p3, false));

	test3.insert(Vertex<TypeParam>(this->p1, false));
	test3.insert(Vertex<TypeParam>(this->p2, true));
	test3.insert(Vertex<TypeParam>(this->p3, false));
	EXPECT_FALSE(test1 == test2);
	EXPECT_TRUE(test2 == test3);
	EXPECT_FALSE(test1 == test3);
}
