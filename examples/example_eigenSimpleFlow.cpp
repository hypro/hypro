/**
 * Sandbox for the Eigendecomposition project.
 */


#include "representations/GeometricObject.h"
#include "util/Plotter.h"
#include <Eigen/Eigenvalues>
#include <Eigen/Dense>
//#define PTS_DEBUG 1         //NO USE
#define ORIGINAL_SYS_PLOT 1   //original system plot
#define DIM_PLOT 0          //starting with 0..n-1 what to plot might be added with multiple dim or data format (struct/enum)
//#define TRAJECTORY 1
//#include <Eigen/LU>
using namespace hypro;
//using namespace Eigen;
using Number = double;
using Matrix = matrix_t<Number>;
using Vector = vector_t<Number>;
using DiagonalMatrix = Eigen::DiagonalMatrix<Number,Eigen::Dynamic>;
using BoolMatrix = matrix_t<bool>;
//using madef = Matrix<Number, Dynamic, Dynamic>;
//Eigen::Matrix<Number, Eigen::Dynamic, Eigen::Dynamic>;
#define vecdef         std::vector<vector_t<Number>>

void elwise_maxtransformation(Matrix& x_tr, int n);
void elwise_backtransformation(Matrix& x_tr, int n);
void initialize (const Matrix& xhomconst, const DiagonalMatrix& D, BoolMatrix& directmaxmin,
                    Matrix& derivFactormaxmin, std::vector<Vector>& ptsxmax_tr,
                        std::vector<Vector>& ptsxmin_tr, int n, Matrix& x_tr, const Matrix& V);

void loop (std::size_t deltalimit, const BoolMatrix& directmaxmin, const DiagonalMatrix& D, const Matrix& xhomconstmaxmin,
            Number delta, int n, std::vector<Vector>& ptsxmax_tr,
            std::vector<Vector>& ptsxmin_tr, Matrix& derivFactormaxmin,
            Matrix& x_tr, const Vector& xinhomconst, const Matrix& V);
    //calculate values according to directmaxmin boolean array


int main()
{
	//using namespace hypro;
	//using Number = double;
	//using Matrix = matrix_t<Number>;
	//using Vector = vector_t<Number>;
    //ref for inplace calculation
    int n = 2;                  //<--- DIMENSION --->
    //int i;
	Matrix A = Matrix(n,n);
    Vector b = Vector(n);
    Vector x0 = Vector(n);
    Vector x0_2 = Vector(n);
    Vector b_tr = Vector(n);      //transformed
    Matrix x_tr = Matrix::Zero(2,3);
    x_tr.col(2).array() = 0;
    Matrix xhomconstmaxmin = Matrix::Zero(2,2);

    Vector xinhomconst = Vector(n);
    Vector factor = Vector(n);
    Vector xvalue = Vector(n);
    Matrix derivFactormaxmin = Matrix(n,2);
    BoolMatrix directmaxmin = BoolMatrix(2,2);
    directmaxmin.setConstant(0);
    #ifdef TRAJECTORY
        Number timestep = 0.01;
        Number traj_time;
        Vector pts_traj = Vector(n);
        VPolytope<Number> traj_poly;
        std::vector<Vector> plot_traj;
    #endif
    Number tend = 2;
    Number delta = 0.01; //segment stepping time
    Matrix V = Matrix(n,n);
    Matrix Vinv = Matrix(n,n);
	DiagonalMatrix D = DiagonalMatrix(2); //type Number size 2

    //######   d/dx = A*x + b  ######
	A << 	0.001, 1,
			0.001, -0.002;
    b <<    0, -9.81;
    x0<<    10.2, 0;        //we require x0 > x0_2 elementwise
    x0_2 << 10, 0;          //else we swap values

	std::cout << "d/dx = A*x+b, A:"<< std::endl << A << std::endl;
	std::cout << "b: "<< std::endl << b << std::endl;
    std::cout << "x0: "<< std::endl << x0 << std::endl;
    std::cout << "x0_2: "<< std::endl << x0_2 << std::endl;
    //decompose directly + constructor
    Eigen::EigenSolver<Matrix> es(A);

    V << es.eigenvectors().real();
    D.diagonal() << es.eigenvalues().real();
    Vinv = V.inverse();
	std::cout << "Eigenvectors: "<< std::endl << V << std::endl;
	std::cout << "Vinverse: "<< std::endl << Vinv << std::endl;
	std::cout << "Eigenvalues: "<< std::endl << D.diagonal() << std::endl;
    //stop on bad conditioning ??

    //invariants+transformed system
    b_tr = Vinv*b;
    x_tr.col(0) = Vinv*x0;
    x_tr.col(1) = Vinv*x0_2;

    std::cout << "x_tr: "<< std::endl << x_tr << std::endl;
    elwise_maxtransformation(x_tr, n); //ref to Eigen::Matrix to write Eigen::Matrix
    xinhomconst = b_tr.array() / D.diagonal().array();

    xhomconstmaxmin.col(0) = xinhomconst.array() + x_tr.col(0).array();
    xhomconstmaxmin.col(1) = xinhomconst.array() + x_tr.col(1).array();
    
    std::cout << "xhomconstmaxmin: "<< std::endl << xhomconstmaxmin << std::endl;
    //plotting structures
    Plotter<Number>& plotter = Plotter<Number>::getInstance();
    std::vector<Vector> ptsxmax_tr;
    std::vector<Vector> ptsxmin_tr;
    //function pointers + 1.step(derivative+value)
    //initialize (const Matrix& a); //
    initialize (xhomconstmaxmin, D, directmaxmin, derivFactormaxmin, ptsxmax_tr, ptsxmin_tr, n, 
                x_tr, V);

    //initial value calculation+derivative, possible trajectory value
    //starting on delta: rational numbers might be better here
    std::size_t deltalimit = std::ceil( (tend/delta) );
    loop (  deltalimit, directmaxmin, D, xhomconstmaxmin, delta, n, ptsxmax_tr, ptsxmin_tr,         
            derivFactormaxmin, x_tr, xinhomconst, V);
    //calculate values according to directmaxmin boolean array

    plotter.plot2d();
    plotter.plotGen();

    //std::cout << "tlimit: " << tlimit << std::endl; //better:rationals

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
    //plotter.plotTex();
    //plotter.plotEps();
	return 0;
}

//assigning elwise maximum/min address to xmax and xmin
void elwise_maxtransformation(Matrix& x_tr, const int n) {     
    std::cout << "x_tr beforemax: "<< std::endl << x_tr << std::endl;
    for(int i=0; i<n; ++i) {   //check if x0_tr >= x0_2_tr
        if(x_tr(i,0) < x_tr(i,1)) {
            x_tr(i,2) = x_tr(i,0);
            x_tr(i,0) = x_tr(i,1);
            x_tr(i,1) = x_tr(i,2);
            x_tr(i,2) = 1; //mark second column to recognize later
        }
    }    
    std::cout << "x_tr aftermax: "<< std::endl << x_tr << std::endl;
}
void elwise_backtransformation(Matrix& x_tr, const int n) {
    std::cout << "x_tr beforeback: "<< std::endl << x_tr << std::endl;
    for(int i=0; i<n; ++i) {
        if(x_tr(i,2) == 1) { //check if x0_tr >= x0_2_tr
            x_tr(i,2) =x_tr(i,0);
            x_tr(i,0) = x_tr(i,1);
            x_tr(i,1) = x_tr(i,2);
            x_tr(i,2) = 0; //mark second column to recognize later
        }
    }
    std::cout << "x_tr afterback: "<< std::endl << x_tr << std::endl;
}
//doing function pointer assigning on cases
    //we might have 2 different conversion levels, 1 or divergence
    //divergence: D>0
    //convergence D<0, 1 or 2 points
    //depending on calculation we set according function pointer
    //and assign according values
    //remind we assume x0 > x0_2 element wise and set addresses accordingly
            //case1:  e^x      --- D>0, xhomconst>0
            //case2: -e^(-x)   --- etc
            //case3: -e^(x)    --- D>0, xhomconst<0
            //case4:  e^(-x)   --- etc
void initialize (const  Matrix& xhomconst, const DiagonalMatrix& D, BoolMatrix& directmaxmin,
                        Matrix& derivFactormaxmin, std::vector<Vector>& ptsxmax_tr,
                        std::vector<Vector>& ptsxmin_tr, int n, Matrix& x_tr, const Matrix& V) {
    Vector plot_vector = Vector(n);
    for(int i=0; i<n; ++i) {
        if (D.diagonal()(i)>0) { //divergence
            if (xhomconst(i,0) >= 0) {
                directmaxmin(i,0) = true;      //xmax(i) directLine
                if (xhomconst(i,1) >= 0) {
                    //xmin(i) derivLine
                } else {
                    directmaxmin(i,1) = true;  //unusual!! xmin(i) directLine
                }
            } else {
                    //xmax(i) derivLine
                if(xhomconst(i,1) >= 0) {
                    //ERROR upwards and downwards
                } else {
                    directmaxmin(i,1) = true;  //xmin(i) directLine
                }
            }
        } else { //case 2 and 4
        //convergence
            if (xhomconst(i,0) >=0) {
                directmaxmin(i,0) = true;      //xmax(i) directLine
                if (xhomconst(i,1) >=0) {
                    //xmin(i) derivLine
                } else {
                    directmaxmin(i,1) = true;  //xmin(i) directLine
                    //convergence point between initial set
                }
            } else {
                //xmax(i) derivLine
                if (xhomconst(i,1) >=0) {
                    //xmin(i) derivLine
                    //2 convergence points!!
                } else {
                    directmaxmin(i,1) = true;   //xmin(i) directLine
                }
            }
        }
    }
    //std::cout << "xhomconst: "<< std::endl << x0_2 << std::endl;
    // .... TODO
    //1.step calculation + inserting
    //e^0 = 1
    derivFactormaxmin.col(0) = xhomconst.col(0).array()*D.diagonal().array();
    derivFactormaxmin.col(1) = xhomconst.col(1).array()*D.diagonal().array();

    #ifdef ORIGINAL_SYS_PLOT
    elwise_backtransformation(x_tr, n);
    plot_vector(0) = 0; //was j before
    plot_vector(1) = (V*x_tr.col(0))(DIM_PLOT);
    ptsxmax_tr.push_back(plot_vector);
    plot_vector(1) = (V*x_tr.col(1))(DIM_PLOT);
    ptsxmin_tr.push_back(plot_vector);
    elwise_maxtransformation(x_tr, n);
    #endif
    #ifndef ORIGINAL_SYS_PLOT
    plot_vector(0) = 0; // TODO: Check again, was "j"
    plot_vector(1) = x_tr(DIM_PLOT,0);
    ptsxmax_tr.push_back(plot_vector);
    plot_vector(1) = x_tr(DIM_PLOT,1);
    ptsxmin_tr.push_back(plot_vector);
    #endif
    //STARTING POINT
    std::cout << "plotvector(0): "<< std::endl << plot_vector(0) << std::endl;
}
    //1.linear value + derivative OR direct value
    //1.1 possible trajectory calculation pushing writing deleting
    //2.pushing,writing,deleting   [maybe flushing in between??]

void loop (std::size_t deltalimit, const BoolMatrix& directmaxmin, const DiagonalMatrix& D, 
            const Matrix& xhomconst, Number delta, int n, std::vector<Vector>& ptsxmax_tr,
            std::vector<Vector>& ptsxmin_tr, Matrix& derivFactormaxmin,
            Matrix& x_tr, const Vector& xinhomconst, const Matrix& V) {
    using namespace hypro;

    Plotter<Number>& plotter = Plotter<Number>::getInstance();
    VPolytope<Number> vpoly_upper;
    VPolytope<Number> vpoly_lower;
    Vector factor = Vector::Zero(n);
    Vector plot_vector = Vector(2);
    for(std::size_t j = 0; j <= deltalimit;  ++j) {
    	std::cout << "Time: " << j*delta << std::endl;
        for (int i=0; i<n; ++i) {
            factor(i) = std::exp(D.diagonal()(i) *j*delta);

            if(directmaxmin(i,0)) {
                x_tr(i,0) = xhomconst(i,0)*factor(i) - xinhomconst(i);
            } else {
                x_tr(i,0) = x_tr(i,0) + derivFactormaxmin(i,0)*delta;
                derivFactormaxmin(i,0) = xhomconst(i,0)*D.diagonal()(i)*factor(i);
            }
            if(directmaxmin(i,1)) {
                x_tr(i,1) = xhomconst(i,1)*factor(i) - xinhomconst(i);
            } else {
                x_tr(i,1) = x_tr(i,1) + derivFactormaxmin(i,1)*delta;
                derivFactormaxmin(i,1) = xhomconst(i,1)*D.diagonal()(i)*factor(i);
            }
            //std::cout << "x0_2: "<< std::endl << x0_2 << std::endl; TODO
        }
        #ifdef ORIGINAL_SYS_PLOT
        elwise_backtransformation(x_tr, n);
        plot_vector(0) = j;
        plot_vector(1) = (V*x_tr.col(0))(DIM_PLOT);
        ptsxmax_tr.push_back(plot_vector);
        plot_vector(1) = (V*x_tr.col(1))(DIM_PLOT);
        ptsxmin_tr.push_back(plot_vector);
        elwise_maxtransformation(x_tr, n);
        #endif
        #ifndef ORIGINAL_SYS_PLOT
        plot_vector(0) = j;
        plot_vector(1) = x_tr(DIM_PLOT,0);
        ptsxmax_tr.push_back(plot_vector);
        plot_vector(1) = x_tr(DIM_PLOT,1);
        ptsxmin_tr.push_back(plot_vector);
        #endif
        vpoly_upper = VPolytope<Number>(ptsxmax_tr);
        vpoly_lower = VPolytope<Number>(ptsxmin_tr);
        #ifdef TRAJECTORY
        for(traj_time = j; traj_time<j+1; traj_time+=timestep) {
            for (i=0; i<n; ++i) {
                factor(i) = std::exp(D.diagonal()(i) *traj_time*delta);
            }
            //depends what we want to plot here
            pts_traj = xhomconstmax.array()*factor.array() - xinhomconst.array();
            plot_vector(0) = traj_time;
            plot_vector(1) = pts_traj(DIM_PLOT);
            plot_traj.push_back(plot_vector);
            traj_poly = VPolytope<Number>(plot_traj);
            if(traj_time > j) {
                unsigned t = plotter.addObject(traj_poly.vertices());
                plotter.setObjectColor(t, plotting::colors[plotting::green]);
                plot_traj.erase(plot_traj.begin() );
            }
        }
        #endif
		unsigned v = plotter.addObject(vpoly_upper.vertices());
		plotter.setObjectColor(v, plotting::colors[plotting::red]);
        unsigned w = plotter.addObject(vpoly_lower.vertices());
        plotter.setObjectColor(w, plotting::colors[plotting::blue]);
        ptsxmax_tr.erase( ptsxmax_tr.begin() );
        ptsxmin_tr.erase( ptsxmin_tr.begin() );
    }
}
