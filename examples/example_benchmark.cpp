/**
 * \example example_benchmark.cpp
 * This is an example file holding a fully functional reachability analysis
 * algorithm implementation with benchmarking features such as time
 * measurements.
 */

#include "algorithms/reachability/Reach.h"
#include "datastructures/HybridAutomaton/HybridAutomaton.h"
//#include "datastructures/HybridAutomaton/LocationManager.h"
#include "algorithms/reachability/Reach.h"
#include "parser/antlr4-flowstar/ParserWrapper.h"
#include "representations/GeometricObjectBase.h"

#include <signal.h>
#include <sys/wait.h>
#ifdef HYPRO_USE_LACE
#include <lace.h>
#endif
#define PLOT_FLOWPIPE

template <typename Number, typename Representation>
static void computeReachableStates( const std::string& filename ) {
	using clock = std::chrono::high_resolution_clock;
	using timeunit = std::chrono::duration<long long unsigned, std::micro>;
	std::string csvString;
	// std::cout << "Filename: " << filename << std::endl;
	std::size_t numberRuns = 1;
	std::vector<std::chrono::duration<double, std::milli>> runtimes( numberRuns );
	std::chrono::duration<double, std::milli> summedTime( 0.0 );
	clock::time_point startParsing = clock::now();
	std::pair<hypro::HybridAutomaton<Number>, hypro::ReachabilitySettings> ha =
		  std::move( hypro::parseFlowstarFile<Number>( filename ) );
	std::chrono::duration<double, std::milli> parseTime =
		  std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(
				clock::now() - startParsing );
	std::vector<std::pair<unsigned, hypro::reachability::flowpipe_t>> flowpipes;
	// std::cout << "Parse time is " << parseTime.count() << std::endl;

	for ( std::size_t run = 0; run < numberRuns; ++run ) {
		clock::time_point start = clock::now();
		hypro::reachability::Reach<Number> reacher( ha.first, ha.second );
		reacher.setRepresentationType( Representation::type() );
		flowpipes = reacher.computeForwardReachability();
		runtimes.push_back(
			  std::chrono::duration_cast<timeunit>( clock::now() - start ) );
		summedTime +=
			  std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(
					clock::now() - start ) /
			  ( numberRuns );
		// std::cout << "Summed time: " <<
		// std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(
		// summedTime ).count() << std::endl;
		std::cout << "Run finished in "
				  << std::chrono::duration_cast<
						   std::chrono::duration<double, std::milli>>( clock::now() -
																	   start )
						   .count()
				  << " ms." << std::endl;
		// std::cout << "Run finished in " <<
		// std::chrono::duration_cast<std::chrono::duration<double, std::ratio<60>>>(
		// clock::now() - start ).count() << " minutes." << std::endl;
		PRINT_STATS()
		RESET_STATS()
	}
	std::cout << ha.second << std::endl;
	double runtime =
		  std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(
				summedTime )
				.count() +
		  std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(
				parseTime )
				.count();
	std::cout
		  << "Finished computation of reachable states: "
		  << std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(
				   summedTime )
						 .count() +
				   std::chrono::duration_cast<
						 std::chrono::duration<double, std::milli>>( parseTime )
						 .count()
		  << " ms" << std::endl;
	std::time_t end_time =
		  std::chrono::system_clock::to_time_t( std::chrono::system_clock::now() );
	std::tm tm = *std::localtime( &end_time );
	std::stringstream str;
	str << std::put_time( &tm, "%F %T" );
	csvString += str.str();

#ifdef PLOT_FLOWPIPE
	clock::time_point startPlotting = clock::now();

	hypro::Plotter<Number>& plotter = hypro::Plotter<Number>::getInstance();
	std::string extendedFilename = ha.second.fileName;
	csvString +=
		  "," + extendedFilename + "," + std::to_string( ha.second.jumpDepth ) + "," +
		  std::to_string( carl::convert<Number, double>( ha.second.timeStep ) );
	switch ( Representation::type() ) {
		case hypro::representation_name::zonotope: {
			extendedFilename += "_zonotope";
			csvString += ",zonotope";
			break;
		}
		case hypro::representation_name::support_function: {
			extendedFilename += "_supportFunction";
			csvString += ",supportFunction";
			break;
		}
		case hypro::representation_name::polytope_v: {
			extendedFilename += "_vpoly";
			csvString += ",vpoly";
			break;
		}
		case hypro::representation_name::polytope_h: {
			extendedFilename += "_hpoly";
			csvString += ",hpoly";
			break;
		}
#ifdef USE_PPL
		case hypro::representation_name::ppl_polytope: {
			extendedFilename += "_PPLpoly";
			csvString += ",pplPoly";
			break;
		}
#endif
		case hypro::representation_name::box: {
			extendedFilename += "_box";
			csvString += ",box";
			break;
		}
		default:
			extendedFilename += "_unknownRep";
			csvString += ",unknown";
	}

	extendedFilename += "_" + hypro::typeName<Number>().get();
	csvString += "," + hypro::typeName<Number>().get();
	extendedFilename += "_glpk";
	csvString += ",glpk";
#ifdef HYPRO_USE_SMTRAT
	extendedFilename += "_smtrat";
	csvString += ",smtrat";
#endif
#ifdef HYPRO_USE_Z3
	extendedFilename += "_z3";
	csvString += ",z3";
#endif
#if !defined HYPRO_USE_SMTRAT && !defined HYPRO_USE_Z3
	csvString += ",";
#endif

	csvString += "," + std::to_string( runtime ) + "\n";

	std::fstream resultFile;
	resultFile.open( "results.csv", std::fstream::app );
	resultFile << csvString;
	resultFile.close();

	std::cout << csvString << std::endl;

	// std::cout << "filename is " << extendedFilename << std::endl;
	plotter.setFilename( extendedFilename );
	std::vector<std::vector<std::size_t>> plottingDimensions =
		  ha.second.plotDimensions;
	plotter.rSettings().dimensions.first = plottingDimensions.front().front();
	plotter.rSettings().dimensions.second = plottingDimensions.front().back();
	plotter.rSettings().cummulative = false;

	// bad states plotting
	typename hypro::HybridAutomaton<Number>::locationConditionMap
		  badStateMapping = ha.first.getLocalBadStates();
	for ( const auto& state : badStateMapping ) {
		unsigned bs = plotter.addObject(
			  Representation( state.second.getMatrix(), state.second.getVector() )
					.vertices() );
		plotter.setObjectColor( bs, hypro::plotting::colors[hypro::plotting::red] );
	}

	// segments plotting
	for ( const auto& flowpipePair : flowpipes ) {
		// std::cout << "Plot flowpipe " << flowpipePair.first << std::endl;
		unsigned cnt = 0;
		for ( const auto& segment : flowpipePair.second ) {
			// std::cout << "Plot segment " << cnt << "/" <<
			// flowpipePair.second.size() << std::endl;
			unsigned tmp = plotter.addObject(
				  segment.projectOn( plottingDimensions.front() ).vertices() );
			plotter.setObjectColor(
				  tmp, hypro::plotting::colors[flowpipePair.first %
											   ( sizeof( hypro::plotting::colors ) /
												 sizeof( *hypro::plotting::colors ) )] );
			++cnt;
		}
	}

	// std::cout << "Use dimensions: " << plotter.settings().dimensions.first <<
	// ", " << plotter.settings().dimensions.second << std::endl;
	INFO( "hypro", "Write to file." );
	plotter.plot2d();
	plotter.plotGen();
	// plotter.plotTex();
	INFO( "hypro", "Finished plotting: " << std::chrono::duration_cast<timeunit>(
												  clock::now() - startPlotting )
														.count() /
												  1000.0
										 << " ms" );

#endif
}

int main( int argc, char** argv ) {
	int rep = 0;
	std::string filename = argv[1];
	if ( argc > 2 ) {
		char* p;
		rep = strtol( argv[2], &p, 10 );
	}

	using Number = double;

	switch ( rep ) {
#ifdef USE_PPL
		case 6: {
			using Representation = hypro::Polytope<Number>;
			computeReachableStates<Number, Representation>( filename );
			break;
		}
#endif
		case 5: {
			using Representation = hypro::Zonotope<Number>;
			computeReachableStates<Number, Representation>( filename );
			break;
		}
		case 4: {
			using Representation = hypro::SupportFunction<Number>;
			computeReachableStates<Number, Representation>( filename );
			break;
		}
		case 3: {
			using Representation = hypro::VPolytope<Number>;
			computeReachableStates<Number, Representation>( filename );
			break;
		}
		case 2: {
			using Representation = hypro::HPolytope<Number>;
			computeReachableStates<Number, Representation>( filename );
			break;
		}
		case 1: {
			using Representation = hypro::Box<Number>;
			computeReachableStates<Number, Representation>( filename );
			break;
		}
		default: {
			using Representation = hypro::Box<Number>;
			computeReachableStates<Number, Representation>( filename );
		}
	}
	exit( 0 );
}
