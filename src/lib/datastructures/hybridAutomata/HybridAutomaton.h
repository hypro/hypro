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
			typedef hypro::Location<Number> location;
			typedef hypro::Transition<Number> transition;
			typedef std::set<location*> locationSet;
			typedef std::set<transition*> transitionSet;
    		typedef std::map<carl::Variable, carl::FLOAT_T<Number>> valuation_t;

    		struct hybridAutomaton {
    			locationSet init;
    			locationSet locs;
    			transitionSet trans;
    			valuation_t valuation;
    		};

    		/**
    		 * Member
    		 */
    		locationSet mInitialLocations;
    		locationSet mLocations;
    		transitionSet mTransitions;
    		valuation_t mValuation;

    		hybridAutomaton mHybridAutomaton;

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
    		hybridAutomaton getHybridAutomaton();

    		void setInitialLocations(locationSet _initLocs);
    		void setLocations(locationSet _locs);
    		void setTransitions(transitionSet _trans);
    		void setValuation(valuation_t _val);
    		void setHybridAutomaton(hybridAutomaton _hybrid);

    		//TODO add further functionality as needed
    };
}

#include "HybridAutomaton.tpp"
