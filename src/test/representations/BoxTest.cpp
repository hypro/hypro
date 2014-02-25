#include "gtest/gtest.h"
#include "../defines.h"
#include "carl/numbers/FLOAT_T.h"
#include <carl/core/VariablePool.h>
#include "../../lib/datastructures/Point.h"
#include "../../lib/representations/Box/Box.h"

using namespace hypro;
using namespace carl;

class BoxTest : public ::testing::Test
{
protected:
    virtual void SetUp()
    {
        std::map<const carl::Variable, carl::Interval<number_t> > boundaries1;
        boundaries1.insert(std::make_pair(x, Interval<number_t>(2,6)));
        boundaries1.insert(std::make_pair(y, Interval<number_t>(1,3)));
        box1.insert(boundaries1);
        
        std::map<const carl::Variable, carl::Interval<number_t> > boundaries2;
        boundaries2.insert(std::make_pair(x, Interval<number_t>(-1,6)));
        boundaries2.insert(std::make_pair(y, Interval<number_t>(4,7)));
        box2.insert(boundaries2);
    }
	
    virtual void TearDown()
    {
    }
	
    VariablePool& pool = VariablePool::getInstance();
    Variable x = pool.getFreshVariable("x");
    Variable y = pool.getFreshVariable("y");

    Box<number_t> box1;
    Box<number_t> box2;
    Box<number_t> box3;
};

TEST_F(BoxTest, Constructor)
{
    Box<number_t> aBox = Box<number_t>();
    SUCCEED();
}

TEST_F(BoxTest, Access)
{
    Box<number_t>::intervalMap tmp = box1.boundaries();
    EXPECT_EQ(2, tmp[x].lower());
    EXPECT_EQ(6, tmp[x].upper());
    EXPECT_EQ(1, tmp[y].lower());
    EXPECT_EQ(3, tmp[y].upper());
}

TEST_F(BoxTest, Insertion)
{
    Box<number_t>::intervalMap tmp;
    Variable z = pool.getFreshVariable("z");
    tmp.insert(std::make_pair(z, Interval<number_t>(3,9)));
    box1.insert(tmp);
    EXPECT_EQ(true, box1.hasVariable(z));
    
    EXPECT_EQ(3, box1.interval(z).lower());
    EXPECT_EQ(9, box1.interval(z).upper());
    
    Variable w = pool.getFreshVariable("w");
    box1.insert(std::make_pair(w, Interval<number_t>(4,5)));
    EXPECT_EQ(true, box1.hasVariable(w));
    
    EXPECT_EQ(4, box1.interval(w).lower());
    EXPECT_EQ(5, box1.interval(w).upper());
}

TEST_F(BoxTest, Union)
{
    cln::cl_RA tmp;
    carl::is_rational<cln::cl_RA> str;
    bool test = str.value;
}

TEST_F(BoxTest, LinearTransformation)
{

}

TEST_F(BoxTest, MinkowskiSum)
{
    Box<number_t> result;
    box1.minkowski_sum(result, box2);
    EXPECT_EQ(1 , result.interval(x).lower());
    EXPECT_EQ(12 , result.interval(x).upper());
    EXPECT_EQ(5 , result.interval(y).lower());
    EXPECT_EQ(10 , result.interval(y).upper());
}

TEST_F(BoxTest, Intersection)
{
    Box<number_t> result;
    box1.intersect(result, box2);
    EXPECT_TRUE(result.isEmpty());
}

TEST_F(BoxTest, ConvexHull)
{
    //stupid for Boxes, only required for orthogonal polyhedra
}

TEST_F(BoxTest, Membership)
{
    Point<number_t> p;
    p.setCoordinate(x, 4);
    p.setCoordinate(y, 2);
    EXPECT_TRUE(box1.contains(p));
}