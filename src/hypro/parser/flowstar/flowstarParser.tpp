#pragma once

#include "flowstarParser.h"

namespace hypro {
namespace parser {

	template<typename Number>
	flowstarParser<Number>::flowstarParser() : base_type( start ) {
		using qi::on_error;
        using qi::fail;

        mDimensionLimit = 0;
        mDiscreteDimensionLimit = 0;

		start =  ( qi::lexeme["continuous reachability"] > qi::lit('{') > continuousStart > qi::lit('}') > -badStates > qi::eoi )
				|( qi::lexeme["hybrid reachability"] > qi::lit('{') > hybridStart > qi::lit('}') > (-badStates) > qi::eoi);

		continuousStart = 		continuousVariables > -discreteVariables > -mSettingsParser(px::ref(mVariableSymbolTable));
		hybridStart = 			continuousVariables > -discreteVariables > settings >
								modes[px::bind( &flowstarParser<Number>::insertModes, px::ref(*this), qi::_1 )] >
								-transitions[px::bind( &flowstarParser<Number>::insertTransitions, px::ref(*this), qi::_1)] >
								(-init);
		discreteVariables = 	qi::lexeme["discrete var"] > mVariableParser[px::bind( &flowstarParser<Number>::insertDiscreteSymbols, px::ref(*this), qi::_1)];
		continuousVariables = 	qi::lexeme["state var"] > mVariableParser[px::bind( &flowstarParser<Number>::insertContinuousSymbols, px::ref(*this), qi::_1)];
		settings = 				qi::lexeme["setting"] > qi::lit('{') > mSettingsParser(px::ref(mVariableSymbolTable))[px::bind( &flowstarParser<Number>::insertSettings, px::ref(*this), qi::_1)] > qi::lit('}');
		modes = 				qi::lexeme["modes"] > qi::lit('{') > *(mModeParser(px::ref(mVariableSymbolTable), px::ref(mDiscreteVariableSymbolTable), px::ref(mDimensionLimit), px::ref(mDiscreteDimensionLimit))) > qi::lit("}");
		transitions = 			mTransitionParser(px::ref(mModes), px::ref(mVariableSymbolTable), px::ref(mDiscreteVariableSymbolTable), px::ref(mDimensionLimit), px::ref(mDiscreteDimensionLimit))[px::bind( &flowstarParser<Number>::insertTransitions, px::ref(*this), qi::_1)];
		init = 					qi::lexeme["init"] > qi::lit('{') > *(mModes[ qi::_a = px::bind( &flowstarParser<Number>::addInitState, px::ref(*this), qi::_1, px::ref(mInitialStates))] > qi::lit('{') > *(continuousInit(qi::_a) | discreteInit(qi::_a)) > qi::lit('}')) > qi::lit('}');
		continuousInit =		mConstraintParser(px::ref(mVariableSymbolTable), px::ref(mDimensionLimit))[px::bind( &flowstarParser<Number>::addContinuousState, px::ref(*this), qi::_1, qi::_r1, px::ref(mInitialStates))];
		discreteInit =			mDiscreteConstraintParser(px::ref(mDiscreteVariableSymbolTable))[px::bind( &flowstarParser<Number>::addDiscreteState, px::ref(*this), qi::_1, qi::_r1, px::ref(mInitialStates))];
		badStates = 			qi::lexeme["unsafe set"] > qi::lit('{') > *( mModes[qi::_a = qi::_1] > qi::lit('{') > *( continuousBad(qi::_a) | discreteBad(qi::_a) ) > qi::lit('}') ) > qi::lit('}');
		continuousBad = 		mConstraintParser(px::ref(mVariableSymbolTable), px::ref(mDimensionLimit))[px::bind( &flowstarParser<Number>::addContinuousState, px::ref(*this), qi::_1, qi::_r1, px::ref(mLocalBadStates))];
		discreteBad = 			mDiscreteConstraintParser(px::ref(mDiscreteVariableSymbolTable))[px::bind( &flowstarParser<Number>::addDiscreteState, px::ref(*this), qi::_1, qi::_r1, px::ref(mLocalBadStates))];

		qi::on_error<qi::fail>( start, errorHandler(qi::_1, qi::_2, qi::_3, qi::_4));
	}

	template <typename Number>
	HybridAutomaton<Number> flowstarParser<Number>::parseInput(
		  const std::string &pathToInputFile ) {
		HybridAutomaton<Number> resultAutomaton;

		std::fstream infile( pathToInputFile );
		if ( !infile.good() ) {
			std::cerr << "Could not open file: " << pathToInputFile << std::endl;
			exit( 1 );
		}
		bool parsingSuccessful = parse( infile, resultAutomaton );
		if ( !parsingSuccessful ) {
			std::cerr << "Parse error" << std::endl;
			exit( 1 );
		}

		return resultAutomaton;
	}

	template <typename Number>
	bool flowstarParser<Number>::parse( std::istream &in, HybridAutomaton<Number> &_result ) {
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
		if(result) {
			_result = createAutomaton();
		}

		return result;
	}

	template <typename Number>
	HybridAutomaton<Number> flowstarParser<Number>::createAutomaton() {
		HybridAutomaton<Number> result;
		LocationManager<Number>& locManag = hypro::LocationManager<Number>::getInstance();

		for(const auto index : mModeIds){
			result.addLocation(locManag.location(index));
			//std::cout << "Added location " << *locManag.location(index) << std::endl;
		}

		for(const auto transition : mTransitions ){
			result.addTransition(transition);
			//std::cout << "Added transition " << *transition << std::endl;
		}

		for(const auto state : mInitialStates ){
			//std::cout << "Add initial state for location " << state.location->id() << std::endl;
			assert(state.discreteAssignment.size() == mDiscreteVariableIds.size());
			result.addInitialState(state);
		}

		for(const auto state : mLocalBadStates ){
			result.addLocalBadState(state);
		}

		result.setReachabilitySettings(mSettings);

		return result;
	}
} // namespace parser
} // namespace hypro
