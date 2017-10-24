/**
 * \example example_differenceBounds.cpp This example shows how to use a representation by difference Bounds.
 */


#include "representations/GeometricObject.h"
#include "datastructures/Halfspace.h"
#include "util/Plotter.h"

int main() {

    typedef int Number;
    std::cout << hypro::DifferenceBounds<Number>();
    return 0;
}