/**
 * @file    OrthogonalPolyhedronTest.cpp
 * 
 * @covers  OrthogonalPolyhedron
 * 
 * @author  Benedikt Seidl
 * 
 * @since   2014-03-17
 * @version 2014-03-17
 */

#include "gtest/gtest.h"
#include "../defines.h"
#include "../../lib/util/types.h"
#include "../../lib/datastructures/Point.h"
#include "../../lib/datastructures/Vertex.h"
#include "../../lib/datastructures/VertexContainer.h"
#include "../../lib/representations/Box/Box.h"
#include "../../lib/representations/OrthogonalPolyhedron/OrthogonalPolyhedron.h"
#include "../../lib/representations/OrthogonalPolyhedron/NeighborhoodContainer.h"

#include <map>
#include <carl/core/VariablePool.h>
#include <carl/core/Variable.h>
#include <carl/interval/Interval.h>

using namespace hypro;
using namespace carl;

class OrthogonalPolyhedronTest : public ::testing::Test
{
protected:
    virtual void SetUp()
    {
        Point<number_t>::rawCoordinateMap coordinates;
        
        coordinates[x] = 3; coordinates[y] = 3;
        container1.insert(Point<number_t>(coordinates), true);
        
        coordinates[x] = 3; coordinates[y] = 6;
        container1.insert(Point<number_t>(coordinates), false);
        
        coordinates[x] = 5; coordinates[y] = 3;
        container1.insert(Point<number_t>(coordinates), false);
        
        coordinates[x] = 5; coordinates[y] = 5;
        container1.insert(Point<number_t>(coordinates), true);
        
        coordinates[x] = 7; coordinates[y] = 5;
        container1.insert(Point<number_t>(coordinates), false);
        
        coordinates[x] = 7; coordinates[y] = 6;
        container1.insert(Point<number_t>(coordinates), false);

        p1 = OrthogonalPolyhedron<number_t>(container1);

        coordinates[x] = 1; coordinates[y] = 3;
        container2.insert(Point<number_t>(coordinates), true);
        
        coordinates[x] = 1; coordinates[y] = 4;
        container2.insert(Point<number_t>(coordinates), false);
        
        coordinates[x] = 2; coordinates[y] = 4;
        container2.insert(Point<number_t>(coordinates), true);
        
        coordinates[x] = 2; coordinates[y] = 5;
        container2.insert(Point<number_t>(coordinates), false);
        
        coordinates[x] = 4; coordinates[y] = 5;
        container2.insert(Point<number_t>(coordinates), false);
        
        coordinates[x] = 4; coordinates[y] = 2;
        container2.insert(Point<number_t>(coordinates), false);
        
        coordinates[x] = 2; coordinates[y] = 2;
        container2.insert(Point<number_t>(coordinates), true);
        
        coordinates[x] = 2; coordinates[y] = 3;
        container2.insert(Point<number_t>(coordinates), true);
        
        p2 = OrthogonalPolyhedron<number_t>(container2);
    }
	
    virtual void TearDown()
    {
    }

    carl::VariablePool& pool = carl::VariablePool::getInstance();
    Variable x = pool.getFreshVariable("x");
    Variable y = pool.getFreshVariable("y");
    
    VertexContainer<number_t> container1;
    VertexContainer<number_t> container2;

    OrthogonalPolyhedron<number_t> p1;
    OrthogonalPolyhedron<number_t> p2;
};

TEST_F(OrthogonalPolyhedronTest, Constructor)
{
    OrthogonalPolyhedron<number_t> p;
    OrthogonalPolyhedron<number_t> copy(p);
    SUCCEED();
}

TEST_F(OrthogonalPolyhedronTest, Properties)
{
    EXPECT_FALSE(p1.empty());
    OrthogonalPolyhedron<number_t> empty;
    EXPECT_TRUE(empty.empty());

    std::vector<carl::Variable> variables;
    variables.push_back(y);
    variables.push_back(x);
    EXPECT_EQ((unsigned)2, p1.dimension());
    EXPECT_EQ(variables, p1.variables());
}

TEST_F(OrthogonalPolyhedronTest, BoundaryBox)
{
    Box<number_t> boundaryBox;
    boundaryBox.insert(x, carl::Interval<number_t>(3, 7));
    boundaryBox.insert(y, carl::Interval<number_t>(3, 6));

    EXPECT_EQ(boundaryBox, p1.boundaryBox());
}


TEST_F(OrthogonalPolyhedronTest, LinearTransformation)
{
	matrix A = createMatrix(std::vector<std::vector<double> >({
			std::vector<double>({5, -2}),
			std::vector<double>({9, 3})
	}));

	vector v = createVector(std::vector<double>({7, 2}));


    VertexContainer<number_t> container1;
    Point<number_t>::rawCoordinateMap coordinates;

    coordinates[x] = 38; coordinates[y] = 16;
    container1.insert(Point<number_t>(coordinates), true);

    coordinates[x] = 65; coordinates[y] = 31;
    container1.insert(Point<number_t>(coordinates), false);

    coordinates[x] = 44; coordinates[y] = 12;
    container1.insert(Point<number_t>(coordinates), false);

    coordinates[x] = 62; coordinates[y] = 22;
    container1.insert(Point<number_t>(coordinates), true);

    coordinates[x] = 68; coordinates[y] = 18;
    container1.insert(Point<number_t>(coordinates), false);

    coordinates[x] = 77; coordinates[y] = 23;
    container1.insert(Point<number_t>(coordinates), false);

    VertexContainer<number_t> container2;

    coordinates[x] = 32; coordinates[y] = 20;
    container2.insert(Point<number_t>(coordinates), true);

    coordinates[x] = 41; coordinates[y] = 25;
    container2.insert(Point<number_t>(coordinates), false);

    coordinates[x] = 44; coordinates[y] = 23;
    container2.insert(Point<number_t>(coordinates), true);

    coordinates[x] = 53; coordinates[y] = 28;
    container2.insert(Point<number_t>(coordinates), false);

    coordinates[x] = 59; coordinates[y] = 24;
    container2.insert(Point<number_t>(coordinates), false);

    coordinates[x] = 32; coordinates[y] = 9;
    container2.insert(Point<number_t>(coordinates), false);

    coordinates[x] = 26; coordinates[y] = 13;
    container2.insert(Point<number_t>(coordinates), true);

    coordinates[x] = 35; coordinates[y] = 18;
    container2.insert(Point<number_t>(coordinates), true);



	OrthogonalPolyhedron<number_t> expected1(container1);
	OrthogonalPolyhedron<number_t> expected2(container2);

	OrthogonalPolyhedron<number_t> result1, result2;

	p1.linearTransformation(result1, A, v);
	p2.linearTransformation(result2, A, v);

	EXPECT_EQ(expected1, result1);
	EXPECT_EQ(expected2, result2);
}

TEST_F(OrthogonalPolyhedronTest, Intersect)
{
    OrthogonalPolyhedron<number_t> result;
    
    VertexContainer<number_t> container;
    Point<number_t>::rawCoordinateMap coordinates;
        
    coordinates[x] = 3; coordinates[y] = 3;
    container.insert(Point<number_t>(coordinates), true);
        
    coordinates[x] = 3; coordinates[y] = 5;
    container.insert(Point<number_t>(coordinates), false);
        
    coordinates[x] = 4; coordinates[y] = 5;
    container.insert(Point<number_t>(coordinates), false);
        
    coordinates[x] = 4; coordinates[y] = 3;
    container.insert(Point<number_t>(coordinates), false);
    
    OrthogonalPolyhedron<number_t> expected(container);

    std::cout << "p1:" << p1 << std::endl;
    std::cout << "p2:" << p2 << std::endl;
    p1.intersect(result, p2);
    
    EXPECT_EQ(expected, result);
}

TEST_F(OrthogonalPolyhedronTest, Hull)
{
    VertexContainer<number_t> container;
    Point<number_t>::rawCoordinateMap coordinates;

    coordinates[x] = 3; coordinates[y] = 3;
    container.insert(Point<number_t>(coordinates), true);

    coordinates[x] = 3; coordinates[y] = 6;
    container.insert(Point<number_t>(coordinates), false);

    coordinates[x] = 7; coordinates[y] = 3;
    container.insert(Point<number_t>(coordinates), false);

    coordinates[x] = 7; coordinates[y] = 6;
    container.insert(Point<number_t>(coordinates), false);

    OrthogonalPolyhedron<number_t> hull(container);
    OrthogonalPolyhedron<number_t> result;
    
    EXPECT_TRUE(p1.hull(result));
    EXPECT_EQ(hull, result);
}

TEST_F(OrthogonalPolyhedronTest, Contains)
{
    Point<number_t>::rawCoordinateMap coordinates;
    
    coordinates[x] = 4; coordinates[y] = 5;
    Point<number_t> pt1(coordinates); // true
    
    coordinates[x] = 4; coordinates[y] = 6;
    Point<number_t> pt2(coordinates); // false
    
    coordinates[x] = 5; coordinates[y] = 5;
    Point<number_t> pt3(coordinates); // true
    
    coordinates[x] = 1; coordinates[y] = 5;
    Point<number_t> pt4(coordinates); // false
    
    coordinates[x] = 6; coordinates[y] = 4;
    Point<number_t> pt5(coordinates); // false
    
    coordinates[x] = 5; coordinates[y] = 6.5;
    Point<number_t> pt6(coordinates); // false
    
    coordinates[x] = 4; coordinates[y] = 3;
    Point<number_t> pt7(coordinates); // true
    
    coordinates[x] = 3; coordinates[y] = 5;
    Point<number_t> pt8(coordinates); // true
    
    coordinates[x] = 5; coordinates[y] = 4;
    Point<number_t> pt9(coordinates); // false
    
    coordinates[x] = 6; coordinates[y] = 5;
    Point<number_t> pt10(coordinates); // true
    
    coordinates[x] = 7; coordinates[y] = 6;
    Point<number_t> pt11(coordinates); // false
    
    coordinates[x] = 0; coordinates[y] = 0;
    Point<number_t> pt12(coordinates); // false
    
    coordinates[x] = 1; coordinates[y] = 1;
    Point<number_t> pt13(coordinates); // false
    
    coordinates[x] = 100; coordinates[y] = 100;
    Point<number_t> pt14(coordinates); // false
    
    EXPECT_TRUE(p1.contains(pt1));
    EXPECT_FALSE(p1.contains(pt2));
    EXPECT_TRUE(p1.contains(pt3));
    EXPECT_FALSE(p1.contains(pt4));
    EXPECT_FALSE(p1.contains(pt5));
    EXPECT_FALSE(p1.contains(pt6));
    EXPECT_TRUE(p1.contains(pt7));
    EXPECT_TRUE(p1.contains(pt8));
    EXPECT_FALSE(p1.contains(pt9));
    EXPECT_TRUE(p1.contains(pt10));
    EXPECT_FALSE(p1.contains(pt11));
    EXPECT_FALSE(p1.contains(pt12));
    EXPECT_FALSE(p1.contains(pt13));
    EXPECT_FALSE(p1.contains(pt14));
    
    // also check all vertices
    for (auto vertexIt : container1.vertices()) {
        EXPECT_EQ(vertexIt.color(), p1.contains(vertexIt));
    }
}

TEST_F(OrthogonalPolyhedronTest, Unite) {
    OrthogonalPolyhedron<number_t> result;
    
    VertexContainer<number_t> container;
    Point<number_t>::rawCoordinateMap coordinates;
        
    coordinates[x] = 1; coordinates[y] = 3;
    container.insert(Point<number_t>(coordinates), true);
        
    coordinates[x] = 1; coordinates[y] = 4;
    container.insert(Point<number_t>(coordinates), false);
        
    coordinates[x] = 2; coordinates[y] = 2;
    container.insert(Point<number_t>(coordinates), true);
        
    coordinates[x] = 2; coordinates[y] = 3;
    container.insert(Point<number_t>(coordinates), true);
        
    coordinates[x] = 2; coordinates[y] = 4;
    container.insert(Point<number_t>(coordinates), true);
        
    coordinates[x] = 2; coordinates[y] = 5;
    container.insert(Point<number_t>(coordinates), false);
        
    coordinates[x] = 3; coordinates[y] = 5;
    container.insert(Point<number_t>(coordinates), true);
        
    coordinates[x] = 3; coordinates[y] = 6;
    container.insert(Point<number_t>(coordinates), false);
        
    coordinates[x] = 4; coordinates[y] = 2;
    container.insert(Point<number_t>(coordinates), false);
        
    coordinates[x] = 4; coordinates[y] = 3;
    container.insert(Point<number_t>(coordinates), true);
        
    coordinates[x] = 5; coordinates[y] = 3;
    container.insert(Point<number_t>(coordinates), false);
        
    coordinates[x] = 5; coordinates[y] = 5;
    container.insert(Point<number_t>(coordinates), true);
        
    coordinates[x] = 7; coordinates[y] = 5;
    container.insert(Point<number_t>(coordinates), false);
        
    coordinates[x] = 7; coordinates[y] = 6;
    container.insert(Point<number_t>(coordinates), false);
    
    OrthogonalPolyhedron<number_t> expected(container);

    std::cout << "p1:" << p1 << std::endl;
    std::cout << "p2:" << p2 << std::endl;
    p1.unite(result, p2);
    
    EXPECT_EQ(expected, result);
}

