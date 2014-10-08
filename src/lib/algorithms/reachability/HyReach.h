#include "hyreach_utils.h"

// Verbosity levels
//#define VECTOR_GEN_VERBOSE
//#define HELPER_METHODS_VERBOSE
//#define SUPPORTFUNCTION_VERBOSE

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
        
    class HyReach
    {
      private:
         options opt;
         parameters params;
         
         std::vector<matrix_t<double>> L; // list of directions
         
         // TODO: datastructure to store results (valuation?)
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
             preprocess(&model);
                     
             // start analysis
             // TODO:
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
