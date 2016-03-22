/**
 * Specialization of some helper functions for computing template directions
 * @file helperFunctions.h
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 * @author Simon Froitzheim
 *
 * @version	2016-03-18
 */

#pragma once
#include "Permutator.h"

namespace hypro {

/*
* Compute a uniform distribution of directions for a dimension-dimensional space template polytope
*/
#define PI 3.14159265359
template<typename Number>
static std::vector<vector_t<Number>> computeTemplate(unsigned dimension, unsigned numberDirections) {
	double degree = (360/ (double) numberDirections)* PI / 180.0;
	std::vector<vector_t<Number>> directions, directions2d;

	//create directions2d
	vector_t<Number> templateVector2d = vector_t<Number>::Zero(2); // init templateVector2d
	templateVector2d(0) = 1;
	templateVector2d(1) = 0;
	directions2d.push_back(templateVector2d);

	matrix_t<Number> m(2, 2); //init matrix
	m(0,0) = carl::rationalize<Number>(cos(degree));
	m(0,1) = carl::rationalize<Number>((-1)*sin(degree));
	m(1,0) = carl::rationalize<Number>(sin(degree));
	m(1,1) = carl::rationalize<Number>(cos(degree));

	for(unsigned i=0; i<(numberDirections-1); ++i) {
		//Rotate templateVector
		templateVector2d = m * templateVector2d;
		directions2d.push_back(templateVector2d);
	}

	//copy directions2d into directions
	Permutator permutator(dimension, 2);
	std::vector<unsigned> permutation;
	while(!permutator.end()) {
		permutation = permutator();
		for(vector_t<Number> vectorOfdirections2d: directions2d) {
			vector_t<Number> templateVector = vector_t<Number>::Zero(dimension); // init templateVector

			templateVector(permutation.at(0)) = vectorOfdirections2d(0);
			templateVector(permutation.at(1)) = vectorOfdirections2d(1);

			if(std::find(directions.begin(), directions.end(), templateVector)== directions.end()){
                            directions.push_back(templateVector);
                        }
		}
	}

	return directions;
}

/*
 * Compute a set of uniformly distributed directions that are orthogonal to a given normal and all lie in one hyperplane
 */

//template<typename Number>
//static matrix_t<Number> computeOrthogonalTemplateDirections( vector_t<Number> normal, unsigned numberOfDirections){
//    unsigned dim = normal.rows();
//    matrix_t<Number> res =matrix_t<Number>(numberOfDirections, dim);
//    vector_t<Number> firstVec = vector_t<Number>::Zero(dim);
    //if dimension is at least 2
//    if (dim > 1){
//        bool foundOne = false;
//        unsigned indexOne;
//        bool foundTwo = false;
//        unsigned indexTwo;
        //check every entry of the normal
//        for (unsigned i=0; i< dim; ++i){
                //the first non-zero entry gets remembered (if it exists)
//                 if (normal(i) != 0 && foundOne == false){
//                         foundOne = true;
//                         indexOne = i;
                 //the second non-zero entry gets remembered (if it exists)
//                 } else if (normal(i) != 0 && foundOne == true && foundTwo == false){
//                         foundTwo = true;
//                         indexTwo = i;
//                 }
//        }
        //if 2 non-zero entries were found
//        if (foundTwo == true && foundOne == true){
//                firstVec(indexOne) = (Number) 1/normal(indexOne);
//                firstVec(indexTwo) = (Number) (-1)*1/normal(indexTwo);
        //if only one non-zero entry was found (is an axis-direction)
//        } else if (foundTwo == false && foundOne == true){
                //if the index before the non-zero entry exists
//                if (indexOne > 0){
//                    firstVec(indexOne-1) = 1;
                //if the index before the non-zero entry doesn't exist (but after it)
//                } else {
//                    firstVec(indexOne+1) = 1;
//                }
        //if the normal is the 0-vector (is not allowed to happen
//        } else {
//            assert(false);
//        }
        
        
        
//    }
//    return res;
//}

} // namespace hypro
