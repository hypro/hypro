/*
 * This file contains the additions needed for eigen3 to support our own floating
 * type FLOAT_T.
 * @file   eigenTypetraits.h
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 *
 * @since   2014-05-02
 * @version 2014-05-02
 */

#pragma once
#include <carl/numbers/numbers.h>
#include <functional>
#include <iostream>
#include <limits>

namespace Eigen {

template <typename Number>
bool operator<( const hypro::vector_t<Number>& lhs, const hypro::vector_t<Number>& rhs ) {
	if ( lhs.rows() != rhs.rows() ){
		return false;
	}

	for ( unsigned dim = 0; dim < lhs.rows(); ++dim ) {
		if ( lhs( dim ) > rhs( dim ) ) {
			return false;
		} else if ( lhs( dim ) < rhs( dim ) ) {
			return true;
		}
	}
	return false;
}

	template <typename Number>
	bool operator<=( const hypro::vector_t<Number>& lhs, const hypro::vector_t<Number>& rhs ) {
		if ( lhs.rows() != rhs.rows() ) {
			return false;
		}

		for ( unsigned dim = 0; dim < lhs.rows(); ++dim ) {
			if ( lhs( dim ) > rhs( dim ) ) {
				return false;
			} else if ( lhs( dim ) <= rhs( dim ) ) {
				return true;
			}
		}
		return false;
	}

	template<typename Number>
	bool operator>( const hypro::vector_t<Number>& lhs, const hypro::vector_t<Number>& rhs ) { return rhs < lhs;}

	template<typename Number>
	bool operator>=( const hypro::vector_t<Number>& lhs, const hypro::vector_t<Number>& rhs ) { return rhs <= lhs;}

	/*!
	 * computes a hash chain over a vector nx1 using carl::hash_add and returns it
	 * @param pVector input vector
	 * @return size_t hash seed
	 */
	template <typename Number>
	std::size_t VectorHashValue( const hypro::vector_t<Number>& pVector ) {
		//std::cout << "VECTOR_HASH(" << pVector.transpose() << ")" << std::endl;
		size_t seed = 0;
		for (int i = 0; i < pVector.rows(); i++) {
			std::size_t tmp = std::hash<Number>()(pVector(i));
			//std::cout << __func__ << ": " << i << ", "<< pVector(i) << " -> " << tmp << std::endl;
			carl::hash_add(seed, tmp);
		}
		//std::cout << seed << std::endl;
		return seed;
	}

	/*!
	 * computes a hash chain over a matrix using carl::hash_add
	 * @param pMatrix input matrix
	 * @return size_t
	 */
	template <typename Number>
	std::size_t MatrixHashValue( const hypro::matrix_t<Number>& pMatrix ) {
		size_t seed = 0;
		for (int i = 0; i < pMatrix.rows(); i++) {
			for (int j = 0; j < pMatrix.cols(); j++) {
				carl::hash_add(seed, pMatrix(i, j));
			}
		}
		return seed;
	}


template <typename Number>
bool operator==( const hypro::vector_t<Number>& lhs, const hypro::vector_t<Number>& rhs ) {
	if ( lhs.rows() != rhs.rows() ){
		return false;
	}
	if ( VectorHashValue(lhs) != VectorHashValue(rhs) ){
		return false;
	}

	for ( unsigned dim = 0; dim < lhs.rows(); ++dim ) {
		if (lhs( dim ) != rhs( dim )) {
			return false;
		}
	}
	return true;
}

template<typename Number>
bool operator!=( const hypro::vector_t<Number>& lhs, const hypro::vector_t<Number>& rhs ) {
	return !(lhs == rhs);
}

template <typename Number>
bool operator==( const hypro::matrix_t<Number>& lhs, const hypro::matrix_t<Number>& rhs ) {
	if ( lhs.rows() != rhs.rows() || lhs.cols() != rhs.cols() ){
		return false;
	}
	if ( MatrixHashValue(lhs) != MatrixHashValue(rhs) ){
		return false;
	}

	for ( unsigned rowIndex = 0; rowIndex < lhs.rows(); ++rowIndex ) {
		for ( unsigned colIndex = 0; colIndex < lhs.cols(); ++colIndex ) {
			if ( lhs( rowIndex, colIndex ) != rhs( rowIndex, colIndex ) ) {
				return false;
			}
		}
	}
	return true;
}

template <typename Number>
bool operator!=( const hypro::matrix_t<Number>& lhs, const hypro::matrix_t<Number>& rhs ) {
	return !(lhs == rhs);
}

template<typename Number>
std::ostream& operator<<(std::ostream& _out, const hypro::vector_t<Number>& in) {
	for(unsigned rowIndex = 0; rowIndex < in.rows(); ++rowIndex) {
		_out << in(rowIndex) << std::endl;
	}
	return _out;
}

template<typename Number>
std::ostream& operator<<(std::ostream& _out, const hypro::matrix_t<Number>& in) {
	for(unsigned rowIndex = 0; rowIndex < in.rows(); ++rowIndex) {
		for(unsigned colIndex = 0; colIndex < in.cols(); ++colIndex) {
			_out << in(rowIndex, colIndex) << " ";
		}
		_out << std::endl;
	}
	return _out;
}

template<typename Number>
Number norm(const hypro::vector_t<Number>& in, bool roundUp = true ) {
	Number squares = 0;
	for(size_t i = 0, size = in.size(); i < size; ++i){
		squares = squares + carl::pow(*(in.data()+i), 2);
	}
	assert(squares >= 0);
	if(squares == 0){
		return 0;
	}

	std::pair<Number, Number> dist = carl::sqrt_safe(squares);
	if(roundUp) {
		return dist.second;
	} else {
		return dist.first;
	}
}

template<typename Number>
Number inftyNorm(const hypro::matrix_t<Number>& in) {
	Number norm = carl::abs(*(in.data()));
	for(size_t i = 1, size = in.size(); i < size; ++i){
		Number value = carl::abs(*(in.data()+i));
		norm = norm < value ? value : norm;
	}
	return norm;
}

template<typename Number>
hypro::matrix_t<Number> abs(const hypro::matrix_t<Number>& in) {
	hypro::matrix_t<Number> result = in;
	for(size_t i = 1, size = result.size(); i < size; ++i) {
		*(result.data()+i) = carl::abs(*(result.data()+i));
	}
	return result;
}

} // namespace Eigen

namespace hypro {
	/**
	 * conversion of a matrix_t
	 */
	template <typename From, typename To>
	hypro::matrix_t<To> convert( const hypro::matrix_t<From>& _mat ) {
		hypro::matrix_t<To> resultMat( _mat.rows(), _mat.cols() );

		for ( int i = 0; i < _mat.rows(); ++i ) {
			for ( int j = 0; j < _mat.cols(); ++j ) {
				resultMat( i, j ) = carl::convert<From,To>(_mat( i, j ));
			}
		}
		assert(resultMat.rows() == _mat.rows() && resultMat.cols() == _mat.cols());
		return resultMat;
	}

	template<typename Number>
	hypro::vector_t<Number> normalize(const hypro::vector_t<Number>& in) {
		return in/norm(in);
	}

	template<typename Number>
	hypro::vector_t<Number> scalarProjection(const vector_t<Number>& source, const vector_t<Number>& target) {
		Number targetLength = norm(target);
		vector_t<Number> res = ((source.dot(target))/(targetLength*targetLength))*target;
		return res;
	}

	template<typename Number>
	int effectiveDimension(const std::vector<vector_t<Number>>& vertices) {
		if(!vertices.empty()){
			if(vertices.size() == 1) {
				return 0;
			}
			unsigned maxDim = vertices.begin()->rows();
			matrix_t<Number> matr = matrix_t<Number>(vertices.size()-1, maxDim);
			// use first vertex as origin, start at second vertex
			unsigned rowIndex = 0;
			for(auto vertexIt = ++vertices.begin(); vertexIt != vertices.end(); ++vertexIt, ++rowIndex) {
				matr.row(rowIndex) = (*vertexIt - *vertices.begin()).transpose();
			}
			return matr.fullPivLu().rank();
		}
		return -1;
	}

} // namespace hypro

namespace std {
    template<class Number>
    struct hash<hypro::vector_t<Number>> {
        std::size_t operator()(hypro::vector_t<Number> const& vector) const
        {
            return Eigen::VectorHashValue(vector);
        }
    };

    inline mpq_class abs(const mpq_class& x) {return carl::abs(x);}
	inline mpq_class sqrt(const mpq_class& x) {return carl::sqrt(x);}
	inline mpq_class max(const mpq_class& x, const mpq_class& y) {return ( x > y ? x : y);}

} // namespace std
