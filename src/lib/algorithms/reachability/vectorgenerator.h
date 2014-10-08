/*
 *  This file provides methods to generate lists of directions used for the hybrid reachability analysis with polytopes
 *  Author: Norman Hansen
 */    
    
//#define VECTOR_GEN_VERBOSE

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
		       std::cout << method << "zero vector created\n";
		#endif

		return result;
	}
	
	/*
	*	Generates an ordered set of direction vectors
	*	2 direction vectors for each dimension along the axe of the dimension
	*   Note: the pairwise ordering of the direction is important for other methods 
    *   relying on vectorgenerator (e.g. boxoperaotr in NonLinearOmega0Supportfunction
	*/
	std::vector<matrix_t<double>> vectorgenerator( unsigned int dimensions)
	{
		std::string method = "Vectorgenerator: ";
		std::vector<matrix_t<double>> result;

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

			result.push_back(vector1);
			result.push_back(vector2);
		}

		#ifdef VECTOR_GEN_VERBOSE
		       cout << method << "done\n";
		#endif

		return result;
	}
	
	/**
	* This method rounds a row-vector (as matrix) according to the specified precision
	*/
	matrix_t<double> round(matrix_t<double> direction, double precision)
	{
        matrix_t<double> result(direction.rows(),1);             
        // round the direction entries according to precision
		for( int i = 0; i < direction.rows(); i++)
		{
			result(i,0) = ((long)(( direction(i,0)*precision)))/precision;			
		}
		
		return result;
    }
	
	/*
	* Generates an (ordered) set of direction vectors
	* Chooses a start vector and rotates the vector in each plane defined by two dimensions
	* The vector entries are rounded to the specified precision and each direction is contained exactly once
	*/ 
	std::vector<matrix_t<double>> vectorgeneratorEXT( unsigned int dimensions, double angle, double precision)
	{
		std::string method = "vectorgeneratorExt: ";

		std::vector<matrix_t<double>> result;	//the result of the computation
		matrix_t<double> last_considered;
		unsigned int numberOfDirections = 0;	// counts how many directions are produced

		// iterate over all pairs of planes along dimensions
		unsigned int iteration = 0;
		unsigned int iteration2 = 0;
		unsigned int iteration3 = 0;
		//unsigned int iteration4 = 0;


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
					result.push_back(start);
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
					//for( iteration4 = 0; iteration4 < dimensions; iteration4++)
					//{
					//	nextDirection(iteration4,0) = ((long)((nextDirection(iteration4,0)*precision)))/precision;	
					//}
					nextDirection = round(nextDirection,precision);

					#ifdef VECTOR_GEN_VERBOSE
					       cout << method << "rounded to\n" << nextDirection << "\n";
					#endif

					if(!contains(result,nextDirection,dimensions))
					{
						result.push_back(nextDirection);
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
