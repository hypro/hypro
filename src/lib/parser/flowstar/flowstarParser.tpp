#include "flowstarParser.h"

namespace hypro {
namespace parser {

	template <typename Number>
	HybridAutomaton<Number> flowstarParser<Number>::parseInput(
		  const std::string &pathToInputFile ) {
		HybridAutomaton<Number> resultAutomaton;

		std::fstream infile( pathToInputFile );
		if ( !infile.good() ) {
			std::cerr << "Could not open file: " << pathToInputFile << std::endl;
			exit( 1 );  // TODO: Create HyPro-specific Errorcodes
		}
		bool parsingSuccessful = parse( infile, pathToInputFile, resultAutomaton );
		if ( !parsingSuccessful ) {
			std::cerr << "Parse error" << std::endl;
			exit( 1 );
		}

		return resultAutomaton;
	}

	template <typename Number>
	bool flowstarParser<Number>::parse( std::istream &in, const std::string &filename,
													HybridAutomaton<Number> &_result ) {
		in.unsetf( std::ios::skipws );
		BaseIteratorType basebegin( in );
		Iterator begin( basebegin );
		Iterator end;
		Skipper skipper;

		//std::cout << "To parse: " << std::string( begin, end ) << std::endl;
		// invoke qi parser
		bool result = qi::phrase_parse( begin, end, start, skipper );

		//std::cout << "Result: Done" << std::endl;
		//std::cout << "To parse: " << std::string( begin, end ) << std::endl;

		// create automaton from parsed result.
		if(result)
			_result = createAutomaton();

		return result;
	}

	template <typename Number>
	HybridAutomaton<Number> flowstarParser<Number>::createAutomaton() {
		HybridAutomaton<Number> result;
		LocationManager<Number>& locManag = hypro::LocationManager<Number>::getInstance();

		for(const auto index : mModeIds)
			result.addLocation(locManag.location(index));

		for(const auto transition : mTransitions )
			result.addTransition(transition);

		for(const auto initPair : mInitialStates )
			result.addInitialState(locManag.location(initPair.first), initPair.second);

		return result;
	}
} // namespace parser
} // namespace hypro
