#include "datastructures/HybridAutomaton/HybridAutomaton.h"
#include <iostream>

using namespace hypro;

static const int firingThreshold = 1;
static const double alpha = 0.1;

template<typename Number>
HybridAutomaton<Number> createComponent1(unsigned i) {
	HybridAutomaton<Number> res;
	std::stringstream st;
	typename HybridAutomaton<Number>::variableVector vars;
	st << "x_" << i;
	vars.push_back(st.str());
	res.setVariables(vars);
	st.str(std::string());
	LocationManager<Number>& manager = LocationManager<Number>::getInstance();

	// wait

	st << "wait_" << i;
	Location<Number>* wait = manager.create();
	wait->setName(st.str());
	matrix_t<Number> waitFlow = matrix_t<Number>::Ones(1,1);
	wait->setFlow(waitFlow);

	matrix_t<Number> waitInvariant = matrix_t<Number>::Ones(1,1);
	vector_t<Number> waitInvConsts = vector_t<Number>::Zero(1);
	waitInvConsts << Number(firingThreshold);
	wait->setInvariant(Condition<Number>{waitInvariant, waitInvConsts});
	res.addLocation(wait);

	// adapt
	Location<Number>* adapt = manager.create();
	st.str(std::string());
	st << "adapt_" << i;
	adapt->setName(st.str());

	matrix_t<Number> adaptFlow = matrix_t<Number>::Zero(1,1);
	adapt->setFlow(adaptFlow);

	matrix_t<Number> adaptInvariant = matrix_t<Number>::Ones(2,1);
	adaptInvariant << 1,-1;
	vector_t<Number> adaptInvConsts = vector_t<Number>::Zero(2);
	adaptInvConsts << 0,0;
	adapt->setInvariant(Condition<Number>{adaptInvariant, adaptInvConsts});
	res.addLocation(adapt);

	// transitions
	// self-loop
	Transition<Number>* loop = new Transition<Number>(wait,wait);
	matrix_t<Number> guardConstraints = matrix_t<Number>::Ones(2,1);
	vector_t<Number> guardConstants = vector_t<Number>::Zero(2);
	guardConstraints << 1,-1;
	guardConstants << Number(firingThreshold), Number(-firingThreshold);
	loop->setGuard(Condition<Number>{guardConstraints,guardConstants});

	matrix_t<Number> resetMat = matrix_t<Number>::Zero(1,1);
	vector_t<Number> resetVec = vector_t<Number>::Zero(1);
	loop->setReset(Reset<Number>(resetMat,resetVec));

	wait->addTransition(loop);
	res.addTransition(loop);

	// to adapt
	Transition<Number>* toAdapt = new Transition<Number>(wait,adapt);

	resetMat = matrix_t<Number>::Zero(1,1);
	resetMat << Number(alpha);
	resetVec = vector_t<Number>::Zero(1);
	toAdapt->setReset(Reset<Number>(resetMat,resetVec));

	wait->addTransition(toAdapt);
	res.addTransition(toAdapt);

	// from adapt, regular
	Transition<Number>* fromAdaptRegular = new Transition<Number>(adapt,wait);
	guardConstraints = matrix_t<Number>::Ones(1,1);
	guardConstants = vector_t<Number>::Zero(1);
	guardConstants << Number(firingThreshold);
	fromAdaptRegular->setGuard(Condition<Number>{guardConstraints,guardConstants});

	adapt->addTransition(fromAdaptRegular);
	res.addTransition(fromAdaptRegular);

	// from adapt, scale
	Transition<Number>* fromAdaptScale = new Transition<Number>(adapt,wait);
	guardConstraints = matrix_t<Number>::Ones(1,1);
	guardConstants = vector_t<Number>::Zero(1);
	guardConstraints << -1;
	guardConstants << Number(firingThreshold);
	fromAdaptScale->setGuard(Condition<Number>{guardConstraints,guardConstants});

	resetMat = matrix_t<Number>::Zero(1,1);
	resetVec = vector_t<Number>::Zero(1);
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
	HybridAutomaton<Number> composed = ha1||ha2;

	std::cout << "Result: " << std::endl << composed << std::endl;

	return 0;
}
