//
// Created by leander.behr on 10/14/19.
//

#include "test/defines.h"
#include "gtest/gtest.h"
#include <hypro/algorithms/quickhull/Quickhull.h>

using namespace hypro;
using number_t = mpq_class;

using qHull = Quickhull<number_t>;
using qIntersection = QuickIntersection<number_t>;

// bool checkContainment(qh::pointVector_t& input, qh& quickhull);
// void printFacet(qh::Facet const& facet, size_t dimension);
// bool exactContains(qh::Facet const& facet, qh::point_t const& point);

template <class Q>
bool containmentCheck( Q quickhull, typename Q::pointVector_t& input ) {
	for ( auto& facet : quickhull.getFacets() ) {
		for ( auto& point : input ) {
			if ( facet.visible( point ) ) return false;
		}
	}
	return true;
}

template <typename Number>
void logPoints( std::vector<vector_t<Number>>& points ) {
	std::stringstream stream;
	stream << std::endl;
	for ( auto point : points ) {
		for ( int d = 0; d < point.rows(); ++d ) {
			stream << carl::convert<Number, double>( point[d] ) << ", ";
		}
		stream << std::endl;
	}
	TRACE( "quickhull", stream.str() );
}

class QuickIntersectionTest : public ::testing::Test {
  protected:
	virtual void SetUp(){};
	virtual void TearDown(){};
};

TEST_F( QuickIntersectionTest, Specific ) {
	qIntersection::pointVector_t inputHalfspaces;

	inputHalfspaces.emplace_back( 3 ) << -1, 0, 1;
	inputHalfspaces.emplace_back( 3 ) << 0, -1, 1;
	inputHalfspaces.emplace_back( 3 ) << 0, 1, -2;
	inputHalfspaces.emplace_back( 3 ) << 1, 0, -2;

	qIntersection qInt{ inputHalfspaces, 2 };
	qInt.compute();

	EXPECT_TRUE( containmentCheck( qInt, inputHalfspaces ) );

	qHull::pointVector_t inputPoints;
	for ( qIntersection::Facet facet : qInt.getFacets() ) {
		inputPoints.emplace_back( 2 );
		inputPoints.back() = facet.mNormal;
		inputPoints.back() /= -facet.mOffset;
	}

	logPoints( inputPoints );

	qHull qh{ inputPoints, 2 };
	qh.compute();

	EXPECT_TRUE( containmentCheck( qh, inputPoints ) );
}

TEST_F( QuickIntersectionTest, Specific2 ) {
	qIntersection::pointVector_t inputPoints;

	inputPoints.emplace_back( 2 ) << -1, 0;
	inputPoints.emplace_back( 2 ) << 0, -1;
	inputPoints.emplace_back( 2 ) << 0, 0.5;
	inputPoints.emplace_back( 2 ) << 0.5, 0;

	qHull qh{ inputPoints, 2 };
	qh.compute();

	EXPECT_TRUE( containmentCheck( qh, inputPoints ) );

	qHull::pointVector_t inputHalfspaces;
	for ( qHull::Facet facet : qh.getFacets() ) {
		inputHalfspaces.emplace_back( 3 );
		inputHalfspaces.back().head( 2 ) = facet.mNormal;
		inputHalfspaces.back()[2] = -facet.mOffset;
	}

	logPoints( inputHalfspaces );

	qIntersection qhInt{ inputHalfspaces, 2 };
	qhInt.compute();

	EXPECT_TRUE( containmentCheck( qhInt, inputHalfspaces ) );
}

TEST_F( QuickIntersectionTest, RandomVertices ) {
	size_t const N = 15;
	size_t const D = 4;

	srand( 42 );

	qHull::pointVector_t inputPoints;

	for ( size_t i = 0; i < N; ++i ) {
		inputPoints.emplace_back( vector_t<number_t>::Random( D ) );
	}

	logPoints( inputPoints );

	qHull quickhull( inputPoints, D );
	quickhull.compute();

	EXPECT_TRUE( containmentCheck( quickhull, inputPoints ) );

	qIntersection::pointVector_t inputHalfspaces;

	for ( qHull::Facet facet : quickhull.getFacets() ) {
		inputHalfspaces.emplace_back( D + 1 );

		inputHalfspaces.back().head( D ) = facet.mNormal;
		inputHalfspaces.back()[D] = -facet.mOffset;
	}

	qIntersection quickIntersection( inputHalfspaces, D );
	quickIntersection.compute();

	EXPECT_TRUE( containmentCheck( quickIntersection, inputHalfspaces ) );

	qIntersection::pointVector_t outputPoints;

	for ( qIntersection::Facet facet : quickIntersection.getFacets() ) {
		outputPoints.emplace_back( D );
		// The resulting points can't be points at infinity
		EXPECT_FALSE( facet.mOffset == 0 );
		facet.mNormal /= -facet.mOffset;
		outputPoints.back() = facet.mNormal;
	}

	logPoints( outputPoints );

	// Each of the reconstruced points should exist in the original points aswell.
	for ( qIntersection::point_t point : outputPoints ) {
		EXPECT_TRUE( std::find( inputPoints.begin(), inputPoints.end(), point ) != inputPoints.end() );
	}
}

TEST_F( QuickIntersectionTest, RandomHalfspaces ) {
	constexpr int N = 50;
	constexpr int D = 4;

	qIntersection::pointVector_t inputHalfspaces;

	for ( int i = 0; i < N; ++i ) {
		inputHalfspaces.push_back( vector_t<number_t>::Random( D + 1 ) );
	}

	// Make sure at least one point is contained
	qIntersection::point_t point = qIntersection::point_t::Random( D );
	for ( auto& halfspace : inputHalfspaces ) {
		if ( halfspace.head( D ).dot( point ) + halfspace[D] > 0 ) {
			halfspace *= -1;
		}
	}

	// Ensure boundedness
	for ( int d = 0; d < D; ++d ) {
		inputHalfspaces.push_back( vector_t<number_t>::Zero( D + 1 ) );
		// Offset = 2
		inputHalfspaces.back()[D] = -10;
		// Limit in d-axis direction to < 10
		inputHalfspaces.back()[d] = 1;

		inputHalfspaces.push_back( vector_t<number_t>::Zero( D + 1 ) );
		// Offset = 2
		inputHalfspaces.back()[D] = -10;
		// Limit in d-axis direction to > -10
		inputHalfspaces.back()[d] = -1;
	}

	qIntersection qInt{ inputHalfspaces, D };
	qInt.compute();

	EXPECT_TRUE( containmentCheck( qInt, inputHalfspaces ) );
}