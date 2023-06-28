/*
 * Copyright (c) 2022-2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "test/defines.h"

#include "gtest/gtest.h"
#include <hypro/datastructures/HybridAutomaton/HybridAutomaton.h>
#include <hypro/datastructures/reachability/timing/EventTimingProvider.h>

using namespace hypro;

/**
 * @brief Test fixture to initialize the TimingProvider properly for each test.
 */
class EventTimingTest : public ::testing::Test {
  public:
	using T = hypro::tNumber;

  protected:
	void SetUp() override {
		auto& tProvider = EventTimingProvider<double>::getInstance();
		// set up location and transition to simulate reachability analysis.
		loc = new Location<double>();
		std::unique_ptr<Transition<Location<double>>> t = std::make_unique<Transition<Location<double>>>( loc, loc );
		loc->addTransition( std::move( t ) );
		std::unique_ptr<Transition<Location<double>>> t2 = std::make_unique<Transition<Location<double>>>( loc, loc );
		loc->addTransition( std::move( t2 ) );
		tRaw = loc->getTransitions()[0].get();
		tRaw2 = loc->getTransitions()[1].get();

		// adds one node as a CHILD to the ROOT node.
		tProvider.initialize( loc, 10 );

		// get that child node (used later)
		initNode = *( tProvider.getRoot()->getChildren().begin() );
		initNode->rGetTimings().insertInvariant( carl::Interval<T>( 0, 10 ), CONTAINMENT::FULL );
	}

	void TearDown() override {
		EventTimingProvider<double>::getInstance().clear();
		delete loc;
	}

	Location<double>* loc;
	Transition<Location<double>>* tRaw;
	Transition<Location<double>>* tRaw2;

	typename EventTimingNode<double>::Node_t initNode;
};

/**
 * @brief Performing a simple path find.
 */
TEST_F( EventTimingTest, FindPath1 ) {
	auto& tProvider = EventTimingProvider<double>::getInstance();

	// create some fictional path using location and transition.
	Path<double, T> p1{
		  { carl::Interval<T>( 0, 3 ) },
		  { tRaw, carl::Interval<T>( 1, 2 ) },
		  { carl::Interval<T>( T( 1.5 ), 5 ) },
	};

	// the path expects one transition event and consequently a child node, which is not yet present
	// EXPECT_EQ(nullptr, tProvider.getTimingNode(p1));

	auto timings = tProvider.getTimings( p1 );

	EXPECT_EQ( std::nullopt, timings );

	// simulate a transition event:
	// create timing node
	auto ch1 = tProvider.addChildToNode( initNode, 10 );
	// add transition event to parent
	initNode->rGetTimings().insertTransition( tRaw, carl::Interval<T>( 1, 2 ), CONTAINMENT::YES );
	// set properties of child
	ch1->setLocation( loc );
	ch1->setEntryTransition( tRaw );
	ch1->setEntryTimestamp( carl::Interval<T>( 1, 2 ) );
	ch1->rGetTimings().insertInvariant( carl::Interval<T>( 1, 10 ), CONTAINMENT::FULL );

	// query using the previously created path
	EXPECT_EQ( ch1, tProvider.getTimingNode( p1 ) );
	EXPECT_NE( std::nullopt, tProvider.getTimings( p1 ) );
}

/**
 * @brief Performing a merged path find.
 */
TEST_F( EventTimingTest, FindPath2 ) {
	auto& tProvider = EventTimingProvider<double>::getInstance();

	// create some fictional path using location and transition.
	Path<double, T> p1{
		  { carl::Interval<T>( 0, 3 ) },
		  { tRaw, carl::Interval<T>( 1, 3 ) },
		  { carl::Interval<T>( T( 1.5 ), 5 ) },
	};

	// the path expects one transition event and consequently a child node, which is not yet present
	// EXPECT_EQ(nullptr, tProvider.getTimingNode(p1));

	// simulate a transition event:
	// create timing node
	auto ch1 = tProvider.addChildToNode( initNode, 10 );
	auto ch2 = tProvider.addChildToNode( initNode, 10 );

	EXPECT_EQ( std::size_t( 2 ), initNode->getChildren().size() );
	// add transition event to parent
	initNode->rGetTimings().insertTransition( tRaw, carl::Interval<T>( 1, 3 ), CONTAINMENT::FULL );
	// set properties of child 1
	ch1->setLocation( loc );
	ch1->setEntryTransition( tRaw );
	ch1->setEntryTimestamp( carl::Interval<T>( 1, 2 ) );
	// insert invariant intervals to test merge
	ch1->rGetTimings().insertInvariant( carl::Interval<T>( 1, 3 ), CONTAINMENT::FULL );
	// set properties of child 2
	ch2->setLocation( loc );
	ch2->setEntryTransition( tRaw );
	ch2->setEntryTimestamp( carl::Interval<T>( 2, 3 ) );
	// insert invariant intervals to test merge
	ch2->rGetTimings().insertInvariant( carl::Interval<T>( 2, 5 ), CONTAINMENT::FULL );

	// query using the previously created path
	auto timings = tProvider.getTimings( p1 );

	EXPECT_NE( std::nullopt, timings );
	if ( timings ) {
		EXPECT_TRUE( ( *timings ).satisfiedInvariant( carl::Interval<T>( 1, 5 ) ) );
	}
}

/**
 * @brief Performing a more complex path find with one incomplete node.
 */
TEST_F( EventTimingTest, FindPath3 ) {
	auto& tProvider = EventTimingProvider<double>::getInstance();

	// create some fictional path using location and transition.
	Path<double, T> p1{
		  { carl::Interval<T>( 0, 3 ) },
		  { tRaw, carl::Interval<T>( 1, 3 ) },
		  { carl::Interval<T>( 1, 5 ) },
	};

	// path which should work
	Path<double, T> p2{
		  { carl::Interval<T>( 0, 3 ) },
		  { tRaw, carl::Interval<T>( 1, 2 ) },
		  { carl::Interval<T>( 1, 2 ) },
	};

	// the path expects one transition event and consequently a child node, which is not yet present
	// EXPECT_EQ(nullptr, tProvider.getTimingNode(p1));

	// simulate a transition event:
	// create timing node
	auto ch1 = tProvider.addChildToNode( initNode, 10 );
	auto ch2 = tProvider.addChildToNode( initNode, 10 );
	auto ch3 = tProvider.addChildToNode( initNode, 10 );

	EXPECT_EQ( std::size_t( 3 ), initNode->getChildren().size() );
	// add transition event to parent
	initNode->rGetTimings().insertTransition( tRaw, carl::Interval<T>( 1, 4 ), CONTAINMENT::YES );
	initNode->rGetTimings().insertTransition( tRaw2, carl::Interval<T>( 1, 3 ),
											  CONTAINMENT::YES );  // set properties of child 1
	ch1->setLocation( loc );
	ch1->setEntryTransition( tRaw );
	ch1->setEntryTimestamp( carl::Interval<T>( 1, 2 ) );
	// insert invariant intervals to test merge
	ch1->rGetTimings().insertInvariant( carl::Interval<T>( 1, 3 ), CONTAINMENT::FULL );
	// set properties of child 2
	ch2->setLocation( loc );
	ch2->setEntryTransition( tRaw );
	ch2->setEntryTimestamp( carl::Interval<T>( 1, 2 ) );
	ch2->rGetTimings().insertInvariant( carl::Interval<T>( 1, 3 ), CONTAINMENT::FULL );
	// set properties of child 3
	ch3->setLocation( loc );
	ch3->setEntryTransition( tRaw2 );
	ch3->setEntryTimestamp( carl::Interval<T>( 2, 3 ) );

	// query using the previously created path
	auto timings = tProvider.getTimings( p1 );
	// timings should be null, as we do not have information in ch2.
	EXPECT_EQ( std::nullopt, timings );

	// query using the previously created path 2
	timings = tProvider.getTimings( p2 );
	// timings should be null, as we do not have information in ch2.
	EXPECT_NE( std::nullopt, timings );
	if ( timings ) {
		EXPECT_TRUE( ( *timings ).satisfiedInvariant( carl::Interval<T>( 1, 2 ) ) );
	}
}

/**
 * @brief Performing a more complex path find. Idea: We want to simulate several levels of refinement. Some of them will
 * be incomplete - in this test we try to verify a correct fallback to lower levels. In this case the first refinement
 * level aggregates and the second does not.
 */
TEST_F( EventTimingTest, FindPath4 ) {
	auto& tProvider = EventTimingProvider<double>::getInstance();

	// create some fictional path using location and transition.
	Path<double, T> p1{
		  { carl::Interval<T>( 0, 3 ) },
		  { tRaw, carl::Interval<T>( 2, 3 ) },
		  { carl::Interval<T>( 2, 5 ) },
	};

	// add transition event
	initNode->rGetTimings().insertTransition( tRaw, carl::Interval<T>( 2, 3 ), CONTAINMENT::YES );

	// add child node for first level (agg. setting)
	auto ch1 = tProvider.addChildToNode( initNode, 10 );
	ch1->rGetTimings().insertInvariant( carl::Interval<T>( 2, 5 ), CONTAINMENT::FULL );
	ch1->setEntryTransition( tRaw );
	ch1->setEntryTimestamp( carl::Interval<T>( 2, 3 ) );
	ch1->setLocation( loc );
	ch1->setLevel( 0 );

	// now add 3 child nodes as a result of non-aggregation
	// covered entry timestamps [2,2.9]

	// add child node for second level (non-agg. setting)
	auto ch2 = tProvider.addChildToNode( initNode, 10 );
	ch2->rGetTimings().insertInvariant( carl::Interval<T>( 2, 3 ), CONTAINMENT::FULL );
	ch2->setEntryTransition( tRaw );
	ch2->setEntryTimestamp( carl::Interval<T>( 2, T( 2.25 ) ) );
	ch2->setLocation( loc );
	ch2->setLevel( 1 );

	auto ch3 = tProvider.addChildToNode( initNode, 10 );
	ch3->rGetTimings().insertInvariant( carl::Interval<T>( 3, 4 ), CONTAINMENT::FULL );
	ch3->setEntryTransition( tRaw );
	ch3->setEntryTimestamp( carl::Interval<T>( T( 2.25 ), T( 2.75 ) ) );
	ch3->setLocation( loc );
	ch3->setLevel( 1 );

	auto ch4 = tProvider.addChildToNode( initNode, 10 );
	// ch4->rGetTimings().insertInvariant(carl::Interval<T>(4,5), CONTAINMENT::FULL);
	ch4->setEntryTransition( tRaw );
	ch4->setEntryTimestamp( carl::Interval<T>( T( 2.75 ), T( 2.9 ) ) );
	ch4->setLocation( loc );
	ch4->setLevel( 1 );

	// query using the previously created path
	auto timings = tProvider.getTimings( p1 );
	EXPECT_NE( std::nullopt, timings );
}

/**
 * @brief Performing a more complex path find. Idea: We want to simulate several levels of refinement. In this
 * particular test, the most refined setting should be taken (level 1, non-aggregating)
 */
TEST_F( EventTimingTest, FindPath5 ) {
	auto& tProvider = EventTimingProvider<double>::getInstance();

	// create some fictional path using location and transition.
	Path<double, T> p1{
		  { carl::Interval<T>( 0, 3 ) },
		  { tRaw, carl::Interval<T>( 2, 3 ) },
		  { carl::Interval<T>( 2, 5 ) },
	};

	// add transition event
	initNode->rGetTimings().insertTransition( tRaw, carl::Interval<T>( 2, 3 ), CONTAINMENT::YES );

	// add child node for first level (agg. setting)
	auto ch1 = tProvider.addChildToNode( initNode, 10 );
	// set invariant coarser than required
	ch1->rGetTimings().insertInvariant( carl::Interval<T>( 2, 6 ), CONTAINMENT::FULL );
	ch1->setEntryTransition( tRaw );
	ch1->setEntryTimestamp( carl::Interval<T>( 2, 3 ) );
	ch1->setLocation( loc );
	ch1->setLevel( 0 );

	// now add 3 child nodes as a result of non-aggregation
	// covered entry timestamps [2,2.9]

	// add child node for second level (non-agg. setting)
	auto ch2 = tProvider.addChildToNode( initNode, 10 );
	ch2->rGetTimings().insertInvariant( carl::Interval<T>( 2, 3 ), CONTAINMENT::FULL );
	ch2->setEntryTransition( tRaw );
	ch2->setEntryTimestamp( carl::Interval<T>( 2, T( 2.25 ) ) );
	ch2->setLocation( loc );
	ch2->setLevel( 1 );

	auto ch3 = tProvider.addChildToNode( initNode, 10 );
	ch3->rGetTimings().insertInvariant( carl::Interval<T>( 3, 4 ), CONTAINMENT::FULL );
	ch3->setEntryTransition( tRaw );
	ch3->setEntryTimestamp( carl::Interval<T>( T( 2.25 ), T( 2.75 ) ) );
	ch3->setLocation( loc );
	ch3->setLevel( 1 );

	auto ch4 = tProvider.addChildToNode( initNode, 10 );
	ch4->rGetTimings().insertInvariant( carl::Interval<T>( 4, 5 ), CONTAINMENT::FULL );
	ch4->setEntryTransition( tRaw );
	ch4->setEntryTimestamp( carl::Interval<T>( T( 2.75 ), T( 2.9 ) ) );
	ch4->setLocation( loc );
	ch4->setLevel( 1 );

	// query using the previously created path
	auto timings = tProvider.getTimings( p1 );
	EXPECT_NE( std::nullopt, timings );
}
