/* 
 * File:   transition.h
 * Author: stefan & chris
 *
 * Created on April 30, 2014, 9:06 AM
 */

#pragma once

#include<Location.h>

namespace hypro
{
    template<typename Number>
    class Transition
    {
        private:
    		typedef std::map<carl::Variable, carl::FLOAT_T<Number> > vector_t; //typedef std::vector<carl::FLOAT_T<Number> > vector_t; ?
    		typedef Eigen::Matrix<Number, Dynamic, Dynamic> matrix_t;
    		typedef std::map<carl::Variable, smth_operator> operator_t; //TODO: logical operators? <,>,==,>=,<=
    		typedef std::map<vector_t, matrix_t, operator_t> guard_t;
    		typedef hypro::Location<Number> location_t;
    		typedef std::map<carl::Variable, carl::FLOAT_T<Number>> valuation_t;
    		typedef std::map<location_t, location_t, guard_t, valuation_t> transition_t;

    		/**
    		 * Member
    		 */
    		vector_t mVecGuard;
    		matrix_t* mMatrixGuard;
    		guard_t mGuard;  //guard: matrix, vector, and operator

    		location_t* mStartLoc;  // start location
    		location_t* mTargetLoc; // target location

    		valuation_t mAssignment; // assignment that takes place if guard is fulfilled

    		transition_t mTransition; // transition: two locations, a guard and an assignment

        public:
    		/**
    		 * Constructors & Destructor
    		 */
    		Transition() {}

    		Transition(const Transition& _trans) : mTransition(_trans.mTransition) {}

    		Transition(const location_t* _start, const location_t* _end, const guard_t _guard, const valuation_t _assign){
    			mStartLoc = _start;
    			mTargetLoc = _end;
    			mGuard = _guard;
    			mAssignment = _assign;

    			//TODO
    			//mTransition.addToMap(mStartLoc, mTargetLoc, mGuard, mAssignment);
    		}

    		~Transition()
    		{}

    		/**
    		 * Getter & Setter
    		 */
    		location_t* getStartLoc() {
    			return mStartLoc;
    		}

    		location_t* getTargetLoc() {
    			return mTargetLoc;
    		}

    		guard_t getGuard() {
    			return mGuard;
    		}

    		transition_t getTransition() {
    			return mTransition;
    		}

    		void setStartLoc(location_t* _start) {
    			mStartLoc = _start;
    		}

    		void setTargetLoc(location_t* _target) {
    			mTargetLoc = _target;
    		}

    		void setGuard(guard_t _guard) {
    			mGuard = _guard;
    		}

    		void setTransition(transition_t _trans) {
    			mTransition = _trans;
    		}

    		bool checkGuard(valuation_t _val) {
    			//TODO
    			//return mMatrixGuard * _val <mGuard.Operator> mVecGuard
    		}

    		valuation_t execAssignment(valuation_t _val) {
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
