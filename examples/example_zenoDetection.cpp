/*
 * Copyright (c) 2022.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/*
 * Created by Stefan Schupp <stefan.schupp@tuwien.ac.at> on 13.07.22.
 */

#include <hypro/algorithms/reachability/fixedPointDetection.h>
#include <hypro/datastructures/reachability/ReachTreev2.h>
#include <hypro/representations/GeometricObjectBase.h>
#include <hypro/types.h>

int main() {
	using Number = double;
	using Interval = carl::Interval<Number>;
	using TimeInterval = carl::Interval<hypro::SegmentInd>;
	using Box = hypro::Box<Number>;
	using Node = hypro::ReachTreeNode<Box>;
	using Location = hypro::Location<Number>;
	using Reset = hypro::Reset<Number>;
	using Transition = hypro::Transition<Number>;
	using M = hypro::matrix_t<Number>;
	using V = hypro::vector_t<Number>;

	// cleanup variables pool for better readability of the variables' names
	hypro::VariablePool::getInstance().clear();

	auto ha = hypro::HybridAutomaton<Number>{};
	auto loc1 = ha.createLocation();
	auto loc2 = ha.createLocation();
	// set flow, required
	M flow = M::Identity( 3, 3 );
	flow( 2, 2 ) = 0;
	loc1->setFlow( flow );
	loc2->setFlow( flow );
	auto transition = loc1->createTransition( loc2 );
	M trafo = M::Identity( 2, 2 );
	trafo( 0, 0 ) = 0;
	V trans = V::Zero( 2 );
	trans( 0 ) = 2;
	transition->setReset( { trafo, trans } );
	M constraint = M::Zero( 2, 2 );
	constraint << 1, 0, -1, 0;
	V constant = V::Zero( 2 );
	transition->setGuard( { constraint, constant } );

	auto root = Node{ loc1, Box{ std::vector<Interval>{ Interval{ 0, 1 }, Interval{ 0, 1 } } }, TimeInterval{ 0, 0 } };
	auto child{ std::move( root.addChild( Box{ std::vector<Interval>{ Interval{ 0, 1 }, Interval{ 0, 1 } } }, TimeInterval{ 0, 0 },
										  transition ) ) };

	auto zenoTransitions = hypro::getZenoTransitions( &child );
	std::cout << "Number of Zeno transitions: " << zenoTransitions << std::endl;

	/* add further nodes, which are non-Zeno */
	auto transition2 = loc2->createTransition( loc1 );

	V translation = V( 2 );
	translation << 0, 0;
	Reset reset{ trafo, translation };
	transition2->setReset( reset );
	constant( 0 ) = 2;
	constant( 1 ) = -2;
	transition2->setGuard( { constraint, constant } );
	auto child2{ std::move( child.addChild( Box{ std::vector<Interval>{ Interval{ 0, 1 }, Interval{ 0, 1 } } }, TimeInterval{ 0, 0 },
											transition2 ) ) };
	auto path = child2.getPath();

	bool hasZeno = isZenoCycle2( path );

	std::cout << "Detected Zeno: " << hasZeno << std::endl;

	return 0;
}