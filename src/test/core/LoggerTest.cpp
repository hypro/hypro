#include "gtest/gtest.h"
#include "../defines.h"
#include "util/Logger.h"

class LoggerTest : public ::testing::Test
{
protected:
    virtual void SetUp()
    {}

    virtual void TearDown()
    {}
};

TEST(LoggerTest, Constructor)
{
	LOG4CPLUS_DEBUG(hypro::logger, "Test.");
}
