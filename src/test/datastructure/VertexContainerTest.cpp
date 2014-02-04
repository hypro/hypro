#include "gtest/gtest.h"
#include "../defines.h"
#include "../../lib/datastructures/VertexContainer.h"
#include <carl/core/VariablePool.h>

using namespace hypro;
using namespace carl;

class VertexContainerTest : public ::testing::Test
{
public:
	typedef FLOAT_T<double> number_t;
protected:
    virtual void SetUp()
    {
        // p1
        Point<number_t>::vector_t coordinates1;
		VariablePool& pool = VariablePool::getInstance();
		Variable x = pool.getFreshVariable();
		Variable y = pool.getFreshVariable();
        coordinates1.insert( std::make_pair(x, FLOAT_T<number_t>(2)) );
        coordinates1.insert( std::make_pair(y, FLOAT_T<number_t>(5)) );
        p1 = Point<number_t>(coordinates1);
		
        // p2
        Point<number_t>::vector_t coordinates2;
		Variable a = pool.getFreshVariable();
		Variable b = pool.getFreshVariable();
        coordinates2.insert( std::make_pair(a, FLOAT_T<number_t>(7)) );
        coordinates2.insert( std::make_pair(b, FLOAT_T<number_t>(8)) );
        p2 = Point<number_t>(coordinates2);
		
        // p3
        Point<number_t>::vector_t coordinates3;
		Variable c = pool.getFreshVariable();
		Variable d = pool.getFreshVariable();
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

TEST_F(VertexContainerTest, Constructor)
{
	VertexContainer<number_t> test1;
	VertexContainer<number_t> test2 = VertexContainer<number_t>(4);
	EXPECT_EQ(4, test2.dimension());
	SUCCEED();
}

TEST_F(VertexContainerTest, Insertion)
{
	VertexContainer<number_t> test1 = VertexContainer<number_t>(4);
	test1.insert(Vertex<number_t>(p1, true));
	test1.insert(Vertex<number_t>(p2, true));
	test1.insert(Vertex<number_t>(p3, false));
	EXPECT_EQ(test1.size(), 3);
	EXPECT_EQ(test1.find(p1) != test1.end(), true);
	EXPECT_EQ(test1.find(p2) != test1.end(), true);
	EXPECT_EQ(test1.find(p3) != test1.end(), true);
}

TEST_F(VertexContainerTest, Deletion)
{
	VertexContainer<number_t> test1 = VertexContainer<number_t>(4);
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
	VertexContainer<number_t> test1 = VertexContainer<number_t>(4);
	test1.insert(Vertex<number_t>(p1, true));
	test1.insert(Vertex<number_t>(p2, true));
	test1.insert(Vertex<number_t>(p3, false));
	SUCCEED();
}

TEST_F(VertexContainerTest, Assignment)
{
	VertexContainer<number_t> test1 = VertexContainer<number_t>(4);
	test1.insert(Vertex<number_t>(p1, true));
	test1.insert(Vertex<number_t>(p2, true));
	test1.insert(Vertex<number_t>(p3, false));
	VertexContainer<number_t> test2 = test1;
	EXPECT_EQ(test2.size(), 3);
	EXPECT_EQ(test2.find(p1) != test2.end(), true);
	EXPECT_EQ(test2.find(p2) != test2.end(), true);
	EXPECT_EQ(test2.find(p3) != test2.end(), true);
}

TEST_F(VertexContainerTest, Access)
{	
}