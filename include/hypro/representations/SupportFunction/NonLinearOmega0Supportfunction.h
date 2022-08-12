/*
 *  This file contains everything related directly to support functions of polyhedra and their evaluation
 *  Author: Norman Hansen
 */

//#define SUPPORTFUNCTION_VERBOSE

//#define BOXOPERATOR_VERBOSE
//#define CALCEPSILON_VERBOSE
//#define CALCVALUES_VERBOSE
//#define TEST_

#include "BoxSupportfunction.h"

// NLopt includes
#include <nlopt.hpp>

namespace hypro {

/*
 * This class defines a support Function object overapproximating Omega0 according to the SpaceEx algorithm with use of
 * nonlinear optimization
 * SupportFunctions can be evaluated in a specified direction l and return a correspondent evaluationResult
 */
template <class Setting>
class NonLinearOmega0Supportfunction : public SupportFunctionContent {
  private:
	// dimensionality of this object
	unsigned int dimensions;

	// externally provided Data
	matrix_t<double>* A;
	SupportFunctionContent* V;
	SupportFunctionContent* X0;

	double delta;

	// general used values for the construction and evaluation of Omega0
	matrix_t<double> absA;
	matrix_t<double> edA;
	matrix_t<double> phi2;
	SupportFunctionContent* epsilonpsi;
	SupportFunctionContent* edX0;
	matrix_t<double> e_p;
	matrix_t<double> e_n;

	// boxoperator values
	std::vector<matrix_t<double>> directionsAlongDimensions;  // contains a vector along each dimension

	/*
	 * Computes a SupportFunctionContent being a symmetric box (centered at the origin) around the specified support function
	 */
	SymmetricCenteredBoxSupportFunction<BoxSupportFunctionSetting>* boxoperator( SupportFunctionContent* sf ) {
		std::string method = "boxoperator:";

		matrix_t<double> e = getZeroVector( dimensions );

		matrix_t<double> l1;
		matrix_t<double> l2;

		auto iterator = directionsAlongDimensions.begin();
		for ( unsigned int i = 0; i < dimensions; i++ ) {
			if ( Setting::SUPPORTFUNCTION_VERBOSE && Setting::BOXOPERATOR_VERBOSE ) {
				TRACE( "hypro.NLOmega0SF", method << " start loop-iteration " << i << '\n' );
			}

			// get 2 successive directions    (they are sorted such that they point both in the opposite direction along
			// the same axis)
			l1 = *iterator;
			++iterator;
			l2 = *iterator;
			++iterator;

			if ( Setting::SUPPORTFUNCTION_VERBOSE && Setting::BOXOPERATOR_VERBOSE ) {
				TRACE( "hypro.NLOmega0SF", method << " l1 = " << l1 << '\n' );
				TRACE( "hypro.NLOmega0SF", method << " l2 = " << l2 << '\n' );
			}

			// get the correspondent evaluation results
			evaluationResult a = sf->evaluate( &l1 );
			evaluationResult b = sf->evaluate( &l2 );

			// set entry in e to the correspondent maximum value
			e( i, 0 ) = std::max( a.supportValue, b.supportValue );

			if ( Setting::SUPPORTFUNCTION_VERBOSE && Setting::BOXOPERATOR_VERBOSE ) {
				TRACE( "hypro.NLOmega0SF", method << " omega(l1) = " << a.supportValue << '\n' );
				TRACE( "hypro.NLOmega0SF", method << " omega(l2) = " << b.supportValue << '\n' );
				TRACE( "hypro.NLOmega0SF", method << "e(" << i << ") = " << e( i, 0 ) << BL );
				TRACE( "hypro.NLOmega0SF", method << " end loop-iteration " << i << '\n' );
			}
		}

		if ( Setting::TEST_ ) {
			SymmetricCenteredBoxSupportFunction<BoxSupportFunctionSetting>* result = new SymmetricCenteredBoxSupportFunction<BoxSupportFunctionSetting>( e, getAD() );
			matrix_t<double> values( directionsAlongDimensions.size(), 1 );
			result->multiEvaluate( &directionsAlongDimensions, &values );
			TRACE( "hypro.NLOmega0SF", "boxoperator(sF): result multiEvaluation: " << BL << values << BL );

			sf->multiEvaluate( &directionsAlongDimensions, &values );
			TRACE( "hypro.NLOmega0SF", "boxoperator(sF): sF multiEvaluation: " << BL << values << BL );
			return result;
		} else {
			return new SymmetricCenteredBoxSupportFunction<BoxSupportFunctionSetting>( e, getAD() );
		}
	}

	/*
	 * computes the matrices edA and phi2
	 */
	matrix_t<double> calcvalues( matrix_t<double>* A, unsigned int i, unsigned int j, unsigned int k, unsigned int l ) {
		std::string method = "calcvalues:";
		if ( Setting::SUPPORTFUNCTION_VERBOSE && Setting::CALCVALUES_VERBOSE ) {
			TRACE( "hypro.NLOmega0SF", method << " A = " << *A << '\n' );
		}

		matrix_t<double> temp = matrix_t<double>::Zero( 3 * dimensions, 3 * dimensions );
		matrix_t<double> Ad = ( *A ) * delta;

		if ( Setting::SUPPORTFUNCTION_VERBOSE && Setting::CALCVALUES_VERBOSE ) {
			TRACE( "hypro.NLOmega0SF", method << " Ad = " << '\n'
											  << Ad << '\n' );
		}

		// copy Ad into temp
		for ( unsigned int i_ = 0; i_ < dimensions; i_++ ) {
			for ( unsigned int j_ = 0; j_ < dimensions; j_++ ) {
				temp( i_, j_ ) = Ad( i_, j_ );
			}
		}

		if ( Setting::SUPPORTFUNCTION_VERBOSE && Setting::CALCVALUES_VERBOSE ) {
			TRACE( "hypro.NLOmega0SF", method << " temp (with Ad) = " << '\n'
											  << temp << '\n' );
		}

		matrix_t<double> Id = matrix_t<double>::Identity( dimensions, dimensions ) * delta;

		if ( Setting::SUPPORTFUNCTION_VERBOSE && Setting::CALCVALUES_VERBOSE ) {
			TRACE( "hypro.NLOmega0SF", method << " Id = " << '\n'
											  << Id << '\n' );
		}

		// copy Id into temp
		for ( unsigned int i_ = 0; i_ < dimensions; i_++ ) {
			for ( unsigned int j_ = 0; j_ < dimensions; j_++ ) {
				temp( i_, dimensions + j_ ) = Id( i_, j_ );
				temp( dimensions + i_, 2 * dimensions + j_ ) = Id( i_, j_ );
			}
		}

		if ( Setting::SUPPORTFUNCTION_VERBOSE && Setting::CALCVALUES_VERBOSE ) {
			TRACE( "hypro.NLOmega0SF", method << " temp = " << temp << '\n' );
		}

		matrix_t<double> exptemp = exponentialmatrix( temp );  // compute exponential of temp

		if ( Setting::SUPPORTFUNCTION_VERBOSE && Setting::CALCVALUES_VERBOSE ) {
			TRACE( "hypro.NLOmega0SF", method << " exptemp = " << exptemp << '\n' );
			TRACE( "hypro.NLOmega0SF", "i: " << i << " j: " << j << " k: " << k << " l: " << l << '\n' );
			TRACE( "hypro.NLOmega0SF", "expcols: " << exptemp.cols() << '\n' );
			TRACE( "hypro.NLOmega0SF", "exprows: " << exptemp.rows() << '\n' );
		}

		// extract the specified part of the exponential matrix exptemp
		return exptemp.block( i, k, j, l );
	}

	/*
	 * Compute further values needed to construct the support function of Omega0
	 */
	void calcepsilon() {
		matrix_t<double> Asquare = ( ( *A ) * ( *A ) );

		std::string method = "calcepsilon:";
		if ( Setting::SUPPORTFUNCTION_VERBOSE && Setting::CALCEPSILON_VERBOSE ) {
			TRACE( "hypro.NLOmega0SF", method << " A = " << *A << '\n' );
			TRACE( "hypro.NLOmega0SF", method << " Asquare = " << Asquare << '\n' );
		}

		// e_p
		MultiplicationSupportfunction* a2x0 = X0->multiply( Asquare );
		SymmetricCenteredBoxSupportFunction<BoxSupportFunctionSetting>* a2x0_box = boxoperator( a2x0 );

		if ( Setting::SUPPORTFUNCTION_VERBOSE && Setting::CALCEPSILON_VERBOSE ) {
			TRACE( "hypro.NLOmega0SF", method << " a2x0_box constructed" << '\n' );
		}

		MultiplicationSupportfunction* temp = a2x0_box->multiply( phi2.transpose() );

		if ( Setting::SUPPORTFUNCTION_VERBOSE && Setting::CALCEPSILON_VERBOSE ) {
			TRACE( "hypro.NLOmega0SF", method << " phi2.transpose() * &a2x0_box constructed" << '\n' );
		}

		SymmetricCenteredBoxSupportFunction<BoxSupportFunctionSetting>* result = boxoperator( temp );
		e_p = result->getE();

		if ( Setting::SUPPORTFUNCTION_VERBOSE && Setting::CALCEPSILON_VERBOSE ) {
			TRACE( "hypro.NLOmega0SF", method << " e_p = " << e_p << '\n' );
		}

		// cleanup heap
		delete a2x0;
		delete a2x0_box;
		delete temp;
		delete result;

		// e_n
		MultiplicationSupportfunction* a2ex0 = X0->multiply( edA * Asquare );
		SymmetricCenteredBoxSupportFunction<BoxSupportFunctionSetting>* a2ex0_box = boxoperator( a2ex0 );
		temp = a2ex0_box->multiply( phi2.transpose() );
		result = boxoperator( temp );
		e_n = result->getE();

		if ( Setting::SUPPORTFUNCTION_VERBOSE && Setting::CALCEPSILON_VERBOSE ) {
			TRACE( "hypro.NLOmega0SF", method << " e_n = " << e_n << '\n' );
		}

		// cleanup heap
		delete a2ex0;
		delete a2ex0_box;
		delete temp;
		delete result;

		// epsilonpsi
		MultiplicationSupportfunction* au = V->multiply( *A );

		if ( Setting::SUPPORTFUNCTION_VERBOSE && Setting::CALCEPSILON_VERBOSE ) {
			TRACE( "hypro.NLOmega0SF", method << " au " << '\n' );
		}

		SymmetricCenteredBoxSupportFunction<BoxSupportFunctionSetting>* au_box = boxoperator( au );

		if ( Setting::SUPPORTFUNCTION_VERBOSE && Setting::CALCEPSILON_VERBOSE ) {
			TRACE( "hypro.NLOmega0SF", method << " au_box " << '\n' );
		}

		delete au;
		temp = au_box->multiply( phi2.transpose() );

		if ( Setting::SUPPORTFUNCTION_VERBOSE && Setting::CALCEPSILON_VERBOSE ) {
			TRACE( "hypro.NLOmega0SF", method << " temp " << '\n' );
		}

		epsilonpsi = boxoperator( temp );

		if ( Setting::SUPPORTFUNCTION_VERBOSE && Setting::CALCEPSILON_VERBOSE ) {
			TRACE( "hypro.NLOmega0SF", method << " epsilonpsi " << '\n' );
		}

		delete temp;
		delete au_box;
		// epsilonpsi = result.copyToHeap();
	}

	// fields to store temporary evaluation results (yield in improved performance)
	evaluationResult x0res;
	evaluationResult edX0res;
	evaluationResult Vres;
	evaluationResult epsilonpsires;
	matrix_t<double> absl;

	// this is the function that will be optimized bei NLOpt
	// calcomega0delta.m
	static double myfunc( unsigned n, const double* x, double* grad,
						  void* my_func_data )	// abs(l) provided using my_func_data
	{
		// TRACE("hypro.NLOmega0SF","x:" << x[0] << '\n');

		// matrix_t<double>* l_pt = (matrix_t<double>*)my_func_data;
		NonLinearOmega0Supportfunction* self = (NonLinearOmega0Supportfunction*)my_func_data;

		// epsilonintersection (function [res] = epsilonintersection(e_p, e_n,x,d,l))
		double epsilonintersection = 0;
		for ( int i = 0; i < ( *self ).absl.rows(); i++ ) {
			epsilonintersection =
				  epsilonintersection + MIN( x[0] * ( ( *self ).e_p( i, 0 ) ),
											 ( 1 - x[0] ) * ( ( *self ).e_n( i, 0 ) ) * ( ( *self ).absl( i, 0 ) ) );
		}
		// TRACE("hypro.NLOmega0SF","epsilonintersection:" << epsilonintersection << '\n');

		// result(edA,delta,u,x0,epsilonpsi,e_p, e_n,start,options,l)
		double t1 = ( ( 1 - x[0] ) * ( ( *self ).x0res.supportValue ) );
		double t2 = ( x[0] * ( ( *self ).edX0res.supportValue ) );
		double t3 = ( x[0] * ( ( *self ).delta ) * ( ( *self ).Vres.supportValue ) );
		double t4 = ( ( x[0] * x[0] ) * ( ( *self ).epsilonpsires.supportValue ) );

		// TRACE("hypro.NLOmega0SF","t1: " << t1 << BL);
		// TRACE("hypro.NLOmega0SF","t2: " << t2 << BL);
		// TRACE("hypro.NLOmega0SF","(*self).edX0res.supportValue): " << (*self).edX0res.supportValue);
		// TRACE("hypro.NLOmega0SF","t3: " << t3 << BL);
		// TRACE("hypro.NLOmega0SF","t4: " << t4 << BL);

		double res = -( t1 + t2 + t3 + t4 + epsilonintersection );	// +epsilonintersection(e_p,e_n,x,size(start,1),l)
		// TRACE("hypro.NLOmega0SF","res:" << res << BL);
		return res;
	}

  protected:
	/**
	 * This method computes the evaluation result for a specified direction l
	 * TODO: optimization object can be declared and initialized outside the evaluate methods to improve performance (see
	 * glpk)
	 */
	evaluationResult specificEvaluation( matrix_t<double> l ) {
		std::string method = "NonLinearOmega0Supportfunction: evaluate: ";
		if ( Setting::SUPPORTFUNCTION_VERBOSE ) {
			TRACE( "hypro.NLOmega0SF", method << " l: " << '\n'
											  << l << '\n' );
		}

		// precompute values needed during optimization (dependent on l)
		// improves evaluation speed of myfunc during optimization
		x0res = X0->evaluate( &l );
		matrix_t<double> edAl = edA.transpose() * l;  // edA * l
		edX0res = X0->evaluate( &edAl );
		Vres = V->evaluate( &l );
		epsilonpsires = epsilonpsi->evaluate( &l );
		absl = l.array().abs().matrix();

		if ( Setting::SUPPORTFUNCTION_VERBOSE ) {
			TRACE( "hypro.NLOmega0SF", "NonLinearOmega0Supportfunction: evaluate: precomputed constants:" << BL );
			TRACE( "hypro.NLOmega0SF", "x0(l): " << x0res.supportValue << BL );
			TRACE( "hypro.NLOmega0SF", "edX0res(l): " << edX0res.supportValue << BL );
			TRACE( "hypro.NLOmega0SF", "Vres(l): " << Vres.supportValue << BL );
			TRACE( "hypro.NLOmega0SF", "epsilonpsires(l): " << epsilonpsires.supportValue << BL );
			TRACE( "hypro.NLOmega0SF", "absl: " << absl << BL );
		}

		// optimization parameter and start value
		std::vector<double> x( 1 );
		x[0] = 0;

		std::vector<double> lb( 1 );
		lb[0] = 0;

		std::vector<double> ub( 1 );
		ub[0] = 1;

		// create optimization object
		nlopt::opt opt( nlopt::LN_COBYLA, 1 );
		opt.set_lower_bounds( lb );	 // lower bounds
		opt.set_upper_bounds( ub );	 // upper bounds
		opt.set_min_objective( myfunc, this );

		opt.set_xtol_rel( 1e-8 );

		double minf;									 // minimization result
		nlopt::result result = opt.optimize( x, minf );	 // optimization call

		// catch error case
		if ( result <= 0 ) {
			if ( Setting::SUPPORTFUNCTION_VERBOSE ) {
				TRACE( "hypro.NLOmega0SF", method << " NLOPT Failure" );
			}

			// avoid program crash
			minf = 0;
			x[0] = 0;
		}

		// create evaluationResult
		evaluationResult eR;
		eR.errorCode = 0;  // unknown (arbitrary chosen)
		eR.supportValue = -minf;
		matrix_t<double> oV( 1, 1 );
		oV( 0, 0 ) = x[0];
		eR.optimumValue = oV;

		if ( Setting::SUPPORTFUNCTION_VERBOSE ) {
			TRACE( "hypro.NLOmega0SF", method << " eR.supportValue: " << '\n'
											  << eR.supportValue << '\n' );
			TRACE( "hypro.NLOmega0SF", method << " eR.optimumValue: " << '\n'
											  << eR.optimumValue << '\n' );
		}

		return eR;
	}

  public:
	// getter for epsilonpsi
	SupportFunctionContent* getEpsilonpsi() { return epsilonpsi; }

	/*
	 * Creates a new SupportFunctionContent describing Omega0
	 *
	 * A: matrix describing the flow
	 * V: support function describing the input (B' * U)
	 * X0: support function describing the initial set
	 * delta: sampling time
	 *
	 */
	NonLinearOmega0Supportfunction( matrix_t<double>* A, SupportFunctionContent* V, SupportFunctionContent* X0, double delta,
									artificialDirections* aD )
		: SupportFunctionContent( SupportFunctionType::NonLinear_Type, aD ) {
		std::string method = "NonLinearOmega0Supportfunction:";

		// initialize values used by boxoperators
		dimensions = ( *A ).rows();
		directionsAlongDimensions = vectorgenerator(
			  dimensions );	 // 2 last directions are equivalent to artificial - caugth by SupportFunctionContent.evaluate
							 // TODO: could be more efficient if the directions in the additional dimension are exactly the same (in memory with same
							 // pointer) as in aD
							 // in this case SupportFunctionContent.evaluate needs no second nested if branch

		if ( Setting::SUPPORTFUNCTION_VERBOSE ) {
			TRACE( "hypro.NLOmega0SF", method << " generated Vectors along dimensions:" << BL );
			printDirectionList( directionsAlongDimensions );
		}

		this->A = A;
		this->V = V;
		this->X0 = X0;
		this->delta = delta;

		if ( Setting::SUPPORTFUNCTION_VERBOSE ) {
			TRACE( "hypro.NLOmega0SF", method << " initialized class attributes with constructor values" << '\n' );
		}

		// absolute value of A
		absA = ( *A ).array().abs().matrix();

		if ( Setting::SUPPORTFUNCTION_VERBOSE ) {
			TRACE( "hypro.NLOmega0SF", method << " computed Abs(A):" << '\n' );
			TRACE( "hypro.NLOmega0SF", absA << '\n' );
		}

		// compute edA and phi2
		unsigned int zero = 0;
		edA = calcvalues( A, zero, dimensions, zero, dimensions );

		if ( Setting::SUPPORTFUNCTION_VERBOSE ) {
			TRACE( "hypro.NLOmega0SF", method << " computed edA: " << '\n'
											  << edA << '\n' );
		}

		phi2 = calcvalues( &absA, zero, dimensions, 2 * dimensions, dimensions );
		if ( Setting::SUPPORTFUNCTION_VERBOSE ) {
			TRACE( "hypro.NLOmega0SF", method << " computed phi2: " << '\n'
											  << phi2 << '\n' );
		}

		// compute epsilonpsi, e_p and e_n
		calcepsilon();

		MultiplicationSupportfunction* temp = X0->multiply( edA );
		edX0 = temp;
	}

	// destructor
	~NonLinearOmega0Supportfunction() {
		if ( Setting::SUPPORTFUNCTION_VERBOSE ) {
			TRACE( "hypro.NLOmega0SF", " NonLinearOmega0Supportfunction: destructor " << '\n' );
		}

		delete epsilonpsi;	// has been explicitely copied to heap and can be deleted at this point
		delete edX0;

		if ( Setting::SUPPORTFUNCTION_VERBOSE ) {
			TRACE( "hypro.NLOmega0SF", " NonLinearOmega0Supportfunction: destructor - complete" << '\n' );
		}
	}
};
}  // namespace hypro
