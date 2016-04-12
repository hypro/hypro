#pragma once

#define BOOST_SPIRIT_USE_PHOENIX_V3

namespace hypro {
namespace parser {

	template<typename Iterator, typename Number>
	struct transitionParser : qi::grammar<Iterator, std::set<Transition<Number>*>(symbol_table const&, symbol_table const&, unsigned const&), Skipper>
	{
		LocationManager<Number>& mLocationManager = LocationManager<Number>::getInstance();
		constraintParser<Iterator> constraint;
		resetParser<Iterator> variableReset;
		aggregation_ mAggregation;
		px::function<ErrorHandler> errorHandler;

		transitionParser() : transitionParser::base_type( start ) {
			using qi::on_error;
	        using qi::fail;

			start = qi::lexeme["jumps"] > qi::lit('{') > (*jump(qi::_r1, qi::_r2, qi::_r3)) > qi::lit('}');
			jump = (edge(qi::_r1) > -guard(qi::_r2, qi::_r3) > -reset(qi::_r2, qi::_r3) > -agg > -timed)[qi::_val = px::bind( &transitionParser<Iterator, Number>::createTransition, px::ref(*this), qi::_1, qi::_2, qi::_3, qi::_4, qi::_5, qi::_r3)];
			edge = (simpleEdge(qi::_r1) | twoLineEdge(qi::_r1));
			simpleEdge = (qi::lazy(qi::_r1) > qi::lexeme["->"] > qi::lazy(qi::_r1))[ qi::_val = px::bind(&transitionParser<Iterator, Number>::createEdge, px::ref(*this), qi::_1, qi::_2)];
			twoLineEdge = (qi::skip(qi::blank)[qi::lexeme["start"] > qi::lazy(qi::_r1)] > qi::eol >
							qi::skip(qi::blank)[qi::lexeme["end"] > qi::lazy(qi::_r1)])[ qi::_val = px::bind(&transitionParser<Iterator, Number>::createEdge, px::ref(*this), qi::_1, qi::_2)];
			guard = qi::lexeme["guard"] > *qi::blank > qi::lit('{') > *qi::blank > (*constraint(qi::_r1, qi::_r2))[ qi::_val = px::bind( &transitionParser<Iterator,Number>::createGuardMatrix, px::ref(*this), qi::_1, qi::_r2 )] > *qi::blank > qi::lit('}');
			reset = qi::lexeme["reset"] > *qi::blank > qi::lit('{') > *qi::blank > (*variableReset(qi::_r1, qi::_r2))[ qi::_val = px::bind( &transitionParser<Iterator,Number>::createMatrix, px::ref(*this), qi::_1, qi::_r2 )] > *qi::blank > qi::lit('}');
			agg = qi::skip(qi::blank)[mAggregation > qi::lexeme["aggregation"] > -(qi::lit('{') > qi::lit('}'))];
			timed = qi::skip(qi::blank)[qi::lexeme["time"] > qi::double_];

			start.name("transitions");
			jump.name("transition");
			edge.name("edge");
			simpleEdge.name("simple edge");
			twoLineEdge.name("old notation edge");
			guard.name("guard");
			reset.name("reset");
			agg.name("aggregation properties");

			qi::on_error<qi::fail>( start, errorHandler(qi::_1, qi::_2, qi::_3, qi::_4));
		}

		qi::rule<Iterator, std::set<Transition<Number>*>(symbol_table const&, symbol_table const&, unsigned const&), Skipper> start;
		qi::rule<Iterator, Transition<Number>*(symbol_table const&, symbol_table const&, unsigned const&), Skipper> jump;
		qi::rule<Iterator, std::pair<unsigned, unsigned>(symbol_table const&), Skipper> edge;
		qi::rule<Iterator, std::pair<unsigned, unsigned>(symbol_table const&), Skipper> simpleEdge;
		qi::rule<Iterator, std::pair<unsigned, unsigned>(symbol_table const&)> twoLineEdge;
		qi::rule<Iterator, matrix_t<Number>(symbol_table const&, unsigned const&)> guard;
		qi::rule<Iterator, matrix_t<Number>(symbol_table const&, unsigned const&)> reset;
		qi::rule<Iterator, Aggregation()> agg;
		qi::rule<Iterator, double()> timed;

		std::pair<unsigned, unsigned> createEdge(unsigned start, unsigned target) {
			//std::cout << "Found transition from " << start << " to " << target << std::endl;
			return std::make_pair(start, target);
		}

		Transition<Number>* createTransition(const std::pair<unsigned, unsigned>& _transition, const boost::optional<matrix_t<Number>>& _guard, const boost::optional<matrix_t<Number>>& _reset, const boost::optional<Aggregation>& _aggregation, const boost::optional<double>& _triggerTime, unsigned _dim) {
			Transition<Number>* res = new Transition<Number>(
									mLocationManager.location(_transition.first),
									mLocationManager.location(_transition.second));

			// setting guard
			if(_guard) {
				typename Transition<Number>::Guard g;
				matrix_t<Number> matr = matrix_t<Number>(_guard->rows(), _guard->cols()-1);
				matr << _guard->block(0,0,_guard->rows(), _guard->cols()-1);
				vector_t<Number> vec = -_guard->col(_guard->cols()-1);
				g.mat = matr;
				g.vec = vec;
				res->setGuard(g);
			}

			// setting reset
			typename Transition<Number>::Reset r;
			if(_reset) {
				matrix_t<Number> matr = matrix_t<Number>(_reset->rows(), _reset->cols()-1);
				matr << _reset->block(0,0,_reset->rows(), _reset->cols()-1);
				vector_t<Number> vec = -_reset->col(_reset->cols()-1);
				r.mat = matr;
				r.vec = vec;
			} else {
				r.mat = matrix_t<Number>::Identity(_dim, _dim);
				r.vec = vector_t<Number>::Zero(_dim);
			}
			res->setReset(r);

			// set aggregation settings
			if(_aggregation){
				res->setAggregation(*_aggregation);
			}

			if(_triggerTime){
				res->setTriggerTime(carl::rationalize<Number>(*_triggerTime));
			}

			// update source location
			mLocationManager.location(_transition.first)->addTransition(res);
			return res;
		}

		matrix_t<Number> createGuardMatrix(const std::vector<std::vector<matrix_t<double>>>& _constraints, unsigned _dim) {
			matrix_t<double> res = matrix_t<double>(_constraints.size(), _dim+1 );
			unsigned rowCnt = 0;
			for(const auto constraintVec : _constraints){
				assert(constraintVec.size() == 1);
				res.row(rowCnt) = constraintVec.begin()->row(0);
				++rowCnt;
			}
			return convert<double,Number>(res);
		}

		matrix_t<Number> createMatrix(const std::vector<std::pair<unsigned, vector_t<double>>>& _assignments, unsigned _dim) {
			matrix_t<double> res = matrix_t<double>::Identity(_dim, _dim+1);
			for(const auto assignmentPair : _assignments){
				res.row(assignmentPair.first) = assignmentPair.second;
			}
			return convert<double,Number>(res);
		}
	};

	template <typename Iterator, typename Number>
	struct modeParser
	    : qi::grammar<Iterator, std::pair<std::string, Location<Number>*>(symbol_table const&, unsigned const&), Skipper>
	{
		LocationManager<Number>& mLocationManager = LocationManager<Number>::getInstance();
		odeParser<Iterator> mOdeParser;
		constraintParser<Iterator> constraint;
		px::function<ErrorHandler> errorHandler;

		modeParser() : modeParser::base_type( start ) {
			using qi::on_error;
	        using qi::fail;

	        start = (name > qi::lit('{') > flow(qi::_r1, qi::_r2) > -(invariant(qi::_r1, qi::_r2)) > qi::lit('}'))[ qi::_val = px::bind( &modeParser<Iterator,Number>::createLocation, px::ref(*this), qi::_1, qi::_2, qi::_3)];

			name = qi::lexeme[ (qi::alpha | qi::char_("~!@$%^&*_+=<>.?/-")) > *(qi::alnum | qi::char_("~!@$%^&*_+=<>.?/-"))];
			flow = *qi::space > qi::lexeme["poly ode 1"] > *qi::space > qi::lit('{') > *qi::space > qi::skip(qi::blank)[(mOdeParser(qi::_r1, qi::_r2) % qi::eol)][qi::_val = px::bind( &modeParser<Iterator, Number>::createFlow, px::ref(*this), qi::_1 )] > *qi::space > qi::lit('}');
			invariant = *qi::space > qi::lexeme["inv"] > *qi::space > qi::lit('{') > *qi::space > (constraint(qi::_r1, qi::_r2) % qi::eol)[qi::_val = px::bind( &modeParser<Iterator, Number>::createInvariant, px::ref(*this), qi::_1, qi::_r2)] > *qi::space > qi::lit('}');

			start.name("mode");
			name.name("location name");
			flow.name("flow");
			invariant.name("invariant");

			qi::on_error<qi::fail>( start, errorHandler(qi::_1, qi::_2, qi::_3, qi::_4));
		}

		qi::rule<Iterator, std::pair<std::string, Location<Number>*>(symbol_table const&, unsigned const&), Skipper> start;
		qi::rule<Iterator, std::string()> name;
		qi::rule<Iterator, matrix_t<Number>(symbol_table const&, unsigned const&)> flow;
		qi::rule<Iterator, matrix_t<Number>(symbol_table const&, unsigned const&)> invariant;

		matrix_t<Number> createFlow( const std::vector<std::pair<unsigned, vector_t<double>>>& _in ) {
			assert(!_in.empty());
			// matrix template with additional row of zeroes for constants
			matrix_t<double> res = matrix_t<double>::Zero(_in.begin()->second.size(), _in.begin()->second.size());
			//std::cout << "Flow is a " << res.rows() << " by " << res.cols() << " matrix." << std::endl;
 			for(const auto& pair : _in) {
 				assert(pair.second.rows() == res.cols());
 				//std::cout << "Row " << pair.first << " = " << pair.second.transpose() << std::endl;
				res.row(pair.first) << pair.second.transpose();
			}
			// Temporary, until Number template has been propagated fully.
			return convert<double,Number>(res);
		}

		matrix_t<Number> createInvariant( const std::vector<std::vector<matrix_t<double>>>& _constraints, unsigned _dim ) {
			matrix_t<double> res = matrix_t<double>(_constraints.size(), _dim+1 );
			unsigned rowCnt = 0;
			for(const auto constraintVec : _constraints){
				assert(constraintVec.size() == 1);
				res.row(rowCnt) = constraintVec.begin()->row(0);
				++rowCnt;
			}
			return convert<double,Number>(res);
		}

		std::pair<std::string, Location<Number>*> createLocation(const std::string& _name, const matrix_t<Number>& _flow, const boost::optional<matrix_t<Number>>& _invariant) {
			assert(_flow.rows() == _flow.cols());
			if(_invariant) {
				Location<Number>* tmp = mLocationManager.create(_flow);
				matrix_t<Number> invariantMat = matrix_t<Number>(_invariant->rows(), _invariant->cols()-1);
				invariantMat = _invariant->block(0,0,_invariant->rows(), _invariant->cols()-1);
				vector_t<Number> constants = -_invariant->col(_invariant->cols()-1);
				tmp->setInvariant(invariantMat, constants);
				return std::make_pair(_name, tmp );
			}
			return std::make_pair(_name, mLocationManager.create(_flow));
		}
	};

	template <typename Iterator, typename Number>
	struct settingsParser
	    : qi::grammar<Iterator, ReachabilitySettings<Number>(symbol_table const&),Skipper>
	{
		ReachabilitySettings<Number> mLocalSettings;
		px::function<ErrorHandler> errorHandler;

		settingsParser() : settingsParser::base_type( start ), mLocalSettings() {
			start = *(steps|order|time|jmpLimit|outFile|print|outBackend(qi::_r1)|remainder|cutoff|precision|precondition)[qi::_val = px::ref(mLocalSettings)];
			steps = ((qi::lexeme["fixed steps"] > qi::double_[px::bind( &settingsParser::setTimeStep, px::ref(*this), qi::_1)]) | (qi::lexeme["adaptive steps"] > qi::lit('{') > qi::lexeme["min"] > qi::int_ > qi::lit(',') > qi::lexeme["max"] > qi::int_ > qi::lit('}')) );
			order = ((qi::lexeme["fixed orders"] > qi::int_) | (qi::lexeme["adaptive orders"] > qi::lit('{') > qi::lexeme["min"] > qi::int_ > qi::lit(',') > qi::lexeme["max"] > qi::int_ > qi::lit('}')) );
			time = qi::lexeme["time"] > qi::double_[px::bind( &settingsParser::setTimeBound, px::ref(*this), qi::_1)];
			jmpLimit = qi::lexeme["max jumps"] > qi::int_[px::bind( &settingsParser::setJumpDepth, px::ref(*this), qi::_1)];
			outFile = qi::lexeme["output"] > filename [px::bind( &settingsParser::setFileName, px::ref(*this), qi::_1)];
			print = qi::lexeme["print"] > (qi::lexeme["on"] | qi::lexeme["off"]);
			outBackend = (qi::lexeme["gnuplot"] | qi::lexeme["matlab"]) > shape > outdimensions(qi::_r1);
			shape = (qi::lexeme["octagon"] | qi::lexeme["interval"]);
			outdimensions = (qi::lazy(qi::_r1) % ',');
			remainder = qi::lexeme["remainder estimation"] > constant;
			cutoff = qi::lexeme["cutoff"] > constant;
			precision = qi::lexeme["precision"] > constant;
			precondition = (qi::lexeme["QR"] | qi::lexeme["identity"]) > qi::lexeme["precondition"];
			filename = qi::lexeme[ (qi::alpha | qi::char_("~!@$%^&*_+=<>.?/-")) > *(qi::alnum | qi::char_("~!@$%^&*_+=<>.?/-"))];
			// placeholder for unused and unreadable numbers (temporary)
			constant = qi::lexeme[ *(qi::alnum | qi::char_("~!@$%^&*_+=<>.?/-")) ];

			start.name("settings");
			steps.name("step-size");
			order.name("Taylormodel order");
			time.name("local time horizon");
			jmpLimit.name("jump depth");
			outFile.name("output file name");
			print.name("print-flag");
			outBackend.name("print backend");
			shape.name("printed segment shape");
			outdimensions.name("printed dimensions");
			remainder.name("remainder estimation");
			cutoff.name("cutoff");
			precision.name("precision");
			precondition.name("precondition");
			filename.name("filename");
			constant.name("unreadable constant");

			qi::on_error<qi::fail>( start, errorHandler(qi::_1, qi::_2, qi::_3, qi::_4));
 		}

 		void setTimeStep(double _in){ mLocalSettings.timeStep = carl::rationalize<Number>(_in); }
 		void setTimeBound(double _in){ mLocalSettings.timeBound = carl::rationalize<Number>(_in); }
 		void setJumpDepth(int _in){ mLocalSettings.jumpDepth = _in; }
 		void setFileName(const std::string& _in){ mLocalSettings.fileName = _in; }

		qi::rule<Iterator, ReachabilitySettings<Number>(symbol_table const&), Skipper> start;
		qi::rule<Iterator, Skipper> steps;
		qi::rule<Iterator, Skipper> order;
		qi::rule<Iterator, Skipper> time;
		qi::rule<Iterator, Skipper> jmpLimit;
		qi::rule<Iterator, Skipper> outFile;
		qi::rule<Iterator, Skipper> print;
		qi::rule<Iterator, qi::unused_type(symbol_table const&), Skipper> outBackend;
		qi::rule<Iterator, Skipper> shape;
		qi::rule<Iterator, std::vector<unsigned>(symbol_table const&), Skipper> outdimensions;
		qi::rule<Iterator, Skipper> remainder;
		qi::rule<Iterator, Skipper> cutoff;
		qi::rule<Iterator, Skipper> precision;
		qi::rule<Iterator, Skipper> precondition;
		qi::rule<Iterator, std::string() ,Skipper> filename;
		qi::rule<Iterator, Skipper> constant;
	};

} // namespace parser
} // namespace hypro
