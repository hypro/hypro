/* 
 * Class that describes one transition of a hybrid automaton.
 * File:   transition.h
 * Author: stefan & ckugler
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

        public:
    		struct guard {
    			hypro::vector_t<Number> vec;
    			hypro::matrix_t<Number> mat;
    			hypro::operator_e op;
    		};

    		struct assignment {
    			hypro::vector_t<Number> translationVec;  //Translation Vector
    			hypro::matrix_t<Number> transformMat;    //Transformation Matrix
    		};

    		//transition: two locations, a guard and an assignment
    		struct transition {
    			location* locStart;
    			location* locTarget;
    			guard tGuard;
    			assignment tAssignment;
    		};

        private:
    		/**
    		 * Member
    		 */
    		transition mTransition;

        public:
    		/**
    		 * Constructors & Destructor
    		 */
    		Transition() {}

    		Transition(const Transition& _trans) : mTransition(_trans.mTransition) {}

    		Transition(const location* _start, const location* _end, const struct guard _guard, const assignment _assign){
    			mTransition.locStart = _start;
    			mTransition.locTarget = _end;
    			mTransition.tGuard = _guard;
    			mTransition.tAssignment = _assign;
    		}

    		~Transition()
    		{}

    		/**
    		 * Getter & Setter
    		 */
    		location* startLoc() {
    			return mTransition.locStart;
    		}

    		location* targetLoc() {
    			return mTransition.locTarget;
    		}

    		guard guard() const{
    			return mTransition.tGuard;
    		}

    		assignment assignment() const{
    			return mTransition.tAssignment;
    		}

    		transition transition() {
    			return mTransition;
    		}

    		void setStartLoc(location* _start) {
    			mTransition.locStart = _start;
    		}

    		void setTargetLoc(location* _target) {
    			mTransition.locTarget = _target;
    		}

    		void setGuard(struct guard _guard) {
    			mTransition.tGuard = _guard;
    		}

    		void setTransition(struct transition _trans) {
    			mTransition = _trans;
    		}

    		void setAssignment(struct assignment _val) {
    			mTransition.tAssignment = _val;
    		}
    };
}
