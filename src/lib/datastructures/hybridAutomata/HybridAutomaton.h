/* 
 * File:   hybridAutomaton.h
 * Author: stefan & chris
 *
 * Created on April 30, 2014, 9:06 AM
 */

#pragma once

#include "Location.h"
#include "Transition.h"
#include "util.h"

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

    		struct hybridAutomaton {
    			locationSet init;
    			locationSet locs;
    			transitionSet trans;
    			hypro::valuation_t valuation;
    		};

    		/**
    		 * Member
    		 */
    		locationSet mInitialLocations;
    		locationSet mLocations;
    		transitionSet mTransitions;
    		hypro::valuation_t mValuation;

    		hybridAutomaton mHybridAutomaton;

        public:
    		/**
    		 * Constructors & Destructor
    		 */
    		HybridAutomaton(){}
    		HybridAutomaton(const HybridAutomaton& _hybrid);
    		HybridAutomaton(const locationSet _initLocs, const locationSet _locs, const transitionSet _trans, hypro::valuation_t _initVal);

    		~HybridAutomaton()
    		{}

    		/**
    		 * Getter & Setter
    		 */
    		locationSet initialLocations();
    		locationSet locations();
    		transitionSet transitions();
    		hypro::valuation_t valuation();
    		hybridAutomaton hybridAutomaton();

    		void setInitialLocations(locationSet _initLocs);
    		void setLocations(locationSet _locs);
    		void setTransitions(transitionSet _trans);
    		void setValuation(hypro::valuation_t _val);
    		void setHybridAutomaton(hybridAutomaton _hybrid);

    };
}

#include "HybridAutomaton.tpp"
