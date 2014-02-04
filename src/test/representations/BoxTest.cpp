#include "gtest/gtest.h"
#include "../defines.h"
#include "carl/numbers/FLOAT_T.h"
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
    }
	
    virtual void TearDown()
    {
    }
};

TEST_F(BoxTest, Constructor)
{
	Box<number_t> aBox = Box<number_t>();
}