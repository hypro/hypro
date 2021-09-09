#include "cli/cli.h"
#include "cli/settingsProcessing.h"
#include "preprocessing/preprocessing.h"
#include "reachability/analysis.h"

#include <hypro/datastructures/HybridAutomaton/StateUtil.h>
#include <hypro/parser/antlr4-flowstar/ParserWrapper.h>
#include <hypro/util/logging/Logger.h>
#include <hypro/util/plotting/Plotter.h>

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
	auto result = hydra::reachability::analyze( automaton, settings, preprocessingInformation );

	// call to plotting.
	START_BENCHMARK_OPERATION( "Plotting" );

	auto const& plotSettings = settings.plotting();
	auto& plt = Plotter<Number>::getInstance();
	for ( std::size_t pic = 0; pic < plotSettings.plotDimensions.size(); ++pic ) {
		assert( plotSettings.plotDimensions[pic].size() == 2 );
		std::cout << "Prepare plot "
				  << "(" << pic + 1 << "/" << plotSettings.plotDimensions.size() << ") for dimensions " << plotSettings.plotDimensions[pic].front() << ", " << plotSettings.plotDimensions[pic].back() << "." << std::endl;
		plt.setFilename( plotSettings.plotFileNames[pic] );
		std::size_t segmentCount = 0;

		for ( auto& segment : result.plotData ) {
			if ( segmentCount % 100 == 0 ) std::cout << "\r" << segmentCount << "/" << result.plotData.size() << "..." << std::flush;
			segmentCount += 1;
			auto vertices = segment.sets.projectOn( plotSettings.plotDimensions[pic] ).vertices();
			if ( vertices.front().dimension() != 2 ) {
				INFO( "hypro.plotter", "broken vertices:\n"
											 << vertices )
				INFO( "hypro.plotter", "from:\n"
											 << printSet( segment.sets ) );
				continue;
			}
			plt.addObject( vertices );
		}
		std::cout << "\r" << segmentCount << "/" << result.plotData.size() << "..."
				  << "\n";

		plt.plot2d( plotSettings.plottingFileType );  // writes to .plt file for pdf creation
	}
	EVALUATE_BENCHMARK_RESULT( "Plotting" );

	PRINT_STATS();

	return 0;
}