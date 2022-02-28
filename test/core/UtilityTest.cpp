/*
 * Copyright (c) 2022.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 *   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "gtest/gtest.h"
#include <hypro/types.h>
#include <hypro/util/convenienceOperators.h>
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
