#include "cli.h"

namespace hydra {

boost::program_options::variables_map handleCMDArguments( int argc,
														  const char **argv ) {
	namespace po = boost::program_options;
	po::variables_map vm;
	// clang-format off
	po::options_description options( "Allowed Parameters" );
	options.add_options()
		( "help,h", "Shows this help message" )
		( "plotoutput,po", po::value<std::string>(), "Plotoutput file path." )
		( "plotoutputformat,pof", po::value<std::string>(), "Plotoutput format - allowed are 'tex' and 'gnuplot'." )
		( "jobs,j", po::value<unsigned>()->default_value( 1 ), "<number> of jobs/threads to be used in parallel. Default is 1." )
		( "model,m", po::value<std::string>()->required(), "<path> to model file." )
		("representation,r", po::value<std::string>(), "representation to be used initially. Valid options are box, support_function, zonotope, polytope_h, polytope_v")
    	( "setting", po::value<std::string>(), "the setting to use for the representation")
		( "skipplot", po::bool_switch(), "skips plotting step" )
		( "noTimingInformation", po::bool_switch(), "do not collect any timing information during refinement" )
		( "noBadStateTimingInformation", po::bool_switch(), "do not collect bad state timing information during refinement" )
		( "noInvariantTimingInformation", po::bool_switch(), "do not collect invariant timing information during refinement" )
		( "noTransitionTimingInformation", po::bool_switch(), "do not collect transition timing information during refinement" )
		( "decider", po::bool_switch(), "Use decision entity to decide on future representation/handlers to use based on the current state to allow for optimized computations." )
		( "decompose", po::bool_switch(), "Decompose automaton into syntactically independent subspaces." )
		( "onlyGlobalQueues", po::bool_switch(), "use only global queues for tasks instead of intermediate local queues." )
		( "queueBalangingRatio,q", po::value<double>()->default_value( 1.0 ), "ratio of tasks which get pushed to a global queue from a local queue. Has no effect if onlyGlobalQueues is enabled." )
		( "strategy,s", po::value<std::string>(), "choose reachability strategy. Valid options are tacas18_1, tacas18_2, tacas18_3." )
		( "delta,d", po::value<mpq_class>(), "choose time step size (rational, i.e., 1/100). Overrides settings in the input file." )
    	( "timehorizon,t", po::value<mpq_class>(), "choose *local* timehorizon (rational, i.e., 1/100). Overrides settings in the input file." )
		( "clustering,c", po::value<int>(), "Select clustering option, -1=off, 0=all, i=max. number of clustered segments. Overrides settings in the input file." )
		// ( "customStrategy", po::bool_switch(), "Enters strategy building mode. Choose a representation, and customize its settings and different reachability settings." )
		( "snode,sn", po::value<std::vector<std::string>>()->multitoken(), "Adds a custom strategy node." );

	// clang-format on
	try {
		// A list of all snodes options, which all have a vector of parameters. Is
		// only used with the --snode option
		std::vector<std::vector<std::string>> snodes;

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
			// Parse, then scan for all snode entries, then store
			po::parsed_options parsedOptions =
				  po::command_line_parser( argc, argv ).options( options ).run();
			for ( const po::option &o : parsedOptions.options ) {
				if ( o.string_key == "snode" ) {
					snodes.push_back( o.value );
				}
			}
			po::store( parsedOptions, vm );
		}

		// set settings in settingsProvider
		hypro::SettingsProvider<State> &sProvider =
			  hypro::SettingsProvider<State>::getInstance();

		if ( vm.count( "help" ) || argc == 1 ) {
			COUT( options << std::endl );
			exit( 0 );
		}

		if ( vm.count( "jobs" ) ) {
			if ( vm["jobs"].as<unsigned>() == 0 ) {
				CERR( "You can not use 0 worker threads!\n" );
				exit( 0 );
			} else {
				sProvider.setWorkerThreadCount( vm["jobs"].as<unsigned>() );
			}
		}

		if ( vm["queueBalangingRatio"].as<double>() < 0.0 ||
			 vm["queueBalangingRatio"].as<double>() > 1.0 ) {
			CERR( "Please chose a value between 0 and 1.\n" );
			exit( 1 );
		}

		if ( vm["decompose"].as<bool>() ) {
			sProvider.setDecomposeAutomaton( true );
		}
		if ( vm["decider"].as<bool>() ) {
			sProvider.setUseDecider( true );
		}

		// If we have at least two of the three strategy options "strategy",
		// "customstrategy" or "snode", then throw error
		// if ((vm["customStrategy"].as<bool>() &&
		//      (vm.count("strategy") >= 1 || vm.count("snode") >= 1)) ||
		//     (vm.count("strategy") >= 1 && vm.count("snode") >= 1)) {
		//   CERR("You can only choose one of the three options --customstrategy, "
		//        "--strategy or --snode.\n");
		//   exit(1);
		// }

		/*
    if (vm["customStrategy"].as<bool>()) {
      DynamicStrategyBuilder d;
      d.startGui();
      hypro::SettingsProvider<State>::getInstance().setStrategy(
              d.getStrategy());
    }
    */

		/*
		if ( vm.count( "delta" ) != 0 ) {
			double tmpDelta = carl::toDouble( vm["delta"].as<mpq_class>() );
			std::cout << "Set delta to " << tmpDelta << std::endl;
		}
    */

		if ( vm.count( "strategy" ) >= 1 ) {
			if ( vm.count( "strategy" ) == 1 ) {
				hypro::SettingsProvider<State>::getInstance().setStrategy(
					  hydra::getStrategyFromName( vm["strategy"].as<std::string>() ) );
			} else {
				CERR( "You can not have more than one strategy!\n" );
				exit( 1 );
			}
		}

		/*
		if (vm.count("snode") >= 1) {
			DynamicStrategyBuilder d(snodes);
			hypro::SettingsProvider<State>::getInstance().setStrategy(d.getStrategy());
		}
		*/
	} catch ( std::exception &e ) {
		CERR( e.what() );
		COUT( options << std::endl );
		exit( 1 );
	}

	return vm;
}

}  // namespace hydra