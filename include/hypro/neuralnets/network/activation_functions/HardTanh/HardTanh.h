#pragma once
#include "hypro/util/logging/Logger.h"

namespace hypro{

template<typename Number>
class HardTanh {
  public:
	static std::vector<hypro::Starset<Number>> exactHardTanh( int i, std::vector<hypro::Starset<Number>>& input_sets );
	static std::vector<hypro::Starset<Number>> approxHardTanh( int i, std::vector<hypro::Starset<Number>>& input_sets );

};
} //namespace hypro

#include "HardTanh.tpp"
