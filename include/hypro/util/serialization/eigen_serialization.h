/*
 * Copyright (c) 2022.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/*
 * Created by Stefan Schupp <stefan.schupp@tuwien.ac.at> on 23.08.22.
 */

#ifndef HYPRO_EIGEN_SERIALIZATION_H
#define HYPRO_EIGEN_SERIALIZATION_H

#include "../../types.h"

#ifdef HYPRO_USE_SERIALIZATION
#include <cereal/archives/json.hpp>
#endif

namespace cereal {

template <class Archive>
void save( Archive& archive,
		   hypro::matrix_t<double> const& matrix ) {
	std::vector<double> values;
	for ( Eigen::Index r = 0; r < matrix.rows(); ++r ) {
		for ( Eigen::Index c = 0; c < matrix.cols(); ++c ) {
			values.push_back( matrix( r, c ) );
		}
	}
	#ifdef HYPRO_USE_SERIALIZATION
	archive( cereal::make_nvp("rows",matrix.rows()), cereal::make_nvp("cols",matrix.cols()), cereal::make_nvp("coefficients",values) );
	#else
	archive( matrix.rows(), matrix.cols(), values );
	#endif
}

template <class Archive>
void load( Archive& archive,
		   hypro::matrix_t<double>& matrix ) {
	Eigen::Index rows, cols;
	std::vector<double> values;
	archive( rows, cols, values );
	matrix = hypro::matrix_t<double>( rows, cols );
	std::size_t pos{ 0 };
	for ( Eigen::Index r = 0; r < rows; ++r ) {
		for ( Eigen::Index c = 0; c < cols; ++c ) {
			matrix( r, c ) = values[pos++];
		}
	}
}

template <class Archive>
void save( Archive& archive,
		   hypro::vector_t<double> const& vector ) {
	std::vector<double> values;
	for ( Eigen::Index r = 0; r < vector.rows(); ++r ) {
		values.push_back( vector( r ) );
	}
	#ifdef HYPRO_USE_SERIALIZATION
	archive( cereal::make_nvp("rows", vector.rows() ), cereal::make_nvp("coefficients",values));
	#else
	archive( vector.rows(), values );
	#endif
}

template <class Archive>
void load( Archive& archive,
		   hypro::vector_t<double>& vector ) {
	Eigen::Index rows;
	std::vector<double> values;
	archive( rows, values );
	vector = hypro::vector_t<double>( rows );
	std::size_t pos{ 0 };
	for ( Eigen::Index r = 0; r < rows; ++r ) {
		vector( r ) = values[pos++];
	}
}

// ####################################################################

template <class Archive>
void save( Archive& archive,
		   hypro::matrix_t<mpq_class> const& matrix ) {
	std::vector<mpq_class> values;
	for ( Eigen::Index r = 0; r < matrix.rows(); ++r ) {
		for ( Eigen::Index c = 0; c < matrix.cols(); ++c ) {
			values.push_back( matrix( r, c ) );
		}
	}
	#ifdef HYPRO_USE_SERIALIZATION
	archive( cereal::make_nvp("rows",matrix.rows()), cereal::make_nvp("cols",matrix.cols()), cereal::make_nvp("coefficients",values) );
	#else
	archive( matrix.rows(), matrix.cols(), values );
	#endif
}

template <class Archive>
void load( Archive& archive,
		   hypro::matrix_t<mpq_class>& matrix ) {
	Eigen::Index rows, cols;
	std::vector<mpq_class> values;
	archive( rows, cols, values );
	matrix = hypro::matrix_t<mpq_class>( rows, cols );
	std::size_t pos{ 0 };
	for ( Eigen::Index r = 0; r < rows; ++r ) {
		for ( Eigen::Index c = 0; c < cols; ++c ) {
			matrix( r, c ) = values[pos++];
		}
	}
}

template <class Archive>
void save( Archive& archive,
		   hypro::vector_t<mpq_class> const& vector ) {
	std::vector<mpq_class> values;
	for ( Eigen::Index r = 0; r < vector.rows(); ++r ) {
		values.push_back( vector( r ) );
	}
	#ifdef HYPRO_USE_SERIALIZATION
	archive( cereal::make_nvp("rows", vector.rows() ), cereal::make_nvp("coefficients",values));
	#else
	archive( vector.rows(), values );
	#endif
}

template <class Archive>
void load( Archive& archive,
		   hypro::vector_t<mpq_class>& vector ) {
	Eigen::Index rows;
	std::vector<mpq_class> values;
	archive( rows, values );
	vector = hypro::vector_t<mpq_class>( rows );
	std::size_t pos{ 0 };
	for ( Eigen::Index r = 0; r < rows; ++r ) {
		vector( r ) = values[pos++];
	}
}

}  // namespace cereal

#endif	// HYPRO_EIGEN_SERIALIZATION_H
