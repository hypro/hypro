/*
 *   This file contains all methods related to the preprocessing procedure
 *   Author: Norman Hansen
 */
 
#define LOCATIONINFO_VERBOSE 
#define TRANSITIONINFO_VERBOSE 
 
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
                       if(L_pt->at(0).rows() > direction->size())     // the entries of L are of higher dimensionality -> fill direction with 0
                       {
                           int dirRows = direction->rows();
                           direction->resize(L_pt->at(0).rows(),1);
                           direction->block(dirRows,0,L_pt->at(0).rows()-dirRows,1) = matrix_t<double>::Zero(1,1);   // fill with 0
                       }
                            
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
                    void normalizeLinearConstraint(matrix_t<double> constraints, matrix_t<double> constraintValues, std::vector<matrix_t<double>>* directions, std::vector<double>* scaledConstraintValues )
                    {
                         std::cout << "normalizeLinearConstraint(...): " << BL << constraints << BL;
                          constraints = addZeroColumn(constraints);  // add additional dimension
                         
                          std::cout << "normalizeLinearConstraint(...): " <<  "constraints.rows(): " << constraints.rows() << BL;
                         
                          double norm = 0;
                          for( int i=0; i<constraints.rows(); i++)
                          {
                               // compute normed and rounded direction
                               matrix_t<double> normedDirection = constraints.row(i).transpose();
                               norm = normedDirection.norm().toDouble();
                               normedDirection = normedDirection/norm;
                               normedDirection = round(normedDirection, precision);
                  
                               // add results for iteration i to the correspondent lists
                               //directions->push_back(normedDirection);
                               directions->at(i) = normedDirection;
                               //scaledConstraintValues->push_back( (constraintValues(i,0)).toDouble()/norm );
                               scaledConstraintValues->at(i) = (constraintValues(i,0)).toDouble()/norm;
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
                    
                    /*
                    * removes zero rows from constraints and the correspondent values in values
                    */
                    void removeZeroRows(matrix_t<double>* constraints, matrix_t<double>* values)
                    {
                         std::cout << "original constraints: " << BL << *constraints << BL << "values: " << (*values).transpose() << BL;
                         
                         std::list<int> nonzerorows(0);   // stores the indices of the rows not beeing zero
                         
                         // backup values
                         matrix_t<double> b_constraints = *constraints;
                         matrix_t<double> b_values = *values;
                         
                         // detect zero rows
                         for(int i=0; i<b_constraints.rows(); i++)
                         {
                             if(!b_constraints.row(i).isZero())
                             {
                                 nonzerorows.push_back(i);
                             }
                         }
                         
                         std::cout << "non-zero-rows: " << nonzerorows << BL;
                         
                         // remove 0related values
                         constraints->resize(nonzerorows.size(),constraints->cols());
                         unsigned int i=0;
                         for(auto iterator = nonzerorows.begin(); iterator != nonzerorows.end(); ++iterator)
                         {
                             constraints->block(i,0,1,constraints->cols()) = b_constraints.row(*iterator);
                             i++;
                         }
                    }
                    
            public:
                    virtual void freeAllocatedMemory() = 0;   // has to be overwritten and will be called to destroy previously created heap objects
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
            for(int i=0; i<loc->activityMat().rows(); i++)
            {
                for(int j=0; j<loc->activityMat().cols(); j++)
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
        
        matrix_t<double> R;
        vector_t<double> w;
        
		SupportFunction* wfunction;

      public:
        // Minimal values of each guard for every direction (or inf if there is no guard in this direction). 
        // May contain "redundant" constraint-values since there is no reconstruction using support functions performed
        // The values are only used to compute the intersection with the guards and during that processing step, the reconstruction and evaluation will be performed
		matrix_t<double> sortedValues;

        mapping I_star_constraints_in_L;
        mapping mirrored_I_star_constraints_in_L;
        std::vector<matrix_t<double>>* IstarAsDirections;
        std::vector<double>* scaledIstarValues;
        
        // guard related values (analog to invariant from location)
		mapping guard_constraints_in_L;
		mapping mirrored_guard_constraints_in_L;
		std::vector<matrix_t<double>>* guardsAsDirections;
        std::vector<double>* scaledGuardValues;
         
        std::vector<double>* g_star_values;  
        
        SupportFunction* getWfunction()
        {
            return wfunction;
        }
        
        matrix_t<double> getR()
        {
            return R;
        }
             
        TransitionInfo(transition* trans, std::vector<matrix_t<double>>* L_pt, artificialDirections* aD)
        {
            #ifdef TRANSITIONINFO_VERBOSE
            std::string method =  "TransitionInfo(...): ";
                std::cout << method << '\n';
            #endif
            
            origTransition = trans;
            //const unsigned int dimensionality = (unsigned int) ((*trans).guard()).mat.cols(); 
            unsigned int guards = (unsigned int) ((*trans).guard()).mat.rows();    // Assuption: the model contains only <= guards
            unsigned int targetInv = (unsigned int) trans->targetLoc()->invariant().mat.rows();
            
            // create new objects on the heap to store relevant information
            I_star_constraints_in_L = new unsigned int[targetInv];
            mirrored_I_star_constraints_in_L = new unsigned int[targetInv];
            IstarAsDirections = new std::vector<matrix_t<double>>(targetInv);
            scaledIstarValues = new std::vector<double>(targetInv);
            
            guard_constraints_in_L = new unsigned int[guards];
            mirrored_guard_constraints_in_L = new unsigned int[guards];
            guardsAsDirections = new std::vector<matrix_t<double>>(guards);
            scaledGuardValues = new std::vector<double>(guards);
            #ifdef TRANSITIONINFO_VERBOSE
                std::cout << method << "fields initialized" << BL;
            #endif
            
            // extend R and w according to the artifically created dimension
            R = addZeroColumn(trans->assignment().transformMat);
            R = addZeroRow(R);
            R(R.rows()-1,R.cols()-1) = 1;
            
            // generate automatically the additional information for transitions
 
            // construct support function wfunction
            unsigned int dim = L_pt->at(0).size();
            matrix_t<double> identity(dim, dim);
            identity.setIdentity();
            #ifdef TRANSITIONINFO_VERBOSE
                std::cout << method << "identity: " << BL << identity << BL;
            #endif
            matrix_t<double> id(2*identity.rows(),identity.cols());
            id.block(0,0,dim,dim) = identity;
            id.block(dim,0,dim,dim) = -identity;
            #ifdef TRANSITIONINFO_VERBOSE
                std::cout << method << "id: " << BL << id << BL;
            #endif
            matrix_t<double> w_local(2*dim,1);
            #ifdef TRANSITIONINFO_VERBOSE
                std::cout << method << "w_local: " << BL << w_local << BL;
            #endif
            // extend w if necessary due to additional dimension
            for(int i=0; i<=trans->assignment().translationVec.size(); i++)
            {
                w_local(i,0) = i<trans->assignment().translationVec.size() ? trans->assignment().translationVec(i) : 1;
                w_local(i+dim,0) = i<trans->assignment().translationVec.size() ? - trans->assignment().translationVec(i) : -1;
            }
            this->w = w_local;
            #ifdef TRANSITIONINFO_VERBOSE
                std::cout << method << "w_local: " << BL << w_local << BL;
                std::cout << method << "this->w: " << BL << this->w << BL;
            #endif
 
            wfunction = new PolytopeSupportFunction(id,this->w,operator_e::LEQ, dim, aD);
            #ifdef TRANSITIONINFO_VERBOSE
                std::cout << method << "wfunction created" << BL;
            #endif
            
            // handle guard (assumption: only inequality guards -> no need to differentiate between different guard types)
            // normalize every guard constraint
            normalizeLinearConstraint(((*trans).guard()).mat,((*trans).guard()).vec, guardsAsDirections, scaledGuardValues);
            #ifdef TRANSITIONINFO_VERBOSE
                std::cout << method << "normalized guards: " << BL;
                printDirectionList(*guardsAsDirections);
                std::cout << "scaled values: " << BL;
                std::cout << *scaledGuardValues << BL;
            #endif
            // compute mapping and add missing directions to L
            guard_constraints_in_L = extendDirections(L_pt,guardsAsDirections);
            mirrored_guard_constraints_in_L = extendMirroredDirections(L_pt,guardsAsDirections);
            #ifdef TRANSITIONINFO_VERBOSE
                std::cout << "guard_constraints_in_L: ";
                printArray<unsigned int>(guard_constraints_in_L, guardsAsDirections->size());
                std::cout << BL <<  method << "guards preprocessed" << BL;
            #endif
            
            // generate I*
            matrix_t<double> I_star_constraints = trans->targetLoc()->invariant().mat;     // initialize I* (values are not important, size is)
		    matrix_t<double> I_star_values(I_star_constraints.rows(),1);

            matrix_t<double> temp;
            for(unsigned int i=0; i<targetInv; i++)
            {
                I_star_constraints.block(i,0,1,I_star_constraints.cols()) = trans->targetLoc()->invariant().mat.row(i) * trans->assignment().transformMat;
                temp = - trans->targetLoc()->invariant().mat.row(i).transpose();
                I_star_values(i,0) = trans->targetLoc()->invariant().vec(i) + wfunction->evaluate(&temp).supportValue;               
            }
            #ifdef TRANSITIONINFO_VERBOSE
                std::cout << method << "I* first step" << BL;
            #endif
        
            //discard 0 entries -> would lead to unecessary tautologies in the equations
            removeZeroRows(&I_star_constraints, &I_star_values);
            #ifdef TRANSITIONINFO_VERBOSE
                std::cout << method << "zero rows removed" << BL;
            #endif
                        
            // scale, round, delete redundant and add to L with correspondent mapping                        
            normalizeLinearConstraint(I_star_constraints,I_star_values, IstarAsDirections, scaledIstarValues);
            I_star_constraints_in_L = extendDirections(L_pt,IstarAsDirections);
            mirrored_I_star_constraints_in_L = extendMirroredDirections(L_pt,IstarAsDirections);
            #ifdef TRANSITIONINFO_VERBOSE
                std::cout << method << "I* preprocessed" << BL;
            #endif
        }     
        
        void freeAllocatedMemory()
        {
             // delete constructed heap objects
            //delete[] iminus_constraints_in_L;
            //delete[] mirrored_iminus_constraints_in_L;
            //delete[] iplus_constraints_in_L;
            //delete[] mirrored_iplus_constraints_in_L;
            delete[] guard_constraints_in_L;
            delete[] mirrored_guard_constraints_in_L;
            delete[] I_star_constraints_in_L;
            delete[] mirrored_I_star_constraints_in_L;
            
            delete guardsAsDirections;
            delete scaledGuardValues;
            delete IstarAsDirections;
            delete scaledIstarValues;
            
            delete wfunction;
            delete g_star_values;
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
        void preprocess_transition(transition* trans, std::vector<matrix_t<double>>* L_pt, artificialDirections* additionalDirections)
        {
             // preprocessing is done by construction of TransInfo object
             TransitionInfo* transInfo = new TransitionInfo(trans, L_pt, additionalDirections);
             
             // store a mapping between the original transition and the object containing the preprocessed information
             TransitionPair transPair(trans, transInfo);
             transitionMap.insert(transPair);
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
                #ifdef LOCATIONINFO_VERBOSE
                     std::cout << "preprocessing_recursion(...): considered location " << loc << " has already been preprocessed" << BL;
                #endif
				// the location has already been considered
				return;
			}
			else
			{
                #ifdef LOCATIONINFO_VERBOSE
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
                     preprocess_transition((*iterator), L_pt, additionalDirections); // preprocess transition
                     
                     #ifdef TRANSITIONINFO_VERBOSE
                         std::cout << "preprocessing_recursion(...): recursive call follows" << BL;
                     #endif
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
            
            // transitions
            
            // precompute G* and sorted values for every transition in the model (can only be done when L is complete)
            matrix_t<double> temp(L_pt->size(),1); 
            for(auto iterator = transitionMap.begin(); iterator != transitionMap.end(); ++iterator)
            {
                // Gstar
                
                delete iterator->second->g_star_values;
                iterator->second->g_star_values = new std::vector<double>(L_pt->size());
                // initialize g_star with Inf
                for(int i=0; i< temp.size(); i++)
                {
                    temp(i,0) = INFINITY;
                }
                
                // intersect with guards
                for(unsigned int i=0; i<iterator->second->guardsAsDirections->size(); i++)
                {
                    temp(iterator->second->mirrored_guard_constraints_in_L[i],0) = MIN(temp(iterator->second->mirrored_guard_constraints_in_L[i],0).toDouble(),iterator->second->scaledGuardValues->at(i));
                }
                
                // intersect with istar
                for(unsigned int i=0; i<iterator->second->IstarAsDirections->size(); i++)
                {
                    temp(iterator->second->mirrored_I_star_constraints_in_L[i],0) = MIN(temp(iterator->second->mirrored_I_star_constraints_in_L[i],0).toDouble(),iterator->second->scaledIstarValues->at(i));
                }
                
                SupportFunction* gstar = new PolytopeSupportFunction(L_pt,temp,L_pt->at(0).size(),additionalDirections);
                gstar->multiEvaluate(L_pt,iterator->second->g_star_values);
                #ifdef TRANSITIONINFO_VERBOSE
                    std::cout << "preprocess(...): " << "G*: " << BL;
                    print(*(iterator->second->g_star_values));
                    std::cout << '\n';
                #endif
                
                // sorted values (do not need to be re-evaluated since this will be done when computing the intersection)
                
                for(int i=0; i< temp.size()-2; i++)
                {
                    temp(i,0) = INFINITY;
                }
                //last 2 entries are artificial
                temp(temp.size()-2,0) = 1;
                temp(temp.size()-1,0) = -1;
                
                // intersect with guards
                for(unsigned int i=0; i<iterator->second->guardsAsDirections->size(); i++)
                {
                    temp(iterator->second->guard_constraints_in_L[i],0) = MIN(temp(iterator->second->guard_constraints_in_L[i],0).toDouble(),iterator->second->scaledGuardValues->at(i));
                }
                iterator->second->sortedValues = temp;
                #ifdef TRANSITIONINFO_VERBOSE
                    std::cout << "preprocess(...): " << "sorted Values: " << (iterator->second->sortedValues) << BL;
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
       	     // call freeAllocatedMemory() on every transitioninfo object to free LocationInfo resources
        }
