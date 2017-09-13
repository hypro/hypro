/**
 * Sandbox for the Eigendecomposition project.
 */
#include "datastructures/hybridAutomata/HybridAutomaton.h"
//#include "datastructures/hybridAutomata/LocationManager.h"
#include "parser/flowstar/ParserWrapper.h"
#include "algorithms/eigendecomposition/Transformation.h"
#include "representations/GeometricObject.h"
#include "util/Plotter.h"
#include <Eigen/Eigenvalues>
#include <Eigen/Dense>
//#define PTS_DEBUG          //NO USE
//#include <Eigen/LU>
using namespace hypro;
using Number = double;
//using Matrix<Number> = matrix_t<Number>;
//using Vector<Number> = vector_t<Number>;
//using DiagonalMatrix<Number> = Eigen::DiagonalMatrix<Number,Eigen::Dynamic>;
//using BoolMatrix<Number> = matrix_t<bool>;
using VPoly = VPolytope<Number>;
using Representation = hypro::HPolytope<Number>;

typedef struct Flags {
    //int n; //<--- DIMENSION ---> NEEDED ? CONST BETTER?
    std::size_t DIM_PLOT;      //0..n-1 for the plot
    bool ORIG_SYS_PLOT; //plotting in original system or transformed?
    bool HULLCONSTR;
    bool HULL_PLOT;
    bool TRAJECTORY_PLOT;
    bool ERROR_PLOT;
} Flags;
//  d/dx = Ax+b, xupper=x0, xlower=x0_2
typedef struct Input_equation {
    Matrix<Number> A;
    Vector<Number> x0;
    Vector<Number> x0_2;
    Vector<Number> b;
} In_eq;
typedef struct Invariants {
    Matrix<Number> iAV;
    Vector<Number> ib;
    //TODO: use std::vector<Matrix<Number>> and read from file etc
} Invar;
/***Independent_part_funct stores all independent parts from input
 *  All matrices contain n-column vector for max on column 0 and
 *                      n-column vector for min on column 1
 *  x=xhom*exp(D*t)-xinhom, D containing eigenvalues lambda
 */
typedef struct Independent_part_funct {
    DiagonalMatrix<Number> D;
    Matrix<Number> xinhom;
    Number delta;
    std::size_t deltalimit;
} Ind_f;
typedef struct Dependent_part_funct {
    Matrix<Number> xhom;
    Matrix<Number> x_tr;
} Dep_f;
/*** Evaluation of resulting functions e^x/-e^x/e^(-x)/-e^(-x)
 *   Evaluation of derivative to calculate safe approximation
 */
typedef struct Eval_functions {
    Matrix<Number> deriv;
    BoolMatrix direct;
} Eval_f;
typedef struct Flowpipe_segment {
    std::vector<Vector<Number>> upper;
    std::vector<Vector<Number>> lower;
} Flow_seg;
void declare_structures(const int n, In_eq& in_eq1, Invar& invar, Ind_f& ind_f,
        Dep_f& dep_f, Dep_f& in_traj, Eval_f& eval_f);
//  x0 is column 0 of x_tr
void mark_x0isMin(Matrix<Number>& x_tr, const int n);
void swap_x0isMax(Matrix<Number>& x_tr, const int n);
void initialize (Eval_f& eval_f, Flow_seg& safe_seg, Flow_seg& error_seg,
        std::size_t DIM_PLOT, bool ORIG_SYS_PLOT, const DiagonalMatrix<Number>& D,
        const int n, const Matrix<Number>& V, Dep_f& dep_f);
void loop (std::vector<VPoly>& flow, std::vector<VPoly>& error_flow,
        const Flags& flag1, const Ind_f& ind_f, const int n, const Matrix<Number>& V,
        Eval_f& eval_f, Dep_f& dep_f, Flow_seg& safe_seg, Flow_seg& error_seg);
void trajectory_plot(std::vector<VPoly>& exactflow, std::size_t DIM_PLOT, bool ORIG_SYS_PLOT,
        const Ind_f& ind_f, const int n, const Matrix<Number>& V, const std::size_t traj_scale,
        Dep_f& in_traj);
void plot_addTimeSegment(Flow_seg& safe_seg, std::size_t DIM_PLOT, bool ORIG_SYS_PLOT,
        const std::size_t traj_time, const Matrix<Number>& x_tr, const Matrix<Number>& V, const int n);
void addSegment(std::vector<VPoly>& flow, bool PLOT, Flow_seg& safe_seg,
        std::size_t colorUpper, std::size_t colorLower);

int main()
{
    //use hybrid automaton from file
    const std::string& filename = "../../examples/input/bouncing_ball_inhomogen.model";
	boost::tuple<HybridAutomaton<Number>, reachability::ReachabilitySettings<Number>> ha = parseFlowstarFile<Number>(filename);
    //std::cout << boost::get<0>(ha);
    //hypro::HybridAutomaton<Number> ha_transformed =  HybridAutomaton<Number>( boost::get<0>(ha) );
    //std::cout << ha_transformed;
    HybridAutomaton<Number> original_ha = boost::get<0>(ha);
    Transformation<Number> trafo = Transformation<Number>(original_ha);
    std::cout << "----------    END OF TRANSFORMATION   ------------" << std::endl;
    std::cout << original_ha << std::endl;
    std::cout << "----------    END OF ORIGINAL         ------------" << std::endl;
    trafo.output_HybridAutomaton();
    std::cout << std::endl;
    //std::cout << trafo;
    //TODO clarify if we copy automata inside the transformation or if we assume transfo_ha ISCOPYOF orig_ha
    //--> might be useful to later wrap another class for simple use around on condition number etc
    //TODO initial state input clarifying

    //remind last line is ALWAYS added by parser
    //use friend class of transformation? to calculate flowpipe elements/evaluation
    //adapt function accordingly!
    Flags flag1;
    In_eq in_eq1;               //input system
    Invar invar;                //invariants
    Ind_f ind_f;         //input independent part of e-function
    Dep_f dep_f;        //input dependent part of e-function(values+xhom)
    Dep_f in_traj;          //input dependent trajectory of e-function
    Eval_f eval_f; //evaluation of e-function for hull
    Plotter<Number>& plotter = Plotter<Number>::getInstance();
    Flow_seg safe_seg;          //plotting_segment
    Flow_seg error_seg;         //error_segment
    //*************** RESULT *******************
    std::vector<VPoly> safeflow;
    std::vector<VPoly> exactflow;
    std::vector<VPoly> error_flow;
    const int n = 2;                  //<---System/Matrix Dimension --->
    Matrix<Number> V = Matrix<Number>(n,n);                             //backtransformation
    Matrix<Number> Vinv = Matrix<Number>(n,n);                          //dumped after use
    Vector<Number> b_tr = Vector<Number>(n);                            //transformed and dumped after use
    Vector<Number> tmp  = Vector<Number>(n);

    flag1.DIM_PLOT      = 0;        //0..n-1 for the plot
    flag1.ORIG_SYS_PLOT = false; //plotting in original system or transformed?
    flag1.HULLCONSTR    = true;
    flag1.HULL_PLOT     = false;
    flag1.ERROR_PLOT    = true;
    flag1.TRAJECTORY_PLOT = false;
    Number tend = 20;                                   //dumped after use
    ind_f.delta = 0.1;                              //segment stepping time
    //calculate number of discrete evaluation steps to compare time steps
    ind_f.deltalimit = std::ceil( (tend/ind_f.delta) );
    declare_structures(n, in_eq1, invar, ind_f, dep_f, in_traj, eval_f);
    std::size_t traj_scale = 1; //?needed?-> adapt step size
    //###### INPUT SYSTEM  d/dx = A*x + b  ######
	in_eq1.A << 	0.001, 1,
			        0.001, -0.002;
    in_eq1.b <<    0, -9.81;
    in_eq1.x0<<    100, 0;        //we require in_eq1.x0 > .in_eq1.x0_2 elementwise
    in_eq1.x0_2 << 10, 0;          //else we swap values
    //###### INVARIANTS:    AVV^(-1)x leq b ######
    invar.iAV<<    -1, 0,
                    0, 0;
    invar.ib.array() = 0;

	//std::cout << "d/dx = A*x+b, A:"<< std::endl << in_eq1.A<< std::endl;
	//std::cout << "b: "<< std::endl << in_eq1.b << std::endl;
    //std::cout << "in_eq1.x0: "<< std::endl << in_eq1.x0 << std::endl;
    //std::cout << "in_eq1.x0_2: "<< std::endl << in_eq1.x0_2 << std::endl;

    Eigen::EigenSolver<Matrix<Number>> es(in_eq1.A);    //decompose matrix directly + constructor
    V << es.eigenvectors().real();
    ind_f.D.diagonal() << es.eigenvalues().real();
    Vinv = V.inverse();
    //std::cout << "Eigenvectors(V): "<< std::endl << V << std::endl;
	//std::cout << "Vinverse: "<< std::endl << Vinv << std::endl;
	//std::cout << "Eigenvalues: "<< std::endl << ind_f.D.diagonal() << std::endl;
    //stop on bad conditioning ??
    //TODO checkups
    //invariants+transformed system
    b_tr = Vinv*in_eq1.b;
    dep_f.x_tr.col(0) = Vinv*in_eq1.x0;
    dep_f.x_tr.col(1) = Vinv*in_eq1.x0_2;
    in_traj.x_tr.col(0) = dep_f.x_tr.col(0);
    in_traj.x_tr.col(1) = dep_f.x_tr.col(1);
    //std::cout << "x_transformed: " << std::endl << in_traj.x_tr << std::endl;
    invar.iAV = invar.iAV*V;                    //transform invariant A(iA)
    //std::cout << "Invariants: A*V="<<std::endl << invar.iAV;
    mark_x0isMin(dep_f.x_tr, n);
    swap_x0isMax(dep_f.x_tr, n);
    //calculate constant values for e-function
    ind_f.xinhom = b_tr.array() / ind_f.D.diagonal().array();
    dep_f.xhom.col(0) = ind_f.xinhom.array() + dep_f.x_tr.col(0).array();
    dep_f.xhom.col(1) = ind_f.xinhom.array() + dep_f.x_tr.col(1).array();
    in_traj.xhom.col(0) = ind_f.xinhom.array() + in_traj.x_tr.col(0).array();
    in_traj.xhom.col(1) = ind_f.xinhom.array() + in_traj.x_tr.col(1).array();
    //std::cout << "xhom: "<< std::endl << dep_f.xhom;
    // -----------------------   to another class ------------------------------
    initialize (eval_f, safe_seg, error_seg,flag1.DIM_PLOT, flag1.ORIG_SYS_PLOT,
        ind_f.D, n, V,  dep_f);
    if (flag1.TRAJECTORY_PLOT) {
        trajectory_plot(exactflow, flag1.DIM_PLOT, flag1.ORIG_SYS_PLOT, ind_f, n, V,
            traj_scale, in_traj);
    }
    if (flag1.HULLCONSTR) {
        loop (safeflow, error_flow, flag1, ind_f, n, V, eval_f, dep_f, safe_seg, error_seg);
    }
    //checking invariants for jump
    //for segment in Segments [std::vector<VPoly>]
    //std::pair<bool,VPoly> res = VPoly.satisfiesHalfspace(AV,b_AV);
    //to check bool=false -> empty
    //otherwise adjust upper+lower bounds of polytope
    plotter.plot2d();
    plotter.plotGen();


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


void declare_structures(const int n, In_eq& in_eq1, Invar& invar, Ind_f& ind_f,
        Dep_f& dep_f, Dep_f& in_traj, Eval_f& eval_f) {
    in_eq1.A = Matrix<Number>(n,n);
    in_eq1.b = Vector<Number>(n);
    in_eq1.x0 = Vector<Number>(n);
    in_eq1.x0_2 = Vector<Number>(n);
    invar.iAV = Matrix<Number>(n,n);
    invar.ib  = Vector<Number>(n);
    ind_f.xinhom = Vector<Number>(n);
	ind_f.D = DiagonalMatrix<Number>(2); //type Number size 2
    dep_f.x_tr = Matrix<Number>::Zero(n,3);
    dep_f.x_tr.col(2).array() = 0;
    dep_f.xhom = Matrix<Number>::Zero(2,2);
    in_traj.x_tr = Matrix<Number>::Zero(n,2);
    in_traj.xhom = Matrix<Number>::Zero(n,2);
    eval_f.deriv = Matrix<Number>(n,2);
    eval_f.direct     = BoolMatrix(n,2);
    eval_f.direct.setConstant(0);
}
//mark if in transformed system x0<x0_2 in 3rd column
void mark_x0isMin(Matrix<Number>& x_tr, const int n) {
    for(int i=0; i<n; ++i) {   //check if x0_tr >= x0_2_tr
        if(x_tr(i,0) < x_tr(i,1)) {
            x_tr(i,2) = 1; //mark second column to recognize later
        }
    }
}
//check if in transformed system x0<x0_2 and swap if needed
void swap_x0isMax(Matrix<Number>& x_tr, const int n) {
    //std::cout << "x_tr beforeback: "<< std::endl << x_tr << std::endl;
    Vector<Number> tmp = Vector<Number>(n);
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
void initialize (Eval_f& eval_f, Flow_seg& safe_seg, Flow_seg& error_seg,
        std::size_t DIM_PLOT, bool ORIG_SYS_PLOT, const DiagonalMatrix<Number>& D,
        const int n, const Matrix<Number>& V, Dep_f& dep_f) {
    Vector<Number> plot_vector = Vector<Number>(n);
    const Matrix<Number> x_tr_error = Matrix<Number>::Zero(n,2);
    for(int i=0; i<n; ++i) {
        if (D.diagonal()(i)>0) { //divergence
            if (dep_f.xhom(i,0) >= 0) {  //
                eval_f.direct(i,0) = true;      //xmax(i) directLine
                if (dep_f.xhom(i,1) > 0) {
                    //xmin(i) derivLine
                } else {    //xmin: -e^x
                    eval_f.direct(i,1) = true;  //unusual!! xmin(i) directLine
                    std::cout<<"set evolves as opposite diverging trajectoris"<<std::endl;
                }
            } else {    //xmax: -e^x
                    //xmax(i) derivLine
                if(dep_f.xhom(i,1) > 0) {
                    std::cout<<"ERROR upwards and downwards"<<std::endl;
                    //ERROR upwards and downwards
                } else {
                    eval_f.direct(i,1) = true;  //xmin(i) directLine
                }
            }
        } else { //e^(-x) and -e^(-x) whereas -x fixed here
        //convergence
            if (dep_f.xhom(i,0) <= 0) {  //xmax:-e^(-x)
                eval_f.direct(i,0) = true;      //xmax(i) directLine
                if (dep_f.xhom(i,1) < 0) {
                    //xmin(i) derivLine
                } else {
                    eval_f.direct(i,1) = true;  //xmin(i) directLine
                    std::cout<<"convergence point between initial set"<<std::endl;
                }
            } else {    //xmax:e^(-x)
                //xmax(i) derivLine
                if (dep_f.xhom(i,1) >=0) {
                    eval_f.direct(i,1) = true;   //xmin(i) directLine
                } else {
                    //xmin(i) derivLine
                    std::cout<<"2 convergence points, check if intended"<<std::endl;
                }
            }
        }
    }
    //std::cout<<"eval_f.direct:"<<std::endl<<eval_f.direct;
    //t=0 step calculation + inserting, e^0 = 1
    eval_f.deriv.col(0) = dep_f.xhom.col(0).array()*D.diagonal().array();
    eval_f.deriv.col(1) = dep_f.xhom.col(1).array()*D.diagonal().array();
    if (ORIG_SYS_PLOT) {
        swap_x0isMax(dep_f.x_tr, n);
        plot_addTimeSegment(safe_seg, DIM_PLOT, ORIG_SYS_PLOT, 0, dep_f.x_tr, V, n);
        plot_addTimeSegment(error_seg, DIM_PLOT, ORIG_SYS_PLOT, 0, x_tr_error, V, n);
        swap_x0isMax(dep_f.x_tr, n);
    } else {
        plot_addTimeSegment(safe_seg, DIM_PLOT, ORIG_SYS_PLOT, 0, dep_f.x_tr, V, n);
        plot_addTimeSegment(error_seg, DIM_PLOT, ORIG_SYS_PLOT, 0, x_tr_error, V, n);
    }
}
    //1.linear value + deriv OR direct value
    //2.pushing,writing,deleting
void loop (std::vector<VPoly>& flow, std::vector<VPoly>& error_flow, const Flags& flag1,
        const Ind_f& ind_f, const int n, const Matrix<Number>& V, Eval_f& eval_f, Dep_f& dep_f,
        Flow_seg& safe_seg, Flow_seg& error_seg) {
    Vector<Number> factor = Vector<Number>::Zero(n);
    Matrix<Number> x_tr_error = Matrix<Number>::Zero(n,3);
    x_tr_error.col(2) = dep_f.x_tr.col(2).array();
    //WE ASSUME we always want to check 1 timestep
    for(std::size_t j = 1; j <= ind_f.deltalimit;  ++j) {
    	//std::cout << "Time: " << j*delta << std::endl;
        for (int i=0; i<n; ++i) {
            factor(i) = std::exp(ind_f.D.diagonal()(i) *j*ind_f.delta);
            if(eval_f.direct(i,0)) { //MAX VALUES
                //e^x OR -e^(-x)
                dep_f.x_tr(i,0) = dep_f.xhom(i,0)*factor(i) - ind_f.xinhom(i);
                //TODO fancy calculation staying the same
            } else {
                //e^(-x) OR -e^x
                dep_f.x_tr(i,0) = dep_f.x_tr(i,0) + eval_f.deriv(i,0)*ind_f.delta;
                eval_f.deriv(i,0) = dep_f.xhom(i,0)*ind_f.D.diagonal()(i)*factor(i);
                //if ERROR_CALC MAX: error = deriv - e-function --> function pointer?
                x_tr_error(i,0) = dep_f.x_tr(i,0) - (dep_f.xhom(i,0)*factor(i) - ind_f.xinhom(i));
            }
            if(eval_f.direct(i,1)) { //MIN VALUES
                dep_f.x_tr(i,1) = dep_f.xhom(i,1)*factor(i) - ind_f.xinhom(i);
                //TODO fancy calculation staying the same
            } else {
                dep_f.x_tr(i,1) = dep_f.x_tr(i,1) + eval_f.deriv(i,1)*ind_f.delta;
                eval_f.deriv(i,1) = dep_f.xhom(i,1)*ind_f.D.diagonal()(i)*factor(i);
                x_tr_error(i,1) = (dep_f.xhom(i,1)*factor(i) - ind_f.xinhom(i)) - dep_f.x_tr(i,1);
            }
        }
        //check invariants in transformed system

        if (flag1.ORIG_SYS_PLOT) {
            swap_x0isMax(dep_f.x_tr, n);
            plot_addTimeSegment(safe_seg, flag1.DIM_PLOT, flag1.ORIG_SYS_PLOT,
                j, dep_f.x_tr, V, n);
            swap_x0isMax(dep_f.x_tr, n);
        } else {
            plot_addTimeSegment(safe_seg, flag1.DIM_PLOT, flag1.ORIG_SYS_PLOT,
                j, dep_f.x_tr, V, n);
        }
        //fill flowpipe and on FLAG add Object to plotter
        addSegment(flow, flag1.HULL_PLOT, safe_seg, plotting::colors[plotting::red],
            plotting::colors[plotting::blue]);
        if (flag1.ORIG_SYS_PLOT) {
            swap_x0isMax(x_tr_error, n);
            plot_addTimeSegment(error_seg, flag1.DIM_PLOT, flag1.ORIG_SYS_PLOT,
                j, x_tr_error, V, n);
            swap_x0isMax(x_tr_error, n);
        } else {
            plot_addTimeSegment(error_seg, flag1.DIM_PLOT, flag1.ORIG_SYS_PLOT,
                j, x_tr_error, V, n);
        }
        //fill flowpipe and on FLAG add Object to plotter
        addSegment(error_flow, flag1.ERROR_PLOT, error_seg, plotting::colors[plotting::red],
            plotting::colors[plotting::blue]);
    }
}

void trajectory_plot(std::vector<VPoly>& exactflow, std::size_t DIM_PLOT, bool ORIG_SYS_PLOT,
        const Ind_f& ind_f, const int n, const Matrix<Number>& V, const std::size_t traj_scale,
        Dep_f& traj_tr) {
    Flow_seg traj_flow_seg;
    Vector<Number> factor = Vector<Number>::Zero(n);
    plot_addTimeSegment(traj_flow_seg, DIM_PLOT, ORIG_SYS_PLOT, 0, traj_tr.x_tr, V, n);
    for(std::size_t traj_time = 1; traj_time<=traj_scale*ind_f.deltalimit; traj_time+=1) {
        for (int i=0; i<n; ++i) {
            factor(i) = std::exp(ind_f.D.diagonal()(i)*traj_time*ind_f.delta/traj_scale);
        }
        //std::cout<<"traj_time"<<traj_time<<" factor "<<std::endl<<factor<<std::endl;
        //depends what we want to plot here
        traj_tr.x_tr.col(0) = traj_tr.xhom.col(0).array()*factor.array()  - ind_f.xinhom.array();
        traj_tr.x_tr.col(1) = traj_tr.xhom.col(1).array()*factor.array()  - ind_f.xinhom.array();
        plot_addTimeSegment(traj_flow_seg, DIM_PLOT, ORIG_SYS_PLOT, traj_time, traj_tr.x_tr, V, n);
        addSegment(exactflow, true, traj_flow_seg, plotting::colors[plotting::green],
            plotting::colors[plotting::green]);
    }
}
void plot_addTimeSegment(Flow_seg& flow_segment, std::size_t DIM_PLOT, bool ORIG_SYS_PLOT,
        std::size_t traj_time, const Matrix<Number>& x_tr, const Matrix<Number>& V, const int n) {
    Vector<Number> plot_vector = Vector<Number>(n);
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
void addSegment(std::vector<VPoly>& flow, bool PLOT, Flow_seg& flow_segment,
        std::size_t colorUpper, std::size_t colorLower) {
    Plotter<Number>& plotter = Plotter<Number>::getInstance();
    VPoly vpoly_upper = VPoly(flow_segment.upper);
    VPoly vpoly_lower = VPoly(flow_segment.lower);
    flow.push_back(vpoly_upper.unite(vpoly_lower));
    if(PLOT) {
        unsigned v = plotter.addObject(vpoly_upper.vertices());
        plotter.setObjectColor(v, colorUpper);
        unsigned w = plotter.addObject(vpoly_lower.vertices());
        plotter.setObjectColor(w, colorLower);
    }
    flow_segment.upper.erase( flow_segment.upper.begin() );
    flow_segment.lower.erase( flow_segment.lower.begin() );
}
