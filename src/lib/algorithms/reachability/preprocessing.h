/*
 *   This file contains all methods related to the preprocessing procedure
 *   Author: Norman Hansen
 */
 
//#define LOCATIONINFO_VERBOSE 
//#define TRANSITIONINFO_VERBOSE 
 
	//typedef std::set<location*> locationSet;
	//typedef std::set<transition*> transitionSet;

	// this type is used to define mappings of indices to directions
	typedef unsigned int* mapping;

    /*
    * (Abstract-) super class for LocationInfo and TransitionInfo
    * Provides some common functionality related to the introduction of additional directions
    */
    class PreprocessingObject
    {
          private:
                   /*
                   * Adds the direction "direction" unchanged to L if it is not already an element of L.
                   * Returns the index of direction in L after a possible insertion operation.
                   */
                   unsigned int addToL(std::vector<matrix_t<double>>* L_pt, matrix_t<double>* direction)
                   {
                       int x = contains(L_pt, direction);
                       if(x < 0)
                       {
                           // not contained yet -> append direction at the end of L
                           L_pt->push_back(*direction);
                           return (unsigned int)(L_pt->size()-1);
                        }
                        else
                        {
                           // already contained in L -> x >= 0
                           return (unsigned int) x;
                        }
                    }
          protected:
                    /*
                    * Normalizes the length of constraints to one (row-wise) and scales the constraintValues correspondingly. Furthermore,
                    * the constraints are rounded regarding global settings.
                    */
                    void normalizeLinearConstraint(matrix_t<double> constraints, vector_t<double> constraintValues, std::vector<matrix_t<double>>* directions, std::vector<double>* scaledConstraintValues )
                    {
                          constraints = addZeroColumn(constraints);  // add additional dimension
                         
                          double norm = 0;
                          for( int i=0; i<constraints.rows(); i++)
                          {
                               // compute normed and rounded direction
                               matrix_t<double> normedDirection = constraints.row(i).transpose();
                               norm = normedDirection.norm().toDouble();
                               normedDirection = normedDirection/norm;
                               normedDirection = round(normedDirection, precision);
                  
                               // add results for iteration i to the correspondent lists
                               directions->push_back(normedDirection);
                               scaledConstraintValues->push_back( (constraintValues(i)).toDouble()/norm );
                           }
                    }
                    
                    /*
                    * Extends the directions list L by the directions of "directions" and returns a mapping between indices
                    */
                    unsigned int* extendDirections(std::vector<matrix_t<double>>* L_pt, std::vector<matrix_t<double>>* directions )
                    {
                           // create value to return
                           unsigned int* result = new unsigned int[directions->size()];  
                           
                           // iterate over all directions and compute mapping
                           for(unsigned int i=0; i<directions->size(); i++)
                           {
                               result[i] = addToL(L_pt, &directions->at(i));
                           }
                           
                           return result;
                    }
                    
                    /*
                    * Similar to "extendDirections" but with automatic computation of the opposite dirrection
                    */
                    unsigned int* extendMirroredDirections(std::vector<matrix_t<double>>* L_pt, std::vector<matrix_t<double>>* directions )
                    {
                        // create value to return
                        unsigned int* result = new unsigned int[directions->size()];  
                           
                        // iterate over all directions and compute mapping
                        for(unsigned int i=0; i<directions->size(); i++)
                        {
                            matrix_t<double> mirrored = -1 * directions->at(i);  // compute opposite direction
                            result[i] = addToL(L_pt, &mirrored);
                        }
                        
                        return result;
                    }
    };

	/*
    * This class basically extends locations with additional preprocessed values for the hyreach analysis
    */
	class LocationInfo: public PreprocessingObject
	{
	  private:
		location* origLocation;	// stores the original location from the model where the missing informations from LocationInfo are stored
		matrix_t<double> A;     // dynamic matrix A combined with b (from Ax +b)
        
      public:
        // additional generated information regarding the invariant
        SupportFunction* invariantSP; // support function representation of the invariant  (needed by algoInv)
		mapping invariant_constraints_in_L = 0;
		mapping mirrored_invariant_constraints_in_L = 0;
		std::vector<double>* complete_invariant_evaluation;

        std::vector<matrix_t<double>>* constraintsAsDirections;    // store constraints as directions (normalized etc.)
        std::vector<double>* scaledConstraintValues;   // since during the analysis the correspondent directions from L are used it is necessary to use scaled constraint values 
                                                       // because the directions in L are normed to length 1 and otherwise the scaling of the invariants would be changed.

        // these values are set by the HyReach object during the analysis
        matrix_t<double> edA;                         // exp(delta*A)
        SupportFunction* V;                           // U(B' * l)
        
        // getter for preprocessed A (additional dimension)
        matrix_t<double>* getA()
        {
            return &A;
        }

	    /*
	    * Constructor
	    */
		LocationInfo(location* loc, std::vector<matrix_t<double>>* L_pt, double delta, SupportFunction* U, artificialDirections* aD)
		{
            #ifdef LOCATIONINFO_VERBOSE
                string method = "LocationInfo(): ";
                std::cout << method << this << '\n';
            #endif
			origLocation = loc;
			
			// generate automatically the additional information
            
            // extract size information from invariant
            //unsigned int dimensionality = (unsigned int) ((*loc).invariant()).mat.cols();
            unsigned int constraints = (unsigned int) ((*loc).invariant()).mat.rows();   // Assuption: the model contains only <= constraints
            
            #ifdef LOCATIONINFO_VERBOSE
                //if(dimensionality != (unsigned int)(L_pt->at(0)).cols())
                //{
                //    std::cout << method << "L and invariant of different dimensionality" << '\n';
                //}
            #endif
            
            A.resize( loc->activityMat().rows()+1,  loc->activityMat().cols()+1);
            #ifdef LOCATIONINFO_VERBOSE
                std::cout << method << "original A:" << BL;
                std::cout << loc->activityMat() << BL;
                std::cout << method << "original b:" << BL;
                std::cout << loc->activityVec() << BL;
            #endif
            
            matrix_t<double> temp = loc->activityMat();
            vector_t<double> temp2 = loc->activityVec();
            for(unsigned int i=0; i<loc->activityMat().rows(); i++)
            {
                for(unsigned int j=0; j<loc->activityMat().cols(); j++)
                {
                    A(i,j) = temp(i,j);
                }
                
                A(i,loc->activityMat().cols()) = temp2(i);
            }             
            #ifdef LOCATIONINFO_VERBOSE
                std::cout << method << "extended A:" << BL;
                std::cout << A << BL;
            #endif
            
            // generate PolytopeSupportFunction object for Invariant
            if((*loc).invariant().vec.size() > 0 )
            {
                matrix_t<double> m = addZeroColumn((*loc).invariant().mat);              // add additional dimension
                #ifdef LOCATIONINFO_VERBOSE
                    std::cout << method << "original invariant matrix:" << BL;
                    std::cout << (*loc).invariant().mat << BL;
                    std::cout << method << "extended invariant matrix:" << BL;
                    std::cout << m << BL;
                    std::cout << method << "original invariant values:" << BL;
                    std::cout << (*loc).invariant().vec << BL;
                #endif
                // note: no need to use normed directions and correspondent scaled values because the invariant support function will always 
                // be evaluated to retrieve values from it an thus the values are computed correctly
                invariantSP = new PolytopeSupportFunction(m, (*loc).invariant().vec, (*loc).invariant().op, (unsigned int) m.cols(), aD);
            }
            else
            {
                #ifdef LOCATIONINFO_VERBOSE
                    std::cout << method << "use infinity invariant" << BL;
                #endif
                invariantSP = new InfinitySupportFunction(aD);
            }
                        
            // create the mapping between constraints and entries in L
            scaledConstraintValues = new std::vector<double>(constraints);
            constraintsAsDirections = new std::vector<matrix_t<double>>(constraints);
                
            // normalize every constraint
            normalizeLinearConstraint((*loc).invariant().mat,(*loc).invariant().vec, constraintsAsDirections, scaledConstraintValues);
            // compute mapping and add missing directions to L
            invariant_constraints_in_L = extendDirections(L_pt,constraintsAsDirections);
            mirrored_invariant_constraints_in_L = extendMirroredDirections(L_pt,constraintsAsDirections);
            
            #ifdef LOCATIONINFO_VERBOSE
                 std::cout << method << "L: " << '\n';
                 printDirectionList(*L_pt);
                 std::cout << method << "constraint matrix: " << ((*loc).invariant()).mat << '\n';
                 std::cout << method << "constraints in L: " << invariant_constraints_in_L <<'\n';
                 std::cout << method << "mirrored constraints in L: " << mirrored_invariant_constraints_in_L <<'\n';
                 std::cout << method << "scaled values : " << scaledConstraintValues << '\n';
            #endif
            
            // construct parametrized values
            edA = exponentialmatrix(delta*A) ;
            matrix_t<double> B = addZeroRow(loc->extInputMat());
            V = U->multiply(B);
            #ifdef LOCATIONINFO_VERBOSE
                 std::cout << method << "edA: " << edA << '\n';
            #endif
		}
        
        /*
        * This method is used instead of the Deconstructor to free allocated memory on the heap
        */
        void freeAllocatedMemory()
        {
             // delete constructed objects on the heap
            delete invariantSP;
            delete[] invariant_constraints_in_L;
            delete[] mirrored_invariant_constraints_in_L;
  
            delete scaledConstraintValues;
            delete constraintsAsDirections;
            
            delete complete_invariant_evaluation;
            delete V;
        }
	};

	/*
    * This class basically extends transitions with additional preprocessed values for the hyreach analysis
    */
	class TransitionInfo: public PreprocessingObject
	{
	  private:     
        transition* origTransition;	// stores the original transition from the model where the missing informations from TransitionInfo are stored
        
		matrix_t<double> I_star_constraints;
		matrix_t<double> I_star_values;
		SupportFunction* guardfunction;
		SupportFunction* wfunction;

        // TODO: what is I+ and I- (if from invariants of locations no need for computation!)
		mapping iminus_constraints_in_L;
		mapping mirrored_iminus_constraints_in_L;
		mapping iplus_constraints_in_L;
		mapping mirrored_iplus_constraints_in_L;

        // guard related values (analog to invariant from location)
		mapping guard_constraints_in_L;
		mapping mirrored_guard_constraints_in_L;
		std::vector<matrix_t<double>>* guardsAsDirections;
        std::vector<double>* scaledGuardValues;

        // Evaluation of ?
		matrix_t<double> sortedValues;
		
      public:
        TransitionInfo(transition* trans, std::vector<matrix_t<double>>* L_pt)
        {
            #ifdef TRANSITIONINFO_VERBOSE
            std::string method =  "TransitionInfo: constructor";
                std::cout << method << '\n';
            #endif
            
            origTransition = trans;
            const unsigned int dimensionality = (unsigned int) ((*trans).guard()).mat.cols(); 
            unsigned int guards = (unsigned int) ((*trans).guard()).mat.rows();    // Assuption: the model contains only <= guards
            
            // create new objects on the heap to store relevant information
            iminus_constraints_in_L = new unsigned int[guards];
            mirrored_iminus_constraints_in_L = new unsigned int[guards];
            iplus_constraints_in_L = new unsigned int[guards];
            mirrored_iplus_constraints_in_L = new unsigned int[guards];
            
            guard_constraints_in_L = new unsigned int[guards];
            mirrored_guard_constraints_in_L = new unsigned int[guards];
            guardsAsDirections = new std::vector<matrix_t<double>>(guards);
            scaledGuardValues = new std::vector<double>(guards);
            
            // generate automatically the additional information
            // TODO:               
            // what to do with I+, I- and I* ??
            // construct support functions wfunction and guardfunction
            
            // handle guard
            // normalize every guard constraint
            normalizeLinearConstraint(((*trans).guard()).mat,((*trans).guard()).vec, guardsAsDirections, scaledGuardValues);
            // compute mapping and add missing directions to L
            guard_constraints_in_L = extendDirections(L_pt,guardsAsDirections);
            mirrored_guard_constraints_in_L = extendMirroredDirections(L_pt,guardsAsDirections);
        }     
        
        ~TransitionInfo()
        {
            #ifdef TRANSITIONINFO_VERBOSE
                std::cout << "TransitionInfo: destructor" << '\n';
            #endif
            
            // delete constructed heap objects
            delete[] iminus_constraints_in_L;
            delete[] mirrored_iminus_constraints_in_L;
            delete[] iplus_constraints_in_L;
            delete[] mirrored_iplus_constraints_in_L;
            delete[] guard_constraints_in_L;
            delete[] mirrored_guard_constraints_in_L;
            
            delete guardsAsDirections;
            delete scaledGuardValues;
        }    
	};

	// typedefs for extended location handling
	typedef std::map<Location<double>*, LocationInfo*> LocationMap;
	typedef std::pair<Location<double>*, LocationInfo*> LocationPair;

	typedef std::map<Transition<double>*, TransitionInfo*> TransitionMap;
	typedef std::pair<Transition<double>*, TransitionInfo*> TransitionPair;
	
	
        LocationMap locationMap;    // maps each location to a locationInfo object containing additional static information
		TransitionMap transitionMap;   // maps each location to a transitionInfo object containing additional static information
		std::set<location*> locationSet;	// set for loop Detection during preprocessing

        typedef std::set<Transition<double>*> transitionSet;          // type of the transitions from a location
           
        /*
         *    This method computes additional static information for the specified location
         */   
        void preprocess_location(location* loc, std::vector<matrix_t<double>>* L_pt, double delta, SupportFunction* U, artificialDirections* additionalDirections)
        {
             // preprocessing is done by construction of LocInfo object
             LocationInfo* locInfo = new LocationInfo(loc, L_pt, delta, U, additionalDirections);
             
             // store a mapping between the original location and the object containing the preprocessed information
             LocationPair locPair(loc, locInfo);
             locationMap.insert(locPair);
        }
        
        /*
         *    This method computes additional static information for the specified transition
         */   
        void preprocess_transition(transition* trans, artificialDirections* additionalDirections)
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
		void preprocessing_recursion(location* loc, std::vector<matrix_t<double>>* L_pt, double delta, SupportFunction* U, artificialDirections* additionalDirections)
		{
			if (locationSet.find(loc) != locationSet.end())
			{
                #ifdef TRANSITIONINFO_VERBOSE
                     std::cout << "preprocessing_recursion(...): considered location " << loc << " has already been preprocessed" << BL;
                #endif
				// the location has already been considered
				return;
			}
			else
			{
                #ifdef TRANSITIONINFO_VERBOSE
                     std::cout << "preprocessing_recursion(...): preprocess unprocessed location " << loc << BL;
                #endif
				// this  location has not yet been preprocessed
				locationSet.insert(loc);

				preprocess_location(loc, L_pt, delta, U, additionalDirections);

                #ifdef TRANSITIONINFO_VERBOSE
                     std::cout << "preprocessing_recursion(...): preprocess transitions" << BL;
                #endif
				// preprocess outgoing transitions
				// iterate over outgoing transitions and preprocess them
                // compute preprocessing for transition destinations
				transitionSet transitions = (*loc).transitions();
				for(auto iterator = transitions.begin(); iterator != transitions.end(); ++iterator)
				{
                     preprocess_transition((*iterator), additionalDirections); // preprocess transition
                     preprocessing_recursion((*iterator)->targetLoc(), L_pt, delta, U, additionalDirections); // preprocess connected location
                }
			}
		}
		
		/**
		* Initiates the preprocessing for all locations, connected through paths beginning at an initial location
		*/
	    void preprocess(HybridAutomaton<double>* automaton,std::vector<matrix_t<double>>* L_pt, double delta, SupportFunction* U, artificialDirections* additionalDirections)
	    {
	    	std::set<location*> locations = (*automaton).initialLocations();

	     	for (auto iterator = locations.begin(); iterator != locations.end(); ++iterator)
	      	{
	       		preprocessing_recursion(*iterator, L_pt, delta, U, additionalDirections) ;
	       	}
	       	
	       	// performe evaluation which can only be done if all L are known
	       	// locations:
            
            for(auto iterator = locationMap.begin(); iterator != locationMap.end(); iterator++) 
            {
                // evaluate PolytopeSupportFunction for invariant object in every direction
                delete iterator->second->complete_invariant_evaluation;
                iterator->second->complete_invariant_evaluation = new std::vector<double>(L_pt->size());
                iterator->second->invariantSP->multiEvaluate(L_pt, iterator->second->complete_invariant_evaluation);
                #ifdef LOCATIONINFO_VERBOSE
                       std::cout << "preprocess(...): " << "invariant evaluation for L: " << '\n';
                       printDirectionList(*L_pt);
                       std::cout << "is: " << '\n';
                       print(*(iterator->second->complete_invariant_evaluation));
                       std::cout << '\n';
                #endif
            }    
                                     
	       	#ifdef TRANSITIONINFO_VERBOSE
                 std::cout << "preprocess(...): complete" << BL;
            #endif
        }

        void removePreprocessingMemory()
        {
             // TODO: remove those objects and all objects inside
             //LocationMap locationMap;   
        	 //TransitionMap transitionMap;   
        	 //std::set<location*> locationSet;
        	 
        	 // call freeAllocatedMemory() on every locationinfo object to free LocationInfo resources
        }
