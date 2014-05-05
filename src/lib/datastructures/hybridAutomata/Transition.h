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
    		typedef hypro::Location<Number> location;
    		typedef std::map<carl::Variable, carl::FLOAT_T<Number>> valuation_t;

    		struct guard {
    			vector_t vec;
    			matrix_t* mat;
    			operator_t op;
    		};

    		struct transition {
    			location* locStart;
    			location* locTarget;
    			guard guard;
    			valuation_t assign;
    		};

    		/**
    		 * Member
    		 */
    		vector_t mVecGuard;
    		matrix_t* mMatrixGuard;
    		guard mGuard;  //guard: matrix, vector, and operator

    		location* mStartLoc;  // start location
    		location* mTargetLoc; // target location

    		valuation_t mAssignment; // assignment that takes place if guard is fulfilled

    		transition mTransition; // transition: two locations, a guard and an assignment

        public:
    		/**
    		 * Constructors & Destructor
    		 */
    		Transition() {}

    		Transition(const Transition& _trans) : mTransition(_trans.mTransition) {}

    		Transition(const location* _start, const location* _end, const guard _guard, const valuation_t _assign){
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
    		location* getStartLoc() {
    			return mStartLoc;
    		}

    		location* getTargetLoc() {
    			return mTargetLoc;
    		}

    		guard getGuard() {
    			return mGuard;
    		}

    		transition getTransition() {
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
