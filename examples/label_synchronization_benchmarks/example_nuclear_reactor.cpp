/*
 * Copyright (c) 2023-2024.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/**
 * This is an example of the benchmark Nuclear Reactor System with synchronizing reachability analysis on rectangular automata.
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
// using Number = double;
using Number = mpq_class;
// using Representation = hypro::HPolytope<Number>;
using Representation = hypro::VPolytope<Number>;
using State = hypro::State<Number, Representation>;
using Matrix = hypro::matrix_t<Number>;
using Vector = hypro::vector_t<Number>;
using VPoly = hypro::VPolytope<Number>;
using Interval = carl::Interval<Number>;
using Point = hypro::Point<Number>;

template <typename Number>
hypro::HybridAutomaton<Number> createRodAutomaton(int rodNumber) {
	// One-dimensional reactangular automaton
	hypro::HybridAutomaton<Number> res;

    // variables
    carl::Variable x = hypro::VariablePool::getInstance().carlVarByIndex(0);
	
    // rectangular dynamics
    std::map<carl::Variable, carl::Interval<Number>> dynamics;
    dynamics.emplace(std::make_pair(x, carl::Interval<Number>(0.9, 1.1)));
    hypro::rectangularFlow<Number> flow(dynamics);

    // Create locations
	auto locOut = res.createLocation("out");
	auto locIn = res.createLocation("in");
	auto locRecover = res.createLocation("recover");
    
    // add flows
	locOut->setRectangularFlow(flow);
	locIn->setRectangularFlow(flow);
	locRecover->setRectangularFlow(flow);

    // add invariants
    // locIn x<=10000
	Matrix invariantConstraints = Matrix::Zero( 1, 1 );
	invariantConstraints( 0, 0 ) = 1;
	Vector invariantConstants = Vector::Zero( 1 );
	invariantConstants( 0 ) = 10000;
	locIn->setInvariant( { invariantConstraints, invariantConstants } );
	// locOut x<=10000
    locOut->setInvariant( { invariantConstraints, invariantConstants } );
	// locRecover x<=10000
    locRecover->setInvariant( { invariantConstraints, invariantConstants } );
    
    // transitions
    // locOut -> locIn
    auto transitionOutIn = locOut->createTransition( locIn );
    std::string add_i = "add_" + std::to_string(rodNumber);
    transitionOutIn->addLabel( hypro::Label{ add_i } );
    // guard x >= 1
    hypro::matrix_t<Number> guardConstraintsOutIn = hypro::matrix_t<Number>(1, 1);
    guardConstraintsOutIn << -1;
    hypro::vector_t<Number> guardConstantsOutIn = hypro::vector_t<Number>(1);
    guardConstantsOutIn << -1;
    hypro::Condition<Number> guardOutIn(guardConstraintsOutIn, guardConstantsOutIn);
    transitionOutIn->setGuard( guardOutIn );
    // reset x in [0, 0]
    std::vector<carl::Interval<Number>> intervalReset;
    intervalReset.emplace_back( carl::Interval<Number>( 0, 0 ) );
    hypro::Reset<Number> reset;
    reset.setIntervals( intervalReset );
    transitionOutIn->setReset( reset );

    // locIn -> locRecover
    auto transitionInRecover = locIn->createTransition( locRecover );
    std::string remove_i = "remove_" + std::to_string(rodNumber);
    transitionInRecover->addLabel( hypro::Label{ remove_i } );
    // reset x in [0, 0]
    transitionInRecover->setReset( reset );

    // locRecover -> locOut
    auto transitionRecoverOut = locRecover->createTransition( locOut );
    std::string recovery_i = "recovery_" + std::to_string(rodNumber);
    transitionRecoverOut->addLabel( hypro::Label{ recovery_i } );

	// Set initial state x = [0,0]
	Matrix initialConstraints = Matrix::Zero( 2, 1 );
	Vector initialConstants = Vector::Zero( 2 );
	initialConstraints << 1, -1;
	initialConstants << 0, 0;

	// Create HA
	res.addInitialState( locOut, hypro::Condition<Number>( initialConstraints, initialConstants ) );

	return res;
}


template <typename Number>
hypro::HybridAutomaton<Number> createControllerAutomaton(int numberOfRods) {
    assert(numberOfRods > 0);

    // One-dimensional reactangular automaton
	hypro::HybridAutomaton<Number> res;

    // variables
    carl::Variable x = hypro::VariablePool::getInstance().carlVarByIndex(0);

    // rectangular dynamics
    std::map<carl::Variable, carl::Interval<Number>> dynamics;
    dynamics.emplace(std::make_pair(x, carl::Interval<Number>(0.9, 1.1)));
    hypro::rectangularFlow<Number> flow(dynamics);

    // Create numberOfRods+1 locations
    std::vector<hypro::Location<Number> *> locs{};
    for (int i = 0; i <= numberOfRods; ++i) {
        std::string locName = "rod_" + std::to_string(i);
        locs.push_back( res.createLocation(locName) );
        locs[i]->setRectangularFlow(flow);

        // add invariants
        if(i==0) {
            // locs[0] x<=16.1
            Matrix invariantConstraints = Matrix::Zero( 1, 1 );
            invariantConstraints( 0, 0 ) = 1;
            Vector invariantConstants = Vector::Zero( 1 );
            invariantConstants( 0 ) = 16.1;
            locs[i]->setInvariant( { invariantConstraints, invariantConstants } );            
        } else {
            // locs[i] x<=5.9
            Matrix invariantConstraints = Matrix::Zero( 1, 1 );
            invariantConstraints( 0, 0 ) = 1;
            Vector invariantConstants = Vector::Zero( 1 );
            invariantConstants( 0 ) = 5.9;
            locs[i]->setInvariant( { invariantConstraints, invariantConstants } );
        }
    }
    
    // transitions
    for (int i = 1; i <= numberOfRods; ++i)
    {
        // add_i
        auto transitionAddi = locs[0]->createTransition( locs[i] );
        std::string add_i = "add_" + std::to_string(i);
        transitionAddi->addLabel( hypro::Label{ add_i } );
        // guard x in [16,16.1]
        hypro::matrix_t<Number> guardConstraintsAddi = hypro::matrix_t<Number>(2, 1);
        guardConstraintsAddi << 1, -1;
        hypro::vector_t<Number> guardConstantsAddi = hypro::vector_t<Number>(2);
        guardConstantsAddi << 16.1, -16;
        hypro::Condition<Number> guardAddi(guardConstraintsAddi, guardConstantsAddi);
        transitionAddi->setGuard( guardAddi );
        // reset x in [0, 0]
        std::vector<carl::Interval<Number>> intervalReset;
        intervalReset.emplace_back( carl::Interval<Number>( 0, 0 ) );
        hypro::Reset<Number> reset;
        reset.setIntervals( intervalReset );
        transitionAddi->setReset( reset );
        
        // remove_i
        auto transitionRemovei = locs[i]->createTransition( locs[0] );
        std::string remove_i = "remove_" + std::to_string(i);
        transitionRemovei->addLabel( hypro::Label{ remove_i } );
        // guard x in [5,5.9]
        hypro::matrix_t<Number> guardConstraintsRemovei = hypro::matrix_t<Number>(2, 1);
        guardConstraintsRemovei << 1, -1;
        hypro::vector_t<Number> guardConstantsRemovei = hypro::vector_t<Number>(2);
        guardConstantsRemovei << 5.9, -5;
        hypro::Condition<Number> guardRemovei(guardConstraintsRemovei, guardConstantsRemovei);
        transitionRemovei->setGuard( guardRemovei );
        // reset x in [0, 0]
        transitionRemovei->setReset( reset );
    }
    
    // Set initial state x = [0,0]
    Matrix initialConstraints = Matrix::Zero( 2, 1 );
    Vector initialConstants = Vector::Zero( 2 );
    initialConstraints << 1, -1;
    initialConstants << 0, 0;

    // Create HA
    res.addInitialState( locs[0], hypro::Condition<Number>( initialConstraints, initialConstants ) );

    return res;
}


int main(int argc, char **argv) {
    using clock = std::chrono::high_resolution_clock;
    using timeunit = std::chrono::microseconds;

    int numberOfRods = 5;

    // // create controller automaton
    // hypro::VariablePool::getInstance().changeToPool(0);
    // auto controllerAutomaton = createControllerAutomaton<Number>(numberOfRods);
    // controllerAutomaton.addTimeVariable();
    // automata.push_back(controllerAutomaton);

    // // create rod automata
    // for (int i = 1; i <= numberOfRods; ++i)
    // {
    //     hypro::VariablePool::getInstance().changeToPool(i);
    //     auto rodAutomaton = createRodAutomaton<Number>(i);
    //     rodAutomaton.addTimeVariable();
    //     automata.push_back( rodAutomaton );
    // }

    std::vector<hypro::HybridAutomaton<Number>> rods{};
    for (int i = 0; i < numberOfRods; ++i)
    {
        hypro::VariablePool::getInstance().changeToPool(i);
        rods.push_back( createRodAutomaton<Number>(i+1) );
        rods[i].addTimeVariable();
    }

    hypro::VariablePool::getInstance().changeToPool(numberOfRods);
    auto controllerAutomaton = createControllerAutomaton<Number>(numberOfRods);
    controllerAutomaton.addTimeVariable();
    
    // change back to pool 0
	hypro::VariablePool::getInstance().changeToPool(0);

    std::vector<hypro::HybridAutomaton<Number>> automata{ rods };
    automata.push_back( controllerAutomaton );


    hypro::AnalysisParameters analysisParameters;
    analysisParameters.timeStep = hypro::tNumber( 1 ) / hypro::tNumber( 100 );
    analysisParameters.aggregation = hypro::AGG_SETTING::NO_AGG;
    analysisParameters.representation_type = hypro::representation_name::polytope_v;

    hypro::Settings settings{ {},
                              hypro::FixedAnalysisParameters{  10 , hypro::tNumber( 20 ), hypro::tNumber( 1 ) },
                              { analysisParameters } };

    clock::time_point startAnalyzing = clock::now();

    auto analyzer = hypro::RectangularSyncAnalyzer<Representation, hypro::HybridAutomaton<Number>>( automata, settings );

    auto result = analyzer.run();
    
    if (result == hypro::REACHABILITY_RESULT::UNKNOWN) {
        std::cout << "Could not verify safety." << std::endl;
    } else {
        std::cout << "The model is safe." << std::endl;
    }
    std::cout << std::endl;

    std::cout << "Finished reachability Analysis: "
                << std::chrono::duration_cast<timeunit>(clock::now() -
                                                        startAnalyzing)
                            .count() /
                    1000.0
                << " ms" << std::endl;

    clock::time_point startPlotting = clock::now();

    for (size_t i = 0; i < automata.size(); ++i) {
        auto &plotter = hypro::Plotter<Number>::getInstance();
        plotter.clear();
        std::string extendedFilename = "NR_unknown_automaton";
        if(i==numberOfRods) {
            extendedFilename = "NR_controller";
        } else {
            extendedFilename = "NR_rod_" + std::to_string(i+1);
        }

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
        std::vector<std::size_t> plottingDimensions = std::vector<std::size_t>{0, 1};
        plotter.rSettings().dimensions.push_back(plottingDimensions.front());
        plotter.rSettings().dimensions.push_back(plottingDimensions.back());
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
                // std::cout << "projected Segment: " << segment.projectOn(plottingDimensions) << std::endl;
                plotter.addObject(segment.projectOn(plottingDimensions).vertices(), hypro::plotting::colors[cnt % 10]);
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