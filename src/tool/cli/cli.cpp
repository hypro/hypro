#include "cli.h"

#include "../typedefs.h"

#include <hypro/types.h>
#include <hypro/util/logging/Logger.h>
#include <hypro/util/type_handling/representation_enums.h>

namespace hydra {

boost::program_options::variables_map handleCMDArguments( int argc, const char** argv ) {
	namespace po = boost::program_options;
	po::variables_map vm;
	// clang-format off
	po::options_description options( "Allowed Parameters" );
	options.add_options()
		( "help,h", "Shows this help message" )
		// general settings
			( "model,m", po::value<std::string>()->required(), "<path> to model file." )
			( "timehorizon,t", po::value<mpq_class>(), "choose *local* timehorizon (rational, i.e., 1/100). Overrides settings in the input file." )
		// analysis parameters aka strategy node
			( "delta,d", po::value<mpq_class>(), "choose time step size (rational, i.e., 1/100). Overrides settings in the input file." )
			( "aggregation,a", po::value<hypro::AGG_SETTING>(), "the aggregation setting to use. MODEL, AGG or NO_AGG." )
			( "clustering,c", po::value<int>(), "Select clustering option, -1=off, 0=all, i=max. number of clustered segments. Overrides settings in the input file." )
			( "representation,r", po::value<hypro::representation_name>(), "representation to be used initially. Valid options are box, support_function, zonotope, polytope_h, polytope_v")
			( "setting,s", po::value<std::string>(), "the setting to use for the representation")
		// plotting
			( "plotoutput", po::value<std::string>(), "Plotoutput file path." )
			( "plotoutputformat", po::value<hypro::PLOTTYPE>()->default_value( hypro::PLOTTYPE::png ), "Plotoutput format - allowed are 'pdf','png','eps,'gen', and 'tex'." )
			( "skipplot", po::bool_switch(), "skips plotting step" )
		// multithreading
			( "jobs,j", po::value<unsigned>()->default_value( 1 ), "<number> of jobs/threads to be used in parallel. Default is 1." )
		// preprocessing
			( "decider", po::bool_switch(), "Use decision entity to decide on future representation/handlers to use based on the current state to allow for optimized computations." )
			( "decompose", po::bool_switch(), "Decompose automaton into syntactically independent subspaces." );
		// ( "configuration", po::value<std::string>(), "Specify a file to load options from. Command line overwrites them." )

	// clang-format on
	try {
		if ( argc == 2 ) {
			COUT( "Trying to read options from file " << argv[1] << "..."
													  << std::endl );
			std::ifstream file( argv[1] );
			if ( !file.is_open() ) {
				CERR( "File does not exist.\n" );
				exit( 1 );
			}
			po::store( po::parse_config_file( file, options ), vm );
		} else {
			// parse then store
			po::parsed_options parsedOptions =
				  po::command_line_parser( argc, argv ).options( options ).run();
			po::store( parsedOptions, vm );
		}

		if ( vm.count( "help" ) || argc == 1 ) {
			COUT( options << std::endl );
			exit( 0 );
		}

	} catch ( std::exception& e ) {
		CERR( e.what() << std::endl );
		COUT( options << std::endl );
		exit( 1 );
	}

	return vm;
}

}  // namespace hydra