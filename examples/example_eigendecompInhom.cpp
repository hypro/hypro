/**
 * Sandbox for the Eigendecomposition project.
 */


#include "representations/GeometricObject.h"
#include "util/Plotter.h"
#include <Eigen/Eigenvalues> 
//TRAJECTORY of e-function plotting comment for no
#define TRAJECTORY 1
//#include <Eigen/LU>

int main()
{
	using namespace hypro;
	using Number = double;
	using Matrix = matrix_t<Number>;
	using Vector = vector_t<Number>;
 
    int n = 2;                  //<--- DIMENSION --->
    int i;
	Matrix A = Matrix(n,n);
    Vector b = Vector(n);
    Vector x0 = Vector(n);
    Vector b_tr = Vector(n);    //transformed
    Vector x0_tr = Vector(n);   //transformed
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
    #ifdef TRAJECTORY
        Number timestep = 0.02;
        Number traj_time;
        Vector plot_all_temp = Vector(n);
        Vector plot_vector = Vector(n);
    #endif
    Number tstart = 0;
    Number tend = 2;
    Number beginElTime, curTime;
    Number delta = 1; //segment stepping time
    Matrix V = Matrix(n,n);
    Matrix Vinv = Matrix(n,n);
	Eigen::DiagonalMatrix<Number,2> D; //type Number size 2

    //######   d/dx = A*x + b  ######
	A << 	0.001, 1, 
			0.001, -0.002;
    b <<    0, -9.81;
    x0<<    10, 0;
	
	std::cout << "d/dx = A*x+b, A:"<< std::endl << A << std::endl;
	std::cout << "b: "<< std::endl << b << std::endl;
    std::cout << "x0: "<< std::endl << x0 << std::endl;
    //decompose directly + constructor
    Eigen::EigenSolver<Matrix> es(A);
    Plotter<Number>& plotter = Plotter<Number>::getInstance();
     
    V << es.eigenvectors().real();
    D.diagonal() << es.eigenvalues().real();
    Vinv = V.inverse();
	std::cout << "Eigenvectors: "<< std::endl << V << std::endl;
	std::cout << "Vinverse: "<< std::endl << Vinv << std::endl;
	std::cout << "Eigenvalues: "<< std::endl << D.diagonal() << std::endl;
    //condition number ? stop on bad conditioning ??

    //invariants+transformed system
    b_tr = Vinv*b;
    x0_tr = Vinv*x0;
    xinhomconst = b_tr.array() / D.diagonal().array();
    xhomconst = xinhomconst.array() + x0_tr.array();

    beginElTime = tstart;
    //main stepping
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
    //needs: curTime (delta as additive)
    for (curTime = delta; curTime<=tend; curTime += delta) {
        //calculating invariants+ cases for delta
        beginElTime = curTime - delta;
        for (i=0; i<n; ++i) {
            derivFactor(i) = xhomconst(i)*D.diagonal()(i) * \
              std::exp(D.diagonal()(i) * beginElTime );
            xvalueStart(i) = xhomconst(i)* \
              std::exp(D.diagonal()(i) * beginElTime ) - xinhomconst(i);
            xvalueEnd(i)   = xhomconst(i)* \
              std::exp(D.diagonal()(i) * curTime )     - xinhomconst(i);
        }
        //derivative line
        derivAdditive = xvalueStart.array() - derivFactor.array()*beginElTime;
        derivLineStart = derivFactor.array()*beginElTime+derivAdditive.array();
        derivLineEnd   = derivFactor.array()*curTime    +derivAdditive.array();
        //direct line
        linGrowth = (xvalueEnd - xvalueStart).array()/(curTime-beginElTime);
        directLineStart = xvalueStart;
        directLineEnd = linGrowth.array()*(curTime-beginElTime) + \
          xvalueStart.array();
        //std::cout << "derivFactor: " << derivFactor;
        //std::cout << "xvalueStart: " << xvalueStart;
        //std::cout << "xvalueEnd: " << xvalueEnd;
        std::cout << "posStart: " << V*xvalueStart << std::endl;
        //plotting dimension!
        //Point<Number> p1(xvalueStart);
        //plotter.addPoint(p1);
        //plotter.addObject(p1.vertices();
        
        //on debug plot complete trajectory of e function
        #ifdef TRAJECTORY
            for (traj_time=beginElTime; traj_time<curTime; traj_time+=timestep) {
                //calculate point
                for (i=0; i<n; ++i) {
                    plot_all_temp(i) = xhomconst(i)* \
                      std::exp(D.diagonal()(i) * traj_time) - xinhomconst(i);
                }
                plot_all_temp = V*plot_all_temp; //transform back
                plot_vector(0) = traj_time;
                plot_vector(1) = plot_all_temp(0); //plotting time vs. height
                //plot point: HOPE that we have references/pointer and not copies
                Point<Number> p1(plot_vector);
                plotter.addPoint(p1);
            }
        #endif
    }
    #ifdef TRAJECTORY
        std::cout << "stepping size of e function: " << timestep << std::endl;
    #endif
    plotter.plot2d();
    //plotter.plotTex();
    plotter.plotEps();

	return 0;
}
