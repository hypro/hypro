/* 
 * This file holds component parsers which would pollute the main parser otherwise.
 * 
 * @file   componentParser.h
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 *
 * @since	2014-11-10
 * @version	2014-11-10
 */

#pragma once

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/support_line_pos_iterator.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/spirit/include/phoenix_object.hpp>
#include <boost/spirit/include/qi_real.hpp>
#include <string>
#include <carl/numbers/FLOAT_T.h>

namespace boost { namespace spirit { namespace traits { 
template<>
inline void scale(int exp, carl::FLOAT_T<mpfr_t>& r) {
	std::cout << __func__ << " exp: " << exp << " r: " << r << std::endl;
	if (exp >= 0)
		r *= carl::pow(carl::FLOAT_T<mpfr_t>(10), (unsigned)exp);
	else
		r /= carl::pow(carl::FLOAT_T<mpfr_t>(10), (unsigned)(-exp));
	std::cout << __func__ << " r: " << r << std::endl;
}
template<>
inline bool is_equal_to_one(const carl::FLOAT_T<mpfr_t>& value) {
	return value == 1;
}
}}}


namespace hypro{
namespace parser{
	
	namespace spirit = boost::spirit;    
	namespace qi = boost::spirit::qi;
	namespace ascii = boost::spirit::ascii;
	namespace phoenix = boost::phoenix;
	namespace fusion = boost::fusion;

	typedef spirit::istream_iterator BaseIteratorType;
	typedef spirit::line_pos_iterator<BaseIteratorType> PositionIteratorType;
	typedef PositionIteratorType Iterator;
	typedef qi::space_type Skipper;
	
	template<typename Number>
	struct FloatPolicies : qi::real_policies< Number > {
//		template <typename It, typename Attr>
//		static bool parse_nan(It&, It const&, Attr&) { return false; }
//		
//		template <typename It, typename Attr>
//		static bool parse_inf(It&, It const&, Attr&) { return false; }
//		template <typename Iterator, typename Attribute>
//        static bool parse_frac_n(Iterator& first, Iterator const& last, Attribute& attr)
//        {
//			carl::FLOAT_T<Number> tmp = qi::extract_uint<carl::FLOAT_T<Number>, 10, 1, -1, true>::call(first, last, attr);
//			std::cout << __func__ << " parsed: " << tmp << std::endl;
//            return qi::extract_uint<carl::FLOAT_T<Number>, 10, 1, -1, true>::call(first, last, attr);
//        }
	};
	
	template<typename Number>
	struct FloatParser : qi::real_parser<Number, FloatPolicies<Number> > {};
	
	template<typename Iterator, typename Number>
	struct MatrixParser : public qi::grammar<Iterator, parser::Matrix<Number>(), Skipper>
	{
		MatrixParser() : MatrixParser::base_type(start)
		{
			start =  qi::lit("matrix") > *(qi::char_-(qi::lit("[") | qi::lit(")") | qi::lit(","))) > -(qi::lit("[") > ((qi::double_ % qi::no_skip[qi::char_(' ',',')]) % ';') > qi::lit("]"));
		}

		qi::rule<Iterator,parser::Matrix<Number>(), Skipper> start;
	};
	
	template<typename Iterator>
	struct NameParser : public qi::grammar<Iterator, unsigned(), Skipper>
	{
		NameParser() : NameParser::base_type(start)
		{
			start =  qi::lexeme[(qi::lit("n") | qi::lit("N") ) > qi::lit("ame")] > qi::lit("=") > qi::uint_;
		}

		qi::rule<Iterator, unsigned(), Skipper> start;
	};
	
	template<typename Iterator>
	struct shortLocationParser : public qi::grammar<Iterator, unsigned(), Skipper>
	{
		shortLocationParser() : shortLocationParser::base_type(start)
		{
			start =  qi::lexeme[(qi::lit("l") | qi::lit("L") ) > qi::lit("ocation")] > qi::lit("=") > qi::uint_;
		}

		qi::rule<Iterator, unsigned(), Skipper> start;
	};
	
	template<typename Iterator, typename Number>
	struct FlowParser : public qi::grammar<Iterator, parser::Matrix<Number>(), Skipper>
	{
		MatrixParser<Iterator, Number> mMatrixParser;
		
		FlowParser() : FlowParser::base_type(start)
		{
			start =  qi::lexeme[(qi::lit("f") | qi::lit("F") ) > qi::lit("low")] > qi::lit("=") > mMatrixParser;
		}

		qi::rule<Iterator, parser::Matrix<Number>(), Skipper> start;
	};
	
	template<typename Iterator, typename Number>
	struct InvariantParser : public qi::grammar<Iterator, parser::Matrix<Number>(), Skipper>
	{
		MatrixParser<Iterator, Number> mMatrixParser;
		
		InvariantParser() : InvariantParser::base_type(start)
		{
			start =  qi::lexeme[(qi::lit("i") | qi::lit("I") ) > qi::lit("nvariant")] > qi::lit("=") > mMatrixParser;
		}

		qi::rule<Iterator, parser::Matrix<Number>(), Skipper> start;
	};
	
	template<typename Iterator, typename Number>
	struct GuardParser : public qi::grammar<Iterator, parser::Matrix<Number>(), Skipper>
	{
		MatrixParser<Iterator, Number> mMatrixParser;
		
		GuardParser() : GuardParser::base_type(start)
		{
			start =  qi::lexeme[(qi::lit("g") | qi::lit("G") ) > qi::lit("uard")] > qi::lit("=") > mMatrixParser;
		}

		qi::rule<Iterator, parser::Matrix<Number>(), Skipper> start;
	};
	
	template<typename Iterator, typename Number>
	struct ResetParser : public qi::grammar<Iterator, parser::Matrix<Number>(), Skipper>
	{
		MatrixParser<Iterator, Number> mMatrixParser;
		
		ResetParser() : ResetParser::base_type(start)
		{
			start =  qi::lexeme[(qi::lit("r") | qi::lit("R") ) > qi::lit("eset")] > qi::lit("=") > mMatrixParser;
		}

		qi::rule<Iterator, parser::Matrix<Number>(), Skipper> start;
	};
	
}
}
