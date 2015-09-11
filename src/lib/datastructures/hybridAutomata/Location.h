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
	class LocationManager;

    template<typename Number>
    class Location
    {
		friend LocationManager<Number>;

		public:
			struct invariantContent {
				hypro::vector_t<Number> vec;
				hypro::matrix_t<Number> mat;
				hypro::operator_e op;
			};

		protected:
			typedef std::set<Transition<Number>*> transitionSet;

			Location(unsigned _id) : mLocation(), mId(_id) {}
			Location(unsigned _id, const Location& _loc);
			Location(unsigned _id, const hypro::matrix_t<Number> _mat, const hypro::vector_t<Number> _vec, const transitionSet _trans, const Location<Number>::invariantContent _inv);
			Location(unsigned _id, const hypro::matrix_t<Number> _mat, const hypro::vector_t<Number> _vec,
					const transitionSet _trans, const Location<Number>::invariantContent _inv, const hypro::matrix_t<Number> _extInputMat);


        public:

    		//location: activity (matrix & vector), invariant, a set of outgoing transitions and a matrix for external Input
    		struct locationContent {
    			hypro::vector_t<Number> vec;
    			hypro::matrix_t<Number> mat;
    			hypro::matrix_t<Number> extInputMat;
    			transitionSet trans;
    			invariantContent inv;
    		};

        private:

    		/**
    		 * Member
    		 */
    		locationContent mLocation;
    		unsigned mId;

        public:
    		/**
    		 * Constructors & Destructor
    		 */

			 ~Location()
 			{}

    		/**
    		 * Getter & Setter
    		 */
    		hypro::vector_t<Number> activityVec();
    		hypro::matrix_t<Number> activityMat();
    		invariantContent invariant();
    		locationContent location();
    		transitionSet transitions();
    		hypro::matrix_t<Number> extInputMat();
    		unsigned id() const {
    			return mId;
    		}

    		void setActivityVec(hypro::vector_t<Number> _vec);
    		void setActivityMat(hypro::matrix_t<Number> _mat);
    		void setInvariant(struct hypro::Location<Number>::invariantContent _inv);
    		void setInvariant(hypro::matrix_t<Number> _mat, hypro::vector_t<Number> _vec, hypro::operator_e _op);
    		void setLocation(struct locationContent _loc);
    		void setTransitions(transitionSet _trans);
    		void setExtInputMat(hypro::matrix_t<Number> _mat);

    		bool operator<(const Location<Number>& _rhs) const {
    			return (mId < _rhs.id());
    		}

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
