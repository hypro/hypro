/**
 * @brief General context interface to set up a reachability worker.
 *
 */

#pragma once

namespace hypro {

class IContext {
  public:
	// virtual ~IContext(){}

	virtual void execOnStart() {}

	virtual void execBeforeFirstSegment() {}

	virtual void firstSegment() = 0;

	virtual void execAfterFirstSegment() {}

	virtual void execBeforeCheckInvariant() {}

	virtual void checkInvariant() = 0;

	virtual void execAfterCheckInvariant() {}

	virtual void execBeforeIntersectBadStates() {}

	virtual void intersectBadStates() = 0;

	virtual void execAfterIntersectBadStates() {}

	virtual void execBeforeLoop() {}

	virtual bool doneCondition() = 0;

	virtual void execOnLoopItEnter() {}

	virtual void execBeforeCheckTransition() {}

	virtual void checkTransition() = 0;

	virtual void execAfterCheckTransition() {}

	virtual void execBeforeContinuousEvolution() {}

	virtual void applyContinuousEvolution() = 0;

	virtual void execAfterContinuousEvolution() {}

	virtual void execOnLoopItExit() {}

	virtual void execAfterLoop() {}

	virtual void execBeforeProcessDiscreteBehavior() {}

	virtual void processDiscreteBehavior() = 0;

	virtual void execAfterProcessDiscreteBehavior() {}

	virtual void execOnEnd() {}
};
}  // namespace hypro