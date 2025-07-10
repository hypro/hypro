/**
 * @file ReLU.h
 * @author László Antal <antal@informatik.rwth-aachen.de>
 * @brief
 * @date 2022-06-13
 */
#pragma once
#include "hypro/util/logging/Logger.h"

namespace hypro {

template <typename Number>
class ReLU {
  public:
	static std::vector<hypro::Starset<Number>> stepReLU( int i, const std::vector<hypro::Starset<Number>>& input_sets );
	static std::vector<hypro::Starset<Number>> approxStepReLU( int i, const std::vector<hypro::Starset<Number>>& input_sets );

	static void resizeShapeAndLimits(hypro::matrix_t<Number>& shape, hypro::vector_t<Number>& limits, int rows);

	static std::vector<std::pair<hypro::Starset<Number>, char>> stepReLUWithHistory( int i, const hypro::Starset<Number>& input_set );
	static std::vector<std::pair<hypro::Starset<Number>, char>> approxStepReLUWithHistory( int i, const hypro::Starset<Number>& input_set );

  private:
	ReLU(){};
	~ReLU(){};
};

}  // namespace hypro

#include "ReLU.tpp"
