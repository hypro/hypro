
#pragma once

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

	struct variableName_ : qi::symbols<char, unsigned>{
		variableName_(){}
	};

	template <typename Iterator>
	struct MonomialParser : public qi::grammar<Iterator, parser::Monomial(), Skipper> {

		MonomialParser() : MonomialParser::base_type( start ) {
			variableName = spirit::lexeme[+( qi::alpha )];
			start = variableName >> *( qi::lit("*") > variableName ) ;
		}
		qi::rule<Iterator, std::string(), Skipper>  variableName;
		qi::rule<Iterator, parser::Monomial(), Skipper> start;
	};

	template <typename Iterator, typename Number>
	struct TermParser : public qi::grammar<Iterator, parser::Term<Number>(), Skipper> {
		MonomialParser<Iterator> mMonomialParser;

		TermParser() : TermParser::base_type( start ) {
			start = qi::double_ > -qi::lit("*") > mMonomialParser;
		}

		qi::rule<Iterator, parser::Term<Number>(), Skipper> start;
	};

	template <typename Iterator, typename Number>
	struct PolynomialParser : public qi::grammar<Iterator, parser::Polynomial<Number>(), Skipper> {
		TermParser<Iterator,Number> mTermParser;
		hypro::parser::variableName_& mTable;

		PolynomialParser() : PolynomialParser::base_type( start ) {
			start = qi::eps >> ( mTermParser % '+' ); // Note: Parsing into structs wíth only one member is not possible, thus the qi::eps
		}

		qi::rule<Iterator, parser::Polynomial<Number>(), Skipper> start;
	};


} // namespace
} // namespace