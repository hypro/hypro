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
#include "../../datastructures/hybridAutomata/LocationManager.h"
#include "../../datastructures/hybridAutomata/HybridAutomaton.h"
#include "../../util/types.h"
#include "polynomialParser.h"
#include "componentParser.h"

#pragma once

namespace qi = boost::spirit::qi;
namespace px = boost::phoenix;
namespace ascii = boost::spirit::ascii;

namespace hypro {
namespace parser {

using symbol_table = qi::symbols<char, unsigned>;
typedef qi::space_type Skipper;

template <typename Number, typename Representation>
struct flowstarParser
    : qi::grammar<Iterator, Skipper>
{
	symbol_table mSymbols;
	symbol_table mModes;
	variables<Iterator> mVariables;
	modeParser<Iterator> mModeParser;
	transitionParser<Iterator> mTransitionParser;
	unsigned mDimension;
	unsigned mModeCount;

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
		mModeCount = 0;
		stateVars = qi::lexeme["state var"] > mVariables[px::bind( &flowstarParser<Number,Representation>::insertSymbols, px::ref(*this), qi::_1)];
		modes = qi::lexeme["modes"] > qi::lit('{') > *(mModeParser(px::ref(mSymbols), px::ref(mDimension))) > qi::lit("}");
		transitions = mTransitionParser(px::ref(mModes));
		start =  stateVars > modes[px::bind( &flowstarParser<Number,Representation>::insertModes, px::ref(*this), qi::_1 )] > -transitions > qi::eoi;

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
	qi::rule<Iterator, std::vector<std::string>(), Skipper> modes;
	qi::rule<Iterator, Skipper> transitions;

	void insertSymbols(const std::vector<std::string>& _in) {
		for(const auto& varName : _in ) {
			std::cout << "Mapped var " << varName << " to dimension " << mDimension << std::endl;
			mSymbols.add(varName, mDimension++);
		}
	}

	void insertModes(const std::vector<std::string>& _in) {
		for(const auto& modeName : _in) {
			std::cout << "Found mode " << modeName << " mapped to " << mModeCount << std::endl;
			mModes.add(modeName, mModeCount++);
		}
	}

	void parseInput( const std::string& pathToInputFile );
	bool parse( std::istream& in, const std::string& filename, HybridAutomaton<Number, Representation>& _result );
	//HybridAutomaton<Number, Representation> createAutomaton();
};

} // namespace parser
} // namespace hypro

#include "flowstarParser.tpp"