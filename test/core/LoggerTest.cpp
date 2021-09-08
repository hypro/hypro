#include "util/Logger.h"
#include "../defines.h"
#include "gtest/gtest.h"

class LoggerTest : public ::testing::Test {
  protected:
	virtual void SetUp() {}

	virtual void TearDown() {}
};

TEST( LoggerTest, Constructor ) {
	LOG4CPLUS_DEBUG( hypro::logger, "Test." );
}
