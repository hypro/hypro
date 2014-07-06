#include "hyreach_utils.h"

//#include "NLF.h"
//#include "NLP.h"
//#include "OptPDS.h"

// OPT++
//using NEWMAT::ColumnVector;
//using namespace::OPTPP;

// Verbosity levels
//#define VECTOR_GEN_VERBOSE
//#define HELPER_METHODS_VERBOSE
//#define SUPPORTFUNCTION_VERBOSE

using namespace::std;

namespace hypro
{
	/*
    * Strucutre defining the options for the reachability algorithm to use
    */
    struct options {
           double angle;     // angle for the direction generation
	       bool preclustering;	// true enables preclustering
	       bool fixpointDetection;	// true enables fixpoint detection
	       double fixpoint_tolerance;	// in case fixpoint detection is enabled, two values are considered equal with regard to this value
	       unsigned int fixpoint_interval;	// the check for fixpoints is performed every fixpoint_interval'th step
	       unsigned int precision;
	};

    /*
    * Structure describing the general parameters for the algorithm to use
    */
    struct parameters {
	       double timeHorizon;
	       double timeStep;
	       unsigned int numberOfTransitions;	// there will n more transitions be considered then indicated by this value
    	};	

    //template<typename Number>
    class HyReach
    {
      private:
         options opt;
         parameters params;
         
         std::forward_list<matrix_t<double>> L; // list of directions
         
         // TODO: datastructure to store results
         // store information about time and location
              
	  public:

        /*
         *   Initiates the start of the hybrid analysis
         */
        void start(HybridAutomaton<double> model, parameters params, options opt)
        {
             // copy the input values
             this->params = params;
             this->opt = opt;
             
             // generate basic direction vectors
             unsigned int dimensions = getDimensionality(&model);
             L = vectorgeneratorEXT(dimensions, opt.angle, opt.precision);
             
             // start preprocessing
             for(auto iterator= model.initialLocations().begin(); iterator != model.initialLocations().end(); ++iterator)
             { 
               // for every initial location, initiate preprocessing
               preprocessing_recursion(*iterator);
             }
                     
             // start analysis
             // TODO:
        }

	/* OPT++
	void init_problem(int ndim, NEWMAT::ColumnVector& x)
	{
		for (unsigned int i; i <= ndims; i++)
		{
			x(i) = 0;
		}
	}

	void problem(int ndim, const NEWMAT::ColumnVector& x, double& fx, int& result)
	{
		// here could be done everything
		double x1 = x(1) +3;
		double x2 = x(2) +3;

		fx = (x1*x1) + (x2*x2);
		result = OPTPP::NLPFunction;
	}

	void solveProblem(int ndim)
	{
		OPTPP::NLF0 nlp(ndim, problem, init_problem);
		OPTPP::OptPDS objfcn(&nlp);

		objfcn.optimize();

	}
	*/
	
	
	//private:            // public for test purpose
		
    	#include "vectorgenerator.h"
    	#include "helperMethods.h"
        #include "preprocessing.h"
	
    };
