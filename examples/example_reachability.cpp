/*
 * Copyright (c) 2023-2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/**
 *
 */

#include <hypro/algorithms/reachability/Reach.h>
#include <hypro/datastructures/HybridAutomaton/HybridAutomaton.h>
#include <hypro/datastructures/reachability/ReachTreev2Util.h>
#include <hypro/parser/antlr4-flowstar/ParserWrapper.h>
#include <hypro/representations/GeometricObjectBase.h>
#include <hypro/util/plotting/Plotter.h>
#include <hypro/util/statistics/statistics.h>

template <typename Number, typename Representation>
static void computeReachableStates( const std::string& filename,
									const hypro::representation_name& type ) {
	using Automaton = hypro::HybridAutomaton<Number>;
	using clock = std::chrono::high_resolution_clock;
	using timeunit = std::chrono::microseconds;
	clock::time_point start = clock::now();

	auto [automaton, parsedSettings] = hypro::parseFlowstarFile<Number>( filename );

	std::cout << parsedSettings << std::endl;

	hypro::Settings settings = hypro::convert( parsedSettings );
	auto roots = hypro::makeRoots<Representation, Automaton>( automaton );

	hypro::AnalysisParameters analysisParams = settings.strategy().front();

	hypro::reachability::Reach<Representation, Automaton> reacher( automaton, settings.fixedParameters(), analysisParams, roots );

	auto result = reacher.computeForwardReachability();
	auto flowpipes = getFlowpipes( roots );

	std::cout
		  << "Finished computation of reachable states: "
		  << std::chrono::duration_cast<timeunit>( clock::now() - start ).count() /
				   1000.0
		  << " ms" << std::endl;

	if ( settings.plotting().plotDimensions.size() > 0 ) {
		clock::time_point startPlotting = clock::now();

		auto& plotter = hypro::Plotter<Number>::getInstance();
		std::string extendedFilename = settings.plotting().plotFileNames.front();
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
			  settings.plotting().plotDimensions.at( 0 );
		plotter.rSettings().dimensions.push_back( plottingDimensions.front() );
		plotter.rSettings().dimensions.push_back( plottingDimensions.back() );
		plotter.rSettings().cummulative = false;

		// bad states plotting
		typename hypro::HybridAutomaton<Number>::locationConditionMap
			  badStateMapping = automaton.getLocalBadStates();
		for ( const auto& state : badStateMapping ) {
			auto matrix = state.second.getMatrix( 0 );
			auto vector = state.second.getVector( 0 );
			// if ( filename == "../examples/input/bouncing_ball.model") {
			// 	std::cout << "Invert matrix columns..." << std::endl;
			// 	for(int i = 0; i < 4; ++i) {
			// 		Number val_c = matrix(i, 0);
			// 		matrix(i, 0) = matrix(i, 1);
			// 		matrix(i, 1) = val_c;
			// 	}
			// }
			unsigned bs = plotter.addObject(
				  Representation( matrix, vector ).projectOn( plottingDimensions ).vertices(),
				  hypro::plotting::colors[hypro::plotting::red] );
		}

		// segments plotting
		for ( const auto& flowpipe : flowpipes ) {
			for ( const auto& segment : flowpipe ) {
				plotter.addObject( segment.projectOn( plottingDimensions ).vertices() );
			}
		}

		PRINT_STATS()

		std::cout << "Write to file." << std::endl;

		plotter.plot2d( hypro::PLOTTYPE::pdf, true );

		std::cout << "Finished plotting: "
				  << std::chrono::duration_cast<timeunit>( clock::now() -
														   startPlotting )
								 .count() /
						   1000.0
				  << " ms" << std::endl;
	}
}

int main( int argc, char** argv ) {
	int rep = 0;
	std::string filename = argv[1];
	if ( argc > 2 ) {
		char* p;
		rep = strtol( argv[2], &p, 10 );
	}

#ifdef USE_CLN_NUMBERS
	using Number = cln::cl_RA;
#else
	// using Number = mpq_class;
	using Number = double;
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
