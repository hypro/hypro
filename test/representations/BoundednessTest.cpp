/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "test/defines.h"

#include "gtest/gtest.h"
#include <hypro/datastructures/HybridAutomaton/Condition.h>
#include <hypro/representations/GeometricObjectBase.h>
#include <hypro/representations/boundedness.h>

using namespace hypro;
using Number = mpq_class;
using I = carl::Interval<Number>;
using IV = std::vector<I>;
using Matrix = matrix_t<Number>;
using Vector = vector_t<Number>;

TEST(BoundednessTest, Boxes) {
    EXPECT_TRUE(isBounded(Box<Number>(IV{I{1, 2}, I{3, 4}})));
    EXPECT_FALSE(isBounded(Box<Number>(IV{I{1, carl::BoundType::WEAK, 2, carl::BoundType::INFTY}, I{3, 4}})));
	EXPECT_FALSE( isBounded( Box<Number>( IV{ createUnboundedInterval<Number>() } ) ) );
    EXPECT_TRUE(isBounded(Box<Number>::Empty(1)));
	EXPECT_TRUE( isBounded( Box<Number>() ) );
}

TEST( BoundednessTest, HPolytopes ) {
	auto condition = conditionFromIntervals( IV{ I{ 2, 3 }, I{ 3, 4 } } );
	auto poly = HPolytope<Number>( condition.getMatrix(), condition.getVector() );
	EXPECT_TRUE( isBounded( poly ) );

	condition = conditionFromIntervals( IV{ I{ 2, carl::BoundType::WEAK, 3, carl::BoundType::INFTY }, I{ 3, 4 } } );
	poly = HPolytope<Number>( condition.getMatrix(), condition.getVector() );
	EXPECT_FALSE( isBounded( poly ) );
}
