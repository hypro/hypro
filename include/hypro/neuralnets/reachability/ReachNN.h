/**
 * Class that implements the reachability analysis for FFNN.
 * @file ReachNN.h
 * @author László Antal <antal@informatik.rwth-aachen.de>
 * @brief Class that implements the forward reachability analysis for 
 * Feedforward Nerual Networks (FFNN) with ReLU activation 
 * functions after each layer (except last layer).
 * @version 2022-01-27
 * @date 2022-01-27
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once
#include "../../representations/GeometricObjectBase.h"
#include "../parser/NNet.h"

#include <iostream>
#include <vector>  // change it later to a better container for Star-sets

namespace hypro {
namespace reachability {

enum NN_reach_method {
	EXACT,
	OVERAPPRX,
};

// TODO: add comments and description/documentation for the different functions
template <typename Number>
class ReachNN {
  private:
	// members
	NNet<Number> mNNet;

  public:
	ReachNN( NNet<Number> nnet )
		: mNNet( nnet ) {}

	// methods
	std::vector<hypro::Starset<Number>> forwardAnalysis( const hypro::Starset<Number>& input_set, NN_reach_method method, bool return_intermediates = false ) const;
	std::vector<hypro::Starset<Number>> layerReach( int l, const std::vector<hypro::Starset<Number>>& input_sets, NN_reach_method method, bool return_intermediates ) const;
	std::vector<hypro::Starset<Number>> reachReLU( const hypro::Starset<Number>& input_star1, NN_reach_method method, bool return_intermediate ) const;
	std::vector<hypro::Starset<Number>> stepReLU( int i, std::vector<hypro::Starset<Number>>& input_sets ) const;
	std::vector<hypro::Starset<Number>> approxStepReLU( int i, std::vector<hypro::Starset<Number>>& input_sets ) const;
};

}  // namespace reachability
}  // namespace hypro

#include "ReachNN.tpp"
