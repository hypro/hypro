/**
 * Your story.
 */

#include "../src/lib/representations/SupportFunction/SupportFunctionContent.h"
#include "../src/lib/representations/Polytopes/HPolytope/HPolytope.h"
//#include "../src/lib/datastructures/Hyperplane.h"

using namespace hypro;

int main(int argc, char const *argv[])
{
	typedef double Number;

	Hyperplane<Number> hp1({1,0},2);
	Hyperplane<Number> hp2({0,1},2);
	Hyperplane<Number> hp3({-1,0},2);
	Hyperplane<Number> hp4({0,-1},2);

	std::vector<Hyperplane<Number>> planes;
	planes.push_back(hp1);
	planes.push_back(hp2);
	planes.push_back(hp3);
	planes.push_back(hp4);

	HPolytope<Number> poly1(planes);

	std::cout << poly1 << std::endl;

	std::shared_ptr<SupportFunctionContent<Number>> sf1 = SupportFunctionContent<Number>::create(SF_TYPE::POLY, poly1.matrix(), poly1.vector());

	return 0;
}
