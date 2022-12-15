/**
* @file HardTanh.h
* @author Hana Masara <hana.masara@rwth-aachen.de>
* @brief
* @date 2022-12-05
 */
#pragma once
#include "hypro/util/logging/Logger.h"


namespace hypro{

template<typename Number>
class HardSigmoid {
  public:
	static std::vector<hypro::Starset<Number>> exactHardSigmoid( int i, std::vector<hypro::Starset<Number>>& input_sets );
	static std::vector<hypro::Starset<Number>> approxHardSigmoid( int i, std::vector<hypro::Starset<Number>>& input_sets );

};
} //namespace hypro

#include "HardSigmoid.tpp"
