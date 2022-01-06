#include "TPolyTimeEvolutionHandler.h"

namespace hypro {

template <typename State>
void TPolyTimeEvolutionHandler<State>::setInvariant( const vector_t<typename State::NumberType>& inv ) {
	mStrengthenedInvariant = std::optional<vector_t<Number>>( inv );
}

template <typename State>
vector_t<typename State::NumberType> TPolyTimeEvolutionHandler<State>::gradientOfLinearFct( const vector_t<Number>& linearFct ) {
	assert( (unsigned)linearFct.rows() == this->mState->getDimension() + 1 );
	vector_t<Number> gradient = linearFct;
	gradient( gradient.rows() - 1 ) = 0;
	return gradient;
}

template <typename State>
vector_t<typename State::NumberType> TPolyTimeEvolutionHandler<State>::lieDerivative( const vector_t<Number>& dir ) {
	assert( dir.rows() == this->mState->getLocation()->getLinearFlow().getFlowMatrix().transpose().rows() );
	assert( this->mState->getLocation()->getLinearFlow().getFlowMatrix().transpose().rows() == this->mState->getLocation()->getLinearFlow().getFlowMatrix().transpose().cols() );
	return this->mState->getLocation()->getLinearFlow().getFlowMatrix().transpose() * gradientOfLinearFct( dir );
}

template <typename State>
void TPolyTimeEvolutionHandler<State>::handle() {
	assert( this->mState->getSetType( this->mIndex ) == representation_name::polytope_t );
	auto tpoly = std::visit( genericConvertAndGetVisitor<TemplatePolyhedron<typename State::NumberType>>(), this->mState->getSet( this->mIndex ) );
	assert( !tpoly.empty() );

	if ( !TemplatePolyhedron<Number>::Settings::USE_ALTERNATIVE_REACH_ALGO ) {
		this->mState->setSet( ltiApplyTimeEvolution<State, Number>( *this->mState, this->mTrafo, this->mTranslation, this->mTimeStep ), this->mIndex );
		return;
	}

	vector_t<Number> newVec = vector_t<Number>::Zero( tpoly.vector().rows() );

	// For each row:
	for ( int rowI = 0; rowI < tpoly.matrix().rows(); ++rowI ) {
		// Compute Lie derivative to power of m from initial.matrix().row(i)
		Number factorial = 1;
		Number timestepPower = 1;
		vector_t<Number> derivative( tpoly.matrix().cols() + 1 );
		derivative.block( 0, 0, tpoly.matrix().cols(), 1 ) = tpoly.matrix().row( rowI ).transpose();
		derivative( derivative.rows() - 1 ) = 0;
		vector_t<Number> g = derivative;
		vector_t<Number> r = vector_t<Number>::Zero( tpoly.matrix().cols() + 1 );

		// For first m coefficients in polynom:
		for ( int coeffI = 1; (unsigned)( coeffI - 1 ) < TemplatePolyhedron<Number>::Settings::DERIVATIVE_ORDER; ++coeffI ) {
			// Special case: first index does not use lie derivative
			factorial *= coeffI;
			timestepPower *= carl::convert<tNumber, Number>( this->mTimeStep );
			derivative = lieDerivative( derivative );

			// Optimization: if the derivative is zero, then the following derivatives will also be zero, not contributing to the values.
			if ( derivative == vector_t<Number>::Zero( derivative.rows() ) ) break;

			// if index < m+1: Solve LP over tpoly to evaluate into derivative direction
			// if index == m+1: Solve LP over TPoly(matrix(),invariants) to evaluate into derivative direction (remainder term only bounded by invariants)
			if ( (unsigned)coeffI < TemplatePolyhedron<Number>::Settings::DERIVATIVE_ORDER - 1 ) {
				g += ( timestepPower / factorial ) * derivative;
			} else {
				// If using the invariant matrix we either get the same or better results.
				r = ( timestepPower / factorial ) * derivative;
			}
		}

		// Evaluate tpoly in direction g without last coeff (since g is dim+1 dimensional)
		// The last coefficient is added to the support value
		EvaluationResult<Number> evalG = tpoly.evaluate( vector_t<Number>( g.block( 0, 0, g.rows() - 1, 1 ) ), std::is_same_v<Number, mpq_class> );
		// std::cout << "TPolyTimeEvolutionHandler::handle, evalG: " << evalG << std::endl;
		// If solution is infeasible, we already received an empty tpoly in the beginning
		// if(evalG.errorCode == SOLUTION::INFEAS){ return; }
		assert( evalG.errorCode == SOLUTION::FEAS );

		// Evaluate invPoly in direction r without last coeff
		EvaluationResult<Number> evalR;
		if ( this->mState->getLocation()->getInvariant().empty() ) {
			evalR = EvaluationResult<Number>( SOLUTION::INFTY );
		} else {
			if ( tpoly.getSettings().USE_LOCATION_INVARIANT_STRENGTHENING && mStrengthenedInvariant ) {
				// mStrengthenedInvariant is strenghtened offset vector of overapproximation of invariant - use this to create invTPoly.
				// Using mStrengthenedInvariant will lead to tighter bounds
				assert( tpoly.matrix().rows() == mStrengthenedInvariant->rows() );
				TemplatePolyhedron<Number> invTPoly( tpoly.matrix(), *mStrengthenedInvariant );
				evalR = invTPoly.evaluate( vector_t<Number>( r.block( 0, 0, r.rows() - 1, 1 ) ), std::is_same_v<Number, mpq_class> );
				// std::cout << "TPolyTimeEvolutionHandler::handle, evalR: " << evalR << std::endl;
			} else {
				auto invMat = this->mState->getLocation()->getInvariant().getMatrix();
				auto invVec = this->mState->getLocation()->getInvariant().getVector();
				assert( invMat.rows() == invVec.rows() );
				assert( (unsigned)invMat.cols() == this->mState->getDimension() );
				TemplatePolyhedron<Number> invTPoly( invMat, invVec );
				evalR = invTPoly.evaluate( vector_t<Number>( r.block( 0, 0, r.rows() - 1, 1 ) ), std::is_same_v<Number, mpq_class> );
				// std::cout << "TPolyTimeEvolutionHandler::handle, evalR: " << evalR << std::endl;
			}
		}

		// Set value in coeff vec
		if ( evalR.errorCode == SOLUTION::FEAS ) {
			newVec( rowI ) = evalG.supportValue + g( g.rows() - 1 ) + evalR.supportValue + r( r.rows() - 1 );
		} else {
			newVec( rowI ) = evalG.supportValue + g( g.rows() - 1 );
		}
	}

	// Set mComputationState vector to the new coeff vec
	// std::cout << "newVec: \n" << newVec << std::endl;
	tpoly.setVector( newVec );
	this->mState->setSet( std::visit( genericInternalConversionVisitor<typename State::repVariant, TemplatePolyhedron<Number>>( tpoly ), this->mState->getSet( this->mIndex ) ), this->mIndex );
}

}  // namespace hypro