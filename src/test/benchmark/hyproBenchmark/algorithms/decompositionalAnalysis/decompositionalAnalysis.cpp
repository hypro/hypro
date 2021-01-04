#include "benchmarkDecompositionalAnalyzer.h"

namespace benchmark {
namespace decompositionalAnalysis {

Results<std::size_t> decompositionalSingularTimeElapse( const Settings& settings ) {
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
        auto [decomposedHa, decomposition] = hypro::decomposeAutomaton( ha );
        for ( std::size_t subspace = 0; subspace < decomposition.subspaceTypes.size(); ++subspace ) {
            if ( decomposition.subspaceTypes[ subspace ] != hypro::DynamicType::linear && decomposition.subspaceTypes[ subspace ] != hypro::DynamicType::affine ) {
                hypro::addClockToAutomaton( decomposedHa, subspace, 2 );
            }
        }

        auto roots = hypro::makeDecompositionalRoots<Representation, Number>( decomposedHa, decomposition );
        hypro::DecompositionalAnalyzer<Representation> analyzer( 
            decomposedHa, 
            decomposition, 
            hypro::FixedAnalysisParameters{ 1, hypro::tNumber( 10 ), hypro::tNumber( 0.01 ) }, 
            hypro::AnalysisParameters{ 0.01 }, 
            roots );
        std::cout << "Dimension " << dim << ": Decomposition and root creation took " << runTimer.elapsed().count() <<" sec." << std::endl;        
        
        analyzer.run();
        auto runningTime = runTimer.elapsed();
        ress.emplace_back( { "decompositionalSingularTimeElapse", runningTime, static_cast<int>( dim ) } );
        std::cout << "Dimension " << dim << ":  Running took " << runningTime.count() << " sec." << std::endl;

        ress.mRunningTime += runningTime;
    }


    return ress;
}

Results<std::size_t> decompositionalSingularJumps( const Settings& settings ) {
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
        auto [decomposedHa, decomposition] = hypro::decomposeAutomaton( ha );
        for ( std::size_t subspace = 0; subspace < decomposition.subspaceTypes.size(); ++subspace ) {
            if ( decomposition.subspaceTypes[ subspace ] != hypro::DynamicType::linear && decomposition.subspaceTypes[ subspace ] != hypro::DynamicType::affine ) {
                hypro::addClockToAutomaton( decomposedHa, subspace, 2 );
            }
        }
        auto roots = hypro::makeDecompositionalRoots<Representation, Number>( decomposedHa, decomposition );        
        std::cout << "Dimension " << dim << ": Decomposition and root creation took " << runTimer.elapsed().count() <<" sec." << std::endl;

        hypro::DecompositionalAnalyzer<Representation> analyzer( 
            decomposedHa, 
            decomposition, 
            hypro::FixedAnalysisParameters{ settings.iterations, hypro::tNumber( settings.iterations + 1 ), 0.1}, 
            hypro::AnalysisParameters{ 0.01 }, 
            roots );
        ress.mCreationTime += creationTime;
        
        auto result = analyzer.run();
        auto runningTime = runTimer.elapsed();
        ress.emplace_back( { "decompositionalSingularJumps", runningTime, static_cast<int>( dim ) } );
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