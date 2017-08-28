/**
 * Sandbox for the Eigendecomposition project.
 */

#include "representations/GeometricObject.h"
#include "util/Plotter.h"
#include <Eigen/Eigenvalues>
#include <Eigen/Dense>
//#define PTS_DEBUG          //NO USE
//#include <Eigen/LU>
using namespace hypro;
using Number = double;
using Matrix = matrix_t<Number>;
using Vector = vector_t<Number>;
using DiagonalMatrix = Eigen::DiagonalMatrix<Number,Eigen::Dynamic>;
using BoolMatrix = matrix_t<bool>;
typedef struct Flags {
    //int n; //<--- DIMENSION ---> NEEDED ? CONST BETTER?
    std::size_t DIM_PLOT;      //0..n-1 for the plot
    bool ORIG_SYS_PLOT; //plotting in original system or transformed?
    bool HULLCONSTR;
    bool TRAJECTORY;
    bool ERROR_PLOT;
} Flags;
typedef struct Input_equation {
    Matrix A;
    Vector x0;
    Vector x0_2;
    Vector b;
} In_eq;
typedef struct Invariants {
    Matrix iAV;
    Vector ib;
    //TODO: use std::vector<Matrix> and read from file etc
} Invar;
/***Eval_sol_funct contains values to evaluate e-function
 *  All matrices contain n-column vector for max on column 0 and 
 *                      n-column vector for min on column 1
 *  x=xhom*exp(D*t)-xinhom, D containing eigenvalues lambda
 */
 //TODO denote CONSTANT 0 as max 1 as min according to index in source code
typedef struct Eval_sol_funct {
    DiagonalMatrix D;
    Matrix xinhom;
    Number delta;
    std::size_t deltalimit;
} Ev_sol_f;
typedef struct Input_part_funct { 
    Matrix xhom;
    Matrix x_tr;
} In_part_f;
typedef struct Eval_e_functions {
    Matrix derivative;
    BoolMatrix direct;
} Eval_e_funct;
typedef struct Flowpipe_segment { 
    std::vector<Vector> upper;
    std::vector<Vector> lower;
} Flow_seg;

void mark_x0isMin(Matrix& x_tr, int n);
void swap_x0isMax(Matrix& x_tr, int n);
void initialize (In_part_f& in_part_f, const DiagonalMatrix& D, Eval_e_funct& eval_e_funct1, 
        Flow_seg& safe_seg, const int n, const Matrix& V, std::size_t DIM_PLOT, bool ORIG_SYS_PLOT);
void loop (std::vector<VPolytope<Number>>& flowpipe, const Ev_sol_f& ev_sol_f1, 
        Eval_e_funct& eval_e_funct1, In_part_f& in_part_f, const int n, Flow_seg& safe_seg, 
        const Matrix& V, std::size_t DIM_PLOT, bool ORIG_SYS_PLOT);
void trajectory_plot(std::vector<VPolytope<Number>>& exactflowpipe, const Ev_sol_f& ev_sol_f1, 
        const int n, const Matrix& V, In_part_f& in_traj, const std::size_t traj_scale,
        std::size_t DIM_PLOT, bool ORIG_SYS_PLOT);
void plot_addTimeSegment(std::size_t traj_time, const Matrix& x_tr, const Matrix& V, 
        const int n, Flow_seg& safe_seg, std::size_t DIM_PLOT, bool ORIG_SYS_PLOT);
void addSegment(std::vector<VPolytope<Number>>& flowpipe, Flow_seg& safe_seg, 
        std::size_t colorUpper, std::size_t colorLower);

int main()
{
    Flags flag1;
    flag1.HULLCONSTR = true;
    flag1.TRAJECTORY = false;
    int n = 2;                  //<---System/Matrix Dimension --->
    flag1.DIM_PLOT = 0;        //0..n-1 for the plot
    flag1.ORIG_SYS_PLOT = true; //plotting in original system or transformed?
    In_eq in_eq1;               //input system
    in_eq1.A = Matrix(n,n);
    in_eq1.b = Vector(n);
    in_eq1.x0 = Vector(n);
    in_eq1.x0_2 = Vector(n);
    Invar invar;                //invariants
    invar.iAV = Matrix(n,n);
    invar.ib  = Vector(n);
    Vector b_tr = Vector(n);                            //transformed and dumped after use
    Ev_sol_f ev_sol_f1;         //input independent part of e-function
    ev_sol_f1.xinhom = Vector(n); 
	ev_sol_f1.D = DiagonalMatrix(2); //type Number size 2
    Number tend = 20;                                   //dumped after use
    ev_sol_f1.delta = 0.1;                              //segment stepping time
    //calculate number of discrete evaluation steps to compare time steps
    ev_sol_f1.deltalimit = std::ceil( (tend/ev_sol_f1.delta) );
    In_part_f in_part_f;        //input dependent part of safe approximation of e-function
    in_part_f.x_tr = Matrix::Zero(n,3);
    in_part_f.x_tr.col(2).array() = 0;
    in_part_f.xhom = Matrix::Zero(2,2);
    In_part_f in_traj;          //input dependent trajectory of e-function
    in_traj.x_tr = Matrix::Zero(n,2);
    in_traj.xhom = Matrix::Zero(n,2);
    Eval_e_funct eval_e_funct1; //evaluation of e-function for hull
    eval_e_funct1.derivative = Matrix(n,2);
    eval_e_funct1.direct     = BoolMatrix(n,2);
    eval_e_funct1.direct.setConstant(0);
    Plotter<Number>& plotter = Plotter<Number>::getInstance();
    Flow_seg safe_seg;          //plotting_segment

    std::size_t traj_scale = 1; //?needed?-> adapt step size
    Matrix V = Matrix(n,n);                             //backtransformation
    Matrix Vinv = Matrix(n,n);                          //dumped after use
    //*************** RESULT *******************
    std::vector<VPolytope<Number>> safeflowpipe;
    std::vector<VPolytope<Number>> exactflowpipe;
    //######  d/dx = A*x + b  ######
	in_eq1.A << 	0.001, 1,
			        0.001, -0.002;
    in_eq1.b <<    0, -9.81;
    in_eq1.x0<<    100, 0;        //we require in_eq1.x0 > .in_eq1.x0_2 elementwise
    in_eq1.x0_2 << 10, 0;          //else we swap values
    //######  AVV^(-1)x leq b ######
    //invar.iAV = in_eq1.A;
    invar.ib.array() = 0;

	std::cout << "d/dx = A*x+b, A:"<< std::endl << in_eq1.A<< std::endl;
	std::cout << "b: "<< std::endl << in_eq1.b << std::endl;
    std::cout << "in_eq1.x0: "<< std::endl << in_eq1.x0 << std::endl;
    std::cout << "in_eq1.x0_2: "<< std::endl << in_eq1.x0_2 << std::endl;
    //decompose directly + constructor
    Eigen::EigenSolver<Matrix> es(in_eq1.A);
    V << es.eigenvectors().real();
    ev_sol_f1.D.diagonal() << es.eigenvalues().real();
    Vinv = V.inverse();
    std::cout << "Eigenvectors(V): "<< std::endl << V << std::endl;
	std::cout << "Vinverse: "<< std::endl << Vinv << std::endl;
	std::cout << "Eigenvalues: "<< std::endl << ev_sol_f1.D.diagonal() << std::endl;
    //stop on bad conditioning ??

    //invariants+transformed system
    b_tr = Vinv*in_eq1.b;
    in_part_f.x_tr.col(0) = Vinv*in_eq1.x0;
    in_part_f.x_tr.col(1) = Vinv*in_eq1.x0_2;
    in_traj.x_tr.col(0) = in_part_f.x_tr.col(0);
    in_traj.x_tr.col(1) = in_part_f.x_tr.col(1);
    std::cout << "x_transformed: " << std::endl << in_traj.x_tr << std::endl;
    //invar.iAV = invar.iAV*(1,0)*V;    //TODO fix
    std::cout << "Invariants: A*V="<<std::endl << invar.iAV;
    //std::cout << "x_tr_bef_maxtrafo: "<< std::endl << x_tr << std::endl;
    mark_x0isMin(in_part_f.x_tr, n); 
    swap_x0isMax(in_part_f.x_tr, n);
    //std::cout << "x_tr_after_maxtrafo: "<< std::endl << x_tr << std::endl;
    ev_sol_f1.xinhom = b_tr.array() / ev_sol_f1.D.diagonal().array();
    in_part_f.xhom.col(0) = ev_sol_f1.xinhom.array() + in_part_f.x_tr.col(0).array();
    in_part_f.xhom.col(1) = ev_sol_f1.xinhom.array() + in_part_f.x_tr.col(1).array();
    in_traj.xhom.col(0) = ev_sol_f1.xinhom.array() + in_traj.x_tr.col(0).array();
    in_traj.xhom.col(1) = ev_sol_f1.xinhom.array() + in_traj.x_tr.col(1).array();
    std::cout << "xhomconstmaxmin: "<< std::endl << in_part_f.xhom;
    initialize (in_part_f, ev_sol_f1.D, eval_e_funct1, safe_seg, 
                n, V, flag1.DIM_PLOT, flag1.ORIG_SYS_PLOT);

    //traj_tr, traj_homconst, traj_scale
    if (flag1.TRAJECTORY) {
        trajectory_plot(exactflowpipe, ev_sol_f1, n, V, in_traj, 
            traj_scale, flag1.DIM_PLOT, flag1.ORIG_SYS_PLOT);
    }
    if (flag1.HULLCONSTR) {
    loop (safeflowpipe, ev_sol_f1, eval_e_funct1, in_part_f, n, safe_seg, V, 
            flag1.DIM_PLOT, flag1.ORIG_SYS_PLOT);
    }
    //checking invariants for jump
    //std::pair<bool,VPolytope> res = Segment.satisfiesHalfspace(AV,b_AV);
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

//mark if in transformed system x0<x0_2 in 3rd column
void mark_x0isMin(Matrix& x_tr, const int n) {
    for(int i=0; i<n; ++i) {   //check if x0_tr >= x0_2_tr
        if(x_tr(i,0) < x_tr(i,1)) {
            x_tr(i,2) = 1; //mark second column to recognize later
        }
    }
}
//check if in transformed system x0<x0_2 and swap if needed
void swap_x0isMax(Matrix& x_tr, const int n) {
    //std::cout << "x_tr beforeback: "<< std::endl << x_tr << std::endl;
    Vector tmp = Vector(n);
    for(int i=0; i<n; ++i) {
        if(x_tr(i,2) == 1) { 
            tmp(i)    = x_tr(i,0);
            x_tr(i,0) = x_tr(i,1);
            x_tr(i,1) = tmp(i);
        }
    }
    //std::cout << "x_tr afterback: "<< std::endl << x_tr << std::endl;
}
//1. assign e-Function behavior 2. calculate initial values
    //divergence: D>0
    //convergence D<0, 1 or 2 points
    //remind we assume x0 > x0_2 element wise and set addresses accordingly
            //case1:  e^x      --- D>0, xhomconst>0
            //case2: -e^(-x)   --- etc
            //case3: -e^(x)    --- D>0, xhomconst<0
            //case4:  e^(-x)   --- etc
void initialize (In_part_f& in_approx, const DiagonalMatrix& D, Eval_e_funct& eval_e_funct1, 
        Flow_seg& safe_seg, const int n, const Matrix& V, std::size_t DIM_PLOT, bool ORIG_SYS_PLOT) {
    Vector plot_vector = Vector(n);
    for(int i=0; i<n; ++i) {
        if (D.diagonal()(i)>0) { //divergence
            if (in_approx.xhom(i,0) >= 0) {  //
                eval_e_funct1.direct(i,0) = true;      //xmax(i) directLine
                if (in_approx.xhom(i,1) > 0) {
                    //xmin(i) derivLine
                } else {    //xmin: -e^x
                    eval_e_funct1.direct(i,1) = true;  //unusual!! xmin(i) directLine
                    std::cout<<"set evolves as opposite diverging trajectoris"<<std::endl;
                }
            } else {    //xmax: -e^x
                    //xmax(i) derivLine
                if(in_approx.xhom(i,1) > 0) {
                    std::cout<<"ERROR upwards and downwards"<<std::endl;
                    //ERROR upwards and downwards
                } else {
                    eval_e_funct1.direct(i,1) = true;  //xmin(i) directLine
                }
            }
        } else { //e^(-x) and -e^(-x) whereas -x fixed here
        //convergence
            if (in_approx.xhom(i,0) <= 0) {  //xmax:-e^(-x)
                eval_e_funct1.direct(i,0) = true;      //xmax(i) directLine
                if (in_approx.xhom(i,1) < 0) {
                    //xmin(i) derivLine
                } else {
                    eval_e_funct1.direct(i,1) = true;  //xmin(i) directLine
                    std::cout<<"convergence point between initial set"<<std::endl;
                }
            } else {    //xmax:e^(-x)
                //xmax(i) derivLine
                if (in_approx.xhom(i,1) >=0) {
                    eval_e_funct1.direct(i,1) = true;   //xmin(i) directLine
                } else {
                    //xmin(i) derivLine
                    std::cout<<"2 convergence points, check if intended"<<std::endl;
                }
            }
        }
    }
    //std::cout<<"eval_e_funct1.direct:"<<std::endl<<eval_e_funct1.direct;
    //std::cout << "in_approx.xhom: "<< std::endl << x0_2 << std::endl;
    //1.step calculation + inserting
    //e^0 = 1
    eval_e_funct1.derivative.col(0) = in_approx.xhom.col(0).array()*D.diagonal().array();
    eval_e_funct1.derivative.col(1) = in_approx.xhom.col(1).array()*D.diagonal().array();
    if (ORIG_SYS_PLOT) {
        swap_x0isMax(in_approx.x_tr, n);
        plot_addTimeSegment(0, in_approx.x_tr, V, n, safe_seg, DIM_PLOT, ORIG_SYS_PLOT);
        swap_x0isMax(in_approx.x_tr, n);
    } else {
        plot_addTimeSegment(0, in_approx.x_tr, V, n, safe_seg, DIM_PLOT, ORIG_SYS_PLOT);
    }

    //STARTING POINT
}
    //1.linear value + derivative OR direct value
    //1.1 possible trajectory calculation pushing writing deleting
    //2.pushing,writing,deleting   [maybe flushing in between??]

void loop (std::vector<VPolytope<Number>>& flowpipe, const Ev_sol_f& ev_sol_f1, 
        Eval_e_funct& eval_e_funct1, In_part_f& in_part_f, const int n, Flow_seg& safe_seg, 
        const Matrix& V, std::size_t DIM_PLOT, bool ORIG_SYS_PLOT) {
    //bool _ERROR_PLOT_, 
    Vector factor = Vector::Zero(n);
    //Matrix x_tr_error = Matrix(n,2);
    //WE ASSUME we always want to check 1 timestep
    for(std::size_t j = 1; j <= ev_sol_f1.deltalimit;  ++j) {
    	//std::cout << "Time: " << j*delta << std::endl;
        for (int i=0; i<n; ++i) {
            factor(i) = std::exp(ev_sol_f1.D.diagonal()(i) *j*ev_sol_f1.delta);
            if(eval_e_funct1.direct(i,0)) {
                //e^x OR -e^(-x)
                in_part_f.x_tr(i,0) = in_part_f.xhom(i,0)*factor(i) - ev_sol_f1.xinhom(i);
            } else {
                //e^(-x) OR -e^x
                in_part_f.x_tr(i,0) = in_part_f.x_tr(i,0) + eval_e_funct1.derivative(i,0)*ev_sol_f1.delta;
                eval_e_funct1.derivative(i,0) = in_part_f.xhom(i,0)*ev_sol_f1.D.diagonal()(i)*factor(i);
            }
            if(eval_e_funct1.direct(i,1)) {
                in_part_f.x_tr(i,1) = in_part_f.xhom(i,1)*factor(i) - ev_sol_f1.xinhom(i);
            } else {
                in_part_f.x_tr(i,1) = in_part_f.x_tr(i,1) + eval_e_funct1.derivative(i,1)*ev_sol_f1.delta;
                eval_e_funct1.derivative(i,1) = in_part_f.xhom(i,1)*ev_sol_f1.D.diagonal()(i)*factor(i);
            }
        }
        //x_tr_error.column(0).array() = ev_sol_f1.xhom.column(0).array()*factor.array()-ev_sol_f1.xinhom.array();
        //x_tr_error.column(1).array() = ev_sol_f1.xhom.column(1).array()*factor.array()-ev_sol_f1.xinhom.array();
        //x_tr_error.column(0) = x_tr.column(0) - x_tr_error;
        //x_tr_error.column(1) -= x_tr.column(1);
        if (ORIG_SYS_PLOT) {
            swap_x0isMax(in_part_f.x_tr, n);
            plot_addTimeSegment(j, in_part_f.x_tr, V, n, safe_seg, DIM_PLOT, ORIG_SYS_PLOT);
            swap_x0isMax(in_part_f.x_tr, n);
        } else {
            plot_addTimeSegment(j, in_part_f.x_tr, V, n, safe_seg, DIM_PLOT, ORIG_SYS_PLOT);
        }
        addSegment(flowpipe, safe_seg, plotting::colors[plotting::red], 
            plotting::colors[plotting::blue]);
    }
}

void trajectory_plot(std::vector<VPolytope<Number>>& exactflowpipe, const Ev_sol_f& ev_sol_f1, 
        const int n, const Matrix& V, In_part_f& traj_tr, const std::size_t traj_scale, 
        std::size_t DIM_PLOT, bool ORIG_SYS_PLOT) {
    Flow_seg traj_flow_seg;
    Vector factor = Vector::Zero(n);
    plot_addTimeSegment(0, traj_tr.x_tr, V, n, traj_flow_seg, DIM_PLOT, ORIG_SYS_PLOT);
    for(std::size_t traj_time = 1; traj_time<=traj_scale*ev_sol_f1.deltalimit; traj_time+=1) {
        for (int i=0; i<n; ++i) {
            factor(i) = std::exp(ev_sol_f1.D.diagonal()(i)*traj_time*ev_sol_f1.delta/traj_scale);
        }
        //std::cout<<"traj_time"<<traj_time<<" factor "<<std::endl<<factor<<std::endl;
        //depends what we want to plot here
        traj_tr.x_tr.col(0) = traj_tr.xhom.col(0).array()*factor.array()  - ev_sol_f1.xinhom.array();
        traj_tr.x_tr.col(1) = traj_tr.xhom.col(1).array()*factor.array()  - ev_sol_f1.xinhom.array();
        plot_addTimeSegment(traj_time, traj_tr.x_tr, V, n, traj_flow_seg, DIM_PLOT, ORIG_SYS_PLOT);
        addSegment(exactflowpipe, traj_flow_seg, plotting::colors[plotting::green], 
            plotting::colors[plotting::green]);
    }
}
void plot_addTimeSegment(std::size_t traj_time, const Matrix& x_tr, const Matrix& V, 
        const int n, Flow_seg& flow_segment, std::size_t DIM_PLOT, bool ORIG_SYS_PLOT) {
    Vector plot_vector = Vector(n);
    plot_vector(0) = traj_time;
    if(ORIG_SYS_PLOT) {
        plot_vector(1) = (V*x_tr.col(0))(DIM_PLOT);
        flow_segment.upper.push_back(plot_vector);
        plot_vector(1) = (V*x_tr.col(1))(DIM_PLOT);
    } else {
        plot_vector(1) = (x_tr.col(0))(DIM_PLOT);
        flow_segment.upper.push_back(plot_vector);
        plot_vector(1) = (x_tr.col(1))(DIM_PLOT);
    }
    flow_segment.lower.push_back(plot_vector);
}
void addSegment(std::vector<VPolytope<Number>>& flowpipe, Flow_seg& flow_segment, 
        std::size_t colorUpper, std::size_t colorLower) { 
    Plotter<Number>& plotter = Plotter<Number>::getInstance();
    VPolytope<Number> vpoly_upper = VPolytope<Number>(flow_segment.upper);
    VPolytope<Number> vpoly_lower = VPolytope<Number>(flow_segment.lower);
    flowpipe.push_back(vpoly_upper.unite(vpoly_lower));
    unsigned v = plotter.addObject(vpoly_upper.vertices());
    plotter.setObjectColor(v, colorUpper);
    unsigned w = plotter.addObject(vpoly_lower.vertices());
    plotter.setObjectColor(w, colorLower);
    flow_segment.upper.erase( flow_segment.upper.begin() );
    flow_segment.lower.erase( flow_segment.lower.begin() );
}
