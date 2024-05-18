/*
 * Copyright (c) 2023-2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/**
 * \example example_bouncingBall.cpp
 * An example file showing how to construct the automaton for a bouncing ball
 * system and afterwards determine the set of reachable states for this system
 * using H-polytopes as a state set representation.
 */

#include "hypro/algorithms/reachability/Reach.h"
#include "hypro/config.h"
#include "hypro/datastructures/HybridAutomaton/HybridAutomaton.h"
#include "hypro/datastructures/Point.h"
#include "hypro/representations/GeometricObjectBase.h"
#include "hypro/util/plotting/Plotter.h"
#include <chrono>


void runExample1(){
    using namespace hypro;

    // typedefs for simplification.
    using Number = double;
    using Representation = hypro::VPolytope<Number>;

    // create the discrete structure of the automaton and the automaton itself.
    HybridAutomaton<Number> bBallAutomaton = HybridAutomaton<Number>();
    Location<Number> *loc1 = bBallAutomaton.createLocation();
    Location<Number> *loc2 = bBallAutomaton.createLocation();

    // Transition<Number>* trans = loc1->createTrnsition(loc1);
    Transition<hypro::Location<Number>> *trans = loc1->createTransition(loc2);

    // matrix defining the flow (note: 3rd dimension for constant parts).
    matrix_t<Number> flowMatrixLoc1 = matrix_t<Number>(3, 3);
    matrix_t<Number> flowMatrixLoc2 = matrix_t<Number>(3, 3);
    
    // setup flow matrix (3x3, we add an artificial dimension to cope with
    // constants).
    flowMatrixLoc1(0, 0) = Number(0);
    flowMatrixLoc1(0, 1) = Number(0); // row 0 column 1
    flowMatrixLoc1(0, 2) = Number(1);
    flowMatrixLoc1(1, 0) = Number(0);
    flowMatrixLoc1(1, 1) = Number(0);
    flowMatrixLoc1(1, 2) = Number(1);
    flowMatrixLoc1(2, 0) = Number(0);
    flowMatrixLoc1(2, 1) = Number(0);
    flowMatrixLoc1(2, 2) = Number(0);

    flowMatrixLoc2(0, 0) = Number(0);
    flowMatrixLoc2(0, 1) = Number(0);
    flowMatrixLoc2(0, 2) = Number(0);
    flowMatrixLoc2(1, 0) = Number(0);
    flowMatrixLoc2(1, 1) = Number(0);
    flowMatrixLoc2(1, 2) = Number(0);
    flowMatrixLoc2(2, 0) = Number(0);
    flowMatrixLoc2(2, 1) = Number(0);
    flowMatrixLoc2(2, 2) = Number(0);

    loc1->setFlow(flowMatrixLoc1);
    loc2->setFlow(flowMatrixLoc2);

    // setup of the transition.
    // guard

    // -x <= -1 
    // x <= 1.5 
    // -y <= -2.5
    // y <= 3

    Condition<Number> guard;
    matrix_t<Number> guardMat = matrix_t<Number>(4, 2);
    vector_t<Number> guardVec = vector_t<Number>(4);

    guardVec(0) = Number(-1);
    guardVec(1) = Number(carl::rationalize<Number>(1.5));
    guardVec(2) = Number(-2.5);
    guardVec(3) = Number(3);

    guardMat(0, 0) = Number(-1);
    guardMat(0, 1) = Number(0);
    guardMat(1, 0) = Number(1);
    guardMat(1, 1) = Number(0);
    guardMat(2, 0) = Number(0);
    guardMat(2, 1) = Number(-1);
    guardMat(3, 0) = Number(0);
    guardMat(3, 1) = Number(1);

    guard.setMatrix(guardMat);
    guard.setVector(guardVec);

    // setup transition
    trans->setAggregation(AGG_SETTING::AGG);
    trans->setGuard(guard);
    trans->setSource(loc1);
    trans->setTarget(loc2);
    // trans->setReset(reset);

    trans->setUrgent(true); //urgent

    // create Box holding the initial set.
    matrix_t<Number> boxMat = matrix_t<Number>(4, 2);
    vector_t<Number> boxVec = vector_t<Number>(4);

    // y in [1,2]
    // x in [0,0]

    boxVec(0) = Number(0);
    boxVec(1) = Number(0);
    boxVec(2) = Number(-1);
    boxVec(3) = Number(2);

    boxMat(0, 0) = Number(1);
    boxMat(0, 1) = Number(0);
    boxMat(1, 0) = Number(-1);
    boxMat(1, 1) = Number(0);
    boxMat(2, 0) = Number(0);
    boxMat(2, 1) = Number(-1);
    boxMat(3, 0) = Number(0);
    boxMat(3, 1) = Number(1);

    // create initial state.
    bBallAutomaton.addInitialState(loc1, Condition<Number>(boxMat, boxVec));

    // set settings
    hypro::FixedAnalysisParameters fixedParameters;
    fixedParameters.jumpDepth = 1;
    fixedParameters.localTimeHorizon = 3;
    fixedParameters.fixedTimeStep = tNumber(1) / tNumber(10);

    hypro::AnalysisParameters analysisParameters;
    analysisParameters.algoUsed = 1;
    analysisParameters.timeStep = tNumber(1) / tNumber(10);
    analysisParameters.aggregation = hypro::AGG_SETTING::AGG;
    analysisParameters.representation_type = hypro::representation_name::polytope_h;

    hypro::Settings settings{{}, fixedParameters, {analysisParameters}};

    // initialize reachability tree
    auto roots = hypro::makeRoots<Representation>(bBallAutomaton);

    // instanciate reachability analysis class
    hypro::reachability::ReachUrgency<Representation, hypro::HybridAutomaton<Number>> reacher{bBallAutomaton,fixedParameters,analysisParameters, roots}; 

    auto start = std::chrono::high_resolution_clock::now();

    // perform reachability analysis.
    REACHABILITY_RESULT res = reacher.computeForwardReachability();

    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Time taken: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " milliseconds" << std::endl;

    std::cout << "Reachability result: " << res << std::endl;

    // plot flowpipes.
    std::cout << "Start plotting ... ";
    Plotter<Number> &plotter = Plotter<Number>::getInstance();
    plotter.setFilename("Example_1");

    for (const auto &node: preorder(roots)) {
        for (const auto &state_set: node.getFlowpipe()) {  // flowpipes
            plotter.addObject(state_set.projectOn({0, 1}).vertices());
        }
    }
    std::cout << "done." << std::endl;

    // write output.
    plotter.plot2d(PLOTTYPE::png);
}

void runExample2(){
    using namespace hypro;

    // typedefs for simplification.
    using Number = double;
    using Representation = hypro::VPolytope<Number>;

    // create the discrete structure of the automaton and the automaton itself.
    HybridAutomaton<Number> bBallAutomaton = HybridAutomaton<Number>();
    Location<Number> *loc1 = bBallAutomaton.createLocation();
    Location<Number> *loc2 = bBallAutomaton.createLocation();

    // Transition<Number>* trans = loc1->createTrnsition(loc1);
    Transition<hypro::Location<Number>> *trans = loc1->createTransition(loc2);

    // matrix defining the flow (note: 3rd dimension for constant parts).
    matrix_t<Number> flowMatrixLoc1 = matrix_t<Number>(3, 3);
    matrix_t<Number> flowMatrixLoc2 = matrix_t<Number>(3, 3);

    // setup flow matrix (3x3, we add an artificial dimension to cope with
    // constants).
    flowMatrixLoc1(0, 0) = Number(0);
    flowMatrixLoc1(0, 1) = Number(0); // row 0 column 1
    flowMatrixLoc1(0, 2) = Number(1);
    flowMatrixLoc1(1, 0) = Number(0);
    flowMatrixLoc1(1, 1) = Number(0);
    flowMatrixLoc1(1, 2) = Number(0);
    flowMatrixLoc1(2, 0) = Number(0);
    flowMatrixLoc1(2, 1) = Number(0);
    flowMatrixLoc1(2, 2) = Number(0);

    flowMatrixLoc2(0, 0) = Number(0);
    flowMatrixLoc2(0, 1) = Number(0);
    flowMatrixLoc2(0, 2) = Number(0);
    flowMatrixLoc2(1, 0) = Number(0);
    flowMatrixLoc2(1, 1) = Number(0);
    flowMatrixLoc2(1, 2) = Number(0);
    flowMatrixLoc2(2, 0) = Number(0);
    flowMatrixLoc2(2, 1) = Number(0);
    flowMatrixLoc2(2, 2) = Number(0);

    loc1->setFlow(flowMatrixLoc1);
    loc2->setFlow(flowMatrixLoc2);

    // setup of the transition.
    // guard

    // -x <= -2 
    // x <= 2.5 
    // -y <= -1
    // y <= 1.5

    Condition<Number> guard;
    matrix_t<Number> guardMat = matrix_t<Number>(4, 2);
    vector_t<Number> guardVec = vector_t<Number>(4);

    guardVec(0) = Number(-2);
    guardVec(1) = Number(carl::rationalize<Number>(2.5));
    guardVec(2) = Number(-1);
    guardVec(3) = Number(carl::rationalize<Number>(1.5));

    guardMat(0, 0) = Number(-1);
    guardMat(0, 1) = Number(0);
    guardMat(1, 0) = Number(1);
    guardMat(1, 1) = Number(0);
    guardMat(2, 0) = Number(0);
    guardMat(2, 1) = Number(-1);
    guardMat(3, 0) = Number(0);
    guardMat(3, 1) = Number(1);

    guard.setMatrix(guardMat);
    guard.setVector(guardVec);

    // setup transition
    trans->setAggregation(AGG_SETTING::AGG);
    trans->setGuard(guard);
    trans->setSource(loc1);
    trans->setTarget(loc2);

    trans->setUrgent(true); //urgent

    // create Box holding the initial set.
    matrix_t<Number> boxMat = matrix_t<Number>(4, 2);
    vector_t<Number> boxVec = vector_t<Number>(4);

    // y in [1,2]
    // x in [0,0]

    boxVec(0) = Number(0);
    boxVec(1) = Number(0);
    boxVec(2) = Number(-1);
    boxVec(3) = Number(2);

    boxMat(0, 0) = Number(1);
    boxMat(0, 1) = Number(0);
    boxMat(1, 0) = Number(-1);
    boxMat(1, 1) = Number(0);
    boxMat(2, 0) = Number(0);
    boxMat(2, 1) = Number(-1);
    boxMat(3, 0) = Number(0);
    boxMat(3, 1) = Number(1);

    // create initial state.
    bBallAutomaton.addInitialState(loc1, Condition<Number>(boxMat, boxVec));

    // set settings
    hypro::FixedAnalysisParameters fixedParameters;
    fixedParameters.jumpDepth = 1;
    fixedParameters.localTimeHorizon = 3;
    fixedParameters.fixedTimeStep = tNumber(1) / tNumber(10);

    hypro::AnalysisParameters analysisParameters;
    analysisParameters.algoUsed = 1;
    analysisParameters.timeStep = tNumber(1) / tNumber(10);
    analysisParameters.aggregation = hypro::AGG_SETTING::AGG;
    analysisParameters.representation_type = hypro::representation_name::polytope_h;

    hypro::Settings settings{{}, fixedParameters, {analysisParameters}};

    // initialize reachability tree
    auto roots = hypro::makeRoots<Representation>(bBallAutomaton);

    // instanciate reachability analysis class
    hypro::reachability::ReachUrgency<Representation, hypro::HybridAutomaton<Number>> reacher{bBallAutomaton,fixedParameters,analysisParameters, roots}; 

    auto start = std::chrono::high_resolution_clock::now();

    // perform reachability analysis.
    REACHABILITY_RESULT res = reacher.computeForwardReachability();

    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Time taken: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " milliseconds" << std::endl;

    std::cout << "Reachability result: " << res << std::endl;

    // plot flowpipes.
    std::cout << "Start plotting ... ";
    Plotter<Number> &plotter = Plotter<Number>::getInstance();
    plotter.setFilename("Example_2");

    for (const auto &node: preorder(roots)) {
        for (const auto &state_set: node.getFlowpipe()) {  // flowpipes
            plotter.addObject(state_set.projectOn({0, 1}).vertices());
        }
    }
    std::cout << "done." << std::endl;

    // write output.
    plotter.plot2d(PLOTTYPE::png);
}

void runExample3(){
    using namespace hypro;

    // typedefs for simplification.
    using Number = double;
    using Representation = hypro::HPolytope<Number>;

    // create the discrete structure of the automaton and the automaton itself.
    HybridAutomaton<Number> bBallAutomaton = HybridAutomaton<Number>();
    Location<Number> *loc1 = bBallAutomaton.createLocation();
    Location<Number> *loc2 = bBallAutomaton.createLocation();

    // Transition<Number>* trans = loc1->createTrnsition(loc1);
    Transition<hypro::Location<Number>> *trans = loc1->createTransition(loc2);

    // matrix defining the flow (note: 3rd dimension for constant parts).
    matrix_t<Number> flowMatrixLoc1 = matrix_t<Number>(3, 3);
    matrix_t<Number> flowMatrixLoc2 = matrix_t<Number>(3, 3);

    // setup flow matrix (3x3, we add an artificial dimension to cope with
    // constants).
    flowMatrixLoc1(0, 0) = Number(0);
    flowMatrixLoc1(0, 1) = Number(0); // row 0 column 1
    flowMatrixLoc1(0, 2) = Number(1);
    flowMatrixLoc1(1, 0) = Number(0);
    flowMatrixLoc1(1, 1) = Number(0);
    flowMatrixLoc1(1, 2) = Number(0);
    flowMatrixLoc1(2, 0) = Number(0);
    flowMatrixLoc1(2, 1) = Number(0);
    flowMatrixLoc1(2, 2) = Number(0);

    flowMatrixLoc2(0, 0) = Number(0);
    flowMatrixLoc2(0, 1) = Number(0);
    flowMatrixLoc2(0, 2) = Number(0);
    flowMatrixLoc2(1, 0) = Number(0);
    flowMatrixLoc2(1, 1) = Number(0);
    flowMatrixLoc2(1, 2) = Number(0);
    flowMatrixLoc2(2, 0) = Number(0);
    flowMatrixLoc2(2, 1) = Number(0);
    flowMatrixLoc2(2, 2) = Number(0);

    loc1->setFlow(flowMatrixLoc1);
    loc2->setFlow(flowMatrixLoc2);

    // setup of the transition.
    // guard

    // y - x <= -2.5    

    Condition<Number> guard;
    matrix_t<Number> guardMat = matrix_t<Number>(1, 2);
    vector_t<Number> guardVec = vector_t<Number>(1);

    guardVec(0) = Number(carl::rationalize<Number>(-2.5));

    guardMat(0, 0) = Number(-1);
    guardMat(0, 1) = Number(1);

    guard.setMatrix(guardMat);
    guard.setVector(guardVec);    

    // setup transition
    trans->setAggregation(AGG_SETTING::AGG);
    trans->setGuard(guard);
    trans->setSource(loc1);
    trans->setTarget(loc2);

    trans->setUrgent(true); //urgent

    // create Box holding the initial set.
    matrix_t<Number> boxMat = matrix_t<Number>(4, 2);
    vector_t<Number> boxVec = vector_t<Number>(4);

    // y in [1,2]
    // x in [0,0]

    boxVec(0) = Number(0);
    boxVec(1) = Number(0);
    boxVec(2) = Number(-1);
    boxVec(3) = Number(2);

    boxMat(0, 0) = Number(1);
    boxMat(0, 1) = Number(0);
    boxMat(1, 0) = Number(-1);
    boxMat(1, 1) = Number(0);
    boxMat(2, 0) = Number(0);
    boxMat(2, 1) = Number(-1);
    boxMat(3, 0) = Number(0);
    boxMat(3, 1) = Number(1);

    // create initial state.
    bBallAutomaton.addInitialState(loc1, Condition<Number>(boxMat, boxVec));

    // set settings
    hypro::FixedAnalysisParameters fixedParameters;
    fixedParameters.jumpDepth = 1;
    fixedParameters.localTimeHorizon = 5;
    fixedParameters.fixedTimeStep = tNumber(1) / tNumber(10);

    hypro::AnalysisParameters analysisParameters;
    analysisParameters.algoUsed = 1;
    analysisParameters.timeStep = tNumber(1) / tNumber(10);
    analysisParameters.aggregation = hypro::AGG_SETTING::AGG;
    analysisParameters.representation_type = hypro::representation_name::polytope_h;

    hypro::Settings settings{{}, fixedParameters, {analysisParameters}};

    // initialize reachability tree
    auto roots = hypro::makeRoots<Representation>(bBallAutomaton);

    // instanciate reachability analysis class
    hypro::reachability::ReachUrgency<Representation, hypro::HybridAutomaton<Number>> reacher{bBallAutomaton,fixedParameters,analysisParameters, roots}; 

    std::cout << "Start reachability analysis ... " << std::endl;

    auto start = std::chrono::high_resolution_clock::now();

    // perform reachability analysis.
    REACHABILITY_RESULT res = reacher.computeForwardReachability();

    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Time taken: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " milliseconds" << std::endl;

    std::cout << "Reachability result: " << res << std::endl;

    // plot flowpipes.
    std::cout << "Start plotting ... ";
    Plotter<Number> &plotter = Plotter<Number>::getInstance();
    plotter.setFilename("Example_3");

    for (const auto &node: preorder(roots)) {
        for (const auto &state_set: node.getFlowpipe()) {  // flowpipes
            plotter.addObject(state_set.projectOn({0, 1}).vertices());
        }
    }
    std::cout << "done." << std::endl;

    // write output.
    plotter.plot2d(PLOTTYPE::png);
}

void runExample4(){
    using namespace hypro;

    // typedefs for simplification.
    using Number = double;
    using Representation = hypro::HPolytope<Number>;

    // create the discrete structure of the automaton and the automaton itself.
    HybridAutomaton<Number> bBallAutomaton = HybridAutomaton<Number>();
    Location<Number> *loc1 = bBallAutomaton.createLocation();

    // Transition<Number>* trans = loc1->createTrnsition(loc1);
    Transition<hypro::Location<Number>> *trans = loc1->createTransition(loc1);

    // matrix defining the flow (note: 3rd dimension for constant parts).
    matrix_t<Number> flowMatrixLoc1 = matrix_t<Number>(4, 4);

    // setup flow matrix (3x3, we add an artificial dimension to cope with
    // constants).
    flowMatrixLoc1(0, 0) = Number(0);
    flowMatrixLoc1(0, 1) = Number(0); // row 0 column 1
    flowMatrixLoc1(0, 2) = Number(0);
    flowMatrixLoc1(0, 3) = Number(1);
    flowMatrixLoc1(1, 0) = Number(0);
    flowMatrixLoc1(1, 1) = Number(0);
    flowMatrixLoc1(1, 2) = Number(0);
    flowMatrixLoc1(1, 3) = Number(1);
    flowMatrixLoc1(2, 0) = Number(0);
    flowMatrixLoc1(2, 1) = Number(0);
    flowMatrixLoc1(2, 2) = Number(0);
    flowMatrixLoc1(2, 3) = Number(0);
    flowMatrixLoc1(3, 0) = Number(0);
    flowMatrixLoc1(3, 1) = Number(0);
    flowMatrixLoc1(3, 2) = Number(0);
    flowMatrixLoc1(3, 3) = Number(0);

    loc1->setFlow(flowMatrixLoc1);

    // setup of the transition.
    // guard

    // z - x <= 0
    // z - y <= 0  

    Condition<Number> guard;
    matrix_t<Number> guardMat = matrix_t<Number>(2, 3);
    vector_t<Number> guardVec = vector_t<Number>(2);

    guardVec(0) = Number(0);
    guardVec(1) = Number(0);

    guardMat(0, 0) = Number(-1);
    guardMat(0, 1) = Number(0);
    guardMat(0, 2) = Number(1);
    guardMat(1, 0) = Number(0);
    guardMat(1, 1) = Number(-1);
    guardMat(1, 2) = Number(1);

    guard.setMatrix(guardMat);
    guard.setVector(guardVec);    

        // reset function
    Reset<Number> reset;
    vector_t<Number> constantReset = vector_t<Number>(3, 1);
    matrix_t<Number> linearReset = matrix_t<Number>(3, 3);

    constantReset(0) = Number(0);
    constantReset(1) = Number(0);
    constantReset(2) = Number(1);

    linearReset(0, 0) = Number(0);
    linearReset(0, 1) = Number(0);
    linearReset(0, 2) = Number(0);
    linearReset(1, 0) = Number(0);
    linearReset(1, 1) = Number(0);
    linearReset(1, 2) = Number(0);
    linearReset(2, 0) = Number(0);
    linearReset(2, 1) = Number(0);
    linearReset(2, 2) = Number(1);

    reset.setVector(constantReset);
    reset.setMatrix(linearReset);

    // setup transition
    trans->setAggregation(AGG_SETTING::AGG);
    trans->setGuard(guard);
    trans->setSource(loc1);
    trans->setTarget(loc1);
    trans->setReset(reset);


    trans->setUrgent(true); //urgent

    // create Box holding the initial set.
    matrix_t<Number> boxMat = matrix_t<Number>(6, 3);
    vector_t<Number> boxVec = vector_t<Number>(6);

    // y in [1,3]
    // x in [1,3]
    // z in [2,2]

    boxVec(0) = Number(-1);
    boxVec(1) = Number(3);
    boxVec(2) = Number(-1);
    boxVec(3) = Number(3);
    boxVec(4) = Number(-2);
    boxVec(5) = Number(2);

    boxMat(0, 0) = Number(1);
    boxMat(0, 1) = Number(0);
    boxMat(0, 2) = Number(0);
    boxMat(1, 0) = Number(-1);
    boxMat(1, 1) = Number(0);
    boxMat(1, 2) = Number(0);
    boxMat(2, 0) = Number(0);
    boxMat(2, 1) = Number(1);
    boxMat(2, 2) = Number(0);
    boxMat(3, 0) = Number(0);
    boxMat(3, 1) = Number(-1);
    boxMat(3, 2) = Number(0);
    boxMat(4, 0) = Number(0);
    boxMat(4, 1) = Number(0);
    boxMat(4, 2) = Number(1);
    boxMat(5, 0) = Number(0);
    boxMat(5, 1) = Number(0);
    boxMat(5, 2) = Number(-1);


    // create initial state.
    bBallAutomaton.addInitialState(loc1, Condition<Number>(boxMat, boxVec));

    // set settings
    hypro::FixedAnalysisParameters fixedParameters;
    fixedParameters.jumpDepth = 1;
    fixedParameters.localTimeHorizon = 5;
    fixedParameters.fixedTimeStep = tNumber(1) / tNumber(10);

    hypro::AnalysisParameters analysisParameters;
    analysisParameters.algoUsed = 0;
    analysisParameters.timeStep = tNumber(1) / tNumber(10);
    analysisParameters.aggregation = hypro::AGG_SETTING::AGG;
    analysisParameters.representation_type = hypro::representation_name::polytope_h;

    hypro::Settings settings{{}, fixedParameters, {analysisParameters}};

    // initialize reachability tree
    auto roots = hypro::makeRoots<Representation>(bBallAutomaton);

    // instanciate reachability analysis class
    hypro::reachability::ReachUrgency<Representation, hypro::HybridAutomaton<Number>> reacher{bBallAutomaton,fixedParameters,analysisParameters, roots}; 

    std::cout << "Start reachability analysis ... " << std::endl;

    auto start = std::chrono::high_resolution_clock::now();

    // perform reachability analysis.
    REACHABILITY_RESULT res = reacher.computeForwardReachability();

    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Time taken for setMinus2: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " milliseconds" << std::endl;


    analysisParameters.algoUsed = 1;
    // instanciate reachability analysis class
    hypro::reachability::ReachUrgency<Representation, hypro::HybridAutomaton<Number>> reacher2{bBallAutomaton,fixedParameters,analysisParameters, roots}; 

    auto start2 = std::chrono::high_resolution_clock::now();

    // perform reachability analysis.
    REACHABILITY_RESULT res2 = reacher2.computeForwardReachability();

    auto end2 = std::chrono::high_resolution_clock::now();

    std::cout << "Time taken for setMinusCrossing: " << std::chrono::duration_cast<std::chrono::milliseconds>(end2 - start2).count() << " milliseconds" << std::endl;


    std::cout << "Reachability result: " << res << std::endl;

    // plot flowpipes.
    std::cout << "Start plotting ... ";
    Plotter<Number> &plotter = Plotter<Number>::getInstance();
    plotter.setFilename("Example_4");

    for (const auto &node: preorder(roots)) {
        for (const auto &state_set: node.getFlowpipe()) {  // flowpipes
            plotter.addObject(state_set.projectOn({0, 1}).vertices());
        }
    }
    std::cout << "done." << std::endl;

    // write output.
    plotter.plot2d(PLOTTYPE::png);
}



int main(int argc, char **argv) {
    
    int rep = 0;
    if (argc == 2) {
        char *p;
        rep = strtol(argv[1], &p, 10);
    }else{
        std::cout << "Please provide a number for example: <example_number>" << std::endl;
        std::cout << "Example numbers available: 1, 2, 3, 4" << std::endl;
        return 0;
    }

    std::cout << "Running example " << rep << std::endl;

    switch (rep)
    {
        case 1:
            runExample1();
            break;

        case 2:
            runExample2();
            break;
        case 3:
            runExample3();
            break;
        case 4:
            runExample4();
            break;
    }
    
    return 0;
}

    