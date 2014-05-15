/* 
 * This file defines the parser for different input files.
 * @file   parser.h
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 *
 * @since   2014-05-14
 * @version 2014-05-14
 */

#pragma once

#define BOOST_SPIRIT_USE_PHOENIX_V3

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
typedef qi::space_type Skipper;





template<typename Iterator>
struct MatrixParser : public qi::grammar<Iterator, std::vector<std::vector<double>>(), Skipper>
{
    MatrixParser() : MatrixParser::base_type(start)
    {
        start =  "[" >> ((qi::double_ % qi::char_(' ',',')) % ';') >> "]";
    }
    
    qi::rule<Iterator,std::vector<std::vector<double>>(), Skipper> start;
};

template<typename Iterator>
//struct StateParser : public qi::grammar<Iterator, Skipper>
struct StateParser : public qi::grammar<Iterator, State(), Skipper>
{
    MatrixParser<Iterator> mMatrixParser;
    
    StateParser() : StateParser::base_type(start)
    {
       start = qi::lit("states") > "{" > qi::int_ > "}." > qi::char_("AbB")  > "=" > mMatrixParser > ";";
    }
    
    qi::rule<Iterator, State(), Skipper> start;
    //qi::rule<Iterator, Skipper> start;
};

template<typename Iterator>
struct MainParser : public qi::grammar<Iterator, Skipper>
{
    StateParser<Iterator> mStateParser;
    
    MainParser() : MainParser::base_type(main)
    {
        //using phoenix::construct;
        using phoenix::val;
        
        qi::debug(main);
        
        main = mStateParser;
        
        qi::on_error<qi::fail>
        (
        main
        , std::cout
            << val("Error! Expecting ")
            << qi::_4                               // what failed?
            << val(" here: \"")
            //<< construct<std::string>(qi::_3, qi::_2)   // iterators to error-pos, end
            << val("\"")
            << std::endl
        );
    }    
    
    qi::rule<Iterator, Skipper> main;
    
};






class HyproParser : public qi::grammar<Iterator, Skipper>
{   
    private:
    // Rules
    MainParser<Iterator> mMainParser;
    qi::rule<Iterator,Skipper> main;
    
    public:
    HyproParser() : HyproParser::base_type(main)
    {
        main = mMainParser;
    }    

    void parseInput(const std::string& pathToInputFile);
    bool parse(std::istream& in, const std::string& filename);
};
}
}