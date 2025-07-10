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
#include "hypro/datastructures/reachability/ReachTreev2Util.h"
#include "hypro/config.h"
#include "hypro/datastructures/HybridAutomaton/HybridAutomaton.h"
#include "hypro/datastructures/Point.h"
#include "hypro/representations/GeometricObjectBase.h"
#include "hypro/util/plotting/Plotter.h"
#include <chrono>

using namespace hypro;

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
    analysisParameters.setMinusAlgoUsed = 1;
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
    analysisParameters.setMinusAlgoUsed = 1;
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
    analysisParameters.setMinusAlgoUsed = 1;
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

template<typename Number, typename Converter, typename Setting>
HPolytopeT<Number, Converter, Setting> getHPolytopeP_Test1() {
    // Create a polytope
    using HalfspaceVector = std::vector<Halfspace<Number>>;

    HalfspaceVector halfspaces;
    halfspaces.push_back(Halfspace<Number>(Point<Number>({Number(-1), Number(0), Number(0), Number(0)}), Number(-2.24154)));

    halfspaces.push_back(Halfspace<Number>(Point<Number>({Number(0), Number(0), Number(0), Number(-1)}), Number(-3)));

    halfspaces.push_back(Halfspace<Number>(Point<Number>({Number(0), Number(-1), Number(0), Number(0)}), Number(-1)));

    halfspaces.push_back(Halfspace<Number>(Point<Number>({Number(0), Number(0), Number(0), Number(1)}), Number(3.01)));

    halfspaces.push_back(Halfspace<Number>(Point<Number>({Number(1), Number(0), Number(0), Number(0)}), Number(2.50846)));

    halfspaces.push_back(Halfspace<Number>(Point<Number>({Number(1), Number(0.00211589), Number(0), Number(0.423177)}), Number(3.78434)));

    halfspaces.push_back(Halfspace<Number>(Point<Number>({Number(1), Number(0.127744), Number(0), Number(0.297549)}), Number(3.78434)));

    halfspaces.push_back(Halfspace<Number>(Point<Number>({Number(0), Number(1), Number(0), Number(0)}), Number(5)));

    halfspaces.push_back(Halfspace<Number>(Point<Number>({Number(1), Number(0.133464), Number(0), Number(-25.8464)}), Number(-74.6302)));

    halfspaces.push_back(Halfspace<Number>(Point<Number>({Number(1), Number(0.129232), Number(0), Number(0)}), Number(2.89616)));

    halfspaces.push_back(Halfspace<Number>(Point<Number>({Number(0), Number(0), Number(1), Number(0)}), Number(2)));

    halfspaces.push_back(Halfspace<Number>(Point<Number>({Number(0), Number(0), Number(-1), Number(0)}), Number(-2)));


    HPolytopeT<Number, Converter, Setting> hp = HPolytopeT<Number, Converter, Setting>(halfspaces);
    return hp;
}

template<typename Number, typename Converter, typename Setting>
HPolytopeT<Number, Converter, Setting> getHPolytopeG_Test1() {
    // Create a polytope
    using HalfspaceVector = std::vector<Halfspace<Number>>;

    HalfspaceVector halfspaces;
    halfspaces.push_back(Halfspace<Number>(Point<Number>({Number(-1), Number(0), Number(1), Number(0)}), Number(0)));
    halfspaces.push_back(Halfspace<Number>(Point<Number>({Number(0), Number(-1), Number(0), Number(1)}), Number(0)));


    HPolytopeT<Number, Converter, Setting> hp = HPolytopeT<Number, Converter, Setting>(halfspaces);
    return hp;
}

void runTest1(){
    using Number = double; 
    //using Number = mpq_class; //slower
    using Converter = Converter<Number>;
	using Setting = HPolytopeSetting;

    HPolytopeT<Number, Converter, Setting> P_H = getHPolytopeP_Test1<Number, Converter, Setting> ();
    HPolytopeT<Number, Converter, Setting> G_H = getHPolytopeG_Test1<Number, Converter, Setting> ();
    std::cout << "P_H:" << std::endl << P_H << std::endl;
    std::cout << "G_H:" << std::endl << G_H << std::endl;

    HPolytopeT<Number, Converter, Setting> res_H = P_H.setMinus(G_H, 1)[0];

    std::cout << "res_H:" << std::endl << res_H << std::endl;

    auto res_V = Converter::toVPolytope(res_H);
    std::cout << "res_V:" << std::endl << res_V << std::endl;

    std::vector<std::size_t> plottingDimensions = {0,1};
    auto res_V_projected = res_H.projectOn(plottingDimensions).vertices();
    std::cout << "res_V_projected:" << std::endl << res_V_projected << std::endl;

    auto &plotter = hypro::Plotter<Number>::getInstance();
    std::string extendedFilename = "SimpleTestPlot";
    std::cout << "filename is " << extendedFilename << std::endl;

    plotter.setFilename(extendedFilename);
    unsigned cnt = 0;
    // segments plotting
    plotter.addObject(res_H.projectOn(plottingDimensions).vertices(), hypro::plotting::colors[cnt % 10]);
    std::cout << "Write to file." << std::endl;
    plotter.plot2d();


}

template<typename Number, typename Converter, typename Setting>
VPolytopeT<Number, Converter, Setting> getVPolytopeP_Test2() {

    using pointVector = std::vector<Point<Number>>;

    pointVector points;
    points.push_back(Point<Number>({Number(11.5987), Number(4)}));
    points.push_back(Point<Number>({Number(11.5987), Number(5)}));
    points.push_back(Point<Number>({Number(11.8118), Number(4)}));
    points.push_back(Point<Number>({Number(11.6127), Number(5)}));
    points.push_back(Point<Number>({Number(11.8118), Number(5)}));
    
    VPolytopeT<Number, Converter, Setting> vp = VPolytopeT<Number, Converter, Setting>(points);
    return vp;

}

void runTest2(){
    using Number = double; 
    //using Number = mpq_class; //slower
    using Converter = Converter<Number>;
	using SettingH = HPolytopeSetting;
    using SettingV = VPolytopeSetting;

    VPolytopeT<Number, Converter, SettingV> P_V = getVPolytopeP_Test2<Number, Converter, SettingV> ();
    std::cout << "P_V:" << std::endl << P_V << std::endl;

    HPolytopeT<Number, Converter, SettingH> P_H = Converter::toHPolytope(P_V, CONV_MODE::EXACT);
    std::cout << "P_H:" << std::endl << P_H << std::endl;

    // VPolytopeT<Number, Converter, SettingV> P_V2 = Converter::toVPolytope(P_H);
    // std::cout << "P_V2:" << std::endl << P_V2 << std::endl;

    std::cout << "P_H.vertices()" << std::endl << P_H.vertices() << std::endl;
}

template<typename Number, typename Converter, typename Setting>
VPolytopeT<Number, Converter, Setting> getVPolytopeP_Test3() {

    using pointVector = std::vector<Point<Number>>;

    pointVector points;
    points.push_back(Point<Number>({Number(7.59871), Number(4)}));
    points.push_back(Point<Number>({Number(7.59871), Number(5)}));
    points.push_back(Point<Number>({Number(7.90517), Number(4)}));
    points.push_back(Point<Number>({Number(7.90517), Number(5)}));
    
    VPolytopeT<Number, Converter, Setting> vp = VPolytopeT<Number, Converter, Setting>(points);
    return vp;

}

void runTest3(){
    using Number = double; 
    //using Number = mpq_class; //slower
    using Converter = Converter<Number>;
	using SettingH = HPolytopeSetting;
    using SettingV = VPolytopeSetting;

    VPolytopeT<Number, Converter, SettingV> P_V = getVPolytopeP_Test3<Number, Converter, SettingV> ();
    std::cout << "P_V:" << std::endl << P_V << std::endl;

    HPolytopeT<Number, Converter, SettingH> P_H = Converter::toHPolytope(P_V, CONV_MODE::EXACT);
    std::cout << "P_H:" << std::endl << P_H << std::endl;

    // VPolytopeT<Number, Converter, SettingV> P_V2 = Converter::toVPolytope(P_H);
    // std::cout << "P_V2:" << std::endl << P_V2 << std::endl;

    // std::cout << "P_H.vertices()" << std::endl << P_H.vertices() << std::endl;
}

int main(int argc, char **argv) {
    
    int rep = 0;
    if (argc == 2) {
        char *p;
        rep = strtol(argv[1], &p, 10);
    }else{
        std::cout << "Please provide a number for example: <example_number>" << std::endl;
        std::cout << "Example numbers available: 1, 2, 3" << std::endl;
        std::cout << "Test numbers available: 4, 5, 6" << std::endl;
        
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
            runTest1();
            break;
        case 5:
            runTest2();
            break;
        case 6:
            runTest3();
            break;
    }
    
    return 0;
}

    