/**
 * @file ReLU.h
 * @author László Antal <antal@informatik.rwth-aachen.de>
 * @brief
 * @date 2022-06-13
 */
#pragma once
#include "../../../util/logging/Logger.h"

namespace hypro {

template <typename Number>
class ReLU {
  public:
	static std::vector<hypro::Starset<Number>> stepReLU( int i, std::vector<hypro::Starset<Number>>& input_sets );
	static std::vector<hypro::Starset<Number>> approxStepReLU( int i, std::vector<hypro::Starset<Number>>& input_sets );

  private:
	ReLU(){};
	~ReLU(){};
};

}  // namespace hypro

#include "ReLU.tpp"
