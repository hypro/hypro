/*
 * Copyright (c) 2021.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 *   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "test/defines.h"

#include "gtest/gtest.h"
#include <cassert>
#include <hypro/algorithms/reachability/Reach.h>
#include <hypro/datastructures/HybridAutomaton/HybridAutomaton.h>
#include <hypro/datastructures/reachability/TreeUtil.h>

using Number = double;
using Matrix = hypro::matrix_t<Number>;
using Vector = hypro::vector_t<Number>;
using Interval = carl::Interval<Number>;
using TimeInterval = carl::Interval<hypro::SegmentInd>;
using Box = hypro::Box<Number>;
using Node = hypro::ReachTreeNode<Box>;
using Location = hypro::Location<Number>;
using Reset = hypro::Reset<Number>;
using Transition = hypro::Transition<Number>;

TEST( ZenoDetectionTest, SimpleDetection ) {
	auto ha = hypro::HybridAutomaton<Number>{};
	auto loc1 = ha.createLocation();
	auto transition = loc1->createTransition( loc1 );

	auto root = Node{ loc1, Box{ std::vector<Interval>{ Interval{ 0, 1 }, Interval{ 0, 1 } } }, TimeInterval{ 0, 0 } };
	auto child{ std::move( root.addChild( Box{ std::vector<Interval>{ Interval{ 0, 1 }, Interval{ 0, 1 } } }, TimeInterval{ 0, 0 },
										  transition ) ) };

	auto zenoTransitions = hypro::getZenoTransitions( &child );
	EXPECT_EQ( 1, zenoTransitions.size() );
	EXPECT_EQ( transition, zenoTransitions.front() );

	/* add further nodes, which are non-Zeno */
	auto transition2 = loc1->createTransition( loc1 );
	Reset reset{};
	Matrix id = Matrix::Identity( 2, 2 );
	Vector translation = Vector( 2 );
	translation << 1, 1;
	reset.setMatrix( id );
	reset.setVector( translation );
	transition2->setReset( reset );
	auto child2{ std::move( child.addChild( Box{ std::vector<Interval>{ Interval{ 0, 1 }, Interval{ 0, 1 } } }, TimeInterval{ 0, 0 },
											transition2 ) ) };
	zenoTransitions.clear();
	zenoTransitions = hypro::getZenoTransitions( &child2 );
	EXPECT_TRUE( zenoTransitions.empty() );
}