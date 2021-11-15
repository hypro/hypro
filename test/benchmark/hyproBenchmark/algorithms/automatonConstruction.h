#pragma once

#include "../types.h"
#include <hypro/flags.h>
#include <hypro/datastructures/HybridAutomaton/HybridAutomaton.h>

#include <random>

namespace benchmark {

template <typename Number>
hypro::matrix_t<Number> randomSingularFlow( const std::size_t& dim ) {
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

    hypro::vector_t<Number> constants = hypro::vector_t<Number>::Zero( 2*dim );
    for( std::size_t varIndex = 0; varIndex < dim; ++varIndex ) {
        constants( varIndex ) = Number( distUpper( generator ) );
        constants( dim + varIndex ) = Number( -1 * distLower( generator ) );
    }
    return constants;

}

template <typename Number>
hypro::HybridAutomaton<Number> randomSingularHaNoJump( const std::size_t& dim ) {
    using Matrix = hypro::matrix_t<Number>;
    using Vector = hypro::vector_t<Number>;

    hypro::HybridAutomaton<Number> ha;

    // Create location
    hypro::Location<Number> loc{};
    auto uniqueLoc{ std::make_unique<hypro::Location<Number>>( loc ) };
    uniqueLoc->setName( "l0" );

    // Set flow
    uniqueLoc->setFlow( randomSingularFlow<Number>( dim ) );
    uniqueLoc->setInvariant( { Matrix::Zero( 1, dim ), Vector::Zero( 1 ) } );

    // Initialise variables as polytope centered around 0
    Vector initialConstants = randomInitConstants<Number>( dim, -10, 10 );
    Matrix initialConstraints = Matrix::Zero( 2*dim, dim );
    for ( std::size_t varIndex = 0; varIndex < dim; ++varIndex ) {
        initialConstraints( varIndex, varIndex ) = 1;
        initialConstraints( dim + varIndex, varIndex ) = -1;
    }

    ha.addInitialState( uniqueLoc.get(), hypro::Condition<Number>( initialConstraints, initialConstants ) );
    ha.addLocation( std::move( uniqueLoc ) );

    return ha;
}

template <typename Number>
hypro::HybridAutomaton<Number> randomSingularHaWithJumps( const std::size_t& dim, const std::size_t& jumps ) {
    using Matrix = hypro::matrix_t<Number>;
    using Vector = hypro::vector_t<Number>;

    hypro::HybridAutomaton<Number> ha;

    // Create locations (need jumps+1 many)
    std::vector<std::unique_ptr<hypro::Location<Number>>> locations;
    for( std::size_t locCount = 0; locCount <= jumps; ++locCount ) {
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
    for( std::size_t locCount = 0; locCount < jumps; ++locCount ) {
        // create random flow
        auto flowMatrix = randomSingularFlow<Number>( dim );
        Vector flowVector = flowMatrix.col( dim ).head( dim );
        locations[ locCount ]->setFlow( flowMatrix );

        // Create guard that contains origin
        Matrix guardMatrix = Matrix::Zero( dim, dim );
        Vector guardVector = Vector::Zero( dim );
        for( std::size_t row = 0; row < dim; ++row ) {
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
        for( std::size_t varIndex = 0; varIndex < dim; ++varIndex ) {
            resetIntervals.push_back( { -1 * resetConstants( dim + varIndex ), resetConstants( varIndex ) } );
        }
        auto transition{ std::make_unique<hypro::Transition<Number>>(
            locations[ locCount ].get(), locations[ locCount + 1 ].get(), guard, hypro::Reset<Number>( resetIntervals ) ) };
        locations[ locCount ]->addTransition( std::move ( transition ) );

        // empty invariant (for now)
    }

    // zero flow for last location
    Matrix zeroFlow = Matrix::Zero( dim, dim );
    locations[ jumps ]->setFlow( zeroFlow );

    for( auto& location : locations ) {
        ha.addLocation( std::move( location ) );
    }


    // Initialise variables as polytope centered around 0
    Vector initialConstants = randomInitConstants<Number>( dim, -10, 10 );
    Matrix initialConstraints = Matrix::Zero( 2*dim, dim );
    for ( std::size_t varIndex = 0; varIndex < dim; ++varIndex ) {
        initialConstraints( varIndex, varIndex ) = 1;
        initialConstraints( dim + varIndex, varIndex ) = -1;
    }

    ha.addInitialState( ha.getLocation( "l0" ), { initialConstraints, initialConstants } );
    // Set last location as bad state, to confirm that it is reachable (all guards satisfied)
    ha.addLocalBadState( ha.getLocation( "l" + std::to_string( jumps ) ), { Matrix::Zero( 1, dim ), Vector::Zero( 1 ) } );

    return ha;
}
} // namespace benchmark