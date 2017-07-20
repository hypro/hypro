/**
 * Sandbox for the Eigendecomposition project.
 */


#include "representations/GeometricObject.h"
#include "util/Plotter.h"
#include <Eigen/Eigenvalues>
#define PTS_DEBUG 1         //show all added points
#define TRANFORMED_PLOT 1   //for later use
#define DIM_PLOT 1          //starting with 0..n-1 what to plot might be added with multiple dim or data format (struct/enum)
//#define TRAJECTORY 1
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
    Vector xvalue = Vector(n);
    Vector derivFactor = Vector(n);
    Vector derivLineEnd = Vector(n);
    Vector plot_vector = Vector(n);
    #ifdef TRAJECTORY
        Number timestep = 0.02;
        Number traj_time;
        Vector plot_all_temp = Vector(n);
    #endif
    Number tend = 2;
    Number delta = 0.1; //segment stepping time
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
    //stop on bad conditioning ??

    //invariants+transformed system
    b_tr = Vinv*b;
    x0_tr = Vinv*x0;
    xinhomconst = b_tr.array() / D.diagonal().array();
    xhomconst = xinhomconst.array() + x0_tr.array();
    std::vector<vector_t<Number>> points;
    std::vector<vector_t<Number>> approx_points;
    VPolytope<Number> vpoly;
    VPolytope<Number> vpoly2;
    //loop through delta steps
    //on each step exact value, derivation and approximation
    //direct line connects exact values
    //approximation uses derivation at each point to get next value
    derivLineEnd = x0_tr;
    std::size_t deltalimit = std::ceil( (tend/delta) );
    //std::cout << "tlimit: " << tlimit << std::endl; //better:rationals
    for(std::size_t j = 0; j <= deltalimit;  ++j) { 
        for (i=0; i<n; ++i) {
            derivFactor(i) = xhomconst(i)*D.diagonal()(i) * \
              std::exp(D.diagonal()(i) *j*delta  );
            xvalue(i) = xhomconst(i)* \
              std::exp(D.diagonal()(i) *j*delta ) - xinhomconst(i);
        }
        std::cout << "time, "<< j*delta <<", value, "<< xvalue(DIM_PLOT) << std::endl;
        //plotting
        plot_vector(0) = j;
        plot_vector(1) =       xvalue(DIM_PLOT);
        //Point<Number> plot_point(plot_vector);
        //plotter.addPoint(plot_point);
        points.push_back(plot_vector);
        plot_vector(1) = derivLineEnd(DIM_PLOT);
        approx_points.push_back(plot_vector);
        vpoly = VPolytope<Number>(points);
        vpoly2 = VPolytope<Number>(approx_points);
        if (j>0) {
            plotter.addObject(vpoly.vertices());
            plotter.addObject(vpoly2.vertices());
            points.erase( points.begin() );
            approx_points.erase( approx_points.begin() );
        }

        derivLineEnd = derivFactor.array()*delta+derivLineEnd.array();
    }
    // ???? USE ???? e-function derivation is NOT linear thus 
    // we can not use such transformation or our error gets high
    // 		sets.push_back(current);
    // 		VPolytope<Number> next = current.affineTransformation(A,b); //Ax+b is affine so we need -b
    //  	/* VPolytope<Number> next = current.linearTransformation(A); */
    // 		plt.addObject(next.vertices());
    // 		current = next;

    // /* compute over-approximative point p2 and exact solution point p1
    // /* also obtain A and b -> v' = Av + b
    // points.push_back(p1);
    // points.push_back(p2);
    //
    // for(std::size_t i = 0; i < (tend/delta); ++i) {
    // 		sets.push_back(current);
    // 		VPolytope<Number> next = current.affineTransformation(A,b); //Ax+b is affine so we need -b
    //  	/* VPolytope<Number> next = current.linearTransformation(A); */
    // 		plt.addObject(next.vertices());
    // 		current = next;
    // }
    //
    // /* compute points of exact solution ... E_points
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
    //Halfspace<Number> hsp = Halfspace<Number>({-1,1},0);
    plotter.plot2d();
    //plotter.plotTex();
    //plotter.plotEps();
	return 0;
}
