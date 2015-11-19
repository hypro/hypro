#include "../src/lib/config.h"
#include "../src/lib/representations/Polytope/Polytope.h"
#include "../src/lib/datastructures/Point.h"
#include "../src/lib/datastructures/Facet.h"
#include "../src/lib/datastructures/Ridge.h"
#include "../src/lib/util/convexHull.h"



using namespace hypro;

int main(int argc, char** argv) {
	vector_t<double> v01_1 = vector_t<double>(3);
		v01_1(0) = 0;	v01_1(1) = 0;	v01_1(2) = 0;

		vector_t<double> v02_1 = vector_t<double>(3);
		v02_1(0) = 0;	v02_1(1) = 2;	v02_1(2) = 0;

		vector_t<double> v03_1 = vector_t<double>(3);
		v03_1(0) = 2;	v03_1(1) = 0;	v03_1(2) = 0;

		vector_t<double> v04_1 = vector_t<double>(3);
		v04_1(0) = 0;	v04_1(1) = 0;	v04_1(2) = 5;

		vector_t<double> v05_1 = vector_t<double>(3);
		v05_1(0) = 2;	v05_1(1) = 2;	v05_1(2) = 0;

		vector_t<double> v06_1 = vector_t<double>(3);
		v06_1(0) = 1;	v06_1(1) = 3;	v06_1(2) = 5;

		vector_t<double> v07_1 = vector_t<double>(3);
		v07_1(0) = 0;	v07_1(1) = 2;	v07_1(2) = 5;

		vector_t<double> v08_1 = vector_t<double>(3);
		v08_1(0) = 2;	v08_1(1) = 0;	v08_1(2) = 5;

		vector_t<double> v09_1 = vector_t<double>(3);
		v09_1(0) = 2;	v09_1(1) = 2;	v09_1(2) = 5;

		vector_t<double> v10_1 = vector_t<double>(3);
		v10_1(0) = 1;	v10_1(1) = 3;	v10_1(2) = 0;

		vector_t<double> v11_1 = vector_t<double>(3);
		v11_1(0) = 1; v11_1(1) = 2;	v11_1(2) = 3;

		std::vector<Point<double>> points;
		points.push_back(Point<double>(v01_1));
		points.push_back(Point<double>(v02_1));
		points.push_back(Point<double>(v03_1));
		points.push_back(Point<double>(v04_1));
		points.push_back(Point<double>(v05_1));
		points.push_back(Point<double>(v06_1));
		points.push_back(Point<double>(v07_1));
		points.push_back(Point<double>(v08_1));
		points.push_back(Point<double>(v09_1));
		points.push_back(Point<double>(v10_1));
		points.push_back(Point<double>(v11_1));

		vector_t<double> v1_2 = vector_t<double>(2);
		v1_2(0) = 4; v1_2(1) = 0;

		vector_t<double> v2_2 = vector_t<double>(2);
		v2_2(0) = -4;	v2_2(1) = 0;

		vector_t<double> v3_2 = vector_t<double>(2);
		v3_2(0) = 0; v3_2(1) = 4;

		vector_t<double> v4_2 = vector_t<double>(2);
		v4_2(0) = 9; v4_2(1) = 5;

		std::vector<Point<double>> points2;
		points2.push_back(Point<double>(v1_2));
		points2.push_back(Point<double>(v2_2));
		points2.push_back(Point<double>(v3_2));
		points2.push_back(Point<double>(v4_2));

		vector_t<double> v01_box = vector_t<double>(3);
		v01_box(0) = 1; v01_box(1) = 1; v01_box(2) = 1;

		vector_t<double> v02_box = vector_t<double>(3);
		v02_box(0) = 1; v02_box(1) = 1; v02_box(2) = -1;

		vector_t<double> v03_box = vector_t<double>(3);
		v03_box(0) = 1; v03_box(1) = -1; v03_box(2) = 1;

		vector_t<double> v04_box = vector_t<double>(3);
		v04_box(0) = 1; v04_box(1) = -1; v04_box(2) = -1;

		vector_t<double> v05_box = vector_t<double>(3);
		v05_box(0) = -1; v05_box(1) = 1; v05_box(2) = 1;

		vector_t<double> v06_box = vector_t<double>(3);
		v06_box(0) = -1; v06_box(1) = 1; v06_box(2) = -1;

		vector_t<double> v07_box = vector_t<double>(3);
		v07_box(0) = -1; v07_box(1) = -1; v07_box(2) = 1;

		vector_t<double> v08_box = vector_t<double>(3);
		v08_box(0) = -1; v08_box(1) = -1; v08_box(2) = -1;

		std::vector<Point<double>> points_box;
		points_box.push_back(Point<double>(v01_box));
		points_box.push_back(Point<double>(v02_box));
		points_box.push_back(Point<double>(v03_box));
		points_box.push_back(Point<double>(v04_box));
		points_box.push_back(Point<double>(v05_box));
		points_box.push_back(Point<double>(v06_box));
		points_box.push_back(Point<double>(v07_box));
		points_box.push_back(Point<double>(v08_box));

		vector_t<double> v01_pyramid = vector_t<double>(3);
		v01_pyramid(0) = 1; v01_pyramid(1) = 0; v01_pyramid(2) = 1;

		vector_t<double> v02_pyramid = vector_t<double>(3);
		v02_pyramid(0) = 1; v02_pyramid(1) = 0; v02_pyramid(2) = -1;

		vector_t<double> v03_pyramid = vector_t<double>(3);
		v03_pyramid(0) = -1; v03_pyramid(1) = 0; v03_pyramid(2) = 1;

		vector_t<double> v04_pyramid = vector_t<double>(3);
		v04_pyramid(0) = -1; v04_pyramid(1) = 0; v04_pyramid(2) = -1;

		vector_t<double> v05_pyramid = vector_t<double>(3);
		v05_pyramid(0) = 0; v05_pyramid(1) = 1; v05_pyramid(2) = 0;

		std::vector<hypro::Point<double>> points_pyramid;
		points_pyramid.push_back(Point<double>(v01_pyramid));
		points_pyramid.push_back(Point<double>(v02_pyramid));
		points_pyramid.push_back(Point<double>(v03_pyramid));
		points_pyramid.push_back(Point<double>(v04_pyramid));
		points_pyramid.push_back(Point<double>(v05_pyramid));

		auto facets = convexHull(points_pyramid);//std::pair<std::vector<std::shared_ptr<Facet<double> > >, std::map<Point<double>, std::set<Point<double> > > > facets = convexHull(points);


		for(unsigned i = 0; i<facets.first.size(); i++){
			std::cout << "Result Nr." << i << std::endl << "normal: "<< facets.first.at(i)->getNormal() <<"\noffset: "<<facets.first.at(i)->getScalar() << std::endl;
		}
}
