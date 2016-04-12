#define BOOST_SPIRIT_USE_PHOENIX_V3
//#define BOOST_SPIRIT_DEBUG
#include <iostream>
#include <fstream>
#include <vector>

#include <boost/spirit/include/support_line_pos_iterator.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/fusion/adapted/std_pair.hpp>
#include <boost/fusion/include/std_pair.hpp>
#include <boost/fusion/include/tuple.hpp>
#include <boost/spirit/include/phoenix_bind.hpp>

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/spirit/include/phoenix_object.hpp>

#include "../../config.h"
#include "common.h"
#include "../../algorithms/reachability/Settings.h"
#include "../../datastructures/hybridAutomata/LocationManager.h"
#include "../../datastructures/hybridAutomata/HybridAutomaton.h"
#include "../../util/types.h"
#include "symbols.h"
#include "polynomialParser.h"
#include "componentParser.h"

#pragma once

namespace hypro {
namespace parser {

template <typename Number>
struct flowstarParser
    : qi::grammar<Iterator, Skipper>
{
	variableParser<Iterator> mVariables;
	modeParser<Iterator, Number> mModeParser;
	transitionParser<Iterator, Number> mTransitionParser;
	settingsParser<Iterator, Number> mSettingsParser;
	constraintParser<Iterator> mConstraintParser;
	px::function<ErrorHandler> errorHandler;

	symbol_table mSymbols;
	symbol_table mModes;
	VariablePool& mVariablePool = VariablePool::getInstance();
	std::set<Transition<Number>*> mTransitions;
	std::multimap<unsigned, std::pair<matrix_t<Number>, vector_t<Number>>> mInitialStates;
	std::multimap<unsigned, std::pair<matrix_t<Number>, vector_t<Number>>> mLocalBadStates;
	std::vector<unsigned> mModeIds;
	std::vector<unsigned> mVariableIds;
	ReachabilitySettings<Number> mSettings;
	unsigned mDimension;

	flowstarParser() : flowstarParser::base_type( start ) {
		using qi::on_error;
        using qi::fail;

        mDimension = 0;

		start =  ( qi::lexeme["continuous reachability"] > qi::lit('{') > continuousStart > qi::lit('}') > -badStates > qi::eoi )
				|( qi::lexeme["hybrid reachability"] > qi::lit('{') > hybridStart > qi::lit('}') > (-badStates)[px::bind( &flowstarParser<Number>::insertBadState, px::ref(*this), qi::_1 )] > qi::eoi);

		continuousStart = 	stateVars > -mSettingsParser(px::ref(mSymbols));
		hybridStart = 		stateVars > settings >
							modes[px::bind( &flowstarParser<Number>::insertModes, px::ref(*this), qi::_1 )] >
							-transitions[px::bind( &flowstarParser<Number>::insertTransitions, px::ref(*this), qi::_1)] >
							(-init)[px::bind( &flowstarParser<Number>::insertInitialState, px::ref(*this), qi::_1 )];
		stateVars = 		qi::lexeme["state var"] > mVariables[px::bind( &flowstarParser<Number>::insertSymbols, px::ref(*this), qi::_1)];
		settings = 			qi::lexeme["setting"] > qi::lit('{') > mSettingsParser(px::ref(mSymbols))[px::bind( &flowstarParser<Number>::insertSettings, px::ref(*this), qi::_1)] > qi::lit('}');
		modes = 			qi::lexeme["modes"] > qi::lit('{') > *(mModeParser(px::ref(mSymbols), px::ref(mDimension))) > qi::lit("}");
		transitions = 		mTransitionParser(px::ref(mModes), px::ref(mSymbols), px::ref(mDimension))[px::bind( &flowstarParser<Number>::insertTransitions, px::ref(*this), qi::_1)];
		init = 				qi::lexeme["init"] > qi::lit('{') > *(mModes > qi::lit('{') > *(mConstraintParser(px::ref(mSymbols), px::ref(mDimension))) > qi::lit('}')) > qi::lit('}');
		badStates = 		qi::lexeme["unsafe set"] > qi::lit('{') > *( mModes > qi::lit('{') > *(mConstraintParser(px::ref(mSymbols), px::ref(mDimension))) > qi::lit('}') ) > qi::lit('}');

		qi::on_error<qi::fail>( start, errorHandler(qi::_1, qi::_2, qi::_3, qi::_4));
	}

	qi::rule<Iterator, Skipper> start;
	qi::rule<Iterator, Skipper> continuousStart;
	qi::rule<Iterator, Skipper> hybridStart;
	qi::rule<Iterator, Skipper> stateVars;
	qi::rule<Iterator, Skipper> settings;
	qi::rule<Iterator, std::vector<boost::fusion::tuple<unsigned, std::vector<std::vector<matrix_t<double>>>>>(), Skipper> init;
	qi::rule<Iterator, std::vector<boost::fusion::tuple<unsigned, std::vector<std::vector<matrix_t<double>>>>>(), Skipper> badStates;
	qi::rule<Iterator, std::vector<std::pair<std::string, Location<Number>*>>(), Skipper> modes;
	qi::rule<Iterator, std::set<Transition<Number>*>(), Skipper> transitions;

	void insertSymbols(const std::vector<std::string>& _in) {
		for(const auto& varName : _in ) {
			carl::Variable tmp = mVariablePool.newCarlVariable(varName);
			//std::cout << "Mapped var " << varName << " to dimension " << mVariablePool.id(tmp) << std::endl;
			mSymbols.add(varName, mVariablePool.id(tmp));
			mVariableIds.push_back(mVariablePool.id(tmp));
			++mDimension;
		}
	}

	void insertSettings(const ReachabilitySettings<Number>& _in) {
		mSettings = _in;
	}

	void insertModes(const std::vector<std::pair<std::string, Location<Number>*>>& _in) {
		for(const auto& modePair : _in) {
			//std::cout << "Found mode " << modePair.first << " mapped to " << modePair.second->id() << std::endl;
			//std::cout << "Mode: " << *modePair.second << std::endl;
			mModes.add(modePair.first, modePair.second->id());
			mModeIds.push_back(modePair.second->id());
		}
	}

	void insertTransitions(const boost::optional<std::set<Transition<Number>*>>& _transitions) {
		if(_transitions){
			mTransitions = *_transitions;
		}
	}

	void insertInitialState(const boost::optional<std::vector<boost::fusion::tuple<unsigned, std::vector<std::vector<matrix_t<double>>>>>>& _set) {
		if(_set){
			for(const auto& pair : *_set){
				std::cout << "Add initial location " << fs::get<0>(pair) << std::endl;
				unsigned rows = 0;
				for(const auto& rowVec : fs::get<1>(pair) ){
					rows += rowVec.size();
				}
				std::cout << "Number constraints: " << rows << std::endl;
				matrix_t<Number> mat = matrix_t<Number>(rows, fs::get<1>(pair).begin()->begin()->cols()-1);
				vector_t<Number> vec = vector_t<Number>(rows);
				//collect matrix and vector
				unsigned rowcnt = 0;
				for(const auto& matrixVec : fs::get<1>(pair)){
					for(const auto& constraintRow : matrixVec){
						std::cout << "Row: " << constraintRow << std::endl;
						matrix_t<Number> tmpMatrix = convert<double,Number>(constraintRow);
						mat.row(rowcnt) = tmpMatrix.block(0,0,1,tmpMatrix.cols()-1);
						vec(rowcnt) = -tmpMatrix(0,tmpMatrix.cols()-1);
						++rowcnt;
					}
				}
				mInitialStates.insert(std::make_pair(fs::get<0>(pair), std::make_pair(mat, vec)));
			}
		}
	}

	void insertBadState(const boost::optional<std::vector<boost::fusion::tuple<unsigned, std::vector<std::vector<matrix_t<double>>>>>>& _set) {
		if(_set){
			for(const auto& pair : *_set){
				std::cout << "Add bad state for location " << fs::get<0>(pair) << std::endl;
				unsigned rows = 0;
				for(const auto& rowVec : fs::get<1>(pair) ){
					rows += rowVec.size();
				}
				std::cout << "Number constraints: " << rows << std::endl;
				matrix_t<Number> mat = matrix_t<Number>(rows, fs::get<1>(pair).begin()->begin()->cols()-1);
				vector_t<Number> vec = vector_t<Number>(rows);
				//collect matrix and vector
				unsigned rowcnt = 0;
				for(const auto& matrixVec : fs::get<1>(pair)){
					for(const auto& constraintRow : matrixVec){
						std::cout << "Row: " << constraintRow << std::endl;
						matrix_t<Number> tmpMatrix = convert<double,Number>(constraintRow);
						mat.row(rowcnt) = tmpMatrix.block(0,0,1,tmpMatrix.cols()-1);
						vec(rowcnt) = -tmpMatrix(0,tmpMatrix.cols()-1);
						++rowcnt;
					}
				}
				//std::cout << "PARSER: added local bad state: " << mat << " <= " << vec << std::endl;
				mLocalBadStates.insert(std::make_pair(fs::get<0>(pair), std::make_pair(mat, vec)));
			}
		}
	}

	HybridAutomaton<Number> parseInput( const std::string& pathToInputFile );
	bool parse( std::istream& in, const std::string& filename, HybridAutomaton<Number>& _result );
	HybridAutomaton<Number> createAutomaton();
};

} // namespace parser
} // namespace hypro

#include "flowstarParser.tpp"
