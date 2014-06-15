#include "gtest/gtest.h"
#include "../defines.h"
#include "../../lib/algorithms/reachability/HyReach.h"
#include <iostream>
#include <string>

using namespace hypro;
using namespace carl;
using namespace std;

class HyReachTest : public ::testing::Test
{
protected:
    virtual void SetUp()
    {
    	
    }

    virtual void TearDown()
    {
    }

};

TEST_F(HyReachTest, LocationConstructorTest)
{
	std::string method = "Vectorgenerator TEST: ";
    	HyReach v;

	cout << method << "Generate matrices to compare\n";
    	forward_list<matrix_t<double>> actual_directions = v.vectorgeneratorEXT(3,PI_UP/2,10000);
	cout << method << "VectorgeneratorEXT: done\n";

	forward_list<matrix_t<double>> expected = v.vectorgenerator(3);
	cout << method << "Vectorgenerator: done\n";

	cout << method << "Start comparison\n";
	bool result = true;
	for(auto iterator1 = expected.begin(); iterator1 != expected.end(); ++iterator1)
	{
		result &= v.contains(actual_directions, *iterator1, 3);
	}

	cout << method << "Comparison completed\n";

    	if(result)
	{
		SUCCEED();
	}
	else
	{	
		cout << method << "vectorgeneratorEXT - FAIL\n";
	}

}
