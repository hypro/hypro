// implement here the Starset.contains(Point) method using SAT solving, but first try to eliminate the variables/equations with Gauss-elimination
// Gauss elimination is not numerically stable
// try to look if Eigen provides already some elimination method to replace Gauss with
// Stefan proposes that glpk can handle also equality constraints (not only inequalities) -> check if all solvers support equality constraints
// -> if all solvers support then extend the interface
// Gauss elimination can be made stable using partial pivoting (look at wikipedia) -> dominant diagonal matrix does not need partial pivoting
// continue CEGAR using tree and 4 approach to go one layer back:
// LP solving, SGD, vertex2vertex, SGD without RELU

#include "hypro/neuralnets/network/NeuralNetwork.h"
#include "hypro/parser/neuralnets/nnet/NNet.h"
#include "hypro/neuralnets/reachability/ReachNN.h"
#include "hypro/neuralnets/reachability_tree/ReachabilityTree.h"
#include "hypro/representations/GeometricObjectBase.h"
// #include "hypro/representations/Starset/Starset.h"
#include "hypro/util/plotting/Plotter.h"

#include "hypro/parser/representations/parseHPolytope.tpp"

#include <chrono>
#include <iomanip>
#include <iostream>
#include <vector>

typedef double Number;

int main(int argc, char* argv[]) {
    
    hypro::matrix_t<Number> A = hypro::matrix_t<Number>(2, 3);
    A << 1, 2, 3, 4, 5, 6;
    std::cout << "The matrix:\n" << A << std::endl;

    Eigen::FullPivLU<hypro::matrix_t<Number>> lu( A );
    hypro::matrix_t<Number> A_inv = A.inverse();
    std::cout << "The inverse:\n" << A_inv << std::endl;

    return 0;
}
