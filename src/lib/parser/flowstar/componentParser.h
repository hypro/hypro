#pragma once

#define BOOST_SPIRIT_USE_PHOENIX_V3

namespace hypro {
namespace parser {

	template<typename Iterator, typename Number>
	struct transitionParser : qi::grammar<Iterator, std::vector<Transition<Number>*>(symbol_table const&), Skipper>
	{
		LocationManager<Number>& mLocationManager = LocationManager<Number>::getInstance();

		transitionParser() : transitionParser::base_type( start ) {
			using qi::on_error;
	        using qi::fail;
	        using ascii::char_;
	        using ascii::string;
	        using namespace qi::labels;

	        using px::construct;
	        using px::val;
	        using namespace qi;

			start = qi::lexeme["jumps"] > qi::lit('{') > (*jump(qi::_r1))[qi::_val = px::bind( &transitionParser<Iterator, Number>::createTransitions, px::ref(*this), qi::_1)] >qi::lit('}');
			jump = edge(qi::_r1);// > *guard > *reset;
			edge = (simpleEdge(qi::_r1) | twoLineEdge(qi::_r1));
			simpleEdge = (qi::lazy(qi::_r1) > qi::lexeme["->"] > qi::lazy(qi::_r1))[ qi::_val = px::bind(&transitionParser<Iterator, Number>::createEdge, px::ref(*this), qi::_1, qi::_2)];
			twoLineEdge = (qi::skip(qi::blank)[qi::lexeme["start"] > qi::lazy(qi::_r1)] > qi::eol >
							qi::skip(qi::blank)[qi::lexeme["end"] > qi::lazy(qi::_r1)])[ qi::_val = px::bind(&transitionParser<Iterator, Number>::createEdge, px::ref(*this), qi::_1, qi::_2)];
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

		qi::rule<Iterator, std::vector<Transition<Number>*>(symbol_table const&), Skipper> start;
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

		std::vector<Transition<Number>*> createTransitions(const std::vector<std::pair<unsigned, unsigned>>& _transitions) {
			std::vector<Transition<Number>*> transitions;
			for(const auto& transitionPair : _transitions) {
				Transition<Number>* tmp = new Transition<Number>(
										mLocationManager.location(transitionPair.first),
										mLocationManager.location(transitionPair.second));
				transitions.push_back(tmp);
				mLocationManager.location(transitionPair.first)->addTransition(tmp);
			}
			return transitions;
		}
	};

	template <typename Iterator, typename Number>
	struct modeParser
	    : qi::grammar<Iterator, std::pair<std::string, Location<Number>*>(symbol_table const&, unsigned const&), Skipper>
	{
		LocationManager<Number>& mLocationManager = LocationManager<Number>::getInstance();
		odeParser<Iterator> mOdeParser;
		constraintParser<Iterator> mConstraintParser;

		modeParser() : modeParser::base_type( start ) {
			using qi::on_error;
	        using qi::fail;
	        using ascii::char_;
	        using ascii::string;
	        using namespace qi::labels;

	        using px::construct;
	        using px::val;
	        using namespace qi;

	        start = (name > qi::lit('{') > flow(qi::_r1, qi::_r2) > -(invariant(qi::_r1, qi::_r2)) > qi::lit('}'))[ qi::_val = px::bind( &modeParser<Iterator,Number>::createLocation, px::ref(*this), qi::_1, qi::_2, qi::_3)];

			name = qi::lexeme[ (qi::alpha | qi::char_("~!@$%^&*_+=<>.?/-")) > *(qi::alnum | qi::char_("~!@$%^&*_+=<>.?/-"))];
			flow = *qi::space > qi::lexeme["poly ode 1"] > *qi::space > qi::lit('{') > *qi::space > qi::skip(qi::blank)[(mOdeParser(qi::_r1, qi::_r2) % qi::eol)][qi::_val = px::bind( &modeParser<Iterator, Number>::createFlow, px::ref(*this), qi::_1 )] > *qi::space > qi::lit('}');
			invariant = *qi::space > qi::lexeme["inv"] > *qi::space > qi::lit('{') > *qi::space > (mConstraintParser(qi::_r1, qi::_r2) % qi::eol)[qi::_val = px::bind( &modeParser<Iterator, Number>::createInvariant, px::ref(*this), qi::_1)] > *qi::space > qi::lit('}');

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

		qi::rule<Iterator, std::pair<std::string, Location<Number>*>(symbol_table const&, unsigned const&), Skipper> start;
		qi::rule<Iterator, std::string()> name;
		qi::rule<Iterator, matrix_t<double>(symbol_table const&, unsigned const&)> flow;
		qi::rule<Iterator, matrix_t<double>(symbol_table const&, unsigned const&)> invariant;

		matrix_t<Number> createFlow( const std::vector<std::pair<unsigned, vector_t<double>>>& _in ) {
			assert(!_in.empty());
			matrix_t<double> res = matrix_t<double>(_in.begin()->second.size()-1, _in.begin()->second.size());
			std::cout << "Flow is a " << res.rows() << " by " << res.cols() << " matrix." << std::endl;
 			for(const auto& pair : _in) {
 				assert(pair.second.rows() == res.cols());
 				std::cout << "Row " << pair.first << " = " << pair.second.transpose() << std::endl;
				res.row(pair.first) << pair.second.transpose();
			}

			std::cout << "Created flow: " << std::endl;
			std::cout << res << std::endl;

			// Temporary, until Number template has been propagated fully.
			return convertMatToFloatT<Number>(res);
		}

		matrix_t<Number> createInvariant( const std::vector<std::vector<vector_t<double>>>& _constraints ) {
			unsigned size = 0;
			for(const auto constraintVector : _constraints){
				for(const auto constraint : constraintVector) {
					++size;
				}
			}
			matrix_t<double> res = matrix_t<double>(size, _constraints.begin()->begin()->rows() );
			unsigned rowCnt = 0;
			for(const auto constraintVector : _constraints){
				for(const auto constraint : constraintVector) {
					res.row(rowCnt) = constraint;
					++rowCnt;
				}
			}
			return convertMatToFloatT<Number>(res);
		}

		std::pair<std::string, Location<Number>*> createLocation(const std::string& _name, const matrix_t<Number>& _flow, const boost::optional<matrix_t<Number>>& _invariant) {
			if(_invariant) {
				Location<Number>* tmp = mLocationManager.create(_flow);
				matrix_t<Number> invariantMat = matrix_t<Number>(_invariant->rows(), _invariant->cols()-1);
				invariantMat = _invariant->block(0,0,_invariant->rows(), _invariant->cols()-1);
				vector_t<Number> constants = _invariant->col(_invariant->cols()-1);
				tmp->setInvariant(invariantMat, constants);
				return std::make_pair(_name, tmp );
			}
			return std::make_pair(_name, mLocationManager.create(_flow));
		}
	};

} // namespace parser
} // namespace hypro