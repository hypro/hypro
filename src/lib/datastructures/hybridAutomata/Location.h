/* 
 * File:   location.h
 * Author: stefan & chris
 * Created on April 30, 2014, 9:06 AM
 */

#pragma once

#include "util.h"

namespace hypro
{
    template<typename Number>
    class Location
    {
        public:
    		struct invariant {
    			hypro::vector_t<Number> vec;
    			hypro::matrix_t<Number>* mat;
    			hypro::operator_e op;
    		};

    		struct location {
    			hypro::vector_t<Number> vec;
    			hypro::matrix_t<Number>* mat;
    			invariant inv;
    		};

        private:

    		/**
    		 * Member
    		 */
    		hypro::vector_t<Number> mVecAct; 	   //vector for activities
    		hypro::matrix_t<Number>* mMatrixAct;  //matrix for activities

    		hypro::vector_t<Number> mVecInv;		//vector for invariants
    		hypro::matrix_t<Number>* mMatrixInv; 	//matrix for invariants
    		hypro::operator_e mOperatorInv; //operator (vector) for invariants
    		invariant mInvariant;  //invariant: matrix, vector, and operator

    		location mLocation;  //location: matrix, vector, and invariant
        
        public:
    		/**
    		 * Constructors & Destructor
    		 */
    		Location() : 
                    mVecAct(),
                    mMatrixAct(),
                    mVecInv(),
                    mMatrixInv(),
                    mOperatorInv(),
                    mInvariant(),
                    mLocation()
                {}
    		Location(const Location& _loc);
    		Location(const hypro::matrix_t<Number>* _mat, const hypro::vector_t<Number> _vec, const struct invariant _inv);
        
    		~Location()
    		{}

    		/**
    		 * Getter & Setter
    		 */
    		hypro::vector_t<Number> activityVec();
    		hypro::matrix_t<Number>* activityMat();
    		invariant invariant();
    		location location();

    		void setActivityVec(hypro::vector_t<Number> _vec);
    		void setActivityMat(hypro::matrix_t<Number>* _mat);
    		void setInvariant(struct invariant _inv);
    		void setInvariant(hypro::matrix_t<Number>* _mat, hypro::vector_t<Number> _vec, hypro::operator_e _op);
    		void setLocation(struct location _loc);

    		//bool checkInvariant(hypro::valuation_t _val);
    		//std::set<hypro::valuation_t> computeForwardTimeClosure(hypro::valuation_t _val);
    };
}

#include "Location.tpp"
