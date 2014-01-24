#include "gtest/gtest.h"
#include "../defines.h"
#include "../../lib/datastructures/VertexContainer.h"

using namespace hypro;

TEST(VertexContainer, Constructor)
{
	VertexContainer<number_t> test1;
	VertexContainer<number_t> test2 = VertexContainer<number_t>(4);
	EXPECT_EQ(4, test2.dimension());
	SUCCEED();
}

TEST(VertexContainer, Insertion)
{
	VertexContainer<number_t> test1 = VertexContainer<number_t>(4);
	test1.insert(Vertex<number_t>(1,1));
	test1.insert(Vertex<number_t>(2,1));
	test1.insert(Vertex<number_t>(3,1));
	test1.insert(Vertex<number_t>(4,1));
}

TEST(VertexContainer, Deletion)
{
}

TEST(VertexContainer, Destructor)
{
}

TEST(VertexContainer, Assignment)
{
}

TEST(VertexContainer, Access)
{
}