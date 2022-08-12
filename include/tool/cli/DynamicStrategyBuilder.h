// /**
//  *	DynamicStrategyBuilder.h
//  *
//  *	Assemble a reachability strategy during runtime via the command line
//  *gui! Or directly build a strategy in the commandline via --snode rep set
//  *timestep agg cluster --snode rep2 set2 timestep2 agg2 cluster2
//  *
//  *	@author Phillip Tse
//  *  @date 7.11.2019
//  */

// #pragma once
// #include "../../hypro/representations/GeometricObjectBase.h"
// #include "../Strategies.h"
// #include "dynamic_setting_util.h"
// #include <boost/program_options.hpp>
// #include <boost/program_options/errors.hpp>
// #include <exception>
// #include <string>

// namespace hydra {

// namespace po = boost::program_options;

// class DynamicStrategyBuilder {

//  private:
// 	// For parsing in gui mode
// 	po::variables_map vmStrat;
// 	po::options_description mOptions =
// 		po::options_description("Allowed Parameters: ");

// 	// For holding values
// 	hypro::representation_name mChosenRep;
// 	std::string mChosenSetting;
// 	hypro::StrategyParameters mStratSettings;
// 	hypro::Strategy<State> mStrategy;
// 	bool done = false;

// 	// Shows instructions in the gui mode
// 	void showMessage();
// 	// Parses input in the gui mode
// 	void parse();
// 	// Handles parsed input in the gui mode
// 	void handle();

// public:
//   // Default constructor
//   DynamicStrategyBuilder();

//   // For building a strategy via the snodes options in command line
//   DynamicStrategyBuilder(
//       const std::vector<std::vector<std::string>> &snodeStrings);

//   // Destructor
//   ~DynamicStrategyBuilder() {}

//   // Starts the gui mode
//   void startGui();

//   /*
//    * Adds a strategyNode.
//    * @param[in] setting		The setting string, i.e.
//    * "BoxLinearOptimizationOn" or "HPolytopeOptimizerCaching"
//    * @param[in] timestep		The time step. Can be either a rational
//    * or a double.
//    * @param[in] agg			The aggregation setting.
//    * @param[in] clustering 	The clustering precision. If it is -1,
//    * clustering option is off.
//    */
//   // template<carl::DisableIf<std::is_same<tNumber,double>> = carl::dummy>
//   // void addStrategyNode(const std::string& setting, const tNumber& timestep,
//   // const hypro::AGG_SETTING agg, const int clustering);
//   void addStrategyNode(const std::string &setting, const double timestep,
//                        const hypro::AGG_SETTING agg, const int clustering);

//   // When building the strategy is finished, get the strategy via this getter.
//   hypro::Strategy<State> getStrategy() const { return mStrategy; }
// };

// } // namespace hydra
