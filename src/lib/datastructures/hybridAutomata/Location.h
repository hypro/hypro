/* 
 * Class that describes one location of a hybrid automaton.
 * File:   location.h
 * Author: stefan & ckugler
 * Created on April 30, 2014, 9:06 AM
 */

#pragma once

#include "util.h"

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

    		//location: activity (matrix & vector), invariant, a set of outgoing transitions and a matrix for external Input
    		struct location {
    			hypro::vector_t<Number> vec;
    			hypro::matrix_t<Number> mat;
    			hypro::matrix_t<Number> extInputMat;
    			transitionSet trans;
    			invariant inv;
    		};

        private:

    		/**
    		 * Member
    		 */
    		location mLocation;
        
        public:
    		/**
    		 * Constructors & Destructor
    		 */
    		Location() : mLocation() {}
    		Location(const Location& _loc);
    		Location(const hypro::matrix_t<Number> _mat, const hypro::vector_t<Number> _vec, const transitionSet _trans, const struct invariant _inv);
    		Location(const hypro::matrix_t<Number> _mat, const hypro::vector_t<Number> _vec,
    				const transitionSet _trans, const struct invariant _inv, const hypro::matrix_t<Number> _extInputMat);
        
    		~Location()
    		{}

    		/**
    		 * Getter & Setter
    		 */
    		hypro::vector_t<Number> activityVec();
    		hypro::matrix_t<Number> activityMat();
    		invariant invariant();
    		location location();
    		transitionSet transitions();
    		hypro::matrix_t<Number> extInputMat();

    		void setActivityVec(hypro::vector_t<Number> _vec);
    		void setActivityMat(hypro::matrix_t<Number> _mat);
    		void setInvariant(struct hypro::Location<Number>::invariant _inv);
    		void setInvariant(hypro::matrix_t<Number> _mat, hypro::vector_t<Number> _vec, hypro::operator_e _op);
    		void setLocation(struct location _loc);
    		void setTransitions(transitionSet _trans);
    		void setExtInputMat(hypro::matrix_t<Number> _mat);

			friend std::ostream & operator<< (std::ostream& _ostr, const Location<Number>& _l)
            {
				_ostr << "location(" << std::endl <<
				"\t Flow = " << _l.mLocation.mat << std::endl <<
				"\t Inv = " << _l.mLocation.inv.mat << std::endl <<
				")";
				return _ostr;
			}
    };
}

#include "Location.tpp"
