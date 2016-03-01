#pragma once

#define BOOST_SPIRIT_USE_PHOENIX_V3

namespace hypro {
namespace parser {

	template<typename Iterator>
	struct transitionParser : qi::grammar<Iterator, std::vector<std::pair<unsigned, unsigned>>(symbol_table const&), Skipper>
	{
		transitionParser() : transitionParser::base_type( start ) {
			using qi::on_error;
	        using qi::fail;
	        using ascii::char_;
	        using ascii::string;
	        using namespace qi::labels;

	        using px::construct;
	        using px::val;
	        using namespace qi;

			start = qi::lexeme["jumps"] > qi::lit('{') > +(jump(qi::_r1)) >qi::lit('}');
			jump = edge(qi::_r1);// > *guard > *reset;
			edge = (simpleEdge(qi::_r1) | twoLineEdge(qi::_r1));
			simpleEdge = (qi::lazy(qi::_r1) > qi::lexeme["->"] > qi::lazy(qi::_r1))[ qi::_val = px::bind(&transitionParser<Iterator>::createEdge, px::ref(*this), qi::_1, qi::_2)];
			twoLineEdge = (qi::skip(qi::blank)[qi::lexeme["start"] > qi::lazy(qi::_r1)] > qi::eol >
							qi::skip(qi::blank)[qi::lexeme["end"] > qi::lazy(qi::_r1)])[ qi::_val = px::bind(&transitionParser<Iterator>::createEdge, px::ref(*this), qi::_1, qi::_2)];
			guard = qi::lexeme["guard"] > qi::lit('{') > qi::lit('}');
			reset = qi::lexeme["reset"] > qi::lit('{') > qi::lit('}');

			qi::on_error<qi::fail>
			(
			    jump
			  , std::cout <<
			  	px::val("TransitionParser: Syntax error. Expecting ")
	        	<< _4
		        << px::val(" here: \"")
		        << construct<std::string>(_3, _2)
		        << px::val("\"")
		        << std::endl
			);
		}

		qi::rule<Iterator, std::vector<std::pair<unsigned, unsigned>>(symbol_table const&), Skipper> start;
		qi::rule<Iterator, std::pair<unsigned, unsigned>(symbol_table const&), Skipper> jump;
		qi::rule<Iterator, std::pair<unsigned, unsigned>(symbol_table const&), Skipper> edge;
		qi::rule<Iterator, std::pair<unsigned, unsigned>(symbol_table const&), Skipper> simpleEdge;
		qi::rule<Iterator, std::pair<unsigned, unsigned>(symbol_table const&)> twoLineEdge;
		qi::rule<Iterator> guard;
		qi::rule<Iterator> reset;

		std::pair<unsigned, unsigned> createEdge(unsigned start, unsigned target) {
			std::cout << "Found transition from " << start << " to " << target << std::endl;
			return std::make_pair(start, target);
		}
	};

	template <typename Iterator>
	struct modeParser
	    : qi::grammar<Iterator, std::string(symbol_table const&, unsigned const&), Skipper>
	{
		odeParser<Iterator> mOdeParser;

		modeParser() : modeParser::base_type( start ) {
			using qi::on_error;
	        using qi::fail;
	        using ascii::char_;
	        using ascii::string;
	        using namespace qi::labels;

	        using px::construct;
	        using px::val;
	        using namespace qi;

			name = qi::lexeme[ (qi::alpha | qi::char_("~!@$%^&*_+=<>.?/-")) > *(qi::alnum | qi::char_("~!@$%^&*_+=<>.?/-"))];
			interval %= qi::lit('[') > qi::double_ > qi::lit(',') > qi::double_ > qi::lit(']');
			flow = *qi::space > qi::lexeme["poly ode 1"] > *qi::space > qi::lit('{') > *qi::space > qi::skip(qi::blank)[(mOdeParser(qi::_r1, qi::_r2) % qi::eol)][qi::_val = px::bind( &modeParser<Iterator>::createFlow, px::ref(*this), qi::_1 )] > *qi::space > qi::lit('}');
			singleInvariant = qi::skip(qi::blank)[qi::lazy(qi::_r1) > qi::lexeme["in"] > interval];
			invariant = *qi::space > qi::lexeme["inv"] > *qi::space > qi::lit('{') > *qi::space > (singleInvariant(qi::_r1, qi::_r2) % qi::eol) > *qi::space > qi::lit('}');

			start = name[qi::_val =  px::bind( &modeParser<Iterator>::printName, px::ref(*this), qi::_1)] > qi::lit('{') > flow(qi::_r1, qi::_r2) > -(invariant(qi::_r1, qi::_r2)) > qi::lit('}');

			qi::on_error<qi::fail>
			(
			    start
			  , std::cout <<
			  	px::val("ModeParser: Syntax error. Expecting ")
	        	<< _4
		        << px::val(" here: \"")
		        << construct<std::string>(_3, _2)
		        << px::val("\"")
		        << std::endl
			);
		}

		qi::rule<Iterator, std::string(symbol_table const&, unsigned const&), Skipper> start;
		qi::rule<Iterator, std::string()> name;
		qi::rule<Iterator, matrix_t<double>(symbol_table const&, unsigned const&)> flow;

		qi::rule<Iterator> interval;
		qi::rule<Iterator, qi::unused_type(symbol_table const&, unsigned const&)> singleInvariant;
		qi::rule<Iterator, qi::unused_type(symbol_table const&, unsigned const&)> invariant;

		std::string printName(const std::string& _in) {
			std::cout << "Name: " << _in << std::endl;
			return _in;
		}

		matrix_t<double> createFlow( std::vector<std::pair<unsigned, std::vector<double>>> _in ) {
			assert(!_in.empty());
			matrix_t<double> res = matrix_t<double>(_in.size(), _in.begin()->second.size());
			for(const auto& pair : _in) {
				res.row(pair.first) = createVector(pair.second);
			}

			std::cout << "Created flow: " << std::endl;
			std::cout << res << std::endl;
			return res;
		}
	};

} // namespace parser
} // namespace hypro