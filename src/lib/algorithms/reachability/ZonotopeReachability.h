/* *
 * ZonotopeReachability class using the Zonotope representation for the reachability analysis algorithm
 * 
 * File:   RAHS.h
 * @author Jonathan Gan, Ibtissem Ben Makhlouf {gan, makhlouf} @ embedded.rwth-aachen.de
 * @version 1.0 on June 22, 2014, 19:15 PM
 */


#ifndef ZONOTOPE_REACHABILITY_H
#define ZONOTOPE_REACHABILITY_H

#include <iostream>
#include <cmath>
#include <algorithm>
#include <map>

#include <Eigen/Core>
#include <Eigen/Dense>
#include <unsupported/Eigen/MatrixFunctions>

#include "../../representations/Zonotope/Zonotope.h"
#include "../../datastructures/hybridAutomata/HybridAutomaton.h"
#include "../../representations/Zonotope/ZUtility.h"

template<typename Number> 
class ZonotopeReachability {

    private: // private member attributes
        unsigned int mDimension;
        
        hypro::matrix_t<Number> exp_rA_;
        std::vector< Zonotope<Number> > sequence_zonQ_;
        std::map <unsigned int, std::vector< Zonotope<Number> > > intersect_zonotopes_;
        std::map <unsigned int, std::vector< Zonotope<Number> > > resulting_intersect_;
        std::map <unsigned int, hypro::matrix_t<Number> > min_intersect_;
        std::map <unsigned int, hypro::matrix_t<Number> > max_intersect_;
        
        std::map <unsigned int, Zonotope<Number> > pivotal_zonotopes_;
        bool mInitialized, mReadjusted;
        
        hypro::matrix_t<Number> A_;
        hypro::matrix_t<Number> bigB_;
        hypro::vector_t<Number> smallb_;
        
        hypro::scalar_t<Number> r_;
        
        Zonotope<Number> U_;
        Zonotope<Number> Q_;
        
        hypro::HybridAutomaton<Number, Zonotope<Number> > mHybridAutomaton;
        hypro::Location<Number> mCurrentLoc;
        
        enum state_t {
            START,
            NORMAL,
            JUMP         
        };
        
    private: // private functions
        
        void preclustering(const std::vector< Zonotope<Number> >& intersects, const Hyperplane<Number>& hp, Zonotope<Number>& finalIntersect, const ZUtility::Options& option);
        void postclustering(const std::vector< Zonotope<Number> >& resultingIntersects, Zonotope<Number>& finalIntersect);
        
        void overapproximateZonotope(Zonotope<Number>& z);
        void readjustMatrices();
        void readjust();
        
        
        void initialize(Zonotope<Number>& res_V, Zonotope<Number>& res_S);
        
        void computeNextZonotope(  unsigned int order_reduction_threshold,
                                        Zonotope<Number>& Q, 
                                        Zonotope<Number>& V,
                                        Zonotope<Number>& S);
        
        void guardToHyperplane(const hypro::Transition<Number>& transitionTaken, Hyperplane<Number>& hp);
        
        void constructIntersectZonotopeFromMinMax(unsigned iteration, const Zonotope<Number>& Q, Zonotope<Number>& result, const Hyperplane<Number>& hp);
        
        bool checkGuardJumpCondition(hypro::Transition<Number>& transition_taken,
                                    const Zonotope<Number>& Q,
                                    hypro::matrix_t<Number>& minMaxOfLine,
                                    const ZUtility::Options& option);
        
        void loadNewState(hypro::Transition<Number>& transition, const Zonotope<Number>& intersect_zonotope);
        
        void overapproximatedConvexHull(Zonotope<Number>& Q, 
                                        const hypro::matrix_t<Number>& expMatrix);
        
        bool checkForIntersection(const Zonotope<Number>& inputZonotope, const Hyperplane<Number>& hp, 
                                    Zonotope<Number>& result,
                                    const ZUtility::IntersectionMethod_t& method);
         
        bool checkForIntersection(const Zonotope<Number>& inputZonotope, const Hyperplane<Number>& hp, 
                                    Zonotope<Number>& result,
                                    const ZUtility::IntersectionMethod_t& method,
                                    hypro::matrix_t<Number>& minMaxOfLine);
        
        
        bool fulfillsInvariant(const Zonotope<Number>& inputZonotope, Zonotope<Number>& result);
        
        bool runReachabilityAnalysis(unsigned int numIterations, 
                                       unsigned int offset,
                                       hypro::scalar_t<Number> r_scalar, 
                                       unsigned int order_reduction_threshold,
                                       Zonotope<Number>& res_V, Zonotope<Number>& res_S,
                                       const ZUtility::Options& option);
        
    public: // public functions
        ZonotopeReachability(unsigned int dimension);
        
        virtual ~ZonotopeReachability();
        
        
        /**
         * Dimensionality of system
         * @return dimension
         */
        unsigned int dimension() const;
        
        /**
         * Flowpipe generated by reachability analysis
         * @return A vector array of states reached by the algorithm
         */
        std::vector< Zonotope<Number> > flowpipe();
        
        /**
         * Set of states where an intersection occurs
         * @return map of iteration number to vector array of zonotopes
         */
        std::map <unsigned int, std::vector< Zonotope<Number> > > intersections();
        
        /**
         * Set of resulting zonotope intersections at each iteration where an intersection occurs
         * @return map of iteration number to vector array of zonotopes
         */
        std::map <unsigned int, std::vector< Zonotope<Number> > > resultingIntersections();
        
        std::map <unsigned int, Zonotope<Number> > pivotalZonotopes();
        
        /**
         * Current state loaded
         * @return Current state (a Zonotope)
         */
        Zonotope<Number> currentSet() const;
        
        /**
         * Initial input passed through the hybrid automata
         * @return Initial input (a Zonotope)
         */
        Zonotope<Number> initialInput() const;
        
        /**
         * Loads the Hybrid Automaton and initializes initial state, initial input,
         * dynamics matrix A, input matrix B and constant vector b
         * @param hybridAutomaton_ A hybrid automaton as defined in hypro library
         */
        void loadHybridAutomaton(hypro::HybridAutomaton<Number, Zonotope<Number> >* hybridAutomaton_);
        
        /**
         * Runs the algorithm
         * @param numIterations Number of iterations that the algorithm should run
         * @param r_scalar Time division e.g. 0.01
         * @param order_reduction_threshold The threshold number of generators, from which we will overapproximate the generators
         * @return true if reachability analysis was completed, false if reachability analysis was terminated prematurely due to unfulfilled conditions
         */
        bool startReachabilityAnalysis(unsigned int numIterations, 
                                       unsigned int offset,
                                       hypro::scalar_t<Number> r_scalar, 
                                       unsigned int order_reduction_threshold,
                                       const ZUtility::Options& option);
        
        
        
        
        
        
};

#include "ZonotopeReachability.tpp"

#endif /* ZonotopeReachability.h */

