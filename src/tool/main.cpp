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

	// combine parsed settings and cli flags
	auto settings = hydra::processSettings( reachSettings, options );

	EVALUATE_BENCHMARK_RESULT( "Parsing" );

	// perform preprocessing
	START_BENCHMARK_OPERATION( "Preprocess" );
	auto preprocessingInformation = hydra::preprocessing::preprocess( automaton,
																	  options["decompose"].as<bool>(),
																	  options["clockCount"].as<std::size_t>() );
	STOP_BENCHMARK_OPERATION( "Preprocess" );

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
			std::vector<hypro::Point<Number>> vertices;
			// project composed set if decompositional analysis was used
			// todo: maybe add a postprocess function to do this
			if ( options["decompose"].as<bool>() ) {
				vertices = detail::projectOnDimensions( std::visit( hypro::genericConvertAndGetVisitor<HPolytope<Number>>(), segment.sets.getSet() ), plotSettings.plotDimensions[pic] ).vertices();
				// switch dimensions if necessary
				if ( plotSettings.plotDimensions[pic][0] > plotSettings.plotDimensions[pic][1] ) {
					vertices = reduceToDimensions<Number>( vertices, { 1, 0 } );
				}
			} else {
				vertices = reduceToDimensions<Number>( segment.sets.vertices(), plotSettings.plotDimensions[pic] );
			}
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