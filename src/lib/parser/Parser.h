/* 
 * This file defines the parser for different input files.
 * @file   parser.h
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 *
 * @since   2014-05-14
 * @version 2014-05-14
 */

#pragma once

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/support_line_pos_iterator.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include "Utils.h"

namespace hypro{
namespace parser{
    
namespace spirit = boost::spirit;    
namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;
namespace phoenix = boost::phoenix;

typedef spirit::istream_iterator BaseIteratorType;
typedef spirit::line_pos_iterator<BaseIteratorType> PositionIteratorType;
typedef PositionIteratorType Iterator;
typedef ascii::space_type Skipper;

class HyproParser : public qi::grammar<Iterator, Skipper>
{
    void parseInput(const std::string& pathToInputFile);
    bool parse(std::istream& in, const std::string& filename);
    
    // Rules
    
    qi::rule<Iterator> main;
};

template<typename Iterator>
struct MatrixParser : public qi::grammar<Iterator, std::vector<std::vector<double>>, Skipper>
{
    MatrixParser() : MatrixParser::base_type(start)
    {
        start =  "[" >> (qi::double_ % qi::char_(' ',',')) % ';' >> "]";
    }
    
    qi::rule<Iterator,std::vector<std::vector<double>>()> start;
};

template<typename Iterator>
struct StateParser : public qi::grammar<Iterator, State(), Skipper>
{
    MatrixParser<Iterator> mMatrixParser;
    
    StateParser() : StateParser::base_type(start)
    {
        start = qi::lit("states") >> "{" >> qi::int_ >> "}." >> qi::char_("A","b","B")  >> "=" >> mMatrixParser;
    }
    
    qi::rule<Iterator, State> start;
};

template<typename Iterator>
struct MainParser : public qi::grammar<Iterator, Skipper>
{
    StateParser<Iterator> mStateParser;
    
    MainParser() : MainParser::base_type(main)
    {
        main = mStateParser;
    }
    qi::rule<Iterator> main;
};

}
}