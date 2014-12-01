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

        public:
            struct hybridAutomaton {
                locationSet init;
                locationSet locs;
                transitionSet trans;
                hypro::valuation_t<Number> valuation;
                hypro::valuation_t<Number> input_valuation;
            };

        private:
    		/**
    		 * Member
    		 */
    		hybridAutomaton mHybridAutomaton;

        public:
    		/**
    		 * Constructors & Destructor
    		 */
    		HybridAutomaton(){}
    		HybridAutomaton(const HybridAutomaton& _hybrid);
    		HybridAutomaton(const locationSet _initLocs, const locationSet _locs, const transitionSet _trans, hypro::valuation_t<Number> _initVal);

    		~HybridAutomaton()
    		{}

    		/**
    		 * Getter & Setter
    		 */
    		locationSet initialLocations();
    		locationSet locations();
    		transitionSet transitions();
    		hypro::valuation_t<Number> valuation();
                hypro::valuation_t<Number> inputValuation();
    		hybridAutomaton hybridAutomaton();

    		void setInitialLocations(locationSet _initLocs);
    		void setLocations(locationSet _locs);
    		void setTransitions(transitionSet _trans);
    		void setValuation(hypro::valuation_t<Number> _val);
                void setInputValuation(hypro::valuation_t<Number> _inputval);
    		void setHybridAutomaton(struct hybridAutomaton _hybrid);

    };
}

#include "HybridAutomaton.tpp"
