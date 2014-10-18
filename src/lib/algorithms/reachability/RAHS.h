/* 
 * File:   RAHS.h
 * Author: Jonathan Gan
 *
 * Created on June 22, 2014, 19:15 PM
 */

#include <iostream>
#include <cmath>
#include "../representations/Zonotope.h"
#include <Eigen/Core>
#include <Eigen/Dense>
#include <unsupported/Eigen/MatrixFunctions>
// #include "Visualizer.h"
#include <algorithm>
#include "../datastructures/HybridAutomaton.h"

#ifndef RAHS_H
#define RAHS_H

template<typename Number> 
class RAHS {

    private:
        unsigned int mDimension;
        
        Eigen::Matrix<Number, Eigen::Dynamic, Eigen::Dynamic> exp_rA_;
        std::vector< Zonotope<Number> > sequence_zonQ_;
        bool mInitialized;
        
        Eigen::Matrix<Number, Eigen::Dynamic, Eigen::Dynamic> A_;
        Eigen::Matrix<Number, Eigen::Dynamic, Eigen::Dynamic> bigB_;
        Eigen::Matrix<Number, Eigen::Dynamic, 1> smallb_;
        Number r_;
        
        Zonotope<Number> U_;
        Zonotope<Number> Q_;
        Zonotope<Number> temp_Q_;
        Zonotope<Number> V_;
        Zonotope<Number> S_;
        
        hypro::HybridAutomaton<Number> mHybridAutomaton;
        hypro::Location<Number> mCurrentLoc;
        
        bool mRestartFlag;
        
        void overapproximateZonotope(Zonotope<Number>& z);
        void readjust();
        void initializeRAHSComputation();
        void computeNextZonotope_RACS(unsigned int i, unsigned int order_reduction_threshold);
        void checkGuardJumpCondition(Zonotope<Number>* intersect_zonotope);
        void loadNewState(hypro::Location<Number>* newLocation, Zonotope<Number>* intersect_zonotope);
        
    public:
        RAHS(unsigned int dimension);
        
//        RAHS(   unsigned int dimension,
//                const Eigen::Matrix<Number, Eigen::Dynamic, Eigen::Dynamic>& A,
//                const Eigen::Matrix<Number, Eigen::Dynamic, Eigen::Dynamic>& bigB,
//                const Eigen::Matrix<Number, Eigen::Dynamic, 1>& smallb, 
//                Number r, 
//                const Zonotope<Number>& U, 
//                const Zonotope<Number>& Q  );
        
        virtual ~RAHS();
        
        
        unsigned int dimension() const;
        
        void loadHybridAutomaton(hypro::HybridAutomaton<Number>* hybridAutomaton_);
        void approxReachDiscrete(unsigned int numIterations, unsigned int order_reduction_threshold);
        
        
        
};

#include "RAHS.tpp"

#endif /* RAHS.h */

