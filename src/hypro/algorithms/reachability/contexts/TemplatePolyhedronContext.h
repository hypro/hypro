/*
 *	TemplatePolyhedronContext.h
 *
 *	The overall reachability algorithm for template polyhedra according to the paper
 *	Sankaranarayanan 2008. 
 *	NOTE: The state template here is guaranteed to have the TemplatePolyhedron class
 *	as underlying set representation.
 *
 *	@author Phillip Tse
 *	@date 17.9.2019
 */

#pragma once

#include "LTIContext.h"
#include "Exceptions.h"
#include "../handlers/IHandler.h"
#include "../handlers/HandlerFactory.h"
#include "../workers/IWorker.h"
#include "../../../datastructures/reachability/workQueue/WorkQueue.h"
#include "../../../datastructures/reachability/Settings.h"
#include "../../../datastructures/reachability/SettingsProvider.h"
#include "../../../datastructures/reachability/Strategy.h"
#include "../../../datastructures/reachability/Task.h"
#include "../../../datastructures/reachability/timing/EventTimingContainer.h"
#include "../../../datastructures/HybridAutomaton/decomposition/DecisionEntity.h"
#include "../../../util/logging/Logger.h"
#include "../../../util/plotting/PlotData.h"

namespace hypro {

template<typename State>
class TemplatePolyhedronContext : public LTIContext<State> {

	using Number = typename State::NumberType;

  private:

  	//Used for minimization of various functions during location invariant strengthening
  	Optimizer<Number> mOptimizer;
  	//The result of the location invariant strengthening. Is passed to TPolyFirstSegmentHandler and TPolyTimeEvolutionHandler.
  	vector_t<Number> mRelaxedInvariant;

  public:

  	TemplatePolyhedronContext() = delete;
  	TemplatePolyhedronContext(
  		const std::shared_ptr<Task<State>>& t,
	    const Strategy<State>& strat,
	    WorkQueue<std::shared_ptr<Task<State>>>* localQueue,
	    WorkQueue<std::shared_ptr<Task<State>>>* localCEXQueue,
	    Flowpipe<State>& localSegments,
	    ReachabilitySettings &settings) 
  		: LTIContext<State>(t,strat,localQueue,localCEXQueue,localSegments,settings),
  		  mOptimizer(Optimizer<Number>())
  	{}
        
	~TemplatePolyhedronContext(){}
  	
  	//Changes template matrix content according to setting and then call locationInvariantStrengthening
	void execBeforeFirstSegment() override;

	//First Segment computation after Sankaranarayanan
  	void firstSegment() override;
    
    //Continuous Evolution after Sankaranarayanan
  	void applyContinuousEvolution() override;

    //Computes the gradient of a multivariate but linear function linearFct
    vector_t<Number> gradientOfLinearFct(const vector_t<Number>& linearFct);

    //Computes the lie derivative given a direction and an affine vector field (aka the flow)
    //NOTE: Usually the lie derivative also works with non linear fcts, but since we cannot parse nonlinear functions yet,
    //we will only use a simple selfwritten derivation function for linear multivariate functions
    //DETAIL: The input vector dir is interpreted as a function, for example if dir = (3 2 -1) then dir is interpreted as 3x + 2y - z, 
    //since no constants are allowed.
    //The gradient of 3x + 2y - z is therefore the vector (3 2 -1), which is the result that will be returned.
    std::pair<vector_t<typename State::NumberType>,typename State::NumberType> lieDerivative(const vector_t<Number>& dir);

    //Conducts the location invariant strengthening method from Sankranarayanan 2008.
    //Only works for closed invariants where the normals point into the inside. 
    //Until it converges, a relaxed bound for the invariants is being computed, thereby shrinking in the region of possible values (strengthening).
    //Returns the relaxed bounds for the invariants.
    vector_t<Number> locationInvariantStrengthening(const TemplatePolyhedron<Number>& invTPpoly, const vector_t<Number>& initialOffsets);
    
    //Adds invariants, guards and bad states to the template matrix according the the setting
    TemplatePolyhedron<Number> createTemplateContent(const TemplatePolyhedron<Number>& tpoly);

    //Tests whether the given tpoly is a positive invariant and therefore admissible for location invariant strengthening
    bool isPositiveInvariant(const TemplatePolyhedron<Number>& tpoly, const vector_t<Number>& invVector);
};

} // namespace hypro

#include "TemplatePolyhedronContext.tpp"