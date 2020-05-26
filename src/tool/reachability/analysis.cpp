#include "analysis.h"

namespace hydra {
namespace reachability {

using namespace hypro;

template <typename State>
void concrete_analyze( HybridAutomaton<Number>& automaton, Settings setting ) {
	START_BENCHMARK_OPERATION( Verification );
	LTIAnalyzer<State> analyzer{automaton, setting};
	auto result = analyzer.run();

	if ( result == REACHABILITY_RESULT::UNKNOWN ) {
		std::cout << "Could not verify safety." << std::endl;
		// Call bad state handling (e.g., return path)
	} else {
		std::cout << "The model is safe." << std::endl;
	}
	EVALUATE_BENCHMARK_RESULT( Verification );

	// call to plotting.
	START_BENCHMARK_OPERATION( Plotting );
	std::size_t amount = 0;
	for ( const auto& fp : analyzer.getFlowpipes() ) {
		amount += fp.size(); 
	}
	std::size_t segmentCount = 0;
	auto& plt = Plotter<typename State::NumberType>::getInstance();
	for ( std::size_t pic = 0; pic < setting.plotDimensions.size(); ++pic ) {
		plt.setFilename( setting.plotFileNames[pic] );
		for ( const auto& fp : analyzer.getFlowpipes() ) {
			for ( const auto& segment : fp ) {
				std::cout << "\r" << segmentCount++ << "/" << amount << "..." << std::flush;
				plt.addObject( segment.project( setting.plotDimensions[pic] ).vertices() );
			}
		}
		plt.plot2d();  // writes to .plt file for pdf creation
	}
	EVALUATE_BENCHMARK_RESULT( Plotting );
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
