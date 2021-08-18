#pragma once

#include "../../types.h"

namespace hypro {

/**
 * @brief      Struct holding linear and affine transformation parameters.
 * @tparam     Number  The used number type.
 * @tparam     Setting A SupportFunctionNew setting, given by the calling TrafoOp obj.
 * @detail	   Holds a map associating exponents n with the nth-timestep flow matrix A^n and vector b^n
 */
template <typename Number, typename Setting>
struct LinTrafoParameters {
	////// Member Variables

	mutable std::map<unsigned, std::pair<matrix_t<Number>, vector_t<Number>>> parameters;
	unsigned power = Setting::LIN_TRANS_REDUCTION_GROUP_SIZE;
	// 2^power operations are collected
	// 2^power defines the max. number of successive lin.trans before reducing the SF

	////// Constructors & Destructors

	LinTrafoParameters() = delete;

	LinTrafoParameters( const matrix_t<Number>& _A, const vector_t<Number>& _b, unsigned _power = Setting::LIN_TRANS_REDUCTION_GROUP_SIZE )
		: power( _power ) {
		// TRACE("hypro.representations.supportFunction", "Created new lintrafo object." << " (@" << this << ")");
		assert( _A.rows() == _b.rows() );
		parameters[1] = std::make_pair( _A, _b );
	}

	~LinTrafoParameters() {
		// TRACE("hypro.representations.supportFunction", "Delete lintrafo object." << " (@" << this << ")");
	}

	////// Getter & Setter

	matrix_t<Number> matrix() const {
		assert( parameters.begin()->first == 1 );
		return parameters.begin()->second.first;
	}

	vector_t<Number> vector() const {
		assert( parameters.begin()->first == 1 );
		return parameters.begin()->second.second;
	}

	const std::pair<matrix_t<Number>, vector_t<Number>>& getParameterSet( unsigned exponent ) const {
		if ( parameters.find( exponent ) != parameters.end() ) {
			return parameters.at( exponent );
		}
		// create new parameters
		while ( ( --parameters.end() )->first < exponent ) {
			createNextReduct();
		}
		assert( parameters.find( exponent ) != parameters.end() );
		return parameters.at( exponent );
	}

	vector_t<Number> getTransformedDirection( const vector_t<Number>& inDirection, unsigned exponent ) const {
		matrix_t<Number> tmp = getParameterSet( exponent ).first.transpose();
		return tmp * inDirection;
	}

	matrix_t<Number> getTransformedDirections( const matrix_t<Number>& inDirections, unsigned exponent ) const {
		return inDirections * getParameterSet( exponent ).first;
	}

	void createNextReduct() const {
		// the last created reduction pair is at the back, as a std::map is per default sorted ascending
		assert( parameters.size() > 0 );
		unsigned powerOfTwo = carl::pow( 2, power );
		// first compute the new b
		vector_t<Number> bTrans = ( --parameters.end() )->second.second;
		matrix_t<Number> aTrans = ( --parameters.end() )->second.first;
		// std::cout << "Starting from exponent " << (--matrices.end())->first << std::endl;
		unsigned exponent = ( ( --parameters.end() )->first ) * powerOfTwo;
		// std::cout << "New exponent: " << exponent << std::endl;
		//  accumulate b
		for ( std::size_t i = 1; i < powerOfTwo; i++ ) {
			// Note: aTrans hasn't changed yet -> we can use it for transformation.
			bTrans = aTrans * bTrans + ( --parameters.end() )->second.second;
		}
		// accumulate A
		for ( std::size_t i = 0; i < power; i++ ) {
			aTrans = aTrans * aTrans;
		}
		parameters[exponent] = std::make_pair( aTrans, bTrans );
	}

	bool operator==( const LinTrafoParameters<Number, Setting>& rhs ) const {
		return ( this->parameters.begin()->second == rhs.parameters.begin()->second );
	}
};

}  // namespace hypro