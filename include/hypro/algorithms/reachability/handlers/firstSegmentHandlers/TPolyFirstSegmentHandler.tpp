#pragma once

#include "TPolyFirstSegmentHandler.h"

namespace hypro {

template <typename State>
void TPolyFirstSegmentHandler<State>::setInvariant( const vector_t<typename State::NumberType>& inv ) {
	mStrengthenedInvariant = std::optional<vector_t<Number>>( inv );
}

template <typename State>
vector_t<typename State::NumberType> TPolyFirstSegmentHandler<State>::gradientOfLinearFct( const vector_t<Number>& linearFct ) const {
	assert( (unsigned)linearFct.rows() == this->mState->getDimension() + 1 );
	vector_t<Number> gradient = linearFct;
	gradient( gradient.rows() - 1 ) = 0;
	return gradient;
}

template <typename State>
vector_t<typename State::NumberType> TPolyFirstSegmentHandler<State>::lieDerivative( const vector_t<Number>& dir ) const {
	assert( dir.rows() == this->mState->getLocation()->getLinearFlow().getFlowMatrix().transpose().rows() );
	assert( this->mState->getLocation()->getLinearFlow().getFlowMatrix().transpose().rows() == this->mState->getLocation()->getLinearFlow().getFlowMatrix().transpose().cols() );
	return this->mState->getLocation()->getLinearFlow().getFlowMatrix().transpose() * gradientOfLinearFct( dir );
}

template <typename State>
tNumber TPolyFirstSegmentHandler<State>::maxValueAtRoots( const carl::UnivariatePolynomial<tNumber>& polynom, const carl::Interval<tNumber>& interval ) const {
	// std::cout << "TPolyFirstSegmentHandler::maxValueAtRoots" << std::endl;
	tNumber max( -1e10 );
	tNumber valueAtRoot = 0;
	// Determine roots of derivative to get point where maximum is at
	// NOTE: RealRootIsolation is not supported in carl 19.01
	carl::UnivariatePolynomial<tNumber> derivative = carl::derivative( polynom );
	// std::vector<carl::RealAlgebraicNumber<tNumber>> roots = carl::rootfinder::RealRootIsolation<tNumber>(polynom, interval).get_roots();
	std::vector<carl::RealAlgebraicNumber<tNumber>> roots = carl::rootfinder::realRoots( derivative, interval );
	for ( const carl::RealAlgebraicNumber<tNumber>& root : roots ) {
		tNumber rootNumber( 0 );
		if ( root.isNumeric() ) {
			rootNumber = root.value();
		} else if ( root.isInterval() ) {
			rootNumber = ( root.getInterval().lower() + root.getInterval().upper() ) / tNumber( 2 );
		} else {
			throw std::runtime_error( "TPolyFirstSegmentHandler::handle, unknown time number type." );
			exit( 1 );
		}
		valueAtRoot = polynom.evaluate( rootNumber );
		if ( valueAtRoot > max ) {
			max = valueAtRoot;
		}
		// std::cout << "TPolyFirstSegmentHandler::maxValueAtRoots, max is:" << valueAtRoot << std::endl;
	}
	return max;
}

template <typename State>
void TPolyFirstSegmentHandler<State>::handle() {
	// TODO: get tpoly but do not convert it to TPoly<Number>
	assert( this->mState->getSetType( this->mIndex ) == representation_name::polytope_t );
	// auto tpolySetting = std::visit(genericSettingVisitor(), this->mState->getSet(this->mIndex));
	// using TPolyType = TemplatePolyhedronT<typename State::NumberType, hypro::Converter<Number>, decltype(tpolySetting)>;
	// auto tpoly = std::visit(genericConvertAndGetVisitor<TPolyType>(), this->mState->getSet(this->mIndex));
	auto tpoly = std::visit( genericConvertAndGetVisitor<TemplatePolyhedron<typename State::NumberType>>(), this->mState->getSet( this->mIndex ) );
	vector_t<Number> newVec( tpoly.vector().rows() );

	// For each template row:
	for ( int rowI = 0; rowI < tpoly.matrix().rows(); ++rowI ) {
		// Compute Lie derivative to power of m from initial.matrix().row(i)
		Number factorial = 1;
		vector_t<Number> derivative( tpoly.matrix().cols() + 1 );
		derivative.block( 0, 0, tpoly.matrix().cols(), 1 ) = tpoly.matrix().row( rowI ).transpose();
		derivative( derivative.rows() - 1 ) = 0;

		std::vector<tNumber> polynomCoeffs;			// Ordering is from lowest to highest degree
		std::vector<Number> polynomCoeffsAsNumber;	// Ordering is from lowest to highest degree
		polynomCoeffs.emplace_back( tpoly.vector()( rowI ) );
		polynomCoeffsAsNumber.emplace_back( tpoly.vector()( rowI ) );
		EvaluationResult<Number> evalRes;

		// For first m coefficients in polynom:
		for ( int coeffI = 1; (unsigned)( coeffI - 1 ) < TemplatePolyhedron<Number>::Settings::DERIVATIVE_ORDER; ++coeffI ) {
			factorial *= coeffI;
			derivative = lieDerivative( derivative );
			vector_t<Number> derivVarCoeffs( derivative.rows() - 1 );
			derivVarCoeffs = derivative.block( 0, 0, derivVarCoeffs.rows(), 1 );

			// if index < m+1: Solve LP over tpoly to evaluate into derivative direction
			// if index == m+1: Solve LP over TPoly(matrix(),invariants) to evaluate into derivative direction (remainder term only bounded by invariants)
			if ( (unsigned)coeffI < TemplatePolyhedron<Number>::Settings::DERIVATIVE_ORDER - 1 ) {
				if ( derivVarCoeffs == vector_t<Number>::Zero( derivVarCoeffs.rows() ) ) {
					evalRes = EvaluationResult<Number>( derivative( derivative.rows() - 1 ), SOLUTION::FEAS );
				} else {
					evalRes = tpoly.evaluate( derivVarCoeffs / factorial, std::is_same_v<Number, mpq_class> );
				}
			} else {
				if ( this->mState->getLocation()->getInvariant().empty() ) {
					evalRes = EvaluationResult<Number>( SOLUTION::INFTY );
				} else {
					if ( tpoly.getSettings().USE_LOCATION_INVARIANT_STRENGTHENING && mStrengthenedInvariant ) {
						// std::cout << "TPolyFirstSegmentHandler::handle, use LIS, mStrengthenedInvariant: " << mStrengthenedInvariant->transpose() << std::endl;
						// mStrengthenedInvariant is strenghtened offset vector of overapproximation of invariant - use this to create invTPoly.
						// Using mStrengthenedInvariant will lead to tighter bounds
						assert( tpoly.matrix().rows() == mStrengthenedInvariant->rows() );
						assert( derivVarCoeffs.rows() == tpoly.matrix().cols() );
						TemplatePolyhedron<Number> invTPoly( tpoly.matrix(), *mStrengthenedInvariant );
						evalRes = invTPoly.evaluate( derivVarCoeffs / factorial, std::is_same_v<Number, mpq_class> );
						// std::cout << "TPolyFirstSegmentHandler::handle, evalRes: " << evalRes << std::endl;
					} else {
						// std::cout << "TPolyFirstSegmentHandler::handle, do not use LIS" << std::endl;
						auto invMat = this->mState->getLocation()->getInvariant().getMatrix();
						auto invVec = this->mState->getLocation()->getInvariant().getVector();
						assert( invMat.rows() == invVec.rows() );
						assert( (unsigned)invMat.cols() == this->mState->getDimension() );
						TemplatePolyhedron<Number> invTPoly( invMat, invVec );
						evalRes = invTPoly.evaluate( derivVarCoeffs / factorial, std::is_same_v<Number, mpq_class> );
						// std::cout << "TPolyFirstSegmentHandler::handle, evalRes: " << evalRes << std::endl;
					}
				}
			}

			// Save resulting value as coeff in polynomCoeffs
			if ( evalRes.errorCode == SOLUTION::FEAS ) {
				if ( TemplatePolyhedron<Number>::Settings::DIRECTLY_COMPUTE_ROOTS ) {
					polynomCoeffs.emplace_back( carl::convert<Number, tNumber>( evalRes.supportValue ) );
				} else {
					polynomCoeffs.emplace_back( carl::convert<Number, tNumber>( evalRes.supportValue ) );
					polynomCoeffsAsNumber.emplace_back( evalRes.supportValue );
				}
			}
		}

		// Get maximum value of polynom in time interval [0,delta] save in new coeff vec
		// if(TPolyType::Settings::DIRECTLY_COMPUTE_ROOTS){
		if ( TemplatePolyhedron<Number>::Settings::DIRECTLY_COMPUTE_ROOTS ) {
			// Compute derivative of polynom
			carl::Variable var = carl::freshRealVariable( "t" );
			carl::UnivariatePolynomial<tNumber> polynom( var, polynomCoeffs );
			// Compute roots that lie in interval and check for maximal value there
			tNumber max = maxValueAtRoots( polynom, carl::Interval<tNumber>( tNumber( 0 ), this->mTimeStep ) );
			// Get value for 0 and for this->mTimeStep and then somehow compute firstSegment
			tNumber valueAtRoot = polynom.evaluate( tNumber( 0 ) );
			if ( valueAtRoot > max ) {
				max = valueAtRoot;
			}
			valueAtRoot = polynom.evaluate( this->mTimeStep );
			if ( valueAtRoot > max ) {
				max = valueAtRoot;
			}
			// Set value in coeff vec
			newVec( rowI ) = carl::convert<tNumber, Number>( max );
		} else {
			// Check approximately whether interval is monotonically in-/decreasing
			// Check some values in [0,mTimeStep] and whether they in-/decrease throughoutly.
			carl::Variable var = carl::freshRealVariable( "t" );
			carl::UnivariatePolynomial<Number> polynom( var, polynomCoeffsAsNumber );
			std::vector<Number> values;
			bool increasing = true;
			bool decreasing = true;
			assert( this->mTimeStep != tNumber( 0 ) );
			for ( tNumber timeStepPart = 0; timeStepPart <= this->mTimeStep; timeStepPart += ( this->mTimeStep / tNumber( tpoly.getSettings().MONOTONICITY_GRANULARITY ) ) ) {
				values.emplace_back( polynom.evaluate( carl::convert<tNumber, Number>( timeStepPart ) ) );
				if ( values.size() >= 2 ) {
					if ( increasing && values.at( values.size() - 2 ) > values.at( values.size() - 1 ) ) {
						// std::cout << "TPolyFirstSegmentHandler::handle, not increasing anymore!" << std::endl;
						increasing = false;
					}
					if ( decreasing && values.at( values.size() - 2 ) <= values.at( values.size() - 1 ) ) {
						// std::cout << "TPolyFirstSegmentHandler::handle, not decreasing anymore!" << std::endl;
						decreasing = false;
					}
					if ( !increasing && !decreasing ) {
						// std::cout << "TPolyFirstSegmentHandler::handle, break!" << std::endl;
						break;
					}
				}
			}
			// std::cout << "TPolyFirstSegmentHandler::handle, timestep: " << carl::toDouble(this->mTimeStep) << std::endl;
			// std::cout << "TPolyFirstSegmentHandler::handle, increasing? " << increasing << " decreasig? " << decreasing << std::endl;
			assert( values.size() <= tpoly.getSettings().MONOTONICITY_GRANULARITY + 1 );
			if ( !increasing && !decreasing ) {
				// If not monotonically increasing or decreasing, then there must be a maximum in the interval -> compute expensive root enumeration
				carl::UnivariatePolynomial<tNumber> polynomAsTNumber( var, polynomCoeffs );
				newVec( rowI ) = carl::convert<tNumber, Number>( maxValueAtRoots( polynomAsTNumber, carl::Interval<tNumber>( tNumber( 0 ), this->mTimeStep ) ) );
			} else if ( !increasing && decreasing ) {
				// If monotonically decreasing, then first value at t = 0 was the biggest one
				newVec( rowI ) = values.front();
			} else if ( increasing && !decreasing ) {
				// If monotonically increasing, then last value at t = mTimeStep was the biggest one
				newVec( rowI ) = values.back();
			} else {
				// Should not be possible
				throw std::runtime_error( "TPolyFirstSegmentHandler::handle, polynom was both monotonically increasing as well as decreasing." );
				exit( 1 );
			}
		}
	}

	// Set mComputationState vector to the new coeff vec
	tpoly.setVector( newVec );
	this->mState->setSet( std::visit( genericInternalConversionVisitor<typename State::repVariant, TemplatePolyhedron<Number>>( tpoly ), this->mState->getSet( this->mIndex ) ), this->mIndex );

	// Set flow for further computations
	this->mTrafo = this->mState->getLocation()->getLinearFlow().getFlowMatrix().block( 0, 0, this->mState->getDimension(), this->mState->getDimension() );
	this->mTranslation = this->mState->getLocation()->getLinearFlow().getFlowMatrix().block( 0, this->mState->getDimension(), this->mState->getDimension(), 1 );
	this->mFlow = affineFlow<Number>( this->mTrafo, this->mTranslation );
}

}  // namespace hypro
