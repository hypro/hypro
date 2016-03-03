#define BOOST_SPIRIT_USE_PHOENIX_V3
//#define BOOST_SPIRIT_DEBUG
#include <iostream>
#include <fstream>
#include <vector>

#include <boost/spirit/include/support_line_pos_iterator.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/fusion/adapted/std_pair.hpp>
#include <boost/fusion/include/std_pair.hpp>
#include <boost/fusion/include/tuple.hpp>
#include <boost/spirit/include/phoenix_bind.hpp>

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/spirit/include/phoenix_object.hpp>

#include "../../config.h"
#include "common.h"
#include "../../datastructures/hybridAutomata/LocationManager.h"
#include "../../datastructures/hybridAutomata/HybridAutomaton.h"
#include "../../util/types.h"
#include "symbols.h"
#include "polynomialParser.h"
#include "componentParser.h"

#pragma once

namespace hypro {
namespace parser {

template <typename Number, typename Representation>
struct flowstarParser
    : qi::grammar<Iterator, Skipper>
{
	symbol_table mSymbols;
	symbol_table mModes;
	VariablePool& mVariablePool = VariablePool::getInstance();
	variables<Iterator> mVariables;
	modeParser<Iterator, Number> mModeParser;
	transitionParser<Iterator, Number> mTransitionParser;
	constraintParser<Iterator> mConstraintParser;
	std::vector<unsigned> mModeIds;
	std::vector<unsigned> mVariableIds;
	unsigned mDimension;

	flowstarParser() : flowstarParser::base_type( start ) {
		using qi::lit;
        using qi::lexeme;
        using qi::on_error;
        using qi::fail;
        using ascii::char_;
        using ascii::string;
        using namespace qi::labels;

        using px::construct;
        using px::val;
        using namespace qi;

        mDimension = 0;

		stateVars = qi::lexeme["state var"] > mVariables[px::bind( &flowstarParser<Number,Representation>::insertSymbols, px::ref(*this), qi::_1)];
		modes = qi::lexeme["modes"] > qi::lit('{') > *(mModeParser(px::ref(mSymbols), px::ref(mDimension))) > qi::lit("}");
		transitions = mTransitionParser(px::ref(mModes), px::ref(mSymbols), px::ref(mDimension))[px::bind( &flowstarParser<Number,Representation>::insertTransitions, px::ref(*this), qi::_1)];
		init = qi::lexeme["init"] > qi::lit('{') > mModes > qi::lit('{') > *(mConstraintParser(px::ref(mSymbols), px::ref(mDimension))) > qi::lit('}') > qi::lit('}');
		badStates = qi::lexeme["unsafe set"] > qi::lit('{') > *( mModes > qi::lit('{') > *(mConstraintParser(px::ref(mSymbols), px::ref(mDimension))) > qi::lit('}') ) > qi::lit('}');
		settings = qi::lexeme["settings"] > qi::lit('{') > qi::lit('}');
		start =  stateVars > modes[px::bind( &flowstarParser<Number,Representation>::insertModes, px::ref(*this), qi::_1 )] > -transitions[px::bind( &flowstarParser<Number, Representation>::insertTransitions, px::ref(*this), qi::_1)] > -init > -badStates > qi::eoi;

		qi::on_error<qi::fail>
		(
		    start
		  , std::cout <<
		  	px::val("MainParser: Syntax error. Expecting ")
        	<< _4
	        << px::val(" here: \"")
	        << construct<std::string>(_3, _2)
	        << px::val("\"")
	        << std::endl
		);
	}

	qi::rule<Iterator, Skipper> start;
	qi::rule<Iterator, Skipper> stateVars;
	qi::rule<Iterator, Skipper> init;
	qi::rule<Iterator, Skipper> settings;
	qi::rule<Iterator, Skipper> badStates;
	qi::rule<Iterator, std::vector<std::pair<std::string, Location<Number>*>>(), Skipper> modes;
	qi::rule<Iterator, std::set<Transition<Number>*>(), Skipper> transitions;

	void insertSymbols(const std::vector<std::string>& _in) {
		for(const auto& varName : _in ) {
			carl::Variable tmp = mVariablePool.newCarlVariable(varName);
			std::cout << "Mapped var " << varName << " to dimension " << mVariablePool.id(tmp) << std::endl;
			mSymbols.add(varName, mVariablePool.id(tmp));
			mVariableIds.push_back(mVariablePool.id(tmp));
			++mDimension;
		}
	}

	void insertModes(const std::vector<std::pair<std::string, Location<Number>*>>& _in) {
		for(const auto& modePair : _in) {
			std::cout << "Found mode " << modePair.first << " mapped to " << modePair.second->id() << std::endl;
			//std::cout << "Mode: " << *modePair.second << std::endl;
			mModes.add(modePair.first, modePair.second->id());
			mModeIds.push_back(modePair.second->id());
		}
	}

	void insertTransitions(const boost::optional<std::set<Transition<Number>*>>& _transitions) {
		if(_transitions){
			for(const auto transition : *_transitions)
				std::cout << *transition << std::endl;
		}
	}

	void parseInput( const std::string& pathToInputFile );
	bool parse( std::istream& in, const std::string& filename, HybridAutomaton<Number, Representation>& _result );
	void printModes() const;
	//HybridAutomaton<Number, Representation> createAutomaton();
};

} // namespace parser
} // namespace hypro

#include "flowstarParser.tpp"