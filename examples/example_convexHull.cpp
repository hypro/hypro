
#include "../src/lib/datastructures/Point.h"
#include "../src/lib/algorithms/convexHull/ConvexHull.h"

int main(int argc, char** argv) {

	using Number = mpq_class;

	std::vector<hypro::Point<Number>> points;
	points.push_back( hypro::Point<Number>({ Number(-9)/Number(100), 15 , Number(14)/Number(10)}) );
	points.push_back( hypro::Point<Number>({ Number(-9)/Number(100), 16 , Number(14)/Number(10)}) );
	points.push_back( hypro::Point<Number>({ Number(-9)/Number(100), 15 , Number(13)/Number(10)}) );
	points.push_back( hypro::Point<Number>({ Number(-9)/Number(100), 16 , Number(13)/Number(10)}) );
	points.push_back( hypro::Point<Number>({ Number(-9)/Number(100), 15 , Number(6)/Number(5)}) );
	points.push_back( hypro::Point<Number>({ Number(-9)/Number(100), 16 , Number(6)/Number(5)}) );
	points.push_back( hypro::Point<Number>({ Number(-9)/Number(100), 15 , Number(9)/Number(100)}) );
	points.push_back( hypro::Point<Number>({ Number(-9)/Number(100), 16 , Number(9)/Number(100)}) );
	points.push_back( hypro::Point<Number>({ Number(-9)/Number(10), 15 , 0}) );
	points.push_back( hypro::Point<Number>({ Number(-9)/Number(10), 16 , 0}) );
	points.push_back( hypro::Point<Number>({ Number(-1)/Number(2) , 15 , Number(5)/Number(2)}) );
	points.push_back( hypro::Point<Number>({ Number(-1)/Number(2) , 16 , Number(5)/Number(2)}) );
	points.push_back( hypro::Point<Number>({ Number(-47)/Number(100) , 15 , Number(5)/Number(2)}) );
	points.push_back( hypro::Point<Number>({ Number(-47)/Number(100) , 16 , Number(5)/Number(2)}) );
	points.push_back( hypro::Point<Number>({ 0 , 15 , 0}) );
	points.push_back( hypro::Point<Number>({ 0 , 15 , Number(7)/Number(5)}) );
	points.push_back( hypro::Point<Number>({ 0 , 15 , Number(5)/Number(2)}) );
	points.push_back( hypro::Point<Number>({ 0 , 16 , 0}) );
	points.push_back( hypro::Point<Number>({ 0 , 16 , Number(7)/Number(5)}) );
	points.push_back( hypro::Point<Number>({ 0 , 16 , Number(5)/Number(2)}) );


	std::set<hypro::Point<Number>> pointSet;
	pointSet.insert(points.begin(), points.end());
	points.clear();
	points.insert(points.end(), pointSet.begin(), pointSet.end());

	hypro::ConvexHull<Number> ch(points);
	ch.convexHullVertices();

	std::cout << std::endl << "Example_convexHull results: " << std::endl;
	for(const auto& hplane : ch.getHsv()) {
		std::cout << hplane << std::endl;
	}
}
