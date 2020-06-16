/**
 *
 */

#include "algorithms/reachability/Reach.h"
#include "datastructures/HybridAutomaton/HybridAutomaton.h"
#include "parser/antlr4-flowstar/ParserWrapper.h"
#include "representations/GeometricObjectBase.h"
#include "util/statistics/statistics.h"
#ifdef HYPRO_USE_LACE
#include <lace.h>
#endif
//#define PLOT_FLOWPIPE

template <typename Number, typename Representation>
static void computeReachableStates( const std::string &filename,
									const hypro::representation_name &type ) {
	using clock = std::chrono::high_resolution_clock;
	using timeunit = std::chrono::microseconds;
	clock::time_point start = clock::now();

	std::pair<hypro::HybridAutomaton<Number>, hypro::ReachabilitySettings> ha = std::move( hypro::parseFlowstarFile<Number>( filename ) );

	//#ifdef HYPRO_LOGGING
	// std::cout << "Parsed HybridAutomaton:\n" << ha.first << "Parsed
	// ReachabilitySettings:\n" << ha.second << std::endl; #endif

	hypro::reachability::Reach<Number, hypro::reachability::ReachSettings, hypro::State_t<Number>> reacher( ha.first, ha.second );
	reacher.setRepresentationType( type );
	// reacher.initQueue();
	std::vector<hypro::State_t<Number>> initialStates;
	for ( const auto &locConditionPair : ha.first.getInitialStates() ) {
		hypro::State_t<Number> initState =
			  hypro::State_t<Number>( locConditionPair.first );
		initState.setSet( Representation( locConditionPair.second.getMatrix(),
										  locConditionPair.second.getVector() ) );
		initialStates.emplace_back( std::move( initState ) );
	}
	reacher.setInitialStates( std::move( initialStates ) );

	std::cout << "Initiated queues" << std::endl;

	auto flowpipes = reacher.computeForwardReachability();

	std::cout
		  << "Finished computation of reachable states: "
		  << std::chrono::duration_cast<timeunit>( clock::now() - start ).count() /
				   1000.0
		  << " ms" << std::endl;

	if ( ha.second.plotDimensions.size() > 0 ) {
		clock::time_point startPlotting = clock::now();

		hypro::Plotter<Number> &plotter = hypro::Plotter<Number>::getInstance();
		std::string extendedFilename = ha.second.fileName;
		switch ( Representation::type() ) {
			case hypro::representation_name::polytope_t: {
				extendedFilename += "_tpoly";
				break;
			}
			case hypro::representation_name::ppl_polytope: {
				extendedFilename += "_pplpoly";
				break;
			}
			case hypro::representation_name::difference_bounds: {
				extendedFilename += "_differenceBounds";
				break;
			}
			case hypro::representation_name::zonotope: {
				extendedFilename += "_zonotope";
				break;
			}
			case hypro::representation_name::support_function: {
				extendedFilename += "_supportFunction";
				break;
			}
			case hypro::representation_name::polytope_v: {
				extendedFilename += "_vpoly";
				break;
			}
			case hypro::representation_name::polytope_h: {
				extendedFilename += "_hpoly";
				break;
			}
			case hypro::representation_name::box: {
				extendedFilename += "_box";
				break;
			}
			case hypro::representation_name::SFN: {
				extendedFilename += "_sfn";
				break;
			}
			default:
				extendedFilename += "_unknownRep";
		}
		std::cout << "filename is " << extendedFilename << std::endl;
		plotter.setFilename( extendedFilename );
		std::vector<std::size_t> plottingDimensions =
			  ha.second.plotDimensions.at( 0 );
		plotter.rSettings().dimensions.first = plottingDimensions.front();
		plotter.rSettings().dimensions.second = plottingDimensions.back();
		plotter.rSettings().cummulative = false;

		// bad states plotting
		typename hypro::HybridAutomaton<Number>::locationConditionMap
			  badStateMapping = ha.first.getLocalBadStates();
		for ( const auto &state : badStateMapping ) {
			unsigned bs = plotter.addObject(
				  Representation( state.second.getMatrix( 0 ), state.second.getVector( 0 ) )
						.vertices() );
			plotter.setObjectColor( bs, hypro::plotting::colors[hypro::plotting::red] );
		}

		// segments plotting
		for ( const auto &flowpipePair : flowpipes ) {
			std::cout << "Plot flowpipe " << flowpipePair.first << std::endl;
			unsigned cnt = 0;
			for ( const auto &segment : flowpipePair.second ) {
				std::cout << "Plot segment " << cnt << "/" << flowpipePair.second.size()
						  << std::endl;
				Representation seg = std::get<Representation>( segment.getSet( 0 ) );
				switch ( type ) {
					case hypro::representation_name::SFN: {
						unsigned tmp =
							  plotter.addObject( seg.project( plottingDimensions ).vertices() );
						plotter.setObjectColor(
							  tmp, hypro::plotting::colors[flowpipePair.first->getState().getLocation()->hash() %
														   ( sizeof( hypro::plotting::colors ) /
															 sizeof( *hypro::plotting::colors ) )] );
						break;
					}
					case hypro::representation_name::support_function: {
						unsigned tmp =
							  plotter.addObject( seg.project( plottingDimensions ).vertices() );
						plotter.setObjectColor(
							  tmp, hypro::plotting::colors[flowpipePair.first->getState().getLocation()->hash() %
														   ( sizeof( hypro::plotting::colors ) /
															 sizeof( *hypro::plotting::colors ) )] );
						break;
					}
					case hypro::representation_name::zonotope: {
						unsigned tmp =
							  plotter.addObject( seg.project( plottingDimensions ).vertices() );
						plotter.setObjectColor(
							  tmp, hypro::plotting::colors[flowpipePair.first->getState().getLocation()->hash() %
														   ( sizeof( hypro::plotting::colors ) /
															 sizeof( *hypro::plotting::colors ) )] );
						plotter.rSettings().dimensions.first = 0;
						plotter.rSettings().dimensions.second = 1;
						break;
					}
					case hypro::representation_name::box: {
						unsigned tmp =
							  plotter.addObject( seg.project( plottingDimensions ).vertices() );
						plotter.setObjectColor(
							  tmp, hypro::plotting::colors[flowpipePair.first->getState().getLocation()->hash() %
														   ( sizeof( hypro::plotting::colors ) /
															 sizeof( *hypro::plotting::colors ) )] );
						plotter.rSettings().dimensions.first = 0;
						plotter.rSettings().dimensions.second = 1;
						break;
					}
					default:
						unsigned tmp = plotter.addObject( seg.project( plottingDimensions ).vertices() );
						plotter.setObjectColor(
							  tmp, hypro::plotting::colors[flowpipePair.first->getState().getLocation()->hash() %
														   ( sizeof( hypro::plotting::colors ) /
															 sizeof( *hypro::plotting::colors ) )] );
				}
				++cnt;
			}
		}

		PRINT_STATS()

		std::cout << "Write to file." << std::endl;
		// std::cout << "Use dimensions: " << plotter.settings().dimensions.first <<
		// ", " << plotter.settings().dimensions.second << std::endl;
		plotter.plot2d();
		plotter.plotGen();
		plotter.plotTex();

		std::cout << "Finished plotting: "
				  << std::chrono::duration_cast<timeunit>( clock::now() -
														   startPlotting )
								 .count() /
						   1000.0
				  << " ms" << std::endl;
	}
}

int main( int argc, char **argv ) {
	int rep = 0;
	std::string filename = argv[1];
	if ( argc > 2 ) {
		char *p;
		rep = strtol( argv[2], &p, 10 );
	}

#ifdef USE_CLN_NUMBERS
	using Number = cln::cl_RA;
#else
	using Number = mpq_class;
	// using Number = double;
#endif

	switch ( rep ) {
		case 9: {
			using Representation = hypro::TemplatePolyhedron<Number>;
			std::cout << "Using a template polytope representation." << std::endl;
			computeReachableStates<Number, Representation>( filename, hypro::representation_name::polytope_t );
			break;
		}

		case 8: {
			using Representation = hypro::SupportFunctionNew<Number>;
			std::cout << "Using a generic support function representation."
					  << std::endl;
			computeReachableStates<Number, Representation>(
				  filename, hypro::representation_name::SFN );
			break;
		}

#ifdef HYPRO_USE_PPL
		case 7: {
			using Representation = hypro::Polytope<Number>;
			std::cout << "Using a ppl-polytope representation." << std::endl;
			computeReachableStates<Number, Representation>(
				  filename, hypro::representation_name::ppl_polytope );
			break;
		}
#endif

		case 6: {
			using Representation = hypro::DifferenceBounds<Number>;
			std::cout << "Using a difference bounds representation." << std::endl;
			computeReachableStates<Number, Representation>(
				  filename, hypro::representation_name::difference_bounds );
			break;
		}

		case 5: {
			using Representation = hypro::Zonotope<Number>;
			std::cout << "Using a zonotope representation." << std::endl;
			computeReachableStates<Number, Representation>(
				  filename, hypro::representation_name::zonotope );
			break;
		}

		case 4: {
			using Representation = hypro::SupportFunction<Number>;
			std::cout << "Using a support function representation." << std::endl;
			computeReachableStates<Number, Representation>(
				  filename, hypro::representation_name::support_function );
			break;
		}

		case 3: {
			using Representation = hypro::VPolytope<Number>;
			std::cout << "Using a v-polytope representation." << std::endl;
			computeReachableStates<Number, Representation>(
				  filename, hypro::representation_name::polytope_v );
			break;
		}
		case 2: {
			using Representation = hypro::HPolytope<Number>;
			std::cout << "Using a h-polytope representation." << std::endl;
			computeReachableStates<Number, Representation>(
				  filename, hypro::representation_name::polytope_h );
			break;
		}

		case 1: {
			using Representation = hypro::Box<Number>;
			std::cout << "Using a box representation." << std::endl;
			computeReachableStates<Number, Representation>(
				  filename, hypro::representation_name::box );
			break;
		}
		default: {
			using Representation = hypro::Box<Number>;
			std::cout << "Using a box representation." << std::endl;
			computeReachableStates<Number, Representation>(
				  filename, hypro::representation_name::box );
		}
	}

	exit( 0 );
}
