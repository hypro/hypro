#pragma once

//#include "lib/EventSystem/EventHandler.h"
#include "../../../datastructures/reachability/StrategyNode.h"
#include "../../../datastructures/reachability/Task.h"
#include "../../../datastructures/reachability/WorkQueue.h"
#include "../../../types.h"
#include "../../../util/PlotData.h"
#include "../../../datastructures/reachability/Settings.h"
#include <atomic>
#include <boost/any.hpp>
#include <mutex>

namespace hypro
{
template <class Workable, typename Number>
class IWorker
{
  public:
    /**
     * Constructor responsible for setting the respective EventHandler
     * and WorkQueue.
     */
    IWorker(const ReachabilitySettings<tNumber> &settings) :
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
    						 const std::vector<StrategyNode>& strategy,
    						 WorkQueue<std::shared_ptr<Task<Number>>>& localQueue,
    						 WorkQueue<std::shared_ptr<Task<Number>>>& localCEXQueue,
    						 std::vector<PlotData<Number>>* localSegments) = 0;


  protected:
    ReachabilitySettings<tNumber> mSettings;
};

}  // namespace hydra

#include "IWorker.tpp"
