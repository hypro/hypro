#pragma once
#include "../../carlTypes.h"

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
	QEQuery mQuery;
	FormulaT<Number> mFormula;

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

template <typename Number>
std::pair<matrix_t<Number>, vector_t<Number>> eliminateCols( const matrix_t<Number>& constraints, const vector_t<Number> constants, const std::vector<Eigen::Index>& cols ) {
	auto resultConstraints = constraints;
	auto resultConstants = constants;
	for ( auto cIndex : cols ) {
		std::tie( resultConstraints, resultConstants ) = eliminateCol( resultConstraints, resultConstants, cIndex );
	}
	return std::make_pair( resultConstraints, resultConstants );
}

template <typename Number>
std::pair<matrix_t<Number>, vector_t<Number>> eliminateCol( const matrix_t<Number>& constraints, const vector_t<Number> constants, Eigen::Index col ) {
	std::vector<std::size_t> nobounds;
	std::vector<std::size_t> upperbounds;
	std::vector<std::size_t> lowerbounds;

	// initialize: detect uper and lower bounds
	for ( Eigen::Index row = 0; row < constraints.rows(); ++row ) {
		if ( constraints( row, col ) == Number( 0 ) ) {
			nobounds.push_back( row );
			//std::cout << "No bound row: " << row << std::endl;
		} else if ( constraints( row, col ) > Number( 0 ) ) {
			upperbounds.push_back( row );
			//std::cout << "Upper bound row: " << row << std::endl;
		} else {
			lowerbounds.push_back( row );
			//std::cout << "Lower bound row: " << row << std::endl;
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
			//std::cout << "Insert no bound for row " << row << std::endl;
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
				std::cout << "row " << row << " is empty" << std::endl;
			}
			//std::cout << "Have combined lb at pos " << lbIndex << " and ub at pos " << ubIndex << " to " << vector_t<Number>( newConstraints.row( row ) ) << " <= " << Number( newConstants( row ) ) << std::endl;
		}
	}

	//std::cout << "Old constraints: " << constraints << std::endl
	//		  << "Old constants: " << constants << std::endl;

	//std::cout << "Eliminate col: " << col << std::endl;

	//std::cout << "New constraints: " << newConstraints << std::endl
	//		  << "New constants: " << newConstants << std::endl;

	assert( vector_t<Number>( newConstraints.col( col ) ) == vector_t<Number>::Zero( newConstants.rows() ) );

	// cleanup
	//newConstraints = removeCol( newConstraints, col );

	newConstraints = removeRows( newConstraints, emptyRows );
	newConstants = removeRows( newConstants, emptyRows );

	auto duplicateRows = getDuplicateRows( newConstraints );
	newConstraints = removeRows( newConstraints, duplicateRows );
	newConstants = removeRows( newConstants, duplicateRows );

	return std::make_pair( newConstraints, newConstants );
}

}  // namespace hypro

#include "FourierMotzkinQE.tpp"
