/*
 * Copyright (c) 2022.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 *   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

#include "typedefs.h"

#include <hypro/datastructures/reachability/Strategy.h>
#include <hypro/representations/types.h>
#include <iostream>
#include <map>
#include <string>

//#define KEY(a,b) ( (a << 8) | b)

namespace hydra {

static const std::map<std::string, hypro::representation_name> inputToRep = {
	  { "box", hypro::representation_name::box },
	  { "carl_polytope", hypro::representation_name::carl_polytope },
	  { "polytope_h", hypro::representation_name::polytope_h },
	  { "polytope_v", hypro::representation_name::polytope_v },
#ifdef HYPRO_USE_PPL
	  { "ppl_polytope", hypro::representation_name::ppl_polytope },
#endif
	  { "support_function", hypro::representation_name::support_function },
	  { "zonotope", hypro::representation_name::zonotope },
	  { "difference_bounds", hypro::representation_name::difference_bounds },
	  { "SFN", hypro::representation_name::SFN },
	  { "UNDEF", hypro::representation_name::UNDEF },
};

/**
 * @brief      This map lists all representations and the names of their
 * respective settings. Used for dynamic settings.
 */
static const std::map<hypro::representation_name, std::vector<std::string>>
	  rep_settings = {
			{ hypro::representation_name::box,
			  std::vector<std::string>{ "BoxLinearOptimizationOn",
										"BoxLinearOptimizationOff",
										"BoxIntervalArithmeticOff", "BoxAllOff" } },
			{ hypro::representation_name::carl_polytope,
			  std::vector<std::string>{ "CarlPolytopeSetting" } },
			{ hypro::representation_name::polytope_h,
			  std::vector<std::string>{ "HPolytopeSetting",
										"HPolytopeOptimizerCaching" } },
			{ hypro::representation_name::polytope_v,
			  std::vector<std::string>{ "VPolytopeSetting" } },
#ifdef HYPRO_USE_PPL
			{ hypro::representation_name::ppl_polytope,
			  std::vector<std::string>{ "PolytopeSetting" } },
#endif
			{ hypro::representation_name::support_function,
			  std::vector<std::string>{
					"SupportFunctionSetting" } },  //,"NoBoxReduction","NoBoxDetection","NoTrafoReduction","NoReduction","PolytopeSupportFunctionSetting"}},
			{ hypro::representation_name::zonotope,
			  std::vector<std::string>{ "ZonotopeSetting" } },
			{ hypro::representation_name::difference_bounds,
			  std::vector<std::string>{ "DifferenceBoundsSetting" } },
			{ hypro::representation_name::SFN,
			  std::vector<std::string>{ "SupportFunctionNewDefault",
										"SupportFunctionNewMorePrecision",
										"SupportFunctionNewNoReduction" } },
			//{hypro::representation_name::UNDEF,
			// std::vector<std::string>{}}
};

/**
 * @brief   Map from all settings ids to a short description. Used for dynamic
 *settings. The settingsId is built from the representation name and the
 *settings string position in the rep_settings map.
 */
static const std::map<std::string, std::string> settings_descriptions = {
	  { "BoxLinearOptimizationOn",
		"BoxLinearOptimizationOn - Default Setting for boxes. Fastest setting." },
	  { "BoxLinearOptimizationOff", "BoxLinearOptimizationOff" },
	  { "BoxIntervalArithmeticOff", "BoxIntervalArithmeticOff" },
	  { "BoxAllOff", "BoxAllOff" },
	  { "CarlPolytopeSetting",
		"CarlPolytopeSetting - Default Setting for CarlPolytopes." },
	  { "HPolytopeSetting", "HPolytopeSetting - Default Setting for HPolytopes." },
	  { "HPolytopeOptimizerCaching",
		"HPolytopeOptimizerCaching - Faster if a single HPolytope is used "
		"throughout the construction the flowpipe." },
	  { "VPolytopeSetting", "VPolytopeSetting - Default Setting for VPolytopes." },
#ifdef HYPRO_USE_PPL
	  { "PolytopeSetting", "PolytopeSetting - Default Setting for PPL Polytopes." },
#endif
	  { "SupportFunctionSetting",
		"SupportFunctionSetting - Default Setting for Support Functions." },
	  //{"NoBoxReduction", "NoBoxReduction"},
	  //{"NoBoxDetection", "NoBoxDetection"},
	  //{"NoTrafoReduction",				"NoTrafoReduction"},
	  //{"NoReduction",						"NoReduction"},
	  //{"PolytopeSupportFunctionSetting",
	  //"PolytopeSupportFunctionSetting"},
	  { "ZonotopeSetting", "ZonotopeSetting - Default Setting for Zonotopes." },
	  { "DifferenceBoundsSetting",
		"DifferenceBoundsSetting - Default Setting for DifferenceBounds." },
	  { "SupportFunctionNewDefault",
		"SupportFunctionNewDefault - Default Setting for DifferenceBounds." },
	  { "SupportFunctionNewMorePrecision", "SupportFunctionNewMorePrecision" },
	  { "SupportFunctionNewNoReduction", "SupportFunctionNewNoReduction" },
};

/**
 * @brief      For every combination of representations and respective settings,
 * there is a function to construct it and give it back as a
 * StrategyNodeVariant. Used for dynamic settings.
 */

static const std::map<std::string,
					  std::function<hypro::StrategyNodeVariant<State>(
							const hypro::StrategyParameters& )>>
	  repCreationMap = {

			{ "BoxLinearOptimizationOn",
			  []( const hypro::StrategyParameters& param )
					-> hypro::StrategyNodeVariant<State> {
				  using Rep = hypro::BoxT<Number, hypro::Converter<Number>,
										  hypro::BoxLinearOptimizationOn>;
				  return hypro::StrategyNodeVariant<State>( hypro::StrategyNode<Rep>(
						param.timeStep, param.aggregation, param.clustering ) );
			  } },

			{ "BoxLinearOptimizationOff",
			  []( const hypro::StrategyParameters& param )
					-> hypro::StrategyNodeVariant<State> {
				  using Rep = hypro::BoxT<Number, hypro::Converter<Number>,
										  hypro::BoxLinearOptimizationOff>;
				  return hypro::StrategyNodeVariant<State>( hypro::StrategyNode<Rep>(
						param.timeStep, param.aggregation, param.clustering ) );
			  } },

			{ "BoxIntervalArithmeticOff",
			  []( const hypro::StrategyParameters& param )
					-> hypro::StrategyNodeVariant<State> {
				  using Rep = hypro::BoxT<Number, hypro::Converter<Number>,
										  hypro::BoxIntervalArithmeticOff>;
				  return hypro::StrategyNodeVariant<State>( hypro::StrategyNode<Rep>(
						param.timeStep, param.aggregation, param.clustering ) );
			  } },

			{ "BoxAllOff",
			  []( const hypro::StrategyParameters& param )
					-> hypro::StrategyNodeVariant<State> {
				  using Rep =
						hypro::BoxT<Number, hypro::Converter<Number>, hypro::BoxAllOff>;
				  return hypro::StrategyNodeVariant<State>( hypro::StrategyNode<Rep>(
						param.timeStep, param.aggregation, param.clustering ) );
			  } },

			{ "CarlPolytopeSetting",
			  []( const hypro::StrategyParameters& param )
					-> hypro::StrategyNodeVariant<State> {
				  using Rep = hypro::CarlPolytopeT<Number, hypro::Converter<Number>,
												   hypro::CarlPolytopeSetting>;
				  return hypro::StrategyNodeVariant<State>( hypro::StrategyNode<Rep>(
						param.timeStep, param.aggregation, param.clustering ) );
			  } },

			{ "HPolytopeSetting",
			  []( const hypro::StrategyParameters& param )
					-> hypro::StrategyNodeVariant<State> {
				  using Rep = hypro::HPolytopeT<Number, hypro::Converter<Number>,
												hypro::HPolytopeSetting>;
				  return hypro::StrategyNodeVariant<State>( hypro::StrategyNode<Rep>(
						param.timeStep, param.aggregation, param.clustering ) );
			  } },

			{ "HPolytopeOptimizerCaching",
			  []( const hypro::StrategyParameters& param )
					-> hypro::StrategyNodeVariant<State> {
				  using Rep = hypro::HPolytopeT<Number, hypro::Converter<Number>,
												hypro::HPolytopeOptimizerCaching>;
				  return hypro::StrategyNodeVariant<State>( hypro::StrategyNode<Rep>(
						param.timeStep, param.aggregation, param.clustering ) );
			  } },

			{ "VPolytopeSetting",
			  []( const hypro::StrategyParameters& param )
					-> hypro::StrategyNodeVariant<State> {
				  using Rep = hypro::VPolytopeT<Number, hypro::Converter<Number>,
												hypro::VPolytopeSetting>;
				  return hypro::StrategyNodeVariant<State>( hypro::StrategyNode<Rep>(
						param.timeStep, param.aggregation, param.clustering ) );
			  } },

#ifdef HYPRO_USE_PPL
			{ "PolytopeSetting",
			  []( const hypro::StrategyParameters& param )
					-> hypro::StrategyNodeVariant<State> {
				  using Rep = hypro::PolytopeT<Number, hypro::Converter<Number>,
											   hypro::PolytopeSetting>;
				  return hypro::StrategyNodeVariant<State>( hypro::StrategyNode<Rep>(
						param.timeStep, param.aggregation, param.clustering ) );
			  } },
#endif

			{ "SupportFunctionSetting",
			  []( const hypro::StrategyParameters& param )
					-> hypro::StrategyNodeVariant<State> {
				  using Rep = hypro::SupportFunctionT<Number, hypro::Converter<Number>,
													  hypro::SupportFunctionSetting>;
				  return hypro::StrategyNodeVariant<State>( hypro::StrategyNode<Rep>(
						param.timeStep, param.aggregation, param.clustering ) );
			  } },
			/*
					{"NoBoxReduction",
			   [](const hypro::StrategyParameters& param) ->
			   hypro::StrategyNodeVariant<State>	{ using Rep =
			   hypro::SupportFunctionT<Number,hypro::Converter<Number>,hypro::NoBoxReduction>;
																									return hypro::StrategyNodeVariant<State>(hypro::StrategyNode<Rep>(param.timeStep, param.aggregation, param.clustering));}},

					{"NoBoxDetection",
			   [](const hypro::StrategyParameters& param) ->
			   hypro::StrategyNodeVariant<State>	{ using Rep =
			   hypro::SupportFunctionT<Number,hypro::Converter<Number>,hypro::NoBoxDetection>;
																									return hypro::StrategyNodeVariant<State>(hypro::StrategyNode<Rep>(param.timeStep, param.aggregation, param.clustering));}},

					{"NoTrafoReduction",				[](const
			   hypro::StrategyParameters& param) ->
			   hypro::StrategyNodeVariant<State>	{ using Rep =
			   hypro::SupportFunctionT<Number,hypro::Converter<Number>,hypro::NoTrafoReduction>;
																									return hypro::StrategyNodeVariant<State>(hypro::StrategyNode<Rep>(param.timeStep, param.aggregation, param.clustering));}},

					{"NoReduction",
			   [](const hypro::StrategyParameters& param) ->
			   hypro::StrategyNodeVariant<State>	{ using Rep =
			   hypro::SupportFunctionT<Number,hypro::Converter<Number>,hypro::NoReduction>;
																									return hypro::StrategyNodeVariant<State>(hypro::StrategyNode<Rep>(param.timeStep, param.aggregation, param.clustering));}},

					{"PolytopeSupportFunctionSetting",	[](const
			   hypro::StrategyParameters& param) ->
			   hypro::StrategyNodeVariant<State>	{ using Rep =
			   hypro::SupportFunctionT<Number,hypro::Converter<Number>,hypro::PolytopeSupportFunctionSetting>;
																									return hypro::StrategyNodeVariant<State>(hypro::StrategyNode<Rep>(param.timeStep, param.aggregation, param.clustering));}},
			*/
			{ "ZonotopeSetting",
			  []( const hypro::StrategyParameters& param )
					-> hypro::StrategyNodeVariant<State> {
				  using Rep = hypro::ZonotopeT<Number, hypro::Converter<Number>,
											   hypro::ZonotopeSetting>;
				  return hypro::StrategyNodeVariant<State>( hypro::StrategyNode<Rep>(
						param.timeStep, param.aggregation, param.clustering ) );
			  } },

			{ "DifferenceBoundsSetting",
			  []( const hypro::StrategyParameters& param )
					-> hypro::StrategyNodeVariant<State> {
				  using Rep =
						hypro::DifferenceBoundsT<Number, hypro::Converter<Number>,
												 hypro::DifferenceBoundsSetting>;
				  return hypro::StrategyNodeVariant<State>( hypro::StrategyNode<Rep>(
						param.timeStep, param.aggregation, param.clustering ) );
			  } },

			{ "SupportFunctionNewDefault",
			  []( const hypro::StrategyParameters& param )
					-> hypro::StrategyNodeVariant<State> {
				  using Rep =
						hypro::SupportFunctionNewT<Number, hypro::Converter<Number>,
												   hypro::SupportFunctionNewDefault>;
				  return hypro::StrategyNodeVariant<State>( hypro::StrategyNode<Rep>(
						param.timeStep, param.aggregation, param.clustering ) );
			  } },

			{ "SupportFunctionNewMorePrecision",
			  []( const hypro::StrategyParameters& param )
					-> hypro::StrategyNodeVariant<State> {
				  using Rep = hypro::SupportFunctionNewT<
						Number, hypro::Converter<Number>,
						hypro::SupportFunctionNewMorePrecision>;
				  return hypro::StrategyNodeVariant<State>( hypro::StrategyNode<Rep>(
						param.timeStep, param.aggregation, param.clustering ) );
			  } },

			{ "SupportFunctionNewNoReduction",
			  []( const hypro::StrategyParameters& param )
					-> hypro::StrategyNodeVariant<State> {
				  using Rep =
						hypro::SupportFunctionNewT<Number, hypro::Converter<Number>,
												   hypro::SupportFunctionNewNoReduction>;
				  return hypro::StrategyNodeVariant<State>( hypro::StrategyNode<Rep>(
						param.timeStep, param.aggregation, param.clustering ) );
			  } },

};

}  // namespace hydra
