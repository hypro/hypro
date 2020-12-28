#include "benchmarkSingularAnalyzer.h"

namespace benchmark {
namespace singularAnalysis {

Results<std::size_t> singularTimeElapse( const Settings& settings ) {
    using Number = ::benchmark::Number;
    using Matrix = hypro::matrix_t<Number>;
    using Vector = hypro::vector_t<Number>;
    using Representation = hypro::HPolytope<Number>;

    Results<std::size_t> ress;

    for ( std::size_t dim = 1; dim <= settings.maxDimension; ++dim ) {
        Timer creationTimer;

        auto ha = randomSingularHaNoJump<Number>( dim );

        // Create empty bad state
        Matrix badStateMat = Matrix::Zero( 2, dim );
        badStateMat( 0, 0 ) = 1;
        badStateMat( 1, 0 ) = -1;
        Vector badStateVec = Vector::Zero( 2 );
        badStateVec( 0 ) = -1;
        badStateVec( 1 ) = -1;

        ha.addGlobalBadState( { badStateMat, badStateVec } );
        auto creationTime = creationTimer.elapsed();
        ress.mCreationTime += creationTime;
        std::cout << "Dimension " << dim << ": Creation took " << creationTime.count() << " sec." << std::endl;

        Timer runTimer;
        auto initialNodes = hypro::makeRoots<Representation, Number>( ha );
        std::cout << "Dimension " << dim << ": Root creation took " << runTimer.elapsed().count() << " sec." << std::endl;

        auto analyzer = hypro::SingularAnalyzer<Representation>(
              ha, hypro::FixedAnalysisParameters{ 1, hypro::tNumber( 10 ), hypro::tNumber( 0.01 ) }, initialNodes );

        analyzer.run();
        auto runningTime = runTimer.elapsed();
        ress.emplace_back( { "singularTimeElapse", runningTime, static_cast<int>( dim ) } );
        std::cout << "Dimension " << dim << ": Running took " << runningTime.count() << " sec." << std::endl;

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

        auto ha = randomSingularHaWithJumps<Number>( dim, settings.iterations );

        auto creationTime = creationTimer.elapsed();
        ress.mCreationTime += creationTime;
        std::cout << "Dimension " << dim << ": Creation took " << creationTime.count() << " sec." << std::endl;

        Timer runTimer;
        auto initialNodes = hypro::makeRoots<Representation, Number>( ha );
        std::cout << "Dimension " << dim << ": Root creation took " << runTimer.elapsed().count() << " sec." << std::endl;

        auto analyzer = hypro::SingularAnalyzer<Representation>(
              ha, hypro::FixedAnalysisParameters{ settings.iterations, hypro::tNumber( settings.iterations + 1 ), hypro::tNumber( 0.01 ) }, initialNodes );

        auto result = analyzer.run();

        auto runningTime = runTimer.elapsed();
        ress.emplace_back( { "singularJumps", runningTime, static_cast<int>( dim ) } );
        std::cout << "Dimension " << dim << ": Running took " << runningTime.count() << " sec." << std::endl;

        ress.mRunningTime += runningTime;
        // last location should be reachable, otherwise there is an error in the analysis method
        if ( result.result() != hypro::REACHABILITY_RESULT::UNKNOWN ) {
            std::cerr << "Error: Last location not reachable\n";
            exit( 1 );
        }
    }


    return ress;
}

} // namespace singularAnalysis
} // namespace benchmark