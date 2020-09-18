//
// Created by leander.behr on 10/14/19.
//

#include "../defines.h"
#include "gtest/gtest.h"
#include <hypro/algorithms/quickhull/Quickhull.h>

using namespace hypro;
using number_t = mpq_class;
using qh = hypro::Quickhull<number_t>;

bool checkContainment( qh::pointVector_t& inputs, qh& quickhull );
bool nonFancyCheckContainment( qh::pointVector_t& inputs, qh& quickhull );
void printFacet( qh::Facet const& facet, size_t dimension );
bool exactContains( qh::Facet const& facet, qh::point_t const& point );

class QuickhullTest : public ::testing::Test {
  protected:
	virtual void SetUp(){};
	virtual void TearDown(){};
};

TEST_F( QuickhullTest, RandomVertices ) {
	size_t const N = 50;
	size_t const D = 4;

	srand( 42 );

	qh::pointVector_t inputs;

	for ( size_t i = 0; i < N; ++i ) {
		inputs.emplace_back( qh::point_t::Random( D ) );
	}

	qh quickhull( inputs, D );
	quickhull.compute();

	EXPECT_TRUE( nonFancyCheckContainment( inputs, quickhull ) );
}

TEST_F( QuickhullTest, SpecificEnumeration ) {
	qh::pointVector_t vertices{};
	vertices.emplace_back( 3 ) << number_t( -9 ) / number_t( 100 ), 15, number_t( 14 ) / number_t( 10 );
	vertices.emplace_back( 3 ) << number_t( -9 ) / number_t( 100 ), 16, number_t( 14 ) / number_t( 10 );
	vertices.emplace_back( 3 ) << number_t( -9 ) / number_t( 100 ), 15, number_t( 13 ) / number_t( 10 );
	vertices.emplace_back( 3 ) << number_t( -9 ) / number_t( 100 ), 16, number_t( 13 ) / number_t( 10 );
	vertices.emplace_back( 3 ) << number_t( -9 ) / number_t( 100 ), 15, number_t( 6 ) / number_t( 5 );
	vertices.emplace_back( 3 ) << number_t( -9 ) / number_t( 100 ), 16, number_t( 6 ) / number_t( 5 );
	vertices.emplace_back( 3 ) << number_t( -9 ) / number_t( 100 ), 15, number_t( 9 ) / number_t( 100 );
	vertices.emplace_back( 3 ) << number_t( -9 ) / number_t( 100 ), 16, number_t( 9 ) / number_t( 100 );
	vertices.emplace_back( 3 ) << number_t( -9 ) / number_t( 10 ), 15, 0;
	vertices.emplace_back( 3 ) << number_t( -9 ) / number_t( 10 ), 16, 0;
	vertices.emplace_back( 3 ) << number_t( -1 ) / number_t( 2 ), 15, number_t( 5 ) / number_t( 2 );
	vertices.emplace_back( 3 ) << number_t( -1 ) / number_t( 2 ), 16, number_t( 5 ) / number_t( 2 );
	vertices.emplace_back( 3 ) << number_t( -47 ) / number_t( 100 ), 15, number_t( 5 ) / number_t( 2 );
	vertices.emplace_back( 3 ) << number_t( -47 ) / number_t( 100 ), 16, number_t( 5 ) / number_t( 2 );
	vertices.emplace_back( 3 ) << 0, 15, 0;
	vertices.emplace_back( 3 ) << 0, 15, number_t( 7 ) / number_t( 5 );
	vertices.emplace_back( 3 ) << 0, 15, number_t( 5 ) / number_t( 2 );
	vertices.emplace_back( 3 ) << 0, 16, 0;
	vertices.emplace_back( 3 ) << 0, 16, number_t( 7 ) / number_t( 5 );
	vertices.emplace_back( 3 ) << 0, 16, number_t( 5 ) / number_t( 2 );

	qh quickhull{ vertices, 3 };
	quickhull.compute();

	for ( auto const& facet : quickhull.getFacets() ) {
		printFacet( facet, 3 );
	}
	std::cout << "SpecificEnumeration END" << std::endl;
	EXPECT_TRUE( nonFancyCheckContainment( vertices, quickhull ) );
}

TEST_F( QuickhullTest, Degenerate ) {
	qh::pointVector_t vertices{};
	vertices.emplace_back( 3 ) << 5, 0, 0;
	vertices.emplace_back( 3 ) << 3, -2, 4;
	vertices.emplace_back( 3 ) << number_t( 1 ) / number_t( 2 ), 3, number_t( 3 ) / number_t( 2 );
	vertices.emplace_back( 3 ) << -12, 14, 3;
	vertices.emplace_back( 3 ) << number_t( 9 ) / number_t( 100 ), 16, number_t( -1109 ) / number_t( 100 );

	qh quickhull{ vertices, 3 };
	quickhull.compute();

	for ( auto const& facet : quickhull.getFacets() ) {
		printFacet( facet, 3 );
	}
	std::cout << "Degenerate END" << std::endl;
	EXPECT_TRUE( nonFancyCheckContainment( vertices, quickhull ) );
}

TEST_F( QuickhullTest, Degenerate3dLine ) {
	qh::pointVector_t vertices{};
	vertices.emplace_back( 3 ) << 5, 0, 0;
	vertices.emplace_back( 3 ) << 3, -2, 4;

	qh quickhull{ vertices, 3 };
	quickhull.compute();

	for ( auto const& facet : quickhull.getFacets() ) {
		printFacet( facet, 3 );
	}
	std::cout << "Degenerate3dLine END" << std::endl;
	EXPECT_TRUE( nonFancyCheckContainment( vertices, quickhull ) );
}

TEST_F( QuickhullTest, Degenerate6dSurface ) {
	size_t const N = 500;
	size_t const D = 6;

	srand( 42 );

	qh::pointVector_t inputs;

	for ( size_t i = 0; i < N; ++i ) {
		inputs.emplace_back( qh::point_t::Random( D ) );
	}

	std::cout << std::setprecision( 23 );

	qh::pointVector_t vertices{};
	vertices.emplace_back( qh::point_t::Random( 6 ) );
	vertices.emplace_back( qh::point_t::Random( 6 ) );
	vertices.emplace_back( qh::point_t::Random( 6 ) );

	qh quickhull{ vertices, 6 };
	quickhull.compute();

	for ( auto const& facet : quickhull.getFacets() ) {
		printFacet( facet, 6 );
	}
	std::cout << "Degenerate6dSurface END" << std::endl;
	EXPECT_TRUE( nonFancyCheckContainment( vertices, quickhull ) );
}

TEST_F( QuickhullTest, SinglePoint ) {
	qh::pointVector_t vertices{};

	vertices.emplace_back( 3 ) << number_t( 9 ) / number_t( 100 ), 16, number_t( -1109 ) / number_t( 100 );

	qh quickhull{ vertices, 3 };
	quickhull.compute();

	for ( auto const& facet : quickhull.getFacets() ) {
		printFacet( facet, 3 );
	}
	std::cout << "SinglePoint END" << std::endl;
	EXPECT_TRUE( nonFancyCheckContainment( vertices, quickhull ) );
}

TEST_F( QuickhullTest, RodReactor ) {
	qh::pointVector_t vertices{};
	vertices.emplace_back( 3 ) << 524.991, 29.16, 29.16;
	vertices.emplace_back( 3 ) << 524.994, 29.16, 29.16;
	vertices.emplace_back( 3 ) << 524.991, 29.16, 29.16;
	vertices.emplace_back( 3 ) << 524.994, 29.16, 29.16;
	vertices.emplace_back( 3 ) << 524.991, 29.16, 29.16;
	vertices.emplace_back( 3 ) << 524.994, 29.16, 29.16;
	vertices.emplace_back( 3 ) << 524.991, 29.16, 29.16;
	vertices.emplace_back( 3 ) << 524.994, 29.16, 29.16;

	vertices.emplace_back( 3 ) << 525.016, 29.17, 29.17;
	vertices.emplace_back( 3 ) << 525.019, 29.17, 29.17;
	vertices.emplace_back( 3 ) << 525.016, 29.17, 29.17;
	vertices.emplace_back( 3 ) << 525.019, 29.17, 29.17;
	vertices.emplace_back( 3 ) << 525.016, 29.17, 29.17;
	vertices.emplace_back( 3 ) << 525.019, 29.17, 29.17;
	vertices.emplace_back( 3 ) << 525.016, 29.17, 29.17;
	vertices.emplace_back( 3 ) << 525.019, 29.17, 29.17;

	vertices.emplace_back( 3 ) << 5, 29.17, 29.17;

	qh quickhull{ vertices, 3 };
	quickhull.compute();

	for ( auto const& facet : quickhull.getFacets() ) {
		printFacet( facet, 3 );
	}
	std::cout << "Degenerate END" << std::endl;
	EXPECT_TRUE( nonFancyCheckContainment( vertices, quickhull ) );
}

bool checkContainment( qh::pointVector_t& inputs, qh& quickhull ) {
	return std::all_of( inputs.begin(), inputs.end(), [&quickhull]( qh::point_t& v ) {
		return std::all_of( quickhull.getFacets().begin(), quickhull.getFacets().end(),
							[&v]( qh::Facet const& facet ) { return !facet.visible( v ); } );
	} );
}
bool nonFancyCheckContainment( qh::pointVector_t& inputs, qh& quickhull ) {
	for ( auto const& vertex : inputs ) {
		for ( auto& facet : quickhull.getFacets() ) {
			if ( !exactContains( facet, vertex ) ) return false;
		}
	}
	return true;
}

void printFacet( qh::Facet const& facet, size_t dimension ) {
	char var = 'b';

	std::cout << "(" << facet.mNormal[0] << ")a";
	for ( size_t i = 1; i < dimension; ++i ) {
		std::cout << " + (" << facet.mNormal[i] << ")" << var;
		var += 1;
	}

	std::cout << " = " << facet.mOffset << std::endl;
}

bool exactContains( qh::Facet const& facet, qh::point_t const& point ) {
	hypro::vector_t<mpq_class> normal = facet.mNormal.template cast<mpq_class>();
	hypro::vector_t<mpq_class> mpq_vertex = point.template cast<mpq_class>();
	mpq_class offset = facet.mOffset;

	return normal.dot( mpq_vertex ) - offset <= 0;
}