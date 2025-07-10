#include <iostream>

#include <hypro/representations/GeometricObjectBase.h>
#include <hypro/util/plotting/Plotter.h>
#include <hypro/algorithms/smtrat-fmplex/eliminate.h>

int main(int argc, char* argv[]) {
    // use rational arithmetic.
    typedef double Number;

    // get plotter reference.
    hypro::Plotter<Number> &plotter = hypro::Plotter<Number>::getInstance();

    smtrat::fmplex::EigenMat<Number> C = smtrat::fmplex::EigenMat<Number>(7, 3);
    C(0, 0) = -1;
    C(0, 1) = -1;
    C(0, 2) =  0;

    C(1, 0) = -1;
    C(1, 1) =  1;
    C(1, 2) =  0;

    C(2, 0) =  1;
    C(2, 1) =  1;
    C(2, 2) =  0;

    C(3, 0) =  1;
    C(3, 1) = -1;
    C(3, 2) =  0;

    C(4, 0) =  0;
    C(4, 1) =  0;
    C(4, 2) = -1;

    C(5, 0) =  1;
    C(5, 1) =  0;
    C(5, 2) = -1;

    C(6, 0) = -0.4585;
    C(6, 1) =  0;
    C(6, 2) =  1;

    smtrat::fmplex::EigenVec<Number> d = smtrat::fmplex::EigenVec<Number>(7);
    d[0] =  2.4142;
    d[1] =  1.4142;
    d[2] =  1.8284;
    d[3] =  1.4142;
    d[4] =  0;
    d[5] =  0;
    d[6] =  0.8778;

    std::vector<std::size_t> cols;
    cols.push_back(0);

    std::cout << "Input C = " << C << std::endl;
    std::cout << "Input d = " << d << std::endl;

    hypro::HPolytope<Number> input_poly = hypro::HPolytope<Number>(C, d);
    std::cout << "Input poly vertices = ";
    for(auto vertex : input_poly.vertices()) {
        std::cout << vertex << " ";
    }
    std::cout << std::endl;

    std::pair<smtrat::fmplex::EigenMat<Number>, smtrat::fmplex::EigenVec<Number>> result = smtrat::fmplex::eliminate_cols(C, d, cols);
    smtrat::fmplex::EigenMat<Number> new_C = result.first;
    smtrat::fmplex::EigenVec<Number> new_d = result.second;

    std::cout << "Resulting C = " << new_C << std::endl;
    std::cout << "Resulting d = " << new_d << std::endl;

    hypro::HPolytope<Number> proj_poly = hypro::HPolytope<Number>(new_C, new_d);
    std::cout << "Projected poly vertices = ";
    for(auto vertex : proj_poly.vertices()) {
        std::cout << vertex << " ";
    }
    std::cout << std::endl;

    
    plotter.addObject(proj_poly.vertices());
    plotter.setFilename("3d_example");
    plotter.plot2d();
    plotter.clear();

    /////////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////

    hypro::matrix_t<Number> boxC = hypro::matrix_t<Number>(4, 2);
    hypro::vector_t<Number> boxd = hypro::vector_t<Number>(4);

    boxC << -1, 0, 1, 0, 0, -1, 0, 1;
    boxd <<  0, 2, 1, 1;

    std::cout << "Input box C = " << boxC << std::endl;
    std::cout << "Input box d = " << boxd << std::endl;

    std::vector<std::size_t> projectDim;
    projectDim.push_back(0);

    std::pair<hypro::matrix_t<Number>, hypro::vector_t<Number>> projectedBox = smtrat::fmplex::eliminate_cols(boxC, boxd, projectDim);

    std::cout << "Projected C = " << projectedBox.first << std::endl;
    std::cout << "Projected d = " << projectedBox.second << std::endl;  

    hypro::HPolytope<Number> result2 = hypro::HPolytope<Number>(projectedBox.first, projectedBox.second);
    std::cout << result2 << std::endl;

    // plotter.addObject(result2.vertices());
    std::cout << "Projected poly vertices = ";
    for(auto vertex : result2.vertices()) {
        vertex.extend(0);   // extend it so it's now a 2D point
        // plotter.addPoint(vertex);
        std::cout << vertex << " ";
    }
    std::cout << std::endl;


    // plotter.setFilename("2d_example");
    // plotter.plot2d();

    return 0;
}