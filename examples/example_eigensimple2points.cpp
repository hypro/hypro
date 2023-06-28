/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/**
 * Overapproximation tryout with 2 points.
 */

#include <hypro/representations/GeometricObjectBase.h>
#include <hypro/util/plotting/Plotter.h>
#include <eigen3/Eigen/Eigenvalues>

#define FLOATING_FIX 10e-12
#define PTS_DEBUG 1       // show all added points
#define TRANFORMED_PLOT 1 // for later use
#define DIM_PLOT                                                               \
  0 // starting with 0..n-1 what to plot might be added with multiple dim or
// data format (struct/enum)
// TRAJECTORY of e-function plotting comment for no
//#define TRAJECTORY 1

int main() {
    using namespace hypro;
    using Number = double;
    using Matrix = matrix_t<Number>;
    using Vector = vector_t<Number>;

    int n = 2; //<--- DIMENSION --->
    int i;
    Matrix A = Matrix(n, n);
    Vector b = Vector(n);
    Vector x0 = Vector(n);
    Vector b_tr = Vector(n);  // transformed
    Vector x0_tr = Vector(n); // transformed
    Vector xinhomconst = Vector(n);
    Vector xhomconst = Vector(n);
    Vector xvalueStart = Vector(n);
    Vector xvalueEnd = Vector(n);
    Vector derivFactor = Vector(n);
    Vector derivAdditive = Vector(n);
    Vector derivLineStart = Vector(n);
    Vector derivLineEnd = Vector(n);
    Vector linGrowth = Vector(n);
    Vector directLineStart = Vector(n);
    Vector directLineEnd = Vector(n);
    Vector plot_vector = Vector(n);
#ifdef TRAJECTORY
    Number timestep = 0.02;
    Number traj_time;
    Vector plot_all_temp = Vector(n);
#endif
    Number tstart = 0;
    Number tend = 4;
    Number beginElTime, curTime;
    Number delta = 0.1; // segment stepping time
    Matrix V = Matrix(n, n);
    Matrix Vinv = Matrix(n, n);
    Eigen::DiagonalMatrix<Number, 2> D; // type Number size 2

    //######   d/dx = A*x + b  ######
    A << 0.001, 1, 0.001, -0.002;
    b << 0, -9.81;
    x0 << 10, 0;

    std::cout << "d/dx = A*x+b, A:" << std::endl << A << std::endl;
    std::cout << "b: " << std::endl << b << std::endl;
    std::cout << "x0: " << std::endl << x0 << std::endl;
    // decompose directly + constructor
    Eigen::EigenSolver<Matrix> es(A);
    Plotter<Number> &plotter = Plotter<Number>::getInstance();

    V << es.eigenvectors().real();
    D.diagonal() << es.eigenvalues().real();
    Vinv = V.inverse();
    std::cout << "Eigenvectors: " << std::endl << V << std::endl;
    std::cout << "Vinverse: " << std::endl << Vinv << std::endl;
    std::cout << "Eigenvalues: " << std::endl << D.diagonal() << std::endl;
    // condition number ? stop on bad conditioning ??

    // invariants+transformed system
    b_tr = Vinv * b;
    x0_tr = Vinv * x0;
    xinhomconst = b_tr.array() / D.diagonal().array();
    xhomconst = xinhomconst.array() + x0_tr.array();

    beginElTime = tstart;
    // main stepping
    /*
    Vector xvalueStart = Vector(n);
    Vector xvalueEnd = Vector(n);
    Vector derivFactor = Vector(n); \
    Vector derivAdditive = Vector(n); \
    Vector derivLineStart = Vector(n); \
    Vector derivLineEnd = Vector(n);
    Vector linGrowth = Vector(n);
    Vector directLineStart = Vector(n);
    Vector directLineEnd = Vector(n);
    */
    // needs: curTime (delta as additive)
    // ugly floating fix
    //
    //
    // std::vector<vector_t<Number>> points;
    // points.push_back(x0);
    // /* compute over-approximative point p2 and exact solution point p1
    // /* also obtain A and b -> v' = Av + b
    // points.push_back(p1);
    // points.push_back(p2);
    // hypro::VPolytope<Number> v0 = hypro::VPolytope<Number>(points);
    //
    // hypro::Plotter<Number>& plt = hypro::Plotter<Number>::getInstance();
    //
    // plt.addObject(v0.vertices());
    // std::vector<VPolytope<Number>> sets;
    // sets.push_back(v0);
    //
    // /* define working ptope */
    // VPolytope<Number> current = v0;
    // for(std::size_t i = 0; i < (tend/delta); ++i) {
    // 		sets.push_back(current);
    // 		VPolytope<Number> next = current.affineTransformation(A,b);
    //  	/* VPolytope<Number> next = current.linearTransformation(A); */
    // 		plt.addObject(next.vertices());
    // 		current = next;
    // }
    //
    // /* compute points of exact solution ... E_points
    //
    // #ifndef NDEBUG
    // for( const auto& p : ePoints) {
    // 		bool contained = false;
    // 		for( const auto& set : sets) {
    // 			if(set.contains(p)) {
    // 				contained = true;
    // 			}
    // 		}
    // 		assert(contained);
    // }
    // #endif
    //
    //
    for (curTime = delta; curTime < tend + FLOATING_FIX; curTime += delta) {
        // std::cout << curTime << " < " << tend+FLOATING_FIX << std::endl;
        // calculating invariants+ cases for delta
        beginElTime = curTime - delta;
        for (i = 0; i < n; ++i) {
            derivFactor(i) = xhomconst(i) * D.diagonal()(i) *
                             std::exp(D.diagonal()(i) * beginElTime);
            xvalueStart(i) = xhomconst(i) * std::exp(D.diagonal()(i) * beginElTime) -
                             xinhomconst(i);
            xvalueEnd(i) =
                    xhomconst(i) * std::exp(D.diagonal()(i) * curTime) - xinhomconst(i);
        }

        // derivative line
        derivAdditive = xvalueStart.array() - derivFactor.array() * beginElTime;
        derivLineStart = derivFactor.array() * beginElTime + derivAdditive.array();
        derivLineEnd = derivFactor.array() * curTime + derivAdditive.array();
        // direct line
        linGrowth = (xvalueEnd - xvalueStart).array() / (curTime - beginElTime);
        directLineStart = xvalueStart;
        directLineEnd =
                linGrowth.array() * (curTime - beginElTime) + xvalueStart.array();
        // ----------------   OUTPUT + PLOTTING ------------------
        // std::cout << "derivFactor: " << derivFactor;
        // std::cout << "xvalueStart: " << xvalueStart;
        // std::cout << "xvalueEnd: " << xvalueEnd;
        // std::cout << "posStart: " << V*xvalueStart << std::endl;
        plot_vector(0) = beginElTime;
        plot_vector(1) = xvalueStart(DIM_PLOT);

        // std::cout << "curTime" << curTime << std::endl;
        // std::cout << "xvalueEnd" << xvalueEnd(0) << std::endl;
        Point<Number> p1(xvalueStart);
        plotter.addPoint(p1);
#ifdef PTS_DEBUG
        // std::cout << "pt adding: (" << beginElTime << "," <<
        // xvalueStart(DIM_PLOT) << ")" << std::endl;
        std::cout << "time (end+1)  = [" << beginElTime << "];" << std::endl;
        std::cout << "value(end+1)  = [" << xvalueStart(DIM_PLOT) << "];"
                  << std::endl;
#endif
        // std::cout << "pt" << std::endl << plot_vector << std::endl;
        // floating values assign wrong size (awkward fix)
        if (curTime + delta > tend + FLOATING_FIX) {
            // std::cout << curTime + delta << " > " << tend << std::endl;
            // std::cout << "curTime" << curTime << std::endl;
            // std::cout << "xvalueEnd" << xvalueEnd(0) << std::endl;
            plot_vector(0) = curTime;
            plot_vector(1) = xvalueEnd(DIM_PLOT);
            Point<Number> p1(plot_vector);
            plotter.addPoint(p1);
#ifdef PTS_DEBUG
            // std::cout << "pt adding: (" << curTime << "," << xvalueEnd(DIM_PLOT) <<
            // ")" << std::endl;
            std::cout << "time (end+1)  = [" << curTime << "];" << std::endl;
            std::cout << "value(end+1)  = [" << xvalueEnd(DIM_PLOT) << "];"
                      << std::endl;
#endif
            // std::cout << "pt" << std::endl << plot_vector << std::endl;
        }
        // plotter.addObject(p1.vertices();
        // plotting lines of segments
        // TODO lines creating by normal vectors
        // Halfspace<Number> hsp = Halfspace<Number>({-1,1},0);
        // plotter.addObject(hsp);     //plotter.addHalfspace(hsp); did not WORK
        // EITHER <--------------------------------------- on debug plot complete
        // trajectory of e function
#ifdef TRAJECTORY
        for (traj_time = beginElTime; traj_time < curTime; traj_time += timestep) {
          // calculate point
          for (i = 0; i < n; ++i) {
            plot_all_temp(i) =
                xhomconst(i) * std::exp(D.diagonal()(i) * traj_time) -
                xinhomconst(i);
          }
          plot_all_temp = V * plot_all_temp; // transform back
          plot_vector(0) = traj_time;
          plot_vector(1) = plot_all_temp(0); // plotting time vs. height
          // plot point: HOPE that we have references/pointer and not copies
          Point<Number> p1(plot_vector);
          plotter.addPoint(p1);
        }
#endif
    }
#ifdef TRAJECTORY
    std::cout << "TRAJECTORY was set" << std::endl;
    std::cout << "stepping size of e function: " << timestep << std::endl;
#endif
    // Halfspace<Number> hsp = Halfspace<Number>({-1,1},0);
    plotter.plot2d();
    // plotter.plotTex();
    // plotter.plotEps();
    return 0;
}
