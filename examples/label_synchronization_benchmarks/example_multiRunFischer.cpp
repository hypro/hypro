/*
 * Copyright (c) 2023-2024.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/**
 * This example is to derive the runtimes of the benchmark Fischer's Mutual Execlusion with synchronizing reachability analysis on rectangular automata.
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
// using Representation = hypro::VPolytope<Number>;
using State = hypro::State<Number, Representation>;
using Matrix = hypro::matrix_t<Number>;
using Vector = hypro::vector_t<Number>;
using VPoly = hypro::VPolytope<Number>;
using Interval = carl::Interval<Number>;
using Point = hypro::Point<Number>;
using timeunit = std::chrono::microseconds;

template <typename Number>
hypro::HybridAutomaton<Number> createProcessAutomaton(int processNumber, Number a, Number b) {
	// One-dimensional reactangular automaton
	hypro::HybridAutomaton<Number> res;

    // variables
    carl::Variable x = hypro::VariablePool::getInstance().carlVarByIndex(0);
	
    // rectangular dynamics
    std::map<carl::Variable, carl::Interval<Number>> dynamics;
    dynamics.emplace(std::make_pair(x, carl::Interval<Number>(1.1, 2.3)));
    hypro::rectangularFlow<Number> flow(dynamics);

    // Create locations
	auto locS1 = res.createLocation("S1");
	auto locS2 = res.createLocation("S2");
	auto locS3 = res.createLocation("S3");
	auto locS4 = res.createLocation("S4");
    
    // add flows
	locS1->setRectangularFlow(flow);
	locS2->setRectangularFlow(flow);
	locS3->setRectangularFlow(flow);
	locS4->setRectangularFlow(flow);

    // add invariants
    // locS2 x<=a
	Matrix invariantConstraints = Matrix::Zero( 1, 1 );
	invariantConstraints( 0, 0 ) = 1;
	Vector invariantConstants = Vector::Zero( 1 );
	invariantConstants( 0 ) = a;
	locS2->setInvariant( { invariantConstraints, invariantConstants } );
    
    // transitions
    // locS1 -> locS2
    auto transition12 = locS1->createTransition( locS2 );
    std::string test_0_i = "test_0_" + std::to_string(processNumber);
    transition12->addLabel( hypro::Label{ test_0_i } );
    // reset x in [0, 0]
    std::vector<carl::Interval<Number>> intervalReset;
    intervalReset.emplace_back( carl::Interval<Number>( 0, 0 ) );
    hypro::Reset<Number> reset;
    reset.setIntervals( intervalReset );
    transition12->setReset( reset );

    // locS4 -> locS1
    auto transition41 = locS4->createTransition( locS1 );
    std::string set_0_i = "set_0_" + std::to_string(processNumber);
    transition41->addLabel( hypro::Label{ set_0_i } );

    // locS2 -> locS3
    auto transition23 = locS2->createTransition( locS3 );
    std::string set_i_i = "set_" + std::to_string(processNumber) + "_" + std::to_string(processNumber);
    transition23->addLabel( hypro::Label{ set_i_i } );
    // reset x in [0, 0]
    transition23->setReset( reset );

    // locS3->locS1
    auto transition31 = locS3->createTransition( locS1 );
    std::string test_not_i_i = "test_not_" + std::to_string(processNumber) + "_" + std::to_string(processNumber);
    transition31->addLabel( hypro::Label{ test_not_i_i } );
    // guard x in [b, inf]
    hypro::matrix_t<Number> guardConstraints31 = hypro::matrix_t<Number>(1, 1);
    guardConstraints31 << -1;
    hypro::vector_t<Number> guardConstants31 = hypro::vector_t<Number>(1);
    guardConstants31 << -b;
    hypro::Condition<Number> guard31(guardConstraints31, guardConstants31);
    transition31->setGuard( guard31 );

    // locS3->locS4
    auto transition34 = locS3->createTransition( locS4 );
    std::string test_i_i = "test_" + std::to_string(processNumber) + "_" + std::to_string(processNumber);
    transition34->addLabel( hypro::Label{ test_i_i } );
    // guard x in [b, inf]
    hypro::matrix_t<Number> guardConstraints34 = hypro::matrix_t<Number>(1, 1);
    guardConstraints34 << -1;
    hypro::vector_t<Number> guardConstants34 = hypro::vector_t<Number>(1);
    guardConstants34 << -b;
    hypro::Condition<Number> guard34(guardConstraints34, guardConstants34);
    transition34->setGuard( guard34 );

	// Set initial state x = [0,0]
	Matrix initialConstraints = Matrix::Zero( 2, 1 );
	Vector initialConstants = Vector::Zero( 2 );
	initialConstraints << 1, -1;
	initialConstants << 0, 0;

	// Create HA
	res.addInitialState( locS1, hypro::Condition<Number>( initialConstraints, initialConstants ) );

	return res;
}


template <typename Number>
hypro::HybridAutomaton<Number> createSharedVariableAutomaton(int processNumber) {
	// One-dimensional reactangular automaton
	hypro::HybridAutomaton<Number> res;

    // variables
    carl::Variable x = hypro::VariablePool::getInstance().carlVarByIndex(0);

    // rectangular dynamics
    std::map<carl::Variable, carl::Interval<Number>> dynamics;
    dynamics.emplace(std::make_pair(x, carl::Interval<Number>(1, 1)));
    hypro::rectangularFlow<Number> flow(dynamics);

    // Create locations
    std::vector<hypro::Location<Number> *> locs{};
    for (int i = 0; i <= processNumber; ++i) {
        std::string locName = "loc" + std::to_string(i);
        locs.push_back( res.createLocation(locName) );
        locs[i]->setRectangularFlow(flow);
    }
    
    // transitions
    for (int i = 1; i <= processNumber; ++i)
    {
        // set_0_i
        auto transitionSet0i = locs[0]->createTransition( locs[0] );
        std::string set_0_i = "set_0_" + std::to_string(i);
        transitionSet0i->addLabel( hypro::Label{ set_0_i } );
        // test_0_i
        auto transitionTest0i = locs[0]->createTransition( locs[0] );
        std::string test_0_i = "test_0_" + std::to_string(i);
        transitionTest0i->addLabel( hypro::Label{ test_0_i } );

        // set_i_i
        auto transitionSetii = locs[0]->createTransition( locs[i] );
        std::string set_i_i = "set_" + std::to_string(i) + "_" + std::to_string(i);
        transitionSetii->addLabel( hypro::Label{ set_i_i } );

        // set_0_i
        auto transitionSet0iFromi = locs[i]->createTransition( locs[0] );
        // std::string set_0_i = "set_0_" + std::to_string(i);
        transitionSet0iFromi->addLabel( hypro::Label{ set_0_i } );

        // test_i_i
        auto transitionTestii = locs[i]->createTransition( locs[i] );
        std::string test_i_i = "test_" + std::to_string(i) + "_" + std::to_string(i);
        transitionTestii->addLabel( hypro::Label{ test_i_i } );

        for (int j = 1; j <= processNumber; ++j)
        {
            if (i != j)
            {
                // test_not_j_j
                auto transitionTestnotjj = locs[i]->createTransition( locs[i] );
                std::string test_not_j_j = "test_not_" + std::to_string(j) + "_" + std::to_string(j);
                transitionTestnotjj->addLabel( hypro::Label{ test_not_j_j } );
                // set_j_j
                auto transitionSetjj = locs[i]->createTransition( locs[j] );
                std::string set_j_j = "set_" + std::to_string(j) + "_" + std::to_string(j);
                transitionSetjj->addLabel( hypro::Label{ set_j_j } );
            }
        }
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

static void displayRuntime(const std::vector<timeunit> &runtimes) {
    double sum = 0;
    double min = 0;
    double max = 0;
    for (auto runtime : runtimes) {
        std::cout << runtime.count()/1000.0 << ", ";
        if (runtime.count() < min || min == 0) {
            min = runtime.count();
        }
        if (runtime.count() > max) {
            max = runtime.count();
        }
        sum += runtime.count();
    }
    std::cout << std::endl;
    double average = sum / runtimes.size();
    std::cout << "Average runtime: " << average / 1000.0 << " ms" << std::endl;
    std::cout << "Max runtime: " << max / 1000.0 << " ms" << std::endl;
    std::cout << "Min runtime: " << min / 1000.0 << " ms" << std::endl;

    // print standard deviation
    double variance = 0;
    for (auto runtime : runtimes) {
        variance += pow(runtime.count() - average, 2);
    }
    variance /= runtimes.size();
    double standardDeviation = sqrt(variance);
    std::cout << "Standard deviation: " << standardDeviation / 1000.0 << " ms" << std::endl;
}

int main(int argc, char **argv) {
    using clock = std::chrono::high_resolution_clock;
    using timeunit = std::chrono::microseconds;

    int numberOfProcesses = 3;

    // create 3 process automata and a shared variable automaton
    std::vector<hypro::HybridAutomaton<Number>> processes{};
    for (int i = 0; i < numberOfProcesses; ++i)
    {
        hypro::VariablePool::getInstance().changeToPool(i);
        processes.push_back( createProcessAutomaton<Number>(i+1, 8, 12) );
        processes[i].addTimeVariable();
    }
    hypro::VariablePool::getInstance().changeToPool(numberOfProcesses);
    auto sharedVariableAutomaton = createSharedVariableAutomaton<Number>(numberOfProcesses);
    sharedVariableAutomaton.addTimeVariable();
    
    // change back to pool 0
	hypro::VariablePool::getInstance().changeToPool(0);

	std::vector<hypro::HybridAutomaton<Number>> automata{ processes };
    automata.push_back(sharedVariableAutomaton);

    hypro::AnalysisParameters analysisParameters;
    analysisParameters.timeStep = hypro::tNumber( 1 ) / hypro::tNumber( 100 );
    analysisParameters.aggregation = hypro::AGG_SETTING::NO_AGG;
    analysisParameters.representation_type = hypro::representation_name::polytope_v;

    hypro::Settings settings{ {},
                              hypro::FixedAnalysisParameters{  10 , hypro::tNumber( 30 ), hypro::tNumber( 1 ) },
                              { analysisParameters } };

    std::vector<timeunit> runtimes;
    int number_iterations = 20;

    for(int iteration = 0; iteration < number_iterations; iteration++) {
         
        clock::time_point start = clock::now();
        
        auto analyzer = hypro::RectangularSyncAnalyzer<Representation, hypro::HybridAutomaton<Number>>( automata, settings );
        auto result = analyzer.run();
        
        runtimes.push_back(std::chrono::duration_cast<timeunit>(clock::now() - start));
    }

    std::cout << "Statistic: Fischer's Protocol" << std::endl;
    
    displayRuntime(runtimes);

    return 0;
}
