/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include <random>
#include <hypro/representations/GeometricObjectBase.h>
#include <hypro/util/plotting/Plotter.h>

using namespace hypro;

int main() {

    // plotter
    hypro::Plotter<double> &plotter = hypro::Plotter<double>::getInstance();
    plotter.setFilename("sfHPolyComparison");

    std::mt19937 generator;
    std::uniform_int_distribution<int> dist =
            std::uniform_int_distribution<int>(0, 10);

    std::size_t dimension = 2;
    matrix_t<double> constraints =
            matrix_t<double>::Zero(2 * dimension, dimension);
    vector_t<double> constants = vector_t<double>::Ones(2 * dimension);
    for (std::size_t i = 0; i < dimension; ++i) {
        constraints(2 * i, i) = 1;
        constraints(2 * i + 1, i) = -1;
    }

    // SupportFunctionT<double,Converter<double>,NoTrafoReduction> sf =
    // SupportFunctionT<double,Converter<double>,NoTrafoReduction>(constraints,
    // constants);
    SupportFunction<double> sf = SupportFunction<double>(constraints, constants);
    HPolytope<double> p = HPolytope<double>(constraints, constants);

    matrix_t<double> matrix = matrix_t<double>(dimension, dimension);
    vector_t<double> vector = vector_t<double>::Zero(dimension);
    vector_t<double> direction = vector_t<double>(dimension);
    // for(std::size_t row = 0; row < dimension; ++row) {
    //    for(std::size_t col = 0; col < dimension; ++col) {
    //        matrix(row,col) = dist(generator);
    //    }
    //    vector(row) = dist(generator);
    //    direction(row) = dist(generator);
    //}
    matrix << cos(30 * 3.141592654 / 180), -sin(30 * 3.141592654 / 180),
            sin(30 * 3.141592654 / 180), cos(30 * 3.141592654 / 180);

    std::cout << "Trafo matrix: " << matrix << ", trafo vector " << vector
              << std::endl;

    for (std::size_t i = 0; i < 10; ++i) {
        std::cout << "Trafo " << i << std::endl;
        sf = sf.affineTransformation(matrix, vector);
        p = p.affineTransformation(matrix, vector);
    }

    Eigen::Index resolution = 360;
    matrix_t<double> evaldirections = matrix_t<double>(resolution, 2);
    for (int pos = 0; pos < resolution; ++pos) {
        double angle = pos * (360 / resolution);
        evaldirections(pos, 0) = cos(angle * 3.141592654 / 180);
        evaldirections(pos, 1) = sin(angle * 3.141592654 / 180);
    }

    std::vector<EvaluationResult<double>> evalResults =
            sf.multiEvaluate(evaldirections);

    {
        HPolytope<double> tmp;
        for (int i = 0; i < resolution; ++i) {
            tmp.insert(Halfspace<double>(evaldirections.row(i),
                                         evalResults[i].supportValue));
        }
        unsigned original = plotter.addObject(tmp.vertices());
        plotter.setObjectColor(original, plotting::colors[plotting::green]);
    }

    unsigned poly = plotter.addObject(p.vertices());
    plotter.setObjectColor(poly, plotting::colors[plotting::red]);

    plotter.plot2d();

    return 0;
}
