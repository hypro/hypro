/*
 *   This file contains all methods related to the preprocessing procedure
 *   Author: Norman Hansen
 */
 
        // typedefs for types returned by the hybrid automata model
	typedef hypro::Location<double> location;
	typedef hypro::Transition<double> transition;
	//typedef std::set<location*> locationSet;
	//typedef std::set<transition*> transitionSet;

	// this type is used to define mappings of indices to directions
	typedef std::vector<unsigned int>* mapping;

	// this class basically extends locations with additional preprocessed values for the hyreach analysis
	class LocationInfo
	{
	  private:
		location* origLocation;	// stores the original location from the model where the missing informations from LocationInfo are stored

        // additional generated information regarding the invariant
        PolytopeSupportFunction* invariantSP; // support function representation of the invariant
		mapping invariant_constraints_in_L;
		mapping mirrored_invariant_constraints_in_L;
		std::vector<double> complete_invariant_evaluation;

	  public:
		LocationInfo(location* loc, std::vector<matrix_t<double>>* L_pt)
		{
			origLocation = loc;
			
			// generate automatically the additional information
			
			// generate PolytopeSupportFunction object for Invariant
            //Location<double>.invariant I = (*loc).invariant();
            
            // extract size information from invariant
            unsigned int dimensionality = (unsigned int) ((*loc).invariant()).mat.cols();
            unsigned int constraints = (unsigned int) ((*loc).invariant()).mat.rows();
            
            #ifdef LOCATIONINFO_VERBOSE
                string method = "LocationInfo: ";
                if(dimensionality != (L_pt->at(0)).cols())
                {
                    std::cout << method << "constructor: L and invariant of different dimensionality" << '\n';
                }
            #endif
            
            invariantSP = new PolytopeSupportFunction((*loc).invariant().mat, (*loc).invariant().vec, (*loc).invariant().op, dimensionality);
            
            // evaluate PolytopeSupportFunction object in every direction
            invariantSP->multiEvaluate(L_pt, complete_invariant_evaluation);
            #ifdef LOCATIONINFO_VERBOSE
                if(dimensionality != (L_pt->at(0)).cols())
                {
                    std::cout << method << "constructor: invariant evaluation for L=" << printDirectionList(*L_pt) '\n';
                    std::cout << "is: " << '\n';
                    print(complete_invariant_evaluation);
                    std::cout << '\n'
                }
            #endif
            
            // create the mapping between constraints and entries in L
            invariant_constraints_in_L = new std::vector<unsigned int>(constraints);
            mirrored_invariant_constraints_in_L = new std::vector<unsigned int>(constraints);
            
            // for each constraint, find equal l in L, store index of l -> contains method (helper methods)
            // analog for mirrored
            
            // normalize every constraint
            for(unsigned int i=0; i<constraints; i++)
            {
                  matrix_t<double> normedDirection = ((*loc).invariant().mat).row(i);
                  normedDirection.normalize();
                  normedDirection = round(normedDirection, precision);
                  
                  #ifdef LOCATIONINFO_VERBOSE
                      std::cout << "" << '\n';
                  #endif
                  
                  int x = contains(L_pt, &normedDirection);
                  if(x < 0)
                  {
                       // not contained yet
                       L_pt->push_back(normedDirection);
                       invariant_constraints_in_L->push_back(L_pt->size()-1);
                  }
                  else
                  {
                      // already contained in L
                      invariant_constraints_in_L->push_back(x);
                  }
                  
                  #ifdef LOCATIONINFO_VERBOSE
                      std::cout << "" << '\n';
                  #endif
                  
                  // compute opposite direction
                  normedDirection = normedDirection * (-1);
                  
                  // same check and procedure for opposite direction
                  x = contains(L_pt, &normedDirection);
                  if(x < 0)
                  {
                       L_pt->push_back(normedDirection);
                       mirrored_invariant_constraints_in_L->push_back(L_pt->size()-1);
                  }
                  else
                  {
                      mirrored_invariant_constraints_in_L->push_back(x);
                  }   
                  
                  #ifdef LOCATIONINFO_VERBOSE
                      std::cout << "" << '\n';
                  #endif
            }
            

		}
        
        ~LocationInfo()
        {
            delete invariantSP;
            delete invariant_constraints_in_L;
            delete mirrored_invariant_constraints_in_L;
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
	
	
        LocationMap locationMap;    // maps each location to a locationInfo object containing additional static information
		TransitionMap transitionMap;   // maps each location to a transitionInfo object containing additional static information
		std::set<location*> locationSet;	// set for loop Detection during preprocessing

        typedef std::set<Transition<double>*> transitionSet;          // type of the transitions from a location
           
        /*
         *    This method computes additional static information for the specified location
         */   
        void preprocess_location(location* loc)
        {
             // TODO: implement preprocessing for location
             // add invariant directions (normalized) to L (at the end) if not already in L
             // create LocationInfoObject
             // add (location,LocationInfo) pair to location mapping
             // (LocationInfo constructor computes all necessary values)
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
		
		/**
		* Initiates the preprocessing for all locations, connected through paths beginning at an initial location
		*/
	    void preprocess(HybridAutomaton<double>* automaton)
	    {
	    	std::set<location*> locations = (*automaton).initialLocations();

	     	for (auto iterator = locations.begin(); iterator != locations.end(); ++iterator)
	      	{
	       		preprocessing_recursion(*iterator) ;
	       	}
        }
