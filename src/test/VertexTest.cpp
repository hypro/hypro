#include "gtest/gtest.h"
#include "defines.h"
#include "datastructures/Vertex.h"

using namespace hypro;

TEST(Vertex, ColorTest)
{ 
    Vertex<number_t> v;
    v.setColor(true);
    ASSERT_TRUE(v.color());
    v.invertColor();
    ASSERT_FALSE(v.color());
}

TEST(Vertex, Constructor)
{ 
    Vertex<number_t> vertex1;
    ASSERT_FALSE(vertex1.color());
    
    Vertex<number_t> vertex2(3, true);
    ASSERT_EQ(vertex2.dimension(), (unsigned) 3);
    ASSERT_TRUE(vertex2.color());
}