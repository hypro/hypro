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
    		enum operator_e {
    			<,
    			>,
    			<=,
    			>=
    		};

    		typedef std::map<carl::Variable, carl::FLOAT_T<Number> > vector_t; //typedef std::vector<carl::FLOAT_T<Number> > vector_t; ?
    		typedef Eigen::Matrix<Number, Dynamic, Dynamic> matrix_t;
    		typedef std::map<carl::Variable, operator_e> operator_t;
    		typedef std::map<carl::Variable, carl::FLOAT_T<Number>> valuation_t;

    		struct invariant {
    			vector_t vec;
    			matrix_t* mat;
    			operator_t op;
    		};

    		struct location {
    			vector_t vec;
    			matrix_t* mat;
    			invariant inv;
    		};

    		/**
    		 * Member
    		 */
    		vector_t mVecAct; 	   //vector for activities
    		matrix_t* mMatrixAct;  //matrix for activities

    		vector_t mVecInv;		//vector for invariants
    		matrix_t* mMatrixInv; 	//matrix for invariants
    		operator_t mOperatorInv; //operator (vector) for invariants
    		invariant mInvariant;  //invariant: matrix, vector, and operator

    		location mLocation;  //location: matrix, vector, and invariant
        
        public:
    		/**
    		 * Constructors & Destructor
    		 */
    		Location(){}
    		Location(const Location& _loc);
    		Location(const matrix_t* _mat, const vector_t _vec, const invariant _inv);
        
    		~Location()
    		{}

    		/**
    		 * Getter & Setter
    		 */
    		vector_t getActivityVec();
    		matrix_t* getActivityMat();
    		invariant getInvariant();
    		location getLocation();

    		void setActivityVec(vector_t _vec);
    		void setActivityMat(matrix_t* _mat);
    		void setInvariant(invariant _inv);
    		void setLocation(location _loc);

    		bool checkInvariant(valuation_t _val);
    		std::set<valuation_t> computeForwardTimeClosure(valuation_t _val);
    };
}

#include "Location.tpp"
