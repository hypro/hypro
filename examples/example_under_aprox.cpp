/*
 * Copyright (c) 2023-2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/**
 * This is an example on how to set up a rudimentary reachability analysis method.
 */

#include "hypro/algorithms/reachability/Reach.h"
#include "hypro/datastructures/HybridAutomaton/HybridAutomaton.h"
#include "hypro/datastructures/reachability/ReachTreev2Util.h"
#include "hypro/parser/antlr4-flowstar/ParserWrapper.h"
#include "hypro/representations/GeometricObjectBase.h"
#include "hypro/util/plotting/Plotter.h"
#include "hypro/util/statistics/statistics.h"

using Number = mpq_class;
using Interval = carl::Interval<Number>;

int main() {
    auto &plotter = hypro::Plotter<Number>::getInstance();

    // typename hypro::VPolytope<Number>::pointVector points;
    // points.push_back(hypro::Point<Number>({-3, 8}));
    // points.push_back(hypro::Point<Number>({-5, 4}));
    // points.push_back(hypro::Point<Number>({3, 4}));
    // hypro::VPolytope<Number> vpoly1 = hypro::VPolytope<Number>(points);


    // std::vector<Interval> intervals;
    // intervals.push_back(Interval(-0.1, 0.2));
    // intervals.push_back(Interval(-0.1, 0.2));
    // hypro::Box<Number> bloatBox{intervals};

    //////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////


    typename hypro::VPolytope<Number>::pointVector points;
    points.push_back(hypro::Point<Number>({1, 4}));
    points.push_back(hypro::Point<Number>({1, 2}));
    points.push_back(hypro::Point<Number>({3, 2}));
    points.push_back(hypro::Point<Number>({3, 4}));
    hypro::VPolytope<Number> vpoly1 = hypro::VPolytope<Number>(points);


    std::vector<Interval> intervals;
    intervals.push_back(Interval(3, 4));
    intervals.push_back(Interval(5, 6));
    hypro::Box<Number> bloatBox{intervals};

    //////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////

    // typename hypro::VPolytope<Number>::pointVector points;
    // points.push_back(hypro::Point<Number>({-5, 5}));
    // points.push_back(hypro::Point<Number>({3, 8}));
    // points.push_back(hypro::Point<Number>({7, 3}));
    // points.push_back(hypro::Point<Number>({1, -4}));
    // points.push_back(hypro::Point<Number>({-6, -3}));

    // hypro::VPolytope<Number> vpoly1 = hypro::VPolytope<Number>(points);


    // std::vector<Interval> intervals;
    // intervals.push_back(Interval(-0.1, 0.2));
    // intervals.push_back(Interval(-0.1, 0.2));
    // hypro::Box<Number> bloatBox{intervals};


    hypro::HPolytope<Number> stateSetH = hypro::Converter<Number>::toHPolytope(vpoly1);
    hypro::HPolytope<Number> bloatBoxH = hypro::Converter<Number>::toHPolytope(bloatBox);
    auto resultOfMinkSum = stateSetH.minkowskiSum(bloatBoxH);

    auto resultOfMinkDiff = stateSetH.minkowskiDiff(bloatBoxH);

    auto maybeOriginal = resultOfMinkSum.minkowskiDiff(bloatBoxH);


    // for (auto halfspace : stateSetH.constraints()) {
    //     hypro::HPolytope<Number> HFromOne({halfspace});

    //     for (auto halfspaceFromOne : HFromOne.minkowskiSum(bloatBoxH)) {

    //         if ()

    //     }
    // }


    plotter.setFilename("out");
    std::vector<std::size_t> plottingDimensions = {0, 1};

    plotter.rSettings().dimensions.push_back(plottingDimensions.front());
    plotter.rSettings().dimensions.push_back(plottingDimensions.back());
    plotter.rSettings().cummulative = false;


    // plotter.addObject(stateSetH.projectOn(plottingDimensions).vertices(), hypro::plotting::colors[0]);
    plotter.addObject(maybeOriginal.projectOn(plottingDimensions).vertices(), hypro::plotting::colors[0]);
    plotter.addObject(resultOfMinkSum.projectOn(plottingDimensions).vertices(), hypro::plotting::colors[1]);
    plotter.addObject(resultOfMinkDiff.projectOn(plottingDimensions).vertices(), hypro::plotting::colors[2]);


    
    
    plotter.plot2d(hypro::PLOTTYPE::pdf, false);
    
}
