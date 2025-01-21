#include "hypro/representations/GeometricObjectBase.h"
// #include "hypro/representations/Starset/Starset.h"
#include "hypro/util/plotting/Plotter.h"

#include <iostream>
#include <chrono>

// use floating point arithmetic.
typedef double Number;

int main( int argc, char* argv[] ) {
    hypro::vector_t<Number> center = hypro::vector_t<Number>(2);
    hypro::matrix_t<Number> basis = hypro::matrix_t<Number>(2,2);
    hypro::matrix_t<Number> constr = hypro::matrix_t<Number>(3,2);
    hypro::vector_t<Number> limits = hypro::vector_t<Number>(3);
    center << 0, 0;
    basis << 1, 0, 0, 1;
    constr << 1, 0, 0, 1, 0, -1;
    limits << 2, 1, 1;

    hypro::Starset<Number> myStar = hypro::Starset<Number>(center, constr, limits, basis);

    std::cout << "Starset: " << myStar << std::endl;
    std::cout << "Empty: " << myStar.empty() << std::endl;
    std::cout << "Vertices: " << myStar.vertices() << std::endl;

    hypro::matrix_t<Number> linearTransformation(2, 2);
    hypro::vector_t<Number> offset(2);
    linearTransformation << 1.4142, -1.4142, 1.4142, 1.4142;
    offset << -1, +1;

    hypro::Starset<Number> transformedStar = myStar.affineTransformation(linearTransformation, offset);
    std::cout << "Transformed star: " << transformedStar << std::endl;
    std::cout << "Empty: " << transformedStar.empty() << std::endl;
    std::cout << "Vertices: " << transformedStar.vertices() << std::endl;

    hypro::vector_t<Number> dir_vect = basis.row(0);
    auto eval_low_result = myStar.constraints().evaluate( -1.0 * dir_vect );
    auto eval_high_result = myStar.constraints().evaluate( dir_vect );

    if(eval_low_result.errorCode == hypro::SOLUTION::FEAS) {
        Number lb = -eval_low_result.supportValue + center[0];
        std::cout << "x0 Lower bound = " << lb << std::endl;
    } else if(eval_low_result.errorCode == hypro::SOLUTION::INFTY) {
        std::cout << "x0 Lower bound is minus infinity (unbounded)" << std::endl;
    }

    if(eval_high_result.errorCode == hypro::SOLUTION::FEAS) {
        Number ub = eval_high_result.supportValue + center[0];
        std::cout << "x0 Upper bound = " << ub << std::endl;
    } else if(eval_high_result.errorCode == hypro::SOLUTION::INFTY) {
        std::cout << "x0 Upper bound is plus infinity (unbounded)" << std::endl;
    }

    dir_vect = basis.row(1);
    eval_low_result = myStar.constraints().evaluate( -1.0 * dir_vect );
    eval_high_result = myStar.constraints().evaluate( dir_vect );

    if(eval_low_result.errorCode == hypro::SOLUTION::FEAS) {
        Number lb = -eval_low_result.supportValue + center[1];
        std::cout << "x1 Lower bound = " << lb << std::endl;
    } else if(eval_low_result.errorCode == hypro::SOLUTION::INFTY) {
        std::cout << "x1 Lower bound is minus infinity (unbounded)" << std::endl;
    }

    if(eval_high_result.errorCode == hypro::SOLUTION::FEAS) {
        Number ub = eval_high_result.supportValue + center[1];
        std::cout << "x1 Upper bound = " << ub << std::endl;
    } else if(eval_high_result.errorCode == hypro::SOLUTION::INFTY) {
        std::cout << "x1 Upper bound is plus infinity (unbounded)" << std::endl;
    }

    hypro::vector_t<Number> new_dir_vect = transformedStar.generator().row(0);
    auto new_eval_low_result = transformedStar.constraints().evaluate( -1.0 * new_dir_vect );
    auto new_eval_high_result = transformedStar.constraints().evaluate( new_dir_vect );

    if(new_eval_low_result.errorCode == hypro::SOLUTION::FEAS) {
        Number lb = -new_eval_low_result.supportValue + transformedStar.center()[0];
        std::cout << "x0 Lower bound = " << lb << std::endl;
    } else if(new_eval_low_result.errorCode == hypro::SOLUTION::INFTY) {
        std::cout << "x0 Lower bound is minus infinity (unbounded)" << std::endl;
    }

    if(new_eval_high_result.errorCode == hypro::SOLUTION::FEAS) {
        Number ub = new_eval_high_result.supportValue + transformedStar.center()[0];
        std::cout << "x0 Upper bound = " << ub << std::endl;
    } else if(new_eval_high_result.errorCode == hypro::SOLUTION::INFTY) {
        std::cout << "x0 Upper bound is plus infinity (unbounded)" << std::endl;
    }

    new_dir_vect = transformedStar.generator().row(1);
    new_eval_low_result = transformedStar.constraints().evaluate( -1.0 * new_dir_vect );
    new_eval_high_result = transformedStar.constraints().evaluate( new_dir_vect );

    if(new_eval_low_result.errorCode == hypro::SOLUTION::FEAS) {
        Number lb = -new_eval_low_result.supportValue + transformedStar.center()[1];
        std::cout << "x1 Lower bound = " << lb << std::endl;
    } else if(new_eval_low_result.errorCode == hypro::SOLUTION::INFTY) {
        std::cout << "x1 Lower bound is minus infinity (unbounded)" << std::endl;
    }

    if(new_eval_high_result.errorCode == hypro::SOLUTION::FEAS) {
        Number ub = new_eval_high_result.supportValue + transformedStar.center()[1];
        std::cout << "x1 Upper bound = " << ub << std::endl;
    } else if(new_eval_high_result.errorCode == hypro::SOLUTION::INFTY) {
        std::cout << "x1 Upper bound is plus infinity (unbounded)" << std::endl;
    }

    return 0;
}