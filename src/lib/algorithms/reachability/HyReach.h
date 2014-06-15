#include "../../datastructures/hybridAutomata/util.h"
#include <list>
#include <forward_list>
#include <iostream>
#include <cmath>
#include <string>

using namespace std;

//#define VECTOR_GEN_VERBOSE
//#define HELPER_METHODS_VERBOSE


namespace hypro
{
    //template<typename Number>
    class HyReach
    {
	public:

	// this method exists only for test purpose (DUMMY METHOD)
	double returnSomething(double x)
	{
		return x;
	}


	/*
	* Generates an (ordered) set of direction vectors
	* Chooses a start vector and rotates the vector in each plane defined by two dimensions
	* The vector entries are rounded to the specified precision and each direction is contained exactly once
	*/ 
	std::forward_list<matrix_t<double>> vectorgeneratorEXT( unsigned int dimensions, double angle, double precision)
	{
		std::string method = "vectorgeneratorExt: ";

		std::forward_list<matrix_t<double>> result;	//the result of the computation
		matrix_t<double> last_considered;
		unsigned int numberOfDirections = 0;	// counts how many directions are produced

		// iterate over all pairs of planes along dimensions
		unsigned int iteration = 0;
		unsigned int iteration2 = 0;
		unsigned int iteration3 = 0;
		unsigned int iteration4 = 0;


		#ifdef VECTOR_GEN_VERBOSE
		cout << method << "var initializes \n";
		#endif

		for(iteration = 0; iteration<dimensions; iteration++)
		{
			for(iteration2 = iteration+1; iteration2 < dimensions; iteration2++)
			{
				// generate start vector
				matrix_t<double> start = getZeroVector(dimensions);
				start(iteration,0) = 1;

				#ifdef VECTOR_GEN_VERBOSE
				cout << method << "ZeroVector constructed\n";
				#endif

				// generate matrix used for the rotation computation along dimensions iteration and iteration2
				matrix_t<double> rotationMatrix = getRotationMatrix(dimensions, iteration, iteration2, angle);

				#ifdef VECTOR_GEN_VERBOSE
				cout << method << "RotationMatrix constructed\n" << rotationMatrix << "\n";
				#endif

				// the start vector is part of the result too
				if(!contains(result,start,dimensions))
				{
					result.push_front(start);
					numberOfDirections++;

					#ifdef VECTOR_GEN_VERBOSE
					cout << method << "Start direction added to list\n" << start << "\n";
					#endif
				}

				matrix_t<double> nextDirection = start;

				// rotate
				for(iteration3 = 0; iteration3 < ((2*PI_UP)/angle)-1; iteration3++)
				{
					nextDirection = rotationMatrix * (nextDirection);

					#ifdef VECTOR_GEN_VERBOSE
					cout << method << "Next direction computed\n";
					#endif

					// round the direction entries according to precision
					for( iteration4 = 0; iteration4 < dimensions; iteration4++)
					{
						nextDirection(iteration4,0) = ((long)((nextDirection(iteration4,0)*precision)))/precision;
						
					}

					#ifdef VECTOR_GEN_VERBOSE
					cout << method << "rounded to\n" << nextDirection << "\n";
					#endif

					if(!contains(result,nextDirection,dimensions))
					{
						result.push_front(nextDirection);
						numberOfDirections++;	
						#ifdef VECTOR_GEN_VERBOSE
						cout << method << "Direction added\n";
						#endif
					}
					else
					{
						#ifdef VECTOR_GEN_VERBOSE
						cout << method << "Discard direction\n";
						#endif
					}
				}
			}
		}

		#ifdef VECTOR_GEN_VERBOSE
		cout << method << "result:\n";
		printDirectionList(result);
		#endif

		return result;
	}



	/*
	*	Generates an ordered set of direction vectors
	*	2 direction vectors for each dimension along the axe of the dimension
	*/
	std::forward_list<matrix_t<double>> vectorgenerator( unsigned int dimensions)
	{
		string method = "Vectorgenerator: ";
		std::forward_list<matrix_t<double>> result;

		#ifdef VECTOR_GEN_VERBOSE
		cout << method << "Dimensions: " << dimensions << "\n";
		#endif

		for( unsigned int i=0; i<dimensions; i++)
		{
			#ifdef VECTOR_GEN_VERBOSE
			cout << method << "Iteration: " << i << "\n";
			#endif

			matrix_t<double> vector1(dimensions,1);
			vector1.setZero();
			vector1(i) = 1;

			matrix_t<double> vector2(dimensions,1);
			vector2.setZero();
			vector2(i) = -1;

			result.push_front(vector1);
			result.push_front(vector2);
		}

		#ifdef VECTOR_GEN_VERBOSE
		cout << method << "done\n";
		#endif

		return result;
	}

	/**
	* Checks wether the list contains the specified direction
	*/
	bool contains(std::forward_list<matrix_t<double>> list, matrix_t<double> direction, unsigned int length)
	{
		#ifdef HELPER_METHODS_VERBOSE
		cout << "contains: check wether a list contains a specific direction ...  ";
		#endif

		for(auto iterator1 = list.begin(); iterator1 != list.end(); ++iterator1)
		{
			bool equal = true;
			matrix_t<double> a = *iterator1;

			for(unsigned int i=0; i<length; i++)
			{
				equal &= a(i) == direction(i);
			}

			if(equal)
			{
				#ifdef HELPER_METHODS_VERBOSE
				cout << "list contains \n" << a <<"\n";
				#endif

				return true;
			}
		}

		#ifdef HELPER_METHODS_VERBOSE
		cout << "no.\n";
		#endif

		return false;		
	}

	private:

	/* 
	* returns a dimensionsx1 vector of zeros
	*/
	matrix_t<double> getZeroVector(unsigned int dimensions)
	{
		std::string method = "getZeroVector: ";

		// stores the entire result
		matrix_t<double> result(dimensions,1);

		// write zeros into the entire vector
		result.setZero();

		#ifdef VECTOR_GEN_VERBOSE
		cout << method << "zero vector created\n";
		#endif

		return result;
	}

	/*
	* Creates a matrix defining a rotation along dimensions dim1 and dim2 by angle
	*/
	matrix_t<double> getRotationMatrix(unsigned int dimensions, unsigned int dim1, unsigned int dim2, double angle)
	{
		std::string method = "getRotationMatrix: ";

		matrix_t<double> rotationMatrix(dimensions,dimensions);	//matrix defining the rotation to performe

		#ifdef VECTOR_GEN_VERBOSE
		cout << method << "Variables initialized\n";	
		#endif	

		rotationMatrix.setZero();
		rotationMatrix(dim1,dim1) = cos(angle);
		rotationMatrix(dim1,dim2) = -sin(angle);
		rotationMatrix(dim2,dim2) = rotationMatrix(dim1,dim1);
		rotationMatrix(dim2,dim1) = sin(angle);

		#ifdef VECTOR_GEN_VERBOSE
		cout << method << "Matrix filled with values\n";
		#endif

		return rotationMatrix;
	}

	/**
	* Prints the argument on the standard output
	*/
	void printDirectionList(std::forward_list<matrix_t<double>> list)
	{
		for(auto iterator1 = list.begin(); iterator1 != list.end(); ++iterator1)
		{
			matrix_t<double> actual = *iterator1;
			cout << actual.transpose() << "\n\n";
		}
	}
    };

    /*
    * Strucutre defining the options for the reachability algorithm to use
    */
    struct options {
	bool preclustering;	// true enables preclustering
	bool fixpointDetection;	// true enables fixpoint detection
	double fixpoint_tolerance;	// in case fixpoint detection is enabled, two values are considered equal with regard to this value
	unsigned int fixpoint_interval;	// the check for fixpoints is performed every fixpoint_interval'th step
	};

    /*
    * Structure describing the general parameters for the algorithm to use
    */
    struct parameters {
	double timeHorizon;
	double timeStep;
	unsigned int numberOfTransitions;	// there will n more transitions be considered then indicated by this value
    	};

    /*
    * This class defines a support Function object
    * SupportFunctions can be evaluated in a specified direction l in return a correspondent evaluationResult
    */
    class SupportFunction {
	public:

	/*
	* Creates a new supportFunction for the closed convex set described by constraints * x operation(>= or <=) constraintConstants
	*/
	SupportFunction(matrix_t<double> constraints, matrix_t<double> constraintConstants, operator_e operation)
	{
		// TODO: depending on the operator, invert constraints
		(*this).constraints = constraints;
		(*this).constraintConstants = constraintConstants;
	}

	/*
	* This structure describes the result of a support function evaluation
	*/
	struct evaluationResult {
		double supportValue;	// the value returned by the support function evaluation
		matrix_t<double> optimumValue;	// the point leading to the support function value (extremum in direction)
		int errorCode; 	// potential error code indicating success or failure of the evaluation
	};
	
	private:
	matrix_t<double> constraints;	// matrix describing constraints of a closed convex polyhedra
	matrix_t<double> constraintConstants;	// vector describing constraints of a closed closed convex polyhedra
    };
}
