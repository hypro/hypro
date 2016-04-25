#pragma once

#define BOOST_SPIRIT_USE_PHOENIX_V3

namespace hypro {
namespace parser {

	template<typename Iterator, typename Number>
	struct transitionParser : qi::grammar<Iterator, std::set<Transition<Number>*>(symbol_table const&, symbol_table const&, symbol_table const&, unsigned const&, unsigned const&), Skipper>
	{
		LocationManager<Number>& mLocationManager = LocationManager<Number>::getInstance();
		constraintParser<Iterator, Number> constraint;
		singleVariableConstraintParser<Iterator, Number> singleVariableConstraint;
		resetParser<Iterator> variableReset;
		aggregation_ mAggregation;
		px::function<ErrorHandler> errorHandler;
		std::vector<std::pair<unsigned, matrix_t<Number>>> mDiscreteGuards;
		std::vector<matrix_t<Number>> mContinuousGuards;
		std::map<unsigned, matrix_t<Number>> mContinuousResets;
		std::map<unsigned, matrix_t<Number>> mDiscreteResets;

		transitionParser() : transitionParser::base_type( start ) {
			using qi::on_error;
	        using qi::fail;

			start = qi::lexeme["jumps"] > qi::lit('{') > (*jump(qi::_r1, qi::_r2, qi::_r3, qi::_r4, qi::_r5)) > qi::lit('}');
			jump = (edge(qi::_r1) > -guard(qi::_r2, qi::_r3, qi::_r4, qi::_r5) > -reset(qi::_r2, qi::_r3, qi::_r4, qi::_r5) > -agg > -timed)[qi::_val = px::bind( &transitionParser<Iterator, Number>::createTransition, px::ref(*this), qi::_1, qi::_2, qi::_3, qi::_r4, qi::_r5)];
			edge = (simpleEdge(qi::_r1) | twoLineEdge(qi::_r1));
			simpleEdge = (qi::lazy(qi::_r1) > qi::lexeme["->"] > qi::lazy(qi::_r1))[ qi::_val = px::bind(&transitionParser<Iterator, Number>::createEdge, px::ref(*this), qi::_1, qi::_2)];
			twoLineEdge = (qi::skip(qi::blank)[qi::lexeme["start"] > qi::lazy(qi::_r1)] > qi::eol >
							qi::skip(qi::blank)[qi::lexeme["end"] > qi::lazy(qi::_r1)])[ qi::_val = px::bind(&transitionParser<Iterator, Number>::createEdge, px::ref(*this), qi::_1, qi::_2)];
			guard = qi::lexeme["guard"] > *qi::blank > qi::lit('{') > *qi::blank > (*(continuousGuard(qi::_r1, qi::_r3) | discreteGuard(qi::_r2,qi::_r4))) > *qi::blank > qi::lit('}');
			continuousGuard = constraint(qi::_r1,qi::_r2)[px::bind(&transitionParser<Iterator,Number>::addContinuousGuard, px::ref(*this), qi::_1)];
			discreteGuard = singleVariableConstraint(qi::_r1,qi::_r2)[px::bind(&transitionParser<Iterator,Number>::addDiscreteGuard, px::ref(*this), qi::_1)];
			reset = qi::lexeme["reset"] > *qi::blank > qi::lit('{') > *qi::blank > (* ( continuousReset(qi::_r1, qi::_r3) | discreteReset(qi::_r2, qi::_r4) )) > *qi::blank > qi::lit('}');
			continuousReset = variableReset(qi::_r1, qi::_r2)[px::bind(&transitionParser<Iterator,Number>::addContinuousReset, px::ref(*this), qi::_1)];
			discreteReset = variableReset(qi::_r1, qi::_r2)[px::bind(&transitionParser<Iterator,Number>::addDiscreteReset, px::ref(*this), qi::_1)];
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

		qi::rule<Iterator, std::set<Transition<Number>*>(symbol_table const&, symbol_table const&, symbol_table const&, unsigned const&, unsigned const&), Skipper> start;
		qi::rule<Iterator, Transition<Number>*(symbol_table const&, symbol_table const&, symbol_table const&, unsigned const&, unsigned const&), Skipper> jump;
		qi::rule<Iterator, std::pair<unsigned, unsigned>(symbol_table const&), Skipper> edge;
		qi::rule<Iterator, std::pair<unsigned, unsigned>(symbol_table const&), Skipper> simpleEdge;
		qi::rule<Iterator, std::pair<unsigned, unsigned>(symbol_table const&)> twoLineEdge;
		qi::rule<Iterator, qi::unused_type(symbol_table const&, symbol_table const&, unsigned const&, unsigned const&)> guard;
		qi::rule<Iterator, qi::unused_type(symbol_table const&, unsigned const&)> continuousGuard;
		qi::rule<Iterator, qi::unused_type(symbol_table const&, unsigned const&)> discreteGuard;
		qi::rule<Iterator, qi::unused_type(symbol_table const&, symbol_table const&, unsigned const&, unsigned const&)> reset;
		qi::rule<Iterator, qi::unused_type(symbol_table const&, unsigned const&)> continuousReset;
		qi::rule<Iterator, qi::unused_type(symbol_table const&, unsigned const&)> discreteReset;
		qi::rule<Iterator, Aggregation()> agg;
		qi::rule<Iterator, double()> timed;

		void cleanup() {
			mDiscreteGuards.clear();
			mContinuousGuards.clear();
			mContinuousResets.clear();
			mDiscreteResets.clear();
		}

		std::pair<unsigned, unsigned> createEdge(unsigned start, unsigned target) {
			//std::cout << "Found transition from " << start << " to " << target << std::endl;
			return std::make_pair(start, target);
		}

		void addContinuousGuard(const std::vector<matrix_t<Number>>& _constraints) {
			for(const auto& matrix : _constraints){
				assert(matrix.rows() == 1);
				mContinuousGuards.push_back(matrix);
			}
		}

		void addDiscreteGuard(const std::pair<unsigned, std::vector<matrix_t<Number>>>& _constraints) {
			for(const auto& matrix : _constraints.second){
				assert(matrix.rows() == 1);
				mDiscreteGuards.emplace_back(_constraints.first, matrix);
			}
		}

		void addContinuousReset(const std::pair<unsigned, matrix_t<double>>& _constraint) {
			assert(_constraint.second.rows() == 1);
			mContinuousResets[_constraint.first] = convert<double,Number>(_constraint.second);
		}

		void addDiscreteReset(const std::pair<unsigned, matrix_t<double>>& _constraint) {
			assert(_constraint.second.rows() == 1);
			mDiscreteResets[_constraint.first] = convert<double,Number>(_constraint.second);
		}

		Transition<Number>* createTransition(const std::pair<unsigned, unsigned>& _transition, const boost::optional<Aggregation>& _aggregation, const boost::optional<double>& _triggerTime, unsigned _dim, unsigned _discreteDim) {
			Transition<Number>* res = new Transition<Number>(
									mLocationManager.location(_transition.first),
									mLocationManager.location(_transition.second));

			// setting guard
			if(mContinuousGuards.size() + mDiscreteGuards.size() > 0) {
				typename Transition<Number>::Guard g;
				matrix_t<Number> matr = matrix_t<Number>(mContinuousGuards.size(), _dim);
				vector_t<Number> vec = vector_t<Number>(mContinuousGuards.size());
				unsigned rowCnt = 0;
				for(const auto& row : mContinuousGuards) {
					assert(row.rows() == 1);
					matr.row(rowCnt) = row.block(0,0,1,row.cols()-1);
					vec(rowCnt) = -row(0,_dim);
					++rowCnt;
				}
				g.mat = matr;
				g.vec = vec;
				// handle discrete guards
				g.discreteOffset = _dim;
				for(const auto& guardPair : mDiscreteGuards) {
					matrix_t<Number> reducedGuard = matrix_t<Number>(1,_discreteDim-_dim+1);
					reducedGuard = guardPair.second.block(0,_dim,1,_discreteDim-_dim+1);
					g.discreteGuard.emplace_back(VariablePool::getInstance().carlVarByIndex(guardPair.first), reducedGuard);
				}

				res->setGuard(g);
			}

			// setting reset
			typename Transition<Number>::Reset r;
			r.mat = matrix_t<Number>::Identity(_dim, _dim);
			r.vec = vector_t<Number>::Zero(_dim);
			r.discreteOffset = _dim;
			r.discreteMat = matrix_t<Number>::Identity(_discreteDim-_dim, _discreteDim-_dim);
			r.discreteVec = vector_t<Number>::Zero(_discreteDim-_dim);
			if(mContinuousResets.size() + mDiscreteResets.size() > 0) {
				matrix_t<Number> matr = matrix_t<Number>::Identity(_dim,_dim);
				vector_t<Number> vec = vector_t<Number>::Zero(_dim);
				for(const auto& resetPair : mContinuousResets){
					matr.row(resetPair.first) = resetPair.second.block(0,0,1,_dim);
					vec(resetPair.first) = resetPair.second(0,_dim);
				}
				r.mat = matr;
				r.vec = vec;
				matrix_t<Number> discreteMat = matrix_t<Number>::Identity(_discreteDim-_dim,_discreteDim-_dim);
				vector_t<Number> discreteVec = vector_t<Number>::Zero(_discreteDim-_dim);
				//std::cout << "Identity reset: " << discreteMat << std::endl;
				for(const auto& resetPair : mDiscreteResets){
					//std::cout << resetPair.second << " should fit in " << discreteMat << std::endl;
					//std::cout << "Block start 0," << _dim << ", size: 1," << _discreteDim-_dim << std::endl;
					//std::cout << "RowNum:" << resetPair.first-_dim << std::endl;
					discreteMat.row(resetPair.first-_dim) = resetPair.second.block(0,_dim,1,_discreteDim-_dim);
					discreteVec(resetPair.first-_dim) = resetPair.second(0,_discreteDim);
				}
				r.discreteMat = discreteMat;
				r.discreteVec = discreteVec;
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
			//std::cout << "Parsed Transition: " << *res << std::endl;
			cleanup();
			return res;
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
	    : qi::grammar<Iterator, std::pair<std::string, Location<Number>*>(symbol_table const&, symbol_table const&, unsigned const&, unsigned const&), Skipper>
	{
		LocationManager<Number>& mLocationManager = LocationManager<Number>::getInstance();
		odeParser<Iterator> mOdeParser;
		constraintParser<Iterator, Number> constraint;
		singleVariableConstraintParser<Iterator, Number> singleVariableConstraint;
		discreteConstraintParser<Iterator,Number> discreteConstraint;
		px::function<ErrorHandler> errorHandler;
		std::vector<matrix_t<Number>> mContinuousInvariants;
		std::vector<std::pair<unsigned, matrix_t<Number>>> mDiscreteInvariants;

		modeParser() : modeParser::base_type( start ) {
			using qi::on_error;
	        using qi::fail;

	        start = (name > qi::lit('{') > flow(qi::_r1, qi::_r3) > -(invariant(qi::_r1, qi::_r2, qi::_r3, qi::_r4)) > qi::lit('}'))[ qi::_val = px::bind( &modeParser<Iterator,Number>::createLocation, px::ref(*this), qi::_1, qi::_2, qi::_r4)];

			name = qi::lexeme[ (qi::alpha | qi::char_("~!@$%^&*_+=<>.?/-")) > *(qi::alnum | qi::char_("~!@$%^&*_+=<>.?/-"))];
			flow = *qi::space > qi::lexeme["poly ode 1"] > *qi::space > qi::lit('{') > *qi::space > qi::skip(qi::blank)[(mOdeParser(qi::_r1, qi::_r2) % qi::eol)][qi::_val = px::bind( &modeParser<Iterator, Number>::createFlow, px::ref(*this), qi::_1 )] > *qi::space > qi::lit('}');
			invariant = *qi::space > qi::lexeme["inv"] > *qi::space > qi::lit('{') > *qi::space > ((continuousInvariant(qi::_r1, qi::_r3) | discreteInvariant(qi::_r2, qi::_r4)) % qi::eol) > *qi::space > qi::lit('}');
			continuousInvariant = constraint(qi::_r1, qi::_r2)[px::bind( &modeParser<Iterator,Number>::addContinuousInvariant, px::ref(*this), qi::_1)];
			discreteInvariant = singleVariableConstraint(qi::_r1, qi::_r2)[px::bind( &modeParser<Iterator,Number>::addDiscreteInvariant, px::ref(*this), qi::_1)];

			start.name("mode");
			name.name("location name");
			flow.name("flow");
			invariant.name("invariant");

			qi::on_error<qi::fail>( start, errorHandler(qi::_1, qi::_2, qi::_3, qi::_4));
		}

		qi::rule<Iterator, std::pair<std::string, Location<Number>*>(symbol_table const&, symbol_table const&, unsigned const&, unsigned const&), Skipper> start;
		qi::rule<Iterator, std::string()> name;
		qi::rule<Iterator, matrix_t<Number>(symbol_table const&, unsigned const&)> flow;
		qi::rule<Iterator, qi::unused_type(symbol_table const&, symbol_table const&, unsigned const&, unsigned const&)> invariant;
		qi::rule<Iterator, qi::unused_type(symbol_table const&, unsigned const&)> continuousInvariant;
		qi::rule<Iterator, qi::unused_type(symbol_table const&, unsigned const&)> discreteInvariant;

		void cleanup() {
			mContinuousInvariants.clear();
			mDiscreteInvariants.clear();
		}

		void addContinuousInvariant(const std::vector<matrix_t<Number>>& _constraints) {
			for(const auto& matrix : _constraints){
				assert(matrix.rows() == 1);
				mContinuousInvariants.push_back(matrix);
			}
		}

		void addDiscreteInvariant(const std::pair<unsigned, std::vector<matrix_t<Number>>>& _constraints) {
			for(const auto& matrix : _constraints.second){
				assert(matrix.rows() == 1);
				std::cout << "Parsed invariant for dimension " << _constraints.first << " = " << matrix << std::endl;
				mDiscreteInvariants.emplace_back(_constraints.first, matrix);
			}
		}

		matrix_t<Number> createFlow( const std::vector<std::pair<unsigned, vector_t<double>>>& _in ) {
			assert(!_in.empty());
			// matrix template with additional row of zeroes for constants, no need for rows for discrete variables, as their flow is 0
			unsigned rowCnt = _in.begin()->second.rows();
			//std::cout << "In-size: " << _in.size() << ", cols: " << _in.begin()->second.rows() << std::endl;
			assert(_in.size() == rowCnt-1);
			matrix_t<double> res = matrix_t<double>::Zero(rowCnt, rowCnt);
			//std::cout << "Flow is a " << res.rows() << " by " << res.cols() << " matrix." << std::endl;
 			for(const auto& pair : _in) {
 				assert(pair.second.rows() == res.cols());
 				assert(pair.first < res.rows());
 				//std::cout << "Row " << pair.first << " = " << pair.second.transpose() << std::endl;
				res.row(pair.first) << pair.second.transpose();
			}
			// Temporary, until Number template has been propagated fully.
			return convert<double,Number>(res);
		}

		std::pair<std::string, Location<Number>*> createLocation(const std::string& _name, const matrix_t<Number>& _flow, unsigned _discreteDim) {
			assert(_flow.rows() == _flow.cols());
			if(mDiscreteInvariants.size() + mContinuousInvariants.size() > 0) {
				Location<Number>* tmp = mLocationManager.create(_flow);
				std::cout << "creating location " << tmp->id() << std::endl;
				std::cout << "flow: " << tmp->flow() << std::endl;
				typename Location<Number>::Invariant inv;
				matrix_t<Number> invariantMat = matrix_t<Number>(mContinuousInvariants.size(), _flow.cols()-1);
				vector_t<Number> constants = vector_t<Number>(mContinuousInvariants.size());
				unsigned rowCnt = 0;
				for(const auto& invariantConstaint : mContinuousInvariants) {
					assert(invariantConstaint.rows() == 1);
					invariantMat.row(rowCnt) = invariantConstaint.block(0,0,1,_flow.cols()-1);
					constants(rowCnt) = -invariantConstaint(0,_flow.cols()-1);
					++rowCnt;
				}
				inv.mat = invariantMat;
				inv.vec = constants;
				std::cout << "set continuous invariant to " << invariantMat << std::endl;
				for(const auto& invariantConstaintPair : mDiscreteInvariants) {
					assert(invariantConstaintPair.second.rows() == 1);
					// resize
					std::cout << "new number of cols: " << _discreteDim-_flow.cols()+2 << std::endl;
					matrix_t<Number> resizedInvariant = matrix_t<Number>(1, _discreteDim-_flow.cols()+2);
					resizedInvariant = invariantConstaintPair.second.block(0, _flow.cols()-1, 1, _discreteDim-_flow.cols()+2);
					inv.discreteInvariant.emplace_back(VariablePool::getInstance().carlVarByIndex(invariantConstaintPair.first), resizedInvariant);
					std::cout << "added discrete invariant for var " << VariablePool::getInstance().carlVarByIndex(invariantConstaintPair.first) << ": " << resizedInvariant << std::endl;
				}
				inv.discreteOffset = _flow.cols()-1;
				tmp->setInvariant(inv);

				// clear local storage
				cleanup();
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
			outBackend = (qi::lexeme["gnuplot"] | qi::lexeme["matlab"]) > shape > outdimensions(qi::_r1)[px::bind( &settingsParser::setPlotDimensions, px::ref(*this), qi::_1 )];
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
 		void setPlotDimensions(const std::vector<unsigned>& _dimensions){
 			assert(_dimensions.size() <= 2);
 			mLocalSettings.plotDimensions = _dimensions;
 		}

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
