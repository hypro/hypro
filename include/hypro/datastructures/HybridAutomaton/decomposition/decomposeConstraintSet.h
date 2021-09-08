#pragma once
#include "../../../types.h"
#include "Decomposition.h"

namespace hypro {

template <template <typename, typename> typename Rep, typename Number, typename Settings>
void decomposeConstraintSet( Rep<Number, Settings>& in, const Decomposition& decomposition, std::vector<Rep<Number, Settings>>& result ) {
	matrix_t<Number> constraintsOld( in.matrix() );
	vector_t<Number> constantsOld( in.vector() );
	int i = 0;
	for ( auto decomp : decomposition.subspaces ) {
#ifdef HYPRO_LOGGING
		DEBUG( "hypro.datastructures", "Trying to project set: \n " << in << "\n to dimensions: " );
		DEBUG( "hypro.datastructures", "{" );
		for ( auto entry : decomp ) {
			DEBUG( "hypro.datastructures", "" << entry << ", " );
		}
		DEBUG( "hypro.datastructures", "}" );
#endif

		// for each row of the constraints check if it contains an entry for one of the variables of the set
		// and add the corresponding rows to a list of indices that are later added to the result matrix
		std::vector<int> indicesToAdd;
		for ( int i = 0; i < constraintsOld.rows(); i++ ) {
			vector_t<Number> row = constraintsOld.row( i );
			bool containsVar = false;
			for ( int j = 0; j < row.rows(); j++ ) {
				if ( row( j, 0 ) != 0 ) {
					if ( std::find( decomp.begin(), decomp.end(), j ) != decomp.end() ) {
						// set contains variable j, which is also contained in this constraint
						containsVar = true;
						break;
					}
				}
			}
			if ( containsVar ) {
				// this row contains information for one of the variables of this decomposition
				indicesToAdd.push_back( i );
			}
		}

		// we found information for our decomposition
		if ( indicesToAdd.size() > 0 ) {
			// create a row matrix with numIndicesToAdd many rows
			matrix_t<Number> rowMat = matrix_t<Number>::Zero( indicesToAdd.size(), constraintsOld.cols() );
			for ( Eigen::Index index = 0; index < rowMat.rows(); index++ ) {
				// copy over preselected rows
				rowMat.row( index ) = constraintsOld.row( indicesToAdd[index] );
			}
			// create final matrix that does not contain columns not in this set
			matrix_t<Number> finMat = matrix_t<Number>::Zero( rowMat.rows(), decomp.size() );
			// -1 for constant column
			for ( Eigen::Index index = 0; index < finMat.cols(); index++ ) {
				finMat.col( index ) = rowMat.col( decomp[index] );
			}
			// create final constant vector
			vector_t<Number> finVec = vector_t<Number>::Zero( indicesToAdd.size() );
			for ( Eigen::Index index = 0; index < finVec.rows(); index++ ) {
				finVec( index ) = constantsOld( indicesToAdd[index] );
			}

			result.emplace_back( Rep<Number, Settings>( finMat, finVec ) );
			DEBUG( "hypro.datastructures", "Final decomposed ConstraintSet: \n"
												 << result.back() );
		} else {
			DEBUG( "hypro.datastructures", "No constraints for set found." );
			// do nothing.
		}
		i++;
	}
}

}  // namespace hypro