#include "analysis.h"

namespace hydra {
namespace reachability {

using namespace hypro;

template <typename State>
std::vector<PlotData<FullState>> concrete_analyze( HybridAutomaton<Number>& automaton, Settings setting ) {
	START_BENCHMARK_OPERATION( Verification );
	LTIAnalyzer<State> analyzer{ automaton, setting };
	auto result = analyzer.run();

	if ( result == REACHABILITY_RESULT::UNKNOWN ) {
		std::cout << "Could not verify safety." << std::endl;
		// Call bad state handling (e.g., return path)
	} else {
		std::cout << "The model is safe." << std::endl;
	}

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

struct Dispatcher {
	template <typename Rep>
	auto operator()( HybridAutomaton<Number>& automaton, Settings setting ) {
		using concreteState = hypro::State<hydra::Number, Rep>;
		return concrete_analyze<concreteState>( automaton, setting );
	}
};

AnalysisResult analyze( HybridAutomaton<Number>& automaton, Settings setting ) {
	return { dispatch<hydra::Number, Converter<hydra::Number>>( setting.strategy.front().representation_type,
																setting.strategy.front().representation_setting, Dispatcher{}, automaton, setting ) };
}

}  // namespace reachability
}  // namespace hydra
