/* 
 * Class that describes a hybrid automaton.
 * File:   hybridAutomaton.h
 * Author: stefan & ckugler
 *
 * Created on April 30, 2014, 9:06 AM
 */

#pragma once

#include "Location.h"
#include "Transition.h"
#include "util.h"

namespace hypro
{
    template<typename Number, typename Representation>
    class HybridAutomaton
    {
        private:
			typedef hypro::Location<Number> location;
			typedef hypro::Transition<Number> transition;
			typedef std::set<location*> locationSet;
			typedef std::set<transition*> transitionSet;

        public:
			//hybrid automaton: a set of locations, a set of initial locations, a set of transitions and a valuation (currently a polytope)
    		struct hybridAutomaton {
    			locationSet init;
    			locationSet locs;
    			transitionSet trans;
    			Representation valuation;
                Representation extInputValuation;
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
    		HybridAutomaton(const locationSet _initLocs, const locationSet _locs, const transitionSet _trans, Representation _initVal);

    		virtual ~HybridAutomaton()
    		{}

    		/**
    		 * Getter & Setter
    		 */
    		locationSet initialLocations();
    		locationSet locations();
    		transitionSet transitions();
    		Representation valuation();
                Representation extInputValuation();
                unsigned dimension() const;
    		hybridAutomaton hybridAutomaton();

    		void setInitialLocations(locationSet _initLocs);
    		void setLocations(locationSet _locs);
    		void setTransitions(transitionSet _trans);
    		void setValuation(Representation _val);
            void setExtInputValuation(Representation _extInputVal);
    		void setHybridAutomaton(struct hybridAutomaton _hybrid);
			
			void addLocation(location* _location);
			void addTransition(transition* _transition);
			
			// move operator
			inline HybridAutomaton<Number,Representation>& operator= (const HybridAutomaton<Number,Representation>& _rhs) {
				mHybridAutomaton = _rhs.mHybridAutomaton;
				return *this;
			}
			
			friend std::ostream & operator<< (std::ostream& _ostr, const HybridAutomaton<Number,Representation>& _a) {
				_ostr << "initial: " << std::endl;
				for(auto initialIT = _a.mHybridAutomaton.init.begin(); initialIT != _a.mHybridAutomaton.init.end(); ++initialIT)
				{
					_ostr << **initialIT << std::endl;
				}
				_ostr << "locations: " << std::endl;
				for(auto locationIT = _a.mHybridAutomaton.locs.begin(); locationIT != _a.mHybridAutomaton.locs.end(); ++locationIT)
				{
					_ostr << **locationIT << std::endl;
				}
				_ostr << "transitions: " << std::endl;
				for(const auto& transition : _a.mHybridAutomaton.trans)
				{
					_ostr << *transition << std::endl;
				}
				return _ostr;
			}
    };
	
	
	
}

#include "HybridAutomaton.tpp"
