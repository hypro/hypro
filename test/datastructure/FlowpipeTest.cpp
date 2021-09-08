#include "test/defines.h"
#include "gtest/gtest.h"
#include <hypro/datastructures/reachability/Flowpipe.h>

using namespace hypro;

TEST( FlowpipeTest, Constructor ) {
	Flowpipe<double> fp1{};
}
