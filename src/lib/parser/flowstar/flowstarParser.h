/**
 * Parser for flowstar files.
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 */

#pragma once

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/support_line_pos_iterator.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/spirit/include/phoenix_bind.hpp>
#include <boost/variant.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <cassert>

#include "componentParser.h"
#include "../../datastructures/hybridAutomata/LocationManager.h"
#include "../../datastructures/hybridAutomata/HybridAutomaton.h"
#include "helper.h"


namespace hypro {
namespace parser {

	template <typename Number>
	using Automaton = std::vector<boost::variant<State<Number>, Transition<Number>>>;

	template <typename Number>
	using matrix = Eigen::Matrix<Number, Eigen::Dynamic, Eigen::Dynamic>;

	template <typename Iterator, typename Number>
	struct LocationParser : public qi::grammar<Iterator, State<Number>(), Skipper> {
		FlowParser<Iterator, Number> mFlowParser;
		InvariantParser<Iterator, Number> mInvariantParser;
		NameParser<Iterator> mNameParser;

		LocationParser() : LocationParser::base_type( start ) {
			start = *( qi::char_ - qi::lit("{")) > qi::lit( "{" ) >  mFlowParser  >
					-( mInvariantParser ) > qi::lit( "}" );
		}

		qi::rule<Iterator, State<Number>(), Skipper> start;
	};

	template <typename Iterator, typename Number>
	struct ModeParser : public qi::grammar<Iterator, std::vector<State<Number>>, Skipper> {
		LocationParser<Iterator, Number> mLocationParser;
		std::vector<State<Number>> mLocations;

		ModeParser() : ModeParser::base_type( start ) {
			start = qi::lit( "modes" ) > qi::lit( "{" ) > *( mLocationParser ) > qi::lit( "}" );
		}

		qi::rule<Iterator, std::vector<State<Number>>, Skipper> start;
	};

	template <typename Iterator, typename Number>
	struct TransitionParser : public qi::grammar<Iterator, Transition<Number>(), Skipper> {
		NameParser<Iterator> mNameParser;
		GuardParser<Iterator, Number> mGuardParser;
		ResetParser<Iterator, Number> mResetParser;

		TransitionParser() : TransitionParser::base_type( start ) {
			start = qi::lit( "transition" ) > qi::lit( "(" ) > -( qi::int_ ) > -( mNameParser > qi::lit( "," ) ) >
					qi::lexeme[( qi::lit( "s" ) | qi::lit( "S" ) ) > qi::lit( "ource" )] > qi::lit( "=" ) > qi::uint_ >
					qi::lit( "," ) > qi::lexeme[( qi::lit( "t" ) | qi::lit( "T" ) ) > qi::lit( "arget" )] > qi::lit( "=" ) >
					qi::uint_ > -( qi::lit( "," ) > mGuardParser ) > -( qi::lit( "," ) > mResetParser ) > qi::lit( ")" );
		}

		qi::rule<Iterator, Transition<Number>(), Skipper> start;
	};

	template <typename Number, typename Representation>
	struct MainParser : public qi::grammar<Iterator, Skipper> {
		//ModeParser<Iterator, Number> mModeParser;
		//TransitionParser<Iterator, Number> mTransitionParser;
		VariableParser<Iterator> mVariableParser;
		PolynomialParser<Iterator, Number> mPolynomialParser;

		std::vector<State<Number>> mStates;
		std::vector<Transition<Number>> mTransitions;

		MainParser() : MainParser::base_type( mMain ) {
			// using phoenix::construct;
			using phoenix::val;

			mMain = mVariableParser >> mPolynomialParser[phoenix::bind( &hypro::parser::MainParser<Number, Representation>::addPolynomial, phoenix::ref(*this), qi::_1)];

			//mMain =
			//	   *( mModeParser[phoenix::bind( &hypro::parser::MainParser<Number, Representation>::push_back_State,
			//									  phoenix::ref( *this ), qi::_1 )] |
			//		  mTransitionParser[phoenix::bind(
			//				&hypro::parser::MainParser<Number, Representation>::push_back_Transition, phoenix::ref( *this ),
			//				qi::_1 )] );

			qi::on_error<qi::fail>(
				  mMain,
				  std::cout
						<< val( "Error! Expecting " ) << qi::_4  // what failed?
						<< val( " here: \"" )
						//<< boost_optional_detail::construct<std::string>(qi::_3, qi::_2)   // iterators to error-pos, end
						<< val( "\"" ) << std::endl );
		}

		qi::rule<Iterator, Skipper> mMain;

		void push_back_State( const State<Number>& _in ) { mStates.push_back( _in ); }
		void push_back_Transition( const Transition<Number>& _in ) { mTransitions.push_back( _in ); }
		void addPolynomial( const Polynomial<Number>& _in ) { std::cout << "Poly: " << _in  << std::endl; }

		HybridAutomaton<Number, Representation> parseInput( const std::string& pathToInputFile );
		bool parse( std::istream& in, const std::string& filename, HybridAutomaton<Number, Representation>& _result );

		HybridAutomaton<Number, Representation> createAutomaton();
	};

	template <typename Number>
	class Automaton_visitor : public boost::static_visitor<> {
	  public:
		State<Number>& operator()( State<Number>& i ) const { return i; }

		Transition<Number>& operator()( Transition<Number>& i ) const { return i; }
	};

} // namespace
} // namespace

#include "flowstarParser.tpp"