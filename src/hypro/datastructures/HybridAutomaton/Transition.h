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
#include "Label.h"

namespace hypro
{
enum Aggregation { none, boxAgg, parallelotopeAgg };

template<typename Number>
class Location;

/**
 * @brief      Class for transition.
 * @tparam     Number  The used number type.
 */
template<typename Number>
class Transition
{
  private:
    Location<Number>* mSource = nullptr; /// Pointer to the source location.
    Location<Number>* mTarget = nullptr; /// Pointer to the target location.
    Condition<Number> mGuard; /// Guard condition enabling the transition if satisfied.
    Reset<Number> mReset; /// Reset function.
    Aggregation mAggregationSetting = Aggregation::none; /// Aggregation settings.
    bool mUrgent = false; /// Flag if transition is urgent.
    Number mTriggerTime = Number(-1); /// Trigger-time: if positive acts as an additional guard.
    std::set<Label> mLabels;

  public:

  	/**
  	 * @brief      Default constructor.
  	 */
    Transition() = default;

    /**
     * @brief      Copy constructor.
     * @param[in]  orig  The original.
     */
    Transition(const Transition<Number>& orig) = default;

    /**
     * @brief      Move constructor.
     * @param[in]  orig  The original.
     */
    Transition(Transition<Number>&& orig) = default;

    /**
     * @brief      Copy assignment operator.
     * @param[in]  orig  The original.
     * @return     A copy of the passed transition.
     */
    Transition& operator=(const Transition<Number>& orig) = default;

    /**
     * @brief      Move assignment operator.
     * @param[in]  orig  The original.
     * @return     Result.
     */
    Transition& operator=(Transition<Number>&& orig) = default;

    /**
     * @brief      Destroys the object.
     */
    ~Transition() {}

    /**
     * @brief      Constructor from source and target location.
     * @param      source  The source
     * @param      target  The target
     */
    Transition(Location<Number>* source, Location<Number>* target)
        : mSource(source), mTarget(target), mGuard(), mReset(), mAggregationSetting(), mUrgent(false)
    {}

    /**
     * @brief      Full constructor for basic transition.
     * @param      source  The source.
     * @param      target  The target.
     * @param[in]  guard   The guard.
     * @param[in]  reset   The reset.
     */
    Transition(Location<Number>* source, Location<Number>* target, const Condition<Number>& guard, const Reset<Number>& reset)
        : mSource(source), mTarget(target), mGuard(guard), mReset(reset), mAggregationSetting(), mUrgent(false)
    {}


    Location<Number>* getSource() const { assert( mSource != nullptr ); return mSource; }
    Location<Number>* getTarget() const { assert( mTarget != nullptr ); return mTarget; }
    const Condition<Number>& getGuard() const { return mGuard; }
    const Reset<Number>& getReset() const { return mReset; }
    Aggregation getAggregation() const { return mAggregationSetting; }
    Number getTriggerTime() const { return mTriggerTime; }
    bool isUrgent() const { return mUrgent; }
    bool isTimeTriggered() const { return mTriggerTime >= 0; }
    std::set<Label> getLabels() const { return mLabels; }

    void setSource(Location<Number>* source) { mSource = source; }
    void setTarget(Location<Number>* target) { mTarget = target; }
    void setGuard(const Condition<Number>& guard) { mGuard = guard; }
    void setReset(const Reset<Number>& val) { mReset = val; }
    void setAggregation(Aggregation agg) { mAggregationSetting = agg; }
    void setUrgent(bool urgent = true) { mUrgent = urgent; }
    void setTriggerTime(Number t) { mTriggerTime = t; }
    void setLabels(const std::set<Label>& labels) { mLabels = labels; }

    /**
     * @brief      Outstream operator.
     * @param      ostr  The outstream.
     * @param[in]  t     The transition.
     * @return     Reference to the outstream.
     */
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

    /**
     * @brief      Equality comparison operator.
     * @param[in]  lhs   The left hand side.
     * @param[in]  rhs   The right hand side.
     * @return     True if both transitions are equal, false otherwise.
     */
    friend bool operator==(const Transition<Number>& lhs, const Transition<Number>& rhs) {
    	if( (*lhs.mSource != *rhs.mSource) ||
			(*lhs.mTarget != *rhs.mTarget) ||
			(lhs.mUrgent != rhs.mUrgent) ||
			(lhs.mGuard != rhs.mGuard) ||
			(lhs.mReset != rhs.mReset) ||
      (lhs.mLabels != rhs.mLabels)) {
			return false;
		}

		return true;
    }
};
}  // namespace hypro
