#pragma once

#define BOOST_SPIRIT_USE_PHOENIX_V3

namespace hypro {
namespace parser {

	template <typename Iterator>
	struct variableParser
	    : qi::grammar<Iterator, std::vector<std::string>(), Skipper>
	{
		//px::function<ErrorHandler> errorHandler;

		variableParser() : variableParser::base_type( start, "variableParser" ) {
			varName = qi::lexeme[ (qi::alpha | qi::char_("~!@$%^&*_+=<>.?/-")) > *(qi::alnum | qi::char_("~!@$%^&*_+=<>.?/-"))];
			start = (varName % ',');

			start.name("variableVector");
			varName.name("singleVariable");

			//qi::on_error<qi::fail>( start, errorHandler(qi::_1, qi::_2, qi::_3, qi::_4));
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
	struct resetParser : qi::grammar<Iterator, std::pair<unsigned, vector_t<double>>(symbol_table const&, unsigned const&)>
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

		qi::rule<Iterator, std::pair<unsigned, vector_t<double>>(symbol_table const&, unsigned const&)> start;

		std::pair<unsigned, vector_t<double>> createRow( const unsigned& _d, const vector_t<double>& _row ) {
			return std::make_pair(_d, _row);
		}
	};

	enum RELATION {LESS,LEQ,EQ,GEQ, GREATER};

	template<typename Iterator>
	struct constraintParser : qi::grammar<Iterator, matrix_t<double>(symbol_table const&, unsigned const&)>
	{
		polynomialParser<Iterator> mPolynomial;
		px::function<ErrorHandler> errorHandler;

		constraintParser() : constraintParser::base_type( start, "constraintParser" ) {
			using qi::on_error;
	        using qi::fail;

			start = qi::skip(qi::blank)[(interval(qi::_r1, qi::_r2) | inequation(qi::_r1, qi::_r2))];
			inequation = qi::skip(qi::blank)[(mPolynomial(qi::_r1, qi::_r2) > relationSymbol > mPolynomial(qi::_r1, qi::_r2))[qi::_val = px::bind( &constraintParser<Iterator>::createRow, px::ref(*this), qi::_1, qi::_2, qi::_3 )]];
			relationSymbol = (qi::lexeme["<="][qi::_val = RELATION::LEQ]
							| qi::lexeme[">="][qi::_val = RELATION::GEQ]
							| qi::lit('=')[qi::_val = RELATION::EQ]);
			interval = qi::skip(qi::blank)[(qi::lazy(qi::_r1) >> qi::lexeme["in"] > qi::lit('[') > qi::double_ > qi::lit(',') > qi::double_ > qi::lit(']'))[qi::_val = px::bind( &constraintParser<Iterator>::createIntervalConstraints, px::ref(*this), qi::_1, qi::_2, qi::_3, qi::_r2 )]];

			start.name("constraint");
			inequation.name("polynomial constraint");
			relationSymbol.name("relation");
			interval.name("interval constraint");

			qi::on_error<qi::fail>( start, errorHandler(qi::_1, qi::_2, qi::_3, qi::_4));
		}

		qi::rule<Iterator, matrix_t<double>(symbol_table const&, unsigned const&)> start;
		qi::rule<Iterator, RELATION()> relationSymbol;
		qi::rule<Iterator, matrix_t<double>(symbol_table const&, unsigned const&)> inequation;
		qi::rule<Iterator, matrix_t<double>(symbol_table const&, unsigned const&)> interval;

		matrix_t<double> createRow(const vector_t<double>& _lhs, RELATION _rel, const vector_t<double>& _rhs) {
			switch(_rel){
				case RELATION::EQ: {
					matrix_t<double> res = matrix_t<double>(2, _lhs.rows());
					assert(_lhs.rows() == res.cols() && _rhs.rows() == res.cols());
					res.row(0) = (_lhs-_rhs);
					res.row(1) = -1*(_lhs)+_rhs;
					return res;
				}
				case RELATION::GEQ: {
					matrix_t<double> res = matrix_t<double>(1, _lhs.rows());
					assert(_lhs.rows() == res.cols() && _rhs.rows() == res.cols());
					//std::cout << "GEQ: lhs:" << _lhs << " >= " << _rhs << std::endl;
					res.row(0) = -1*(_lhs)+_rhs;
					return res;
				}
				case RELATION::LEQ: {
					matrix_t<double> res = matrix_t<double>(1, _lhs.rows());
					assert(_lhs.rows() == res.cols() && _rhs.rows() == res.cols());
					res.row(0) = _lhs-_rhs;
					return res;
				}
				default:{
					assert(false);
				}
			}
			return matrix_t<double>::Zero(1,1);
		}

		matrix_t<double> createIntervalConstraints(unsigned _varIndex, double _lower, double _upper, unsigned _dimension) {
			matrix_t<double> res = matrix_t<double>::Zero(2,_dimension+1);

			res(0,_varIndex) = -1;
			res(0,_dimension) = -_lower;
			res(1,_varIndex) = 1;
			res(1,_dimension) = _upper;
			return res;
		}
	};


} // namespace
} // namespace
