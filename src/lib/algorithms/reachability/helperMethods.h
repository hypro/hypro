/*
 *  This file contains general helper methods.
 *  Some of these methods correspond to standard Matlab functionality
 *  Author: Norman Hansen
 */

#include "hyreach_utils.h"    
//#include "../../datastructures/hybridAutomata/util.h"
    
//#define HELPER_METHODS_VERBOSE


    /*
	* Prints the argument on the standard output
	*/
	void printDirectionList(std::vector<matrix_t<double>> list)
	{
		for(auto iterator1 = list.begin(); iterator1 != list.end(); ++iterator1)
		{
			matrix_t<double> actual = *iterator1;
            std::cout << actual.transpose() << "\n\n";
		}
	}
	
	/*
	* Prints the argument on the standard output
	*/
	void print(std::vector<double> list)
	{
         for(unsigned int i=0; i<list.size(); i++)
         {
             std::cout << list[i] << '\n';
         }
    }

    /*
	* Checks wether the list contains the specified direction
	*/
	bool contains(std::vector<matrix_t<double>> list, matrix_t<double> direction, unsigned int length)
	{
		#ifdef HELPER_METHODS_VERBOSE
		       std::cout << "contains: check wether a list contains a specific direction ...  ";
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
				       std::cout << "list contains \n" << a <<"\n";
				#endif

				return true;
			}
		}

		#ifdef HELPER_METHODS_VERBOSE
		       std::cout << "no.\n";
		#endif

		return false;		
	}
	
	/*
	* Returns the index of the position of direction in directions if it is contained.
	* In case direction is not in directions, this method returns -1
	*/
	int contains(std::vector<matrix_t<double>>* directions, matrix_t<double>* direction)
	{
		#ifdef HELPER_METHODS_VERBOSE
		       std::cout << "contains: check wether a list directions contains a specific direction ...  ";
		#endif

        unsigned int length = direction->rows();
		for(unsigned int i=0; i< directions->size(); i++)
		{
			matrix_t<double> temp = directions->at(i);

            bool equal = true;
			for(unsigned int j=0; j<length; j++)
			{
				equal &= temp(j) == (*direction)(j);
			}

			if(equal)
			{
				#ifdef HELPER_METHODS_VERBOSE
				       std::cout << "list contains \n" << temp <<"\n";
				#endif

				return i;
			}
		}

		#ifdef HELPER_METHODS_VERBOSE
		       std::cout << "no.\n";
		#endif

		return -1;		
	}

    /**
	*  Converts a list of directions into a matrix containing directions
	*/
	matrix_t<double> directionList2Matrix(std::vector<matrix_t<double>>* list)
	{
		// get list size
		unsigned int counter = 0;
		unsigned int matrixlength = 0;
		unsigned int temp = 0;
		for (auto iterator = (*list).begin(); iterator != (*list).end(); ++iterator)
		{
			counter++;
			temp = (*iterator).size();
			
			if(matrixlength != 0 && temp != matrixlength)
			{
                std::cout << "Cannot convert a list of matrices with different length into a single matrix!";
                matrix_t<double> null(0, 0);
                return null;           
            }
            else
            {
                matrixlength = temp;
            }
		}

		matrix_t<double> result(counter, matrixlength);

		counter = 0;
		for (auto iterator = (*list).begin(); iterator != (*list).end(); ++iterator)
		{
			for(unsigned int i=0; i<matrixlength; i++)
			{
                 result(counter, i) = (*iterator)(i);
            }
             
			counter++;
		}
		return result;
	}
	
	/*
	* Converts a forward list of matrices into an array of matrices
	*/
	matrix_t<double>* list2Array(std::vector<matrix_t<double>>* list)
	{
		// get list size
		unsigned int counter = 0;
		for (auto iterator = (*list).begin(); iterator != (*list).end(); ++iterator)
		{
			counter++;
		}

		matrix_t<double> *result[counter];

		counter = 0;
		for (auto iterator = (*list).begin(); iterator != (*list).end(); ++iterator)
		{
			result[counter] = &(*iterator);
			counter++;
		}

		return *result;
	}
	
	/*
	 *  returns the dimensionality (number of rows) of the matrix from the first initial location
	 */
	double getDimensionality(HybridAutomaton<double>* model)
	{
           return ((*((*model).initialLocations().begin()))->activityMat()).rows();
    }
