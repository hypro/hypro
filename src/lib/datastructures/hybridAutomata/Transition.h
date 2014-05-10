/* 
 * File:   transition.h
 * Author: stefan & chris
 *
 * Created on April 30, 2014, 9:06 AM
 */

#pragma once

#include "Location.h"
#include "util.h"

namespace hypro
{
    template<typename Number>
    class Transition
    {
        private:

    		typedef hypro::Location<Number> location;

    		struct guard {
    			hypro::vector_t vec;
    			hypro::matrix_t* mat;
    			hypro::operator_t op;
    		};

    		struct transition {
    			location* locStart;
    			location* locTarget;
    			guard guard;
    			hypro::valuation_t assign;
    		};

    		/**
    		 * Member
    		 */
    		hypro::vector_t mVecGuard;
    		hypro::matrix_t* mMatrixGuard;
    		guard mGuard;  //guard: matrix, vector, and operator

    		location* mStartLoc;  // start location
    		location* mTargetLoc; // target location

    		hypro::valuation_t mAssignment; // assignment that takes place if guard is fulfilled

    		transition mTransition; // transition: two locations, a guard and an assignment

        public:
    		/**
    		 * Constructors & Destructor
    		 */
    		Transition() {}

    		Transition(const Transition& _trans) : mTransition(_trans.mTransition) {}

    		Transition(const location* _start, const location* _end, const guard _guard, const hypro::valuation_t _assign){
    			mStartLoc = _start;
    			mTargetLoc = _end;
    			mGuard = _guard;
    			mAssignment = _assign;

    			mTransition.locStart = _start;
    			mTransition.locTarget = _end;
    			mTransition.guard = _guard;
    			mTransition.assign = _assign;
    		}

    		~Transition()
    		{}

    		/**
    		 * Getter & Setter
    		 */
    		location* startLoc() {
    			return mStartLoc;
    		}

    		location* targetLoc() {
    			return mTargetLoc;
    		}

    		guard guard() {
    			return mGuard;
    		}

    		transition transition() {
    			return mTransition;
    		}

    		void setStartLoc(location* _start) {
    			mStartLoc = _start;
    		}

    		void setTargetLoc(location* _target) {
    			mTargetLoc = _target;
    		}

    		void setGuard(guard _guard) {
    			mGuard = _guard;
    		}

    		void setTransition(transition _trans) {
    			mTransition = _trans;
    		}

    		bool checkGuard(hypro::valuation_t _val) {
    			//TODO interval!
    			//return mGuard.mat * _val mGuard.op mGuard.vec
    		}

    		//previously: execAssignment (name tbd)
    		//TODO set of valuations is returned? -> Script!
    		hypro::valuation_t computePost(hypro::valuation_t _val) {
    			if (checkGuard(_val)) {
    				return mAssignment;
    			} else {
    				//TODO
    				//maybe throw error: transition may not be taken
    				return _val;
    			}
    		}
    };
}
