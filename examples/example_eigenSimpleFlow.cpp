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
#define TRAJECTORY 1
//#include <Eigen/LU>
void elwise_maxtransformation( void );
void elwise_backtranformation( void );
void initialize (void);
void loop(std::size_t deltalimit);

int main()
{
	using namespace hypro;
	using Number = double;
	using Matrix = matrix_t<Number>;
	using Vector = vector_t<Number>;
    //ref for inplace calculation
    int n = 2;                  //<--- DIMENSION --->
    int i;
	Matrix A = Matrix(n,n);
    Vector b = Vector(n);
    Vector x0 = Vector(n);
    Vector x0_2 = Vector(n);
    Vector b_tr = Vector(n);      //transformed
    Vector x0_tr = Vector(n);     //tr
    Vector x0_2_tr = Vector(n);   //tr
    //VecPtr xmax_tr = nulled(n);  //tr Vector to ptrs to values
    //VecPtr xmin_tr = nulled(n);  //tr Vector to ptrs to values
    Eigen::Matrix<Number, 2, 3> x_tr;
    x_tr.col(2).array() = 0;

    Vector xinhomconst = Vector(n);
    Vector xhomconstmax = Vector(n);
    Vector xhomconstmin = Vector(n);
    Vector factor = Vector(n);
    Vector xvalue = Vector(n);
    //Vector xvalue2 = Vector(n);
    Vector derivFactormax = Vector(n);
    Vector derivFactormin = Vector(n);
    Vector plot_vector = Vector(n);
    Eigen::Array<bool, 1, 2> directmin(n);
    Eigen::Array<bool, 1, 2> directmax(n);
    directmin.setConstant(0);
    directmax.setConstant(0);
    #ifdef TRAJECTORY
        Number timestep = 0.01;
        Number traj_time;
        Vector pts_traj = Vector(n);
        VPolytope<Number> traj_poly;
        std::vector<vector_t<Number>> plot_traj;
    #endif
    Number tend = 1;
    Number delta = 0.01; //segment stepping time
    Matrix V = Matrix(n,n);
    Matrix Vinv = Matrix(n,n);
	Eigen::DiagonalMatrix<Number,2> D; //type Number size 2

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
    x0_2_tr = Vinv*x0_2;
    x_tr.col(0) = x0_tr;
    x_tr.col(1) = x0_2_tr;
    elwise_maxtransformation();
    //x_tr.col(2) = 0 //zeros see upwards
    xinhomconst = b_tr.array() / D.diagonal().array();
    xhomconstmax = xinhomconst.array() + x_tr.col(0).array(); 
    xhomconstmin = xinhomconst.array() + x_tr.col(1).array(); 

    std::vector<vector_t<Number>> ptsxmax_tr;
    std::vector<vector_t<Number>> ptsxmin_tr;
    VPolytope<Number> vpoly_upper;
    VPolytope<Number> vpoly_lower;
    initialize ();        //function pointers + 1.step(derivative+value) 

    //initial value calculation+derivative, possible trajectory value
    //starting on delta: rational numbers might be better here
    std::size_t deltalimit = std::ceil( (tend/delta) );
    loop (deltalimit);  //calculate values according to boolean arrays
    
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
void elwise_maxtransformation( void ) {
    for( i=0; i<n; ++i) {   //check if x0_tr >= x0_2_tr
        if(x_tr(i)(0) < x_tr(i)(1)) {
            x_tr(i)(2) =x_tr(i)(0);
            x_tr(i)(0) = x_tr(i)(1);
            x_tr(i)(1) = x_tr(i)(2);
            x_tr(i)(2) = 1; //mark second column to recognize later
        }
    }
}
void elwise_backtranformation( void ) {
    
    for( i=0; i<n; ++i) {   
        if(x_tr(i)(2) == 1) { //check if x0_tr >= x0_2_tr
            x_tr(i)(2) =x_tr(i)(0);
            x_tr(i)(0) = x_tr(i)(1);
            x_tr(i)(1) = x_tr(i)(2);
            x_tr(i)(2) = 0; //mark second column to recognize later
        }
    }
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
void initialize (void) {
    for(i=0; i<n; ++i) { 
        if (D.diagonal()(i)>0) { //divergence
            if (xhomconstmax(i) >= 0) {
                directmax(i) = true;      //xmax(i) directLine 
                if (xhomconstmin(i) >= 0) {
                    //xmin(i) derivLine
                } else {
                    directmin(i) = true;  //unusual!! xmin(i) directLine
                }
            } else {
                    //xmax(i) derivLine 
                if(xhomconstmin(i) >= 0) {
                    //ERROR upwards and downwards
                } else {
                    directmin(i) = true;  //xmin(i) directLine
                }
            }
        } else { //case 2 and 4
        //convergence
            if (xhomconstmax(i) >=0) {
                directmax(i) = true;      //xmax(i) directLine
                if (xhomconstmin(i) >=0) {
                    //xmin(i) derivLine
                } else {
                    directmin(i) = true;  //xmin(i) directLine
                    //convergence point between initial set
                }
            } else {
                //xmax(i) derivLine
                if (xhomconstmin(i) >=0) {
                    //xmin(i) derivLine
                    //2 convergence points!!
                } else {
                    directmin(i) = true;   //xmin(i) directLine
                }
            }
        }
    }
    //1.step calculation + inserting
    //e^0 = 1
    derivFactormax = xhomconstmax.array()*D.diagonal().array();
    derivFactormin = xhomconstmin.array()*D.diagonal().array();
    plot_vector(0) = 0;
    plot_vector(1) = x_tr(DIM_PLOT)(0);
    ptsxmax_tr.push_back(plot_vector);
    plot_vector(0) = 0;
    plot_vector(1) = x_tr(DIM_PLOT)(1);
    ptsxmin_tr.push_back(plot_vector);
}
    //1.linear value + derivative OR direct value
    //1.1 possible trajectory calculation pushing writing deleting
    //2.pushing,writing,deleting   [maybe flushing in between??]
void loop(std::size_t deltalimit) {
    for(std::size_t j = 0; j <= deltalimit;  ++j) {
    	std::cout << "Time: " << j*delta << std::endl;
        for (i=0; i<n; ++i) {
            factor(i) = std::exp(D.diagonal()(i) *j*delta);
        
            if(directmax(i)) {
                x_tr(i)(0) = xhomconstmax(i)*factor(i) - xinhomconst(i);
            } else {
                x_tr(i)(0) = x_tr(i)(0) + derivFactormax(i)*delta;
                derivFactormax(i) = xhomconstmax(i)*D.diagonal()(i)*factor(i);
            }
            if(directmin(i)) {
                x_tr(i)(1) = xhomconstmin(i)*factor(i) - xinhomconst(i);
            } else {
                x_tr(i)(1) = x_tr(i)(1) + derivFactormin(i)*delta;
                derivFactormin(i) = xhomconstmin(i)*D.diagonal()(i)*factor(i);
            }
        }
        #ifdef ORIGINAL_SYS_PLOT
            elwise_backtranformation();
            plot_vector(0) = j;
            plot_vector(1) = (V*x_tr.col(0))(DIM_PLOT);
            ptsmax_tr.push_back(plot_vector);
            plot_vector(1) = (V*x_tr.col(1))(DIM_PLOT);
        #endif
        #ifndef ORIGINAL_SYS_PLOT
        plot_vector(0) = j;
        plot_vector(1) = x_tr(DIM_PLOT)(0);
        ptsxmax_tr.push_back(plot_vector);
        plot_vector(1) = x_tr(DIM_PLOT)(0);
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
