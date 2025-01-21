/**
 * @file GeneralPiecewiseLinear.h
 * @author László Antal <antal@informatik.rwth-aachen.de>
 * @brief
 * @date 2022-06-13
 */
#pragma once
#include "hypro/util/logging/Logger.h"

namespace hypro {

template <typename Number>
class GeneralPiecewiseLinear {
  public:
	static std::vector<hypro::Starset<Number>> stepGeneralPiecewiseLinear( int i, const std::vector<hypro::Starset<Number>>& input_sets, size_t numPieces,
                                                                          const std::vector<Number>& lowerBounds, const std::vector<Number>& upperBounds,
                                                                          const std::vector<Number>& slopes, const std::vector<Number>& offsets );
	static std::vector<hypro::Starset<Number>> approxStepGeneralPiecewiseLinear( int i, const std::vector<hypro::Starset<Number>>& input_sets, size_t numPieces,
                                                                                const std::vector<Number>& lowerBounds, const std::vector<Number>& upperBounds,
                                                                                const std::vector<Number>& slopes, const std::vector<Number>& offsets );

	static void resizeShapeAndLimits(hypro::matrix_t<Number>& shape, hypro::vector_t<Number>& limits, int rows);

  private:
	GeneralPiecewiseLinear(){};
	~GeneralPiecewiseLinear(){};
};

}  // namespace hypro

#include "GeneralPiecewiseLinear.tpp"
