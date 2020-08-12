#include "algorithms/reachability/handlers/jumpHandlers/util.h"
#include "gtest/gtest.h"
#include <iostream>

TEST( UtilityTest, ClusteringDistribution ) {
	// full aggregation of 10 state sets
	auto distr1 = hypro::reachability::clusterDistribution( 1, 10 );
	EXPECT_EQ( std::vector<std::size_t>{ 10 }, distr1 );

	// full distribution of 10 state sets on 10 clusters
	auto distr2 = hypro::reachability::clusterDistribution( 10, 10 );
	EXPECT_EQ( std::vector<std::size_t>( 10, 1 ), distr2 );

	// uniform distribution
	auto distr3 = hypro::reachability::clusterDistribution( 3, 6 );
	EXPECT_EQ( std::vector<std::size_t>( 3, 2 ), distr3 );

	// non-uniform distribution
	auto distr4 = hypro::reachability::clusterDistribution( 5, 6 );
	std::vector<std::size_t> expected{ 2, 1, 1, 1, 1 };
	EXPECT_EQ( expected, distr4 );

	// non-matching distribution (3 sets on 6 clusters)
	auto distr5 = hypro::reachability::clusterDistribution( 6, 3 );
	EXPECT_EQ( std::vector<std::size_t>( 3, 1 ), distr5 );
}
