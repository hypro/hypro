#include "util.h"

namespace hypro {
namespace reachability {

std::vector<std::size_t> clusterDistribution( std::size_t numberClusters, std::size_t numberStateSets ) {
	if ( numberClusters >= numberStateSets ) {
		return std::vector<std::size_t>( numberStateSets, 1 );
	}
	std::vector<std::size_t> clusterDistribution;
	std::size_t minSegmentsPerCluster = numberStateSets / numberClusters;
	std::size_t maxSegmentsPerCluster = ceil( double( numberStateSets ) / double( numberClusters ) );
	std::size_t largerClusterCount = numberStateSets - minSegmentsPerCluster * numberClusters;

	assert( minSegmentsPerCluster > 0 );
	assert( largerClusterCount <= numberClusters );

	clusterDistribution = std::vector<std::size_t>( numberClusters, minSegmentsPerCluster );
	for ( std::size_t i = 0; i < largerClusterCount; ++i ) {
		clusterDistribution[i] += 1;
	}

	assert( std::all_of( clusterDistribution.begin(), clusterDistribution.end(), []( std::size_t cnt ) { return cnt > 0; } ) && "Will have empty clusters" );
	assert( std::accumulate( clusterDistribution.begin(), clusterDistribution.end(), std::size_t( 0 ) ) == numberStateSets );
	return clusterDistribution;
}

}  // namespace reachability
}  // namespace hypro