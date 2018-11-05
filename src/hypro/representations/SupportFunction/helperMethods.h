/*
 *  This file contains general helper methods.
 *  Some of these methods correspond to standard Matlab functionality
 *  Author: Norman Hansen
 */

#pragma once
#include <boost/tuple/tuple.hpp>

//#define HELPER_METHODS_VERBOSE
namespace hypro {

/**
 * @brief      Determines if a constraint set represented by a matrix and a vector in fact defines a box.
 * @param[in]  constraints  The constraints.
 * @param[in]  constants    The constants.
 * @tparam     Number       The used number type.
 * @return     True if box, False otherwise.
 */
template<typename Number>
boost::tuple<bool,std::vector<carl::Interval<Number>>> isBox(const matrix_t<Number>& constraints, const vector_t<Number>& constants) {
	if(constraints.rows() != constants.rows()) {
		//std::cout << "Rows do not match." << std::endl;
		//return false;
		return boost::tuple<bool,std::vector<carl::Interval<Number>>>(false);
	}
	Eigen::Index dimension = constraints.cols();
	std::vector<carl::Interval<Number>> boundsDefined = std::vector<carl::Interval<Number>>(dimension, carl::Interval<Number>::unboundedInterval());
	for(Eigen::Index r = 0; r < constraints.rows(); ++r) {
		std::size_t posNonZeroCoeff = 0;
		std::size_t negNonZeroCoeff = 0;
		for(Eigen::Index c = 0; c < constraints.cols(); ++c) {
			if(constraints(r,c) > carl::constant_zero<Number>().get()) {
				Number val = constants(r)/constraints(r,c);
				++posNonZeroCoeff;
				if(boundsDefined[c].upperBoundType() == carl::BoundType::INFTY) {
					//std::cout << "Set upper bound to " << Number(val) << std::endl;
					boundsDefined[c].setUpperBound(val, carl::BoundType::WEAK);
				} else if(val < boundsDefined[c].upper()) {
					//std::cout << "Set upper bound multiple times." << std::endl;
					boundsDefined[c].setUpperBound(val, carl::BoundType::WEAK);
				}
			} else if (constraints(r,c) < carl::constant_zero<Number>().get()) {
				Number val = constants(r)/constraints(r,c);
				++negNonZeroCoeff;
				if(boundsDefined[c].lowerBoundType() == carl::BoundType::INFTY) {
					//std::cout << "Set lower bound to " << Number(val) << std::endl;
					boundsDefined[c].setLowerBound(val, carl::BoundType::WEAK);
				} else if( val > boundsDefined[c].lower()){
					//std::cout << "Set lower bound multiple times." << std::endl;
					boundsDefined[c].setLowerBound(val, carl::BoundType::WEAK);
				}
			}
			if(posNonZeroCoeff + negNonZeroCoeff > 1) {
				//std::cout << "Too many coefficients, described set is not a box." << std::endl;
				return boost::tuple<bool,std::vector<carl::Interval<Number>>>(false);
			}
		}
	}
	//std::cout << "Return true." << std::endl;
	return boost::tuple<bool,std::vector<carl::Interval<Number>>>(true,boundsDefined);
}


/*
* Checks wether the list contains the specified direction
*/
template<typename Number>
bool contains( std::vector<matrix_t<Number>> list, matrix_t<Number> direction, unsigned int length ) {
#ifdef HELPER_METHODS_VERBOSE
	std::cout << "contains: check wether a list contains a specific direction ...  ";
#endif

	for ( auto iterator1 = list.begin(); iterator1 != list.end(); ++iterator1 ) {
		bool equal = true;
		matrix_t<Number> a = *iterator1;

		for ( unsigned int i = 0; i < length; i++ ) {
			equal &= a( i ) == direction( i );
		}

		if ( equal ) {
#ifdef HELPER_METHODS_VERBOSE
			std::cout << "list contains \n" << a << std::endl;
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
template<typename Number>
int contains( std::vector<matrix_t<Number>>* directions, matrix_t<Number>* direction ) {
#ifdef HELPER_METHODS_VERBOSE
	std::string method = "contains(...) ";
#endif

	unsigned int length = direction->rows();
	for ( unsigned int i = 0; i < directions->size(); i++ ) {
		matrix_t<Number> temp = directions->at( i );

		bool equal = true;
		for ( unsigned int j = 0; j < length; j++ ) {
			equal &= temp( j ) == ( *direction )( j );
		}

		if ( equal ) {
#ifdef HELPER_METHODS_VERBOSE
			std::cout << method << "list contains" << std::endl << temp << std::endl;
#endif

			return i;
		}
	}

#ifdef HELPER_METHODS_VERBOSE
	std::cout << method << "no suitable match found for " << std::endl;
	std::cout << *direction << std::endl;
#endif

	return -1;
}

/*
* Delegator
*/
template<typename Number>
int contains( std::vector<matrix_t<Number>>* directions, matrix_t<Number> direction ) {
	return contains( directions, &direction );
}

/*
* This method computes a mapping of directions to the opposite directions using an array of indices
*/
template<typename Number>
int* computeDirectionMapping( std::vector<matrix_t<Number>>* directions ) {
	int* result = new int[directions->size()];
#ifdef HELPER_METHODS_VERBOSE
	std::string method = "computeDirectionMapping(...): ";
	std::cout << method << "directions: " << std::endl;
	std::cout << *directions << std::endl;

	std::cout << "for every direction: " << std::endl;
#endif

	for ( unsigned int i = 0; i < directions->size(); i++ ) {
#ifdef HELPER_METHODS_VERBOSE
		std::cout << method << "directions contains: " << std::endl;
		std::cout << -directions->at( i ) << std::endl;
#endif
		result[i] = contains( directions, -( directions->at( i ) ) );
#ifdef HELPER_METHODS_VERBOSE
		std::cout << "at position " << result[i] << std::endl;
#endif
	}

	return result;
}

/*
* Returns true if the list of integers "list" contains the value "item"
*/
template<typename Number>
bool listContains( std::vector<Number>* list, Number item ) {
	for ( auto iterator = list->begin(); iterator != list->end(); ++iterator ) {
		if ( *iterator == item ) {
			return true;
		}
	}
	return false;
}

/**
*  Converts a list of directions into a matrix containing directions
*/
template<typename Number>
matrix_t<Number> directionList2Matrix( std::vector<matrix_t<Number>>* list ) {
	// get list size
	unsigned int counter = 0;
	unsigned int matrixlength = 0;
	unsigned int temp = 0;
	for ( auto iterator = ( *list ).begin(); iterator != ( *list ).end(); ++iterator ) {
		counter++;
		temp = ( *iterator ).size();

		if ( matrixlength != 0 && temp != matrixlength ) {
			std::cout << "Cannot convert a list of matrices with different length into a single matrix!";
			matrix_t<Number> null( 0, 0 );
			return null;
		} else {
			matrixlength = temp;
		}
	}

	matrix_t<Number> result( counter, matrixlength );

	counter = 0;
	for ( auto iterator = ( *list ).begin(); iterator != ( *list ).end(); ++iterator ) {
		for ( unsigned int i = 0; i < matrixlength; i++ ) {
			result( counter, i ) = ( *iterator )( i );
		}

		counter++;
	}
	return result;
}

/*
* Converts a forward list of matrices into an array of matrices
*/
template<typename Number>
matrix_t<Number>* list2Array( std::vector<matrix_t<Number>>* list ) {
	// get list size
	unsigned int counter = 0;
	for ( auto iterator = ( *list ).begin(); iterator != ( *list ).end(); ++iterator ) {
		counter++;
	}

	matrix_t<Number>* result[counter];

	counter = 0;
	for ( auto iterator = ( *list ).begin(); iterator != ( *list ).end(); ++iterator ) {
		result[counter] = &( *iterator );
		counter++;
	}

	return *result;
}

/*
* Converts a nx1 matrix into an array of Numbers
*/
template<typename Number>
Number* matrix2Array( matrix_t<Number> m ) {
	Number* result = new Number[m.rows()];

	for ( int i = 0; i < m.rows(); i++ ) {
		result[i] = m( i, 0 );
	}

	return result;
}

/*
* Converts a vector into an array of Numbers
*/
template<typename Number>
Number* vector2Array( vector_t<Number> v ) {
	Number* result = new Number[v.size()];

	for ( int i = 0; i < v.size(); i++ ) {
		result[i] = v( i );
	}

	return result;
}

/*
 *  returns the dimensionality (number of rows) of the matrix from the first initial location
 */
//	Number getDimensionality(HybridAutomaton<Number, valuation_t<Number>>* model)
//	{
//           return model->dimension();
//    }

/*
* adds a zero column at the right side of the matrix m
*/
template<typename Number>
matrix_t<Number> addZeroColumn( matrix_t<Number> m ) {
	// matrix_t<Number> result = matrix_t<Number>::Zero(m.rows(), m.cols()+1);
	int newcols = m.cols() + 1;
	matrix_t<Number> result( m.rows(), m.cols() + 1 );
#ifdef HELPER_METHODS_VERBOSE
	std::cout << "empty result: " << result;
	std::cout << "result rows: " << result.rows() << std::endl;
	std::cout << "result cols: " << result.cols() << std::endl;

	std::cout << "m rows: " << m.rows() << std::endl;
	std::cout << "m cols: " << m.cols() << std::endl;
#endif

	// copy m into result
	for ( int i = 0; i < m.rows(); i++ ) {
		for ( int j = 0; j < m.cols(); j++ ) {
			// std::cout << "i: " << i << " j: " << j << std::endl;
			result( i, j ) = m( i, j );
			std::cout << "result( " << i << ", " << j << ") = " << result( i, j ) << std::endl;
		}

		std::cout << "i: " << i << " j: " << newcols - 1 << std::endl;
		result( i, newcols - 1 ) = 0;
	}

#ifdef HELPER_METHODS_VERBOSE
	std::cout << "complete result: " << result;
#endif
	return result;
}

/*
* adds a zero row at the bottom of a matrix
*/
template<typename Number>
matrix_t<Number> addZeroRow( matrix_t<Number> m ) {
	matrix_t<Number> result( m.rows() + 1, m.cols() );
	result.block( 0, 0, m.rows(), m.cols() ) = m;
	result.block( m.rows(), 0, 1, m.cols() ) = matrix_t<Number>::Zero( 1, m.cols() );

#ifdef HELPER_METHODS_VERBOSE
	std::cout << "addZeroRow(m): m:" << std::endl << m << std::endl << "extended m: " << std::endl << result
			  << std::endl;
#endif

	return result;
}
}
