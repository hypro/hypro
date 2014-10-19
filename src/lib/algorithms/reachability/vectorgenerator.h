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
		matrix_t<double> rotationMatrix(dimensions,dimensions);	//matrix defining the rotation to performe

		#ifdef VECTOR_GEN_VERBOSE
		       std::string method = "getRotationMatrix: ";
		       std::cout << method << "Variables initialized\n";	
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

        // ensure every direction has an opposite (needed for algoInv)
        for(auto iterator = result.begin(); iterator != result.end(); ++iterator)
        {
                 matrix_t<double> l = *iterator;
                 if( !contains(result, -l, l.size()) )
                 {
                     result.push_back(-l);
                 }
        }
        
		#ifdef VECTOR_GEN_VERBOSE
		cout << method << "result:\n";
		printDirectionList(result);
		#endif

		return result;
	}
	
	// structure to store the 2 directions artificially introduced due to the augmentation by one artificial dimension
	struct artificialDirections
	{
        matrix_t<double> dir1; // positive direction (0 ....0  1)
        matrix_t<double> dir2; // negative direction (0 ....0 -1)
        
        // pointer to the correspondent entries in the global directions list
        matrix_t<double>* dir1_pt;
        matrix_t<double>* dir2_pt;
        
        // constant evaluation results
        double dir1_eval = 1;
        double dir2_eval = -1;
    };
	
	/*
	* replaces all directions by a direction of the original dimensionality+1 with the additional entry being 0
	*/
	artificialDirections extendDimensions(std::vector<matrix_t<double>>* directions)
	{
         matrix_t<double> l;
         // replace directions by direction of higher dimensionality
         for(auto iterator = directions->begin(); iterator != directions->end(); ++iterator)
         {
             l = *iterator;
             //directions->erase(iterator);
             matrix_t<double> newl(l.rows()+1,1);
             for(int i=0; i<l.rows(); i++)
             {
                     newl(i,0) = l(i,0);  // copy l to newl
             }
             newl(l.rows(),0) = 0;        // add final 0 entry
             //directions->push_back(newl);
             *iterator = newl;
         }
         
         // construct artificial directions
         artificialDirections result;
         result.dir1 = getZeroVector(l.rows()+1);
         result.dir2 = getZeroVector(l.rows()+1);
         
         result.dir1(l.rows(),0) = 1;
         result.dir2(l.rows(),0) = -1;
         
         directions->push_back(result.dir1);
         auto iterator = directions->begin();
         result.dir1_pt = &(*iterator);
         
         directions->push_back(result.dir2);
         iterator = directions->begin();
         result.dir2_pt = &(*iterator);
         
         return result;
    }
