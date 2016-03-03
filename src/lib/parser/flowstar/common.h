#pragma once

namespace hypro{
namespace parser{

	namespace spirit = boost::spirit;
	namespace qi = boost::spirit::qi;
	namespace ascii = boost::spirit::ascii;
	namespace px = boost::phoenix;

	using symbol_table = qi::symbols<char, unsigned>;
	typedef spirit::istream_iterator BaseIteratorType;
	typedef spirit::line_pos_iterator<BaseIteratorType> PositionIteratorType;
	typedef PositionIteratorType Iterator;

	template<typename Iterator>
	struct fsSkipper : public qi::grammar<Iterator> {

	    fsSkipper() : fsSkipper::base_type(skip) {
	        skip = qi::space | (qi::lit('#') >> *(qi::char_ - qi::eol) >> qi::eol);
	    }
	    qi::rule<Iterator> skip;
	};

	typedef fsSkipper<Iterator> Skipper;

} // namespace parser
} // namespace hypro

