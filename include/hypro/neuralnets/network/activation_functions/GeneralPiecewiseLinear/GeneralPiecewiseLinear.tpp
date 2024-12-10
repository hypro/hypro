#include "GeneralPiecewiseLinear.h"

namespace hypro{

template <typename Number>
std::vector<hypro::Starset<Number>> GeneralPiecewiseLinear<Number>::stepGeneralPiecewiseLinear( int i, const std::vector<hypro::Starset<Number>>& input_sets, size_t numPieces,
																  const std::vector<Number>& lowerBounds, const std::vector<Number>& upperBounds,
																  const std::vector<Number>& slopes, const std::vector<Number>& offsets ) {
    std::vector<hypro::Starset<Number>> result;
    for ( auto& input_set : input_sets ) {
        std::cout << "input set: " << input_set << std::endl;

        // get starset components 
        auto center = input_set.center();
        auto basis = input_set.generator();
        auto polytope = input_set.constraints();

        // find the lower (lb) and upper bound (ub) of x_i 
        hypro::vector_t<Number> dir_vect = basis.row(i);
        auto eval_low_result = polytope.evaluate( -dir_vect );
        auto eval_high_result = polytope.evaluate( dir_vect );

        // if the bound could not be found (either because of infeasability or some other issue) ... this should not happen
		if ( eval_low_result.errorCode == SOLUTION::INFEAS ||
			 eval_low_result.errorCode == SOLUTION::UNKNOWN ||
			 eval_high_result.errorCode == SOLUTION::INFEAS ||
			 eval_high_result.errorCode == SOLUTION::UNKNOWN ) {
			continue;
		}

        // find the index of the piece that include lb
        size_t L = 0;
        if ( eval_low_result.errorCode == SOLUTION::FEAS ) {
            Number lb = -eval_low_result.supportValue + center[i];
            // std::cout << "lb = " << lb << std::endl;
            for ( size_t j = 0; j < numPieces; ++j ) {
                if ( lowerBounds[j] < lb && lb < upperBounds[j] ) {
                    L = j;
                    break;          // can stop searching if we found the index of the piece that contains the lower bound lb, i.e. a_j < lb < b_j
                }
            }
        }

        // find the index of the piece that include lb
        size_t U = numPieces - 1;
        if ( eval_high_result.errorCode == SOLUTION::FEAS ) {
            Number ub = eval_high_result.supportValue + center[i];
            // std::cout << "ub = " << ub << std::endl;
            for ( size_t j = L; j < numPieces; ++j ) {  // can start searching from index L since L <= U
                if ( lowerBounds[j] < ub && ub < upperBounds[j] ) {
                    U = j;
                    break;
                }
            }
        }

        // std::cout << "L = " << L << " & U = " << U << std::endl;

        // if L = U, the input star spans over only one piece of the activation, so it acts as only an affine transformation using f_i  
        if (L == U) {
            basis.row(i) *= slopes[L];
            center.row(i) *= slopes[L]; 
            center.row(i) += offsets[L];
            result.emplace_back(basis, center, polytope);
            continue;
        }

        // otherwise if L < U, then we split the input star into multiple subsets using the pre-defined domains of the relevant pieces and do the corresponding affine transformation on each
        
        // first star and last star are only intersected by 1 constraint, the rest are intersected with two
        auto first_center = center;
        auto first_basis = center;
        auto first_polytope = center;

        // x_i < b_l   (x_i is less or equal than the upper bound of the piece with index L)
        hypro::Halfspace<Number> firstUpperBound = hypro::Halfspace<Number>( basis.row(i), upperBounds[L] - center[i] );
        first_polytope = first_polytope.intersectHalfspace(firstUpperBound);
        first_basis *= slopes[L];
        first_center *= slopes[L];
        first_center += offsets[L];
        
        result.emplace_back(first_center, first_basis, first_polytope);

        auto last_center = center;
        auto last_basis = center;
        auto last_polytope = center;

        // x_i > a_l   (x_i is greater or equal than the lower bound of the piece with index U)
        hypro::Halfspace<Number> lastLowerBound = hypro::Halfspace<Number>( -basis.row(i), center[i] - lowerBounds[U] );
        last_polytope = first_polytope.intersectHalfspace(lastLowerBound);
        last_basis *= slopes[U];
        last_center *= slopes[U];
        last_center += offsets[U];

        result.emplace_back(last_center, last_basis, last_polytope);

        for ( size_t j = L + 1; j < U; ++j ) {
            auto tmp_center = center;
            auto tmp_basis = center;
            auto tmp_polytope = center;

            // a_j <= x_i && x_i <= b_j 
            hypro::Halfspace<Number> tmpLowerBound = hypro::Halfspace<Number>( -basis.row(i), center[i] - lowerBound[j] );
            hypro::Halfspace<Number> tmpUpperBound = hypro::Halfspace<Number>(  basis.row(i), upperBound[j] - center[u] );
            tmp_polytope = tmp_polytope.intersectHalfspace(tmpLowerBound);
            tmp_polytope = tmp_polytope.intersectHalfspace(tmpUpperBound);

            tmp_basis *= slopes[j];
            tmp_center *= slopes[j];
            tmp_center += offsets[j];

            result.emplace_back(tmp_center, tmp_basis, tmp_polytope);
        }
    }
    return result;
}

template <typename Number>
std::vector<hypro::Starset<Number>> GeneralPiecewiseLinear<Number>::approxStepGeneralPiecewiseLinear( int i, const std::vector<hypro::Starset<Number>>& input_sets, size_t numPieces,
																  const std::vector<Number>& lowerBounds, const std::vector<Number>& upperBounds,
																  const std::vector<Number>& slopes, const std::vector<Number>& offsets ) {
    // TODO: implement method
    return std::vector<hypro::Starset<Number>>();
}

// Resize helper function
template <typename Number>
void GeneralPiecewiseLinear<Number>::resizeShapeAndLimits(hypro::matrix_t<Number>& shape, hypro::vector_t<Number>& limits, int rows) {
    shape.conservativeResize(shape.rows() + rows, shape.cols() + 1);
    shape.col(shape.cols() - 1) = hypro::vector_t<Number>::Zero(shape.rows());
    limits.conservativeResize(limits.rows() + rows);
}

} // namespace hypro
