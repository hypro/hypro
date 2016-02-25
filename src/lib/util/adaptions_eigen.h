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

namespace Eigen {
template <typename Number>
struct NumTraits<carl::FLOAT_T<Number>> {
	enum {
		IsComplex = 0,
		IsInteger = 0,
		ReadCost = 1,
		AddCost = 1,
		MulCost = 1,
		IsSigned = 1,
		RequireInitialization = 1
	};

	typedef carl::FLOAT_T<Number> Real;
	typedef carl::FLOAT_T<Number> NonInteger;
	typedef carl::FLOAT_T<Number> Nested;

	static inline Real epsilon() { return std::numeric_limits<Real>::epsilon(); }
	static inline Real dummy_precision() {
		// make sure to override this for floating-point types
		return Real( 0 );
	}
	static inline carl::FLOAT_T<Number> highest() { return carl::FLOAT_T<Number>::maxVal(); }
	static inline carl::FLOAT_T<Number> lowest() { return carl::FLOAT_T<Number>::minVal(); }
};

template<>
struct NumTraits<mpq_class> {
	enum {
		IsComplex = 0,
		IsInteger = 0,
		ReadCost = 1,
		AddCost = 1,
		MulCost = 1,
		IsSigned = 1,
		RequireInitialization = 1
	};

	typedef mpq_class Real;
	typedef mpq_class NonInteger;
	typedef mpq_class Nested;

	static inline Real epsilon() { return std::numeric_limits<Real>::epsilon(); }
};

inline mpq_class abs(const mpq_class& x) {return carl::abs(x);}
inline mpq_class sqrt(const mpq_class& x) {return carl::sqrt(x);}
inline mpq_class max(const mpq_class& x, const mpq_class& y) {return ( x > y ? x : y);}

template <typename Number>
bool operator<( const hypro::vector_t<Number>& lhs, const hypro::vector_t<Number>& rhs ) {
	if ( lhs.rows() != rhs.rows() ) return false;

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
		if ( lhs.rows() != rhs.rows() ) return false;

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
	if ( lhs.rows() != rhs.rows() ) return false;
	if ( VectorHashValue(lhs) != VectorHashValue(rhs) ) return false;

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
	if ( lhs.rows() != rhs.rows() || lhs.cols() != rhs.cols() ) return false;
	if ( MatrixHashValue(lhs) != MatrixHashValue(rhs) ) return false;

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
	Number squares;
	for(size_t i = 0, size = in.size(); i < size; ++i){
		squares = squares + carl::pow(*(in.data()+i), 2);
	}

	std::pair<Number, Number> dist = carl::sqrt_safe(squares);
	if(roundUp)
		return dist.second;
	else
		return dist.first;
}

} // namespace Eigen

namespace std {
    template<class Number>
    struct hash<hypro::vector_t<Number>> {
        std::size_t operator()(hypro::vector_t<Number> const& vector) const
        {
            return Eigen::VectorHashValue(vector);
        }
    };
} // namespace std
