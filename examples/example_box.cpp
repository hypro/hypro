#include "../lib/config.h"
#include "../lib/representations/Box/Box.h"

int main(int argc, char const *argv[])
{
	typedef double Number;
	hypro::matrix_t<Number> A = hypro::matrix_t<Number>::Zero(3,3);
	A(0,0) = 1;
	A(1,1) = carl::cos(45);
	A(1,2) = -carl::sin(45);
	A(2,1) = carl::sin(45);
	A(2,2) = carl::cos(45);

	hypro::vector_t<Number> b = hypro::vector_t<Number>::Zero(3);

	hypro::Box<Number> testbox(std::make_pair(hypro::Point<Number>({-2,2,-4}), hypro::Point<Number>({2,4,-2})));

	std::vector<hypro::Point<Number>> tvertices = testbox.vertices();
	for(const auto& vertex : tvertices)
		std::cout << vertex << std::endl;

	std::cout << testbox << std::endl;

	hypro::Box<Number> res = testbox.linearTransformation(A,b);

	std::cout << res << std::endl;

	std::vector<hypro::Point<Number>> vertices = res.vertices();
	for(const auto& vertex : vertices)
		std::cout << vertex << std::endl;

	std::cout << "Manual computation" << std::endl;

	std::vector<hypro::Point<Number>> originalVertices = testbox.vertices();
	for(auto& v : originalVertices){
		std::cout << v << " -> ";
		v = A*v.rawCoordinates();
		std::cout << v << std::endl;
	}



	hypro::Box<Number> testResBox(originalVertices);
	std::cout << testResBox << std::endl;
}