#include "../defines.h"
#include "gtest/gtest.h"
#include <algorithms/reachability/workers/SingularWorker.h>
#include <datastructures/HybridAutomaton/HybridAutomaton.h>
#include <datastructures/reachability/Settings.h>
#include <representations/GeometricObjectBase.h>

template <typename Number>
hypro::HybridAutomaton<Number> createBouncingBall() {
	using Matrix = hypro::matrix_t<Number>;
	using Vector = hypro::vector_t<Number>;

	hypro::HybridAutomaton<Number> res;

	hypro::Location<Number> loc;
	loc.setName( "l0" );

	Matrix invariantConstraints = Matrix::Zero( 1, 3 );
	invariantConstraints( 1, 1 ) = Number( -1 );
	Vector invariantConstants = Vector::Zero( 1 );
	loc.setInvariant( { invariantConstraints, invariantConstants } );

	res.addLocation( std::make_unique<hypro::Location<Number>>( loc ) );

	return hypro::HybridAutomaton<Number>{};
}

TEST( SingularRechabilityTest, WorkerConstruction ) {
	using Number = mpq_class;
	using VPoly = hypro::VPolytope<Number>;
	using Vector = hypro::vector_t<Number>;
	using Representation = hypro::HPolytope<Number>;

	auto automaton = createBouncingBall<Number>();

	auto worker =
		  hypro::SingularWorker<Representation>( automaton, hypro::Settings{ {}, { 1, hypro::tNumber( 10 ) }, {} } );
}