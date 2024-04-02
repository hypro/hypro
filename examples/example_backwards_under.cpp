
/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include <hypro/representations/GeometricObjectBase.h>
#include <hypro/util/plotting/Plotter.h>

using namespace hypro;

using Number = mpq_class; // double;


template <typename Number>
VPolytope<Number> getUnBloatedPolytope (const VPolytope<Number> & poly, const VPolytope<Number> &bloating);

int main() {
    using Poly = VPolytope<Number>;
    using Box = Box<Number>;
    using Point = Point<Number>;
    using Matrix = matrix_t<Number>;
    using Vector = vector_t<Number>;

    Plotter<Number> &plt = Plotter<Number>::getInstance();
    Box bloatbox = Box(std::make_pair(Point({-0.1, -0.1}), Point({0.1, 0.1})));
    

    std::vector<hypro::Point<Number>> points2 = {hypro::Point<Number>({-3, 4}), hypro::Point<Number>({2, 5}), hypro::Point<Number>({5, 2}), hypro::Point<Number>({0, -2}), hypro::Point<Number>({-5, -1})};
    Poly polytope = Poly(points2);
    
    // Box aux = Box(std::make_pair(Point({-2, -2}), Point({-1, -1})));
    // Poly polytope = Converter<Number>::toVPolytope(aux);

    // std::vector<hypro::Point<Number>> points2 = {hypro::Point<Number>({1, 0.5}), hypro::Point<Number>({2.5, 0.5}), hypro::Point<Number>({1.75, 2})};
    // Poly polytope = Poly(points2);
    

    plt.addObject(polytope.vertices(), plotting::colors[plotting::green]);

    Poly bloated = polytope.minkowskiSum(Converter<Number>::toVPolytope(bloatbox));
    bloated.removeRedundancy();
    plt.addObject(bloated.vertices(), plotting::colors[plotting::red]);

    HPolytope<Number> hpoly2 = Converter<Number>::toHPolytope(bloated);

    hypro::Point<Number> maxPoint = bloatbox.max();
    Number distance = maxPoint.distance(maxPoint.origin());
    // std::cout << "max point " << maxPoint << std::endl;
    // std::cout << "distance " << distance << std::endl;

    HPolytope<Number> bloatedH = Converter<Number>::toHPolytope(bloated);
    bloatedH.normalize();
    bloatedH.offsetAllToNegative(distance);
    plt.addObject(bloatedH.vertices());

    plt.setFilename("bloated");
    plt.plot2d();

    return 0;
}