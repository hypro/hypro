#include <flags.h>
#ifdef HYPRO_GSL_INTEGRATION
#include <gsl/gsl_math.h>
#include <gsl/gsl_monte.h>
#include <gsl/gsl_monte_miser.h>
#include <gsl/gsl_monte_plain.h>
#include <gsl/gsl_monte_vegas.h>
#include <stdlib.h>

// Documentation of the gsl-routines at https://www.gnu.org/software/gsl/doc/html/montecarlo.html
// Example taken from there and adapted (added comments/instructions)

/* Computation of the integral,

      I = int (dx dy dz)/(2pi)^3  1/(1-cos(x)cos(y)cos(z))

   over (-pi,-pi,-pi) to (+pi, +pi, +pi).  The exact answer
   is Gamma(1/4)^4/(4 pi^3).  This example is taken from
   C.Itzykson, J.M.Drouffe, "Statistical Field Theory -
   Volume 1", Section 1.1, p21, which cites the original
   paper M.L.Glasser, I.J.Zucker, Proc.Natl.Acad.Sci.USA 74
   1800 (1977) */

/* For simplicity we compute the integral over the region
   (0,0,0) -> (pi,pi,pi) and multiply by 8 */

double exact = 1.3932039296856768591842462603255;

// Stefan: This is the actual function for integration. If you want to integrate over a set, first check, whether the point passed in k of dimension dim is contained in the set. To pass the set use the void pointer "params".
// If the point is not contained, return zero, otherwise insert the point into the function (which you also need to pass via params in case you do not want to hardcode your distribution in the function g). I suggest using a struct of sets and the distribution to pass within params.
//
// get the point:
//  Eigen::Map<Eigen::Matrix<double, Eigen::Dynamic, 1>> map = Eigen::Map<Eigen::Matrix<double, Eigen::Dynamic, 1>>(k, dim);
//  vector_t<double> vec{map};
//  auto point = hypro::Point<double>(vec);
//
// get the set from params:
// setType mySet = *((setType *)params);
//
//

double
g( double* k, size_t dim, void* params ) {
	(void)( dim ); /* avoid unused parameter warnings */
	(void)( params );
	double A = 1.0 / ( M_PI * M_PI * M_PI );
	return A / ( 1.0 - cos( k[0] ) * cos( k[1] ) * cos( k[2] ) );
}

void display_results( char* title, double result, double error ) {
	printf( "%s ==================\n", title );
	printf( "result = % .6f\n", result );
	printf( "sigma  = % .6f\n", error );
	printf( "exact  = % .6f\n", exact );
	printf( "error  = % .6f = %.2g sigma\n", result - exact,
			fabs( result - exact ) / error );
}

int main( void ) {
	double res, err;

	// Stefan: Defines the boundaries of the hyperbox which is the integration domain
	// To get those bounds, convert the set to a box and read lower and upper bounds of the intervals.
	double xl[3] = { 0, 0, 0 };
	double xu[3] = { M_PI, M_PI, M_PI };

	// Stefan: Random number generator - we can just use the same.
	const gsl_rng_type* T;
	gsl_rng* r;

	// Stefan: The function "g" as given above is important and needs to be adapted
	gsl_monte_function G = { &g, 3, 0 };

	// Stefan: The number of calls - the more calls the higher the precision
	size_t calls = 500000;

	// Stefan: Some initialization of the workspace
	gsl_rng_env_setup();

	T = gsl_rng_default;
	r = gsl_rng_alloc( T );

	// Stefan: Here three different algorithms are used - I think we can stick to the Monte-Carlo Vegas method.
	{
		gsl_monte_plain_state* s = gsl_monte_plain_alloc( 3 );
		gsl_monte_plain_integrate( &G, xl, xu, 3, calls, r, s,
								   &res, &err );
		gsl_monte_plain_free( s );

		display_results( "plain", res, err );
	}

	{
		gsl_monte_miser_state* s = gsl_monte_miser_alloc( 3 );
		gsl_monte_miser_integrate( &G, xl, xu, 3, calls, r, s,
								   &res, &err );
		gsl_monte_miser_free( s );

		display_results( "miser", res, err );
	}

	{
		gsl_monte_vegas_state* s = gsl_monte_vegas_alloc( 3 );

		gsl_monte_vegas_integrate( &G, xl, xu, 3, 10000, r, s,
								   &res, &err );
		display_results( "vegas warm-up", res, err );

		printf( "converging...\n" );

		do {
			gsl_monte_vegas_integrate( &G, xl, xu, 3, calls / 5, r, s,
									   &res, &err );
			printf(
				  "result = % .6f sigma = % .6f "
				  "chisq/dof = %.1f\n",
				  res, err, gsl_monte_vegas_chisq( s ) );
		} while ( fabs( gsl_monte_vegas_chisq( s ) - 1.0 ) > 0.5 );

		display_results( "vegas final", res, err );

		gsl_monte_vegas_free( s );
	}

	gsl_rng_free( r );

	return 0;
}
#else

int main() {
	return 0;
}

#endif