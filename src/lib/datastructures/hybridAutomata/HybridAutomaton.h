/* 
 * File:   hybridAutomaton.h
 * Author: stefan & chris
 *
 * Created on April 30, 2014, 9:06 AM
 */

#pragma once


namespace hypro
{
    template<typename Number>
    class HybridAutomaton
    {
        private:
			typedef hypro::Location<Number> location_t;
			typedef hypro::Transition<Number> transition_t;
			typedef std::set<location_t*> locationSet;
			typedef std::set<transition_t*> transitionSet;
    		typedef std::map<carl::Variable, carl::FLOAT_T<Number>> valuation_t;
    		typedef std::map<locationSet, locationSet, transitionSet, valuation_t> hybridAutomaton_t;

    		/**
    		 * Member
    		 */
    		locationSet mInitialLocations;
    		locationSet mLocations;
    		transitionSet mTransitions;
    		valuation_t mValuation;

    		hybridAutomaton_t mHybridAutomaton;

        public:
    		/**
    		 * Constructors & Destructor
    		 */
    		HybridAutomaton(){}
    		HybridAutomaton(const HybridAutomaton& _hybrid);
    		HybridAutomaton(const locationSet _initLocs, const locationSet _locs, const transitionSet _trans, valuation_t _initVal);

    		~HybridAutomaton()
    		{}

    		/**
    		 * Getter & Setter
    		 */
    		locationSet getInitialLocations();
    		locationSet getLocations();
    		transitionSet getTransitions();
    		valuation_t getValuation();
    		hybridAutomaton_t getHybridAutomaton();

    		void setInitialLocations(locationSet _initLocs);
    		void setLocations(locationSet _locs);
    		void setTransitions(transitionSet _trans);
    		void setValuation(valuation_t _val);

    		//TODO add further functionality as needed
    };
}

#include "HybridAutomaton.tpp"
