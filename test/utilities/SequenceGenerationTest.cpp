/*
 * Copyright (c) 2022.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 *   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/*
 * Created by Stefan Schupp <stefan.schupp@tuwien.ac.at> on 17.02.22.
 */

#include "gtest/gtest.h"
#include <hypro/types.h>
#include <hypro/util/convenienceOperators.h>
#include <hypro/util/sequenceGeneration/SequenceGenerator.h>
#include <iostream>

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
			EXPECT_TRUE( val < 4 );
		}
		tuples.emplace_back( cur );
	}

	EXPECT_EQ( std::size_t( 6 ), count );
	EXPECT_TRUE( std::none_of( tuples.begin(), tuples.end(),
							   [&]( const auto& tuple ) { return isDuplicate( tuples, tuple ); } ) );
}

TEST( UtilityTest, CombinatorDifferentBounds ) {
	// permutator which creates all combinations of 2-tuples where values are chosen from the domain [0,3].
	// Values are chosen without duplicates and without considering order.
	hypro::Combinator perm{ { 2, 1, 3, 2 }, 4 };

	std::size_t count = 0;
	std::vector<std::vector<std::size_t>> tuples;
	while ( !perm.end() ) {
		auto cur = perm();
		++count;
		for ( const auto val : cur ) {
			EXPECT_TRUE( val < 4 );
		}
		EXPECT_TRUE( cur.size() == 4 );
		tuples.emplace_back( cur );
	}

	EXPECT_EQ( std::size_t( 12 ), count );
	std::vector<std::vector<std::size_t>> expected{
		  { 0, 0, 0, 0 },
		  { 0, 0, 0, 1 },
		  { 0, 0, 1, 0 },
		  { 0, 0, 1, 1 },
		  { 0, 0, 2, 0 },
		  { 0, 0, 2, 1 },
		  { 1, 0, 0, 0 },
		  { 1, 0, 0, 1 },
		  { 1, 0, 1, 0 },
		  { 1, 0, 1, 1 },
		  { 1, 0, 2, 0 },
		  { 1, 0, 2, 1 },
	};
	EXPECT_TRUE( std::all_of( std::begin( expected ), std::end( expected ), [&tuples]( const auto& exp ) { return std::find( std::begin( tuples ), std::end( tuples ), exp ) != std::end( tuples ); } ) );
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
		tuples.emplace_back( cur );
	}
	EXPECT_EQ( std::size_t( 16 ), count );
	EXPECT_TRUE( std::none_of( tuples.begin(), tuples.end(),
							   [&]( const auto& tuple ) { return isDuplicate( tuples, tuple ); } ) );
}