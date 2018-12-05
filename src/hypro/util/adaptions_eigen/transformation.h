/**
 * This file contains transformation functions for matrices and vectors.
 */

#pragma once

namespace hypro {

	template<typename Number, typename IdxType>
	matrix_t<Number> selectRows(const matrix_t<Number>& original, const std::vector<IdxType>& rowIndices) {
		matrix_t<Number> res = matrix_t<Number>(rowIndices.size(), original.cols());
		for(Eigen::Index index = 0; index < res.rows(); index++){
			res.row(index) = original.row(Eigen::Index(rowIndices[index]));
		}
		return res;
	}

	template<typename Number, typename IdxType>
	vector_t<Number> selectRows(const vector_t<Number>& original, const std::vector<IdxType>& rowIndices) {
		vector_t<Number> res = vector_t<Number>(rowIndices.size());
		for(Eigen::Index index = 0; index < res.rows(); index++){
			res(index) = original(Eigen::Index(rowIndices[index]));
		}
		return res;
	}

	template<typename Number, typename IdxType>
	matrix_t<Number> selectCols(const matrix_t<Number>& original, const std::vector<IdxType>& colIndices) {
		matrix_t<Number> res = matrix_t<Number>(original.rows(), Eigen::Index(colIndices.size()));
		for(Eigen::Index index = 0; index < res.cols(); index++){
			res.col(index) = original.col(Eigen::Index(colIndices[index]));
		}
		return res;
	}

	template<typename Number>
	static matrix_t<Number> combine(
		const matrix_t<Number>& lhsMatrix, const matrix_t<Number>& rhsMatrix,
		const std::vector<std::string>& haVar, const std::vector<std::string>& lhsVar, const std::vector<std::string>& rhsVar) {

		Eigen::Index lhsRows = lhsMatrix.rows();
		Eigen::Index rhsRows = rhsMatrix.rows();
		matrix_t<Number> tmpMatrix = matrix_t<Number>::Zero(lhsRows+rhsRows, haVar.size());

		size_t col=0;
		unsigned colLhs = 0;
		while (colLhs < lhsMatrix.cols()) {
			if(haVar[col] == lhsVar[colLhs]) {
				tmpMatrix.block(0, col, lhsRows, 1) = lhsMatrix.block(0, colLhs, lhsRows, 1);
				col++; colLhs++;
				continue;
			}
			if(haVar[col] < lhsVar[colLhs]) {
				col++;
				continue;
			}
		}

		col=0;
		unsigned colRhs = 0;
		while (colRhs < rhsMatrix.cols()) {
			if(haVar[col] == rhsVar[colRhs]) {
				tmpMatrix.block(lhsRows, col, rhsRows, 1) = rhsMatrix.block(0, colRhs, rhsRows, 1);
				col++; colRhs++;
				continue;
			}
			if(haVar[col] < rhsVar[colRhs]) {
				col++;
				continue;
			}
		  }
		return tmpMatrix;
	}

	template<typename Number>
	static vector_t<Number> combine(const vector_t<Number>& lhs, const vector_t<Number>& rhs){
		vector_t<Number> newVec = vector_t<Number>::Zero(lhs.size()+rhs.size());
		newVec.head(lhs.size()) = lhs;
		newVec.tail(rhs.size()) = rhs;

		return newVec;
	}

	// interprets all vectors as row-vectors and creates a matrix
	template<typename Number>
	static matrix_t<Number> combineRows(const std::vector<vector_t<Number>>& vectors) {
		matrix_t<Number> res = matrix_t<Number>(vectors.size(),vectors.begin()->rows());

		Eigen::Index rowCount = 0;
		for(const auto& r : vectors) {
			assert(r.rows() == res.cols());
			res.row(rowCount) = r;
			++rowCount;
		}

		return res;
	}

}
