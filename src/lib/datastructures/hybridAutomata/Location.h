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
        private:
    		struct invariant {
    			hypro::vector_t vec;
    			hypro::matrix_t* mat;
    			hypro::operator_t op;
    		};

    		struct location {
    			hypro::vector_t vec;
    			hypro::matrix_t* mat;
    			invariant inv;
    		};

    		/**
    		 * Member
    		 */
    		hypro::vector_t mVecAct; 	   //vector for activities
    		hypro::matrix_t* mMatrixAct;  //matrix for activities

    		hypro::vector_t mVecInv;		//vector for invariants
    		hypro::matrix_t* mMatrixInv; 	//matrix for invariants
    		hypro::operator_t mOperatorInv; //operator (vector) for invariants
    		invariant mInvariant;  //invariant: matrix, vector, and operator

    		location mLocation;  //location: matrix, vector, and invariant
        
        public:
    		/**
    		 * Constructors & Destructor
    		 */
    		Location(){}
    		Location(const Location& _loc);
    		Location(const hypro::matrix_t* _mat, const hypro::vector_t _vec, const invariant _inv);
        
    		~Location()
    		{}

    		/**
    		 * Getter & Setter
    		 */
    		hypro::vector_t activityVec();
    		hypro::matrix_t* activityMat();
    		invariant invariant();
    		location location();

    		void setActivityVec(hypro::vector_t _vec);
    		void setActivityMat(hypro::matrix_t* _mat);
    		void setInvariant(invariant _inv);
    		void setLocation(location _loc);

    		bool checkInvariant(hypro::valuation_t _val);
    		std::set<hypro::valuation_t> computeForwardTimeClosure(hypro::valuation_t _val);
    };
}

#include "Location.tpp"
