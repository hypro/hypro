#include "cli/cli.h"
#include "cli/util.h"
#include "preprocessing/preprocessing.h"
#include "reachability/analysis.h"
#include "typedefs.h"

#include <hypro/datastructures/reachability/PreprocessingInformation.h>
#include <hypro/datastructures/reachability/Settings.h>
#include <hypro/datastructures/reachability/SettingsProvider.h>
#include <hypro/parser/antlr4-flowstar/ParserWrapper.h>
#include <hypro/types.h>
#include <hypro/util/logging/Logger.h>
#include <hypro/util/type_handling/plottype_enums.h>

int main( int argc, char const *argv[] ) {
	// parse command line arguments
	START_BENCHMARK_OPERATION( Parsing );
	auto options = hydra::handleCMDArguments( argc, argv );

	// parse model file
	COUT( "Passed model file: " << options["model"].as<std::string>() << std::endl );
	auto [automaton, reachSettings] = hypro::parseFlowstarFile<hydra::Number>(
		  options["model"].as<std::string>() );

	// perform preprocessing
	auto preprocessingInformation = hydra::preprocessing::preprocess( automaton,
																	  reachSettings );

	// combine parsed settings and cli flags
	auto settings = hydra::processSettings( reachSettings, options );

	EVALUATE_BENCHMARK_RESULT( Parsing );

	// run reachability analysis
	hydra::reachability::analyze( automaton, settings, preprocessingInformation );

	PRINT_STATS();

	return 0;
}