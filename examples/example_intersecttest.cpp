/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include <hypro/representations/GeometricObjectBase.h>
#include <hypro/algorithms/quickhull/Quickhull.h>
#include <hypro/algorithms/convexHull/ConvexHull.h>
#include <cassert>
#include <hypro/algorithms/reachability/Reach.h>
#include <hypro/datastructures/HybridAutomaton/HybridAutomaton.h>
#include <hypro/datastructures/reachability/TreeUtil.h>

int main() {

    /**
     * generating two boxes and intersecting them once using the satisfiesHalfspaces method and once the intersect method
    * the second box has an open interval bound -> satisfiesHalfspaces returns an empty box because of multiplication with empty interval
    *                                           -> intersect returns the expected box
    *  also comparing both methods with boxes without open bounds -> result is the same
    */

    // use rational arithmetic.
    typedef mpq_class Number;

    // create a box out of two given limit points.
    hypro::Box<Number> testbox(std::make_pair(hypro::Point<Number>({70, 100}),
                                              hypro::Point<Number>(
                                                      {Number(230) / Number(2), Number(211) / Number(2)})));
    std::vector<carl::Interval<Number>> intervals = testbox.intervals();
    hypro::setLowerBoundType(intervals.at(1), carl::BoundType::STRICT);
    hypro::Box<Number> testbox2(intervals);
    std::cout << "testbox without open bound: " << testbox << std::endl;
    std::cout << "testbox with open bound: " << testbox2 << std::endl;
    //hypro::Box<Number> minusbox(std::make_pair(hypro::Point<Number>({30, 100}),
    //                                        hypro::Point<Number>({70, 150})));

    // create location north_west
    std::unique_ptr<hypro::Location<Number>> l0{
            std::make_unique<hypro::Location<Number>>(hypro::Location<Number>{"l0"})};
    // create flow
    hypro::matrix_t<Number> flow_north_west = hypro::matrix_t<Number>(3, 3);
    flow_north_west << 0, 0, -10, 0, 0, 9, 0, 0, 0;

    hypro::Transition<hypro::Location<Number>> trans{l0.get(), l0.get()};
    hypro::matrix_t<Number> urgent_guard_mat = hypro::matrix_t<Number>(4, 2);
    urgent_guard_mat << -1, 0, 1, 0, 0, -1, 0, 1;
    hypro::vector_t<Number> urgent_guard_off = hypro::vector_t<Number>(4);
    urgent_guard_off << -30, 70, -100, 150;
    // assign guard to transition
    hypro::Condition<Number> condition(urgent_guard_mat, urgent_guard_off);
    trans.setGuard(condition);
    trans.setAggregation(hypro::AGG_SETTING::AGG);
    trans.setUrgent();
    l0->addTransition(std::make_unique<hypro::Transition<hypro::Location<Number>>>(trans));

    if (condition.isTrue()) {
        std::cout << "true" << std::endl;
    }
    if (condition.isFalse()) {
        std::cout << "false" << std::endl;
    }
    assert(testbox.dimension() == condition.dimension());

    hypro::Box<Number> minusbox(trans.getGuard().getMatrix(), trans.getGuard().getVector());
    std::cout << "minusbox: " << minusbox << std::endl;

    auto [con, inter] = testbox.satisfiesHalfspaces(condition.getMatrix(), condition.getVector());
    auto [containment, intersected] = testbox.satisfiesHalfspaces(trans.getGuard().getMatrix(),
                                                                  trans.getGuard().getVector());
    hypro::Box<Number> intersect(testbox.intersect(minusbox));

    std::cout << "no open bounds: " << std::endl;
    std::cout << "satisfiedHalfspaces mit condition: " << inter << std::endl;
    std::cout << "satisfiedHalfspaces mit transition: " << intersected << std::endl;
    std::cout << "intersect: " << intersect << std::endl;

    std::cout << "-------------" << std::endl;
    std::cout << "open bound: " << std::endl;

    auto [con2, inter2] = testbox2.satisfiesHalfspaces(condition.getMatrix(), condition.getVector());
    auto [containment2, intersected2] = testbox2.satisfiesHalfspaces(trans.getGuard().getMatrix(),
                                                                     trans.getGuard().getVector());
    hypro::Box<Number> intersect2(testbox2.intersect(minusbox));

    std::cout << "satisfiedHalfspaces mit condition: " << inter2 << std::endl;
    std::cout << "satisfiedHalfspaces mit transition: " << intersected2 << std::endl;
    std::cout << "intersect: " << intersect2 << std::endl;

    return 0;
}
