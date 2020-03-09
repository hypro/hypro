#include "algorithms/reachability/Reach.h"
#include "config.h"
#include "datastructures/HybridAutomaton/HybridAutomaton.h"
#include "datastructures/Point.h"
#include "representations/GeometricObject.h"
#include "util/plotting/Plotter.h"
#include <iostream>

int main() {

  // typedefs for simplification.
  typedef mpq_class Number;
  typedef hypro::HPolytope<Number> Representation;
  using Matrix = hypro::matrix_t<Number>;
  using Vector = hypro::vector_t<Number>;
  using State = hypro::State_t<Number>;

  // create the discrete structure of the automaton and the automaton itself.
  std::unique_ptr<hypro::Location<Number>> loc1 =
      std::make_unique<hypro::Location<Number>>();
  std::unique_ptr<hypro::Transition<Number>> trans =
      std::make_unique<hypro::Transition<Number>>();
  hypro::HybridAutomaton<Number> bBallAutomaton =
      hypro::HybridAutomaton<Number>();

  // matrix defining the flow (note: 3rd variable for constant parts)
  Matrix flowMatrix = Matrix::Zero(3, 3);

  // location parameter setting.
  // creation of the invariant.
  Matrix invariantMat = Matrix::Zero(1, 2);
  Vector invariantVec = Vector::Zero(1);

  invariantMat(0, 0) = Number(-1);

  hypro::Condition<Number> inv(invariantMat, invariantVec);

  loc1->setInvariant(inv);

  // setup flow matrix (3x3, we add an artificial dimension to cope with
  // constants).
  flowMatrix(0, 1) = Number(1);
  flowMatrix(1, 2) = Number(carl::rationalize<Number>(-9.81));

  loc1->setFlow(hypro::linearFlow<Number>(flowMatrix));

  // setup of the transition.
  // guard
  hypro::Condition<Number> guard;
  Matrix guardMat = Matrix::Zero(3, 2);
  Vector guardVec = Vector::Zero(3);

  guardMat(0, 0) = Number(1);
  guardMat(1, 0) = Number(-1);
  guardMat(2, 1) = Number(1);

  guard.setMatrix(guardMat);
  guard.setVector(guardVec);

  // reset function
  hypro::Reset<Number> reset;
  Vector constantReset = Vector::Zero(2, 1);
  Matrix linearReset = Matrix::Zero(2, 2);

  linearReset(0, 0) = Number(1);
  linearReset(1, 1) = Number(carl::rationalize<Number>(-0.75));

  reset.setVector(constantReset);
  reset.setMatrix(linearReset);

  // setup transition
  trans->setAggregation(hypro::Aggregation::clustering);
  trans->setClusterBound(2);
  trans->setGuard(guard);
  trans->setSource(loc1);
  trans->setTarget(loc1);
  trans->setReset(reset);

  // add defined location and transition to the automaton.
  loc1->addTransition(std::move(trans));

  // create Box holding the initial set.
  Matrix boxMat = Matrix::Zero(4, 2);
  Vector boxVec = Vector::Zero(4);

  boxVec(0) = Number(carl::rationalize<Number>(10.2));
  boxVec(1) = Number(-10);

  boxMat(0, 0) = Number(1);
  boxMat(1, 0) = Number(-1);
  boxMat(2, 1) = Number(1);
  boxMat(3, 1) = Number(-1);

  // create initial state.
  bBallAutomaton.addInitialState(loc1.get(),
                                 hypro::Condition<Number>(boxMat, boxVec));

  bBallAutomaton.addLocation(std::move(loc1));

  // vector of sets to collect flowpipes (which are again a vector of sets).
  std::vector<std::vector<Representation>> flowpipes;

  // instanciate reachability analysis algorithm.
  hypro::reachability::Reach<Number, hypro::reachability::ReachSettings, State>
      reacher(bBallAutomaton);
  hypro::ReachabilitySettings settings = reacher.settings();
  settings.timeStep = carl::convert<double, Number>(0.01);
  settings.timeBound = Number(3);
  settings.jumpDepth = 3;
  reacher.setSettings(settings);
  reacher.setRepresentationType(Representation::type());

  // set initial states
  std::vector<State> initialStates;
  for (const auto &locationConditionPair : bBallAutomaton.getInitialStates()) {
    State tmp{locationConditionPair.first};
    tmp.setSet(Representation(locationConditionPair.second.getMatrix(),
                              locationConditionPair.second.getVector()));
    initialStates.emplace_back(tmp);
  }
  reacher.setInitialStates(std::move(initialStates));

  // perform reachability analysis.
  auto flowpipeIndices = reacher.computeForwardReachability();

  // Test if we can get the tree and check its contents
  std::cout << "Reach tree depth: " << reacher.getReachabilityTree()->getDepth()
            << " and number nodes: "
            << reacher.getReachabilityTree()->getNumberNodes() << std::endl;
  // write tree in dot-format to file.
  std::string dotString = reacher.getReachabilityTree()->getDotRepresentation();
  std::fstream outfile = std::fstream("reachTree.gv", std::ios_base::out);
  outfile << dotString;
  outfile.close();

  // plot flowpipes.
  hypro::Plotter<Number> &plotter = hypro::Plotter<Number>::getInstance();
  plotter.setFilename("bouncingBall");
  for (auto &indexPair : flowpipeIndices) {
    std::vector<State> flowpipe = indexPair.second;
    // Plot single flowpipe
    for (auto &set : flowpipe) {
      std::vector<hypro::Point<Number>> points = set.vertices();
      if (!points.empty() && points.size() > 2) {
        for (auto &point : points) {
          point.reduceDimension(2);
        }
        plotter.addObject(points);
        points.clear();
      }
    }
  }

  // write output.
  plotter.plot2d();

  return 0;
}
