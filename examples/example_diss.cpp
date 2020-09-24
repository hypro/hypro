#include <hypro/representations/GeometricObjectBase.h>
#include <hypro/util/plotting/Plotter.h>

int main() {
	using Box = hypro::Box<double>;
	using Point = hypro::Point<double>;
	using Matrix = hypro::matrix_t<double>;
	using Vector = hypro::vector_t<double>;

	hypro::Plotter<double>& plt = hypro::Plotter<double>::getInstance();

	Box b = Box( std::make_pair( Point( { 1, 1 } ), Point( { 2, 2 } ) ) );
	plt.addObject( b.vertices() );

	Matrix A = Matrix( 2, 2 );
	A << 1, 1, 0, 1;

	for ( int i = 0; i < 10; ++i ) {
		b = b.linearTransformation( A );
		plt.addObject( b.vertices() );
	}

	plt.plot2d();

	return 0;
}
