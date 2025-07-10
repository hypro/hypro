/**
 * @file StepFunction.h
 * @author Hana Masara <hana.masara@rwth-aachen.de>
 * @brief
 * @date 2022-12-05
 */
#pragma once
#include "hypro/util/logging/Logger.h"

namespace hypro {

template <typename Number>
class StepFunction {
  public:
	static std::vector<hypro::Starset<Number>> exactStepFunction( int i, std::vector<hypro::Starset<Number>>& input_sets, float value, float minValue, float maxValue );
  static std::vector<hypro::Starset<Number>> approxStepFunction( int i, std::vector<hypro::Starset<Number>>& input_sets, float value, float minValue, float maxValue );

  static void resizeShapeAndLimits(hypro::matrix_t<Number>& shape, hypro::vector_t<Number>& limits, int rows);
};
}  // namespace hypro

#include "StepFunction.tpp"
