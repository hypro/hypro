#include "settingsProcessing.h"

#include <hypro/types.h>

namespace hydra {

hypro::AnalysisParameters constructSingleNodeStrategy( const hypro::ReachabilitySettings& parsedSettings, const boost::program_options::variables_map& cliOptions ) {
	hypro::AnalysisParameters parameters{};

	parameters.timeStep = cliOptions.count( "delta" ) ? cliOptions["delta"].as<mpq_class>() : parsedSettings.timeStep;
	parameters.aggregation = cliOptions.count( "aggregation" ) ? cliOptions["aggregation"].as<hypro::AGG_SETTING>() : +hypro::AGG_SETTING::MODEL;
	parameters.clustering = cliOptions.count( "clustering" ) ? cliOptions["clustering"].as<int>() : parsedSettings.clustering;
	parameters.representation_type = cliOptions["representation"].as<hypro::representation_name>();
	parameters.representation_setting = hypro::stringToSetting( cliOptions["setting"].as<std::string>() );

	return parameters;
}

std::vector<hypro::AnalysisParameters> constructFullStrategy( const hypro::ReachabilitySettings&, const boost::program_options::variables_map& cliOptions ) {
	std::vector<hypro::AnalysisParameters> parameters{};

	size_t snodeCount = cliOptions["strategy.delta"].as<std::vector<mpq_class>>().size();
	for ( size_t i = 0; i < snodeCount; ++i ) {
		parameters.push_back(
			  hypro::AnalysisParameters{
					/*.timeStep =*/cliOptions["strategy.delta"].as<std::vector<mpq_class>>().at( i ),
					/*.aggregation =*/cliOptions["strategy.aggregation"].as<std::vector<hypro::AGG_SETTING>>().at( i ),
					/*.clustering =*/cliOptions["strategy.clustering"].as<std::vector<int>>().at( i ),
					/*.representation_type =*/cliOptions["strategy.representation"].as<std::vector<hypro::representation_name>>().at( i ),
					/*.representation_setting =*/hypro::stringToSetting( cliOptions["strategy.setting"].as<std::vector<std::string>>().at( i ) ) } );
	}
	// designated initialization is C99 or c++20 so we can't use it

	return parameters;
}

hypro::Settings processSettings( const hypro::ReachabilitySettings& parsedSettings, const boost::program_options::variables_map& cliOptions ) {
	// general settings
	hypro::FixedAnalysisParameters fixedParameters{};

	fixedParameters.jumpDepth = static_cast<size_t>( parsedSettings.jumpDepth );
	fixedParameters.localTimeHorizon = cliOptions.count( "timehorizon" )
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

	// strategy
	if ( cliOptions.count( "strategy_file" ) ) {
		return hypro::Settings{ plotting, fixedParameters, constructFullStrategy( parsedSettings, cliOptions ) };
	} else {
		return hypro::Settings{ plotting, fixedParameters, { constructSingleNodeStrategy( parsedSettings, cliOptions ) } };
	}
}

}  // namespace hydra