
#include "hypro/representations/GeometricObjectBase.h"
#include "hypro/util/plotting/Plotter.h"
#include <carl/numbers/numbers.h>

using namespace hypro;

int main(int argc, char **argv) {
  using Number = mpq_class;

  // plotting
  hypro::Plotter<Number> &plotter = hypro::Plotter<Number>::getInstance();
  plotting::gnuplotSettings settings = plotter.settings();
  settings.keepAspectRatio = false;
  settings.linewidth = 1.5;
  plotter.updateSettings(settings);
  plotter.setFilename("example_sf");
  std::vector<Point<Number>> points;

  /*
  vector_t<Number> a = vector_t<Number>(3);
  vector_t<Number> b = vector_t<Number>(3);
  a << 6,-6,7;
  b << -3,2,-6;
  std::cout << "Scalar projection a on b: " << scalarProjection(a,b) <<
  std::endl; std::cout << "Scalar projection b on a: " << scalarProjection(b,a)
  << std::endl;
  */

  matrix_t<Number> matrix = matrix_t<Number>(4, 2);
  vector_t<Number> distances = vector_t<Number>(4);
  matrix << 0, 1, 1, 0, 0, -1, -1, 0;
  distances << 1, carl::rationalize<Number>(5), carl::rationalize<Number>(.5),
      -4;

  /*
  matrix_t<Number> matrix2 = matrix_t<Number>(3,2);
  vector_t<Number> distances2 = vector_t<Number>(3);
  matrix2 << 1,1,
          -1,1,
          0,-1,
  distances2 << 1,1,0;
  vector_t<Number> distances3 = vector_t<Number>(4);
  distances3 <<
  carl::rationalize<Number>(1.5),carl::rationalize<Number>(1.5),carl::rationalize<Number>(-0.5),carl::rationalize<Number>(-0.5);

  vector_t<Number> shift = vector_t<Number>(2);
  shift <<
  Number(-762609227)/Number(1554758872579),Number(-357301353556)/Number(3642215632579);
  matrix_t<Number> trafoMatrix = matrix_t<Number>(2,2);
  //trafoMatrix << 1,0,0,1;
  trafoMatrix << 1, Number(35583997055767)/Number(3558399705576699), 0, 1;
  vector_t<Number> dir = vector_t<Number>(2);
  dir << 1,0;

  std::cout << "Trafo: " << trafoMatrix << " + " << shift << std::endl;
  */

  // matrix_t<Number> linearMap = matrix_t<Number>(2,2);
  // linearMap << -1,-4,4,-1;
  // Number timestep = carl::rationalize<Number>(0.01);
  //
  //	//linearMap = linearMap*timestep;
  // matrix_t<Number> exponential = linearMap.exp();

  /*
  matrix_t<Number> invariant = matrix_t<Number>(4,2);
  vector_t<Number> invariantConstants = vector_t<Number>(4);
  invariant << 1,0,-1,0,0,1,0,-1;
  invariantConstants << 10,10,carl::rationalize<Number>(0.4),
  carl::rationalize<Number>(0.4);
  */

  // unsigned id =
  // plotter.addObject(HPolytope<Number>(invariant,invariantConstants).vertices());
  // plotter.setObjectColor(id, plotting::colors[plotting::red]);

  // std::cout << "Invariant: " << invariant << " <= " << invariantConstants <<
  // std::endl;

  SupportFunction<Number> poly1(matrix, distances);
  // SupportFunctionContent<Number> poly2(SF_TYPE::POLY, matrix2, distances2);
  // SupportFunction<Number> poly3(matrix, distances3);
  SupportFunction<Number> ball(SF_TYPE::INFTY_BALL,
                               carl::rationalize<Number>(.5), 2);
  // SupportFunction<Number> shifted = poly1.linearTransformation(trafoMatrix,
  // shift);

  // HPolytope<Number> real(matrix, distances);
  // auto trafo = real.linearTransformation(trafoMatrix, shift);

  // for(unsigned i = 0; i < 9; ++i){
  //	shifted = shifted.linearTransformation(trafoMatrix, shift);
  //	trafo = trafo.linearTransformation(trafoMatrix, shift);
  //}

  SupportFunction<Number> rounded1 = poly1.minkowskiSum(ball);

  // SupportFunction<Number> intersectedInvariant =
  // poly1.intersectHalfspaces(invariant, invariantConstants); std::pair<bool,
  // SupportFunction<Number>> intersectionPair =
  // rounded1.satisfiesHalfspaces(invariant, invariantConstants);
  // SupportFunction<Number> intersection =
  // rounded1.intersectHalfspaces(invariant, invariantConstants);

  // SupportFunctionContent<Number> rounded2 = poly2.minkowskiSum(ball);
  // SupportFunctionContent<Number> rounded = ball;
  // SupportFunction<Number> unionRes = poly1.unite(poly3);
  // SupportFunction<Number> intersectionRes = poly1.intersect(poly3);

  // rounded1.print();
  // intersectedInvariant.second.print();

  // create array holding equaly distributed directions
  int resolution = 180;
  if (argc == 2) {
    resolution = std::stoi(argv[1]);
  }

  matrix_t<Number> evaldirections = matrix_t<Number>(resolution, 2);
  for (int pos = 0; pos < resolution; ++pos) {
    double angle = pos * (360 / resolution);
    evaldirections(pos, 0) =
        carl::rationalize<Number>(cos(angle * 3.141592654 / 180));
    evaldirections(pos, 1) =
        carl::rationalize<Number>(sin(angle * 3.141592654 / 180));
    // std::cout << "angle: " << angle <<  " . " <<
    // carl::toDouble(evaldirections(pos,0)) << ", " <<
    // carl::toDouble(evaldirections(pos,1)) << std::endl;
  }

  // std::cout << "evaldirections " << evaldirections << std::endl << std::endl;

  // vector_t<Number> result1 = rounded1.multiEvaluate(evaldirections);
  std::vector<EvaluationResult<Number>> ballEval =
      ball.multiEvaluate(evaldirections);
  std::vector<EvaluationResult<Number>> polyBoxEval =
      poly1.multiEvaluate(evaldirections);
  std::vector<EvaluationResult<Number>> trafoed;
  std::vector<EvaluationResult<Number>> multiEvaledVerify;
  std::vector<EvaluationResult<Number>> rounded1Eval =
      rounded1.multiEvaluate(evaldirections);
  // std::vector<EvaluationResult<Number>> rounded1IntersectEval =
  // intersectionPair.second.multiEvaluate(evaldirections);

  // for(unsigned rowIndex = 0; rowIndex < evaldirections.rows(); ++rowIndex){
  //	polyBox.push_back(poly1.evaluate(evaldirections.row(rowIndex)));
  //}
  // std::cout << "Eval: Trafoed." << std::endl;
  // for(unsigned rowIndex = 0; rowIndex < evaldirections.rows(); ++rowIndex){
  //	trafoed.push_back(shifted.evaluate(evaldirections.row(rowIndex)));
  //}
  // std::cout << "Eval: Trafoed END." << std::endl;

  // multiEvaledVerify = shifted.multiEvaluate(evaldirections);

  // std::vector<EvaluationResult<Number>> withInvariant =
  // intersectionPair.second.multiEvaluate(evaldirections); vector_t<Number>
  // result2 = rounded2.multiEvaluate(evaldirections);

  // vector_t<Number> sf1 = poly1.multiEvaluate(evaldirections);
  // vector_t<Number> sf2 = poly2.multiEvaluate(evaldirections);
  // vector_t<Number> sf3 = ball.multiEvaluate(evaldirections);
  // vector_t<Number> sf4 = unionRes.multiEvaluate(evaldirections);
  // vector_t<Number> sf5 = poly3.multiEvaluate(evaldirections);
  // vector_t<Number> sf6 = intersectionRes.multiEvaluate(evaldirections);
  // std::cout << result << std::endl;

  /*
  for(int i = 0; i < resolution; ++i) {
          //std::cout << "Calculate intersection between " << i << " and " <<
  ((i-1+resolution)%resolution) << std::endl; matrix_t<Number> matr =
  matrix_t<Number>(2,2); matr.row(0) = evaldirections.row(i); matr.row(1) =
  evaldirections.row(((i-1+resolution)%resolution)); vector_t<Number> vec =
  vector_t<Number>(2); vec(0) = result1(i); vec(1) =
  result1(((i-1+resolution)%resolution)); Point<Number> res =
  Point<Number>(matr.colPivHouseholderQr().solve(vec));
          //std::cout << "solve " << matr << " = " << vec << std::endl << " => "
  << res << std::endl << std::endl; points.push_back(res);
  }
  plotter.addObject(points);
  */
  {
    HPolytope<Number> tmp;
    for (int i = 0; i < resolution; ++i) {
      tmp.insert(Halfspace<Number>(evaldirections.row(i),
                                   polyBoxEval[i].supportValue));
    }
    unsigned original = plotter.addObject(tmp.vertices());
    plotter.setObjectColor(original, plotting::colors[plotting::green]);
  }

  {
    HPolytope<Number> tmp;
    for (int i = 0; i < resolution; ++i) {
      tmp.insert(
          Halfspace<Number>(evaldirections.row(i), ballEval[i].supportValue));
    }
    unsigned sf = plotter.addObject(tmp.vertices());
    plotter.setObjectColor(sf, plotting::colors[plotting::orange]);
  }
  //{
  // HPolytope<Number> tmp;
  // for(int i = 0; i < resolution; ++i) {
  //	tmp.insert(Halfspace<Number>(evaldirections.row(i),
  //multiEvaledVerify[i].supportValue));
  //}
  // unsigned sf = plotter.addObject(tmp.vertices());
  // plotter.setObjectColor(sf, plotting::colors[plotting::lila]);
  //}

  {
    HPolytope<Number> tmp;
    for (int i = 0; i < resolution; ++i) {
      tmp.insert(Halfspace<Number>(evaldirections.row(i),
                                   rounded1Eval[i].supportValue));
    }
    unsigned sf = plotter.addObject(tmp.vertices());
    plotter.setObjectColor(sf, plotting::colors[plotting::blue]);
    // std::cout << "Object: " << std::endl << tmp << std::endl;
    // std::cout << "Number vertices: " << tmp.vertices().size() << std::endl;
  }

  /*
  {
  HPolytope<Number> tmp;
  for(int i = 0; i < resolution; ++i) {
          tmp.insert(Halfspace<Number>(evaldirections.row(i),
  rounded1IntersectEval[i].supportValue));
  }
  unsigned sf = plotter.addObject(tmp.vertices());
  plotter.setObjectColor(sf, plotting::colors[plotting::green]);
  std::cout << "Object: " << std::endl << tmp << std::endl;
  std::cout << "Number vertices: " << tmp.vertices().size() << std::endl;
  //std::cout << intersection << std::endl;
  }
  */

  /*
  points.erase(points.begin(), points.end());
  for(int i = 0; i < resolution; ++i) {
          //std::cout << "Calculate intersection between " << i << " and " <<
  ((i-1+resolution)%resolution) << std::endl; matrix_t<Number> matr =
  matrix_t<Number>(2,2); matr.row(0) = evaldirections.row(i); matr.row(1) =
  evaldirections.row(((i-1+resolution)%resolution)); vector_t<Number> vec =
  vector_t<Number>(2); vec(0) = result2(i); vec(1) =
  result2(((i-1+resolution)%resolution)); Point<Number> res =
  Point<Number>(matr.colPivHouseholderQr().solve(vec));
          //std::cout << "solve " << matr << " = " << vec << std::endl << " => "
  << res << std::endl << std::endl; points.push_back(res);
  }
  //plotter.addObject(points);
  */

  /*
  points.erase(points.begin(), points.end());
  for(int i = 0; i < resolution; ++i) {
          //std::cout << "Calculate intersection between " << i << " and " <<
  ((i-1+resolution)%resolution) << std::endl; matrix_t<Number> matr =
  matrix_t<Number>(2,2); matr.row(0) = evaldirections.row(i); matr.row(1) =
  evaldirections.row(((i-1+resolution)%resolution)); vector_t<Number> vec =
  vector_t<Number>(2); vec(0) = sf1(i); vec(1) =
  sf1(((i-1+resolution)%resolution)); Point<Number> res =
  Point<Number>(matr.colPivHouseholderQr().solve(vec));
          //std::cout << "solve " << matr << " = " << vec << std::endl << " => "
  << res << std::endl << std::endl; points.push_back(res);
  }
  plotter.addObject(points);
  */

  /*
  points.erase(points.begin(), points.end());
  for(int i = 0; i < resolution; ++i) {
          //std::cout << "Calculate intersection between " << i << " and " <<
  ((i-1+resolution)%resolution) << std::endl; matrix_t<Number> matr =
  matrix_t<Number>(2,2); matr.row(0) = evaldirections.row(i); matr.row(1) =
  evaldirections.row(((i-1+resolution)%resolution)); vector_t<Number> vec =
  vector_t<Number>(2); vec(0) = sf3(i); vec(1) =
  sf3(((i-1+resolution)%resolution)); Point<Number> res =
  Point<Number>(matr.colPivHouseholderQr().solve(vec));
          //std::cout << "solve " << matr << " = " << vec << std::endl << " => "
  << res << std::endl << std::endl; points.push_back(res);
  }
  plotter.addObject(points);
  */

  /*
  SupportFunction<Number> res = rounded1.linearTransformation(exponential);
  //SupportFunction<Number> res = rounded1.minkowskiSum(ball);
  res.print();

  for(unsigned iteration = 0; iteration < 20; ++iteration) {
          std::cout << "Example: res.multiEvaluate(evaldirections)" <<
  std::endl; vector_t<Number> tmp = res.multiEvaluate(evaldirections);
          points.erase(points.begin(), points.end());
          for(int i = 0; i < resolution; ++i) {
                  //std::cout << "Calculate intersection between " << i << " and
  " << ((i-1+resolution)%resolution) << std::endl; matrix_t<Number> matr =
  matrix_t<Number>(2,2); matr.row(0) = evaldirections.row(i); matr.row(1) =
  evaldirections.row(((i-1+resolution)%resolution)); vector_t<Number> vec =
  vector_t<Number>(2); vec(0) = tmp(i); vec(1) =
  tmp(((i-1+resolution)%resolution)); Point<Number> res =
  Point<Number>(matr.colPivHouseholderQr().solve(vec));
                  //std::cout << "solve " << matr << " = " << vec << std::endl
  << " => " << res << std::endl << std::endl; points.push_back(res);
          }
          std::cout << "iteration: " << iteration << std::endl;
          res = res.linearTransformation(exponential);
          //res = res.minkowskiSum(ball);
          res.print();
          plotter.addObject(points);
  }
  */
  /*
  points.erase(points.begin(), points.end());
  for(int i = 0; i < resolution; ++i) {
          //std::cout << "Calculate intersection between " << i << " and " <<
  ((i-1+resolution)%resolution) << std::endl; matrix_t<Number> matr =
  matrix_t<Number>(2,2); matr.row(0) = evaldirections.row(i); matr.row(1) =
  evaldirections.row(((i-1+resolution)%resolution)); vector_t<Number> vec =
  vector_t<Number>(2); vec(0) = sf4(i); vec(1) =
  sf4(((i-1+resolution)%resolution)); Point<Number> res =
  Point<Number>(matr.colPivHouseholderQr().solve(vec));
          //std::cout << "solve " << matr << " = " << vec << std::endl << " => "
  << res << std::endl << std::endl; points.push_back(res);
  }
  plotter.addObject(points);
  */
  /*
  points.erase(points.begin(), points.end());
  for(int i = 0; i < resolution; ++i) {
          //std::cout << "Calculate intersection between " << i << " and " <<
  ((i-1+resolution)%resolution) << std::endl; matrix_t<Number> matr =
  matrix_t<Number>(2,2); matr.row(0) = evaldirections.row(i); matr.row(1) =
  evaldirections.row(((i-1+resolution)%resolution)); vector_t<Number> vec =
  vector_t<Number>(2); vec(0) = sf5(i); vec(1) =
  sf5(((i-1+resolution)%resolution)); Point<Number> res =
  Point<Number>(matr.colPivHouseholderQr().solve(vec));
          //std::cout << "solve " << matr << " = " << vec << std::endl << " => "
  << res << std::endl << std::endl; points.push_back(res);
  }
  plotter.addObject(points);
  */

  plotter.plot2d();
}
