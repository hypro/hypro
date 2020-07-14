#include "../hypro/datastructures/reachability/Settings.h"
#include "../hypro/datastructures/reachability/SettingsProvider.h"
#include "../hypro/parser/antlr4-flowstar/ParserWrapper.h"
#include "../hypro/types.h"
#include "../hypro/util/logging/Logger.h"
#include "../hypro/util/type_handling/plottype_enums.h"
#include "cli/cli.h"
#include "preprocessing/preprocessing.h"
#include "reachability/analysis.h"
#include "typedefs.h"

using namespace hydra;
using namespace hypro;


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

	hypro::PLOTTYPE pltType = hypro::PLOTTYPE::pdf;
	if ( options.count( "skipplot" ) and options["skipplot"].as<bool>() ) {
		std::cout << "Skip plotting." << std::endl;
		reachSettings.plotDimensions.clear();
	} else {
		pltType = hypro::plotting::outputFormat( options["plotoutputformat"].as<std::string>() );
	}

	if ( options.count( "plotoutput" ) ) {
		reachSettings.fileName = options["plotoutput"].as<std::string>();
	}

	hypro::representation_name representation =
		  hypro::representation_name::_from_string( options["representation"].as<std::string>().c_str() );

	// create strategy
	hypro::Settings settings{{{timeStep, hypro::AGG_SETTING::MODEL, -1, representation,
							   hypro::stringToSetting( options["setting"].as<std::string>() )}},
							 reachSettings.jumpDepth,
							 timehorizon,
							 {reachSettings.plotDimensions},
							 {std::vector<std::string>( {reachSettings.plotDimensions.size(), reachSettings.fileName} )},
							 {pltType}};

	EVALUATE_BENCHMARK_RESULT( Parsing );

	// run reachability analysis
	auto result = hydra::reachability::analyze( automaton, settings );

	EVALUATE_BENCHMARK_RESULT( Verification );

	// call to plotting.
	START_BENCHMARK_OPERATION( Plotting );

	auto& plt = Plotter<Number>::getInstance();
	for ( std::size_t pic = 0; pic < settings.plotDimensions.size(); ++pic ) {
		std::cout << "Prepare plot " << pic + 1 << "/" << settings.plotDimensions.size() << "." << std::endl;
		plt.setFilename( settings.plotFileNames[pic] );
		std::size_t segmentCount = 0;

		for ( const auto& segment : result.plotData ) {
			std::cout << "\r" << segmentCount++ << "/" << result.plotData.size() << "..." << std::flush;
			plt.addObject( segment.sets.project( settings.plotDimensions[pic] ).vertices() );
		}

		plt.plot2d( settings.plottingFileType );	 // writes to .plt file for pdf creation
	}
	EVALUATE_BENCHMARK_RESULT( Plotting );

	PRINT_STATS();

	return 0;
}