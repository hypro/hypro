/**
* @file HardTanh.h
* @author Hana Masara <hana.masara@rwth-aachen.de>
* @brief
* @date 2022-12-07
 */
#pragma once
#include "hypro/util/logging/Logger.h"

namespace hypro{

template<typename Number>
class LeakyReLU {
  public:
	static std::vector<hypro::Starset<Number>> exactLeakyReLU( int i, std::vector<hypro::Starset<Number>>& input_sets, float negativeSlope);
	static std::vector<hypro::Starset<Number>> approxLeakyReLU( int i, std::vector<hypro::Starset<Number>>& input_sets, float negativeSlope );

};
} //namespace hypro

#include "LeakyReLU.tpp"