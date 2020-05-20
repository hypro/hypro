#include "../hypro/datastructures/reachability/Settings.h"
#include "../hypro/datastructures/reachability/SettingsProvider.h"
#include "../hypro/parser/antlr4-flowstar/ParserWrapper.h"
#include "../hypro/types.h"
#include "../hypro/util/logging/Logger.h"
#include "cli/cli.h"
#include "preprocessing/preprocessing.h"
#include "reachability/analysis.h"
#include "typedefs.h"

int main( int argc, char const *argv[] ) {
	// parse command line arguments
	START_BENCHMARK_OPERATION( Parsing );
	auto options = hydra::handleCMDArguments( argc, argv );

	// parse model file
	COUT( "Passed model file: " << options["model"].as<std::string>() << std::endl );
	auto [automaton, reachSettings] = hypro::parseFlowstarFile<hydra::Number>(
		  options["model"].as<std::string>() );

	// perform preprocessing
	hydra::preprocessing::preprocess( automaton,
									  reachSettings );

	mpq_class timeStep = options.count( "delta" )
							   ? options["delta"].as<mpq_class>()
							   : reachSettings.timeStep;

	mpq_class timehorizon = options.count( "timehorizon" )
								  ? options["timehorizon"].as<mpq_class>()
								  : reachSettings.timeBound;

	hypro::representation_name representation =
		  hypro::representation_name::_from_string( options["representation"].as<std::string>().c_str() );

	// create strategy
	hypro::Settings settings{{{timeStep, hypro::AGG_SETTING::MODEL, -1, representation,
							   hypro::stringToSetting( options["setting"].as<std::string>() )}},
							 reachSettings.jumpDepth,
							 timehorizon,
							 {reachSettings.plotDimensions},
							 {std::vector<std::string>( {reachSettings.plotDimensions.size(), reachSettings.fileName} )}};

	EVALUATE_BENCHMARK_RESULT( Parsing );

	// run reachability analysis
	hydra::reachability::analyze( automaton, settings );

	PRINT_STATS();

	return 0;
}