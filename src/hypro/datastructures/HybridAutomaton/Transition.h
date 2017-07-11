/*
 * Class that describes one transition of a hybrid automaton.
 * File:   transition.h
 * Author: stefan & ckugler
 *
 * Created on April 30, 2014, 9:06 AM
 */

#pragma once

#include "Condition.h"
#include "Location.h"
#include "Reset.h"
#include "lib/utils/types.h"
#include <carl/interval/Interval.h>
#include <hypro/types.h>

namespace hydra
{
enum Aggregation { none, boxAgg, parallelotopeAgg };

class Location;

class Transition
{
  private:
    Location* mSource = nullptr;
    Location* mTarget = nullptr;
    Condition mGuard;
    Reset mReset;
    Aggregation mAggregationSetting = Aggregation::none;
    bool mUrgent = false;

  public:

    Transition() = default;
    Transition(const Transition& orig) = default;
    Transition(Transition&& orig) = default;
    Transition& operator=(const Transition& orig) = default;
    Transition& operator=(Transition&& orig) = default;
    ~Transition() {}

    Transition(Location* source, Location* target)
        : mSource(source), mTarget(target), mGuard(), mReset(), mAggregationSetting(), mUrgent(false)
    {}

    Transition(Location* source, Location* target, const Condition& guard, const Reset& reset)
        : mSource(source), mTarget(target), mGuard(guard), mReset(reset), mAggregationSetting(), mUrgent(false)
    {}

    /**
     * Getter & Setter
     */
    Location* getSource() const { return mSource; }
    Location* getTarget() const { return mTarget; }
    const Condition& getGuard() const { return mGuard; }
    const Reset& getReset() const { return mReset; }
    Aggregation getAggregation() const { return mAggregationSetting; }
    bool isUrgent() const { return mUrgent; }

    void setSource(Location* source) { mSource = source; }
    void setTarget(Location* target) { mTarget = target; }
    void setGuard(const Condition& guard) { mGuard = guard; }
    void setReset(const Reset& val) { mReset = val; }
    void setAggregation(Aggregation agg) { mAggregationSetting = agg; }
    void setUrgent(bool urgent = true) { mUrgent = urgent; }

    friend std::ostream& operator<<(std::ostream& ostr, const Transition& t);
    friend bool operator==(const Transition& lhs, const Transition& rhs);
};
}  // namespace hydra
