#pragma once

//#include "lib/EventSystem/EventHandler.h"
#include "../../../datastructures/reachability/StrategyNode.h"
#include "../../../datastructures/reachability/Task.h"
#include "../../../datastructures/reachability/workQueue/WorkQueue.h"
#include "../../../types.h"
#include "../../../util/plotting/PlotData.h"
#include "../../../datastructures/reachability/Settings.h"
#include <atomic>
#include <boost/any.hpp>
#include <mutex>

namespace hypro
{
template <class Workable, typename State>
class IWorker
{
  using Number = typename State::NumberType;
  public:
    /**
     * Constructor responsible for setting the respective EventHandler
     * and WorkQueue.
     */
    IWorker(const ReachabilitySettings &settings) :
      mSettings(settings)
    {}

    virtual ~IWorker() {}
    /**
     * abstract definition of the function responsible for
     * Flowpipe computation. It is important that the Workable class
     * has a constructor taking a Flowpipe! this way new Workable Elements
     * can be constructed, which then will be added to the WorkQueue.
     */
    virtual void processTask(const Workable& w,
    						 const Strategy<State>& strategy,
    						 WorkQueue<std::shared_ptr<Task<State>>>& localQueue,
    						 WorkQueue<std::shared_ptr<Task<State>>>& localCEXQueue,
    						 std::vector<PlotData<Number>>* localSegments) = 0;


  protected:
    ReachabilitySettings mSettings;
};

}  // namespace hypro

