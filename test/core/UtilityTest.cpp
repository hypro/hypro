#include "gtest/gtest.h"
#include <hypro/types.h>
#include <hypro/util/convenienceOperators.h>
#include <hypro/util/sequenceGeneration/SequenceGenerator.h>
#include <hypro/util/templateDirections.h>
#include <iostream>

TEST( UtilityTest, OutstreamOperators ) {
	std::ostringstream out;
	hypro::SOLUTION sol = hypro::SOLUTION::INFEAS;
	out << sol;
	EXPECT_EQ( "INFEAS", out.str() );

	out.str( std::string() );

	sol = hypro::SOLUTION::FEAS;
	out << sol;
	EXPECT_EQ( "FEAS", out.str() );

	out.str( std::string() );

	sol = hypro::SOLUTION::INFTY;
	out << sol;
	EXPECT_EQ( "INFTY", out.str() );

	out.str( std::string() );

	sol = hypro::SOLUTION::UNKNOWN;
	out << sol;
	EXPECT_EQ( "UNKNOWN", out.str() );
}

TEST( UtilityTest, CreateTemplateDirections ) {
	std::vector<hypro::vector_t<double>> res = hypro::computeTemplate<double>( 1, 4 );
	EXPECT_EQ( res.size(), unsigned( 2 ) );

	res = hypro::computeTemplate<double>( 2, 4 );
	EXPECT_EQ( res.size(), unsigned( 4 ) );
	hypro::vector_t<double> toFind = hypro::vector_t<double>( 2 );
	toFind << 1, 0;
	EXPECT_TRUE( std::find( res.begin(), res.end(), toFind ) != res.end() );
	toFind << 0, 1;
	EXPECT_TRUE( std::find( res.begin(), res.end(), toFind ) != res.end() );
	toFind << -1, 0;
	EXPECT_TRUE( std::find( res.begin(), res.end(), toFind ) != res.end() );
	toFind << 0, -1;
	EXPECT_TRUE( std::find( res.begin(), res.end(), toFind ) != res.end() );

	res = hypro::computeTemplate<double>( 2, 8 );
	EXPECT_EQ( res.size(), unsigned( 8 ) );
	toFind << 1, 0;
	EXPECT_TRUE( std::find( res.begin(), res.end(), toFind ) != res.end() );
	toFind << 1, 1;
	EXPECT_TRUE( std::find( res.begin(), res.end(), toFind ) != res.end() );
	toFind << 0, 1;
	EXPECT_TRUE( std::find( res.begin(), res.end(), toFind ) != res.end() );
	toFind << -1, 1;
	EXPECT_TRUE( std::find( res.begin(), res.end(), toFind ) != res.end() );
	toFind << -1, 0;
	EXPECT_TRUE( std::find( res.begin(), res.end(), toFind ) != res.end() );
	toFind << -1, -1;
	EXPECT_TRUE( std::find( res.begin(), res.end(), toFind ) != res.end() );
	toFind << 0, -1;
	EXPECT_TRUE( std::find( res.begin(), res.end(), toFind ) != res.end() );
	toFind << 1, -1;
	EXPECT_TRUE( std::find( res.begin(), res.end(), toFind ) != res.end() );

	// we do not test for containment of all vectors here (numerics)
	res = hypro::computeTemplate<double>( 2, 12 );
	EXPECT_EQ( res.size(), unsigned( 12 ) );

	// test higher dimensional reduced template creation
	std::vector<std::size_t> dimensions;
	dimensions.push_back( 0 );
	dimensions.push_back( 2 );

	res = hypro::computeTemplate<double>( dimensions, 4, 3 );
	EXPECT_EQ( res.size(), unsigned( 4 ) );
	toFind = hypro::vector_t<double>( 3 );
	toFind << 1, 0, 0;
	EXPECT_TRUE( std::find( res.begin(), res.end(), toFind ) != res.end() );
	toFind << 0, 0, 1;
	EXPECT_TRUE( std::find( res.begin(), res.end(), toFind ) != res.end() );
	toFind << -1, 0, 0;
	EXPECT_TRUE( std::find( res.begin(), res.end(), toFind ) != res.end() );
	toFind << 0, 0, -1;
	EXPECT_TRUE( std::find( res.begin(), res.end(), toFind ) != res.end() );

	res = hypro::computeTemplate<double>( dimensions, 8, 3 );
	EXPECT_EQ( res.size(), unsigned( 8 ) );
	toFind << 1, 0, 0;
	EXPECT_TRUE( std::find( res.begin(), res.end(), toFind ) != res.end() );
	toFind << 1, 0, 1;
	EXPECT_TRUE( std::find( res.begin(), res.end(), toFind ) != res.end() );
	toFind << 0, 0, 1;
	EXPECT_TRUE( std::find( res.begin(), res.end(), toFind ) != res.end() );
	toFind << -1, 0, 1;
	EXPECT_TRUE( std::find( res.begin(), res.end(), toFind ) != res.end() );
	toFind << -1, 0, 0;
	EXPECT_TRUE( std::find( res.begin(), res.end(), toFind ) != res.end() );
	toFind << -1, 0, -1;
	EXPECT_TRUE( std::find( res.begin(), res.end(), toFind ) != res.end() );
	toFind << 0, 0, -1;
	EXPECT_TRUE( std::find( res.begin(), res.end(), toFind ) != res.end() );
	toFind << 1, 0, -1;
	EXPECT_TRUE( std::find( res.begin(), res.end(), toFind ) != res.end() );

	// we do not test for containment of all vectors here (numerics)
	res = hypro::computeTemplate<double>( 2, 12 );
	EXPECT_EQ( res.size(), unsigned( 12 ) );
}

template <typename ElementType>
bool isDuplicate( const std::vector<ElementType>& sequence, const ElementType& rhs ) {
	return std::count( sequence.begin(), sequence.end(), rhs ) > 1;
}

TEST( UtilityTest, Permutator ) {
	// permutator which creates all combinations of 2-tuples where values are chosen from the domain [0,3].
	// Values are chosen without duplicates and without considering order.
	hypro::Permutator perm{ 4, 2 };

	std::size_t count = 0;
	std::vector<std::vector<std::size_t>> tuples;
	while ( !perm.end() ) {
		auto cur = perm();
		++count;
		EXPECT_TRUE( cur.size() == 2 );
		for ( const auto val : cur ) {
			std::cout << val << " ";
			EXPECT_TRUE( val < 4 );
		}
		std::cout << std::endl;
		tuples.emplace_back( cur );
	}

	EXPECT_EQ( std::size_t( 6 ), count );
	EXPECT_TRUE( std::none_of( tuples.begin(), tuples.end(),
							   [&]( const auto& tuple ) { return isDuplicate( tuples, tuple ); } ) );
}

TEST( UtilityTest, Combinator ) {
	// permutator which creates all combinations of 4-tuples with values from 0,1.
	hypro::Combinator comb{ 2, 4 };

	std::size_t count = 0;
	std::vector<std::vector<std::size_t>> tuples;
	while ( !comb.end() ) {
		auto cur = comb();
		++count;
		EXPECT_TRUE( cur.size() == 4 );
		EXPECT_TRUE( std::all_of( cur.begin(), cur.end(), []( auto val ) { return val == 0 || val == 1; } ) );
		for ( const auto val : cur ) {
			std::cout << val << " ";
		}
		std::cout << std::endl;
		tuples.emplace_back( cur );
	}
	EXPECT_EQ( std::size_t( 16 ), count );
	EXPECT_TRUE( std::none_of( tuples.begin(), tuples.end(),
							   [&]( const auto& tuple ) { return isDuplicate( tuples, tuple ); } ) );
}
