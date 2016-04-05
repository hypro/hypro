#pragma once

namespace hypro{
namespace parser{

	namespace spirit = boost::spirit;
	namespace qi = boost::spirit::qi;
	namespace ascii = boost::spirit::ascii;
	namespace px = boost::phoenix;
	namespace fs = boost::fusion;

	using symbol_table = qi::symbols<char, unsigned>;
	using BaseIteratorType = spirit::istream_iterator;
	using PositionIteratorType = spirit::line_pos_iterator<BaseIteratorType>;
	using Iterator = PositionIteratorType;

	template<typename Iterator>
	struct fsSkipper : public qi::grammar<Iterator> {

	    fsSkipper() : fsSkipper::base_type(skip) {
	        skip = qi::space | (qi::lit('#') >> *(qi::char_ - qi::eol) >> qi::eol);
	    }
	    qi::rule<Iterator> skip;
	};
	using Skipper = fsSkipper<Iterator>;

	struct ErrorHandler {
		template<typename> struct result { using type = qi::error_handler_result; };
		template<typename T1, typename T2, typename T3, typename T4>
		qi::error_handler_result operator()(T1 b, T2 e, T3 where, T4 const& what) const {
			auto line_start = spirit::get_line_start(b, where);
			auto line_end = std::find(where, e, '\n');
			std::string line(++line_start, line_end);

			std::cout << "Parsing error at " << spirit::get_line(where) << ":" << spirit::get_column(line_start, where);
			std::cout << " expected" << std::endl << "\t" << what.tag << ": " << what;
			std::cout << " but got" << std::endl << "\t\"" << std::string(where, line_end) << "\" in line " << spirit::get_line(where) << std::endl;
			//exit(1);
			return qi::fail;
		}
	};

} // namespace parser
} // namespace hypro

