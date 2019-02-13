#include "gtest/gtest.h"
#include "../defines.h"
#include "../../hypro/datastructures/reachability/timing/EventTimingProvider.h"
#include "../../hypro/datastructures/HybridAutomaton/Location.h"
#include "../../hypro/datastructures/HybridAutomaton/Transition.h"

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
        std::unique_ptr<Transition<double>> t = std::make_unique<Transition<double>>(loc,loc);
        loc->addTransition(std::move(t));
        std::unique_ptr<Transition<double>> t2 = std::make_unique<Transition<double>>(loc,loc);
        loc->addTransition(std::move(t2));
        tRaw = loc->getTransitions()[0];
        tRaw2 = loc->getTransitions()[1];

        // adds one node as a CHILD to the ROOT node.
        tProvider.initialize(loc, 10);

        // get that child node (used later)
        initNode = *(tProvider.getRoot()->getChildren().begin());
        initNode->rGetTimings().insertInvariant(carl::Interval<T>(0,10), CONTAINMENT::FULL);
    }

    void TearDown() override {
        EventTimingProvider<double>::getInstance().clear();
    }

    Location<double>* loc;
    Transition<double>* tRaw;
    Transition<double>* tRaw2;

    EventTimingNode<double>* initNode;
};

/**
 * @brief Performing a simple path find.
 */
TEST_F(EventTimingTest, FindPath1)
{
    auto& tProvider = EventTimingProvider<double>::getInstance();

    // create some fictional path using location and transition.
    Path<double,T> p1{
        {carl::Interval<T>(0,3)},
        {tRaw, carl::Interval<T>(1,2)},
        {carl::Interval<T>(T(1.5),5)},
    };

    // the path expects one transition event and consequently a child node, which is not yet present
    EXPECT_EQ(nullptr, tProvider.getTimingNode(p1));
    EXPECT_EQ(std::nullopt, tProvider.getTimings(p1));

    // simulate a transition event:
    // create timing node
    EventTimingNode<double>* ch1 = tProvider.addChildToNode(initNode, 10);
    // add transition event to parent
    initNode->rGetTimings().insertTransition(tRaw,carl::Interval<T>(1,2), CONTAINMENT::YES);
    // set properties of child
    ch1->setLocation(loc);
    ch1->setEntryTransition(tRaw);
    ch1->setEntryTimestamp(carl::Interval<T>(1,2));
    ch1->rGetTimings().insertInvariant(carl::Interval<T>(1,10), CONTAINMENT::FULL);

    // query using the previously created path
    EXPECT_EQ(ch1, tProvider.getTimingNode(p1));
    EXPECT_NE(std::nullopt, tProvider.getTimings(p1));
}

/**
 * @brief Performing a merged path find.
 */
TEST_F(EventTimingTest, FindPath2)
{
    auto& tProvider = EventTimingProvider<double>::getInstance();

    // create some fictional path using location and transition.
    Path<double,T> p1{
        {carl::Interval<T>(0,3)},
        {tRaw, carl::Interval<T>(1,3)},
        {carl::Interval<T>(T(1.5),5)},
    };

    // the path expects one transition event and consequently a child node, which is not yet present
    EXPECT_EQ(nullptr, tProvider.getTimingNode(p1));

    // simulate a transition event:
    // create timing node
    EventTimingNode<double>* ch1 = tProvider.addChildToNode(initNode, 10);
    EventTimingNode<double>* ch2 = tProvider.addChildToNode(initNode, 10);

    EXPECT_EQ(2, initNode->getChildren().size());
    // add transition event to parent
    initNode->rGetTimings().insertTransition(tRaw,carl::Interval<T>(1,3), CONTAINMENT::FULL);
    // set properties of child 1
    ch1->setLocation(loc);
    ch1->setEntryTransition(tRaw);
    ch1->setEntryTimestamp(carl::Interval<T>(1,2));
    // insert invariant intervals to test merge
    ch1->rGetTimings().insertInvariant(carl::Interval<T>(1,3), CONTAINMENT::FULL);
    // set properties of child 2
    ch2->setLocation(loc);
    ch2->setEntryTransition(tRaw);
    ch2->setEntryTimestamp(carl::Interval<T>(2,3));
    // insert invariant intervals to test merge
    ch2->rGetTimings().insertInvariant(carl::Interval<T>(2,5), CONTAINMENT::FULL);

    // query using the previously created path
    auto timings = tProvider.getTimings(p1);
    EXPECT_NE(std::nullopt, timings);
    if(timings) {
        EXPECT_TRUE((*timings).satisfiedInvariant(carl::Interval<T>(1,5)));
    }
}

/**
 * @brief Performing a more complex path find with one incomplete node.
 */
TEST_F(EventTimingTest, FindPath3)
{
    auto& tProvider = EventTimingProvider<double>::getInstance();

    // create some fictional path using location and transition.
    Path<double,T> p1{
        {carl::Interval<T>(0,3)},
        {tRaw, carl::Interval<T>(1,3)},
        {carl::Interval<T>(1,5)},
    };

    // path which should work
    Path<double,T> p2{
        {carl::Interval<T>(0,3)},
        {tRaw, carl::Interval<T>(1,2)},
        {carl::Interval<T>(1,2)},
    };

    // the path expects one transition event and consequently a child node, which is not yet present
    EXPECT_EQ(nullptr, tProvider.getTimingNode(p1));

    // simulate a transition event:
    // create timing node
    EventTimingNode<double>* ch1 = tProvider.addChildToNode(initNode, 10);
    EventTimingNode<double>* ch2 = tProvider.addChildToNode(initNode, 10);
    EventTimingNode<double>* ch3 = tProvider.addChildToNode(initNode, 10);

    EXPECT_EQ(3, initNode->getChildren().size());
    // add transition event to parent
    initNode->rGetTimings().insertTransition(tRaw,carl::Interval<T>(1,4), CONTAINMENT::YES);
    initNode->rGetTimings().insertTransition(tRaw2,carl::Interval<T>(1,3), CONTAINMENT::YES);    // set properties of child 1
    ch1->setLocation(loc);
    ch1->setEntryTransition(tRaw);
    ch1->setEntryTimestamp(carl::Interval<T>(1,2));
    // insert invariant intervals to test merge
    ch1->rGetTimings().insertInvariant(carl::Interval<T>(1,3), CONTAINMENT::FULL);
    // set properties of child 2
    ch2->setLocation(loc);
    ch2->setEntryTransition(tRaw);
    ch2->setEntryTimestamp(carl::Interval<T>(1,2));
    ch2->rGetTimings().insertInvariant(carl::Interval<T>(1,3), CONTAINMENT::FULL);
    // set properties of child 3
    ch3->setLocation(loc);
    ch3->setEntryTransition(tRaw2);
    ch3->setEntryTimestamp(carl::Interval<T>(2,3));

    // query using the previously created path
    auto timings = tProvider.getTimings(p1);
    // timings should be null, as we do not have information in ch2.
    EXPECT_EQ(std::nullopt, timings);

    // query using the previously created path 2
    timings = tProvider.getTimings(p2);
    // timings should be null, as we do not have information in ch2.
    EXPECT_NE(std::nullopt, timings);
    if(timings) {
        EXPECT_TRUE((*timings).satisfiedInvariant(carl::Interval<T>(1,2)));
    }
}
