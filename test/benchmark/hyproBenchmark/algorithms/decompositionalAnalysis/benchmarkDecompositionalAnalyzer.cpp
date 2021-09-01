#include "benchmarkDecompositionalAnalyzer.h"

namespace benchmark {
namespace decompositionalAnalysis {

Results<std::size_t> run( const Settings& settings ) {
    Timer totalRunningTime;
    Results<std::size_t> ress;

    
    std::cout << "Benchmarking singular time elapse with decompositional analyzer." << std::endl;
    
    auto tmp = decompositionalSingularTimeElapse( settings );
    tmp.createCSV( "decompositionalSingularTimeElapse", "\t", "decompositionalSingularTimeElapse" );
    ress.insert( ress.end(), tmp.begin(), tmp.end() );

    std::cout << "Benchmarking singular with jumps with decompositional analyzer." << std::endl;
    tmp = decompositionalSingularJumps( settings );
    tmp.createCSV( "decompositionalSingularJumps", "\t", "decompositionalSingularJumps" );
    ress.insert( ress.end(), tmp.begin(), tmp.end() );

    std::cout << "Decompositional analyzer benchmarking took " << totalRunningTime.elapsedMs() << " sec in total." << std::endl;

    return ress;
}
}  // namespace singularAnalysis
}  // namespace benchmark
