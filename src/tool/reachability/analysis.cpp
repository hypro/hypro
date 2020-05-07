#include "analysis.h"

namespace hydra {
namespace reachability {

using namespace hypro;

template <typename State>
void concrete_analyze( HybridAutomaton<Number>& automaton, Settings setting ) {
	LTIAnalyzer<State> analyzer{automaton, setting};
	auto result = analyzer.run();

	if ( result == REACHABILITY_RESULT::UNKNOWN ) {
		std::cout << "Could not verify safety." << std::endl;
		// Call bad state handling (e.g., return path)
	} else {
		std::cout << "The model is safe." << std::endl;
	}

	// call to plotting.
	auto& plt = Plotter<typename State::NumberType>::getInstance();
	plt.setFilename( "outtest" );
	for ( const auto pltDimensions : setting.plotDimensions ) {
		for ( const auto& fp : analyzer.getFlowpipes() ) {
			for ( const auto& segment : fp ) {
				plt.addObject( segment.project( pltDimensions ).vertices() );
			}
		}
		plt.plot2d();  // writes to .plt file for pdf creation
	}
}

struct Dispatcher {
	template <typename Rep>
	void operator()( HybridAutomaton<Number>& automaton, Settings setting ) {
		using concreteState = hypro::State<hydra::Number, Rep>;
		concrete_analyze<concreteState>( automaton, setting );
	}
};

void analyze( HybridAutomaton<Number>& automaton, Settings setting ) {
	dispatch<hydra::Number, Converter<hydra::Number>>( setting.strategy.front().representation_type,
													   setting.strategy.front().representation_setting, Dispatcher{}, automaton, setting );
}

}  // namespace reachability
}  // namespace hydra
