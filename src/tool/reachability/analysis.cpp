#include "analysis.h"

namespace hydra {
namespace reachability {

using namespace hypro;

template <typename State>
std::vector<PlotData<FullState>> lti_analyze( HybridAutomaton<Number>& automaton, Settings setting ) {
	START_BENCHMARK_OPERATION( Verification );
	LTIAnalyzer<State> analyzer{ automaton, setting };
	auto result = analyzer.run();

	if ( result == REACHABILITY_RESULT::UNKNOWN ) {
		std::cout << "Could not verify safety." << std::endl;
		// Call bad state handling (e.g., return path)
	} else {
		std::cout << "The model is safe." << std::endl;
	}
	EVALUATE_BENCHMARK_RESULT( Verification );

	// create plot data
	std::vector<PlotData<FullState>> plotData{};

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
	return plotData;
}

template <typename State>
std::vector<PlotData<FullState>> rectangular_analyze( HybridAutomaton<Number>& automaton, Settings setting ) {
	START_BENCHMARK_OPERATION( Verification );
	RectangularAnalyzer<State> analyzer{ automaton, setting };
	auto result = analyzer.run();

	if ( result == REACHABILITY_RESULT::UNKNOWN ) {
		std::cout << "Could not verify safety." << std::endl;
		// Call bad state handling (e.g., return path)
	} else {
		std::cout << "The model is safe." << std::endl;
	}
	EVALUATE_BENCHMARK_RESULT( Verification );

	// create plot data
	std::vector<PlotData<FullState>> plotData{};

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
	return plotData;
}

struct LTIDispatcher {
	template <typename Rep>
	auto operator()( HybridAutomaton<Number>& automaton, Settings setting ) {
		using concreteState = hypro::State<hydra::Number, Rep>;
		return lti_analyze<concreteState>( automaton, setting );
	}
};

struct RectangularDispatcher {
	template <typename Rep>
	auto operator()( HybridAutomaton<Number>& automaton, Settings setting ) {
		using concreteState = hypro::State<hydra::Number, Rep>;
		return rectangular_analyze<concreteState>( automaton, setting );
	}
};

AnalysisResult analyze( HybridAutomaton<Number>& automaton, Settings setting, PreprocessingInformation information ) {
	switch ( information.dynamic ) {
		case DynamicType::affine:
			[[fallthrough]];
		case DynamicType::linear:
			return { dispatch<hydra::Number, Converter<hydra::Number>>( setting.strategy.front().representation_type,
																		setting.strategy.front().representation_setting, LTIDispatcher{}, automaton, setting ) };
			break;
		case DynamicType::rectangular: {
			// no dispatch for rectangular automata, representation and setting are fixed
			RectangularDispatcher rectangularDisp{};
			return { rectangularDisp.operator()<CarlPolytope<Number>>( automaton, setting ) };
		} break;
		case DynamicType::timed:
			break;
		case DynamicType::discrete:
			break;
		default:
			assert( false && "No analyzer selected." );
			break;
	}
}

}  // namespace reachability
}  // namespace hydra
