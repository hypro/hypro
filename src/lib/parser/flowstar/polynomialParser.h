#pragma once

#define BOOST_SPIRIT_USE_PHOENIX_V3

namespace hypro {
namespace parser {

	template <typename Iterator>
	struct variableParser
	    : qi::grammar<Iterator, std::vector<std::string>(), Skipper>
	{
		px::function<ErrorHandler> errorHandler;

		variableParser() : variableParser::base_type( start, "variableParser" ) {
			varName = qi::lexeme[ (qi::alpha | qi::char_("~!@$%^&*_+=<>.?/-")) > *(qi::alnum | qi::char_("~!@$%^&*_+=<>.?/-"))];
			start = (varName % ',');

			start.name("variableVector");
			varName.name("singleVariable");

			qi::on_error<qi::fail>( start, errorHandler(qi::_1, qi::_2, qi::_3, qi::_4));
		}

		qi::rule<Iterator, std::vector<std::string>(), Skipper> start;
		qi::rule<Iterator, std::string(), Skipper> varName;
	};

	template <typename Iterator>
	struct monomialParser
	    : qi::grammar<Iterator, std::vector<unsigned>(symbol_table const&)>
	{
		px::function<ErrorHandler> errorHandler;

	    monomialParser()
	    : monomialParser::base_type(start, "monomialParser")
	    {
	    	using qi::on_error;
	        using qi::fail;

	        start = (var(qi::_r1) % '*')[qi::_val = px::bind( &monomialParser<Iterator>::printMonomial, px::ref(*this), qi::_1)];
	        var = qi::skip(qi::blank)[qi::lazy(qi::_r1)];

	        start.name("monomial");
	        var.name("variable");

	        qi::on_error<qi::fail>( start, errorHandler(qi::_1, qi::_2, qi::_3, qi::_4));
	    }
	    qi::rule<Iterator, std::vector<unsigned>(symbol_table const&)> start;
	    qi::rule<Iterator, unsigned(symbol_table const&)> var;

	    std::vector<unsigned> printMonomial( const std::vector<unsigned>& _in ) {
	    	//std::cout << "Parsed monomial ";
	    	//for(const auto& item : _in)
	    	//	std::cout << item << " ";
//
	    	//std::cout << std::endl;
	    	return _in;
	    }
	};

	template<typename Iterator>
	struct polynomialParser
		: qi::grammar<Iterator, vector_t<double>(symbol_table const&, unsigned const&)>
	{
		monomialParser<Iterator> monomial;
		px::function<ErrorHandler> errorHandler;

		polynomialParser() : polynomialParser::base_type( start, "polynomialParser" )
		{
			using qi::on_error;
	        using qi::fail;

			term = (nonconstant(qi::_r1, qi::_r2) | constant(qi::_r1, qi::_r2));
			constant = qi::skip(qi::blank)[ qi::double_ ][qi::_val = px::bind(&polynomialParser<Iterator>::createConstantTermMap, px::ref(*this), qi::_1, qi::_r2)];
			nonconstant = qi::skip(qi::blank)[(-(qi::double_ >> qi::lit('*')) >> monomial(qi::_r1) )[qi::_val = px::bind(&polynomialParser<Iterator>::createTermMap, px::ref(*this), qi::_1, qi::_2)]];
			start = qi::skip(qi::blank)[(term(qi::_r1, qi::_r2) % '+')][qi::_val = px::bind(&polynomialParser<Iterator>::createLinearPolynomial, px::ref(*this), qi::_1, qi::_r2)];

			start.name("polynomial");
			constant.name("const polynomial");
			nonconstant.name("nonconstant polynomial");
			term.name("term");

			qi::on_error<qi::fail>( start, errorHandler(qi::_1, qi::_2, qi::_3, qi::_4));
		}

		qi::rule<Iterator, std::pair<unsigned, double>(symbol_table const&, unsigned const&)> constant;
		qi::rule<Iterator, std::pair<unsigned, double>(symbol_table const&, unsigned const&)> nonconstant;
		qi::rule<Iterator, vector_t<double>(symbol_table const&, unsigned const&)> start;
		qi::rule<Iterator, std::pair<unsigned, double>(symbol_table const&, unsigned const&)> term;

		std::pair<unsigned, double> createConstantTermMap( double _in, unsigned _dim) {
			//std::cout << "Found constant term with coefficient " << _in << " mapping to dimension " << _dim << std::endl;
			return std::make_pair(_dim, _in);
		}

		std::pair<unsigned, double> createTermMap(const boost::optional<double>& _coeff, const std::vector<unsigned>& _in ) {
			std::pair<unsigned,double> coefficentMap;
			assert(_in.size() == 1 ); // currently we only support linear polynomials

			if(_coeff)
				coefficentMap = std::make_pair(_in.at(0), *_coeff);
			else
				coefficentMap = std::make_pair(_in.at(0), 1.0);

			//std::cout << "Found linear term with coefficient " << coefficentMap.second << " mapping to dimension " << coefficentMap.first << std::endl;
			return coefficentMap;
		}

		vector_t<double> createLinearPolynomial(const std::vector<std::pair<unsigned,double>>& _in, unsigned _dim) {
			vector_t<double> res = vector_t<double>::Zero(_dim+1);
			//std::cout << "Maximal dimension is " << _dim << std::endl;
			//std::cout << "Size: " << _in.size() << std::endl;

			//std::cout << "Create constraint row: ";
			for(const auto& pair : _in) {
				assert(pair.first < res.size());
				//std::cout << pair.first << " -> " << pair.second << std::endl;
				res(pair.first) += pair.second;
			}
			//std::cout << res.transpose() << std::endl;
			return res;
		}
	};

	template<typename Iterator>
	struct odeParser : qi::grammar<Iterator, std::pair<unsigned, vector_t<double>>(symbol_table const&, unsigned const&)>
	{
		polynomialParser<Iterator> mPolynomial;
		px::function<ErrorHandler> errorHandler;

		odeParser() : odeParser::base_type( start, "odeParser" ) {
			using qi::on_error;
	        using qi::fail;

			start = qi::skip(qi::blank)[(qi::lazy(qi::_r1) > qi::lit("'") > qi::lit("=") > mPolynomial(qi::_r1, qi::_r2))[qi::_val = px::bind( &odeParser<Iterator>::createRow, px::ref(*this), qi::_1, qi::_2 )]];
			start.name("flow ode");

			qi::on_error<qi::fail>( start, errorHandler(qi::_1, qi::_2, qi::_3, qi::_4));
		}

		qi::rule<Iterator, std::pair<unsigned, vector_t<double>>(symbol_table const&, unsigned const&)> start;

		std::pair<unsigned, vector_t<double>> createRow( const unsigned& _d, const vector_t<double>& _row ) {
			return std::make_pair(_d, _row);
		}
	};

	template<typename Iterator>
	struct resetParser : qi::grammar<Iterator, std::pair<unsigned, matrix_t<double>>(symbol_table const&, unsigned const&)>
	{
		polynomialParser<Iterator> mPolynomial;
		px::function<ErrorHandler> errorHandler;

		resetParser() : resetParser::base_type( start, "resetParser" ) {
			using qi::on_error;
	        using qi::fail;

			start = qi::skip(qi::blank)[(qi::lazy(qi::_r1) > qi::lit("'") > qi::lit(":=") > mPolynomial(qi::_r1, qi::_r2))[qi::_val = px::bind( &resetParser<Iterator>::createRow, px::ref(*this), qi::_1, qi::_2 )]];
			start.name("reset assignment");

			qi::on_error<qi::fail>( start, errorHandler(qi::_1, qi::_2, qi::_3, qi::_4));
		}

		qi::rule<Iterator, std::pair<unsigned, matrix_t<double>>(symbol_table const&, unsigned const&)> start;

		std::pair<unsigned, matrix_t<double>> createRow( const unsigned& _d, const vector_t<double>& _row ) {
			return std::make_pair(_d, _row.transpose());
		}
	};

	enum RELATION {LESS,LEQ,EQ,GEQ, GREATER};

	template<typename Iterator, typename Number>
	struct singleVariableConstraintParser : qi::grammar<Iterator, std::pair<unsigned, std::vector<matrix_t<Number>>>(symbol_table const&, unsigned const&)>
	{
		polynomialParser<Iterator> polynomial;
		px::function<ErrorHandler> errorHandler;

		singleVariableConstraintParser() : singleVariableConstraintParser::base_type( start, "singleVariableConstraintParser" ) {
			using qi::on_error;
	        using qi::fail;

			start = qi::skip(qi::blank)[( interval(qi::_r1, qi::_r2) | assignment(qi::_r1, qi::_r2) )];
			assignment = qi::skip(qi::blank)[(qi::lazy(qi::_r1) > relationSymbol > polynomial(qi::_r1, qi::_r2))[qi::_val = px::bind( &singleVariableConstraintParser<Iterator,Number>::createPairFromPoly, px::ref(*this), qi::_1, qi::_2, qi::_3 )]];
			relationSymbol = (qi::lexeme["<="][qi::_val = RELATION::LEQ]
							| qi::lexeme[">="][qi::_val = RELATION::GEQ]
							| qi::lit('=')[qi::_val = RELATION::EQ]);
			interval = qi::skip(qi::blank)[(qi::lazy(qi::_r1) >> qi::lexeme["in"] > qi::lit('[') > qi::double_ > qi::lit(',') > qi::double_ > qi::lit(']'))[qi::_val = px::bind( &singleVariableConstraintParser<Iterator,Number>::createPairFromInterval, px::ref(*this), qi::_1, qi::_2, qi::_3, qi::_r2 )]];
			start.name("singleVarConstraint");
			relationSymbol.name("relationSymbol");
			assignment.name("singleVarConstraint assignment");
			interval.name("singleVarConstraint interval");

			qi::on_error<qi::fail>( start, errorHandler(qi::_1, qi::_2, qi::_3, qi::_4));
		}

		qi::rule<Iterator, std::pair<unsigned, std::vector<matrix_t<Number>>>(symbol_table const&, unsigned const&)> start;
		qi::rule<Iterator, RELATION()> relationSymbol;
		qi::rule<Iterator, std::pair<unsigned, std::vector<matrix_t<Number>>>(symbol_table const&, unsigned const&)> interval;
		qi::rule<Iterator, std::pair<unsigned, std::vector<matrix_t<Number>>>(symbol_table const&, unsigned const&)> assignment;

		std::pair<unsigned, std::vector<matrix_t<Number>>> createPairFromPoly( const unsigned& _d, const RELATION& _rel, const vector_t<double>& _constraint) {
			std::vector<matrix_t<Number>> res;
			// convert to Number and transpose to create a row.
			matrix_t<Number> newRhs = convert<double,Number>(_constraint.transpose());
			assert(newRhs.rows() == 1);
			//std::cout << "create constraint for dimension " << _d << std::endl;
			assert(_d < newRhs.cols()-1);
			switch(_rel){
				case RELATION::EQ: {
					matrix_t<Number> resLower = matrix_t<Number>::Zero(1, newRhs.cols());
					matrix_t<Number> resUpper = matrix_t<Number>::Zero(1, newRhs.cols());
					resLower(0,_d) = -1;
					resLower = resLower + newRhs;
					resUpper(0,_d) = 1;
					resUpper = resUpper - newRhs;
					res.emplace_back(resLower);
					res.emplace_back(resUpper);
					//std::cout << "Created row from =: " << resLower << std::endl;
					//std::cout << "Created row from =: " << resUpper << std::endl;
					break;
				}
				case RELATION::GEQ: {
					matrix_t<Number> resRow = matrix_t<Number>::Zero(1, newRhs.cols());
					resRow(0,_d) = -1;
					resRow = resRow + newRhs;
					//std::cout << "GEQ: lhs:" << _d << " >= " << newRhs << std::endl;
					res.emplace_back(resRow);
					//std::cout << "Created row from >=: " << resRow << std::endl;
					break;
				}
				case RELATION::LEQ: {
					matrix_t<Number> resRow= matrix_t<Number>::Zero(1, newRhs.cols());
					resRow(0,_d) = 1;
					resRow = resRow - newRhs;
					res.emplace_back(resRow);
					//std::cout << "Created row from <=: " << resRow << std::endl;
					break;
				}
				default:{
					assert(false);
					break;
				}
			}
			return std::make_pair(_d, res);
		}

		std::pair<unsigned, std::vector<matrix_t<Number>>> createPairFromInterval( const unsigned& _d, const double& _lower, const double& _upper, unsigned _dimension ) {
			std::vector<matrix_t<Number>> res;
			//std::cout << __func__ << ": passed dimension: " << _dimension << std::endl;
			matrix_t<Number> lower = matrix_t<Number>::Zero(1,_dimension+1);
			matrix_t<Number> upper = matrix_t<Number>::Zero(1,_dimension+1);
			lower(0,_d) = -1;
			lower(0,_dimension) = carl::convert<double,Number>(_lower);
			upper(0,_d) = 1;
			upper(0,_dimension) = -carl::convert<double,Number>(_upper);
			res.emplace_back(lower);
			res.emplace_back(upper);

			return std::make_pair(_d, res);
		}
	};

	/**
	 * @brief Creates a matrix representing the parsed constraint.
	 * @details The matrix is augmented by a column (the last one), which represents the constant parts.
	 */
	template<typename Iterator, typename Number>
	struct constraintParser : qi::grammar<Iterator, std::vector<matrix_t<Number>>(symbol_table const&, unsigned const&)>
	{
		polynomialParser<Iterator> mPolynomial;
		px::function<ErrorHandler> errorHandler;

		constraintParser() : constraintParser::base_type( start, "constraintParser" ) {
			using qi::on_error;
	        using qi::fail;

			start = qi::skip(qi::blank)[(interval(qi::_r1, qi::_r2) | inequation(qi::_r1, qi::_r2))];
			inequation = qi::skip(qi::blank)[(mPolynomial(qi::_r1, qi::_r2) > relationSymbol > mPolynomial(qi::_r1, qi::_r2))[qi::_val = px::bind( &constraintParser<Iterator,Number>::createRow, px::ref(*this), qi::_1, qi::_2, qi::_3 )]];
			relationSymbol = (qi::lexeme["<="][qi::_val = RELATION::LEQ]
							| qi::lexeme[">="][qi::_val = RELATION::GEQ]
							| qi::lit('=')[qi::_val = RELATION::EQ]);
			interval = qi::skip(qi::blank)[(qi::lazy(qi::_r1) >> qi::lexeme["in"] > qi::lit('[') > qi::double_ > qi::lit(',') > qi::double_ > qi::lit(']'))[qi::_val = px::bind( &constraintParser<Iterator,Number>::createIntervalConstraints, px::ref(*this), qi::_1, qi::_2, qi::_3, qi::_r2 )]];

			start.name("constraint");
			inequation.name("polynomial constraint");
			relationSymbol.name("relation");
			interval.name("interval constraint");

			qi::on_error<qi::fail>( start, errorHandler(qi::_1, qi::_2, qi::_3, qi::_4));
		}

		qi::rule<Iterator, std::vector<matrix_t<Number>>(symbol_table const&, unsigned const&)> start;
		qi::rule<Iterator, RELATION()> relationSymbol;
		qi::rule<Iterator, std::vector<matrix_t<Number>>(symbol_table const&, unsigned const&)> inequation;
		qi::rule<Iterator, std::vector<matrix_t<Number>>(symbol_table const&, unsigned const&)> interval;

		std::vector<matrix_t<Number>> createRow(const vector_t<double>& _lhs, RELATION _rel, const vector_t<double>& _rhs) {
			std::vector<matrix_t<Number>> res;
			// convert to Number and transpose to create a row.
			matrix_t<Number> newLhs = convert<double,Number>(_lhs.transpose());
			matrix_t<Number> newRhs = convert<double,Number>(_rhs.transpose());
			assert(newLhs.rows() == 1 && newLhs.cols() == _lhs.rows());
			assert(newRhs.rows() == 1 && newRhs.cols() == _rhs.rows());
			assert(newLhs.cols() == newRhs.cols());
			switch(_rel){
				case RELATION::EQ: {
					matrix_t<Number> resLower = matrix_t<Number>(1, newLhs.cols());
					matrix_t<Number> resUpper = matrix_t<Number>(1, newLhs.cols());
					resLower.row(0) = (newLhs-newRhs);
					resUpper.row(0) = -1*(newLhs)+newRhs;
					res.emplace_back(resLower);
					res.emplace_back(resUpper);

					//std::cout << "Created row from =: " << resLower << std::endl;
					//std::cout << "Created row from =: " << resUpper << std::endl;
					return res;
				}
				case RELATION::GEQ: {
					matrix_t<Number> resRow = matrix_t<Number>(1, newLhs.cols());
					//std::cout << "GEQ: lhs:" << newLhs << " >= " << newRhs << std::endl;
					resRow.row(0) = -1*(newLhs)+newRhs;
					res.emplace_back(resRow);
					//std::cout << "Created row from >=: " << resRow << std::endl;
					return res;
				}
				case RELATION::LEQ: {
					matrix_t<Number> resRow= matrix_t<Number>(1, newLhs.cols());
					resRow.row(0) = newLhs-newRhs;
					res.emplace_back(resRow);
					//std::cout << "Created row from <=: " << resRow << std::endl;
					return res;
				}
				default:{
					assert(false);
				}
			}
			return res;
		}

		std::vector<matrix_t<Number>> createIntervalConstraints(unsigned _varIndex, double _lower, double _upper, unsigned _dimension) {
			std::vector<matrix_t<Number>> res;
			matrix_t<Number> resLower = matrix_t<Number>::Zero(1,_dimension+1);
			matrix_t<Number> resUpper = matrix_t<Number>::Zero(1,_dimension+1);
			resLower(0,_varIndex) = -1;
			resLower(0,_dimension) = carl::convert<double,Number>(_lower);
			resUpper(0,_varIndex) = 1;
			resUpper(0,_dimension) = -carl::convert<double,Number>(_upper);
			res.emplace_back(resLower);
			res.emplace_back(resUpper);
			//std::cout << "Created row from interval: " << resLower << std::endl;
			//std::cout << "Created row from interval: " << resUpper << std::endl;
			return res;
		}
	};

	template<typename Iterator, typename Number>
	struct discreteConstraintParser : qi::grammar<Iterator, std::pair<unsigned, carl::Interval<Number>>(symbol_table const&)>
	{
		polynomialParser<Iterator> mPolynomial;
		px::function<ErrorHandler> errorHandler;

		discreteConstraintParser() : discreteConstraintParser::base_type( start, "discreteConstraintParser" ) {
			using qi::on_error;
	        using qi::fail;

			start = qi::skip(qi::blank)[(interval(qi::_r1) | inequation(qi::_r1))];
			inequation = qi::skip(qi::blank)[( lhsVar(qi::_r1) | rhsVar(qi::_r1) )];
			lhsVar = qi::skip(qi::blank)[ ((qi::lazy(qi::_r1)) > relationSymbol > qi::double_) [qi::_val = px::bind( &discreteConstraintParser<Iterator, Number>::createInterval, px::ref(*this), qi::_1, qi::_2, qi::_3, false )]];
			rhsVar = qi::skip(qi::blank)[ (qi::double_ > relationSymbol > (qi::lazy(qi::_r1))) [qi::_val = px::bind( &discreteConstraintParser<Iterator, Number>::createInterval, px::ref(*this), qi::_3, qi::_2, qi::_1, true )]];
			relationSymbol = (qi::lexeme["<="][qi::_val = RELATION::LEQ]
							| qi::lexeme[">="][qi::_val = RELATION::GEQ]
							| qi::lit('=')[qi::_val = RELATION::EQ]);
			interval = qi::skip(qi::blank)[(qi::lazy(qi::_r1) >> qi::lexeme["in"] > qi::lit('[') > qi::double_ > qi::lit(',') > qi::double_ > qi::lit(']'))[qi::_val = px::bind( &discreteConstraintParser<Iterator, Number>::createIntervalConstraints, px::ref(*this), qi::_1, qi::_2, qi::_3 )]];

			start.name("constraint");
			inequation.name("polynomial constraint");
			lhsVar.name("inequation variable left");
			rhsVar.name("inequation variable right");
			relationSymbol.name("relation");
			interval.name("interval constraint");

			qi::on_error<qi::fail>( start, errorHandler(qi::_1, qi::_2, qi::_3, qi::_4));
		}

		qi::rule<Iterator, std::pair<unsigned, carl::Interval<Number>>(symbol_table const&)> start;
		qi::rule<Iterator, RELATION()> relationSymbol;
		qi::rule<Iterator, std::pair<unsigned, carl::Interval<Number>>(symbol_table const&)> inequation;
		qi::rule<Iterator, std::pair<unsigned, carl::Interval<Number>>(symbol_table const&)> lhsVar;
		qi::rule<Iterator, std::pair<unsigned, carl::Interval<Number>>(symbol_table const&)> rhsVar;
		qi::rule<Iterator, std::pair<unsigned, carl::Interval<Number>>(symbol_table const&)> interval;

		std::pair<unsigned, carl::Interval<Number>> createInterval(const unsigned& _lhs, RELATION _rel, double& _rhs, bool _invert) {
			std::pair<unsigned, carl::Interval<Number>> res;
			res.first = _lhs;
			switch(_rel){
				case RELATION::EQ: {
					res.second = carl::Interval<Number>(carl::convert<double,Number>(_rhs));
					return res;
				}
				case RELATION::GEQ: {
					res.second = carl::Interval<Number>(carl::convert<double,Number>(_rhs));
					if(_invert){
						res.second.setLowerBoundType(carl::BoundType::INFTY);
					} else {
						res.second.setUpperBoundType(carl::BoundType::INFTY);
					}
					return res;
				}
				case RELATION::LEQ: {
					res.second = carl::Interval<Number>(carl::convert<double,Number>(_rhs));
					if(_invert){
						res.second.setUpperBoundType(carl::BoundType::INFTY);
					} else {
						res.second.setLowerBoundType(carl::BoundType::INFTY);
					}
					return res;
				}
				default:{
					assert(false);
				}
			}
			return res;
		}

		std::pair<unsigned, carl::Interval<Number>> createIntervalConstraints(unsigned _varIndex, double _lower, double _upper) {
			std::pair<unsigned, carl::Interval<Number>> res;
			res.first = _varIndex;
			res.second = carl::Interval<Number>(carl::convert<double,Number>(_lower), carl::convert<double,Number>(_upper));
			return res;
		}
	};


} // namespace
} // namespace
