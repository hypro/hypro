/**
 * @file example_star.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-01-13
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "hypro/representations/GeometricObjectBase.h"
// #include "hypro/representations/Starset/Starset.h"
#include "hypro/util/plotting/Plotter.h"

#include <chrono>


int main() {
    // use rational arithmetic.
    typedef mpq_class Number;

    // get plotter reference.
    hypro::Plotter<Number> &plotter = hypro::Plotter<Number>::getInstance();
    plotter.setFilename("Starsets");

    hypro::vector_t<Number> center = hypro::vector_t<Number>(2);
    hypro::matrix_t<Number> basis = hypro::matrix_t<Number>(2,2);
    hypro::matrix_t<Number> constr = hypro::matrix_t<Number>(4,2);
    hypro::vector_t<Number> limits = hypro::vector_t<Number>(4);
    center << 5, 2;
    basis << 1, 0, 0, 1;
    constr << 1, 0, -1, 0, 0, 1, 0, -1;
    limits << 2, 1, 1, 1;
    hypro::Starset<Number> myStar = hypro::Starset<Number>(center, constr, limits, basis);
    plotter.addObject(myStar.vertices());

    hypro::matrix_t<Number> transmat=hypro::matrix_t<Number>(2,2);
    double angle = 5 * PI / 180.0;
    transmat<<cos(angle),-sin(angle),sin(angle),cos(angle);
    hypro::vector_t<Number> offset=hypro::vector_t<Number>(2);
    offset<<1,1;


    auto start = std::chrono::high_resolution_clock::now();
    for(int i = 0; i < 1000; i++) {
        myStar = myStar.affineTransformation(transmat, offset);
        plotter.addObject(myStar.vertices());
    }
    auto stop = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    std::cout << "Total time elapsed: " << elapsed.count() << " milliseconds." << std::endl;

    plotter.plot2d();


    // =================== AFFINE TRANSFORMATION + ASSIGNMENT ===================
    start = std::chrono::high_resolution_clock::now();
    for(int i = 0; i < 10000; i++) {
        myStar = myStar.affineTransformation(transmat, offset);
    }
    stop = std::chrono::high_resolution_clock::now();
    elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    std::cout << "Total time elapsed for 10000 affine transformations: " << elapsed.count() << " milliseconds." << std::endl;

    // =================== EMPTINESS CHECK ONLY ===================
    start = std::chrono::high_resolution_clock::now();
    for(int i = 0; i < 10000; i++) {
        myStar.empty();
    }
    stop = std::chrono::high_resolution_clock::now();
    elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    std::cout << "Total time elapsed for 10000 emptiness checks: " << elapsed.count() << " milliseconds." << std::endl;

    // =================== RAW AFFINE TRANSFORMATION ===================
    start = std::chrono::high_resolution_clock::now();
    for(int i = 0; i < 10000; i++) {
        center = transmat * center + offset;
        basis = transmat * basis;
    }
    stop = std::chrono::high_resolution_clock::now();
    elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    std::cout << "Total time elapsed for 10000 raw affine transformations: " << elapsed.count() << " milliseconds." << std::endl;

    // =================== CONSTRUCTOR CALLS ===================
    hypro::HPolytope<Number> constraints = hypro::HPolytope<Number>(constr, limits);
    start = std::chrono::high_resolution_clock::now();
    for(int i = 0; i < 10000; i++) {
        myStar = hypro::Starset<Number>(center, basis, constraints);  // be carefull, the default copy constructur takes half time
    }
    stop = std::chrono::high_resolution_clock::now();
    elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    std::cout << "Total time elapsed for 10000 constructor calls: " << elapsed.count() << " milliseconds." << std::endl;

    // =================== ASSIGNMENT OPERATOR ===================
    hypro::Starset<Number> copyStar = hypro::Starset<Number>();
    start = std::chrono::high_resolution_clock::now();
    for(int i = 0; i < 10000; i++) {
        copyStar = myStar;
    }
    stop = std::chrono::high_resolution_clock::now();
    elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    std::cout << "Total time elapsed for 10000 assignment operator calls: " << elapsed.count() << " milliseconds." << std::endl;

    return 0;
}
