#include "GeneralPiecewiseLinear.h"

namespace hypro{

template <typename Number>
std::vector<hypro::Starset<Number>> GeneralPiecewiseLinear<Number>::stepGeneralPiecewiseLinear( int i, const std::vector<hypro::Starset<Number>>& input_sets, size_t numPieces,
																  const std::vector<Number>& lowerBounds, const std::vector<Number>& upperBounds,
																  const std::vector<Number>& slopes, const std::vector<Number>& offsets ) {
    return std::vector<hypro::Starset<Number>>();
}

template <typename Number>
std::vector<hypro::Starset<Number>> GeneralPiecewiseLinear<Number>::approxStepGeneralPiecewiseLinear( int i, const std::vector<hypro::Starset<Number>>& input_sets, size_t numPieces,
																  const std::vector<Number>& lowerBounds, const std::vector<Number>& upperBounds,
																  const std::vector<Number>& slopes, const std::vector<Number>& offsets ) {
    return std::vector<hypro::Starset<Number>>();
}

} // namespace hypro
