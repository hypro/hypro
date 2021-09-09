#include "benchmarkBox.h"

namespace benchmark {
namespace box {

Results<std::size_t> intersect( const Settings& settings ) {
	Results<std::size_t> ress;
	// benchmark against PPL
#ifdef HYPRO_USE_PPL
	using pplItv = Parma_Polyhedra_Library::Interval<
		  double, Parma_Polyhedra_Library::Interval_Info_Null<benchmark::box::Double_Interval_Policy>>;
	using pplbox = Parma_Polyhedra_Library::Box<pplItv>;
#endif

	// initialize random number generator
	std::mt19937 generator;
	std::uniform_int_distribution<int> dist = std::uniform_int_distribution<int>( 0, 10 );

	// iterate over dimensions
	for ( std::size_t d = 1; d < settings.maxDimension; ++d ) {
		// create instances
		std::vector<hypro::Box<::benchmark::Number>> lhsBoxes;
		std::vector<hypro::Box<::benchmark::Number>> rhsBoxes;
#ifdef HYPRO_USE_PPL
		std::vector<pplbox> pplLhsBoxes;
		std::vector<pplbox> pplRhsBoxes;
#endif
		Timer creationTimer;
		for ( std::size_t i = 0; i < settings.iterations; ++i ) {
			hypro::Box<::benchmark::Number> lhsBox;
			hypro::Box<::benchmark::Number> rhsBox;
			// create same constraint for PPL.
#ifdef HYPRO_USE_PPL
			pplbox lhs = pplbox( d );
			pplbox rhs = pplbox( d );
#endif

			for ( std::size_t id = 0; id < d; ++id ) {
				::benchmark::Number ll = -dist( generator );
				::benchmark::Number lu = dist( generator );
				::benchmark::Number rl = -dist( generator );
				::benchmark::Number ru = dist( generator );

				lhsBox.insert( carl::Interval<::benchmark::Number>( ll, lu ) );
				rhsBox.insert( carl::Interval<::benchmark::Number>( rl, ru ) );
				assert( !lhsBox.empty() );
				assert( !rhsBox.empty() );

#ifdef HYPRO_USE_PPL
				pplItv itvl;
				pplItv itvr;
				itvl.lower() = ll;
				itvl.upper() = lu;
				itvr.lower() = rl;
				itvr.upper() = ru;
				lhs.set_interval( Parma_Polyhedra_Library::Variable( id ), itvl );
				rhs.set_interval( Parma_Polyhedra_Library::Variable( id ), itvr );
#endif
			}
			lhsBoxes.emplace_back( std::move( lhsBox ) );
			rhsBoxes.emplace_back( std::move( rhsBox ) );
#ifdef HYPRO_USE_PPL
			pplLhsBoxes.emplace_back( lhs );
			pplRhsBoxes.emplace_back( rhs );
#endif
		}
		auto creationTime = creationTimer.elapsed();
		// std::cout << "Dimension " << d << ": Creation took " << creationTime.count() << " sec." << std::endl;
		ress.mCreationTime += creationTime;

		// run instances
		Timer runTimerHyPro;
		for ( std::size_t i = 0; i < settings.iterations; ++i ) {
			auto tmp = lhsBoxes[i].intersect( rhsBoxes[i] );
		}
		auto runningTime = runTimerHyPro.elapsed();
		ress.emplace_back( { "intersect", runningTime / settings.iterations, static_cast<int>( d ) } );
		// std::cout << "Dimension " << d << ":  Running took " << runningTime.count() << " sec." << std::endl;

#ifdef HYPRO_USE_PPL
		Timer runTimerPPL;
		for ( std::size_t i = 0; i < settings.iterations; ++i ) {
			pplLhsBoxes[i].intersection_assign( pplRhsBoxes[i] );
		}
		runningTime = runTimerPPL.elapsed();
		ress.emplace_back( { "intersectPPL", runningTime / settings.iterations, static_cast<int>( d ) } );
		std::cout << "Dimension " << d << ":  Running took " << runningTime.count() << " sec (PPL)." << std::endl;
#endif

		ress.mRunningTime += runningTime;
	}
	return ress;
}

}  // namespace box
}  // namespace benchmark
