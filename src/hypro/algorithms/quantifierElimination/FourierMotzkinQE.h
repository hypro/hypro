#pragma once
#include "../../carlTypes.h"
#include "../../util/adaptions_carl/adaptions_formula.h"
#include "../../util/logging/Logger.h"

namespace hypro {

/**
 * @brief Provides a simple implementation for Fourier Motzkin variable elimination for linear, existentially quantified
 * constraints.
 *
 */
template <typename Number>
class FourierMotzkinQE {
  public:
	// we use four vectors, one for the discovered lower bounds, one for the upper bounds, one for the equations and one
	// for unrelated constraints.
	using FormulaPartition = std::vector<FormulasT<Number>>;

  private:
	QEQuery mQuery;				///< The quantifiers to eliminate
	FormulaT<Number> mFormula;	///< The logical representation of the solution space

  public:
	FourierMotzkinQE( const FormulaT<Number>& qfree, const QEQuery& quantifiers )
		: mQuery( quantifiers )
		, mFormula( qfree ) {
		assert( qfree.getType() == carl::FormulaType::CONSTRAINT || qfree.isRealConstraintConjunction() );
	}

	FormulaT<Number> eliminateQuantifiers();

  private:
	FormulaPartition findBounds( const carl::Variable& variable );

	FormulasT<Number> createNewConstraints( const FormulaPartition& bounds, carl::Variable v );

	FormulasT<Number> substituteEquations( const FormulaPartition& bounds, carl::Variable v );

	bool isLinearLowerBound( const ConstraintT<Number>& f, carl::Variable v );

	PolyT<Number> getRemainder( const ConstraintT<Number>& c, carl::Variable v, bool isLowerBnd );
};

template <typename Number, typename IdxType>
std::pair<matrix_t<Number>, vector_t<Number>> eliminateCol( const matrix_t<Number>& constraints, const vector_t<Number> constants, IdxType col, bool conservative = true ) {
	std::vector<std::size_t> nobounds;
	std::vector<std::size_t> upperbounds;
	std::vector<std::size_t> lowerbounds;

	// initialize: detect upper and lower bounds
	for ( Eigen::Index row = 0; row < constraints.rows(); ++row ) {
		if ( constraints( row, col ) == Number( 0 ) ) {
			nobounds.push_back( row );
		} else if ( constraints( row, col ) > Number( 0 ) ) {
			upperbounds.push_back( row );
		} else {
			lowerbounds.push_back( row );
		}
	}

	// initialize result
	Eigen::Index newConstraintsCount = nobounds.size() + ( upperbounds.size() * lowerbounds.size() );
	matrix_t<Number> newConstraints = matrix_t<Number>( newConstraintsCount, constraints.cols() );
	vector_t<Number> newConstants = vector_t<Number>( newConstraintsCount );

	// compute new constraints
	std::vector<Eigen::Index> emptyRows;
	for ( Eigen::Index row = 0; row < newConstraintsCount; ++row ) {
		if ( std::size_t( row ) < nobounds.size() ) {
			newConstraints.row( row ) = constraints.row( nobounds[row] );
			newConstants.row( row ) = constants.row( nobounds[row] );
		} else {
			std::size_t combinationIndex = row - nobounds.size();
			assert( combinationIndex >= 0 and combinationIndex < lowerbounds.size() * upperbounds.size() );
			std::size_t lbIndex = combinationIndex / upperbounds.size();
			std::size_t ubIndex = combinationIndex % upperbounds.size();
			assert( lbIndex < lowerbounds.size() );
			assert( ubIndex < upperbounds.size() );
			newConstraints.row( row ) = constraints( upperbounds[ubIndex], col ) * constraints.row( lowerbounds[lbIndex] ) - constraints( lowerbounds[lbIndex], col ) * constraints.row( upperbounds[ubIndex] );
			newConstants( row ) = constraints( upperbounds[ubIndex], col ) * constants( lowerbounds[lbIndex] ) - constraints( lowerbounds[lbIndex], col ) * constants( upperbounds[ubIndex] );
			if ( newConstraints.row( row ).isZero() ) {
				emptyRows.push_back( row );
			}
		}
	}

	assert( vector_t<Number>( newConstraints.col( col ) ) == vector_t<Number>::Zero( newConstants.rows() ) );

	// cleanup, if demanded
	if ( !conservative ) {
		newConstraints = removeCol( newConstraints, col );
	}

	newConstraints = removeRows( newConstraints, emptyRows );
	newConstants = removeRows( newConstants, emptyRows );

	auto duplicateRows = getDuplicateRows( newConstraints, newConstants );
	newConstraints = removeRows( newConstraints, duplicateRows );
	newConstants = removeRows( newConstants, duplicateRows );

	return std::make_pair( newConstraints, newConstants );
}

template <typename Number, typename IdxType>
std::pair<matrix_t<Number>, vector_t<Number>> eliminateCols( const matrix_t<Number>& constraints, const vector_t<Number> constants, const std::vector<IdxType>& cols, bool conservative = true ) {
	auto resultConstraints = constraints;
	auto resultConstants = constants;
	for ( auto cIndex : cols ) {
		std::tie( resultConstraints, resultConstants ) = eliminateCol( resultConstraints, resultConstants, cIndex, conservative );
	}
	return std::make_pair( resultConstraints, resultConstants );
}

}  // namespace hypro

#include "FourierMotzkinQE.tpp"
