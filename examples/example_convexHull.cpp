#include "../src/lib/config.h"
#include "../src/lib/representations/Polytope/Polytope.h"
#include "../src/lib/datastructures/Point.h"
#include "../src/lib/datastructures/Facet.h"
#include "../src/lib/datastructures/Ridge.h"
#include "../src/lib/util/convexHull.h"



using namespace hypro;

int main(int argc, char** argv) {
	vector_t<double> v01 = vector_t<double>(3);
		v01(0) = 0;
		v01(1) = 0;
		v01(2) = 0;
		Point<double> p01 = Point<double>(v01);

		vector_t<double> v02 = vector_t<double>(3);
		v02(0) = 0;
		v02(1) = 2;
		v02(2) = 0;
		Point<double> p02 = Point<double>(v02);

		vector_t<double> v03 = vector_t<double>(3);
		v03(0) = 2;
		v03(1) = 0;
		v03(2) = 0;
		Point<double> p03 = Point<double>(v03);

		vector_t<double> v04 = vector_t<double>(3);
		v04(0) = 0;
		v04(1) = 0;
		v04(2) = 5;
		Point<double> p04= Point<double>(v04);

		vector_t<double> v05 = vector_t<double>(3);
		v05(0) = 2;
		v05(1) = 2;
		v05(2) = 0;
		Point<double> p05 = Point<double>(v05);

		vector_t<double> v06 = vector_t<double>(3);
		v06(0) = 1;
		v06(1) = 3;
		v06(2) = 5;
		Point<double> p06 = Point<double>(v06);

		vector_t<double> v07 = vector_t<double>(3);
		v07(0) = 0;
		v07(1) = 2;
		v07(2) = 5;
		Point<double> p07 = Point<double>(v07);

		vector_t<double> v08 = vector_t<double>(3);
		v08(0) = 2;
		v08(1) = 0;
		v08(2) = 5;
		Point<double> p08 = Point<double>(v08);

		vector_t<double> v09 = vector_t<double>(3);
		v09(0) = 2;
		v09(1) = 2;
		v09(2) = 5;
		Point<double> p09 = Point<double>(v09);

		vector_t<double> v10 = vector_t<double>(3);
		v10(0) = 1;
		v10(1) = 3;
		v10(2) = 0;
		Point<double> p10 = Point<double>(v10);

		vector_t<double> v11 = vector_t<double>(3);
		v11(0) = 1;
		v11(1) = 2;
		v11(2) = 3;
		Point<double> p11 = Point<double>(v11);

		std::vector<Point<double>> points;
		points.push_back(p01);
		points.push_back(p02);
		points.push_back(p03);
		points.push_back(p04);
		points.push_back(p05);
		points.push_back(p06);
		points.push_back(p07);
		points.push_back(p08);
		points.push_back(p09);
		points.push_back(p10);
		points.push_back(p11);

		vector_t<double> v1_2 = vector_t<double>(2);
		v1_2(0) = 4;
		v1_2(1) = 0;
		Point<double> p1_2 = Point<double>(v1_2);

		vector_t<double> v2_2 = vector_t<double>(2);
		v2_2(0) = 0;
		v2_2(1) = -4;
		Point<double> p2_2 = Point<double>(v2_2);

		vector_t<double> v3_2 = vector_t<double>(2);
		v3_2(0) = 0;
		v3_2(1) = 0;
		Point<double> p3_2 = Point<double>(v3_2);

		std::vector<Point<double>> points2;
		points2.push_back(p1_2);
		points2.push_back(p2_2);
		points2.push_back(p3_2);

		auto facets = convexHull(points);//std::pair<std::vector<std::shared_ptr<Facet<double> > >, std::map<Point<double>, std::set<Point<double> > > > facets = convexHull(points);


		for(unsigned i = 0; i<facets.first.size(); i++){
			std::cout << "Result Nr." << i << std::endl << *facets.first.at(i) << std::endl;
		}
}
