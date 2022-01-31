/*
 * Copyright (c) 2021.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 *   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "benchmarkSingularAnalyzer.h"

namespace benchmark {
namespace singularAnalysis {

template <typename Number>
hypro::matrix_t<Number> randomFlow( const std::size_t& dim ) {
	using Matrix = hypro::matrix_t<Number>;

	static std::mt19937 generator;
	std::uniform_real_distribution<double> dist = std::uniform_real_distribution<double>( -100, 100 );

	Matrix flow = Matrix::Zero( dim + 1, dim + 1 );
	for ( std::size_t row = 0; row < dim; ++row ) {
		flow( row, dim ) = Number( dist( generator ) );
	}
	return flow;
}

template <typename Number>
hypro::vector_t<Number> randomInitConstants( const std::size_t& dim, int lower, int upper ) {
	static std::mt19937 generator;
	std::uniform_int_distribution<int> distLower = std::uniform_int_distribution<int>( lower, -1 );
	std::uniform_int_distribution<int> distUpper = std::uniform_int_distribution<int>( 1, upper );

	hypro::vector_t<Number> constants = hypro::vector_t<Number>::Zero( 2 * dim );
	for ( std::size_t varIndex = 0; varIndex < dim; ++varIndex ) {
		constants( varIndex ) = Number( distUpper( generator ) );
		constants( dim + varIndex ) = Number( -1 * distLower( generator ) );
	}
	return constants;
}

template <typename Number>
hypro::HybridAutomaton<Number> randomHaNoJump( const std::size_t& dim ) {
	using Matrix = hypro::matrix_t<Number>;
	using Vector = hypro::vector_t<Number>;

	hypro::HybridAutomaton<Number> ha;

	// Create location
	hypro::Location<Number> loc{};
	auto uniqueLoc{ std::make_unique<hypro::Location<Number>>( loc ) };
	uniqueLoc->setName( "l0" );

	// Set flow
	uniqueLoc->setFlow( randomFlow<Number>( dim ) );
	uniqueLoc->setInvariant( { Matrix::Zero( 1, dim ), Vector::Zero( 1 ) } );

	// Initialise variables as polytope centered around 0
	Vector initialConstants = randomInitConstants<Number>( dim, -10, 10 );
	Matrix initialConstraints = Matrix::Zero( 2 * dim, dim );
	for ( std::size_t varIndex = 0; varIndex < dim; ++varIndex ) {
		initialConstraints( varIndex, varIndex ) = 1;
		initialConstraints( dim + varIndex, varIndex ) = -1;
	}

	ha.addInitialState( uniqueLoc.get(), hypro::Condition<Number>( initialConstraints, initialConstants ) );
	ha.addLocation( std::move( uniqueLoc ) );

	return ha;
}

template <typename Number>
hypro::HybridAutomaton<Number> randomHaWithJumps( const std::size_t& dim, const std::size_t& jumps ) {
	using Matrix = hypro::matrix_t<Number>;
	using Vector = hypro::vector_t<Number>;

	hypro::HybridAutomaton<Number> ha;

	// Create locations (need jumps+1 many)
	std::vector<std::unique_ptr<hypro::Location<Number>>> locations;
	for ( std::size_t locCount = 0; locCount <= jumps; ++locCount ) {
		hypro::Location<Number> loc{};
		auto uniqueLoc{ std::make_unique<hypro::Location<Number>>( loc ) };
		uniqueLoc->setName( "l" + std::to_string( locCount ) );

		locations.push_back( std::move( uniqueLoc ) );
	}

	/*
	 * Create jumps such that the origin always satisfies the guards (no empty guard intersections)
	 * Additionaly, every jump should be enabled after 1 time unit, so that every location
	 * can be reached in time.
	 */
	for ( std::size_t locCount = 0; locCount < jumps; ++locCount ) {
		// create random flow
		auto flowMatrix = randomFlow<Number>( dim );
		Vector flowVector = flowMatrix.col( dim ).head( dim );
		locations[locCount]->setFlow( flowMatrix );

		// Create guard that contains origin
		Matrix guardMatrix = Matrix::Zero( dim, dim );
		Vector guardVector = Vector::Zero( dim );
		for ( std::size_t row = 0; row < dim; ++row ) {
			// Encode inequality sgn(flow_i)*x_i >= sgn(flow_i)*flow_i
			// scale rhs with factor of 0.9 to not lose too many states on every guard
			int sgn = flowVector( row ) < 0 ? -1 : 1;
			guardMatrix( row, row ) = Number( -sgn );
			guardVector( row ) = Number( -sgn * flowVector( row ) * Number( 0.9 ) );
		}
		hypro::Condition<Number> guard( guardMatrix, guardVector );

		// Reset to box centered at the origin
		auto resetConstants = randomInitConstants<Number>( dim, -10, 10 );
		// Reset uses intervals
		std::vector<carl::Interval<Number>> resetIntervals;
		for ( std::size_t varIndex = 0; varIndex < dim; ++varIndex ) {
			resetIntervals.push_back( { -1 * resetConstants( dim + varIndex ), resetConstants( varIndex ) } );
		}
		auto transition{ std::make_unique<hypro::Transition<Number>>( locations[locCount].get(),
																	  locations[locCount + 1].get(), guard,
																	  hypro::Reset<Number>( resetIntervals ) ) };
		locations[locCount]->addTransition( std::move( transition ) );

		// empty invariant (for now)
	}

	for ( auto& location : locations ) {
		ha.addLocation( std::move( location ) );
	}

	// Initialise variables as polytope centered around 0
	Vector initialConstants = randomInitConstants<Number>( dim, -10, 10 );
	Matrix initialConstraints = Matrix::Zero( 2 * dim, dim );
	for ( std::size_t varIndex = 0; varIndex < dim; ++varIndex ) {
		initialConstraints( varIndex, varIndex ) = 1;
		initialConstraints( dim + varIndex, varIndex ) = -1;
	}

	ha.addInitialState( ha.getLocation( "l0" ), { initialConstraints, initialConstants } );
	// Set last location as bad state, to confirm that it is reachable (all guards satisfied)
	ha.addLocalBadStates( ha.getLocation( "l" + std::to_string( jumps ) ),
						  { Matrix::Zero( 1, dim ), Vector::Zero( 1 ) } );

	return ha;
}

Results<std::size_t> singularTimeElapse( const Settings& settings ) {
	using Number = ::benchmark::Number;
	using Matrix = hypro::matrix_t<Number>;
	using Vector = hypro::vector_t<Number>;
	using Representation = hypro::HPolytope<Number>;

	Results<std::size_t> ress;

	for ( std::size_t dim = 1; dim <= settings.maxDimension; ++dim ) {
		Timer creationTimer;

		auto ha = randomHaNoJump<Number>( dim );

		// Create empty bad state
		Matrix badStateMat = Matrix::Zero( 2, dim );
		badStateMat( 0, 0 ) = 1;
		badStateMat( 1, 0 ) = -1;
		Vector badStateVec = Vector::Zero( 2 );
		badStateVec( 0 ) = -1;
		badStateVec( 1 ) = -1;

		ha.addGlobalBadStates( { badStateMat, badStateVec } );
		auto initialNodes = hypro::makeRoots<Representation, Number>( ha );
		auto analyzer = hypro::SingularAnalyzer<Representation>(
			  ha, hypro::FixedAnalysisParameters{ 1, hypro::tNumber( 10 ), hypro::tNumber( 0.01 ) }, initialNodes );

		auto creationTime = creationTimer.elapsed();
		std::cout << "Dimension " << dim << ": Creation took " << creationTime.count() << " sec." << std::endl;
		ress.mCreationTime += creationTime;

		Timer runTimer;
		analyzer.run();
		auto runningTime = runTimer.elapsed();
		ress.emplace_back( { "singularTimeElapse", runningTime, static_cast<int>( dim ) } );
		std::cout << "Dimension " << dim << ":  Running took " << runningTime.count() << " sec." << std::endl;

		ress.mRunningTime += runningTime;
	}

	return ress;
}

Results<std::size_t> singularJumps( const Settings& settings ) {
	using Number = ::benchmark::Number;
	using Representation = hypro::HPolytope<Number>;

	Results<std::size_t> ress;

	for ( std::size_t dim = 1; dim <= settings.maxDimension; ++dim ) {
		Timer creationTimer;

		auto ha = randomHaWithJumps<Number>( dim, settings.iterations );

		auto initialNodes = hypro::makeRoots<Representation, Number>( ha );
		auto analyzer = hypro::SingularAnalyzer<Representation>(
			  ha,
			  hypro::FixedAnalysisParameters{ settings.iterations, hypro::tNumber( settings.iterations + 1 ),
											  hypro::tNumber( 0.01 ) },
			  initialNodes );

		auto creationTime = creationTimer.elapsed();
		std::cout << "Dimension " << dim << ": Creation took " << creationTime.count() << " sec." << std::endl;
		ress.mCreationTime += creationTime;

		Timer runTimer;
		auto result = analyzer.run();
		std::cout << "Last location is "
				  << ( result.result() == hypro::REACHABILITY_RESULT::UNKNOWN ? "reachable" : "not reachable" )
				  << std::endl;
		auto runningTime = runTimer.elapsed();
		ress.emplace_back( { "singularJumps", runningTime, static_cast<int>( dim ) } );
		std::cout << "Dimension " << dim << ":  Running took " << runningTime.count() << " sec." << std::endl;

		ress.mRunningTime += runningTime;
	}

	return ress;
}

}  // namespace singularAnalysis
}  // namespace benchmark