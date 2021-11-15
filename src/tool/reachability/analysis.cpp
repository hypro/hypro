/*
 * Copyright (c) 2021.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 *   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "reachability/analysis.h"

#include <hypro/algorithms/reachability/analyzer/CEGARAnalyzer.h>
#include <hypro/algorithms/reachability/analyzer/DecompositionalAnalyzer.h>
#include <hypro/algorithms/reachability/analyzer/RectangularAnalyzer.h>
#include <hypro/algorithms/reachability/analyzer/SingularAnalyzer.h>
#include <hypro/algorithms/reachability/analyzer/UrgencyCEGARAnalyzer.h>
#include <hypro/datastructures/reachability/Settings.h>
#include <hypro/datastructures/reachability/TreeTraversal.h>
#include <hypro/representations/conversion/Converter.h>
#include <hypro/util/plotting/Plotter.h>

namespace hydra {
namespace reachability {

using namespace hypro;

std::vector<PlotData<FullState>> cegar_analyze( HybridAutomaton<Number>& automaton, Settings setting ) {
	START_BENCHMARK_OPERATION( "Verification" );
	CEGARAnalyzer<Number> analyzer{ automaton, setting };

	REACHABILITY_RESULT result = analyzer.run();
	if ( result == REACHABILITY_RESULT::UNKNOWN ) {
		std::cout << "Could not verify safety." << std::endl;
		// Call bad state handling (e.g., return path)
	} else {
		std::cout << "The model is safe." << std::endl;
	}
	EVALUATE_BENCHMARK_RESULT( "Verification" );

	// create plot data
	std::vector<PlotData<FullState>> plotData{};
	if ( !setting.plotting().plotDimensions.empty() ) {
		auto levels = analyzer.getLevels();

		size_t levelIndex = 0;
		for ( auto levelVar : levels ) {
			std::visit( [&]( auto* level ) {
				for ( const auto& node : preorder( level->roots ) ) {
					std::transform( node.getFlowpipe().begin(), node.getFlowpipe().end(), std::back_inserter( plotData ), [=]( auto& segment ) {
						FullState state{};
						state.setSet( segment );
						return PlotData{ state, levelIndex };
					} );
				}
			},
						levelVar );
			levelIndex += 1;
		}
	}

	return plotData;
}



template <typename LTIRep>
std::vector<PlotData<FullState>> decompositional_analyze ( HybridAutomaton<Number>& decomposedHa, Decomposition& decomposition, Settings setting, std::size_t clockCount ) {
	START_BENCHMARK_OPERATION( "Verification" );
	using Number = typename LTIRep::NumberType;
	using SingularRep = hypro::VPolytope<Number>;
	using DiscreteRep = hypro::Box<Number>;
	using RectangularRep = hypro::Box<Number>;
	DecompositionalAnalyzer<LTIRep, SingularRep, DiscreteRep, RectangularRep> analyzer{ decomposedHa, decomposition, clockCount,
																						setting.fixedParameters(), setting.strategy().front() };
	auto result = analyzer.run();
	if ( !setting.fixedParameters().silent ) {
		if ( result.result() == REACHABILITY_RESULT::UNKNOWN ) {
			std::cout << "Could not verify safety." << std::endl;
		} else {
			std::cout << "The model is safe." << std::endl;
		}
	}
	EVALUATE_BENCHMARK_RESULT( "Verification" );
	START_BENCHMARK_OPERATION( "Compose flowpipes" );
	std::vector<PlotData<FullState>> plotData{};
	// skip if not plotted, otherwise compose plot data
	if ( !setting.plotting().plotDimensions.empty() ) {
		DecompositionalSegmentGen segments( analyzer.getRoots(), analyzer.getDepRoots(), decomposition, clockCount );
		for ( auto segment = segments.next(); segment; segment = segments.next() ) {
			FullState state{};
			state.setSet( segment.value() );
			plotData.push_back( PlotData{ state, 0, 0 } );
		}
	}
	STOP_BENCHMARK_OPERATION( "Compose flowpipes" );
	return plotData;
}

template <typename State>
std::vector<PlotData<FullState>> urgency_cegar_analyze( HybridAutomaton<Number>& automaton, Settings setting ) {
	START_BENCHMARK_OPERATION( "Verification" );
	UrgencyCEGARAnalyzer<State> analyzer{ automaton, setting.fixedParameters(), setting.strategy().front(), setting.urgencySettings() };
	auto result = analyzer.run();

	if ( result.result() == REACHABILITY_RESULT::UNKNOWN ) {
		std::cout << "Could not verify safety." << std::endl;
		// Call bad state handling (e.g., return path)
	} else {
		std::cout << "The model is safe." << std::endl;
	}
	EVALUATE_BENCHMARK_RESULT( "Verification" );

	// create plot data
	std::vector<PlotData<FullState>> plotData{};

	auto roots = analyzer.getRoots();
	for ( const auto& node : preorder<ReachTreeNode<State>>( roots ) ) {
		if ( result.result() == REACHABILITY_RESULT::SAFE && node.getSafety() == REACHABILITY_RESULT::UNKNOWN ) continue;
		std::transform( node.getFlowpipe().begin(), node.getFlowpipe().end(), std::back_inserter( plotData ), []( auto& segment ) {
			FullState state{};
			state.setSet( segment );
			return PlotData{ state, 0, 0 };
		} );
	}
	return plotData;
}

template <typename State>
std::vector<PlotData<FullState>> lti_analyze( HybridAutomaton<Number>& automaton, Settings setting ) {
	START_BENCHMARK_OPERATION( "Verification" );
	auto roots = makeRoots<State>( automaton );
	LTIAnalyzer<State> analyzer{ automaton, setting.fixedParameters(), setting.strategy().front(), roots };
	auto result = analyzer.run();

	if ( !setting.fixedParameters().silent ) {
		if ( result.result() == REACHABILITY_RESULT::UNKNOWN ) {
			std::cout << "Could not verify safety." << std::endl;
		} else {
			std::cout << "The model is safe." << std::endl;
		}
	}
	EVALUATE_BENCHMARK_RESULT( "Verification" );

	// create plot data
	std::vector<PlotData<FullState>> plotData{};

	if ( !setting.plotting().plotDimensions.empty() ) {
		for ( const auto& node : preorder( roots ) ) {
			std::transform( node.getFlowpipe().begin(), node.getFlowpipe().end(), std::back_inserter( plotData ), []( auto& segment ) {
				FullState state{};
				state.setSet( segment );
				return PlotData{ state, 0, 0 };
			} );
		}
	}
	return plotData;
}

template <typename State>
std::vector<PlotData<FullState>> singular_analyze( HybridAutomaton<Number>& automaton, Settings setting ) {
	START_BENCHMARK_OPERATION( "Verification" );
	auto roots = makeRoots<State>( automaton );
	SingularAnalyzer<State> analyzer{ automaton, setting.fixedParameters(), roots };
	auto result = analyzer.run();

	if ( !setting.fixedParameters().silent ) {
		if ( result.result() == REACHABILITY_RESULT::UNKNOWN ) {
			std::cout << "Could not verify safety." << std::endl;
		} else {
			std::cout << "The model is safe." << std::endl;
		}
	}
	EVALUATE_BENCHMARK_RESULT( "Verification" );

	// create plot data
	std::vector<PlotData<FullState>> plotData{};
	if ( !setting.plotting().plotDimensions.empty() ) {
		for ( const auto& node : preorder( roots ) ) {
			std::transform( node.getFlowpipe().begin(), node.getFlowpipe().end(), std::back_inserter( plotData ), []( auto& segment ) {
				FullState state{};
				state.setSet( segment );
				return PlotData{ state, 0, 0 };
			} );
		}
	}
	return plotData;
}

template <typename State>
std::vector<PlotData<FullState>> rectangular_analyze( HybridAutomaton<Number>& automaton, Settings setting ) {
	auto roots = makeRoots<State>( automaton );
	START_BENCHMARK_OPERATION( "Verification" );
	RectangularAnalyzer<State> analyzer{ automaton, setting, roots };
	auto result = analyzer.run();

	if ( !setting.fixedParameters().silent ) {
		if ( result.result() == REACHABILITY_RESULT::UNKNOWN ) {
			std::cout << "Could not verify safety." << std::endl;
		} else {
			std::cout << "The model is safe." << std::endl;
		}
	}
	EVALUATE_BENCHMARK_RESULT( "Verification" );

	// create plot data
	std::vector<PlotData<FullState>> plotData{};

	if ( !setting.plotting().plotDimensions.empty() ) {
		for ( const auto& fp : analyzer.getFlowpipes() ) {
			std::transform( fp.begin(), fp.end(), std::back_inserter( plotData ), []( auto& segment ) {
				FullState state{};
				std::visit( [&]( auto& valuationSet ) {
					state.setSet( valuationSet );
				},
							segment.getSet() );
				return PlotData{ state, 0, 0 };
			} );
		}
	}
	return plotData;
}

struct DecompositionalDispatcher {
	template <typename Rep>
	auto operator()( HybridAutomaton<Number>& decomposedHa, Decomposition& decomposition, Settings setting, std::size_t clockCount ) {
		return decompositional_analyze<Rep>( decomposedHa, decomposition, setting, clockCount );
	}
};

struct LTIDispatcher {
	template <typename Rep>
	auto operator()( HybridAutomaton<Number>& automaton, Settings setting ) {
		return lti_analyze<Rep>( automaton, setting );
	}
};

struct UrgencyCEGARDispatcher {
	template <typename Rep>
	auto operator()( HybridAutomaton<Number>& automaton, Settings setting ) {
		return urgency_cegar_analyze<Rep>( automaton, setting );
	}
};

struct SingularDispatcher {
	template <typename Rep>
	auto operator()( HybridAutomaton<Number>& automaton, Settings setting ) {
		return singular_analyze<Rep>( automaton, setting );
	}
};

AnalysisResult analyze( HybridAutomaton<Number>& automaton, Settings& setting, PreprocessingInformation information ) {
	if ( urgency_cegar ) {
		return { dispatchUrgency<hydra::Number, Converter<hydra::Number>>( setting.strategy().front().representation_type,
																			setting.strategy().front().representation_setting, UrgencyCEGARDispatcher{}, automaton, setting ) };
	}
	if ( information.decomposition.subspaces.size() > 1 ) {
		// decompositional analysis
		return { dispatch<hydra::Number, Converter<hydra::Number>>( setting.strategy().front().representation_type,
																	setting.strategy().front().representation_setting, DecompositionalDispatcher{},
																	information.decomposedHa, information.decomposition, setting, information.clockCount ) };
	}

	switch ( information.dynamic ) {
		case DynamicType::affine:
			[[fallthrough]];
		case DynamicType::linear:
			if ( urgency_cegar ) {
				return { dispatchUrgency<hydra::Number, Converter<hydra::Number>>( setting.strategy().front().representation_type,
																			setting.strategy().front().representation_setting, UrgencyCEGARDispatcher{}, automaton, setting ) };
			} else if ( setting.strategy().size() == 1 ) {
				return { dispatch<hydra::Number, Converter<hydra::Number>>( setting.strategy().front().representation_type,
																			setting.strategy().front().representation_setting, LTIDispatcher{}, automaton, setting ) };
			} else {
				return { cegar_analyze( automaton, setting ) };
			}
			break;
		case DynamicType::rectangular: {
			// no dispatch for rectangular automata, representation and setting are fixed
			//return { rectangular_analyze<hypro::State<Number, CarlPolytope<Number>>>( automaton, setting ) };
			assert( false );
			[[fallthrough]];
		}
		case DynamicType::singular: {
			// no dispatch for singular automata, representation and setting are fixed
			/*
			return { singular_analyze<hypro::VPolytope<Number>>( automaton, setting ) };
			*/
			/*
			return { dispatch<hydra::Number, Converter<hydra::Number>>( setting.strategy().front().representation_type,
																		setting.strategy().front().representation_setting, SingularDispatcher{}, automaton, setting ) };
	*/
			[[fallthrough]];
		}
		case DynamicType::timed:
			[[fallthrough]];
		case DynamicType::discrete:
			[[fallthrough]];
		case DynamicType::mixed:
			assert( false && "specialized analysis not implemented yet." );
		default:
			assert( false && "No analyzer selected." );
			break;
	}
	throw std::invalid_argument( "Invalid automaton type." );
}

}  // namespace reachability
}  // namespace hydra
