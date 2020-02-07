#include <representations/GeometricObject.h>
#include <util/plotting/Plotter.h>
#include <util/VariablePool.h>
#include <carl/interval/Interval.h>

int main()
{

    using Number = double;
    using Matrix = hypro::matrix_t<Number>;
    using Vector = hypro::vector_t<Number>;

    int dimension = 2;
    int j = 1; // variable x_j

    // original segment (-1*pc1 <= 0 and -2*time + pc1 <= 0 and -2 + time <= 0 and -7/2 + pc1 <= 0)
    Matrix constraints = Matrix::Zero(4,dimension);
    constraints << 0,-1,-2,1,1,0,0,1;
    Vector constants = Vector::Zero(4);
    constants << 0,0,2,3.5;

    hypro::CarlPolytope<Number> c1(constraints,constants);

    std::cout << "Matrix: " << c1.matrix() << std::endl;
    std::cout << "Vector: " << c1.vector() << std::endl;

    // intersection halfspace
    double boundary = 3.5;
    Matrix halfspaceMatrix = Matrix::Zero(2,dimension);
    Vector halfspaceVector = Vector(2);
    halfspaceMatrix(0,j) = 1;
    halfspaceMatrix(1,j) = -1;
    halfspaceVector(0) = boundary;
    halfspaceVector(1) = -boundary;

    auto newStatePair = c1.satisfiesHalfspaces(halfspaceMatrix, halfspaceVector);
    if(newStatePair.first == hypro::CONTAINMENT::NO || boundary==0) {
        // stop
    } else {

        auto carlPolytope = newStatePair.second;

        std::cout << "carl polytope is " << carlPolytope << " and " << carlPolytope.empty() << std::endl;
        std::cout << "carl polytope matrix is " << carlPolytope.matrix() << std::endl;
        std::cout << "carl polytope vector is " << carlPolytope.vector() << std::endl;

        carlPolytope.make_rectangular();
        std::vector<carl::Interval<Number>> carlIntervalVector = carlPolytope.getIntervals();
        carl::Interval<Number> carlInterval = carlIntervalVector[0];

    }

    return 0;
}
