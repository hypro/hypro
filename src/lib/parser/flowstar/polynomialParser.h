#pragma once

#define BOOST_SPIRIT_USE_PHOENIX_V3

namespace hypro {
namespace parser {

	template <typename Iterator>
	struct variables
	    : qi::grammar<Iterator, std::vector<std::string>(), Skipper>
	{
		variables() : variables::base_type( start ) {
			varName = ( qi::lexeme[+qi::alnum] );
			start = (varName % ',');
		}

		qi::rule<Iterator, std::vector<std::string>(), Skipper> start;
		qi::rule<Iterator, std::string(), Skipper> varName;
	};

	template <typename Iterator>
	struct monomialParser
	    : qi::grammar<Iterator, std::vector<unsigned>(symbol_table const&)>
	{
	    monomialParser()
	    : monomialParser::base_type(query)
	    {
	        query = (var(qi::_r1) % '*')[qi::_val = px::bind( &monomialParser<Iterator>::printMonomial, px::ref(*this), qi::_1)];
	        var =  qi::skip(qi::blank)[qi::lazy(qi::_r1)];
	    }
	    qi::rule<Iterator, std::vector<unsigned>(symbol_table const&)> query;
	    qi::rule<Iterator, unsigned(symbol_table const&)> var;

	    std::vector<unsigned> printMonomial( const std::vector<unsigned>& _in ) {
	    	std::cout << "Parsed monomial ";
	    	for(const auto& item : _in)
	    		std::cout << item << " ";

	    	std::cout << std::endl;
	    	return _in;
	    }
	};

	template<typename Iterator>
	struct polynomialParser
		: qi::grammar<Iterator, vector_t<double>(symbol_table const&, unsigned const&)>
	{
		monomialParser<Iterator> monomial;

		polynomialParser() : polynomialParser::base_type( linearPolynomial )
		{
			using qi::on_error;
	        using qi::fail;
	        using ascii::char_;
	        using ascii::string;
	        using namespace qi::labels;

	        using px::construct;
	        using px::val;
	        using namespace qi;

			term = (nonconstant(qi::_r1, qi::_r2) | constant(qi::_r1, qi::_r2));
			constant = qi::skip(qi::blank)[ qi::double_ ][qi::_val = px::bind(&polynomialParser<Iterator>::createConstantTermMap, px::ref(*this), qi::_1, qi::_r2)];
			nonconstant = qi::skip(qi::blank)[(-(qi::double_ >> qi::lit('*')) >> monomial(qi::_r1) )[qi::_val = px::bind(&polynomialParser<Iterator>::createTermMap, px::ref(*this), qi::_1, qi::_2)]];
			linearPolynomial = qi::skip(qi::blank)[(term(qi::_r1, qi::_r2) % '+')][qi::_val = px::bind(&polynomialParser<Iterator>::createLinearPolynomial, px::ref(*this), qi::_1, qi::_r2)];

			qi::on_error<qi::fail>
			(
			    nonconstant
			  , std::cout <<
			  	px::val("Polynomial: Syntax error. Expecting ")
	        	<< _4
		        << px::val(" here: \"")
		        << construct<std::string>(_3, _2)
		        << px::val("\"")
		        << std::endl
			);
		}

		qi::rule<Iterator, std::pair<unsigned, double>(symbol_table const&, unsigned const&)> constant;
		qi::rule<Iterator, std::pair<unsigned, double>(symbol_table const&, unsigned const&)> nonconstant;
		qi::rule<Iterator, vector_t<double>(symbol_table const&, unsigned const&)> linearPolynomial;
		qi::rule<Iterator, std::pair<unsigned, double>(symbol_table const&, unsigned const&)> term;

		std::pair<unsigned, double> createConstantTermMap( double _in, unsigned _dim) {
			std::cout << "Found constant term with coefficient " << _in << " mapping to dimension " << _dim << std::endl;
			return std::make_pair(_dim, _in);
		}

		std::pair<unsigned, double> createTermMap(const boost::optional<double>& _coeff, const std::vector<unsigned>& _in ) {
			std::pair<unsigned,double> coefficentMap;
			assert(_in.size() == 1 ); // currently we only support linear polynomials

			if(_coeff)
				coefficentMap = std::make_pair(_in.at(0), *_coeff);
			else
				coefficentMap = std::make_pair(_in.at(0), 1.0);

			std::cout << "Found linear term with coefficient " << coefficentMap.second << " mapping to dimension " << coefficentMap.first << std::endl;
			return coefficentMap;
		}

		vector_t<double> createLinearPolynomial(const std::vector<std::pair<unsigned,double>>& _in, unsigned _dim) {
			vector_t<double> res = vector_t<double>::Zero(_dim+1);
			std::cout << "Maximal dimension is " << _dim << std::endl;
			std::cout << "Size: " << _in.size() << std::endl;

			std::cout << "Create constraint row: ";
			for(const auto& pair : _in) {
				assert(pair.first < res.size());
				std::cout << pair.first << " -> " << pair.second << std::endl;
				res(pair.first) += pair.second;
			}
			std::cout << res.transpose() << std::endl;
			return res;
		}
	};

	template<typename Iterator>
	struct odeParser : qi::grammar<Iterator, std::pair<unsigned, vector_t<double>>(symbol_table const&, unsigned const&)>
	{
		polynomialParser<Iterator> mPolynomial;

		odeParser() : odeParser::base_type( start ) {
			start = qi::skip(qi::blank)[(qi::lazy(qi::_r1) > qi::lit("'") > qi::lit("=") > mPolynomial(qi::_r1, qi::_r2))[qi::_val = px::bind( &odeParser<Iterator>::createRow, px::ref(*this), qi::_1, qi::_2 )]];
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

		resetParser() : resetParser::base_type( start ) {
			start = qi::skip(qi::blank)[(qi::lazy(qi::_r1) > qi::lit("'") > qi::lit(":=") > mPolynomial(qi::_r1, qi::_r2))[qi::_val = px::bind( &resetParser<Iterator>::createRow, px::ref(*this), qi::_1, qi::_2 )]];
		}

		qi::rule<Iterator, std::pair<unsigned, vector_t<double>>(symbol_table const&, unsigned const&)> start;

		std::pair<unsigned, vector_t<double>> createRow( const unsigned& _d, const vector_t<double>& _row ) {
			return std::make_pair(_d, _row);
		}
	};

	enum RELATION {LESS,LEQ,EQ,GEQ, GREATER};

	template<typename Iterator>
	struct constraintParser : qi::grammar<Iterator, std::vector<vector_t<double>>(symbol_table const&, unsigned const&)>
	{
		polynomialParser<Iterator> mPolynomial;

		constraintParser() : constraintParser::base_type( start ) {
			start = qi::skip(qi::blank)[(interval(qi::_r1, qi::_r2) | inequation(qi::_r1, qi::_r2))];
			inequation = qi::skip(qi::blank)[(mPolynomial(qi::_r1, qi::_r2) > relationSymbol > mPolynomial(qi::_r1, qi::_r2))[qi::_val = px::bind( &constraintParser<Iterator>::createRow, px::ref(*this), qi::_1, qi::_2, qi::_3 )]];
			relationSymbol = (qi::lexeme["<="][qi::_val = RELATION::LEQ]
							| qi::lexeme[">="][qi::_val = RELATION::GEQ]
							| qi::lit('=')[qi::_val = RELATION::EQ]);
			interval = qi::skip(qi::blank)[(qi::lazy(qi::_r1) >> qi::lexeme["in"] > qi::lit('[') > qi::double_ > qi::lit(',') > qi::double_ > qi::lit(']'))[qi::_val = px::bind( &constraintParser<Iterator>::createIntervalConstraints, px::ref(*this), qi::_1, qi::_2, qi::_3, qi::_r2 )]];
		}

		qi::rule<Iterator, std::vector<vector_t<double>>(symbol_table const&, unsigned const&)> start;
		qi::rule<Iterator, RELATION()> relationSymbol;
		qi::rule<Iterator, std::vector<vector_t<double>>(symbol_table const&, unsigned const&)> inequation;
		qi::rule<Iterator, std::vector<vector_t<double>>(symbol_table const&, unsigned const&)> interval;

		std::vector<vector_t<double>> createRow(const vector_t<double>& _lhs, RELATION _rel, const vector_t<double>& _rhs) {
			std::vector<vector_t<double>> res;
			switch(_rel){
				case RELATION::EQ: {
					vector_t<double> lhspace = (_lhs-_rhs);
					vector_t<double> uhspace = -1*(_lhs-_rhs);
					res.push_back(lhspace);
					res.push_back(uhspace);
					break;
				}
				case RELATION::GEQ: {
					vector_t<double> normalized = -1*(_lhs-_rhs);
					res.push_back(normalized);
					break;
				}
				case RELATION::LEQ: {
					vector_t<double> normalized = _lhs-_rhs;
					res.push_back(normalized);
					break;
				}
			}
			return res;
		}

		std::vector<vector_t<double>> createIntervalConstraints(unsigned _varIndex, double _lower, double _upper, unsigned _dimension) {
			std::vector<vector_t<double>> res;
			vector_t<double> lower = vector_t<double>::Zero(_dimension+1);
			vector_t<double> upper = vector_t<double>::Zero(_dimension+1);

			lower(_varIndex) = -1;
			lower(_dimension) = -_lower;
			upper(_varIndex) = 1;
			upper(_dimension) = _upper;
			res.push_back(lower);
			res.push_back(upper);
			return res;
		}
	};


} // namespace
} // namespace