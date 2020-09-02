#include "cli/cli.h"
#include "cli/settingsProcessing.h"
#include "preprocessing/preprocessing.h"
#include "reachability/analysis.h"
#include "typedefs.h"

#include <hypro/datastructures/reachability/PreprocessingInformation.h>
#include <hypro/datastructures/reachability/Settings.h>
#include <hypro/parser/antlr4-flowstar/ParserWrapper.h>
#include <hypro/types.h>
#include <hypro/util/logging/Logger.h>
#include <hypro/util/type_handling/plottype_enums.h>

using namespace hydra;
using namespace hypro;

int main( int argc, char const* argv[] ) {
	// parse command line arguments
	START_BENCHMARK_OPERATION( "Parsing" );
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

	EVALUATE_BENCHMARK_RESULT( "Parsing" );

	// run reachability analysis
	START_BENCHMARK_OPERATION( "Verification" );
	auto result = hydra::reachability::analyze( automaton, settings, preprocessingInformation );

	EVALUATE_BENCHMARK_RESULT( "Verification" );

	// call to plotting.
	START_BENCHMARK_OPERATION( "Plotting" );

	auto const& plotSettings = settings.plotting();
	auto& plt = Plotter<Number>::getInstance();
	for ( std::size_t pic = 0; pic < plotSettings.plotDimensions.size(); ++pic ) {
		std::cout << "Prepare plot " << pic + 1 << "/" << plotSettings.plotDimensions.size() << "." << std::endl;
		plt.setFilename( plotSettings.plotFileNames[pic] );
		std::size_t segmentCount = 0;

		for ( const auto& segment : result.plotData ) {
			std::cout << "\r" << segmentCount++ << "/" << result.plotData.size() << "..." << std::flush;
			plt.addObject( segment.sets.projectOn( plotSettings.plotDimensions[pic] ).vertices() );
		}

		plt.plot2d( plotSettings.plottingFileType );  // writes to .plt file for pdf creation
	}
	EVALUATE_BENCHMARK_RESULT( "Plotting" );

	PRINT_STATS();

	return 0;
}