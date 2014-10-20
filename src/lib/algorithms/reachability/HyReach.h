#include "hyreach_utils.h"

// Verbosity levels
//#define VECTOR_GEN_VERBOSE
//#define HELPER_METHODS_VERBOSE
//#define SUPPORTFUNCTION_VERBOSE
#define FLOWPIPE_VERBOSE
#define HYREACH_VERBOSE

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
              double p_I = I->evaluate(l).supportValue;
              double p_I_minus = I->evaluate(l_opposite).supportValue;
              double I_minus = -p_I_minus;
              double I_plus = -p_I;
              
              //res(1,1) = min(p_omega,p_I);    
              //res(2,1) = min(X0(-l),p_I_minus);  
              matrix_t<double> eA = locInfo->edA.transpose();
              
              while (results->sets(indexL,j) >= I_minus && j < params.setsToCompute && results->sets(indexL_opposite,j) >= I_plus)
              {
                    j++;
                    
                    r_i = eA * r_old;
            
                    s_i = s_old + epsilonpsi->evaluate(&r_old).supportValue;
                    s_i_minus = s_old_minus + epsilonpsi->evaluate(&r_old_minus).supportValue;  
            
                    p_omega = X0->evaluate(&r_i).supportValue + s_i;
                    p_omega_minus = X0->evaluate(&r_i_minus).supportValue + s_i_minus;
            
                    k_i = MIN(k_old,p_I);
                    k_i_minus = MIN(k_old_minus,p_I_minus);
            
                    p_I = I->evaluate(&r_i).supportValue + s_i;
                    p_I_minus = I->evaluate(&r_i_minus).supportValue + s_i_minus;

                    results->sets(indexL,j) = MIN(p_omega,k_i);
                    results->sets(indexL_opposite,j) = MIN(p_omega_minus,k_i_minus);

                    r_old = r_i;
                    r_old_minus = r_i_minus;
                    s_old = s_i;
                    s_old_minus = s_i_minus;
                    k_old = k_i;
                    k_old_minus = k_i_minus;

                    // if it does not fall into the invariant, cut it later out and stop analysis
                    if ((p_omega_minus>I_plus && results->sets(indexL,j) < I_minus) || (p_omega>I_minus && results->sets(indexL_opposite,j) < I_plus))   
                    { 
                        return j-1;
                    }           
               }
               
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
              FlowpipeSegment* flowpipe = new FlowpipeSegment(loc,timeStep,L.size(),(unsigned int) params.timeHorizon/params.timeStep);
              flowpipe->startTimestep = timeStep;
                  
              matrix_t<double> X0_values(L.size(),1); // stores the evaluation of X0
              X0->multiEvaluate(&L, &X0_values);
              
              #ifdef FLOWPIPE_VERBOSE
                      std::cout << method << "X0 evaluation':" << X0_values.transpose() << '\n';
              #endif
              
              // test for an intersection between X0 and the invariant
              if(testIntersection(locInfo->scaledConstraintValues,locInfo->mirrored_invariant_constraints_in_L, X0_values))
              {
                  #ifdef FLOWPIPE_VERBOSE
                      std::cout << method << "testIntersection: true" << BL;;
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
                  intersectWithInvariant(omega0_values, locInfo->invariant_constraints_in_L, locInfo->scaledConstraintValues);
                  
                  #ifdef FLOWPIPE_VERBOSE
                      std::cout << method << "omega0' intersecting invariant" << omega0_values.transpose() << '\n';
                  #endif
                  
                  // reconstruct omega0 intersects invariant and re-evaluate (creates tight constraints)
                  PolytopeSupportFunction set0(&L, omega0_values, dimensionality, &additionalDirections);
                  
                  double* set0_values = new double[L.size()]; // stores the evaluation of set0 (heap!)
                  set0.multiEvaluate(&L, set0_values);
                  
                  #ifdef FLOWPIPE_VERBOSE
                      std::cout << method << "set0 of the flowpipe" << set0_values << '\n';
                  #endif
    
                  // add first computed set to the flowpipe (omega0 intersects invariant)
                  flowpipe->addSetAtPosition(set0_values,0);
    
                  // psidelta is needed for the algorithm
                  SupportFunction* multiplicationtemp = locInfo->V->multiply(params.timeStep);
                  SupportFunction* psidelta = multiplicationtemp->minowskisum(omega0.getEpsilonpsi());
                     
                  // start with the iteration of successive timesteps
                  unsigned int maxNumberOfCompleteSets = (unsigned int) params.timeHorizon/params.timeStep;
                  std::vector<int> processedDirections;
                  unsigned int i=0;
                  while(processedDirections.size() != L.size())
                  {
                      int oppositeOfDirectionI = oppositeDirectionMapping[i];
                      if(oppositeOfDirectionI < 0)
                      {
                          std::cout << "opposite direction missing (or not found)" << '\n';
                      }
                      
                      if( !listContains(&processedDirections, (int) i))
                      { 
                          unsigned int j = parallelizationHelper(flowpipe, locInfo, &set0, omega0.getEpsilonpsi(), &L.at(i), i, &L.at(oppositeOfDirectionI), oppositeOfDirectionI);
                          maxNumberOfCompleteSets = MIN(maxNumberOfCompleteSets, j);                 
                      }
                      
                      i++;
                  }
                  
                  #ifdef FLOWPIPE_VERBOSE
                      std::cout << method << "maxNumberOfCompleteSets: " << maxNumberOfCompleteSets << BL;
                  #endif
                  
                  // cut evaluation values which are not needed
                  flowpipe->sets = flowpipe->sets.block(0,0,maxNumberOfCompleteSets,L.size());
                   
                  // conversions in order to reconstruct non-redundant results (or should this be done instantly?)
                  matrix_t<double> temp_values(L.size(),1);
                  for( unsigned int i=0; i<maxNumberOfCompleteSets; i++)
                  {
                       PolytopeSupportFunction temp( &L, flowpipe->sets.col(i), dimensionality, &additionalDirections);
                       temp.multiEvaluate(&L,&temp_values);
                       flowpipe->addSetAtPosition(set0_values,i);
                  }
                  
                  #ifdef FLOWPIPE_VERBOSE
                      // store flowpipe in file
                      char* buffer = new char[100];
                      sprintf(buffer, "matlab_flowpipe_loc%d_time%d", loc, timeStep);
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
                      std::cout << method << "no flowpipe constructed because intersection between X0 and the invariant are empty" << '\n';
                  #endif
              }
              
              return flowpipe;
         }    
          
         #include "transitionHandling.h"
          
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
                  std::vector<possibleTransition>* possibleTransitions = getPossibleTransitions(loc, flowpipe);
                  #ifdef HYREACH_VERBOSE
                      std::cout << method << "possibleTransitions:" << possibleTransitions << BL;
                  #endif
             
                  // choose which transition to take -> Assuption: all
                  // iterate over this list and do for each the required transition handling:
                  matrix_t<double> valuesForNextSet;                    
                  for(auto iterator = possibleTransitions->begin(); iterator != possibleTransitions->end(); ++iterator)
                  {           
                      // Note: iterator is a pointer to possibleTransition structure
                      
                      // cluster always all sets
                      valuesForNextSet = clustering(*iterator); // cluster all sets which are relevant for the construction of the initial set for the next node
                      
                      // TODO:
                      // compute intersection                      
                      // valuesForNextSet =
                      
                      // compute reset
                      // valuesForNextSet = ;
                      
                      // start next Recursion (recursive call of this method)
                      PolytopeSupportFunction nextX0(&L, valuesForNextSet, dimensionality, &additionalDirections);
                      analyze( iterator->transition_pt->transition().locTarget, recursionNumber-1, &nextX0, U, timeStep + flowpipe->size());
                  }
                 
                  delete possibleTransitions; // clear heap memory as soon as possible
              }
         }   
            
	  public:    	
        
        /*
         *   Initiates the start of the hybrid analysis
         */
        void start(HybridAutomaton<double>* model, parameters params, options opt, matrix_t<double> X0constraints,operator_e op, vector_t<double> X0constraintValues, SupportFunction* U)
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
             additionalDirections = extendDimensions(&L);
             #ifdef HYREACH_VERBOSE
                 std::cout << method << "extended L:" << BL;
                 std::cout << L << BL;
                 std::cout << method << "additionalDirections:" << BL;
                 std::cout << "dir1':" << additionalDirections.dir1.transpose() << BL;
                 std::cout << "dir2':" << additionalDirections.dir2.transpose() << BL;
             #endif  
             oppositeDirectionMapping = computeDirectionMapping(&L);
             #ifdef HYREACH_VERBOSE
                 std::cout << method << "oppositeDirectionMapping L:" << BL;
                 printArray<int>(oppositeDirectionMapping, L.size());
                 std::cout << BL;
             #endif  
             dimensionality = (unsigned int)L[0].size();            // extended with additional dimensionality
             
             if( U == 0 )   // use zero function if none provided
             {
                 U = new ZeroSupportFunction(dimensionality, &additionalDirections);
                 #ifdef HYREACH_VERBOSE
                     std::cout << method << "U is ZeroSupportFunction" << BL;
                 #endif
             }
             
             #ifdef HYREACH_VERBOSE
                 std::cout << method << "start preprocessing .... ------------------------------------------------------------------------" << BL;
             #endif
             // start preprocessing
             preprocess(model, &L, params.timeStep, U, &additionalDirections);
             #ifdef HYREACH_VERBOSE
                 std::cout << method << "preprocessing completed. ------------------------------------------------------------------------ " << BL;
             #endif
                  
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
                 std::cout << X0constraints;
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
             
	       	 delete X0;
        }
    
        ~HyReach()
        {
             CleanupOnExit::removeFlowpipeSegments(&results);
             removePreprocessingMemory();
        }
    };


/* 
typedef struct {
    double a, b;
} my_constraint_data;

 double myfunc(unsigned n, const double *x, double *grad, void *my_func_data)
        {
            if (grad) {
                grad[0] = 0.0;
                grad[1] = 0.5 / sqrt(x[1]);
            }
            return sqrt(x[1]);
        }
        
        double myconstraint(unsigned n, const double *x, double *grad, void *data)
        {
            my_constraint_data *d = (my_constraint_data *) data;
            double a = d->a, b = d->b;
            if (grad) {
                grad[0] = 3 * a * (a*x[0] + b) * (a*x[0] + b);
                grad[1] = -1.0;
            }
            return ((a*x[0] + b) * (a*x[0] + b) * (a*x[0] + b) - x[1]);
         }
        
class NLOPTTEST
{
      public:
             
      void test()
      {
           nlopt::opt opt(nlopt::LD_MMA, 2);

            std::vector<double> lb(2);
            lb[0] = -HUGE_VAL; lb[1] = 0;
            opt.set_lower_bounds(lb);
            
            opt.set_min_objective(myfunc, NULL);
            
            my_constraint_data data[2] = { {2,0}, {-1,1} };
            opt.add_inequality_constraint(myconstraint, &data[0], 1e-8);
            opt.add_inequality_constraint(myconstraint, &data[1], 1e-8);
            
            opt.set_xtol_rel(1e-4);
            
            std::vector<double> x(2);
            x[0] = 1.234; x[1] = 5.678;
            double minf;
            nlopt::result result = opt.optimize(x, minf);
            
            if(result > 0 )
            {
                      std::cout << "success";
                      std::cout << "\n";
                      std::cout << "x: ";
                      for( auto i = x.begin(); i != x.end(); ++i)
                      {
                           std::cout << *i << ' ';
                           }
                           
                      std::cout << "\n";
                      std::cout << "minf: ";
                      std::cout << minf;
            }
            else
            {
                std::cout << "failure";
            }
      }

      };
*/
