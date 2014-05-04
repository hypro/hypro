/* 
 * File:   location.h
 * Author: stefan & chris
 * Created on April 30, 2014, 9:06 AM
 */

#pragma once

namespace hypro
{
    template<typename Number>
    class Location
    {
        private:
    		typedef std::map<carl::Variable, carl::FLOAT_T<Number> > vector_t; //typedef std::vector<carl::FLOAT_T<Number> > vector_t; ?
    		typedef Eigen::Matrix<Number, Dynamic, Dynamic> matrix_t;
    		typedef std::map<carl::Variable, smth_operator> operator_t; //TODO: logical operators? <,>,==,>=,<=
    		typedef std::map<vector_t, matrix_t, operator_t> invariant_t;
    		typedef std::map<matrix_t,vector_t,invariant_t> location_t;
    		typedef std::map<carl::Variable, carl::FLOAT_T<Number>> valuation_t;

    		/**
    		 * Member
    		 */
    		vector_t mVecAct; 	   //vector for activities
    		matrix_t* mMatrixAct;  //matrix for activities

    		vector_t mVecInv;		//vector for invariants
    		matrix_t* mMatrixInv; 	//matrix for invariants
    		operator_t mOperatorInv; //operator (vector) for invariants
    		invariant_t mInvariant;  //invariant: matrix, vector, and operator

    		location_t mLocation;  //location: matrix, vector, and invariant
        
        public:
    		/**
    		 * Constructors & Destructor
    		 */
    		Location(){}
    		Location(const Location& _loc);
    		Location(const matrix_t* _mat, const vector_t _vec, const invariant_t _inv);
        
    		~Location()
    		{}

    		/**
    		 * Getter & Setter
    		 */
    		vector_t getActivityVec();
    		matrix_t* getActivityMat();
    		invariant_t getInvariant();
    		location_t getLocation();

    		void setActivityVec(vector_t _vec);
    		void setActivityMat(matrix_t* _mat);
    		void setInvariant(invariant_t _inv);
    		void setLocation(location_t _loc);

    		bool checkInvariant(valuation_t _val);
    };
}

#include "Location.tpp"
