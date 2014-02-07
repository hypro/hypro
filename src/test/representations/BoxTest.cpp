#include "gtest/gtest.h"
#include "../defines.h"
#include "carl/numbers/FLOAT_T.h"
#include <carl/core/VariablePool.h>
#include "../../lib/representations/Box/Box.h"

using namespace hypro;
using namespace carl;

class BoxTest : public ::testing::Test
{
public:
	typedef FLOAT_T<double> number_t;
protected:
    virtual void SetUp()
    {
		std::map<carl::Variable, carl::Interval<number_t> > boundaries1;
		boundaries1.insert(std::make_pair(x, Interval<number_t>(2,6)));
		boundaries1.insert(std::make_pair(y, Interval<number_t>(1,3)));
		box1.insert(boundaries1);
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
	
}

TEST_F(BoxTest, Insertion)
{
	
}

TEST_F(BoxTest, Union)
{
	
}

TEST_F(BoxTest, LinearTransformation)
{
	
}

TEST_F(BoxTest, MinkowskiSum)
{
	
}

TEST_F(BoxTest, Intersection)
{
	
}

TEST_F(BoxTest, ConvexHull)
{
	
}

TEST_F(BoxTest, Membership)
{
	
}