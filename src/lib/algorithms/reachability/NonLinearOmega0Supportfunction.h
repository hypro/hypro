/*
 *  This file contains everything related directly to support functions of polyhedra and their evaluation
 *  Author: Norman Hansen
 */
 
#define SUPPORTFUNCTION_VERBOSE 

//#define BOXOPERATOR_VERBOSE
//#define CALCEPSILON_VERBOSE
//#define CALCVALUES_VERBOSE
 
#include "hyreach_utils.h" 
#include "BoxSupportfunction.h"

// NLopt includes
#include <nlopt.hpp>
    
namespace hypro
{     
        
    /*
    * This class defines a support Function object overapproximating Omega0 according to the SpaceEx algorithm with use of nonlinear optimization
    * SupportFunctions can be evaluated in a specified direction l and return a correspondent evaluationResult
    */
    class NonLinearOmega0Supportfunction : public SupportFunction
    {
      private:
        
        // dimensionality of this object  
        unsigned int dimensions;
        
        // externally provided Data
        matrix_t<double>* A;
        SupportFunction* V;
        SupportFunction* X0;
        
        double delta;
        
        // general used values for the construction and evaluation of Omega0
        matrix_t<double> absA;
        matrix_t<double> edA;
        matrix_t<double> phi2;
        SupportFunction* epsilonpsi;
        SupportFunction* edX0;
        matrix_t<double> e_p;
        matrix_t<double> e_n;
        
        // boxoperator values
        std::vector<matrix_t<double>> directionsAlongDimensions;   // contains a vector along each dimension   
  
        /*
        * Computes a supportfunction being a symmetric box (centered at the origin) around the specified support function
        */
        SymmetricCenteredBoxSupportFunction boxoperator(SupportFunction* sf)
        {
             #ifdef SUPPORTFUNCTION_VERBOSE
                 #ifdef BOXOPERATOR_VERBOSE
    		         string method = "boxoperator:";
    		     #endif
		     #endif
		     
             matrix_t<double> e = getZeroVector(dimensions);
             
             matrix_t<double> l1;
             matrix_t<double> l2;
             
             auto iterator = directionsAlongDimensions.begin();
             for(unsigned int i=0; i< dimensions; i++)
             {
                     #ifdef SUPPORTFUNCTION_VERBOSE
                         #ifdef BOXOPERATOR_VERBOSE
                             cout << method << " start loop-iteration " << i << '\n';
                         #endif
                     #endif
                         
                     // get 2 successive directions    (they are sorted such that they point both in the opposite direction along the same axis)
                     l1 = *iterator;
                     ++iterator;
                     l2 = *iterator;
                     ++iterator;
                     
                     // get the correspondent evaluation results
                     evaluationResult a = sf->evaluate(l1);
                     evaluationResult b = sf->evaluate(l2);
                     
                     // set entry in e to the correspondent maximum value
                     e(i,0) = std::max(a.supportValue,b.supportValue);
                     
                     #ifdef SUPPORTFUNCTION_VERBOSE
                         #ifdef BOXOPERATOR_VERBOSE
                             cout << method << " l1 = " << l1 << '\n';
                             cout << method << " l2 = " << l2 << '\n';
                             cout << method << " omega(l1) = " << a.supportValue << '\n';
                             cout << method << " omega(l2) = " << b.supportValue << '\n';
                             cout << method << " end loop-iteration " <<i << '\n';
                         #endif
                     #endif
             } 
             return SymmetricCenteredBoxSupportFunction(e);
        }
        
        /*
        * Computes the exponential matrix of the parameter
        */
        matrix_t<double> exponentialmatrix(matrix_t<double> matrix)
        {	
            // TODO: does not work yet (compile errors)		
			// adapted/used code from C.Kugler (forwardReachability.h & util.h)
                matrix_t<double> resultMatrix(matrix.rows(),matrix.cols());
				Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> doubleMatrix(matrix.rows(),matrix.cols());
				Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> expMatrix(matrix.rows(),matrix.cols());
				doubleMatrix = convertMatToDouble<double>(matrix);
				expMatrix = doubleMatrix.exp();
				resultMatrix = convertMatToFloatT<double>(expMatrix);
				
				return resultMatrix;
        }
        
        /*
        * computes the matrices edA and phi2
        */
        matrix_t<double> calcvalues(matrix_t<double>* A, unsigned int i, unsigned int j, unsigned int k, unsigned int l)
        {
             #ifdef SUPPORTFUNCTION_VERBOSE
                #ifdef CALCVALUES_VERBOSE
    			    string method = "calcvalues:";
    			    cout << method << " A = " << *A << '\n';
    			#endif
    		 #endif
                         
             matrix_t<double> temp = matrix_t<double>::Zero(3*dimensions, 3*dimensions);
             matrix_t<double> Ad = (*A)*delta;
             
             #ifdef SUPPORTFUNCTION_VERBOSE
                #ifdef CALCVALUES_VERBOSE
    			    cout << method << " Ad = "<< '\n' << Ad << '\n';
    			#endif
    		 #endif
    		 
             // copy Ad into temp
             for (unsigned int i_=0; i_<dimensions; i_++ )
             {
                 for (unsigned int j_=0; j_<dimensions; j_++)
                 {
                     temp(i_,j_) = Ad(i_,j_);
                 }
             } 
             
             #ifdef SUPPORTFUNCTION_VERBOSE
                #ifdef CALCVALUES_VERBOSE
		            cout << method << " temp (with Ad) = " << '\n' << temp << '\n';
    			#endif
    		 #endif
    		 
             matrix_t<double> Id = matrix_t<double>::Identity(dimensions, dimensions);
             
             #ifdef SUPPORTFUNCTION_VERBOSE
                #ifdef CALCVALUES_VERBOSE
    			    cout << method << " Id = "<< '\n' << Id << '\n';
    			#endif
    		 #endif
    		 
             // copy Id into temp
             for (unsigned int i_=0; i_<dimensions; i_++ )
             {
                 for (unsigned int j_=0; j_<dimensions; j_++)
                 {
                     temp(i_,dimensions+j_) = Id(i_,j_);
                     temp(dimensions+i_,2*dimensions+j_) = Id(i_,j_);
                 }
             }
             
             #ifdef SUPPORTFUNCTION_VERBOSE
                #ifdef CALCVALUES_VERBOSE
    			    cout << method << " temp = " << temp << '\n';
    			#endif
    		 #endif
             
            matrix_t<double> exptemp = exponentialmatrix(temp);		// compute exponential of temp   
            
            #ifdef SUPPORTFUNCTION_VERBOSE
                #ifdef CALCVALUES_VERBOSE
        			cout << method << " exptemp = " << exptemp << '\n';
        			cout << "i: " <<i << " j: " << j << " k: " << k << " l: " << l << '\n';
        			cout << "expcols: " << exptemp.cols() << '\n';
        			cout << "exprows: " << exptemp.rows() << '\n';
        		#endif
		    #endif
              
            // extract the specified part of the exponential matrix exptemp
            return exptemp.block(i,k,j,l);
            //return exptemp.block(i,k,2,2);
        }
        
        /*
        * Compute further values needed to construct the support function of Omega0
        */
        void calcepsilon()
        {
             matrix_t<double> Asquare = ((*A)*(*A));
             #ifdef SUPPORTFUNCTION_VERBOSE
                 #ifdef CALCEPSILON_VERBOSE
        		        string method = "calcepsilon:";
        		        cout << method << " A = " << *A << '\n';
        		        cout << method << " Asquare = " << Asquare << '\n';
        		 #endif
    		 #endif
    		 
             // e_p
             MultiplicationSupportfunction a2x0 = Asquare * X0;
             SymmetricCenteredBoxSupportFunction a2x0_box = boxoperator(&a2x0);
             #ifdef SUPPORTFUNCTION_VERBOSE
                 #ifdef CALCEPSILON_VERBOSE
                     cout << method << " a2x0_box constructed" << '\n';
                 #endif
    		 #endif
             MultiplicationSupportfunction temp = phi2.transpose() * &a2x0_box;
             #ifdef SUPPORTFUNCTION_VERBOSE
                 #ifdef CALCEPSILON_VERBOSE
                     cout << method << " phi2.transpose() * &a2x0_box constructed" << '\n';
                 #endif
    		 #endif
             SymmetricCenteredBoxSupportFunction result = boxoperator(&temp);
             e_p = result.getE();
             #ifdef SUPPORTFUNCTION_VERBOSE
                 #ifdef CALCEPSILON_VERBOSE
                        cout << method << " e_p = " << e_p << '\n';
                 #endif
    		 #endif
    		 
             // e_n
             MultiplicationSupportfunction a2ex0 = (Asquare.transpose() * edA.transpose()) * X0;
             SymmetricCenteredBoxSupportFunction a2ex0_box = boxoperator(&a2ex0);
             temp = phi2.transpose() * &a2ex0_box;
             result = boxoperator(&temp);
             e_n = result.getE();
             #ifdef SUPPORTFUNCTION_VERBOSE
                 #ifdef CALCEPSILON_VERBOSE
                     cout << method << " e_n = " << e_n << '\n';
                 #endif
    		 #endif
    		 
             // epsilonpsi
             MultiplicationSupportfunction au = *A * V;
             SymmetricCenteredBoxSupportFunction au_box = boxoperator(&au);
             temp = phi2.transpose() * &au_box;
             result = boxoperator(&temp);
             epsilonpsi = result.copyToHeap();
        }
        
        // fields to store temporary evaluation results (yield in improved performance)
        evaluationResult x0res;
        evaluationResult edX0res;
        evaluationResult Vres;
        evaluationResult epsilonpsires;
        matrix_t<double> absl;
        
        // this is the function that will be optimized bei NLOpt
        // calcomega0delta.m
        static double myfunc(unsigned n, const double *x, double *grad, void *my_func_data)  // abs(l) provided using my_func_data
        {
               //matrix_t<double>* l_pt = (matrix_t<double>*)my_func_data;
               NonLinearOmega0Supportfunction* self = (NonLinearOmega0Supportfunction*)my_func_data;
               //cout << "myfunc l:" << '\n' << *l_pt << '\n';
               
               // epsilonintersection (function [res] = epsilonintersection(e_p, e_n,x,d,l))
               double epsilonintersection =0;
               for (int i=0;i<(*self).absl.rows(); i++)
               {
                   epsilonintersection = epsilonintersection+ min(x[0]*((*self).e_p(i,0).toDouble()), (1-x[0])*((*self).e_n(i,0).toDouble())*((*self).absl(i,0).toDouble()));
               }

               // result(edA,delta,u,x0,epsilonpsi,e_p, e_n,start,options,l)
               double res = -( ((1-x[0])*((*self).x0res.supportValue)) + (x[0]*((*self).edX0res.supportValue)) + (x[0]*((*self).delta)*((*self).Vres.supportValue)) + ((x[0]*x[0])*((*self).epsilonpsires.supportValue)) + epsilonintersection);   // +epsilonintersection(e_p,e_n,x,size(start,1),l)
               return res;
        }  
        
      public:
    
        // getter for epsilonpsi
        SupportFunction* getEpsilonpsi()
        {
            return epsilonpsi;
        }
                         
    	/*
    	 * Creates a new supportFunction describing Omega0
    	 *
    	 * A: matrix describing the flow
    	 * V: support function describing the input (B' * U)
    	 * X0: support function describing the initial set
    	 * delta: sampling time
    	 *
    	 */
    	NonLinearOmega0Supportfunction(matrix_t<double>* A, SupportFunction* V, SupportFunction* X0, double delta):SupportFunction(SupportFunctionType::NonLinear_Type)
    	{
             #ifdef SUPPORTFUNCTION_VERBOSE
    			string method = "NonLinearOmega0Supportfunction:";
    		 #endif
                                                        
             // initialize values used by boxoperators
             dimensions = (*A).rows();
             directionsAlongDimensions = vectorgenerator(dimensions);
             
             #ifdef SUPPORTFUNCTION_VERBOSE
    			std::cout << method << " generated Vectors along dimensions" << '\n';
    		 #endif
    		
             this->A = A;
             this->V = V;
             this->X0 = X0;
             this->delta = delta;
             
             #ifdef SUPPORTFUNCTION_VERBOSE
    			std::cout << method << " initialized class attributes with constructor values" << '\n';
    		 #endif
    		 
             // absolute value of A
             absA = (*A).array().abs().matrix();
             
             #ifdef SUPPORTFUNCTION_VERBOSE
    			std::cout << method << " computed Abs(A):" << '\n';
    			std::cout << absA << '\n';
    		 #endif
    		
             // compute edA and phi2
             unsigned int zero = 0;
             edA = calcvalues(A, zero, dimensions, zero, dimensions);
             #ifdef SUPPORTFUNCTION_VERBOSE
    			std::cout << method << " computed edA: " << '\n'<< edA << '\n';
    		 #endif
    		 
             phi2 = calcvalues(&absA, zero, dimensions, 2*dimensions, dimensions);
             #ifdef SUPPORTFUNCTION_VERBOSE
    			std::cout << method << " computed phi2: " << '\n'<< phi2 << '\n';
    		 #endif
             
             // compute epsilonpsi, e_p and e_n
             calcepsilon();
             
             MultiplicationSupportfunction temp = edA * X0;
             edX0 = &temp;
        }

        /**
    	* This method computes the evaluation result for a specified direction l
    	* TODO: optimization object can be declared and initialized outside the evaluate methods to improve performance (see glpk)
    	*/
    	evaluationResult evaluate(matrix_t<double> l)
    	{       
             #ifdef SUPPORTFUNCTION_VERBOSE
                string method = "NonLinearOmega0Supportfunction: evaluate: ";
    			std::cout << method << " l: " << '\n'<< l << '\n';
    		 #endif        
    		 
    		 // precompute values needed during optimization (dependent on l)
    		 // improves evaluation speed of myfunc during optimization
    		 x0res = X0->evaluate(l);
    		 Vres = V->evaluate(l);
    		 epsilonpsires = epsilonpsi->evaluate(l);
    		 absl = l.array().abs().matrix();
    		 
             // optimization parameter and start value
             std::vector<double> x(1);
             x[0] = 0;
             
             std::vector<double> lb(1);
             lb[0] = 0;
             
             std::vector<double> ub(1);
             ub[0] = 1;
             
             // create optimization object
             nlopt::opt opt( nlopt::LN_COBYLA, 1);
             opt.set_lower_bounds(lb);       // lower bounds
             opt.set_upper_bounds(ub);       // upper bounds
             opt.set_min_objective(myfunc, &l);
             
             opt.set_xtol_rel(1e-8);
  
             double minf;           // minimization result
             nlopt::result result = opt.optimize(x, minf);      // optimization call
             
             // catch error case
             if(result <= 0 )
             {
                  #ifdef SUPPORTFUNCTION_VERBOSE     
                      std::cout << method << " NLOPT Failure";
                  #endif
                  
                  // avoid program crash
                  minf = 0;
                  x[0] = 0;
             }
            
             // create evaluationResult
             evaluationResult eR;
             eR.errorCode = 0;                                  // unknown (arbitrary chosen)
             eR.supportValue = -minf;
             matrix_t<double> oV(1,1);
             oV(0,0) = x[0];
             eR.optimumValue = oV;
             
             #ifdef SUPPORTFUNCTION_VERBOSE
    			std::cout << method << " eR.supportValue: " << '\n'<< eR.supportValue << '\n';
    			std::cout << method << " eR.optimumValue: " << '\n'<< eR.optimumValue << '\n';
    		 #endif  
    		 
             return eR;
        }
        
        // destructor
        ~NonLinearOmega0Supportfunction()
        {
            #ifdef SUPPORTFUNCTION_VERBOSE
    			std::cout << " NonLinearOmega0Supportfunction: destructor " << '\n';
	        #endif  
	        
            delete epsilonpsi; // has been explicitely copied to heap and can be deleted at this point
            
            #ifdef SUPPORTFUNCTION_VERBOSE
    			std::cout << " NonLinearOmega0Supportfunction: destructor - complete" << '\n';
	        #endif  
        }
        
    };

}
