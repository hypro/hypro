/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/**
 * Example file for polytope size.
 * Compute the size and perform the executable with massif-valgrind
 *
 */

#include <hypro/datastructures/Halfspace.h>
#include <hypro/representations/GeometricObjectBase.h>

using namespace hypro;

int main() {
    typedef double Number;
    unsigned dim = 4;
    unsigned amountOfFacets = 500;

    std::cout << "Example_massif with dimension " << dim << " and facets from "
              << amountOfFacets << std::endl;

    HPolytope<Number> test_massif, test_massif2, test_massif3, test_massif4;
    std::vector<vector_t<Number>> directions =
            computeTemplate<Number>(dim, amountOfFacets);

    for (vector_t<Number> direction: directions) {
        test_massif.insert(Halfspace<Number>(direction, 1));
    }

    double sizeOfHPolytope = test_massif.sizeOfHPolytopeT();
    double size = test_massif.size();

    std::cout << "Size of test_massif before reduction is " << sizeOfHPolytope
              << " and amount of facets is " << size << std::endl;

    return 0;
}
