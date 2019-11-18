#ifndef BOOST_SPIRIT_USE_PHOENIX_V3
#define BOOST_SPIRIT_USE_PHOENIX_V3
#endif
//#define BOOST_SPIRIT_DEBUG

#pragma once

#ifdef USE_CLANG
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Woverloaded-shift-op-parentheses"
#endif

#include <iosfwd>
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

#include "config.h"
#include "common.h"
#include "datastructures/HybridAutomaton/Settings.h"
#include "datastructures/HybridAutomaton/State.h"
#include "datastructures/HybridAutomaton/LocationManager.h"
#include "datastructures/HybridAutomaton/HybridAutomaton.h"
#include "util/logging/Logger.h"
#include "util/VariablePool.h"
#include "symbols.h"
#include "polynomialParser.h"
#include "componentParser.h"

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
	std::vector<State<Number,ConstraintSet<Number>>> mInitialStates;
	std::vector<State<Number,ConstraintSet<Number>>> mLocalBadStates;
	std::vector<unsigned> mModeIds;
	std::vector<unsigned> mVariableIds;
	std::vector<unsigned> mDiscreteVariableIds;
	hypro::ReachabilitySettings mSettings;
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
			TRACE("hypro.parser","Mapped var " << varName << " to dimension " << mVariablePool.id(tmp));
			mVariableSymbolTable.add(varName, mVariablePool.id(tmp));
			mVariableIds.push_back(mVariablePool.id(tmp));
			++mDimensionLimit;
			++mDiscreteDimensionLimit;
			TRACE("hypro.parser","New continuous dimension: " << mDimensionLimit);
		}
	}

	void insertDiscreteSymbols(const std::vector<std::string>& _in) {
		for(const auto& varName : _in ) {
			carl::Variable tmp = mVariablePool.newCarlVariable(varName);
			TRACE("hypro.parser","Mapped var " << varName << " to dimension " << mVariablePool.id(tmp));
			mDiscreteVariableSymbolTable.add(varName, mVariablePool.id(tmp));
			mDiscreteVariableIds.push_back(mVariablePool.id(tmp));
			++mDiscreteDimensionLimit;
			TRACE("hypro.parser","New discrete dimension: " << mDiscreteDimensionLimit);
		}
	}

	void addContinuousState(const std::vector<matrix_t<Number>>& _constraint, unsigned id, std::vector<State<Number,ConstraintSet<Number>>>& _states) {
		TRACE("hypro.parser","Add new continuous state.");
		if(_constraint.size() > 0) {
			TRACE("hypro.parser","Add continuous state for location " << id);
			bool found = false;
			// due to the creation of initial states, which uses this function as well and the occurrence of duplicates in the initial states, we need the last instance of a matching state.
			for(auto stateIt = _states.rbegin(); stateIt != _states.rend(); ++stateIt) {
				if(stateIt->getLocation()->getId() == id){
					TRACE("hypro.parser","stateIt->already exists.");
					found = true;
					unsigned constraintsNum = 0;
					if(stateIt->getNumberSets() > 0) {
						constraintsNum = unsigned(boost::get<ConstraintSet<Number>>(stateIt->getSet()).matrix().rows());
						TRACE("hypro.parser","current constraints: " << boost::get<ConstraintSet<Number>>(stateIt->getSet()).matrix());
					}
					unsigned dimension = constraintsNum > 0 ? unsigned(boost::get<ConstraintSet<Number>>(stateIt->getSet()).matrix().cols()) : unsigned((_constraint.begin()->cols())-1);
					ConstraintSet<Number> set = constraintsNum > 0 ? boost::get<ConstraintSet<Number>>(stateIt->getSet()) : ConstraintSet<Number>();
					TRACE("hypro.parser","Resize to " << constraintsNum+_constraint.size() << " x " << dimension);
					set.rMatrix().conservativeResize(constraintsNum+Eigen::Index(_constraint.size()), dimension);
					set.rVector().conservativeResize(constraintsNum+Eigen::Index(_constraint.size()));
					TRACE("hypro.parser","State already existing with " << constraintsNum << " rows.");
					for(const auto& row : _constraint) {
						assert(row.rows() == 1);
						assert(row.cols() > 0);
						TRACE("hypro.parser","add row " << constraintsNum);
						TRACE("hypro.parser","row properties: " << row.rows() << " , " << row.cols());
						TRACE("hypro.parser","set properties: " << set.matrix().rows() << " , " << set.matrix().cols());
						set.rMatrix().row(constraintsNum) = row.block(0,0,1,row.cols()-1);
						//TRACE("hypro.parser"," " << set.matrix().row(constraintsNum) << " <= " );
						set.rVector()(constraintsNum) = -row(0,row.cols()-1);
						//TRACE("hypro.parser",set.vector()(constraintsNum));
						++constraintsNum;
					}
					stateIt->setSet(set);
					TRACE("hypro.parser","New constraints: " << boost::get<ConstraintSet<Number>>(stateIt->getSet()).matrix());
					break;
				}
			}
			if(!found){
				State<Number,ConstraintSet<Number>> s(mLocationManager.location(id));
				ConstraintSet<Number> set(matrix_t<Number>(_constraint.size(), _constraint.begin()->cols()-1), vector_t<Number>(_constraint.size()));
				unsigned constraintsNum = 0;
				TRACE("hypro.parser","State newly created with " << _constraint.size() << " rows.");
				for(const auto& row : _constraint) {
					assert(row.rows() == 1);
					TRACE("hypro.parser","add row " << constraintsNum);
					set.rMatrix().row(constraintsNum) = row.block(0,0,1,row.cols()-1);
					//TRACE("hypro.parser"," " << set.matrix().row(constraintsNum) << " <= ");
					set.rVector()(constraintsNum) = -row(0,row.cols()-1);
					//TRACE("hypro.parser",set.vector()(constraintsNum));
					++constraintsNum;
				}
				s.setSet(set);
				_states.emplace_back(s);
			}
		}
	}

	void addDiscreteState(const std::pair<unsigned, carl::Interval<Number>>& _initPair, unsigned id, std::vector<State<Number,ConstraintSet<Number>>>& _states) {
		TRACE("hypro.parser","Add discrete state for location " << id);
		bool found = false;
		// due to the creation of initial states, which uses this function as well and the occurrence of duplicates in the initial states, we need the last instance of a matching state.
		for(auto stateIt = _states.rbegin(); stateIt != _states.rend(); ++stateIt) {
			if(stateIt->getLocation() == mLocationManager.location(id)){
				found = true;
				vector_t<Number> lowerNormal = vector_t<Number>::Zero(Eigen::Index(mDiscreteVariableIds.size()));
				vector_t<Number> upperNormal = vector_t<Number>::Zero(Eigen::Index(mDiscreteVariableIds.size()));
				lowerNormal(_initPair.first) = -1;
				upperNormal(_initPair.first) = 1;

				ConstraintSet<Number> currentAssignment = boost::get<ConstraintSet<Number>>(stateIt->getSet(1));
				currentAssignment.addConstraint(lowerNormal,-_initPair.second.lower());
				currentAssignment.addConstraint(upperNormal,_initPair.second.upper());
				//stateIt->discreteAssignment[VariablePool::getInstance().carlVarByIndex(_initPair.first)] = _initPair.second;
				stateIt->setSet(currentAssignment,1);
			}
			break;
		}
		if(!found){
			State<Number,ConstraintSet<Number>> s(mLocationManager.location(id));
			vector_t<Number> lowerNormal = vector_t<Number>::Zero(Eigen::Index(mDiscreteVariableIds.size()));
			vector_t<Number> upperNormal = vector_t<Number>::Zero(Eigen::Index(mDiscreteVariableIds.size()));
			lowerNormal(_initPair.first) = -1;
			upperNormal(_initPair.first) = 1;

			ConstraintSet<Number> currentAssignment;
			currentAssignment.addConstraint(lowerNormal,-_initPair.second.lower());
			currentAssignment.addConstraint(upperNormal,_initPair.second.upper());
			//stateIt->discreteAssignment[VariablePool::getInstance().carlVarByIndex(_initPair.first)] = _initPair.second;
			s.setSet(currentAssignment,1);
			_states.emplace_back(s);
		}
	}

	unsigned addInitState(unsigned _id, std::vector<State<Number,ConstraintSet<Number>>>& _states) {
		TRACE("hypro.parser","Add initial state for location " << _id);
		State<Number,ConstraintSet<Number>> s(mLocationManager.location(_id));
		s.setTimestamp(carl::Interval<Number>(0));
		_states.emplace_back(s);
		return _id;
	}

	void insertSettings(const hypro::ReachabilitySettings& _in) {
		mSettings = _in;
	}

	void insertModes(const std::vector<std::pair<std::string, Location<Number>*>>& _in) {
		for(const auto& modePair : _in) {
			TRACE("hypro.parser","Found mode " << modePair.first << " mapped to " << modePair.second->getId());
			TRACE("hypro.parser","Mode: " << *modePair.second);

			if(mModes.find(modePair.first) == nullptr) {
				mModes.add(modePair.first, modePair.second->getId());
				mModeIds.push_back(modePair.second->getId());
				TRACE("hypro.parser","Add new mode " << modePair.first << " mapped to id " << modePair.second->getId());
			} else {
				TRACE("hypro.parser","Overwrite mode " << modePair.first << " mapped to id " << mModes.at(modePair.first) << " with mode mapped to id " << modePair.second->getId());
				unsigned redundantId = mModes.at(modePair.first);
				mModes.at(modePair.first) = modePair.second->getId();
				mLocationManager.erase(redundantId);
				// update mModeIds
				auto modeIdIt = mModeIds.begin();
				while(modeIdIt != mModeIds.end() && *modeIdIt != redundantId) { ++modeIdIt; }
				assert(modeIdIt != mModeIds.end());
				if(modeIdIt != mModeIds.end()) {
					mModeIds.erase(modeIdIt);
				}
				mModeIds.push_back(modePair.second->getId());
			}
		}
	}

	void insertTransitions(const boost::optional<std::set<Transition<Number>*>>& _transitions) {
		if(_transitions){
			TRACE("hypro.parser","insert "<< _transitions->size() << " transitions.");
			for(const auto& transition :  *_transitions) {
				mTransitions.insert(transition);
			}
		}
	}

	HybridAutomaton<Number> parseInput( const std::string& pathToInputFile );
	bool parse( std::istream& in, HybridAutomaton<Number>& _result );
	HybridAutomaton<Number> createAutomaton();
};

} // namespace parser
} // namespace hypro

#include "flowstarParser.tpp"

#ifdef USE_CLANG
#pragma clang diagnostic pop
#endif
