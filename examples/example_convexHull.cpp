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
		v1_2(0) = 100; v1_2(1) = 0;

		vector_t<double> v2_2 = vector_t<double>(2);
		v2_2(0) = -50;	v2_2(1) = 0;

		vector_t<double> v3_2 = vector_t<double>(2);
		v3_2(0) = 0; v3_2(1) = 50;

		vector_t<double> v4_2 = vector_t<double>(2);
		v4_2(0) = 0; v4_2(1) = 25;

		vector_t<double> v5_2 = vector_t<double>(2);
		v5_2(0) = 0; v5_2(1) = 15;

		vector_t<double> v6_2 = vector_t<double>(2);
		v6_2(0) = 1; v6_2(1) = 4;

		std::vector<Point<double>> points2;
		points2.push_back(Point<double>(v1_2));
		points2.push_back(Point<double>(v2_2));
		points2.push_back(Point<double>(v3_2));
		points2.push_back(Point<double>(v4_2));
		points2.push_back(Point<double>(v5_2));
		//points2.push_back(Point<double>(v6_2));


		vector_t<double> v1_massif = vector_t<double>(2);
		v1_massif(0) = 505084; v1_massif(1) = 340951;

		vector_t<double> v2_massif = vector_t<double>(2);
		v2_massif(0) = 464886;	v2_massif(1) = 28512;

		vector_t<double> v3_massif = vector_t<double>(2);
		v3_massif(0) = 509059; v3_massif(1) = 361304;

		vector_t<double> v4_massif = vector_t<double>(2);
		v4_massif(0) = 51257; v4_massif(1) = 351494;

		vector_t<double> v5_massif = vector_t<double>(2);
		v5_massif(0) = 450059; v5_massif(1) = 293059;

		vector_t<double> v6_massif = vector_t<double>(2);
		v6_massif(0) = 447026;	v6_massif(1) = 302869; // <- smallest x

		vector_t<double> v7_massif = vector_t<double>(2);
		v7_massif(0) = 454343; v7_massif(1) = 28512;

		vector_t<double> v8_massif = vector_t<double>(2);
		v8_massif(0) = 508772; v8_massif(1) = 361864;


		vector_t<double> v9_massif = vector_t<double>(2);
		v9_massif(0) = 504402; v9_massif(1) =  368829;

		vector_t<double> v10_massif = vector_t<double>(2);
		v10_massif(0) = 493858;	v10_massif(1) = 368829;

		vector_t<double> v11_massif = vector_t<double>(2);
		v11_massif(0) = 508445; v11_massif(1) = 331141;

		vector_t<double> v12_massif = vector_t<double>(2);
		v12_massif(0) = 467689; v12_massif(1) =  27531;

		vector_t<double> v13_massif = vector_t<double>(2);
		v13_massif(0) = 512623;	v13_massif(1) =  351494;

		vector_t<double> v14_massif = vector_t<double>(2);
		v14_massif(0) = 516036; v14_massif(1) = 341684;

		vector_t<double> v15_massif = vector_t<double>(2);
		v15_massif(0) = 45294; v15_massif(1) = 283249;

		vector_t<double> v16_massif = vector_t<double>(2);
		v16_massif(0) = 450006; v16_massif(1) = 293059;

		std::vector<Point<double>> points_massif;
		points_massif.push_back(Point<double>(v1_massif));
		points_massif.push_back(Point<double>(v2_massif));
		points_massif.push_back(Point<double>(v3_massif));
		points_massif.push_back(Point<double>(v4_massif));
		points_massif.push_back(Point<double>(v5_massif));
		points_massif.push_back(Point<double>(v6_massif));
		points_massif.push_back(Point<double>(v7_massif));
		points_massif.push_back(Point<double>(v8_massif));
		points_massif.push_back(Point<double>(v9_massif));
		points_massif.push_back(Point<double>(v10_massif));
		points_massif.push_back(Point<double>(v11_massif));
		points_massif.push_back(Point<double>(v12_massif));
		points_massif.push_back(Point<double>(v13_massif));
		points_massif.push_back(Point<double>(v14_massif));
		points_massif.push_back(Point<double>(v15_massif));
		points_massif.push_back(Point<double>(v16_massif));


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

		auto facets = convexHull(points2);

		std::cout << std::endl << "Example_convexHull results: " << std::endl;
		for(unsigned i = 0; i<facets.first.size(); i++){
			std::cout << "Result Nr." << i+1 << std::endl << "normal:\n"<< facets.first.at(i)->getNormal() <<"\noffset: "<<facets.first.at(i)->getScalar() << std::endl;
		}
}
