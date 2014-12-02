/* 
 * This file holds component parsers which would pollute the main parser otherwise.
 * 
 * @file   componentParser.h
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 *
 * @since	2014-11-10
 * @version	2014-11-10
 */

#pragma once

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/support_line_pos_iterator.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include "boost/variant.hpp"
#include <string>

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
	struct MatrixParser : public qi::grammar<Iterator, parser::Matrix(), Skipper>
	{
		MatrixParser() : MatrixParser::base_type(start)
		{
			start =  qi::lit("matrix") > *(qi::char_-(qi::lit("[") | qi::lit(")") | qi::lit(","))) > -(qi::lit("[") > ((qi::double_ % qi::no_skip[qi::char_(' ',',')]) % ';') > qi::lit("]"));
		}

		qi::rule<Iterator,parser::Matrix(), Skipper> start;
	};
	
	template<typename Iterator>
	struct NameParser : public qi::grammar<Iterator, unsigned(), Skipper>
	{
		NameParser() : NameParser::base_type(start)
		{
			start =  qi::lexeme[(qi::lit("n") | qi::lit("N") ) > qi::lit("ame")] > qi::lit("=") > qi::uint_;
		}

		qi::rule<Iterator, unsigned(), Skipper> start;
	};
	
	template<typename Iterator>
	struct shortLocationParser : public qi::grammar<Iterator, unsigned(), Skipper>
	{
		shortLocationParser() : shortLocationParser::base_type(start)
		{
			start =  qi::lexeme[(qi::lit("l") | qi::lit("L") ) > qi::lit("ocation")] > qi::lit("=") > qi::uint_;
		}

		qi::rule<Iterator, unsigned(), Skipper> start;
	};
	
	template<typename Iterator>
	struct FlowParser : public qi::grammar<Iterator, parser::Matrix(), Skipper>
	{
		MatrixParser<Iterator> mMatrixParser;
		
		FlowParser() : FlowParser::base_type(start)
		{
			start =  qi::lexeme[(qi::lit("f") | qi::lit("F") ) > qi::lit("low")] > qi::lit("=") > mMatrixParser;
		}

		qi::rule<Iterator, parser::Matrix(), Skipper> start;
	};
	
	template<typename Iterator>
	struct InvariantParser : public qi::grammar<Iterator, parser::Matrix(), Skipper>
	{
		MatrixParser<Iterator> mMatrixParser;
		
		InvariantParser() : InvariantParser::base_type(start)
		{
			start =  qi::lexeme[(qi::lit("i") | qi::lit("I") ) > qi::lit("nvariant")] > qi::lit("=") > mMatrixParser;
		}

		qi::rule<Iterator, parser::Matrix(), Skipper> start;
	};
	
	template<typename Iterator>
	struct GuardParser : public qi::grammar<Iterator, parser::Matrix(), Skipper>
	{
		MatrixParser<Iterator> mMatrixParser;
		
		GuardParser() : GuardParser::base_type(start)
		{
			start =  qi::lexeme[(qi::lit("g") | qi::lit("G") ) > qi::lit("uard")] > qi::lit("=") > mMatrixParser;
		}

		qi::rule<Iterator, parser::Matrix(), Skipper> start;
	};
	
	template<typename Iterator>
	struct ResetParser : public qi::grammar<Iterator, parser::Matrix(), Skipper>
	{
		MatrixParser<Iterator> mMatrixParser;
		
		ResetParser() : ResetParser::base_type(start)
		{
			start =  qi::lexeme[(qi::lit("r") | qi::lit("R") ) > qi::lit("eset")] > qi::lit("=") > mMatrixParser;
		}

		qi::rule<Iterator, parser::Matrix(), Skipper> start;
	};
	
}
}


