#include "SettingsProvider.h"

namespace hypro
{
template<typename Number>
const HybridAutomaton<Number>& SettingsProvider<Number>::getHybridAutomaton()
{
    return mHybridAutomaton;
}

template<typename Number>
ReachabilitySettings& SettingsProvider<Number>::getReachabilitySettings()
{
    return mReachabilitySettings;
}

template<typename Number>
bool SettingsProvider<Number>::skipPlot() const
{
    return mSkipPlot;
}

template<typename Number>
bool SettingsProvider<Number>::useGlobalQueuesOnly() const
{
    return mGlobalQueuesOnly;
}

template<typename Number>
bool SettingsProvider<Number>::useDecider()
{
    return mUseDecider;
}

template<typename Number>
bool SettingsProvider<Number>::decomposeAutomaton()
{
    return mDoDecomposition;
}


template<typename Number>
double SettingsProvider<Number>::getQueueBalancingRatio() const {
	return mBalancingRatio;
}

template<typename Number>
unsigned SettingsProvider<Number>::getWorkerThreadCount()
{
    return mThreadcount;
}

template<typename Number>
representation_name SettingsProvider<Number>::getStartingRepresentation()
{
    return mStrategy.begin()->representation;
}

template<typename Number>
void SettingsProvider<Number>::setHybridAutomaton(const HybridAutomaton<Number>& ha)
{
    mHybridAutomaton = ha;
}

template<typename Number>
void SettingsProvider<Number>::setReachabilitySettings(const ReachabilitySettings& rs)
{
    mReachabilitySettings = rs;
}

template<typename Number>
void SettingsProvider<Number>::computeLocationSubspaceTypeMapping(const HybridAutomaton<Number> &ha){
    assert(SettingsProvider<Number>::getInstance().getSubspaceDecomposition().size() != 0);

    Decomposition decompositions = SettingsProvider<Number>::getInstance().getSubspaceDecomposition();
    for(auto location : ha.getLocations()){
        DEBUG("hypro.util", "Subspace types for location " << location->getName()<< ":");

        std::vector<SUBSPACETYPE> vec;
        for(int i = 0; i < decompositions.size(); i++){
            if(DecisionEntity<Number>::getInstance().isTimedSubspace(*location, i)){
                vec.push_back(SUBSPACETYPE::TIMED);
            }
            else if(DecisionEntity<Number>::getInstance().isDiscreteSubspace(*location, i)){
                vec.push_back(SUBSPACETYPE::DISCRETE);
            }
            else {
                vec.push_back(SUBSPACETYPE::LTI);
            }
             DEBUG("hypro.util",  "" << i << ": " << vec.at(i));
        }
        mLocationSubspaceTypeMap.insert(std::make_pair(location, std::make_shared<std::vector<SUBSPACETYPE>>(vec)));
    }
}

template<typename Number>
void SettingsProvider<Number>::computeLocationTypeMapping(const HybridAutomaton<Number> &ha){
    assert(mLocationSubspaceTypeMap.size() != 0);
    for(auto location : ha.getLocations()){

        auto subspacetypesptr = mLocationSubspaceTypeMap.find(location)->second;
        std::vector<SUBSPACETYPE> subspacetypes = *subspacetypesptr;

        bool timed = true;
        for(int i = 0; i < subspacetypes.size(); i++){
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
