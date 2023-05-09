
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

int main() {
    using Number = double;
    using Poly = HPolytope<Number>;
    using Box = Box<Number>;
    using Point = Point<Number>;
    using Matrix = matrix_t<Number>;
    using Vector = vector_t<Number>;

    Plotter<Number> &plt = Plotter<Number>::getInstance();

    Box i = Box(std::make_pair(Point({0, 0}), Point({1, 1})));

    Poly init = Converter<Number>::toHPolytope(i);
    Matrix trafo = Matrix(2, 2);
    Vector offset = Vector(2);
    trafo << 1, 1, 0, 1;
    offset << 2, 1;

    Poly deltaSet = init.affineTransformation(trafo, offset);

    Box bloatbox = Box(std::make_pair(Point({-0.1, -0.1}), Point({0.1, 0.1})));

    Poly bloated =
            deltaSet.minkowskiSum(Converter<Number>::toHPolytope(bloatbox));

    Poly firstSegment = init.unite(bloated);

    Poly secondSegment = firstSegment.affineTransformation(trafo, offset);
    Poly thirdSegment = secondSegment.affineTransformation(trafo, offset);

    Poly guard = Converter<Number>::toHPolytope(
            Box(std::make_pair(Point({6, 1}), Point({10, 4}))));

    Poly secondIntersected =
            secondSegment.satisfiesHalfspaces(guard.matrix(), guard.vector()).second;
    Poly thirdIntersected =
            thirdSegment.satisfiesHalfspaces(guard.matrix(), guard.vector()).second;

    Poly guardUnion = secondIntersected.unite(thirdIntersected);

    unsigned initId = plt.addObject(i.vertices());

    plt.setFilename("init");
    plt.plot2d();

    unsigned deltaId = plt.addObject(deltaSet.vertices());
    unsigned bloatId = plt.addObject(bloated.vertices());

    plt.setFilename("bloat");
    plt.plot2d();

    unsigned firstSegmentId = plt.addObject(firstSegment.vertices());

    plt.setFilename("firstSeg");
    plt.plot2d();

    unsigned secondSegmentId = plt.addObject(secondSegment.vertices());
    unsigned thirdSegmentId = plt.addObject(thirdSegment.vertices());

    plt.setFilename("segments");
    plt.plot2d();

    unsigned guardId = plt.addObject(guard.vertices());

    plt.setFilename("guard");
    plt.plot2d();

    unsigned secondGuardId = plt.addObject(secondIntersected.vertices());
    unsigned thirdGuardId = plt.addObject(thirdIntersected.vertices());

    plt.setObjectColor(secondGuardId, plotting::colors[plotting::green]);
    plt.setObjectColor(thirdGuardId, plotting::colors[plotting::green]);

    plt.setFilename("guardIt");
    plt.plot2d();

    unsigned guardUnionId = plt.addObject(guardUnion.vertices());

    plt.setObjectColor(secondGuardId, plotting::colors[plotting::blue]);
    plt.setObjectColor(thirdGuardId, plotting::colors[plotting::blue]);
    plt.setObjectColor(guardUnionId, plotting::colors[plotting::green]);

    plt.setFilename("final");
    plt.plot2d();

    plt.plot2d();
    plt.plotTex();

    return 0;
}
