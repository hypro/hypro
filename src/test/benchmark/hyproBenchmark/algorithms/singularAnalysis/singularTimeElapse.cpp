#include "benchmarkSingularAnalyzer.h"

namespace benchmark {
namespace singularAnalysis {


template <typename Number>
hypro::matrix_t<Number> randomFlow( const std::size_t& dim ) {
    using Matrix = hypro::matrix_t<Number>;

    std::mt19937 generator;
    std::uniform_real_distribution<double> dist = std::uniform_real_distribution<double>( -100, 100 );

    Matrix flow = Matrix::Zero( dim + 1, dim + 1 );
    for ( std::size_t row = 0; row <= dim; ++row ) {
        flow( row, dim ) = Number( dist( generator ) );
    }
    return flow;
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

    // Initialise all variables to 0
    Matrix initialConstraints = Matrix::Zero( 2*dim, dim );
    Vector initialConstants = Vector::Zero( 2*dim );
    for ( std::size_t varIndex = 0; varIndex < dim; ++varIndex ) {
        initialConstraints( varIndex, varIndex ) = 1;
        initialConstraints( 2*varIndex + 1, varIndex ) = -1;
    }

    ha.addInitialState( uniqueLoc.get(), hypro::Condition<Number>( initialConstraints, initialConstants ) );
    ha.addLocation( std::move( uniqueLoc ) );

    return ha;
}

Results<std::size_t> singularTimeElapse( const Settings& settings ) {
    using Number = mpq_class;
    using Matrix = hypro::matrix_t<Number>;
    using Vector = hypro::vector_t<Number>;
    using Representation = hypro::VPolytope<Number>;

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
        badStateVec( 1 ) = 1;

        ha.addGlobalBadState( { badStateMat, badStateVec } );
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

} // namespace singularAnalysis
} // namespace benchmark