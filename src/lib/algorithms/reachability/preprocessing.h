/*
 *   This file contains all methods related to the preprocessing procedure
 *   Author: Norman Hansen
 */
 
        LocationMap locationMap;    // maps each location to a locationInfo object containing additional static information
		TransitionMap transitionMap;   // maps each location to a transitionInfo object containing additional static information
		std::set<location*> locationSet;	// set for loop Detection during preprocessing

        typedef std::set<Transition<double>*> transitionSet;          // type of the transitions from a location
        
        /*
         *    This methods traverses, starting with the location specified by the method's argument, 
         *    recursively the model (depth-first search) and preprocesses all connected locations and transitions.
         */
		void preprocessing_recursion(location* loc)
		{
			if (locationSet.find(loc) != locationSet.end())
			{
				// the location has already been considered
				return;
			}
			else
			{
				// this  location has not yet been preprocessed
				locationSet.insert(loc);

				preprocess_location(loc);

				// preprocess outgoing transitions
				// iterate over outgoing transitions and preprocess them
                // compute preprocessing for transition destinations
				transitionSet transitions = (*loc).transitions();
				for(auto iterator = transitions.begin(); iterator != transitions.end(); ++iterator)
				{
                     preprocess_transition((*iterator)); // preprocess transition
                     preprocessing_recursion((*iterator)->targetLoc()); // preprocess connected location
                }
			}
		}
           
        /*
         *    This method computes additional static information for the specified location
         */   
        void preprocess_location(location* loc)
        {
             // TODO: implement preprocessing for location
        }
        
        /*
         *    This method computes additional static information for the specified transition
         */   
        void preprocess_transition(transition* trans)
        {
             // TODO: implement preprocessing for transition
        }
            
		/**
		* This method preprocesses the model of the hybrid automaton
		* Therefore every reachable location will be visited.
		* During a visit (depth-first-serach) different values are computed.
		* See preprocessing_recursion for further details
		*/
	void preprocess(HybridAutomaton<double> automaton)
	{
		std::set<location*> locations = automaton.initialLocations();

		for (auto iterator = locations.begin(); iterator != locations.end(); ++iterator)
		{
			preprocessing_recursion(*iterator) ;
		}
	}
