 /*
 *  This file contains th main class providing the functionality to compute the reachable sets
 *  of an hybrid automaton using support functions.
 *  
 *  Important notes:
 *  - The method assumes, that all guards/invariants and constraints are provided in a normal form 
 *    using only <= as comparison operator
 *  - 
 *
 *  Author: Norman Hansen
 */


#include "hyreach_utils.h"

//#define FILE_OUTPUT  //defining FILE_OUTPUT will lead to the creation of text files with the generated flowpipe segments in matlab syntax

// Verbosity levels
//#define VECTOR_GEN_VERBOSE
//#define HELPER_METHODS_VERBOSE
//#define SUPPORTFUNCTION_VERBOSE
//#define FLOWPIPE_VERBOSE
//#define HYREACH_VERBOSE
//#define PARALLHELPER_VERBOSE

using namespace::std;

namespace hypro
{
    const unsigned int precision = 10000;
          
    #include "preprocessing.h"      
          
	/*
    * Strucutre defining the options for the reachability algorithm to use
    */
    struct options {
           double angle;     // angle for the direction generation
//	       bool preclustering;	// true enables preclustering
//	       bool fixpointDetection;	// true enables fixpoint detection
//	       double fixpoint_tolerance;	// in case fixpoint detection is enabled, two values are considered equal with regard to this value
//	       unsigned int fixpoint_interval;	// the check for fixpoints is performed every fixpoint_interval'th step
	       unsigned int precision;
	};

    /*
    * Structure describing the general parameters for the algorithm to use
    */
    struct parameters {
	       double timeHorizon;
	       double timeStep;
	       unsigned int setsToCompute;  // (N) = timeHorizon/timeStep
	       unsigned int numberOfTransitions;	// there will n more transitions be considered then indicated by this value
    	};	
        
    class HyReach
    {
      private:
         options opt;
         parameters params;
         
         std::vector<matrix_t<double>> L; // list of directions
         artificialDirections additionalDirections;
         
         unsigned int dimensionality;
         int* oppositeDirectionMapping; // array of indexis mapping each direction to its opposite direction
         
         #include "intersectionmethods.h"
         #include "CleanupOnExit.h"
         
         CleanupOnExit cleanup_class(); // private instance of the cleanup class. 
                                        // Without this field, the cleanup classes destructor would not be used
                                        // to free some ressources automatically when the HyReach object is deleted
                                                 
         // datastructure to store the computed evaluation results     
         std::list<FlowpipeSegment*> results;  
         
         /*
         * This method computes the results for a single direction and its opposite and stores the evaluation results directly into a flowpipeSegment object.
         * Returns the index of the last computed entry for the directions in the flowpipe.
         */
         unsigned int parallelizationHelper(FlowpipeSegment* results, LocationInfo* locInfo, SupportFunction* X0, SupportFunction* epsilonpsi, matrix_t<double>* l, unsigned int indexL, matrix_t<double>* l_opposite, unsigned int indexL_opposite)
         {
              #ifdef PARALLHELPER_VERBOSE
                  std::string method = "parallelizationHelper: ";
                  std::cout << method << "indexL: " << indexL << " opposite: " << indexL_opposite << BL;
                  std::cout << "setsToCompute(max): " << params.setsToCompute << BL;
              #endif
              
              unsigned int j=0;
              
              matrix_t<double> r_old = *l;
              matrix_t<double> r_old_minus = - *l;
              matrix_t<double> r_i = *l;
              matrix_t<double> r_i_minus = - *l;
              
              double s_old = 0;
              double s_old_minus = 0;
              double s_i = 0;
              double s_i_minus = 0;
              
              double k_old = INFINITY;
              double k_old_minus = INFINITY;
              double k_i = INFINITY;
              double k_i_minus = INFINITY;
              
              SupportFunction* I = locInfo->invariantSP;
              
              double p_omega = X0->evaluate(l).supportValue;
              double p_omega_minus = X0->evaluate(l_opposite).supportValue;
              #ifdef PARALLHELPER_VERBOSE
                  std::cout << method << "omega evaluated" << BL;
              #endif
              
              double p_I = I->evaluate(l).supportValue;
              double p_I_minus = I->evaluate(l_opposite).supportValue;
              #ifdef PARALLHELPER_VERBOSE
                  std::cout << method << "p_i evaluated" << BL;
              #endif
              double I_minus = -p_I_minus;
              double I_plus = -p_I;
              
              //res(1,1) = min(p_omega,p_I);    
              //res(2,1) = min(X0(-l),p_I_minus);  
              matrix_t<double> eA = locInfo->edA.transpose();
              
              #ifdef PARALLHELPER_VERBOSE
                  std::cout << method << "start while ..." << BL;
              #endif
              while (results->sets(indexL,j) >= I_minus && j < params.setsToCompute && results->sets(indexL_opposite,j) >= I_plus)
              {
                    j++;
                    
                    r_i = eA * r_old;
                    r_i_minus = -r_i;
                    
                    #ifdef PARALLHELPER_VERBOSE
                        std::cout << method << "r_i = " << BL << r_i << BL;
                        std::cout << method << "r_i_minus = " << BL << r_i_minus << BL;
                    #endif
                    
                    s_i = s_old + epsilonpsi->evaluate(&r_old).supportValue;
                    s_i_minus = s_old_minus + epsilonpsi->evaluate(&r_old_minus).supportValue;  
                    #ifdef PARALLHELPER_VERBOSE
                        std::cout << method << "s_i evaluated" << BL;
                        std::cout << "s_i = " << s_i << BL;
                        std::cout << "s_i_minus = " << s_i_minus << BL;
                    #endif
            
                    p_omega = X0->evaluate(&r_i).supportValue + s_i;
                    p_omega_minus = X0->evaluate(&r_i_minus).supportValue + s_i_minus;
                    #ifdef PARALLHELPER_VERBOSE
                        std::cout << method << "p_omega evaluated" << BL;
                        
                        std::cout << "p_omega = " << p_omega << BL;
                        std::cout << "p_omega_minus = " << p_omega_minus << BL;
                    #endif
                    
                    k_i = MIN(k_old,p_I);
                    k_i_minus = MIN(k_old_minus,p_I_minus);
                    #ifdef PARALLHELPER_VERBOSE                        
                        std::cout << "k_i = " << k_i << BL;
                        std::cout << "k_i_minus = " << k_i_minus << BL;
                    #endif
            
                    p_I = I->evaluate(&r_i).supportValue + s_i;
                    p_I_minus = I->evaluate(&r_i_minus).supportValue + s_i_minus;
                    #ifdef PARALLHELPER_VERBOSE
                        std::cout << method << "p_I evaluated" << BL;
                        
                        std::cout << "p_I = " << p_I << BL;
                        std::cout << "p_I_minus = " << p_I_minus << BL << BL << BL;
                    #endif
                    
                    results->sets(indexL,j) = MIN(p_omega,k_i);
                    results->sets(indexL_opposite,j) = MIN(p_omega_minus,k_i_minus);
                    #ifdef PARALLHELPER_VERBOSE
                        std::cout << method << "results:" << BL;
                        
                        std::cout << "+ = " << results->sets(indexL,j) << BL;
                        std::cout << "- = " << results->sets(indexL_opposite,j) << BL;
                    #endif

                    r_old = r_i;
                    r_old_minus = r_i_minus;
                    s_old = s_i;
                    s_old_minus = s_i_minus;
                    k_old = k_i;
                    k_old_minus = k_i_minus;

                    // if it does not fall into the invariant, cut it later out and stop analysis
                    if ((p_omega_minus>I_plus && results->sets(indexL,j) < I_minus) || (p_omega>I_minus && results->sets(indexL_opposite,j) < I_plus))   
                    { 
                        #ifdef PARALLHELPER_VERBOSE
                            std::cout << BL << method << "return because of complete invariant violation" << BL;
                        #endif
                        return j-1;
                    }           
               }
               
               #ifdef PARALLHELPER_VERBOSE
                   std::cout << BL << method << "return after complete loop" << BL;
               #endif
               return j;
         }
         
         /*
         * Constructs the flowpipe according to algoInv
         * loc: pointer to the location in the original model which will be analyzed
         * locInfo: pointer to the LocationInfo object storing the precomputed values for the location being analyzed
         * X0: pointer to support function describing the initial set (for this location)
         * U: pointer to the support function describing the free input
         */
         FlowpipeSegment* constructFlowpipe(location* loc, LocationInfo* locInfo, SupportFunction* X0, SupportFunction* U, unsigned int timeStep)
         {
              #ifdef FLOWPIPE_VERBOSE
                  std::string method = "constructFlowpipe(...): ";
              #endif
              
              // create flowpipe segment
              FlowpipeSegment* flowpipe = new FlowpipeSegment(loc,timeStep,L.size(), params.setsToCompute);
              flowpipe->startTimestep = timeStep;
                  
              matrix_t<double> X0_values(L.size(),1); // stores the evaluation of X0
              X0->multiEvaluate(&L, &X0_values);
              
              #ifdef FLOWPIPE_VERBOSE
                      std::cout << method << "X0 evaluation':" << X0_values.transpose() << '\n';
                      
                      matrix_t<double> V_values(L.size(),1);
                      (locInfo->V)->multiEvaluate(&L, &V_values);
                      std::cout << method << "V evaluation':" << V_values.transpose() << '\n';
              #endif
              
              // test for an intersection between X0 and the invariant
              if(testIntersection(locInfo->scaledConstraintValues,locInfo->mirrored_invariant_constraints_in_L, X0_values, locInfo->scaledConstraintValues->size(), false))
              {
                  #ifdef FLOWPIPE_VERBOSE
                      std::cout << method << "testIntersection: true" << BL;
                      std::cout << "............. begin Omega0 construction" << BL;
                  #endif
                  
                  // compute flowpipe
                  // edA = delta * A -> precomputed in LocationInfo
                  // V = calcpV(B,U) -> precomputed in LocationInfo
                  
                  matrix_t<double>* A = locInfo->getA();
                  
                  // compute Omega0
                  NonLinearOmega0Supportfunction omega0( A, (locInfo->V), X0, params.timeStep, &additionalDirections);
                  matrix_t<double> omega0_values(L.size(),1); // stores the evaluation of omega0
                  omega0.multiEvaluate(&L, &omega0_values);
                  #ifdef FLOWPIPE_VERBOSE
                      std::cout << method << "omega0' evaluation: " << omega0_values.transpose() << '\n';
                  #endif
                  
                  // intersect Omega0 with invariant
                  //values(state.invariant_constraints_in_L) = min(values(state.invariant_constraints_in_L),state.d);
                  omega0_values = intersectWithInvariant(omega0_values, locInfo->invariant_constraints_in_L, locInfo->scaledConstraintValues);
                  
                  #ifdef FLOWPIPE_VERBOSE
                      std::cout << method << "omega0' intersecting invariant" << omega0_values.transpose() << '\n';
                      std::cout << "............. terminated Omega0 construction" << BL;
                  #endif
                  
                  
                  // reconstruct omega0 intersects invariant and re-evaluate (creates tight constraints)
                  PolytopeSupportFunction set0(&L, omega0_values, dimensionality, &additionalDirections);
                  
                  double* set0_values = new double[L.size()]; // stores the evaluation of set0 (heap!)
                  set0.multiEvaluate(&L, set0_values);
              
                  #ifdef FLOWPIPE_VERBOSE
                      std::cout << method << "set0 of the flowpipe:"; //<< set0_values << '\n';
                      printArray<double>(set0_values, L.size()); 
                      std::cout <<  "OK" << BL;
                  #endif
    
                  // add first computed set to the flowpipe (omega0 intersects invariant)
                  flowpipe->addSetAtPosition(set0_values,0);
                  delete[] set0_values;
    
                  #ifdef FLOWPIPE_VERBOSE
                      std::cout << method << "added set0 to flowpipe" << BL;
                  #endif
                  // psidelta is needed for the algorithm
                  SupportFunction* multiplicationtemp = locInfo->V->multiply(params.timeStep);
                  #ifdef FLOWPIPE_VERBOSE
                      std::cout << method << "created multiplicationtemp" << BL;
                  #endif
                  SupportFunction* psidelta = multiplicationtemp->minowskisum(omega0.getEpsilonpsi());
                  #ifdef FLOWPIPE_VERBOSE
                      std::cout << method << "created psidelta" << BL;
                  #endif
                     
                  // start with the iteration of successive timesteps
                  unsigned int maxNumberOfCompleteSets = params.setsToCompute;
                  std::vector<int> processedDirections;
                  // 2 artificial directions will not be processed
                  // therefore start with index 2
                  unsigned int i=2;
                  while(processedDirections.size() != L.size()-2)     
                  {
                      #ifdef FLOWPIPE_VERBOSE
                          std::cout << method << "iterate over direction number: " << i << BL;
                      #endif
                      int oppositeOfDirectionI = oppositeDirectionMapping[i];
                      if(oppositeOfDirectionI < 0)
                      {
                          std::cout << "opposite direction missing (or not found)" << '\n';
                      }
                      
                      if( !listContains(&processedDirections, (int) i))
                      { 
                          #ifdef FLOWPIPE_VERBOSE
                              std::cout << method << " not yet processed " << i << BL;
                          #endif
                          unsigned int j = parallelizationHelper(flowpipe, locInfo, &set0, omega0.getEpsilonpsi(), &L.at(i), i, &L.at(oppositeOfDirectionI), oppositeOfDirectionI);
                          maxNumberOfCompleteSets = MIN(maxNumberOfCompleteSets, j);  
                          #ifdef FLOWPIPE_VERBOSE
                              std::cout << method << " maxNumberOfCompleteSets = MIN(" << maxNumberOfCompleteSets << ", " << j << ") " << BL;
                          #endif
                          
                          // mark processed directions as processed (by indices)
                          processedDirections.push_back(i);
                          processedDirections.push_back(oppositeOfDirectionI);  
                          
                          #ifdef FLOWPIPE_VERBOSE
                              std::cout << method << " processing succesfull " << BL;
                          #endif            
                      }
                      #ifdef FLOWPIPE_VERBOSE
                          else
                          {
                              std::cout << method << " already processed "<< BL;
                          }
                      #endif
                      
                      i++;
                  }
                  
                  #ifdef FLOWPIPE_VERBOSE
                      std::cout << method << "maxNumberOfCompleteSets: " << maxNumberOfCompleteSets << BL;
                      std::cout << method << "flowpipe sets: " << BL << flowpipe->sets << BL << BL;
                      
                      //std::cout << "rows: " << flowpipe->sets.rows() <<  " cols: " << flowpipe->sets.cols();
                  #endif
                  
                  // cut evaluation values which are not needed
                  matrix_t<double> temp = flowpipe->sets.block(0,0,L.size(),maxNumberOfCompleteSets+1);
                  flowpipe->sets = temp;
                  
                  // insert artificial evaluations for additional dimensions
                  matrix_t<double> constant(2,flowpipe->sets.cols());
                  for(int i= 0; i<flowpipe->sets.cols(); i++)
                  {
                          constant(0,i) = 1;
                          constant(1,i) = -1;
                  }
                  flowpipe->sets.block(0,0,2,flowpipe->sets.cols()) = constant;
                  
                  #ifdef FLOWPIPE_VERBOSE
                      std::cout << method << "reduced sets: " << BL << flowpipe->sets << BL;
                  #endif
                   
                  // conversions in order to reconstruct non-redundant results (or should this be done instantly?)
                  //matrix_t<double> temp_values(L.size(),1);
                  double* temp_values = new double[L.size()];
                  for( unsigned int i=1; i<=maxNumberOfCompleteSets; i++)      // first set has already been re-evaluated
                  {
                       #ifdef FLOWPIPE_VERBOSE
                           std::cout << method << "reevaluate set " << i << ": " << BL;
                       #endif
                       PolytopeSupportFunction temp( &L, flowpipe->sets.col(i), dimensionality, &additionalDirections);
                       temp.multiEvaluate(&L,temp_values);
                       flowpipe->addSetAtPosition(temp_values,i);
                  }
                  delete[] temp_values;
                  
                  #ifdef FLOWPIPE_VERBOSE
                      std::cout << "flowpipe:" << BL << flowpipe->sets << BL;
                      // store flowpipe in file
                  #endif
                  
                  #ifdef FILE_OUTPUT    
                      char* buffer = new char[200];
                      sprintf(buffer, "matlab_flowpipe_loc%d_time%d.txt", loc, timeStep);
                      matrixToMatlab(buffer, flowpipe->sets);
                  #endif
                  
                  // clear temporary used memory from the heap
                  delete multiplicationtemp;
                  delete psidelta;
              }
              else
              {
                  // no flowpipe constructed because X0 does not satisfy the invariant
                  #ifdef FLOWPIPE_VERBOSE
                      std::cout << method << "no flowpipe constructed because intersection between X0 and the invariant is empty" << '\n';
                  #endif
              }
              
              return flowpipe;
         }    
          
         #include "transitionhandling.h"
          
         /*
         * Method to construct the flowpipe (called recursively by itself dependent on recursionNumber)
         * loc: pointer to the location in the original model which will be analyzed
         * recursionNumber: number of recursions left to performe
         * X0: pointer to support function describing the initial set (for this location)
         * U: pointer to the support function describing the free input
         */   
         void analyze(location* loc, unsigned int recursionNumber, SupportFunction* X0, SupportFunction* U, unsigned int timeStep)
         {
             #ifdef HYREACH_VERBOSE
                 std::string method = "analyze(...): ";
                 std::cout << method << "recursionNumber:" << recursionNumber << BL;
             #endif  
             
              if( recursionNumber > 0)        // compute flowpipe only if there is a further recursion to performe
              {
                  // compute Flowpipe
                  FlowpipeSegment* flowpipe = constructFlowpipe(loc, (locationMap.find(loc)->second), X0, U, timeStep); //algoInv
                  #ifdef HYREACH_VERBOSE
                      std::cout << method << "flowpipe constructed" << BL;
                  #endif
                  // add segment to the final flowpipe (results)
                  results.push_back(flowpipe);
                  
                  // detect possible transitions -> flowpipe might NOT be shortened dependend on the chosen transition -> due to use of algoinv only reachable (in the invariant) sets are computed!
                  std::vector<possibleTransition*>* possibleTransitions = getPossibleTransitions(loc, flowpipe);
                  #ifdef HYREACH_VERBOSE
                      std::cout << method << "#possibleTransitions:" << possibleTransitions->size() << BL;
                  #endif
             
                  // choose which transition to take -> Assuption: all
                  // iterate over this list and do for each the required transition handling:
                  matrix_t<double> valuesForNextSet;    
                  TransitionInfo* transitionInfo = 0;                
                  for(auto iterator = possibleTransitions->begin(); iterator != possibleTransitions->end(); ++iterator)
                  {    
                      #ifdef HYREACH_VERBOSE
                           std::cout << method << "considering transition: " << BL;
                      #endif 
                              
                      // Note: iterator is a pointer to possibleTransition structure
                      transitionInfo = transitionMap.find((*iterator)->transition_pt)->second;
                      
                      // cluster always all sets
                      valuesForNextSet = clustering(**iterator); // cluster all sets which are relevant for the construction of the initial set for the next node
                      #ifdef HYREACH_VERBOSE
                           std::cout << method << "clustered values: " << valuesForNextSet.transpose() << BL;                           
                      #endif 
                      
                      // compute intersection                      
                      valuesForNextSet = intersect(transitionInfo->sortedValues, valuesForNextSet);
                      #ifdef HYREACH_VERBOSE
                           std::cout << method << "valuesForNextSet: " << valuesForNextSet.transpose() << BL;                          
                      #endif 
                      // reconstruct and evaluate to create tight bounds
                      SupportFunction* intersectedSet = new PolytopeSupportFunction(&L,valuesForNextSet,X0->getAD()->dir1.size(),X0->getAD());
                      #ifdef HYREACH_VERBOSE
                           matrix_t<double> temp(valuesForNextSet.rows(),1);
                           intersectedSet->multiEvaluate(&L, &temp);  // does not need to be done if reset is applied directly
                           std::cout << method << "intersectedSet evaluation: " << temp.transpose() << BL << BL;
                      #endif 
                      
                      // compute reset
                      SupportFunction* resetTemp = intersectedSet->multiply(transitionInfo->getR());
                      #ifdef HYREACH_VERBOSE
                           matrix_t<double> resetTemp_values(L.size(),1);
                           resetTemp->multiEvaluate(&L,&resetTemp_values);
                           std::cout << method << "resetTemp evaluation: " << BL << resetTemp_values.transpose() << BL << BL;
                           
                           matrix_t<double> w(L.size(),1);
                           transitionInfo->getWfunction()->multiEvaluate(&L, &w);
                           std::cout << method << "w evaluation: " << w.transpose() << BL;
                      #endif
                      
                      SupportFunction* resetSet = resetTemp->minowskisum(transitionInfo->getWfunction());
                      matrix_t<double> resetSet_values(L.size(),1);
                      resetSet->multiEvaluate(&L,&resetSet_values);
                      // explicitely set the values for the artificial directions back to the constants and reconstruct the SupportFunction
                      // this is necessary because the evaluation along the additional dimension of W() and resetTemp() is 1 (or -1) and thus the sum is 2 (or -2)
                      // which are no valid values for evaluations along the additional dimensions.
                      // Setting the evaluation of W() along those directions to 0 yields in a worst case scenario (everything is zero in a PolytopeSupportFunction)
                      // where optimization errors occure.
                      resetSet_values(0,0) = 1;
                      resetSet_values(1,0) =-1;
                      #ifdef HYREACH_VERBOSE
                           std::cout << method << "resetSet evaluation: " << BL << resetSet_values.transpose() << BL;
                      #endif
                   
                      // start next Recursion (recursive call of this method)
                      PolytopeSupportFunction nextX0(&L, resetSet_values, dimensionality, &additionalDirections);
                      analyze( (*iterator)->transition_pt->transition().locTarget, recursionNumber-1, &nextX0, U, (timeStep + 1 + (*iterator)->sets.begin()->start)); /*flowpipe->size()*/
                      
                      // free memory
                      delete resetSet;
                      delete resetTemp;
                      delete intersectedSet;
                  }
                 
                  freePossibleTransitions(possibleTransitions);   // free allocated memory
                  delete possibleTransitions;
              }
         }   
            
	  public:    	
        
        /*
         *   Initiates the start of the hybrid analysis
         */
        void start(HybridAutomaton<double, valuation_t<double>>* model, parameters params, options opt, matrix_t<double> X0constraints,operator_e op, vector_t<double> X0constraintValues, SupportFunction* U_param)
        {
             CleanupOnExit::removeFlowpipeSegments(&results); // remove potential previously computed results
             results.clear();
             #ifdef HYREACH_VERBOSE
                 std::string method = "start(): ";
                 std::cout << method << "initial results:" << BL;
                 std::cout << results << BL;
             #endif  
                        
             // copy the input values
             this->params = params;
             this->opt = opt;
             
             // generate basic direction vectors
             unsigned int dimensions = getDimensionality(model);
             L = vectorgeneratorEXT(dimensions, opt.angle, opt.precision);
             #ifdef HYREACH_VERBOSE
                 std::cout << method << "original L:" << BL;
                 std::cout << L << BL;
             #endif  
             std::vector<matrix_t<double>>* newL = 0;
             additionalDirections = extendDimensions(&L, &newL);
             L = *newL;
             #ifdef HYREACH_VERBOSE
                 std::cout << method << "extended L:" << BL;
                 std::cout << L << BL;
                 std::cout << method << "additionalDirections:" << BL;
                 std::cout << "dir1':" << additionalDirections.dir1.transpose() << BL;
                 std::cout << "dir2':" << additionalDirections.dir2.transpose() << BL;
             #endif  
             
             SupportFunction* U = U_param;
             if( U == 0 )   // use zero function if none provided
             {
                 U = new ZeroSupportFunction(dimensionality, 0); // 2nd parameter 0 will disable special handling for artificial directions during evaluation (since U does not know any additional dimension - will be introduced using B)
                 #ifdef HYREACH_VERBOSE
                     std::cout << method << "U is ZeroSupportFunction" << BL;
                     matrix_t<double> u_eval(L.size(),1);
                     U->multiEvaluate(&L, &u_eval);
                     std::cout << method << "U evaluation:" << BL << u_eval << BL;
                 #endif
             }
             
             #ifdef HYREACH_VERBOSE
                 std::cout << BL << BL << method << "start preprocessing .... ------------------------------------------------------------------------" << BL;
             #endif
             // start preprocessing
             preprocess(model, &L, params.timeStep, U, &additionalDirections);
             #ifdef HYREACH_VERBOSE
                 std::cout << method << "preprocessing completed. ------------------------------------------------------------------------ " << BL << BL;
                 
                 std::cout << method << "final L:" << BL;
                 std::cout << L << BL;
             #endif
             
             oppositeDirectionMapping = computeDirectionMapping(&L);    // can only be done after preprocessing because preprocessing may introduce additional directions
             #ifdef HYREACH_VERBOSE
                 std::cout << method << "oppositeDirectionMapping L:" << BL;
                 printArray<int>(oppositeDirectionMapping, L.size());
                 std::cout << BL;
             #endif  
             dimensionality = (unsigned int)L[0].size();            // extended with additional dimensionality
                
             // Create X0 SupportFunction (extended by additional dimension)
             #ifdef HYREACH_VERBOSE
                 std::cout << method << "original X0constraints: " << BL;
                 std::cout << X0constraints << BL;
                 std::cout << method << "original X0values: " << BL;
                 std::cout << X0constraintValues << BL;
             #endif
             X0constraints = addZeroColumn(X0constraints);
             #ifdef HYREACH_VERBOSE
                 std::cout << method << "extended X0constraints: " << BL;
                 std::cout << X0constraints << BL;
             #endif
             SupportFunction* X0 = new PolytopeSupportFunction(X0constraints,X0constraintValues, op, dimensionality, &additionalDirections);
                                        
             // start analysis (for every initial location)
             std::set<location*> initialLocations = model->initialLocations();

	     	 for (auto iterator = initialLocations.begin(); iterator != initialLocations.end(); ++iterator)
	      	 {
                #ifdef HYREACH_VERBOSE
                    std::cout << method << "start analysis ... ----------------------" << BL;
                #endif 
	       		analyze(*iterator, params.numberOfTransitions, X0, U, 0);   // initiate recursion
	       	 }
	       	 #ifdef HYREACH_VERBOSE
                 std::cout << method << "analysis done. -----------------------------" << BL;
             #endif
             
             // clear memory
             
	       	 delete X0;
	       	 if(U_param == 0) // delete 0 only if it has been constructed by this function
	       	 {
	       	     delete U;
             }
	       	 
	       	 removePreprocessingMemory();
        }
    
        /*
        * Getter for the generated results
        */
        std::list<FlowpipeSegment*> getResults()
        {
            return results;
        }
        
        ~HyReach()
        {
             CleanupOnExit::removeFlowpipeSegments(&results);
             //removePreprocessingMemory(); -> done at the end of start();
        }
    };
