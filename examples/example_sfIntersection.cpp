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
using Number = double;
using Matrix = matrix_t<Number>;
using Vector = vector_t<Number>;

Number sandwichValue(const SupportFunction<Number> &obj, Vector a, Number b,
                     Vector direction, Number lambda) {
    Vector tmp = direction - lambda * a;
    std::cout << "Updated direction is " << tmp << std::endl;
    return obj.evaluate(tmp).supportValue + lambda * b;
}

Number lowerBound(const SupportFunction<Number> &obj, Vector a, Number b,
                  Vector direction, Number lambdaI, Number lambdaJ,
                  Number lambda) {
    return ((sandwichValue(obj, a, b, direction, lambdaJ) -
             sandwichValue(obj, a, b, direction, lambdaI)) /
            (lambdaJ - lambdaI)) *
           (lambda - lambdaI) +
           sandwichValue(obj, a, b, direction, lambdaI);
}

/*
Number fMinus(const std::vector<std::pair<Number,Number>>& samples, const
std::pair<Number,Number>& sample) { std::vector<Number> fMinusSampleValues;
        for(std::size_t i = 0; i < samples.size(); ++i) {
                for(std::size_t j = i+1; j < samples.size(); ++j) {
                        fMinusSampleValues.emplace_back(lowerBound(obj,a,b,direction,samples.at(i).first,
samples.at(j).first, sample.first));
                }
        }
        return std::max(-std::numeric_limits<Number>::infinity, )
}
*/

std::pair<Number, Number>
determineLowerBound(const SupportFunction<Number> &obj, Vector a, Number b,
                    Vector direction) {
    int i = 0;
    Number rLow = -std::numeric_limits<Number>::infinity();
    Number rUp = std::numeric_limits<Number>::infinity();
    std::vector<std::pair<Number, Number>> samples;
    samples.emplace_back(
            std::make_pair(0, sandwichValue(obj, a, b, direction, 0)));
    std::cout << "Lambda is: " << samples.back().first
              << ", f is: " << samples.back().second << std::endl;
    samples.emplace_back(
            std::make_pair(0.001, sandwichValue(obj, a, b, direction, 0.001)));
    std::cout << "Lambda is: " << samples.back().first
              << ", f is: " << samples.back().second << std::endl;

    // sample
    while (true) {
        samples.emplace_back(std::make_pair(
                2 * (samples.back().first),
                sandwichValue(obj, a, b, direction, 2 * (samples.back().first))));
        std::cout << "Lambda is: " << samples.back().first
                  << ", f is: " << samples.back().second << std::endl;
        std::cout << "Compare " << std::next(samples.rbegin(), 2)->second << " and "
                  << std::next(samples.rbegin(), 1)->second << " and "
                  << samples.rbegin()->second << std::endl;
        if (std::next(samples.rbegin(), 1)->second <=
            std::next(samples.rbegin(), 2)->second &&
            std::next(samples.rbegin(), 1)->second <= samples.rbegin()->second) {
            break;
        }
    }

    // tighten bounds

    rUp = samples.back().second;

    return std::make_pair(std::next(samples.rbegin(), 2)->second,
                          samples.rbegin()->second);
}

int main() {

    Plotter<Number> &plt = Plotter<Number>::getInstance();

    Matrix constraints = Matrix(3, 2);
    Vector constants = Vector(3);

    constraints << 1, 1, -1, 1, 0, -1;
    constants << 2, 2, 1;

    SupportFunction<Number> sf = SupportFunction<Number>(constraints, constants);

    Matrix hsNormal = Matrix(1, 2);
    Vector hsOffset = Vector(1);

    hsNormal << 1, 0.5;
    hsOffset << 1.5;

    sf.intersectHalfspaces(hsNormal, hsOffset);

    plt.addObject(sf.vertices());
    plt.addObject(Halfspace<Number>(Vector(hsNormal.row(0)), hsOffset(0)));

    Vector direction = Vector(2);
    direction << 1, 0;

    std::pair<Number, Number> lowerUpperBound =
            determineLowerBound(sf, Vector(hsNormal.row(0)), hsOffset(0), direction);

    plt.addObject(Halfspace<Number>(Vector(direction), lowerUpperBound.first));
    // plt.addObject(Halfspace<Number>(Vector(direction),lowerUpperBound.second));

    plt.plot2d();

    return 0;
}
