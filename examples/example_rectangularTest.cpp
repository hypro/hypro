/*
 * Copyright (c) 2023-2024.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/**
 * This is an example on how to perform synchronizing reachability analysis on rectangular automata.
 */

#include "hypro/datastructures/reachability/ReachTreev2Util.h"
#include "hypro/datastructures/HybridAutomaton/HybridAutomaton.h"
#include "hypro/representations/GeometricObjectBase.h"
#include <hypro/algorithms/reachability/analyzer/LabelSynchronization/RectangularSyncAnalyzer.h>
#include "hypro/algorithms/reachability/Reach.h"
#include "hypro/parser/antlr4-flowstar/ParserWrapper.h"
#include "hypro/util/plotting/Plotter.h"
#include "hypro/util/statistics/statistics.h"
#include <hypro/util/VariablePool.h>

#include <iostream>

// typedefs
using Number = mpq_class;
using Representation = hypro::HPolytope<Number>;
using State = hypro::State<Number, Representation>;
using Matrix = hypro::matrix_t<Number>;
using Vector = hypro::vector_t<Number>;
using VPoly = hypro::VPolytope<Number>;
using Interval = carl::Interval<Number>;
using Point = hypro::Point<Number>;

template <typename Number>
hypro::HybridAutomaton<Number> createRectangularHA() {
	// One-dimensional reactangular automaton with one location and a loop
	hypro::HybridAutomaton<Number> res;

	// Create location
	auto loc = res.createLocation();

	// Set flow x' = [1,1]
	Interval flow{ 1, 1 };
	typename hypro::rectangularFlow<Number>::flowMap fMap;
	fMap[hypro::VariablePool::getInstance().carlVarByIndex( 0 )] = flow;
	loc->setFlow( { hypro::rectangularFlow<Number>{ fMap } } );

	// Set invariant x <= 10
	Matrix invariantConstraints = Matrix::Zero( 1, 1 );
	invariantConstraints( 0, 0 ) = 1;
	Vector invariantConstants = Vector::Zero( 1 );
	invariantConstants( 0 ) = 10;
	loc->setInvariant( { invariantConstraints, invariantConstants } );

	// Add loop transition in first location
	auto transition = loc->createTransition( loc );
    transition->addLabel( hypro::Label{"a"} );
    // add guard x in [3,5]
    hypro::matrix_t<Number> guardConstraints = hypro::matrix_t<Number>(2, 1);
    guardConstraints << 1, -1;
    hypro::vector_t<Number> guardConstants = hypro::vector_t<Number>(2);
    guardConstants << 5, -3;
    hypro::Condition<Number> guard(guardConstraints, guardConstants);

    // add reset function x' := 0
    // interval representation
    std::vector<carl::Interval<Number>> intervalReset;
    intervalReset.emplace_back( carl::Interval<Number>( 0, 0 ) );
    hypro::Reset<Number> reset;
    reset.setIntervals( intervalReset );

    transition->setGuard( guard );
    transition->setReset( reset );

	// Set initial state x = [0,1], aff = 1
	Matrix initialConstraints = Matrix::Zero( 2, 1 );
	Vector initialConstants = Vector::Zero( 2 );
	initialConstraints << 1, -1;
	initialConstants << 1, 0;

	// Create HA
	res.addInitialState( loc, hypro::Condition<Number>( initialConstraints, initialConstants ) );

	return res;
}

template <typename Number>
hypro::HybridAutomaton<Number> createRectangularHA1() {
	// One-dimensional reactangular automaton with one location and a loop
	hypro::HybridAutomaton<Number> res;

	// Create location
	auto loc = res.createLocation();

	// Set flow x' = [1,1]
	Interval flow{ 1, 1 };
	typename hypro::rectangularFlow<Number>::flowMap fMap;
	fMap[hypro::VariablePool::getInstance().carlVarByIndex( 0 )] = flow;
	loc->setFlow( { hypro::rectangularFlow<Number>{ fMap } } );

	// Set invariant x <= 20
	Matrix invariantConstraints = Matrix::Zero( 1, 1 );
	invariantConstraints( 0, 0 ) = 1;
	Vector invariantConstants = Vector::Zero( 1 );
	invariantConstants( 0 ) = 20;
	loc->setInvariant( { invariantConstraints, invariantConstants } );

	// Add loop transition in first location
	auto transition = loc->createTransition( loc );
    transition->addLabel( hypro::Label{"a"} );
    
    // add guard x in [14,16]
    hypro::matrix_t<Number> guardConstraints = hypro::matrix_t<Number>(2, 1);
    guardConstraints << 1, -1;
    hypro::vector_t<Number> guardConstants = hypro::vector_t<Number>(2);
    guardConstants << 16, -14;
    hypro::Condition<Number> guard(guardConstraints, guardConstants);

    // reset function x' := 10
    // interval representation
    std::vector<carl::Interval<Number>> intervalReset;
    intervalReset.emplace_back( carl::Interval<Number>( 10, 10 ) );
    hypro::Reset<Number> reset;
    reset.setIntervals( intervalReset );

    transition->setGuard( guard );
    transition->setReset( reset );

	// Set initial state x = [10,11], aff = 1
	Matrix initialConstraints = Matrix::Zero( 2, 1 );
	Vector initialConstants = Vector::Zero( 2 );
	initialConstraints << 1, -1;
	initialConstants << 11, -10;

	// Create HA
	res.addInitialState( loc, hypro::Condition<Number>( initialConstraints, initialConstants ) );

	return res;
}

int main(int argc, char **argv) {
    using clock = std::chrono::high_resolution_clock;
    using timeunit = std::chrono::microseconds;

    // create first automaton with variable pool 0
    auto automaton1 = createRectangularHA<Number>();
	automaton1.addTimeVariable();
	// create second automaton with variable pool 1
	hypro::VariablePool::getInstance().changeToPool(1);
    auto automaton2 = createRectangularHA1<Number>();
	automaton2.addTimeVariable();
	// change back to pool 0
	hypro::VariablePool::getInstance().changeToPool(0);

	std::vector<hypro::HybridAutomaton<Number>> automata{ automaton1, automaton2 };

    hypro::AnalysisParameters analysisParameters;
    analysisParameters.timeStep = hypro::tNumber( 1 ) / hypro::tNumber( 100 );
    analysisParameters.aggregation = hypro::AGG_SETTING::NO_AGG;
    analysisParameters.representation_type = hypro::representation_name::polytope_v;

    hypro::Settings settings{ {},
                              hypro::FixedAnalysisParameters{ 1, hypro::tNumber( 9 ), hypro::tNumber( 0.01 ) },
                              { analysisParameters } };

    auto analyzer = hypro::RectangularSyncAnalyzer<Representation, hypro::HybridAutomaton<Number>>( automata, settings );

    auto result = analyzer.run();
    
    if (result == hypro::REACHABILITY_RESULT::UNKNOWN) {
        std::cout << "Could not verify safety." << std::endl;
    } else {
        std::cout << "The model is safe." << std::endl;
    }
    std::cout << std::endl;

    clock::time_point startPlotting = clock::now();

    for (size_t i = 0; i < automata.size(); ++i) {
        auto &plotter = hypro::Plotter<Number>::getInstance();
        plotter.clear();
        std::string extendedFilename = "testAutomatonSync" + std::to_string(i);
        switch (Representation::type()) {
            case hypro::representation_name::polytope_v: {
                extendedFilename += "_vpoly";
                break;
            }
            case hypro::representation_name::polytope_h: {
                extendedFilename += "_hpoly";
                break;
            }
            default:
                extendedFilename += "_unknownRep";
        }
        std::cout << "filename is " << extendedFilename << std::endl;
        plotter.setFilename(extendedFilename);
        // std::vector<std::size_t> plottingDimensions =
        //         settings[i].plotting().plotDimensions.at(0);
        // plotter.rSettings().dimensions.push_back(plottingDimensions.front());
        // plotter.rSettings().dimensions.push_back(plottingDimensions.back());
        plotter.rSettings().cummulative = false;
        
        // // bad states plotting
        // typename hypro::HybridAutomaton<Number>::locationConditionMap
        //         badStateMapping = automata[i].getLocalBadStates();
        // for (const auto &state: badStateMapping) {
        //     auto matrix = state.second.getMatrix(0);
        //     auto vector = state.second.getVector(0);
        //     unsigned bs = plotter.addObject(
        //             Representation(matrix, vector).vertices(),
        //             hypro::plotting::colors[hypro::plotting::red]);
        // }

        unsigned cnt = 0;
        // segments plotting
        // auto flowpipes = getFlowpipes(roots);
        auto flowpipes = getFlowpipes( analyzer.getReachTreeForAutomaton(automata[i]).front() );
        for (const auto &flowpipe: flowpipes) {
            std::cout << "Flowpipe size " << flowpipe.size() << std::endl;
            for (const auto &segment: flowpipe) {
                plotter.addObject(segment.vertices(), hypro::plotting::colors[cnt % 10]);
            }
            ++cnt;
        }
    
        PRINT_STATS()

        std::cout << "Write to file." << std::endl;

        plotter.plot2d(hypro::PLOTTYPE::pdf, true);

        std::cout << "Finished plotting: "
                << std::chrono::duration_cast<timeunit>(clock::now() -
                                                        startPlotting)
                            .count() /
                    1000.0
                << " ms" << std::endl;
    }

    return 0;
}
