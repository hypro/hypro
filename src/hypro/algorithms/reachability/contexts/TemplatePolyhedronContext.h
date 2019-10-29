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

  public:

  	TemplatePolyhedronContext() = default;
  	TemplatePolyhedronContext(
  		const std::shared_ptr<Task<State>>& t,
	    const Strategy<State>& strat,
	    WorkQueue<std::shared_ptr<Task<State>>>* localQueue,
	    WorkQueue<std::shared_ptr<Task<State>>>* localCEXQueue,
	    std::vector<PlotData<State>>* localSegments,
	    ReachabilitySettings &settings) 
  		: LTIContext<State>(t,strat,localQueue,localCEXQueue,localSegments,settings)
  	{}
        
	~TemplatePolyhedronContext(){}
  	
	void execBeforeFirstSegment() override;

  	void firstSegment() override;
    
  	void applyContinuousEvolution() override;

  private:

    TemplatePolyhedron<Number> createTemplateContent(const TemplatePolyhedron<Number>& tpoly);

};


} // namespace hypro

#include "TemplatePolyhedronContext.tpp"