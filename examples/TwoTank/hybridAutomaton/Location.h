/* 
 * File:   location.h
 * Author: stefan & chris
 * Created on April 30, 2014, 9:06 AM
 */

#pragma once

#include "util.h"
#include <set>

//#include "Transition.h"



namespace hypro
{
    template<typename Number>
    class Transition;

    template<typename Number>
    class Location
    {
    	private:

            typedef std::set<Transition<Number>*> transitionSet;

        public:
            struct invariant {
                hypro::vector_t<Number> vec;
                hypro::matrix_t<Number> mat;
                hypro::operator_e op;
            };

            struct location {
                hypro::vector_t<Number> vec;
                hypro::matrix_t<Number> mat;
                hypro::matrix_t<Number> input_mat;
                transitionSet trans;
                invariant inv;
            };

        private:

    		/**
    		 * Member
    		 */
    		location mLocation;  //location: matrix, vector, invariant and set of outgoing transitions
        
        public:
    		/**
    		 * Constructors & Destructor
    		 */
    		Location() : mLocation() {}
    		Location(const Location& _loc);
    		Location(const hypro::matrix_t<Number> _mat, const hypro::vector_t<Number> _vec, const transitionSet _trans, const struct invariant _inv);
        
    		~Location()
    		{}

    		/**
    		 * Getter & Setter
    		 */
    		hypro::vector_t<Number> activityVec();
    		hypro::matrix_t<Number> activityMat();
                hypro::matrix_t<Number> activityInputMat();
    		invariant invariant();
    		location location();
    		transitionSet transitions();

    		void setActivityVec(hypro::vector_t<Number> _vec);
    		void setActivityMat(hypro::matrix_t<Number> _mat);
                void setActivityInputMat(hypro::matrix_t<Number> _inputMat);
    		void setInvariant(struct hypro::Location<Number>::invariant _inv);
    		void setInvariant(hypro::matrix_t<Number> _mat, hypro::vector_t<Number> _vec, hypro::operator_e _op);
    		void setLocation(struct location _loc);
    		void setTransitions(transitionSet _trans);

    		//bool checkInvariant(hypro::valuation_t _val);
    		//std::set<hypro::valuation_t> computeForwardTimeClosure(hypro::valuation_t _val);
    };
}

#include "Location.tpp"
