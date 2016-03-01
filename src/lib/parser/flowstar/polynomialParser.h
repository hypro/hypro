#pragma once

#define BOOST_SPIRIT_USE_PHOENIX_V3

namespace hypro {
namespace parser {

	namespace spirit = boost::spirit;
	namespace qi = boost::spirit::qi;
	namespace ascii = boost::spirit::ascii;
	namespace px = boost::phoenix;

	using symbol_table = qi::symbols<char, unsigned>;
	typedef spirit::istream_iterator BaseIteratorType;
	typedef spirit::line_pos_iterator<BaseIteratorType> PositionIteratorType;
	typedef PositionIteratorType Iterator;
	typedef qi::space_type Skipper;

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
		: qi::grammar<Iterator, std::vector<double>(symbol_table const&, unsigned const&)>
	{
		monomialParser<Iterator> monomial;

		polynomialParser() : polynomialParser::base_type( linearPolynomial )
		{
			term = (qi::double_ > -(qi::skip(qi::blank)[qi::lit('*') > monomial(qi::_r1)]))[qi::_val = px::bind(&polynomialParser<Iterator>::createTermMap, px::ref(*this), qi::_1, qi::_2, qi::_r2)];
			linearPolynomial = qi::skip(qi::blank)[(term(qi::_r1, qi::_r2) % '+')][qi::_val = px::bind(&polynomialParser<Iterator>::createLinearPolynomial, px::ref(*this), qi::_1, qi::_r2)];
		}

		qi::rule<Iterator, std::vector<double>(symbol_table const&, unsigned const&)> linearPolynomial;
		qi::rule<Iterator, std::pair<unsigned, double>(symbol_table const&, unsigned const&)> term;

		std::pair<unsigned, double> createTermMap(const double& _coeff,  boost::optional<std::vector<unsigned>>& _in, unsigned _dim) {
			std::pair<unsigned,double> coefficentMap;
			std::cout << "Ping" << std::endl;

			if(_in) { // the term was not constant
				assert(_in->size() == 1 ); // currently we only support linear polynomials
				coefficentMap = std::make_pair(_in->at(0), _coeff);
				std::cout << "Found linear term with coefficient " << coefficentMap.second << " mapping to dimension " << coefficentMap.first << std::endl;
			} else { // term is constant
				// determine symbol table size
				coefficentMap = std::make_pair(_dim, _coeff);
				std::cout << "Found linear term with coefficient " << coefficentMap.second << " mapping to dimension " << coefficentMap.first << std::endl;
			}
			return coefficentMap;
		}

		std::vector<double> createLinearPolynomial(const std::vector<std::pair<unsigned,double>>& _in, unsigned _dim) {
			std::vector<double> res(_dim+1, 0.0);
			std::cout << "Maximal dimension is " << _dim << std::endl;
			std::cout << "Size: " << _in.size() << std::endl;

			std::cout << "Create constraint row: ";
			for(const auto& pair : _in) {
				assert(pair.first < res.size());
				std::cout << pair.first << " -> " << pair.second << std::endl;
				res[pair.first] += pair.second;
			}
			for(const auto& entry : res)
				std::cout << entry <<  " ";

			std::cout << std::endl;
			return res;
		}
	};

	template<typename Iterator>
	struct odeParser : qi::grammar<Iterator, std::pair<unsigned, std::vector<double>>(symbol_table const&, unsigned const&)>
	{
		polynomialParser<Iterator> mPolynomial;

		odeParser() : odeParser::base_type( start ) {
			start = qi::skip(qi::blank)[(qi::lazy(qi::_r1) > qi::lit("'") > qi::lit("=") > mPolynomial(qi::_r1, qi::_r2))[qi::_val = px::bind( &odeParser<Iterator>::createRow, px::ref(*this), qi::_1, qi::_2 )]];
		}

		qi::rule<Iterator, std::pair<unsigned, std::vector<double>>(symbol_table const&, unsigned const&)> start;

		std::pair<unsigned, std::vector<double>> createRow( const unsigned& _d, const std::vector<double>& _row ) {
			return std::make_pair(_d, _row);
		}
	};

	enum RELATION {LESS,LEQ,EQ,GEQ, GREATER};

	template<typename Iterator>
	struct constraintParser : qi::grammar<Iterator, std::vector<std::pair<unsigned, std::vector<double>>>(symbol_table const&, unsigned const&)>
	{
		polynomialParser<Iterator> mPolynomial;

		constraintParser() : constraintParser::base_type( start ) {
			start = qi::lazy(qi::_r1) > relationSymbol > mPolynomial(qi::_r1, qi::_r2);
			relationSymbol = (qi::lexeme["<="][qi::_val = RELATION::LEQ]
							| qi::lexeme[">="][qi::_val = RELATION::GEQ]
							| qi::lit('=')[qi::_val = RELATION::EQ]
							| qi::lit("<")[qi::_val = RELATION::LESS]
							| qi::lit(">")[qi::_val = RELATION::GREATER]);
		}

		qi::rule<Iterator, std::vector<std::pair<unsigned, std::vector<double>>>(symbol_table const&, unsigned const&) > start;
		qi::rule<Iterator, RELATION()> relationSymbol;
	};


} // namespace
} // namespace