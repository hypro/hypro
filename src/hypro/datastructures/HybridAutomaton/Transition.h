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
#include <carl/interval/Interval.h>

namespace hypro
{
enum Aggregation { none, boxAgg, parallelotopeAgg };

template<typename Number>
class Location;

template<typename Number>
class Transition
{
  private:
    Location<Number>* mSource = nullptr;
    Location<Number>* mTarget = nullptr;
    Condition<Number> mGuard;
    Reset<Number> mReset;
    Aggregation mAggregationSetting = Aggregation::none;
    bool mUrgent = false;
    Number mTriggerTime = Number(-1);

  public:

    Transition() = default;
    Transition(const Transition<Number>& orig) = default;
    Transition(Transition<Number>&& orig) = default;
    Transition& operator=(const Transition<Number>& orig) = default;
    Transition& operator=(Transition<Number>&& orig) = default;
    ~Transition() {}

    Transition(Location<Number>* source, Location<Number>* target)
        : mSource(source), mTarget(target), mGuard(), mReset(), mAggregationSetting(), mUrgent(false)
    {}

    Transition(Location<Number>* source, Location<Number>* target, const Condition<Number>& guard, const Reset<Number>& reset)
        : mSource(source), mTarget(target), mGuard(guard), mReset(reset), mAggregationSetting(), mUrgent(false)
    {}

    /**
     * Getter & Setter
     */
    Location<Number>* getSource() const { return mSource; }
    Location<Number>* getTarget() const { return mTarget; }
    const Condition<Number>& getGuard() const { return mGuard; }
    const Reset<Number>& getReset() const { return mReset; }
    Aggregation getAggregation() const { return mAggregationSetting; }
    Number getTriggerTime() const { return mTriggerTime; }
    bool isUrgent() const { return mUrgent; }
    bool isTimeTriggered() const { return mTriggerTime >= 0; }

    void setSource(Location<Number>* source) { mSource = source; }
    void setTarget(Location<Number>* target) { mTarget = target; }
    void setGuard(const Condition<Number>& guard) { mGuard = guard; }
    void setReset(const Reset<Number>& val) { mReset = val; }
    void setAggregation(Aggregation agg) { mAggregationSetting = agg; }
    void setUrgent(bool urgent = true) { mUrgent = urgent; }
    void setTriggerTime(Number t) { mTriggerTime = t; }

    friend std::ostream& operator<<(std::ostream& ostr, const Transition<Number>& t) {
		#ifdef HYPRO_LOGGING
	    ostr << "transition(" << std::endl
	          << "\t Source = " << t.getSource()->getId() << std::endl
	          << "\t Target = " << t.getTarget()->getId() << std::endl
	          << "\t urgent = " << t.isUrgent() << std::endl
	          << "\t Guard = " << t.getGuard() << std::endl
	          << "\t Reset = " << t.getReset() << std::endl
	          << ")";
		#endif
	    return ostr;
    }

    friend bool operator==(const Transition<Number>& lhs, const Transition<Number>& rhs) {
    	if( (*lhs.mSource != *rhs.mSource) ||
			(*lhs.mTarget != *rhs.mTarget) ||
			(lhs.mUrgent != rhs.mUrgent) ||
			(lhs.mGuard != rhs.mGuard) ||
			(lhs.mReset != rhs.mReset) ) {
			return false;
		}

		return true;
    }
};
}  // namespace hypro
