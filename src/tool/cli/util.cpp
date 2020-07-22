#include "util.h"

#include <hypro/types.h>

namespace hydra {

hypro::Settings processSettings( const hypro::ReachabilitySettings& parsedSettings, const boost::program_options::variables_map& cliOptions ) {
	// general settings
	hypro::Settings settings{};

	settings.jumpDepth = static_cast<size_t>( parsedSettings.jumpDepth );
	settings.localTimeHorizon = cliOptions.count( "timehorizon" )
									  ? cliOptions["timehorizon"].as<mpq_class>()
									  : parsedSettings.timeBound;

	// plotting
	hypro::PlottingSettings plotting{};
	if ( !cliOptions.count( "skipplot" ) or !cliOptions["skipplot"].as<bool>() ) {
		std::string fileName = cliOptions.count( "plotoutput" ) ? cliOptions["plotoutput"].as<std::string>() : parsedSettings.fileName;

		plotting.plotDimensions = parsedSettings.plotDimensions;
		plotting.plotFileNames = std::vector<std::string>( plotting.plotDimensions.size(), fileName );
		plotting.plottingFileType = cliOptions.count( "plotoutputformat" ) ? cliOptions["plotoutputformat"].as<hypro::PLOTTYPE>() : +hypro::PLOTTYPE::nset;
	}
	settings.plotting = plotting;

	// strategy
	hypro::AnalysisParameters parameters{};

	parameters.timeStep = cliOptions.count( "delta" )
								? cliOptions["delta"].as<mpq_class>()
								: parsedSettings.timeStep;
	parameters.aggregation = cliOptions.count( "aggregation" ) ? cliOptions["aggregation"].as<hypro::AGG_SETTING>() : +hypro::AGG_SETTING::MODEL;
	parameters.clustering = cliOptions.count( "clustering" ) ? cliOptions["clustering"].as<int>() : parsedSettings.clustering;
	parameters.representation_type = cliOptions["representation"].as<hypro::representation_name>();
	parameters.representation_setting = hypro::stringToSetting( cliOptions["setting"].as<std::string>() );

	settings.strategy = { parameters };

	return settings;
}

}  // namespace hydra