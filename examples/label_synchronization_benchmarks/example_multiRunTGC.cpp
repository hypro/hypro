/*
 * Copyright (c) 2023-2024.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/**
 * This example is to derive the runtimes of the benchmark Train Gate System with synchronizing reachability analysis on rectangular automata.
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
// using Representation = hypro::HPolytope<Number>;
using Representation = hypro::VPolytope<Number>;
using State = hypro::State<Number, Representation>;
using Matrix = hypro::matrix_t<Number>;
using Vector = hypro::vector_t<Number>;
using VPoly = hypro::VPolytope<Number>;
using Interval = carl::Interval<Number>;
using Point = hypro::Point<Number>;
using timeunit = std::chrono::microseconds;

template <typename Number>
hypro::HybridAutomaton<Number> createTrainAutomaton() {
	// One-dimensional reactangular automaton
	hypro::HybridAutomaton<Number> res;

    // variables
    carl::Variable x = hypro::VariablePool::getInstance().carlVarByIndex(0);
    carl::Variable y = hypro::VariablePool::getInstance().carlVarByIndex(1);
	
    // rectangular dynamics
    std::map<carl::Variable, carl::Interval<Number>> farDynamics;
    farDynamics.emplace(std::make_pair(x, carl::Interval<Number>(-50, -40)));
    farDynamics.emplace(std::make_pair(y, carl::Interval<Number>(10, 10)));
    hypro::rectangularFlow<Number> farFlow(farDynamics);
    std::map<carl::Variable, carl::Interval<Number>> nearDynamics;
    nearDynamics.emplace(std::make_pair(x, carl::Interval<Number>(-50, -30)));
    nearDynamics.emplace(std::make_pair(y, carl::Interval<Number>(10, 10)));
    hypro::rectangularFlow<Number> nearFlow(nearDynamics);
    
    // Create locations
	auto locFar = res.createLocation("Far");
	auto locNear = res.createLocation("Near");
	auto locPast = res.createLocation("Past");
    
    // add flows
	locFar->setRectangularFlow(farFlow);
	locNear->setRectangularFlow(nearFlow);
	locPast->setRectangularFlow(nearFlow);

    // add invariants
    // locFar x>=1000
	Matrix invariantConstraints = Matrix::Zero( 1, 2 );
	invariantConstraints( 0, 0 ) = -1;
	Vector invariantConstants = Vector::Zero( 1 );
	invariantConstants( 0 ) = -1000;
	locFar->setInvariant( { invariantConstraints, invariantConstants } );
    // locNear x>=0
    Matrix invariantConstraintsNear = Matrix::Zero( 1, 2 );
    invariantConstraintsNear( 0, 0 ) = -1;
    Vector invariantConstantsNear = Vector::Zero( 1 );
    invariantConstantsNear( 0 ) = 0;
    locNear->setInvariant( { invariantConstraintsNear, invariantConstantsNear } );
    // locPast x>=-100
    Matrix invariantConstraintsPast = Matrix::Zero( 1, 2 );
    invariantConstraintsPast( 0, 0 ) = -1;
    Vector invariantConstantsPast = Vector::Zero( 1 );
    invariantConstantsPast( 0 ) = 100;
    locPast->setInvariant( { invariantConstraintsPast, invariantConstantsPast } );

    // transitions
    // locFar -> locNear
    auto transitionFarNear = locFar->createTransition( locNear );
    transitionFarNear->addLabel( hypro::Label{"approach"} );
    // guard x in [1000,1000]
    hypro::matrix_t<Number> guardConstraints = hypro::matrix_t<Number>(2, 2);
    guardConstraints << 1, 0, -1, 0;
    hypro::vector_t<Number> guardConstants = hypro::vector_t<Number>(2);
    guardConstants << 1000, -1000;
    hypro::Condition<Number> guard(guardConstraints, guardConstants);
    transitionFarNear->setGuard( guard );

    // locNear -> locPast
    auto transitionNearPast = locNear->createTransition( locPast );
    transitionNearPast->addLabel( hypro::Label{"pass"} );
    // guard x in [0,0]
    hypro::matrix_t<Number> guardConstraintsNear = hypro::matrix_t<Number>(2, 2);
    guardConstraintsNear << 1, 0, -1, 0;
    hypro::vector_t<Number> guardConstantsNear = hypro::vector_t<Number>(2);
    guardConstantsNear << 0, 0;
    hypro::Condition<Number> guardNear(guardConstraintsNear, guardConstantsNear);
    transitionNearPast->setGuard( guardNear );

    // locPast -> locFar
    auto transitionPastFar = locPast->createTransition( locFar );
    transitionPastFar->addLabel( hypro::Label{"exit"} );
    // guard x in [-100,-100]
    hypro::matrix_t<Number> guardConstraintsPast = hypro::matrix_t<Number>(2, 2);
    guardConstraintsPast << 1, 0, -1, 0;
    hypro::vector_t<Number> guardConstantsPast = hypro::vector_t<Number>(2);
    guardConstantsPast << -100, 100;
    hypro::Condition<Number> guardPast(guardConstraintsPast, guardConstantsPast);
    transitionPastFar->setGuard( guardPast );
    // reset x in [1900, 4900]
    std::vector<carl::Interval<Number>> intervalReset;
    intervalReset.emplace_back( carl::Interval<Number>( 1900, 4900 ) );
    hypro::Reset<Number> reset;
    reset.setIntervals( intervalReset );
    transitionPastFar->setReset( reset );

	// Set initial state x = [1900,5000], y = [0,0]
	Matrix initialConstraints = Matrix::Zero( 4, 2 );
	Vector initialConstants = Vector::Zero( 4 );
	initialConstraints << 1, 0, -1, 0, 0, 1, 0, -1;
	initialConstants << 5000, -1900, 0, 0;

	// Create HA
	res.addInitialState( locFar, hypro::Condition<Number>( initialConstraints, initialConstants ) );

	return res;
}

template <typename Number>
hypro::HybridAutomaton<Number> createControllerAutomaton() {
	// One-dimensional reactangular automaton
	hypro::HybridAutomaton<Number> res;

    // variables
    carl::Variable z = hypro::VariablePool::getInstance().carlVarByIndex(0);
	
    // rectangular dynamics
    std::map<carl::Variable, carl::Interval<Number>> oneDynamics;
    oneDynamics.emplace(std::make_pair(z, carl::Interval<Number>(1, 1)));
    // Flows
    hypro::rectangularFlow<Number> oneFlow(oneDynamics);
    
    // Create locations
	auto locIdle = res.createLocation("idle");
	auto locApproach = res.createLocation("approach");
	auto locExit = res.createLocation("exit");

    // add flows
	locIdle->setRectangularFlow(oneFlow);
	locApproach->setRectangularFlow(oneFlow);
	locExit->setRectangularFlow(oneFlow);

    // add invariants
    // locApproach z<=2
	Matrix invariantConstraints = Matrix::Zero( 1, 1 );
	invariantConstraints( 0, 0 ) = 1;
	Vector invariantConstants = Vector::Zero( 1 );
	invariantConstants( 0 ) = 2;
	locApproach->setInvariant( { invariantConstraints, invariantConstants } );
    // locExit z<=2
    Matrix invariantConstraintsExit = Matrix::Zero( 1, 1 );
    invariantConstraintsExit( 0, 0 ) = 1;
    Vector invariantConstantsExit = Vector::Zero( 1 );
    invariantConstantsExit( 0 ) = 2;
    locExit->setInvariant( { invariantConstraintsExit, invariantConstantsExit } );

    // transitions
    // locIdle -> locApproach
    auto transitionIdleApproach = locIdle->createTransition( locApproach );
    transitionIdleApproach->addLabel( hypro::Label{"approach"} );
    // reset z in [0,0]
    std::vector<carl::Interval<Number>> intervalReset;
    intervalReset.emplace_back( carl::Interval<Number>( 0, 0 ) );
    hypro::Reset<Number> reset;
    reset.setIntervals( intervalReset );
    transitionIdleApproach->setReset( reset );

    // locApproach -> locApproach
    auto transitionApproachApproach = locApproach->createTransition( locApproach );
    transitionApproachApproach->addLabel( hypro::Label{"approach"} );
    // locApproach -> locApproach
    auto transitionApproachApproach2 = locApproach->createTransition( locApproach );
    transitionApproachApproach2->addLabel( hypro::Label{"exit"} );

    // locApproach -> locIdle
    auto transitionApproachIdle = locApproach->createTransition( locIdle );
    transitionApproachIdle->addLabel( hypro::Label{"lower"} );

    // locIdle -> locExit
    auto transitionIdleExit = locIdle->createTransition( locExit );
    transitionIdleExit->addLabel( hypro::Label{"exit"} );
    // reset z in [0,0]
    transitionIdleExit->setReset( reset );

    // locExit -> locIdle
    auto transitionExitIdle = locExit->createTransition( locIdle );
    transitionExitIdle->addLabel( hypro::Label{"raise"} );
    // locExit -> locExit
    auto transitionExitExit = locExit->createTransition( locExit );
    transitionExitExit->addLabel( hypro::Label{"exit"} );
    // locExit -> locApproach
    auto transitionExitApproach = locExit->createTransition( locApproach );
    transitionExitApproach->addLabel( hypro::Label{"approach"} );

	// Set initial state z = [0,0]
	Matrix initialConstraints = Matrix::Zero( 2, 1 );
	Vector initialConstants = Vector::Zero( 2 );
	initialConstraints << 1, -1;
	initialConstants << 0, 0;

	// Create HA
	res.addInitialState( locIdle, hypro::Condition<Number>( initialConstraints, initialConstants ) );

	return res;
}

template <typename Number>
hypro::HybridAutomaton<Number> createGateAutomaton() {
	// One-dimensional reactangular automaton
	hypro::HybridAutomaton<Number> res;

    // variables
    carl::Variable y = hypro::VariablePool::getInstance().carlVarByIndex(0);
	
    // rectangular dynamics
    std::map<carl::Variable, carl::Interval<Number>> zeroDynamics;
    zeroDynamics.emplace(std::make_pair(y, carl::Interval<Number>(0, 0)));
    hypro::rectangularFlow<Number> zeroFlow(zeroDynamics);
    std::map<carl::Variable, carl::Interval<Number>> upDynamics;
    upDynamics.emplace(std::make_pair(y, carl::Interval<Number>(9, 9)));
    hypro::rectangularFlow<Number> upFlow(upDynamics);
    std::map<carl::Variable, carl::Interval<Number>> downDynamics;
    downDynamics.emplace(std::make_pair(y, carl::Interval<Number>(-9, -9)));
    hypro::rectangularFlow<Number> downFlow(downDynamics);
    
    // Create locations
	auto locMoveUp = res.createLocation("moveUp");
	auto locMoveDown = res.createLocation("moveDown");
	auto locOpen = res.createLocation("open");    
	auto locClosed = res.createLocation("closed");    
    // add flows
	locMoveUp->setRectangularFlow(upFlow);
	locMoveDown->setRectangularFlow(downFlow);
	locOpen->setRectangularFlow(zeroFlow);
	locClosed->setRectangularFlow(zeroFlow);
    //add invariants
    // locMoveUp y<=90
    Matrix invariantConstraints = Matrix::Zero( 1, 1 );
    invariantConstraints( 0, 0 ) = 1;
    Vector invariantConstants = Vector::Zero( 1 );
    invariantConstants( 0 ) = 90;
    locMoveUp->setInvariant( { invariantConstraints, invariantConstants } );
    // locMoveDown y>=0
    Matrix invariantConstraintsDown = Matrix::Zero( 1, 1 );
    invariantConstraintsDown( 0, 0 ) = -1;
    Vector invariantConstantsDown = Vector::Zero( 1 );
    invariantConstantsDown( 0 ) = 0;
    locMoveDown->setInvariant( { invariantConstraintsDown, invariantConstantsDown } );
    // locOpen y in [90, 90]
    Matrix invariantConstraintsOpen = Matrix::Zero( 2, 1 );
    invariantConstraintsOpen << 1, -1;
    Vector invariantConstantsOpen = Vector::Zero( 2 );
    invariantConstantsOpen << 90, -90;
    locOpen->setInvariant( { invariantConstraintsOpen, invariantConstantsOpen } );
    // locClosed y in [0, 0]
    Matrix invariantConstraintsClosed = Matrix::Zero( 2, 1 );
    invariantConstraintsClosed << 1, -1;
    Vector invariantConstantsClosed = Vector::Zero( 2 );
    invariantConstantsClosed << 0, 0;
    locClosed->setInvariant( { invariantConstraintsClosed, invariantConstantsClosed } );

    // transitions
    // locMoveUp -> locMoveUp
    auto transitionMoveUpMoveUp = locMoveUp->createTransition( locMoveUp );
    transitionMoveUpMoveUp->addLabel( hypro::Label{"raise"} );
    // locMoveUp -> locMoveDown
    auto transitionMoveUpMoveDown = locMoveUp->createTransition( locMoveDown );
    transitionMoveUpMoveDown->addLabel( hypro::Label{"lower"} );
    
    // locMoveUp -> locOpen
    auto transitionMoveUpOpen = locMoveUp->createTransition( locOpen );
    // guard y in [90,90]
    hypro::matrix_t<Number> guardConstraints = hypro::matrix_t<Number>(2, 1);
    guardConstraints << 1, -1;
    hypro::vector_t<Number> guardConstants = hypro::vector_t<Number>(2);
    guardConstants << 90, -90;
    hypro::Condition<Number> guard(guardConstraints, guardConstants);
    transitionMoveUpOpen->setGuard( guard );

    // locMoveDown -> locMoveDown
    auto transitionMoveDownMoveDown = locMoveDown->createTransition( locMoveDown );
    transitionMoveDownMoveDown->addLabel( hypro::Label{"lower"} );
    // locMoveDown -> locMoveUp
    auto transitionMoveDownMoveUp = locMoveDown->createTransition( locMoveUp );
    transitionMoveDownMoveUp->addLabel( hypro::Label{"raise"} );

    // locMoveDown -> locClosed
    auto transitionMoveDownClosed = locMoveDown->createTransition( locClosed );
    // guard y in [0,0]
    hypro::matrix_t<Number> guardConstraintsDown = hypro::matrix_t<Number>(2, 1);
    guardConstraintsDown << 1, -1;
    hypro::vector_t<Number> guardConstantsDown = hypro::vector_t<Number>(2);
    guardConstantsDown << 0, 0;
    hypro::Condition<Number> guardDown(guardConstraintsDown, guardConstantsDown);
    transitionMoveDownClosed->setGuard( guardDown );

    // locOpen -> locOpen
    auto transitionOpenOpen = locOpen->createTransition( locOpen );
    transitionOpenOpen->addLabel( hypro::Label{"raise"} );
    // locOpen -> locMoveDown
    auto transitionOpenMoveDown = locOpen->createTransition( locMoveDown );
    transitionOpenMoveDown->addLabel( hypro::Label{"lower"} );

    // locClosed -> locClosed
    auto transitionClosedClosed = locClosed->createTransition( locClosed );
    transitionClosedClosed->addLabel( hypro::Label{"lower"} );
    // locClosed -> locMoveUp
    auto transitionClosedMoveUp = locClosed->createTransition( locMoveUp );
    transitionClosedMoveUp->addLabel( hypro::Label{"raise"} );

	// Set initial state y = [90,90]
	Matrix initialConstraints = Matrix::Zero( 2, 1 );
	Vector initialConstants = Vector::Zero( 2 );
	initialConstraints << 1, -1;
	initialConstants << 90, -90;

	// Create HA
	res.addInitialState( locOpen, hypro::Condition<Number>( initialConstraints, initialConstants ) );

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

    // create first automaton with variable pool 0
    auto trainAutomaton = createTrainAutomaton<Number>();
	trainAutomaton.addTimeVariable();
	// create second automaton with variable pool 1
	hypro::VariablePool::getInstance().changeToPool(1);
    auto controllerAutomaton = createControllerAutomaton<Number>();
	controllerAutomaton.addTimeVariable();
    // create third automaton with variable pool 2
    hypro::VariablePool::getInstance().changeToPool(2);
    auto gateAutomaton = createGateAutomaton<Number>();
    gateAutomaton.addTimeVariable();

	// change back to pool 0
	hypro::VariablePool::getInstance().changeToPool(0);

	std::vector<hypro::HybridAutomaton<Number>> automata{ trainAutomaton, controllerAutomaton, gateAutomaton };

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

    std::cout << "Statistic: Train-Gate-System" << std::endl;
    
    displayRuntime(runtimes);

    return 0;
}
