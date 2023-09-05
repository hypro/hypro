
/*
 * File:   example_pca.cpp
 * Author: Simon Froitzheim
 *
 * Created on April 20, 2016, 3:43 PM
 */

#include "hypro/config.h"
#include "hypro/representations/GeometricObjectBase.h"
#include "hypro/util/plotting/Plotter.h"
#include <chrono>

using namespace hypro;
using namespace carl;

int main() {
  typedef mpq_class Number;
  typedef std::chrono::high_resolution_clock clock;
  typedef std::chrono::microseconds timeunit;
  const int runs = 50;
  Plotter<Number> &plotter = Plotter<Number>::getInstance();

  hypro::VPolytope<Number> vpolytope;
  hypro::VPolytope<Number> vpolytope2;
  hypro::VPolytope<Number> vpolytope3;
  hypro::VPolytope<Number> vpolytope4;
  hypro::VPolytope<Number> vpolytope5;

  // first vpolytope (simple triangle 2D)
  vector_t<Number> p1 = vector_t<Number>(2);
  p1(0) = 1;
  p1(1) = 2;
  vector_t<Number> p2 = vector_t<Number>(2);
  p2(0) = 3;
  p2(1) = 2;
  vector_t<Number> p3 = vector_t<Number>(2);
  p3(0) = 1;
  p3(1) = 4;
  typename hypro::VPolytope<Number>::pointVector points;
  points.push_back(Point<Number>(p1));
  points.push_back(Point<Number>(p2));
  points.push_back(Point<Number>(p3));
  // plotter.addPoints(points);
  vpolytope = VPolytope<Number>(points);

  // second vpolytope (ambiguous box)
  vector_t<Number> p4 = vector_t<Number>(2);
  p4(0) = 1;
  p4(1) = 3;
  vector_t<Number> p5 = vector_t<Number>(2);
  p5(0) = 3;
  p5(1) = 1;
  vector_t<Number> p6 = vector_t<Number>(2);
  p6(0) = 5;
  p6(1) = 3;
  vector_t<Number> p7 = vector_t<Number>(2);
  p7(0) = 3;
  p7(1) = 5;
  typename hypro::VPolytope<Number>::pointVector points2;
  points2.push_back(Point<Number>(p4));
  points2.push_back(Point<Number>(p5));
  points2.push_back(Point<Number>(p6));
  points2.push_back(Point<Number>(p7));
  // plotter.addPoints(points2);
  vpolytope2 = VPolytope<Number>(points2);

  // third  vpolytope (point cloud)
  vector_t<Number> p8 = vector_t<Number>(2);
  p8(0) = 2;
  p8(1) = 1;
  vector_t<Number> p9 = vector_t<Number>(2);
  p9(0) = 3;
  p9(1) = 1;
  vector_t<Number> p10 = vector_t<Number>(2);
  p10(0) = 2;
  p10(1) = 2;
  vector_t<Number> p11 = vector_t<Number>(2);
  p11(0) = 1;
  p11(1) = 2;
  vector_t<Number> p12 = vector_t<Number>(2);
  p12(0) = 1;
  p12(1) = 3;
  vector_t<Number> p13 = vector_t<Number>(2);
  p13(0) = 3;
  p13(1) = 3;
  vector_t<Number> p14 = vector_t<Number>(2);
  p14(0) = 2;
  p14(1) = 4;
  vector_t<Number> p15 = vector_t<Number>(2);
  p15(0) = 4;
  p15(1) = 4;
  vector_t<Number> p16 = vector_t<Number>(2);
  p16(0) = 5;
  p16(1) = 4;
  vector_t<Number> p17 = vector_t<Number>(2);
  p17(0) = 4;
  p17(1) = 5;
  typename hypro::VPolytope<Number>::pointVector points3;
  points3.push_back(Point<Number>(p8));
  points3.push_back(Point<Number>(p9));
  points3.push_back(Point<Number>(p10));
  points3.push_back(Point<Number>(p11));
  points3.push_back(Point<Number>(p12));
  points3.push_back(Point<Number>(p13));
  points3.push_back(Point<Number>(p14));
  points3.push_back(Point<Number>(p15));
  points3.push_back(Point<Number>(p16));
  points3.push_back(Point<Number>(p17));
  // plotter.addPoints(points3);
  vpolytope3 = VPolytope<Number>(points3);

  // fourth vpolytope (stretched box)
  vector_t<Number> p18 = vector_t<Number>(2);
  p18(0) = 1;
  p18(1) = 4;
  vector_t<Number> p19 = vector_t<Number>(2);
  p19(0) = 2;
  p19(1) = 5;
  vector_t<Number> p20 = vector_t<Number>(2);
  p20(0) = 4;
  p20(1) = 1;
  vector_t<Number> p21 = vector_t<Number>(2);
  p21(0) = 5;
  p21(1) = 2;
  typename hypro::VPolytope<Number>::pointVector points4;
  points4.push_back(Point<Number>(p18));
  points4.push_back(Point<Number>(p19));
  points4.push_back(Point<Number>(p20));
  points4.push_back(Point<Number>(p21));
  // plotter.addPoints(points4);
  vpolytope4 = VPolytope<Number>(points4);

  // fifth vpolytope(line)
  vector_t<Number> p22 = vector_t<Number>(2);
  p22(0) = 3;
  p22(1) = 1;
  vector_t<Number> p23 = vector_t<Number>(2);
  p23(0) = 2;
  p23(1) = 2;
  vector_t<Number> p24 = vector_t<Number>(2);
  p24(0) = 1;
  p24(1) = 3;
  typename hypro::VPolytope<Number>::pointVector points5;
  points5.push_back(Point<Number>(p22));
  points5.push_back(Point<Number>(p23));
  points5.push_back(Point<Number>(p24));
  // plotter.addPoints(points5);
  vpolytope5 = VPolytope<Number>(points5);

  std::set<long int> results;
  std::set<long int> results2;
  std::set<long int> results3;
  std::set<long int> results4;
  std::set<long int> results5;
  HPolytope<Number> result;
  HPolytope<Number> result2;
  HPolytope<Number> result3;
  HPolytope<Number> result4;
  HPolytope<Number> result5;
  for (int index = 0; index < runs; ++index) {
    long int testresult;

    // 1st polytope (triangle)
    clock::time_point start = clock::now();

    result = Converter<Number>::toHPolytope(vpolytope, CONV_MODE::OVER);

    std::cout
        << "Total time(triangle): "
        << std::chrono::duration_cast<timeunit>(clock::now() - start).count() /
               1000
        << std::endl;
    testresult =
        std::chrono::duration_cast<timeunit>(clock::now() - start).count() /
        1000;
    results.insert(testresult);

    // 2nd polytope (ambiguous box)
    start = clock::now();

    result2 = Converter<Number>::toHPolytope(vpolytope2, CONV_MODE::OVER);

    std::cout
        << "Total time(ambiBox): "
        << std::chrono::duration_cast<timeunit>(clock::now() - start).count() /
               1000
        << std::endl;
    testresult =
        std::chrono::duration_cast<timeunit>(clock::now() - start).count() /
        1000;
    results2.insert(testresult);

    // 3rd polytope (point cloud)
    start = clock::now();

    result3 = Converter<Number>::toHPolytope(vpolytope3, CONV_MODE::OVER);

    std::cout
        << "Total time(pointCloud): "
        << std::chrono::duration_cast<timeunit>(clock::now() - start).count() /
               1000
        << std::endl;
    testresult =
        std::chrono::duration_cast<timeunit>(clock::now() - start).count() /
        1000;
    results3.insert(testresult);

    // 4th polytope (stretched box)
    start = clock::now();

    result4 = Converter<Number>::toHPolytope(vpolytope4, CONV_MODE::OVER);

    std::cout
        << "Total time(stretchBox): "
        << std::chrono::duration_cast<timeunit>(clock::now() - start).count() /
               1000
        << std::endl;
    testresult =
        std::chrono::duration_cast<timeunit>(clock::now() - start).count() /
        1000;
    results4.insert(testresult);

    // 5th polytope (line)
    start = clock::now();

    result5 = Converter<Number>::toHPolytope(vpolytope5, CONV_MODE::OVER);

    std::cout
        << "Total time(line): "
        << std::chrono::duration_cast<timeunit>(clock::now() - start).count() /
               1000
        << std::endl;
    testresult =
        std::chrono::duration_cast<timeunit>(clock::now() - start).count() /
        1000;
    results5.insert(testresult);
  }

  double avgTri = 0;
  double avgAmbiBox = 0;
  double avgCloud = 0;
  double avgStretch = 0;
  double avgLine = 0;

  for (auto resultIt = results.begin(); resultIt != results.end(); ++resultIt) {
    avgTri += double((*resultIt) / double(runs));
  }

  for (auto resultIt = results2.begin(); resultIt != results2.end();
       ++resultIt) {
    avgAmbiBox += double((*resultIt) / double(runs));
  }

  for (auto resultIt = results3.begin(); resultIt != results3.end();
       ++resultIt) {
    avgCloud += double((*resultIt) / double(runs));
  }

  for (auto resultIt = results4.begin(); resultIt != results4.end();
       ++resultIt) {
    avgStretch += double((*resultIt) / double(runs));
  }

  for (auto resultIt = results5.begin(); resultIt != results5.end();
       ++resultIt) {
    avgLine += double((*resultIt) / double(runs));
  }

  std::cout << "AVGTri: " << avgTri << std::endl;
  std::cout << "AVGAmbiBox: " << avgAmbiBox << std::endl;
  std::cout << "AVGCloud: " << avgCloud << std::endl;
  std::cout << "AVGStretch: " << avgStretch << std::endl;
  std::cout << "AVGLine: " << avgLine << std::endl;

  // plotter.addObject(result.vertices());
  // plotter.addObject(result2.vertices());
  // plotter.addObject(result3.vertices());
  // plotter.addObject(result4.vertices());
  // plotter.addObject(result5.vertices());
  plotter.plot2d();
  plotter.plotTex();

  return 0;
}
