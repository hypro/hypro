#include "gtest/gtest.h"
#include "../defines.h"
#include "carl/numbers/FLOAT_T.h"
#include <carl/core/VariablePool.h>
#include "../../lib/datastructures/Point.h"
#include "../../lib/representations/VPolytope/VPolytope.h"

using namespace hypro;
using namespace carl;

class VPolytopeTest : public ::testing::Test
{
protected:
    virtual void SetUp()
    {
        Point<number_t>::vector_t coordinates;
        coordinates.insert(std::make_pair(x, 1));
        coordinates.insert(std::make_pair(y, 1));
        coordinates.insert(std::make_pair(z, 0));
        Point<number_t> p1 = Point<number_t>(coordinates);
        coordinates.insert(std::make_pair(x, 4));
        coordinates.insert(std::make_pair(y, 1));
        coordinates.insert(std::make_pair(z, 0));
        Point<number_t> p2 = Point<number_t>(coordinates);
        coordinates.insert(std::make_pair(x, 4));
        coordinates.insert(std::make_pair(y, 1));
        coordinates.insert(std::make_pair(z, 4));
        Point<number_t> p3 = Point<number_t>(coordinates);
        
        points.insert(p1);
        points.insert(p2);
        points.insert(p3);
    }
	
    virtual void TearDown()
    {
    }
	
    VariablePool& pool = VariablePool::getInstance();
    Variable x = pool.getFreshVariable("x");
    Variable y = pool.getFreshVariable("y");
    Variable z = pool.getFreshVariable("z");

    VPolytope<number_t>::vertices points;
    
    VPolytope<number_t> vpt1;
    VPolytope<number_t> vpt2;
    VPolytope<number_t> vpt3;
};

TEST_F(VPolytopeTest, Constructor)
{
    VPolytope<number_t> aVPolytope = VPolytope<number_t>();
    VPolytope<number_t> anotherVPolytope = VPolytope<number_t>(points);
    SUCCEED();
}

TEST_F(VPolytopeTest, Access)
{
}

TEST_F(VPolytopeTest, Insertion)
{
}

TEST_F(VPolytopeTest, Union)
{
}

TEST_F(VPolytopeTest, LinearTransformation)
{

}

TEST_F(VPolytopeTest, MinkowskiSum)
{
    VPolytope<number_t> result;
}

TEST_F(VPolytopeTest, Intersection)
{
    VPolytope<number_t> result;
    vpt1.intersect(result, vpt2);
}

TEST_F(VPolytopeTest, ConvexHull)
{
    //stupid for VPolytopes, only required for orthogonal polyhedra
}

TEST_F(VPolytopeTest, Membership)
{
    Point<number_t> p;
    p.setCoordinate(x, 4);
    p.setCoordinate(y, 2);
}