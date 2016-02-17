
#pragma once

#define BOOST_SPIRIT_USE_PHOENIX_V3

#include "components.h"
#include "polynomialParser.h"
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/support_line_pos_iterator.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
//#include <boost/spirit/include/phoenix_object.hpp>
#include <boost/spirit/include/qi_real.hpp>
#include <string>

namespace hypro {
namespace parser {

namespace spirit = boost::spirit;
namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;
namespace phoenix = boost::phoenix;
namespace fusion = boost::fusion;

typedef spirit::istream_iterator BaseIteratorType;
typedef spirit::line_pos_iterator<BaseIteratorType> PositionIteratorType;
typedef PositionIteratorType Iterator;
typedef qi::space_type Skipper;

template <typename Number>
struct FloatPolicies : qi::real_policies<Number> {
	template <typename It, typename Attr>
	static bool parse_nan( It&, It const&, Attr& ) {
		return false;
	}

	template <typename It, typename Attr>
	static bool parse_inf( It&, It const&, Attr& ) {
		return false;
	}
};

template <typename Number>
struct FloatParser : qi::real_parser<Number, FloatPolicies<Number> > {};

template <typename Iterator>
struct NameParser : public qi::grammar<Iterator, unsigned(), Skipper> {
	NameParser() : NameParser::base_type( start ) {
		start = qi::lexeme[( qi::lit( "n" ) | qi::lit( "N" ) ) > qi::lit( "ame" )] > qi::lit( "=" ) > qi::uint_;
	}

	qi::rule<Iterator, unsigned(), Skipper> start;
};

template<typename Iterator>
struct VariableParser : public qi::grammar<Iterator, Skipper> {

	hypro::parser::variableName_ mNames;

	VariableParser() : VariableParser::base_type( start ) {
		varName = ( qi::lexeme[+qi::alnum] );
		start = qi::lexeme["state var"] >> (varName[phoenix::bind( &hypro::parser::VariableParser<Iterator>::push_variable, phoenix::ref(*this), qi::_1)] % ',') > qi::eps;
	}

	qi::rule<Iterator,Skipper> start;
	qi::rule<Iterator, std::string(), Skipper> varName;

	void push_variable(const std::string& _in) {
		std::cout << "Found Var: " << _in << std::endl;
		mNames.add(_in,0);
	}

	hypro::parser::variableName_& getTable() {
		return mNames;
	}
};

template <typename Iterator, typename Number>
struct MatrixParser : public qi::grammar<Iterator, parser::Matrix<Number>(), Skipper> {
	FloatParser<Number> mFloatParser;

	MatrixParser() : MatrixParser::base_type( start ) {
		start = qi::lit( "matrix" ) > *( qi::char_ - ( qi::lit( "[" ) | qi::lit( ")" ) | qi::lit( "," ) ) ) >
				-( qi::lit( "[" ) > ( ( mFloatParser % qi::no_skip[qi::char_( ' ', ',' )] ) % ';' ) > qi::lit( "]" ) );
	}

	qi::rule<Iterator, parser::Matrix<Number>(), Skipper> start;
};

template <typename Iterator, typename Number>
struct FlowParser : public qi::grammar<Iterator, parser::Matrix<Number>(), Skipper> {
	MatrixParser<Iterator, Number> mMatrixParser;

	FlowParser() : FlowParser::base_type( start ) {
		start = *(qi::char_ -(qi::lit("{"))) > qi::lit("{") > mMatrixParser > qi::lit("}");
	}

	qi::rule<Iterator, parser::Matrix<Number>(), Skipper> start;
};

template <typename Iterator, typename Number>
struct InvariantParser : public qi::grammar<Iterator, parser::Matrix<Number>(), Skipper> {
	MatrixParser<Iterator, Number> mMatrixParser;

	InvariantParser() : InvariantParser::base_type( start ) {
		start =
			  qi::lexeme[( qi::lit( "i" ) | qi::lit( "I" ) ) > qi::lit( "nvariant" )] > qi::lit( "=" ) > mMatrixParser;
	}

	qi::rule<Iterator, parser::Matrix<Number>(), Skipper> start;
};

template <typename Iterator, typename Number>
struct GuardParser : public qi::grammar<Iterator, parser::Matrix<Number>(), Skipper> {
	MatrixParser<Iterator, Number> mMatrixParser;

	GuardParser() : GuardParser::base_type( start ) {
		start = qi::lexeme[( qi::lit( "g" ) | qi::lit( "G" ) ) > qi::lit( "uard" )] > qi::lit( "=" ) > mMatrixParser;
	}

	qi::rule<Iterator, parser::Matrix<Number>(), Skipper> start;
};

template <typename Iterator, typename Number>
struct ResetParser : public qi::grammar<Iterator, parser::Matrix<Number>(), Skipper> {
	MatrixParser<Iterator, Number> mMatrixParser;

	ResetParser() : ResetParser::base_type( start ) {
		start = qi::lexeme[( qi::lit( "r" ) | qi::lit( "R" ) ) > qi::lit( "eset" )] > qi::lit( "=" ) > mMatrixParser;
	}

	qi::rule<Iterator, parser::Matrix<Number>(), Skipper> start;
};

} // namespace
} // namespace

