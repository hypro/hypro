#include "analysis.h"

namespace hydra {
namespace reachability {

using namespace hypro;

template <typename State>
void lti_analyze( HybridAutomaton<Number>& automaton, Settings setting ) {
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

	// call to plotting.
	START_BENCHMARK_OPERATION( Plotting );
	std::size_t amount = 0;
	for ( const auto& fp : analyzer.getFlowpipes() ) {
		amount += fp.size();
	}

	auto& plt = Plotter<typename State::NumberType>::getInstance();
	for ( std::size_t pic = 0; pic < setting.plotDimensions.size(); ++pic ) {
		std::cout << "Prepare plot " << pic + 1 << "/" << setting.plotDimensions.size() << "." << std::endl;
		plt.setFilename( setting.plotFileNames[pic] );
		std::size_t segmentCount = 0;
		for ( const auto& fp : analyzer.getFlowpipes() ) {
			for ( const auto& segment : fp ) {
				std::cout << "\r" << segmentCount++ << "/" << amount << "..." << std::flush;
				plt.addObject( segment.project( setting.plotDimensions[pic] ).vertices() );
			}
		}
		plt.plot2d( setting.plottingFileType );	 // writes to .plt file for pdf creation
	}
	EVALUATE_BENCHMARK_RESULT( Plotting );
}

template <typename State>
void rectangular_analyze( HybridAutomaton<Number>& automaton, Settings setting ) {
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

	// call to plotting.
	START_BENCHMARK_OPERATION( Plotting );
	std::size_t amount = 0;
	for ( const auto& fp : analyzer.getFlowpipes() ) {
		amount += fp.size();
	}

	auto& plt = Plotter<typename State::NumberType>::getInstance();
	for ( std::size_t pic = 0; pic < setting.plotDimensions.size(); ++pic ) {
		std::cout << "Prepare plot " << pic + 1 << "/" << setting.plotDimensions.size() << "." << std::endl;
		plt.setFilename( setting.plotFileNames[pic] );
		std::size_t segmentCount = 0;
		for ( const auto& fp : analyzer.getFlowpipes() ) {
			for ( const auto& segment : fp ) {
				std::cout << "\r" << segmentCount++ << "/" << amount << "..." << std::flush;
				plt.addObject( segment.project( setting.plotDimensions[pic] ).vertices() );
			}
		}
		plt.plot2d( setting.plottingFileType );	 // writes to .plt file for pdf creation
	}
	EVALUATE_BENCHMARK_RESULT( Plotting );
}

struct LTIDispatcher {
	template <typename Rep>
	void operator()( HybridAutomaton<Number>& automaton, Settings setting ) {
		using concreteState = hypro::State<hydra::Number, Rep>;
		lti_analyze<concreteState>( automaton, setting );
	}
};

struct RectangularDispatcher {
	template <typename Rep>
	void operator()( HybridAutomaton<Number>& automaton, Settings setting ) {
		using concreteState = hypro::State<hydra::Number, Rep>;
		rectangular_analyze<concreteState>( automaton, setting );
	}
};

void analyze( HybridAutomaton<Number>& automaton, Settings setting, hypro::PreprocessingInformation information ) {
	switch ( information.dynamic ) {
		case DynamicType::affine:
			[[fallthrough]];
		case DynamicType::linear:
			dispatch<hydra::Number, Converter<hydra::Number>>( setting.strategy.front().representation_type,
															   setting.strategy.front().representation_setting, LTIDispatcher{}, automaton, setting );
			break;
		case DynamicType::rectangular: {
			// no dispatch for rectangular automata, representation and setting are fixed
			RectangularDispatcher rectangularDisp{};
			rectangularDisp.operator()<hypro::CarlPolytope<hydra::Number>>( automaton, setting );
		} break;
		case DynamicType::timed:
			break;
		case DynamicType::discrete:
			break;
		default:
			break;
	}
}

}  // namespace reachability
}  // namespace hydra
