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
#include "../../datastructures/hybridAutomata/State.h"
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
struct flowstarParser : qi::grammar<Iterator, Skipper>
{
	variableParser<Iterator> mVariableParser;
	modeParser<Iterator, Number> mModeParser;
	transitionParser<Iterator, Number> mTransitionParser;
	settingsParser<Iterator, Number> mSettingsParser;
	constraintParser<Iterator,Number> mConstraintParser;
	discreteConstraintParser<Iterator,Number> mDiscreteConstraintParser;
	px::function<ErrorHandler> errorHandler;

	LocationManager<Number>& mLocationManager = LocationManager<Number>::getInstance();
	symbol_table mVariableSymbolTable;
	symbol_table mDiscreteVariableSymbolTable;
	symbol_table mModes;
	VariablePool& mVariablePool = VariablePool::getInstance();
	std::set<Transition<Number>*> mTransitions;
	std::vector<State<Number>> mInitialStates;
	std::vector<State<Number>> mLocalBadStates;
	std::vector<unsigned> mModeIds;
	std::vector<unsigned> mVariableIds;
	std::vector<unsigned> mDiscreteVariableIds;
	ReachabilitySettings<Number> mSettings;
	unsigned mDimensionLimit;
	unsigned mDiscreteDimensionLimit;

	flowstarParser();

	qi::rule<Iterator, Skipper> start;
	qi::rule<Iterator, Skipper> continuousStart;
	qi::rule<Iterator, Skipper> hybridStart;
	qi::rule<Iterator, Skipper> continuousVariables;
	qi::rule<Iterator, Skipper> discreteVariables;
	qi::rule<Iterator, Skipper> settings;
	qi::rule<Iterator, qi::unused_type(), spirit::locals<unsigned>, Skipper> init;
	qi::rule<Iterator, qi::unused_type(const unsigned&)> continuousInit;
	qi::rule<Iterator, qi::unused_type(const unsigned&)> discreteInit;
	qi::rule<Iterator, qi::unused_type(), spirit::locals<unsigned>, Skipper> badStates;
	qi::rule<Iterator, qi::unused_type(const unsigned&)> continuousBad;
	qi::rule<Iterator, qi::unused_type(const unsigned&)> discreteBad;
	qi::rule<Iterator, std::vector<std::pair<std::string, Location<Number>*>>(), Skipper> modes;
	qi::rule<Iterator, std::set<Transition<Number>*>(), Skipper> transitions;

	void insertContinuousSymbols(const std::vector<std::string>& _in) {
		for(const auto& varName : _in ) {
			carl::Variable tmp = mVariablePool.newCarlVariable(varName);
			//std::cout << "Mapped var " << varName << " to dimension " << mVariablePool.id(tmp) << std::endl;
			mVariableSymbolTable.add(varName, mVariablePool.id(tmp));
			mVariableIds.push_back(mVariablePool.id(tmp));
			++mDimensionLimit;
			++mDiscreteDimensionLimit;
			//std::cout << "New continuous dimension: " << mDimensionLimit << std::endl;
		}
	}

	void insertDiscreteSymbols(const std::vector<std::string>& _in) {
		for(const auto& varName : _in ) {
			carl::Variable tmp = mVariablePool.newCarlVariable(varName);
			//std::cout << "Mapped var " << varName << " to dimension " << mVariablePool.id(tmp) << std::endl;
			mDiscreteVariableSymbolTable.add(varName, mVariablePool.id(tmp));
			mDiscreteVariableIds.push_back(mVariablePool.id(tmp));
			++mDiscreteDimensionLimit;
			//std::cout << "New discrete dimension: " << mDiscreteDimensionLimit << std::endl;
		}
	}

	void addContinuousState(const std::vector<matrix_t<Number>>& _constraint, unsigned id, std::vector<State<Number>>& _states) {
		//std::cout << "Add continuous state for location " << id << std::endl;
		bool found = false;
		for(auto& state : _states) {
			if(state.location->id() == id){
				//std::cout << "State already exists." << std::endl;
				found = true;
				assert(state.discreteAssignment.size() == mDiscreteVariableIds.size());
				unsigned constraintsNum = boost::get<cPair<Number>>(state.set).first.rows();
				//std::cout << "current constraints: " << boost::get<cPair<Number>>(state.set).first << std::endl;
				cPair<Number> set = boost::get<cPair<Number>>(state.set);
				//std::cout << "Resize to " << constraintsNum+_constraint.size() << " x " << boost::get<cPair<Number>>(state.set).first.cols() << std::endl;
				set.first.conservativeResize(constraintsNum+_constraint.size(), boost::get<cPair<Number>>(state.set).first.cols());
				set.second.conservativeResize(constraintsNum+_constraint.size());
				//std::cout << "State already existing with " << constraintsNum << " rows." << std::endl;
				for(const auto& row : _constraint) {
					assert(row.rows() == 1);
					//std::cout << "add row " << constraintsNum;
					set.first.row(constraintsNum) = row.block(0,0,1,row.cols()-1);
					//std::cout << " " << convert<Number,double>(boost::get<cPair<Number>>(state.set).first.row(constraintsNum)) << " <= ";
					set.second(constraintsNum) = -row(0,row.cols()-1);
					//std::cout << boost::get<cPair<Number>>(state.set).second(constraintsNum) << std::endl;
					++constraintsNum;
				}
				state.set = set;
				//std::cout << "New constraints: " << boost::get<cPair<Number>>(state.set).first << std::endl;
			}
		}
		if(!found){
			State<Number> s;
			s.location = mLocationManager.location(id);
			std::pair<matrix_t<Number>, vector_t<Number>> set;
			set.first = matrix_t<Number>(_constraint.size(), _constraint.begin()->cols()-1);
			set.second = vector_t<Number>(_constraint.size());
			unsigned constraintsNum = 0;
			//std::cout << "State newly created with " << _constraint.size() << " rows." << std::endl;
			for(const auto& row : _constraint) {
				assert(row.rows() == 1);
				//std::cout << "add row " << constraintsNum;
				set.first.row(constraintsNum) = row.block(0,0,1,row.cols()-1);
				//std::cout << " " << s.constraints.row(constraintsNum) << " <= ";
				set.second(constraintsNum) = -row(0,row.cols()-1);
				//std::cout << s.constants(constraintsNum) << std::endl;
				++constraintsNum;
			}
			s.set = set;
			// initial setup of the discrete assignment
			for(const auto& id : mDiscreteVariableIds ){
				s.discreteAssignment[VariablePool::getInstance().carlVarByIndex(id)] = carl::Interval<Number>::unboundedInterval();
			}
			_states.emplace_back(s);
		}
	}

	void addDiscreteState(const std::pair<unsigned, carl::Interval<Number>>& _initPair, unsigned id, std::vector<State<Number>>& _states) {
		//std::cout << "Add discrete state for location " << id << std::endl;
		bool found = false;
		for(auto& state : _states) {
			assert(state.discreteAssignment.size() == mDiscreteVariableIds.size());
			if(state.location == mLocationManager.location(id)){
				found = true;
				state.discreteAssignment[VariablePool::getInstance().carlVarByIndex(_initPair.first)] = _initPair.second;
			}
			assert(state.discreteAssignment.size() == mDiscreteVariableIds.size());
		}
		if(!found){
			State<Number> s;
			s.location = mLocationManager.location(id);
			// initialize all discrete assignments to unbounded, when a new state is created
			for(const auto& id : mDiscreteVariableIds ){
				if(id == _initPair.first){
					s.discreteAssignment[VariablePool::getInstance().carlVarByIndex(_initPair.first)] = _initPair.second;
				} else {
					s.discreteAssignment[VariablePool::getInstance().carlVarByIndex(id)] = carl::Interval<Number>::unboundedInterval();
				}
			}
			assert(s.discreteAssignment.size() == mDiscreteVariableIds.size());
			_states.emplace_back(s);
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

	HybridAutomaton<Number> parseInput( const std::string& pathToInputFile );
	bool parse( std::istream& in, const std::string& filename, HybridAutomaton<Number>& _result );
	HybridAutomaton<Number> createAutomaton();
};

} // namespace parser
} // namespace hypro

#include "flowstarParser.tpp"
