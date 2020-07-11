#include "analysis.h"

#include "../../hypro/algorithms/reachability/analyzer/CEGARAnalyzer.h"
#include "../../hypro/algorithms/reachability/analyzer/LTIAnalyzer.h"
#include "../../hypro/datastructures/HybridAutomaton/State.h"
#include "../../hypro/datastructures/reachability/TreeTraversal.h"
#include "../../hypro/representations/conversion/Converter.h"
#include "../../hypro/util/plotting/Plotter.h"
#include "../../hypro/util/type_handling/dispatch.h"

namespace hydra {
namespace reachability {

using namespace hypro;

template <class Analyzer, class Representation, class Number>
void concrete_analyze( HybridAutomaton<Number> const& automaton, Settings settings ) {
	START_BENCHMARK_OPERATION( Verification );

	auto roots = makeRoots<Representation>(automaton);
	Analyzer analyzer{automaton, settings, roots};
	auto [result, _] = analyzer.run();

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
	for ( const auto& node : preorder(roots) ) {
		amount += node.getFlowpipe().size();
	}

	auto& plt = Plotter<typename State::NumberType>::getInstance();
	for ( std::size_t pic = 0; pic < settings.plotDimensions.size(); ++pic ) {
		std::cout << "Prepare plot " << pic + 1 << "/" << settings.plotDimensions.size() << "." << std::endl;
		plt.setFilename( settings.plotFileNames[pic] );
		std::size_t segmentCount = 0;
		for ( const auto& node : preorder(roots) ) {
			for ( const auto& segment : node.getFlowpipe() ) {
				std::cout << "\r" << segmentCount++ << "/" << amount << "..." << std::flush;
				plt.addObject( segment.project( settings.plotDimensions[pic] ).vertices() );
			}
		}
		plt.plot2d( settings.plottingFileType );	 // writes to .plt file for pdf creation
	}
	EVALUATE_BENCHMARK_RESULT( Plotting );
}

struct Dispatcher {
	template <typename Rep>
	void operator()( HybridAutomaton<Number>& automaton, Settings settings ) {
		concrete_analyze<LTIAnalyzer<Rep>, Rep>( automaton, settings );
	}
};

void analyze( HybridAutomaton<Number>& automaton, Settings settings ) {
	if ( false ) {
		dispatch<hydra::Number, Converter<hydra::Number>>( settings.strategy.front().representation_type, settings.strategy.front().representation_setting, Dispatcher{}, automaton, settings );
	} else {
		CEGARAnalyzer<Number> analyzer{ automaton, settings };
		analyzer.run();
		analyzer.plot();
	}
}

}  // namespace reachability
}  // namespace hydra
