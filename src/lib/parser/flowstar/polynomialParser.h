
#pragma once

#define BOOST_SPIRIT_USE_PHOENIX_V3

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

	template <typename Iterator>
	struct MonomialParser : public qi::grammar<Iterator, parser::Monomial(qi::symbols<char, unsigned>const &), Skipper> {

		MonomialParser() : MonomialParser::base_type( start ) {
			variableName = qi::raw[qi::lazy(qi::_r1)];
			start = variableName >> *( qi::lit("*") > variableName(qi::_r1) ) ;
		}
		qi::rule<Iterator, std::string(qi::symbols<char, unsigned>&), Skipper>  variableName;
		qi::rule<Iterator, parser::Monomial(qi::symbols<char, unsigned>&), Skipper> start;
	};

	template <typename Iterator, typename Number>
	struct TermParser : public qi::grammar<Iterator, parser::Term<Number>(qi::symbols<char, unsigned>const &), Skipper> {
		MonomialParser<Iterator> mMonomialParser;

		TermParser() : TermParser::base_type( start ) {
			start = qi::double_ > -qi::lit("*") > mMonomialParser(qi::_r1);
		}

		qi::rule<Iterator, parser::Term<Number>(qi::symbols<char, unsigned>&), Skipper> start;
	};

	template <typename Iterator, typename Number>
	struct PolynomialParser : public qi::grammar<Iterator, parser::Polynomial<Number>(qi::symbols<char, unsigned>const &), Skipper> {
		TermParser<Iterator,Number> mTermParser;

		PolynomialParser() : PolynomialParser::base_type( start ) {
			start = qi::eps >> ( mTermParser(qi::_r1) % '+' ); // Note: Parsing into structs with only one member is not possible, thus the qi::eps
		}

		qi::rule<Iterator, parser::Polynomial<Number>(qi::symbols<char, unsigned>&), Skipper> start;
	};


} // namespace
} // namespace