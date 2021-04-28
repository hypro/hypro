#include <hypro/datastructures/HybridAutomaton/HybridAutomaton.h>
#include <hypro/datastructures/HybridAutomaton/output/Flowstar.h>
#include <hypro/parser/antlr4-flowstar/ParserWrapper.h>
#include <hypro/util/logging/Filewriter.h>
#include <hypro/datastructures/HybridAutomaton/State.h>
#include <iostream>

using namespace hypro;

static const int firingThreshold = 100;
static const double alpha = 1.1;
static const double globalTimeHorizon = 300;

/**
 * @brief      Creates a component using a synchronization variable for the
 * synchronizating robots benchmark.
 * @param[in]  i       Component identifier.
 * @tparam     Number  Numeric type.
 * @return     A hybrid automaton for one component (one robot).
 */
template <typename Number>
HybridAutomaton<Number> createComponent1(unsigned i) {
  using HA = HybridAutomaton<Number>;
  using M = matrix_t<Number>;
  using V = vector_t<Number>;
  using Lpt = Location<Number> *;
  using Tpt = Transition<Number> *;
  using S = State_t<Number>;
  std::stringstream st;

  // result automaton
  HA res;

  // set up variables
  typename HybridAutomaton<Number>::variableVector vars;
  st << "x_" << i;
  vars.push_back(st.str());
  vars.push_back("x_t"); // t is the global clock for plotting
  vars.push_back("z");   // z is the shared variable
  res.setVariables(vars);
  st.str(std::string());
  unsigned dim = vars.size();

  // wait

  st << "wait_" << i;
  Location<Number> wait = Location<Number>();
  wait->setName(st.str());
  M waitFlow = M::Zero(dim + 1, dim + 1);
  waitFlow(0, dim) = 1;
  waitFlow(1, dim) = 1; // time always advances at rate 1
  wait->setFlow(waitFlow);

  M initConstraints = M::Zero(6, 3);
  initConstraints << 1, 0, 0, -1, 0, 0, 0, 1, 0, 0, -1, 0, 0, 0, 1, 0, 0, -1;
  V initConstants = V::Zero(6);
  initConstants << 0, 0, 0, 0, 0, 0;

  S initialState;
  initialState.setLocation(wait);
  initialState.setSet(ConstraintSet<Number>(initConstraints, initConstants));
  res.addInitialState(initialState);

  M waitInvariant = M::Zero(2, dim);
  waitInvariant << 1, 0, 0, 0, 1, 0;
  V waitInvConsts = V::Zero(2);
  waitInvConsts << Number(firingThreshold), Number(globalTimeHorizon);
  wait->setInvariant(Condition<Number>{waitInvariant, waitInvConsts});
  res.addLocation(wait);

  // adapt
  Location<Number> adapt;
  st.str(std::string());
  st << "adapt_" << i;
  adapt->setName(st.str());

  M adaptFlow = M::Zero(dim + 1, dim + 1);
  adaptFlow(1, dim) = 1; // time always advances at rate 1
  adapt->setFlow(adaptFlow);

  res.addLocation(adapt);

  // flash
  Location<Number> flash;
  st.str(std::string());
  st << "flash_" << i;
  flash->setName(st.str());

  M flashFlow = M::Zero(dim + 1, dim + 1);
  flashFlow(1, dim) = 1; // time always advances at rate 1
  flash->setFlow(flashFlow);

  M flashInvariant = M::Zero(2, dim);
  flashInvariant(0, 0) = 1;
  flashInvariant(1, 0) = -1;
  V flashInvConsts = V::Zero(2);
  flash->setInvariant(Condition<Number>{flashInvariant, flashInvConsts});
  res.addLocation(flash);

  // transitions
  // to flash
  Tpt toFlash = new Transition<Number>(wait, flash);
  M guardConstraints = M::Zero(2, dim);
  guardConstraints(0, 0) = 1;
  guardConstraints(1, 0) = -1;
  V guardConstants = V::Zero(2);
  guardConstants << Number(firingThreshold), Number(-firingThreshold);
  toFlash->setGuard(Condition<Number>{guardConstraints, guardConstants});

  M resetMat = M::Identity(dim, dim);
  V resetVec = V::Zero(dim);
  resetMat(0, 0) = 0;
  resetMat(2, 2) = 0;
  resetVec(2) = 1;
  toFlash->setReset(Reset<Number>(resetMat, resetVec));
  toFlash->setAggregation(Aggregation::aggregation);
  // toFlash->setUrgent();

  wait->addTransition(toFlash);
  res.addTransition(toFlash);

  // to execFlash
  Tpt flashLoop = new Transition<Number>(flash, flash);
  guardConstraints = M::Zero(2, dim);
  guardConstraints(0, 2) = 1;
  guardConstraints(1, 2) = -1;
  guardConstants = V::Zero(2);
  guardConstants << 1, -1;
  flashLoop->setGuard(Condition<Number>{guardConstraints, guardConstants});

  resetMat = M::Identity(dim, dim);
  resetMat(2, 2) = 0;
  resetVec = V::Zero(dim);
  flashLoop->setReset(Reset<Number>(resetMat, resetVec));
  flashLoop->setUrgent();
  flashLoop->addLabel(Label{"flash"});
  flashLoop->setAggregation(Aggregation::aggregation);

  flash->addTransition(flashLoop);
  res.addTransition(flashLoop);

  // back to wait
  Tpt reWait = new Transition<Number>(flash, wait);
  guardConstraints = M::Zero(2, dim);
  guardConstraints(0, 2) = 1;
  guardConstraints(1, 2) = -1;
  guardConstants = V::Zero(2);
  reWait->setGuard(Condition<Number>{guardConstraints, guardConstants});
  resetMat = M::Identity(dim, dim);
  resetVec = V::Zero(dim);
  reWait->addLabel({"return"});
  reWait->setReset(Reset<Number>(resetMat, resetVec));
  reWait->setUrgent();
  reWait->setAggregation(Aggregation::aggregation);

  flash->addTransition(reWait);
  res.addTransition(reWait);

  // to adapt
  Tpt toAdapt = new Transition<Number>(wait, adapt);
  guardConstraints = M::Zero(3, dim);
  guardConstraints(0, 2) = 1;
  guardConstraints(1, 2) = -1;
  guardConstraints(2, 0) = 1;
  guardConstants = V::Zero(3);
  guardConstants << 1, -1, Number(firingThreshold);
  toAdapt->setGuard(Condition<Number>{guardConstraints, guardConstants});
  resetMat = M::Identity(dim, dim);
  resetMat(0, 0) = Number(alpha);
  resetMat(2, 2) = 0;
  resetVec = V::Zero(dim);
  toAdapt->setReset(Reset<Number>(resetMat, resetVec));
  toAdapt->addLabel({"flash"});
  toAdapt->setAggregation(Aggregation::aggregation);
  // toAdapt->setUrgent();

  wait->addTransition(toAdapt);
  res.addTransition(toAdapt);

  // from adapt, regular
  Tpt fromAdaptRegular = new Transition<Number>(adapt, wait);
  guardConstraints = M::Zero(1, dim);
  guardConstraints(0, 0) = 1;
  guardConstants = V::Zero(1);
  guardConstants << Number(firingThreshold);
  fromAdaptRegular->setGuard(
      Condition<Number>{guardConstraints, guardConstants});
  resetMat = M::Identity(dim, dim);
  resetVec = V::Zero(dim);
  fromAdaptRegular->setReset(Reset<Number>(resetMat, resetVec));
  fromAdaptRegular->addLabel(Label{"return"});
  fromAdaptRegular->setAggregation(Aggregation::aggregation);
  fromAdaptRegular->setUrgent();

  adapt->addTransition(fromAdaptRegular);
  res.addTransition(fromAdaptRegular);

  // from adapt, scale
  Tpt fromAdaptScale = new Transition<Number>(adapt, flash);
  guardConstraints = M::Zero(1, dim);
  guardConstraints(0, 0) = -1;
  guardConstants = V::Zero(1);
  guardConstants << Number(-firingThreshold);
  fromAdaptScale->setGuard(Condition<Number>{guardConstraints, guardConstants});
  // fromAdaptScale->addLabel(Label{"flash"});
  fromAdaptScale->setAggregation(Aggregation::aggregation);
  fromAdaptScale->setUrgent();

  resetMat = M::Identity(dim, dim);
  resetMat(0, 0) = 0;
  resetVec = V::Zero(dim);
  fromAdaptScale->setReset(Reset<Number>(resetMat, resetVec));

  adapt->addTransition(fromAdaptScale);
  res.addTransition(fromAdaptScale);

  return res;
}

template <typename Number>
HybridAutomaton<Number> createComponent2(unsigned i,
                                         const std::vector<Label> &labels) {
  using HA = HybridAutomaton<Number>;
  using M = matrix_t<Number>;
  using V = vector_t<Number>;
  using Lpt = Location<Number> *;
  using Tpt = Transition<Number> *;
  using S = State_t<Number>;
  std::stringstream st;

  // result automaton
  HA res;

  // set up variables
  typename HybridAutomaton<Number>::variableVector vars;
  st << "x_" << i;
  vars.push_back(st.str());
  vars.push_back("x_t"); // t is the global clock for plotting
  res.setVariables(vars);
  st.str(std::string());
  unsigned dim = vars.size();

  // wait

  st << "wait_" << i;
  Location<Number> waitLoc = Location<Number>();
  Lpt wait = &waitLoc;
  wait->setName(st.str());
  M waitFlow = M::Zero(dim + 1, dim + 1); // both variables advance
  waitFlow(0, dim) = 1;
  waitFlow(1, dim) = 1;
  wait->setFlow(waitFlow);

  M waitInvariant = M::Zero(2, dim);
  waitInvariant(0, 0) = 1;
  waitInvariant(1, 1) = 1;
  V waitInvConsts = V::Zero(2);
  waitInvConsts << Number(firingThreshold), Number(globalTimeHorizon);
  wait->setInvariant(Condition<Number>{waitInvariant, waitInvConsts});
  res.addLocation(std::move(std::unique_ptr<Location<Number>>(wait)));

  // initial state
  M initConstraints = M::Zero(4, 2);
  initConstraints << 1, 0, -1, 0, 0, 1, 0, -1;
  V initConstants = V::Zero(4);
  initConstants << 0, 0, 0, 0;

  S initialState;
  initialState.setLocation(wait);
  initialState.setSet(ConstraintSet<Number>(initConstraints, initConstants));
  res.addInitialState(initialState);

  // adapt
  Location<Number> adaptLoc;
  Lpt adapt = &adaptLoc;
  st.str(std::string());
  st << "adapt_" << i;
  adapt->setName(st.str());

  M adaptFlow = M::Zero(dim + 1, dim + 1);
  adaptFlow(1, dim) = 1; // time always advances at rate 1
  adapt->setFlow(adaptFlow);

  res.addLocation(*adapt);

  // transitions
  // flash self loop
  auto flash = std::make_unique<Transition<Number>>(wait, wait);
  M guardConstraints = M::Zero(2, dim);
  guardConstraints(0, 0) = 1;
  guardConstraints(1, 0) = -1;
  V guardConstants = V::Zero(2);
  guardConstants << Number(firingThreshold), Number(-firingThreshold);
  flash->setGuard(Condition<Number>{guardConstraints, guardConstants});

  M resetMat = M::Identity(dim, dim);
  V resetVec = V::Zero(dim);
  resetMat(0, 0) = 0;
  flash->addLabel(labels.at(i));
  flash->setReset(Reset<Number>(resetMat, resetVec));
  flash->setAggregation(Aggregation::aggregation);

  wait->addTransition(std::move(flash));
  res.addTransition(*flash);

  // to adapt
  for (unsigned j = 0; j < labels.size(); ++j) {
    if (j != i) {
      Tpt toAdapt = new Transition<Number>(wait, adapt);
      resetMat = M::Identity(dim, dim);
      resetMat(0, 0) = Number(alpha);
      resetVec = V::Zero(dim);
      toAdapt->setReset(Reset<Number>(resetMat, resetVec));

      toAdapt->addLabel(labels.at(j));

      toAdapt->setAggregation(Aggregation::aggregation);

      wait->addTransition(toAdapt);
      res.addTransition(*toAdapt);
    }
  }

  // from adapt, regular
  Tpt fromAdaptRegular = new Transition<Number>(adapt, wait);
  guardConstraints = M::Zero(1, dim);
  guardConstraints(0, 0) = 1;
  guardConstants = V::Zero(1);
  guardConstants << Number(firingThreshold);
  fromAdaptRegular->setGuard(
      Condition<Number>{guardConstraints, guardConstants});
  resetMat = M::Identity(dim, dim);
  resetVec = V::Zero(dim);
  fromAdaptRegular->setReset(Reset<Number>(resetMat, resetVec));
  fromAdaptRegular->setAggregation(Aggregation::aggregation);
  fromAdaptRegular->setUrgent();

  adapt->addTransition(fromAdaptRegular);
  res.addTransition(*fromAdaptRegular);

  // from adapt, scale
  Tpt fromAdaptScale = new Transition<Number>(adapt, wait);
  guardConstraints = M::Zero(1, dim);
  guardConstraints(0, 0) = -1;
  guardConstants = V::Zero(1);
  guardConstants << Number(-firingThreshold);
  fromAdaptScale->setGuard(Condition<Number>{guardConstraints, guardConstants});
  fromAdaptScale->setAggregation(Aggregation::aggregation);
  fromAdaptScale->setUrgent();

  resetMat = M::Identity(dim, dim);
  resetMat(0, 0) = 0;
  resetVec = V::Zero(dim);
  fromAdaptScale->setReset(Reset<Number>(resetMat, resetVec));

  adapt->addTransition(fromAdaptScale);
  res.addTransition(*fromAdaptScale);

  return res;
}

template <typename Number>
HybridAutomaton<Number> createComponent3(unsigned i) {
  using HA = HybridAutomaton<Number>;
  using M = matrix_t<Number>;
  using V = vector_t<Number>;
  using Lpt = Location<Number> *;
  using Tpt = Transition<Number> *;
  using S = State_t<Number>;
  std::stringstream st;

  // result automaton
  HA res;

  // set up variables
  typename HybridAutomaton<Number>::variableVector vars;
  st << "x_" << i;
  vars.push_back(st.str());
  vars.push_back("x_t"); // t is the global clock for plotting
  vars.push_back("z");   // z is the shared variable
  res.setVariables(vars);
  st.str(std::string());
  unsigned dim = vars.size();

  // wait

  st << "wait_" << i;
  Location<Number> wait;
  wait->setName(st.str());
  M waitFlow = M::Zero(dim + 1, dim + 1);
  waitFlow(0, dim) = 1;
  waitFlow(1, dim) = 1; // time always advances at rate 1
  wait->setFlow(waitFlow);

  M initConstraints = M::Zero(6, 3);
  initConstraints << 1, 0, 0, -1, 0, 0, 0, 1, 0, 0, -1, 0, 0, 0, 1, 0, 0, -1;
  V initConstants = V::Zero(6);
  initConstants << 0, 0, 0, 0, 0, 0;

  S initialState;
  initialState.setLocation(wait);
  initialState.setSet(ConstraintSet<Number>(initConstraints, initConstants));
  res.addInitialState(initialState);

  M waitInvariant = M::Zero(2, dim);
  waitInvariant << 1, 0, 0, 0, 1, 0;
  V waitInvConsts = V::Zero(2);
  waitInvConsts << Number(firingThreshold), Number(globalTimeHorizon);
  wait->setInvariant(Condition<Number>{waitInvariant, waitInvConsts});
  res.addLocation(wait);

  // adapt
  // Lpt adapt = manager.create();
  // st.str(std::string());
  // st << "adapt_" << i;
  // adapt->setName(st.str());
  //
  //	//M adaptFlow = M::Zero(dim+1,dim+1);
  //	//adaptFlow(1,dim) = 1; // time always advances at rate 1
  //	//adapt->setFlow(adaptFlow);
  //
  // res.addLocation(adapt);

  // flash
  Location<Number> flash;
  st.str(std::string());
  st << "flash_" << i;
  flash->setName(st.str());

  M flashFlow = M::Zero(dim + 1, dim + 1);
  flashFlow(1, dim) = 1; // time always advances at rate 1
  flash->setFlow(flashFlow);

  // M flashInvariant = M::Zero(2,dim);
  // flashInvariant(0,0) = 1;
  // flashInvariant(1,0) = -1;
  // V flashInvConsts = V::Zero(2);
  // flash->setInvariant(Condition<Number>{flashInvariant, flashInvConsts});
  res.addLocation(flash);

  // transitions
  // to flash
  Tpt toFlash = new Transition<Number>(wait, flash);
  M guardConstraints = M::Zero(2, dim);
  guardConstraints(0, 0) = 1;
  guardConstraints(1, 0) = -1;
  V guardConstants = V::Zero(2);
  guardConstants << Number(firingThreshold), Number(-firingThreshold);
  toFlash->setGuard(Condition<Number>{guardConstraints, guardConstants});

  M resetMat = M::Identity(dim, dim);
  V resetVec = V::Zero(dim);
  resetMat(0, 0) = 0;
  resetMat(2, 2) = 0;
  resetVec(2) = 1;
  toFlash->setReset(Reset<Number>(resetMat, resetVec));
  toFlash->setAggregation(Aggregation::aggregation);
  // toFlash->setUrgent();

  wait->addTransition(toFlash);
  res.addTransition(toFlash);

  // to execFlash
  Tpt flashLoop = new Transition<Number>(flash, flash);
  guardConstraints = M::Zero(2, dim);
  guardConstraints(0, 2) = 1;
  guardConstraints(1, 2) = -1;
  guardConstants = V::Zero(2);
  guardConstants << 1, -1;
  flashLoop->setGuard(Condition<Number>{guardConstraints, guardConstants});

  resetMat = M::Identity(dim, dim);
  resetMat(2, 2) = 0;
  resetVec = V::Zero(dim);
  flashLoop->setReset(Reset<Number>(resetMat, resetVec));
  flashLoop->setUrgent();
  flashLoop->addLabel(Label{"flash"});
  flashLoop->setAggregation(Aggregation::aggregation);
  // flashLoop->setUrgent();

  flash->addTransition(flashLoop);
  res.addTransition(flashLoop);

  // back to wait
  /*
  Tpt reWait = new Transition<Number>(flash,wait);
  guardConstraints = M::Zero(2,dim);
  guardConstraints(0,2) = 1;
  guardConstraints(1,2) = -1;
  guardConstants = V::Zero(2);
  reWait->setGuard(Condition<Number>{guardConstraints,guardConstants});
  resetMat = M::Identity(dim,dim);
  resetVec = V::Zero(dim);
  reWait->addLabel({"return"});
  reWait->setReset(Reset<Number>(resetMat,resetVec));
  reWait->setUrgent();
  reWait->setAggregation(Aggregation::aggregation);

  flash->addTransition(reWait);
  res.addTransition(reWait);
  */

  // to adapt
  Tpt toAdapt = new Transition<Number>(wait, flash);
  guardConstraints = M::Zero(3, dim);
  guardConstraints(0, 2) = 1;
  guardConstraints(1, 2) = -1;
  guardConstraints(2, 0) = 1;
  guardConstants = V::Zero(3);
  guardConstants << 1, -1, Number(firingThreshold);
  toAdapt->setGuard(Condition<Number>{guardConstraints, guardConstants});
  resetMat = M::Identity(dim, dim);
  resetMat(0, 0) = Number(alpha);
  resetMat(2, 2) = 0;
  resetVec = V::Zero(dim);
  toAdapt->setReset(Reset<Number>(resetMat, resetVec));
  toAdapt->addLabel({"flash"});
  toAdapt->setAggregation(Aggregation::aggregation);
  // toAdapt->setUrgent();

  wait->addTransition(toAdapt);
  res.addTransition(toAdapt);

  // from adapt, regular
  Tpt fromAdaptRegular = new Transition<Number>(flash, wait);
  guardConstraints = M::Zero(3, dim);
  guardConstraints(0, 0) = 1;
  guardConstraints(1, 2) = 1;
  guardConstraints(2, 2) = -1;
  guardConstants = V::Zero(3);
  guardConstants << Number(firingThreshold), 0, 0;
  fromAdaptRegular->setGuard(
      Condition<Number>{guardConstraints, guardConstants});
  resetMat = M::Identity(dim, dim);
  resetVec = V::Zero(dim);
  fromAdaptRegular->setReset(Reset<Number>(resetMat, resetVec));
  fromAdaptRegular->addLabel(Label{"return"});
  fromAdaptRegular->setAggregation(Aggregation::aggregation);
  fromAdaptRegular->setUrgent();

  flash->addTransition(fromAdaptRegular);
  res.addTransition(fromAdaptRegular);

  // from adapt, scale
  Tpt fromAdaptScale = new Transition<Number>(flash, wait);
  guardConstraints = M::Zero(3, dim);
  guardConstraints(0, 0) = -1;
  guardConstraints(1, 2) = 1;
  guardConstraints(2, 2) = -1;
  guardConstants = V::Zero(3);
  guardConstants << Number(-firingThreshold), 0, 0;
  fromAdaptScale->setGuard(Condition<Number>{guardConstraints, guardConstants});
  fromAdaptScale->addLabel(Label{"return"});
  fromAdaptScale->setAggregation(Aggregation::aggregation);
  fromAdaptScale->setUrgent();

  resetMat = M::Identity(dim, dim);
  resetMat(0, 0) = 0;
  resetVec = V::Zero(dim);
  fromAdaptScale->setReset(Reset<Number>(resetMat, resetVec));

  flash->addTransition(fromAdaptScale);
  res.addTransition(fromAdaptScale);

  return res;
}

template <typename Number>
HybridAutomaton<Number> createComponent4(unsigned i,
                                         const std::vector<Label> &labels) {
  using HA = HybridAutomaton<Number>;
  using M = matrix_t<Number>;
  using V = vector_t<Number>;
  using Lpt = Location<Number> *;
  using Tpt = Transition<Number> *;
  using S = State_t<Number>;
  std::stringstream st;

  // result automaton
  HA res;

  // set up variables
  typename HybridAutomaton<Number>::variableVector vars;
  st << "x_" << i;
  vars.push_back(st.str());
  vars.push_back("x_t"); // t is the global clock for plotting
  res.setVariables(vars);
  st.str(std::string());
  unsigned dim = vars.size();

  // wait

  st << "wait_" << i;
  Location<Number> wait;
  wait->setName(st.str());
  M waitFlow = M::Zero(dim + 1, dim + 1); // both variables advance
  waitFlow(0, dim) = 1;
  waitFlow(1, dim) = 1;
  wait->setFlow(waitFlow);

  M waitInvariant = M::Zero(2, dim);
  waitInvariant(0, 0) = 1;
  waitInvariant(1, 1) = 1;
  V waitInvConsts = V::Zero(2);
  waitInvConsts << Number(firingThreshold), Number(globalTimeHorizon);
  wait->setInvariant(Condition<Number>{waitInvariant, waitInvConsts});
  res.addLocation(wait);

  // initial state
  M initConstraints = M::Zero(4, 2);
  initConstraints << 1, 0, -1, 0, 0, 1, 0, -1;
  V initConstants = V::Zero(4);
  initConstants << 0, 0, 0, 0;

  S initialState;
  initialState.setLocation(wait);
  initialState.setSet(ConstraintSet<Number>(initConstraints, initConstants));
  res.addInitialState(initialState);

  // adapt
  Location<Number> adapt;
  st.str(std::string());
  st << "adapt_" << i;
  adapt->setName(st.str());

  M adaptFlow = M::Zero(dim + 1, dim + 1);
  adaptFlow(1, dim) = 1; // time always advances at rate 1
  adapt->setFlow(adaptFlow);

  res.addLocation(adapt);

  // transitions
  // flash self loop
  Tpt flash = new Transition<Number>(wait, adapt);
  M guardConstraints = M::Zero(2, dim);
  guardConstraints(0, 0) = 1;
  guardConstraints(1, 0) = -1;
  V guardConstants = V::Zero(2);
  guardConstants << Number(firingThreshold), Number(-firingThreshold);
  flash->setGuard(Condition<Number>{guardConstraints, guardConstants});

  M resetMat = M::Identity(dim, dim);
  V resetVec = V::Zero(dim);
  resetMat(0, 0) = 0;
  flash->addLabel(labels.at(i));
  flash->setReset(Reset<Number>(resetMat, resetVec));
  flash->setAggregation(Aggregation::aggregation);
  // flash->setUrgent();

  wait->addTransition(flash);
  res.addTransition(flash);

  // to adapt
  for (unsigned j = 0; j < labels.size(); ++j) {
    if (j != i) {
      Tpt toAdapt = new Transition<Number>(wait, adapt);
      resetMat = M::Identity(dim, dim);
      resetMat(0, 0) = Number(alpha);
      resetVec = V::Zero(dim);
      toAdapt->setReset(Reset<Number>(resetMat, resetVec));

      toAdapt->addLabel(labels.at(j));

      toAdapt->setAggregation(Aggregation::aggregation);
      // toAdapt->setUrgent();

      wait->addTransition(toAdapt);
      res.addTransition(toAdapt);
    }
  }

  // from adapt, regular
  Tpt fromAdaptRegular = new Transition<Number>(adapt, wait);
  guardConstraints = M::Zero(1, dim);
  guardConstraints(0, 0) = 1;
  guardConstants = V::Zero(1);
  guardConstants << Number(firingThreshold);
  fromAdaptRegular->setGuard(
      Condition<Number>{guardConstraints, guardConstants});
  resetMat = M::Identity(dim, dim);
  resetVec = V::Zero(dim);
  fromAdaptRegular->setReset(Reset<Number>(resetMat, resetVec));
  fromAdaptRegular->setAggregation(Aggregation::aggregation);
  fromAdaptRegular->setUrgent();
  fromAdaptRegular->addLabel("return");

  adapt->addTransition(fromAdaptRegular);
  res.addTransition(fromAdaptRegular);

  // from adapt, scale
  Tpt fromAdaptScale = new Transition<Number>(adapt, wait);
  guardConstraints = M::Zero(1, dim);
  guardConstraints(0, 0) = -1;
  guardConstants = V::Zero(1);
  guardConstants << Number(-firingThreshold);
  fromAdaptScale->setGuard(Condition<Number>{guardConstraints, guardConstants});
  fromAdaptScale->setAggregation(Aggregation::aggregation);
  fromAdaptScale->setUrgent();
  fromAdaptScale->addLabel("return");

  resetMat = M::Identity(dim, dim);
  resetMat(0, 0) = 0;
  resetVec = V::Zero(dim);
  fromAdaptScale->setReset(Reset<Number>(resetMat, resetVec));

  adapt->addTransition(fromAdaptScale);
  res.addTransition(fromAdaptScale);

  return res;
}

int main(int argc, char **argv) {
  using Number = double;

  int componentCount = 0;
  componentCount = atoi(argv[1]);

  // settings to be used for flowstar format output
  ReachabilitySettings settings;
  settings.jumpDepth = 20;
  settings.timeBound = 110;
  settings.timeStep = 0.01;
  // settings.plotDimensions.push_back(std::vector<std::size_t>());
  // settings.plotDimensions[0].push_back(0);
  // settings.plotDimensions[0].push_back(componentCount+1);

  /*
  std::cout << "Create parallel composition for synchronization benchmark with "
  << componentCount << " components using a shared variable." << std::endl;

  HybridAutomaton<Number> composed_sync_sharedVar = createComponent1<Number>(1);
  for(int i = 2; i <= componentCount; ++i) {
          HybridAutomaton<Number> tmp = createComponent1<Number>(i);
          composed_sync_sharedVar = composed_sync_sharedVar || tmp;
          assert(composed_sync_sharedVar.isComposedOf(tmp));
  }

  composed_sync_sharedVar.reduce();

  settings.fileName = "sync_sharedVar";
  LockedFileWriter flowstar_sharedVar("sync_sharedVar.model");
  flowstar_sharedVar.clearFile();
  flowstar_sharedVar << toFlowstarFormat(composed_sync_sharedVar, settings);
  // create dot output.
  LockedFileWriter sharedVar_single("sync_sharedVarSingle.dot");
  sharedVar_single.clearFile();
  sharedVar_single << createComponent1<Number>(1).getDotRepresentation();
  LockedFileWriter sharedVar_res("sync_sharedVarComposed.dot");
  sharedVar_res.clearFile();
  sharedVar_res << composed_sync_sharedVar.getDotRepresentation();

  std::cout << "Automaton stats: " << std::endl <<
  composed_sync_sharedVar.getStatistics() << std::endl;
  */

  std::cout << "Create parallel composition for synchronization benchmark with "
            << componentCount << " components using label synchronization."
            << std::endl;

  std::vector<Label> labels;
  std::stringstream s;
  for (int i = 0; i < componentCount; ++i) {
    s.str("");
    s << "flash" << i;
    labels.emplace_back(s.str());
  }

  HybridAutomaton<Number> composed_sync_label =
      createComponent2<Number>(0, labels);
  for (int i = 1; i < componentCount; ++i) {
    HybridAutomaton<Number> tmp = createComponent2<Number>(i, labels);
    composed_sync_label = composed_sync_label || tmp;
    assert(composed_sync_label.isComposedOf(tmp));
  }
  composed_sync_label.reduce();
  settings.fileName = "sync_labels";
  LockedFileWriter flowstar_label("sync_labelSync.model");
  flowstar_label.clearFile();
  flowstar_label << toFlowstarFormat(composed_sync_label, settings);
  // create dot output.
  LockedFileWriter label_single("sync_labelSingle.dot");
  label_single.clearFile();
  label_single << createComponent2<Number>(
                      0, std::vector<Label>({Label("flash0")}))
                      .getDotRepresentation();
  LockedFileWriter label_res("sync_labelComposed.dot");
  label_res.clearFile();
  label_res << composed_sync_label.getDotRepresentation();

  std::cout << "Automaton stats: " << std::endl
            << composed_sync_label.getStatistics() << std::endl;

  std::cout << "Create parallel composition for synchronization benchmark with "
            << componentCount
            << " components using  optimized label synchronization."
            << std::endl;

  for (auto t = composed_sync_label.getTransitions().begin();
       t != composed_sync_label.getTransitions().end(); ++t) {
    if ((*t)->getSource()->getName().find("adapt") != std::string::npos &&
        (*t)->getTarget()->getName().find("adapt") != std::string::npos) {
      std::cout << "Remove edge " << (*t)->getSource()->getName() << " -> "
                << (*t)->getTarget()->getName() << std::endl;
      composed_sync_label.removeTransition(*t);
      t = composed_sync_label.getTransitions().begin();
    }
  }

  composed_sync_label.reduce();

  LockedFileWriter flowstar_label2("sync_labelSyncRed.model");
  flowstar_label2.clearFile();
  flowstar_label2 << toFlowstarFormat(composed_sync_label, settings);
  // create dot output.
  LockedFileWriter label_res2("sync_labelComposed2.dot");
  label_res2.clearFile();
  label_res2 << composed_sync_label.getDotRepresentation();

  std::cout << "Automaton stats: " << std::endl
            << composed_sync_label.getStatistics() << std::endl;

  /*
  std::cout << "Create parallel composition for synchronization benchmark with "
  << componentCount << " components using 2nd optimized label synchronization."
  << std::endl;
  */
  /*
  HybridAutomaton<Number> composed_sync_label_opt =
  createComponent4<Number>(0,labels); for(int i = 1; i < componentCount; ++i) {
          HybridAutomaton<Number> tmp = createComponent4<Number>(i,labels);
          composed_sync_label = composed_sync_label || tmp;
          assert(composed_sync_label.isComposedOf(tmp));
  }
  settings.fileName = "sync_labels";
  LockedFileWriter flowstar_label("sync_labelSync.model");
  flowstar_label.clearFile();
  flowstar_label << toFlowstarFormat(composed_sync_label,settings);
  // create dot output.
  LockedFileWriter label_single("sync_labelSingle.dot");
  label_single.clearFile();
  label_single <<
  createComponent2<Number>(0,std::vector<Label>({Label("flash0")})).getDotRepresentation();
  LockedFileWriter label_res("sync_labelComposed.dot");
  label_res.clearFile();
  label_res << composed_sync_label.getDotRepresentation();

  std::cout << "Automaton stats: " << std::endl <<
  composed_sync_label.getStatistics() << std::endl;
  */
  /*
  std::cout << "Create parallel composition for synchronization benchmark with "
  << componentCount << " components using a reduced version with a shared
  variable." << std::endl;

  HybridAutomaton<Number> composed_sync_sharedVar_2states =
  createComponent3<Number>(1); for(int i = 2; i <= componentCount; ++i) {
          HybridAutomaton<Number> tmp = createComponent3<Number>(i);
          composed_sync_sharedVar_2states = composed_sync_sharedVar_2states ||
  tmp; assert(composed_sync_sharedVar_2states.isComposedOf(tmp));
  }

  composed_sync_sharedVar_2states.reduce();

  settings.fileName = "sync_sharedVar2";
  LockedFileWriter flowstar_sharedVarRed("sync_sharedVar_2_states.model");
  flowstar_sharedVarRed.clearFile();
  flowstar_sharedVarRed <<
  toFlowstarFormat(composed_sync_sharedVar_2states,settings);
  // create dot output.
  LockedFileWriter sharedVarReduced_single("sync_sharedVarReducedSingle.dot");
  sharedVarReduced_single.clearFile();
  sharedVarReduced_single << createComponent3<Number>(1).getDotRepresentation();
  LockedFileWriter sharedVarReduced_res("sync_sharedVarReducedComposed.dot");
  sharedVarReduced_res.clearFile();
  sharedVarReduced_res <<
  composed_sync_sharedVar_2states.getDotRepresentation();

  std::cout << "Automaton stats: " << std::endl <<
  composed_sync_sharedVar_2states.getStatistics() << std::endl;
  */

  // for testing
  // auto haTuple = parseFlowstarFile<double>(std::string("composed.model"));

  return 0;
}
