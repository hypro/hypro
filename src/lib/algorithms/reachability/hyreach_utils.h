/*
 * This file contains typdefs, includes and some general stuff used by HyReach
 * Author: Norman Hansen
 */

#pragma once

// model includes
#include "../../datastructures/hybridAutomata/util.h"
#include "../../datastructures/hybridAutomata/HybridAutomaton.h"

// standard includes
#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <map>
#include <list>
#include <forward_list>

// Supportfunction
#include "PolytopeSupportfunction.h"

   // GLPK includes
   #include <stdio.h>            /* C input/output                       */
   #include <stdlib.h>           /* C standard library                   */
   #include <glpk.h>             /* GNU GLPK linear/mixed integer solver */

namespace hypro
{
	// typedefs for types returned by the hybrid automata model
	typedef hypro::Location<double> location;
	typedef hypro::Transition<double> transition;
	typedef std::set<location*> locationSet;
	typedef std::set<transition*> transitionSet;

	// this type is used to define mappings of indices to directions
	typedef std::vector<matrix_t<double>*> mapping;

	// this class basically extends locations with additional preprocessed values for the hyreach analysis
	class LocationInfo
	{
	  private:
		location* origLocation;	// stores the original location from the model where the missing informations from LocationInfo are stored

        // additional generated information regarding the invariant
        SupportFunction* invariant; // support function representation of the invariant
		mapping invariant_constraints_in_L;
		mapping mirrored_invariant_constraints_in_L;
		std::vector<double> complete_invariant_evaluation;

	  public:
		LocationInfo(location* loc)
		{
			origLocation = loc;
			
			// generate automatically the additional information
			// TODO:
		}	
	};

	// this class basically extends transitions with additional preprocessed values for the hyreach analysis
	class TransitionInfo
	{
	  private:     
        transition* origTransition;	// stores the original transition from the model where the missing informations from TransitionInfo are stored
        
		matrix_t<double> I_star_constraints;
		matrix_t<double> I_star_values;
		SupportFunction* guardfunction;
		SupportFunction* wfunction;

		mapping iminus_constraints_in_L;
		mapping mirrored_iminus_constraints_in_L;
		mapping iplus_constraints_in_L;
		mapping mirrored_iplus_constraints_in_L;

		mapping guard_constraints_in_L;
		mapping mirrored_guard_constraints_in_L;

		matrix_t<double> sortedValues;
		
      public:
        TransitionInfo(transition* trans)
        {
            origTransition = trans;
            
            // generate automatically the additional information
            // TODO:
        }         
	};

	// typedefs for extended location handling
	typedef std::map<Location<double>, LocationInfo> LocationMap;
	typedef std::pair<Location<double>, LocationInfo> LocationPair;

	typedef std::map<Transition<double>, int> TransitionMap;
	typedef std::pair<Transition<double>, int> TransitionPair;
}
