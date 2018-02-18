#include "datastructures/HybridAutomaton/HybridAutomaton.h"
#include "datastructures/HybridAutomaton/output/Flowstar.h"
#include "util/multithreading/Filewriter.h"
#include "parser/antlr4-flowstar/ParserWrapper.h"
#include <iostream>

using namespace hypro;

static const int firingThreshold = 1;
static const double alpha = 1.1;

template<typename Number>
HybridAutomaton<Number> createComponent1(unsigned i) {
	using HA = HybridAutomaton<Number>;
	using M = matrix_t<Number>;
	using V = vector_t<Number>;
	using Lpt = Location<Number>*;
	using Tpt = Transition<Number>*;
	using S = State_t<Number>;
	LocationManager<Number>& manager = LocationManager<Number>::getInstance();
	std::stringstream st;

	// result automaton
	HA res;

	// set up variables
	typename HybridAutomaton<Number>::variableVector vars;
	st << "x_" << i;
	vars.push_back(st.str());
	vars.push_back("x_t"); // t is the global clock for plotting
	vars.push_back("z"); // z is the shared variable
	res.setVariables(vars);
	st.str(std::string());
	unsigned dim = vars.size();

	// wait

	st << "wait_" << i;
	Lpt wait = manager.create();
	wait->setName(st.str());
	M waitFlow = M::Zero(dim+1,dim+1);
	waitFlow(0,dim) = 1;
	waitFlow(1,dim) = 1; // time always advances at rate 1
	wait->setFlow(waitFlow);

	M initConstraints = M::Zero(6,3);
	initConstraints << 1,0,0,-1,0,0,0,1,0,0,-1,0,0,0,1,0,0,-1;
	V initConstants = V::Zero(6);
	initConstants << 0,0,0,0,0,0;

	S initialState;
	initialState.setLocation(wait);
	initialState.setSet(ConstraintSet<Number>(initConstraints,initConstants));
	res.addInitialState(initialState);

	M waitInvariant = M::Zero(1,dim);
	waitInvariant << 1,0,0;
	V waitInvConsts = V::Zero(1);
	waitInvConsts << Number(firingThreshold);
	wait->setInvariant(Condition<Number>{waitInvariant, waitInvConsts});
	res.addLocation(wait);

	// adapt
	Lpt adapt = manager.create();
	st.str(std::string());
	st << "adapt_" << i;
	adapt->setName(st.str());

	M adaptFlow = M::Zero(dim+1,dim+1);
	adaptFlow(1,dim) = 1; // time always advances at rate 1
	adapt->setFlow(adaptFlow);

	//M adaptInvariant = M::Zero(2,dim);
	//adaptInvariant(0,0) = 1;
	//adaptInvariant(1,0) = -1;
	//V adaptInvConsts = V::Zero(2);
	//adapt->setInvariant(Condition<Number>{adaptInvariant, adaptInvConsts});
	res.addLocation(adapt);

	// flash
	Lpt flash = manager.create();
	st.str(std::string());
	st << "flash_" << i;
	flash->setName(st.str());

	M flashFlow = M::Zero(dim+1,dim+1);
	flashFlow(1,dim) = 1; // time always advances at rate 1
	flash->setFlow(flashFlow);

	M flashInvariant = M::Zero(2,dim);
	flashInvariant(0,0) = 1;
	flashInvariant(1,0) = -1;
	V flashInvConsts = V::Zero(2);
	flash->setInvariant(Condition<Number>{flashInvariant, flashInvConsts});
	res.addLocation(flash);

	// execFlash
	/*
	Lpt execFlash = manager.create();
	st.str(std::string());
	st << "execFlash_" << i;
	execFlash->setName(st.str());

	M execFlashFlow = M::Zero(dim+1,dim+1);
	execFlash->setFlow(execFlashFlow);

	M execFlashInvariant = M::Zero(2,dim);
	execFlashInvariant(0,0) = 1;
	execFlashInvariant(1,0) = -1;
	V execFlashInvConsts = V::Zero(2);
	execFlash->setInvariant(Condition<Number>{execFlashInvariant, execFlashInvConsts});
	res.addLocation(execFlash);
	*/

	// transitions
	// to flash
	Tpt toFlash = new Transition<Number>(wait,flash);
	M guardConstraints = M::Zero(2,dim);
	guardConstraints(0,0) = 1;
	guardConstraints(1,0) = -1;
	V guardConstants = V::Zero(2);
	guardConstants << Number(firingThreshold), Number(-firingThreshold);
	toFlash->setGuard(Condition<Number>{guardConstraints,guardConstants});

	M resetMat = M::Identity(dim,dim);
	V resetVec = V::Zero(dim);
	resetMat(0,0) = 0;
	resetMat(2,2) = 0;
	resetVec(2) = 1;
	toFlash->setReset(Reset<Number>(resetMat,resetVec));
	toFlash->setAggregation(Aggregation::parallelotopeAgg);
	toFlash->setUrgent();

	wait->addTransition(toFlash);
	res.addTransition(toFlash);

	// to execFlash
	Tpt flashLoop = new Transition<Number>(flash,flash);
	guardConstraints = M::Zero(2,dim);
	guardConstraints(0,2) = 1;
	guardConstraints(1,2) = -1;
	guardConstants = V::Zero(2);
	guardConstants << 1,-1;
	flashLoop->setGuard(Condition<Number>{guardConstraints,guardConstants});

	resetMat = M::Identity(dim,dim);
	resetMat(2,2) = 0;
	resetVec = V::Zero(dim);
	flashLoop->setReset(Reset<Number>(resetMat,resetVec));
	flashLoop->setUrgent();
	flashLoop->addLabel(Label{"flash"});
	flashLoop->setAggregation(Aggregation::parallelotopeAgg);
	flashLoop->setUrgent();

	flash->addTransition(flashLoop);
	res.addTransition(flashLoop);

	// back to flash
	/*
	Tpt reFlash = new Transition<Number>(execFlash,flash);

	resetMat = M::Identity(dim,dim);
	resetVec = V::Zero(dim);
	reFlash->setReset(Reset<Number>(resetMat,resetVec));
	reFlash->setUrgent();

	execFlash->addTransition(reFlash);
	res.addTransition(reFlash);
	*/

	// back to wait
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
	reWait->setAggregation(Aggregation::parallelotopeAgg);

	flash->addTransition(reWait);
	res.addTransition(reWait);

	// to adapt
	Tpt toAdapt = new Transition<Number>(wait,adapt);
	guardConstraints = M::Zero(3,dim);
	guardConstraints(0,2) = 1;
	guardConstraints(1,2) = -1;
	guardConstraints(2,0) = 1;
	guardConstants = V::Zero(3);
	guardConstants << 1,-1,Number(firingThreshold);
	toAdapt->setGuard(Condition<Number>{guardConstraints,guardConstants});
	resetMat = M::Identity(dim,dim);
	resetMat(0,0) = Number(alpha);
	resetMat(2,2) = 0;
	resetVec = V::Zero(dim);
	toAdapt->setReset(Reset<Number>(resetMat,resetVec));
	toAdapt->addLabel({"flash"});
	toAdapt->setAggregation(Aggregation::parallelotopeAgg);
	toAdapt->setUrgent();

	wait->addTransition(toAdapt);
	res.addTransition(toAdapt);

	// from adapt, regular
	Tpt fromAdaptRegular = new Transition<Number>(adapt,wait);
	guardConstraints = M::Zero(1,dim);
	guardConstraints(0,0) = 1;
	guardConstants = V::Zero(1);
	guardConstants << Number(firingThreshold);
	fromAdaptRegular->setGuard(Condition<Number>{guardConstraints,guardConstants});
	resetMat = M::Identity(dim,dim);
	resetVec = V::Zero(dim);
	fromAdaptRegular->setReset(Reset<Number>(resetMat,resetVec));
	fromAdaptRegular->addLabel(Label{"return"});
	fromAdaptRegular->setAggregation(Aggregation::parallelotopeAgg);
	fromAdaptRegular->setUrgent();

	adapt->addTransition(fromAdaptRegular);
	res.addTransition(fromAdaptRegular);

	// from adapt, scale
	Tpt fromAdaptScale = new Transition<Number>(adapt,flash);
	guardConstraints = M::Zero(1,dim);
	guardConstraints(0,0) = -1;
	guardConstants = V::Zero(1);
	guardConstants << Number(-firingThreshold);
	fromAdaptScale->setGuard(Condition<Number>{guardConstraints,guardConstants});
	//fromAdaptScale->addLabel(Label{"flash"});
	fromAdaptScale->setAggregation(Aggregation::parallelotopeAgg);
	fromAdaptScale->setUrgent();

	resetMat = M::Identity(dim,dim);
	resetMat(0,0) = 0;
	resetVec = V::Zero(dim);
	fromAdaptScale->setReset(Reset<Number>(resetMat,resetVec));

	adapt->addTransition(fromAdaptScale);
	res.addTransition(fromAdaptScale);

	return res;
}


int main(int argc, char** argv) {
	using Number = double;

	int componentCount = 0;
	char* p;
	componentCount = strtol(argv[2], &p, 10);

	std::cout << "Create parallel composition for synchronization benchmark with " << componentCount << " components." << std::endl;

	HybridAutomaton<Number> ha1 = createComponent1<Number>(1);
	HybridAutomaton<Number> ha2 = createComponent1<Number>(2);
	HybridAutomaton<Number> ha3 = createComponent1<Number>(3);
	HybridAutomaton<Number> composed = ha1||ha2;
	composed = composed||ha3;

	assert(composed.isComposedOf(ha1));
	assert(composed.isComposedOf(ha2));
	assert(composed.isComposedOf(ha3));

	//std::cout << "################################################" << std::endl;
	//std::cout << "Result: " << std::endl << composed << std::endl;

	LockedFileWriter out{"parallelHa.dot"};
	out.clearFile();
	out << composed.getDotRepresentation();

	LockedFileWriter out2{"singleHa.dot"};
	out2.clearFile();
	out2 << ha1.getDotRepresentation();

	LockedFileWriter flowstar("composed.model");
	flowstar.clearFile();
	flowstar << toFlowstarFormat(composed);

	// for testing
	auto haTuple = parseFlowstarFile<double>(std::string("composed.model"));

	return 0;
}
