#include "gtest/gtest.h"
#include "../defines.h"
#include "carl/numbers/FLOAT_T.h"
#include <carl/core/VariablePool.h>
#include "../../lib/datastructures/Point.h"
#include "../../lib/representations/Polytopes/VPolytope/VPolytope.h"

using namespace hypro;
using namespace carl;

template<typename Number>
class VPolytopeTest : public ::testing::Test
{
protected:
    virtual void SetUp()
    {
        typename Point<Number>::coordinateMap coordinates;
        coordinates.insert(std::make_pair(x, 1));
        coordinates.insert(std::make_pair(y, 1));
        coordinates.insert(std::make_pair(z, 0));
        Point<Number> p1 = Point<Number>(coordinates);
        coordinates.insert(std::make_pair(x, 4));
        coordinates.insert(std::make_pair(y, 1));
        coordinates.insert(std::make_pair(z, 0));
        Point<Number> p2 = Point<Number>(coordinates);
        coordinates.insert(std::make_pair(x, 4));
        coordinates.insert(std::make_pair(y, 1));
        coordinates.insert(std::make_pair(z, 4));
        Point<Number> p3 = Point<Number>(coordinates);
        
        points.insert(p1);
        points.insert(p2);
        points.insert(p3);
    }
	
    virtual void TearDown()
    {
    }
	
    carl::VariablePool& pool = carl::VariablePool::getInstance();
    Variable x = pool.getFreshVariable("x");
    Variable y = pool.getFreshVariable("y");
    Variable z = pool.getFreshVariable("z");

    typename VPolytope<Number>::verticeSet points;
    
    VPolytope<Number> vpt1;
    VPolytope<Number> vpt2;
    VPolytope<Number> vpt3;
};

TYPED_TEST(VPolytopeTest, Constructor)
{
    //VPolytope<number_t> aVPolytope = VPolytope<number_t>();
    //VPolytope<number_t> anotherVPolytope = VPolytope<number_t>(points);
    SUCCEED();
}

TYPED_TEST(VPolytopeTest, Access)
{
}

TYPED_TEST(VPolytopeTest, Insertion)
{
}

TYPED_TEST(VPolytopeTest, Union)
{
}

TYPED_TEST(VPolytopeTest, LinearTransformation)
{

}

TYPED_TEST(VPolytopeTest, MinkowskiSum)
{
    //VPolytope<number_t> result;
}

TYPED_TEST(VPolytopeTest, Intersection)
{
    //VPolytope<number_t> result;
    //vpt1.intersect(result, vpt2);
}

TYPED_TEST(VPolytopeTest, ConvexHull)
{
    //stupid for VPolytopes, only required for orthogonal polyhedra
}

TYPED_TEST(VPolytopeTest, Membership)
{
    //Point<number_t> p;
    //p.setCoordinate(x, 4);
    //p.setCoordinate(y, 2);
}