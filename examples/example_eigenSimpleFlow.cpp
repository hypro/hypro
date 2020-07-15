/**
 * Sandbox for the Eigendecomposition project.
 */
#include "algorithms/eigendecomposition/Transformation.h"
#include "datastructures/HybridAutomaton/HybridAutomaton.h"
#include "parser/antlr4-flowstar/ParserWrapper.h"
#include "representations/GeometricObjectBase.h"
#include "util/plotting/Plotter.h"
using namespace hypro;
using Number = double;
using VPoly = VPolytope<Number>;
// using Representation = hypro::HPolytope<Number>;

namespace hypro {
namespace detail {
typedef struct Flags {
	// int n; //<--- DIMENSION ---> NEEDED ? CONST BETTER?
	std::size_t DIM_PLOT;  // 0..n-1 for the plot
	bool ORIG_SYS_PLOT;	   // plotting in original system or transformed?
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
	// TODO: use std::vector<Matrix<Number>> and read from file etc
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
void declare_structures( const int n, In_eq &in_eq1, Invar &invar, Ind_f &ind_f,
						 Dep_f &dep_f, Dep_f &in_traj, Eval_f &eval_f );
//  x0 is column 0 of x_tr
void mark_x0isMin( Matrix<Number> &x_tr, const int n );
void swap_x0isMax( Matrix<Number> &x_tr, const int n );
void initialize( Eval_f &eval_f, Flow_seg &safe_seg, Flow_seg &error_seg,
				 std::size_t DIM_PLOT, bool ORIG_SYS_PLOT,
				 const DiagonalMatrix<Number> &D, const int n,
				 const Matrix<Number> &V, Dep_f &dep_f );
void loop( std::vector<VPoly> &flow, std::vector<VPoly> &error_flow,
		   const Flags &flag1, const Ind_f &ind_f, const int n,
		   const Matrix<Number> &V, Eval_f &eval_f, Dep_f &dep_f,
		   Flow_seg &safe_seg, Flow_seg &error_seg );

}  // namespace detail
}  // namespace hypro

int main( int argc, char **argv ) {
	std::string filename1 = "../../examples/input/bouncing_ball_inhomogen.model";
	std::string filename2 = "../../examples/input/rod_reactor.model";
	std::string filename3 = "../../examples/input/switching_5.model";
	std::string filenamegeneral = "../../examples/input/";
	std::string filename;
	long sl;
	if ( argc == 2 || argc == 3 ) {
		char *p;
		sl = strtol( argv[1], &p, 10 );
	}
	switch ( sl ) {
		case 4:
			filename = filenamegeneral.append( argv[2] );
		case 3:
			filename = filename3;
			break;
		case 2:
			filename = filename2;
			break;
		case 1:
			filename = filename1;
			break;
		default:
			std::cout << "wrong example chosen, choose 1 bounding_ball, 2 rod_reactor, "
						 "3 switching_5, 4 [from examples/input/ choose ] modelname "
						 "for general input\n";
			std::exit( EXIT_FAILURE );
			break;
	}
	// wont work: bouncing_ball.model filtered_oscillator_4.model
	// hypo working: bouncin_ball_inhomogen rod_reactor
	// hypro not working switching_5 (to fix!!!)
	// HyDRA not working: rod_reactor
	// bouncing_ball_inhomogen.model  rod_reactor.model switching_5.model
	// filtered_oscillator_4.model bouncing_ball_inhomogen.model missing: GearBox
	// ARCH17, Comp3
	std::pair<HybridAutomaton<Number>, ReachabilitySettings> ha =
		  parseFlowstarFile<Number>( filename );
	HybridAutomaton<Number> original_ha = ha.first;
	Transformation<Number> trafo = Transformation<Number>( original_ha );
	std::cout << "----------    END OF TRANSFORMATION   ------------\n";
	std::cout << original_ha << std::endl;
	std::cout << "----------    END OF ORIGINAL         ------------\n";
	trafo.output_HybridAutomaton();
	std::cout << "----------    END OF TRAFO OUTPUT     ------------\n";
	std::cout << std::endl;
	return 0;
}

namespace hypro {
namespace detail {
void declare_structures( const int n, In_eq &in_eq1, Invar &invar, Ind_f &ind_f,
						 Dep_f &dep_f, Dep_f &in_traj, Eval_f &eval_f ) {
	in_eq1.A = Matrix<Number>( n, n );
	in_eq1.b = Vector<Number>( n );
	in_eq1.x0 = Vector<Number>( n );
	in_eq1.x0_2 = Vector<Number>( n );
	invar.iAV = Matrix<Number>( n, n );
	invar.ib = Vector<Number>( n );
	ind_f.xinhom = Vector<Number>( n );
	ind_f.D = DiagonalMatrix<Number>( 2 );	// type Number size 2
	dep_f.x_tr = Matrix<Number>::Zero( n, 3 );
	dep_f.x_tr.col( 2 ).array() = 0;
	dep_f.xhom = Matrix<Number>::Zero( 2, 2 );
	in_traj.x_tr = Matrix<Number>::Zero( n, 2 );
	in_traj.xhom = Matrix<Number>::Zero( n, 2 );
	eval_f.deriv = Matrix<Number>( n, 2 );
	eval_f.direct = BoolMatrix( n, 2 );
	eval_f.direct.setConstant( 0 );
}
// mark if in transformed system x0<x0_2 in 3rd column
void mark_x0isMin( Matrix<Number> &x_tr, const int n ) {
	for ( int i = 0; i < n; ++i ) {	 // check if x0_tr >= x0_2_tr
		if ( x_tr( i, 0 ) < x_tr( i, 1 ) ) {
			x_tr( i, 2 ) = 1;  // mark second column to recognize later
		}
	}
}
// check if in transformed system x0<x0_2 and swap if needed
void swap_x0isMax( Matrix<Number> &x_tr, const int n ) {
	// std::cout << "x_tr beforeback: "<< std::endl << x_tr << std::endl;
	Vector<Number> tmp = Vector<Number>( n );
	for ( int i = 0; i < n; ++i ) {
		if ( x_tr( i, 2 ) == 1 ) {
			tmp( i ) = x_tr( i, 0 );
			x_tr( i, 0 ) = x_tr( i, 1 );
			x_tr( i, 1 ) = tmp( i );
		}
	}
	// std::cout << "x_tr afterback: "<< std::endl << x_tr << std::endl;
}
// 1. assign e-Function behavior 2. calculate initial values
// divergence: D>0
// convergence D<0, 1 or 2 points
// remind we assume x0 > x0_2 element wise and set addresses accordingly
// case1:  e^x      --- D>0, xhomconst>0
// case2: -e^(-x)   --- etc
// case3: -e^(x)    --- D>0, xhomconst<0
// case4:  e^(-x)   --- etc
void initialize( Eval_f &eval_f, Flow_seg &safe_seg, Flow_seg &error_seg,
				 std::size_t DIM_PLOT, bool ORIG_SYS_PLOT,
				 const DiagonalMatrix<Number> &D, const int n,
				 const Matrix<Number> &V, Dep_f &dep_f ) {
	Vector<Number> plot_vector = Vector<Number>( n );
	const Matrix<Number> x_tr_error = Matrix<Number>::Zero( n, 2 );
	for ( int i = 0; i < n; ++i ) {
		if ( D.diagonal()( i ) > 0 ) {		   // divergence
			if ( dep_f.xhom( i, 0 ) >= 0 ) {   //
				eval_f.direct( i, 0 ) = true;  // xmax(i) directLine
				if ( dep_f.xhom( i, 1 ) > 0 ) {
					// xmin(i) derivLine
				} else {						   // xmin: -e^x
					eval_f.direct( i, 1 ) = true;  // unusual!! xmin(i) directLine
					std::cout << "set evolves as opposite diverging trajectoris"
							  << std::endl;
				}
			} else {  // xmax: -e^x
				// xmax(i) derivLine
				if ( dep_f.xhom( i, 1 ) > 0 ) {
					std::cout << "ERROR upwards and downwards" << std::endl;
					// ERROR upwards and downwards
				} else {
					eval_f.direct( i, 1 ) = true;  // xmin(i) directLine
				}
			}
		} else {  // e^(-x) and -e^(-x) whereas -x fixed here
			// convergence
			if ( dep_f.xhom( i, 0 ) <= 0 ) {   // xmax:-e^(-x)
				eval_f.direct( i, 0 ) = true;  // xmax(i) directLine
				if ( dep_f.xhom( i, 1 ) < 0 ) {
					// xmin(i) derivLine
				} else {
					eval_f.direct( i, 1 ) = true;  // xmin(i) directLine
					std::cout << "convergence point between initial set" << std::endl;
				}
			} else {  // xmax:e^(-x)
				// xmax(i) derivLine
				if ( dep_f.xhom( i, 1 ) >= 0 ) {
					eval_f.direct( i, 1 ) = true;  // xmin(i) directLine
				} else {
					// xmin(i) derivLine
					std::cout << "2 convergence points, check if intended" << std::endl;
				}
			}
		}
	}
	// std::cout<<"eval_f.direct:"<<std::endl<<eval_f.direct;
	// t=0 step calculation + inserting, e^0 = 1
	eval_f.deriv.col( 0 ) = dep_f.xhom.col( 0 ).array() * D.diagonal().array();
	eval_f.deriv.col( 1 ) = dep_f.xhom.col( 1 ).array() * D.diagonal().array();
	if ( ORIG_SYS_PLOT ) {
		swap_x0isMax( dep_f.x_tr, n );
		plot_addTimeSegment( safe_seg, DIM_PLOT, ORIG_SYS_PLOT, 0, dep_f.x_tr, V, n );
		plot_addTimeSegment( error_seg, DIM_PLOT, ORIG_SYS_PLOT, 0, x_tr_error, V,
							 n );
		swap_x0isMax( dep_f.x_tr, n );
	} else {
		plot_addTimeSegment( safe_seg, DIM_PLOT, ORIG_SYS_PLOT, 0, dep_f.x_tr, V, n );
		plot_addTimeSegment( error_seg, DIM_PLOT, ORIG_SYS_PLOT, 0, x_tr_error, V,
							 n );
	}
}
// 1.linear value + deriv OR direct value
// 2.pushing,writing,deleting
void loop( std::vector<VPoly> &flow, std::vector<VPoly> &error_flow,
		   const Flags &flag1, const Ind_f &ind_f, const int n,
		   const Matrix<Number> &V, Eval_f &eval_f, Dep_f &dep_f,
		   Flow_seg &safe_seg, Flow_seg &error_seg ) {
	Vector<Number> factor = Vector<Number>::Zero( n );
	Matrix<Number> x_tr_error = Matrix<Number>::Zero( n, 3 );
	x_tr_error.col( 2 ) = dep_f.x_tr.col( 2 ).array();
	// WE ASSUME we always want to check 1 timestep
	for ( std::size_t j = 1; j <= ind_f.deltalimit; ++j ) {
		// std::cout << "Time: " << j*delta << std::endl;
		for ( int i = 0; i < n; ++i ) {
			factor( i ) = std::exp( ind_f.D.diagonal()( i ) * j * ind_f.delta );
			if ( eval_f.direct( i, 0 ) ) {	// MAX VALUES
				// e^x OR -e^(-x)
				dep_f.x_tr( i, 0 ) = dep_f.xhom( i, 0 ) * factor( i ) - ind_f.xinhom( i );
				// TODO fancy calculation staying the same
			} else {
				// e^(-x) OR -e^x
				dep_f.x_tr( i, 0 ) = dep_f.x_tr( i, 0 ) + eval_f.deriv( i, 0 ) * ind_f.delta;
				eval_f.deriv( i, 0 ) =
					  dep_f.xhom( i, 0 ) * ind_f.D.diagonal()( i ) * factor( i );
				// if ERROR_CALC MAX: error = deriv - e-function --> function pointer?
				x_tr_error( i, 0 ) =
					  dep_f.x_tr( i, 0 ) - ( dep_f.xhom( i, 0 ) * factor( i ) - ind_f.xinhom( i ) );
			}
			if ( eval_f.direct( i, 1 ) ) {	// MIN VALUES
				dep_f.x_tr( i, 1 ) = dep_f.xhom( i, 1 ) * factor( i ) - ind_f.xinhom( i );
				// TODO fancy calculation staying the same
			} else {
				dep_f.x_tr( i, 1 ) = dep_f.x_tr( i, 1 ) + eval_f.deriv( i, 1 ) * ind_f.delta;
				eval_f.deriv( i, 1 ) =
					  dep_f.xhom( i, 1 ) * ind_f.D.diagonal()( i ) * factor( i );
				x_tr_error( i, 1 ) =
					  ( dep_f.xhom( i, 1 ) * factor( i ) - ind_f.xinhom( i ) ) - dep_f.x_tr( i, 1 );
			}
		}
		// check invariants in transformed system

		if ( flag1.ORIG_SYS_PLOT ) {
			swap_x0isMax( dep_f.x_tr, n );
			plot_addTimeSegment( safe_seg, flag1.DIM_PLOT, flag1.ORIG_SYS_PLOT, j,
								 dep_f.x_tr, V, n );
			swap_x0isMax( dep_f.x_tr, n );
		} else {
			plot_addTimeSegment( safe_seg, flag1.DIM_PLOT, flag1.ORIG_SYS_PLOT, j,
								 dep_f.x_tr, V, n );
		}
		// fill flowpipe and on FLAG add Object to plotter
		addSegment( flow, flag1.HULL_PLOT, safe_seg, plotting::colors[plotting::red],
					plotting::colors[plotting::blue] );
		if ( flag1.ORIG_SYS_PLOT ) {
			swap_x0isMax( x_tr_error, n );
			plot_addTimeSegment( error_seg, flag1.DIM_PLOT, flag1.ORIG_SYS_PLOT, j,
								 x_tr_error, V, n );
			swap_x0isMax( x_tr_error, n );
		} else {
			plot_addTimeSegment( error_seg, flag1.DIM_PLOT, flag1.ORIG_SYS_PLOT, j,
								 x_tr_error, V, n );
		}
		// fill flowpipe and on FLAG add Object to plotter
		addSegment( error_flow, flag1.ERROR_PLOT, error_seg,
					plotting::colors[plotting::red],
					plotting::colors[plotting::blue] );
	}
}
}  // namespace detail
}  // namespace hypro
