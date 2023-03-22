/*
 * Copyright (c) 2021-2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "cli/cli.h"

#include "typedefs.h"

#include <hypro/types.h>
#include <hypro/util/logging/Logger.h>
#include <hypro/util/type_handling/representation_enums.h>

namespace hydra {

boost::program_options::variables_map handleCMDArguments( int argc, const char** argv ) {
	namespace po = boost::program_options;
	po::variables_map vm;
	// clang-format off
	po::options_description general( "General options for the whole analysis." );
	general.add_options()
			( "help,h", "Shows this help message" )
			( "model,m", po::value<std::string>()->required(), "<path> to model file." )
			( "timehorizon,t", po::value<mpq_class>(), "choose *local* timehorizon (rational, i.e., 1/100). Overrides settings in the input file." )
			( "strategy_file", po::value<std::string>(), "specify a file to load options from. Command line overwrites them." )
			( "urgency_cegar", po::bool_switch(), "Use CEGAR analysis for urgent transitions" )
			( "silent", po::bool_switch(), "if set, nothing is output to stdout" );

	po::options_description strategy ( "The options of a strategy. Specifying lists results in multiple strategy nodes." );
	strategy.add_options()
			( "strategy.delta,d", po::value<std::vector<mpq_class>>()->multitoken()->required(), "choose time step size (rational, i.e., 1/100). Overrides settings in the input file." )
			( "strategy.aggregation,a", po::value<std::vector<hypro::AGG_SETTING>>()->multitoken()->required(), "the aggregation setting to use. MODEL, AGG or NO_AGG." )
			( "strategy.clustering,c", po::value<std::vector<int>>()->multitoken()->required(), "select clustering option, -1=off, 0=all, i=max. number of clustered segments. Overrides settings in the input file." )
			( "strategy.representation,r", po::value<std::vector<hypro::representation_name>>()->multitoken()->required(), "representation to be used initially. Valid options are box, support_function, zonotope, polytope_h, polytope_v")
			( "strategy.setting,s", po::value<std::vector<std::string>>()->multitoken()->required(), "the setting to use for the representation");

	po::options_description analysisParameters( "Analysis parameters." );
	analysisParameters.add_options()
			( "delta,d", po::value<mpq_class>(), "choose time step size (rational, i.e., 1/100). Overrides settings in the input file." )
			( "aggregation,a", po::value<hypro::AGG_SETTING>(), "the aggregation setting to use. MODEL, AGG or NO_AGG." )
			( "clustering,c", po::value<int>(), "select clustering option, -1=off, 0=all, i=max. number of clustered segments. Overrides settings in the input file." )
			( "representation,r", po::value<hypro::representation_name>(), "representation to be used initially. Valid options are box, support_function, zonotope, polytope_h, polytope_v")
			( "setting,s", po::value<std::string>(), "the setting to use for the representation");

	po::options_description urgencyCEGARSettings( "Urgency CEGAR settings." );
	urgencyCEGARSettings.add_options()
			( "refinementLevels", po::value<std::vector<hypro::UrgencyRefinementLevel>>()->multitoken()->default_value({}), "the refinement levels for urgency cegar (selction of FULL, CUTOFF and SETDIFF)")
			( "refineHalfspaces", po::bool_switch(), "always refine urgent halfspaces" )
			( "pruneUrgentSegments", po::bool_switch(), "remove segments contained in urgent guards")
			( "aggregatedRefine", po::bool_switch(), "aggregate initial segments for path computation when finding refinement transitions")
			( "heuristic", po::value<hypro::UrgencyRefinementHeuristic>(), "used heuristic for choosing refinement transition. NONE, VOLUME, CONSTRAINT_COUNT or COUNT");

	po::options_description plotting( "Plotting options." );
	plotting.add_options()
			( "plotoutput", po::value<std::string>(), "plotoutput file path." )
			( "plotoutputformat", po::value<hypro::PLOTTYPE>()->default_value( hypro::PLOTTYPE::png ), "plotoutput format - allowed are 'pdf','png','eps,'gen', and 'tex'." )
			( "skipplot", po::bool_switch(), "skips plotting step" );

	po::options_description multithreading( "Multithreading options" );
	multithreading.add_options()
			( "jobs,j", po::value<unsigned>()->default_value( 1 ), "<number> of jobs/threads to be used in parallel. Default is 1." );

	po::options_description preprocessing( "Preprocessing options" );
	preprocessing.add_options()
			( "decider", po::bool_switch(), "use decision entity to decide on future representation/handlers to use based on the current state to allow for optimized computations." )
			( "decompose", po::bool_switch(), "decompose automaton into syntactically independent subspaces." )
			( "clockCount", po::value<std::size_t>()->default_value( 0 ), "number of clocks to use in decompositional analysis. Default is 0." )
			( "singularSubspaceSize", po::value<std::size_t>()->default_value( 1 ), "maximal number of variables in singular subspace. Default is 1, use -1 for unlimited.");

	po::options_description allOptions("Allowed options");
	allOptions.add(general).add(analysisParameters).add(plotting).add(urgencyCEGARSettings).add(preprocessing);

	// clang-format on
	try {
		po::store( po::parse_command_line( argc, argv, allOptions ), vm );

		if ( vm.count( "strategy_file" ) ) {
			po::store( po::parse_config_file<char>( vm["strategy_file"].as<std::string>().c_str(), strategy ), vm );
		}

		if ( vm.count( "strategy_file" ) ) {
			size_t snodeCount = vm["strategy.delta"].as<std::vector<mpq_class>>().size();
			if ( !( vm["strategy.aggregation"].as<std::vector<hypro::AGG_SETTING>>().size() == snodeCount &&
					vm["strategy.clustering"].as<std::vector<int>>().size() == snodeCount &&
					vm["strategy.representation"].as<std::vector<hypro::representation_name>>().size() == snodeCount &&
					vm["strategy.setting"].as<std::vector<std::string>>().size() == snodeCount ) ) {
				COUT( "All options must be specified the same number of times to construct a strategy" );
				exit( 0 );
			}
		}

		if ( vm.count( "help" ) || argc == 1 ) {
			COUT( allOptions << std::endl );
			exit( 0 );
		}

	} catch ( po::error& e ) {
		CERR( e.what() << std::endl );
		COUT( allOptions << std::endl );
		exit( 1 );
	}

	return vm;
}

}  // namespace hydra
