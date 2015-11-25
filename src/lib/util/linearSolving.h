/**
 * File holding very basic implementations for solving linear problems.
 * @file
 *
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 *
 * @since	2015-11-24
 * @version	2015-11-24
 */

#pragma once
#include "../config.h"

namespace hypro {

	template<typename Number>
	static vector_t<Number> gauss(const matrix_t<Number>& A, const vector_t<Number>& b) {
		assert(A.rows() == A.cols());
		assert(A.rows() == b.rows());

		vector_t<Number> result = vector_t<Number>::Zero(A.rows());
		matrix_t<Number> matrix = A;
		matrix.conservativeResize(Eigen::NoChange, A.cols()+1);
		unsigned lastCol = matrix.cols()-1;
		matrix.col(lastCol) = b;
		std::set<unsigned> usedRows;

		for(unsigned colIndex = 0; colIndex < A.rows(); ++colIndex)
		{
			//std::cout << "Eliminate for column " << colIndex << std::endl;
			unsigned rowIndex = 0;
			// find first row suitable for elimination
			while(rowIndex < matrix.rows() && (usedRows.find(rowIndex) != usedRows.end() || matrix(rowIndex,colIndex) == 0)) {
				++rowIndex;
			}

			//std::cout << "Use row " << rowIndex << " for elimination" << std::endl;
			if(rowIndex < matrix.rows() && matrix(rowIndex,colIndex) != 0){
				usedRows.insert(rowIndex);
				//normalize
				matrix.row(rowIndex) = matrix.row(rowIndex)/matrix(rowIndex,colIndex);
				//assert(matrix(rowIndex,colIndex) == 1);
				for(unsigned rIt = 0; rIt < matrix.rows(); ++ rIt){
					if(rIt != rowIndex && matrix(rIt,colIndex) != 0) {
						// forward insertion
						matrix.row(rIt) = matrix.row(rIt) - (matrix.row(rowIndex)*matrix(rIt, colIndex));
					}
				}
			}
			//std::cout << "A:\n "<< matrix << std::endl;
		}

		// set result
		for(unsigned rIt = 0; rIt < matrix.rows(); ++rIt) {
			if(matrix(rIt, matrix.cols()-1) != 0) {
				for(unsigned cIt = 0; cIt < matrix.cols()-1; ++cIt) {
					if(matrix(rIt,cIt) != 0) {
						result(cIt) = matrix(rIt, matrix.cols()-1);
						break;
					}
				}
			}
		}

		return result;
	}

} // namespace hypro
