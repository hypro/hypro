#include "SettingsProvider.h"

namespace hypro
{
template<typename State>
const HybridAutomaton<typename State::NumberType>& SettingsProvider<State>::getHybridAutomaton()
{
    return mHybridAutomaton;
}

template<typename State>
ReachabilitySettings& SettingsProvider<State>::getReachabilitySettings()
{
    return mReachabilitySettings;
}

template<typename State>
bool SettingsProvider<State>::skipPlot() const
{
    return mSkipPlot;
}

template<typename State>
bool SettingsProvider<State>::useGlobalQueuesOnly() const
{
    return mGlobalQueuesOnly;
}

template<typename State>
bool SettingsProvider<State>::useDecider()
{
    return mUseDecider;
}

template<typename State>
bool SettingsProvider<State>::decomposeAutomaton()
{
    return mDoDecomposition;
}


template<typename State>
double SettingsProvider<State>::getQueueBalancingRatio() const {
	return mBalancingRatio;
}

template<typename State>
unsigned SettingsProvider<State>::getWorkerThreadCount()
{
    return mThreadcount;
}

template<typename State>
void SettingsProvider<State>::setHybridAutomaton(const HybridAutomaton<Number>& ha)
{
    mHybridAutomaton = ha;
}

template<typename State>
void SettingsProvider<State>::setReachabilitySettings(const ReachabilitySettings& rs)
{
    mReachabilitySettings = rs;
}

template<typename State>
template<typename Representation>
void SettingsProvider<State>::addStrategyElement(tNumber timeStep, representation_name rep, AGG_SETTING agg, int clustering) {
    mStrategy.emplace_back(StrategyNode<Representation>(timeStep,agg,clustering));
}

template<typename State>
void SettingsProvider<State>::computeLocationSubspaceTypeMapping(const HybridAutomaton<Number> &ha){
   // assert(SettingsProvider<State>::getInstance().getSubspaceDecomposition().size() != 0);

    Decomposition decompositions = SettingsProvider<State>::getInstance().getSubspaceDecomposition();
    for(auto location : ha.getLocations()){
        DEBUG("hypro.util", "Subspace types for location " << location->getName()<< ":");

        std::vector<SUBSPACETYPE> vec;
        for(std::size_t i = 0; i < decompositions.size(); i++){
            if(DecisionEntity<Number>::getInstance().isTimedSubspace(*location, i)){
                vec.push_back(SUBSPACETYPE::TIMED);
            }
            else if(DecisionEntity<Number>::getInstance().isDiscreteSubspace(*location, i)){
                vec.push_back(SUBSPACETYPE::DISCRETE);
            }
            else {
                vec.push_back(SUBSPACETYPE::LTI);
            }
             //DEBUG("hypro.util",  "" << i << ": " << vec.at(i));
        }
        mLocationSubspaceTypeMap.insert(std::make_pair(location, std::make_shared<std::vector<SUBSPACETYPE>>(vec)));
    }
}

template<typename State>
void SettingsProvider<State>::computeLocationTypeMapping(const HybridAutomaton<Number> &ha){
    assert(mLocationSubspaceTypeMap.size() != 0);
    for(auto location : ha.getLocations()){

        auto subspacetypesptr = mLocationSubspaceTypeMap.find(location)->second;
        std::vector<SUBSPACETYPE> subspacetypes = *subspacetypesptr;

        bool timed = true;
        for(std::size_t i = 0; i < subspacetypes.size(); i++){
            if(subspacetypes.at(i) == SUBSPACETYPE::LTI){
                timed = false;
                break;
            }
        }

        if(timed){
            mLocationTypeMap.insert(std::make_pair(location, LOCATIONTYPE::TIMEDLOC));
        }
        else{
            mLocationTypeMap.insert(std::make_pair(location, LOCATIONTYPE::LTILOC));
        }

        DEBUG("hypro.util", "Types for location " << location->getName()<< ":" << mLocationTypeMap.find(location)->second);
    }
}

} // hypro
