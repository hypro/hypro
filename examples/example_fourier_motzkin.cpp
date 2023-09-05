#include "hypro/neuralnets/parser/NNet.h"
#include "hypro/neuralnets/reachability/ReachNN.h"
#include "hypro/representations/GeometricObjectBase.h"
// #include "hypro/representations/Starset/Starset.h"
#include "hypro/util/plotting/Plotter.h"

// use floating point arithmetic.
typedef double Number;	// -3090.30109487     <=>      -3090.3   (mpq_class vs double)

int main( int argc, char* argv[] ) {
	// define plotter settings
	hypro::plotting::gnuplotSettings settings;
	settings.filename = "Fourier-Motzkin";
	settings.fill = true;
	settings.pointSize = 5.0;
	settings.linewidth = 3.0;
	settings.keepAspectRatio = true;

	// get plotter reference.
	hypro::Plotter<Number>& plotter = hypro::Plotter<Number>::getInstance();
	plotter.updateSettings( settings );

	// define input file name
	const char* filename = "../examples/nnet/fc_identity.nnet";
	std::cout << "Filename is: " << filename << std::endl;

	// read and build neural network
	hypro::NNet<Number> rotate_nn = hypro::NNet<Number>( filename );
	std::cout << rotate_nn << std::endl;

	// // a triangle:  |>
	// hypro::vector_t<Number> center = hypro::vector_t<Number>( 2 );
	// hypro::matrix_t<Number> basis = hypro::matrix_t<Number>( 2, 2 );
	// hypro::matrix_t<Number> constr = hypro::matrix_t<Number>( 3, 2 );
	// hypro::vector_t<Number> limits = hypro::vector_t<Number>( 3 );
	// center << 0, 0;
	// basis << 1, 0, 0, 1;
	// constr << -1, 0, 1, 1, 1, -1;
	// limits << 1, 1, 1;

	//a simple rectangle [_]
	hypro::vector_t<Number> center = hypro::vector_t<Number>( 2 );
	hypro::matrix_t<Number> basis = hypro::matrix_t<Number>( 2, 2 );
	hypro::matrix_t<Number> constr = hypro::matrix_t<Number>( 4, 2 );
	hypro::vector_t<Number> limits = hypro::vector_t<Number>( 4 );
	center << 0, 0;
	basis << 1, 0, 0, 1;
	constr << 1, 0, 0, 1, -1, 0, 0, -1;
	limits << 2, 1, 1, 1;

    // create and plot the star-set
	hypro::Starset<Number> input_star = hypro::Starset<Number>( center, constr, limits, basis );
	plotter.addObject( input_star.vertices(), hypro::plotting::colors[hypro::plotting::red] );
	plotter.plot2d();
	plotter.clear();

    // use the overapproximate method to calculate the result starset
	hypro::reachability::NN_REACH_METHOD method = hypro::reachability::NN_REACH_METHOD::OVERAPPRX;
	hypro::reachability::ReachNN<Number> reach_nn = hypro::reachability::ReachNN<Number>( rotate_nn );
	std::vector<hypro::Starset<Number>> output_set = reach_nn.forwardAnalysis( input_star, method, true );

    // print and plot each resulting star on the same diagram with different colors
	int N = output_set.size();
	for ( int i = 0; i < N; i++ ) {
		std::cout << output_set[i] << std::endl;
		std::vector<hypro::Point<Number>> vertices = output_set[i].vertices();
		if ( method == hypro::reachability::NN_REACH_METHOD::EXACT && i % 4 == 3 ) {
			plotter.addPoint( vertices[0] );
		} else {
			plotter.addObject( vertices, hypro::plotting::colors[( 2 * i ) % 9] );	// i % 10 is the color of the enum from 9 to 0 (Plotter.h)
		}
	}
	plotter.plot2d();

	return 0;
}