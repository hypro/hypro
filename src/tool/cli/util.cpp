#include "util.h"

namespace hydra {

hypro::Settings processSettings( const hypro::ReachabilitySettings& parsedSettings, const boost::program_options::variables_map& cliOptions ) {
	// determine time step size
	mpq_class timeStep = cliOptions.count( "delta" )
							   ? cliOptions["delta"].as<mpq_class>()
							   : parsedSettings.timeStep;
	// determine time horizon
	mpq_class timehorizon = cliOptions.count( "timehorizon" )
								  ? cliOptions["timehorizon"].as<mpq_class>()
								  : parsedSettings.timeBound;
	// determine plot output file type
	hypro::PLOTTYPE pltType = hypro::PLOTTYPE::pdf;
	std::vector<std::vector<std::size_t>> plotDimensions;
	if ( cliOptions.count( "skipplot" ) and cliOptions["skipplot"].as<bool>() ) {
	} else {
		pltType = hypro::plotting::outputFormat( cliOptions["plotoutputformat"].as<std::string>() );
		plotDimensions = parsedSettings.plotDimensions;
	}

	std::string fileName = parsedSettings.fileName;
	if ( cliOptions.count( "plotoutput" ) ) {
		fileName = cliOptions["plotoutput"].as<std::string>();
	}
	// detect representation type
	hypro::representation_name representation =
		  hypro::representation_name::_from_string( cliOptions["representation"].as<std::string>().c_str() );

	// if strategy has been passed, use this
	std::vector<hypro::AnalysisParameters> strategy{ { timeStep, hypro::AGG_SETTING::MODEL, -1, representation,
													   hypro::stringToSetting( cliOptions["setting"].as<std::string>() ) } };
	if ( cliOptions.count( "strategy" ) ) {
		strategy = hydra::getStrategyFromName( cliOptions["strategy"].as<std::string>() );
	}

	// create strategy inside settings
	hypro::Settings settings{ strategy,
							  parsedSettings.jumpDepth,
							  timehorizon,
							  plotDimensions,
							  { std::vector<std::string>( { parsedSettings.plotDimensions.size(), fileName } ) },
							  pltType };

	return settings;
}

}  // namespace hydra