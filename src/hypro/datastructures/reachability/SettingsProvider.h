#pragma once

#include "Settings.h"
#include "StrategyNode.h"
#include "../../types.h"
#include "../HybridAutomaton/HybridAutomaton.h"
#include "../HybridAutomaton/decomposition/DecisionEntity.h"
#include "../../util/multithreading/Filewriter.h"
#include "../../util/logging/Logger.h"
#include <carl/util/Singleton.h>
//#include <hypro/representations/GeometricObject.h>

namespace hypro
{
/**
 * SettingsProvider is a Singleton class providing meta information about the reachability analysis process.
 */
template<typename Number>
class SettingsProvider : public carl::Singleton<SettingsProvider<Number>>
{
    friend carl::Singleton<SettingsProvider<Number>>;
    SettingsProvider<Number>() : treeDotFileWriter("test.dot") {}

  public:
    const HybridAutomaton<Number>& getHybridAutomaton();

    ReachabilitySettings<tNumber> &getReachabilitySettings();

    unsigned getWorkerThreadCount();

    representation_name getStartingRepresentation();

    bool skipPlot() const;
    bool useGlobalQueuesOnly() const;
    bool useFixedPointTest() const { return mUseFixedPointTest; }
    double getQueueBalancingRatio() const;
    bool useLocalTiming() const { return mUseLocalTiming; }
    bool useDecider();
    bool decomposeAutomaton();

    void setHybridAutomaton(const HybridAutomaton<Number> &ha);

    void setReachabilitySettings(const ReachabilitySettings<tNumber> &rs);

    //In case we got a ReachabilitySettings<double> from parser, we need to convert it to ReachabilitySettings<tNumber>
    template<typename N = Number, typename T = tNumber, carl::DisableIf< std::is_same<N,T> > = carl::dummy >
    void setReachabilitySettings(const ReachabilitySettings<Number> &rs){
        ReachabilitySettings<tNumber> rsConverted;
        rsConverted.timeBound = carl::convert<Number,tNumber>(rs.timeBound);
        rsConverted.timeStep = carl::convert<Number,tNumber>(rs.timeStep);
        rsConverted.jumpDepth = rs.jumpDepth;
        rsConverted.fileName = rs.fileName;
        rsConverted.pplDenomimator = rs.pplDenomimator;
        rsConverted.plotDimensions = rs.plotDimensions;
        rsConverted.uniformBloating = rs.uniformBloating;
        rsConverted.clustering = rs.clustering;
        mReachabilitySettings = rsConverted;
    }
    
    void addStrategyElement(const StrategyNode& node) { mStrategy.push_back(node); }
    void setStrategy(const std::vector<StrategyNode>& strat) { mStrategy = strat; }
    const std::vector<StrategyNode>& getStrategy() const { return mStrategy; }

    const LockedFileWriter& getDotFileWriter() const { return treeDotFileWriter; }

    bool isFullTimed(){return fullTimed;}
    void setFullTimed(bool timed){fullTimed = timed;}


   
    
    // experimental feature to switch between standard and fulltimed context. 
    bool useContextSwitch(){return contextSwitch;}
    
    const std::vector<std::vector<size_t>> getSubspaceDecomposition() const {return mSubspaceDecomposition;}
    void setSubspaceDecomposition(const std::vector<std::vector<size_t>> decomp) {mSubspaceDecomposition = decomp;}

    std::map<const Location<Number>*, std::shared_ptr<std::vector<SUBSPACETYPE>>> getLocationSubspaceTypeMap(){return mLocationSubspaceTypeMap;}
    void computeLocationSubspaceTypeMapping(const HybridAutomaton<Number> &ha);

    std::map<const Location<Number>*, LOCATIONTYPE> getLocationTypeMap(){return mLocationTypeMap;}
    void computeLocationTypeMapping(const HybridAutomaton<Number> &ha);

  private:
    HybridAutomaton<Number> mHybridAutomaton;
    ReachabilitySettings<tNumber> mReachabilitySettings;
    std::vector<StrategyNode> mStrategy;
    bool mGlobalQueuesOnly = false;
    bool mSkipPlot = false;
    bool mUseLocalTiming = false;
    bool mUseFixedPointTest = true;
    bool mDoDecomposition = false;
    bool mUseDecider = false;
    int mThreadcount = 1;
    double mBalancingRatio = 1.0;
    LockedFileWriter treeDotFileWriter;
    std::vector<std::vector<size_t>> mSubspaceDecomposition;

    bool fullTimed = false;

    // experimental feature to switch between standard and fulltimed context. 
    bool contextSwitch = false;

    // used to decide for the representaion and handlers of each subspace in a location
    std::map<const Location<Number>*, std::shared_ptr<std::vector<SUBSPACETYPE>>> mLocationSubspaceTypeMap;  
    std::map<const Location<Number>*, LOCATIONTYPE> mLocationTypeMap;
};

} // hypro

#include "SettingsProvider.tpp"