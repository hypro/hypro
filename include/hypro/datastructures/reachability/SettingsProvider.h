#pragma once

#include "../../types.h"
#include "../../util/logging/Filewriter.h"
#include "../../util/logging/Logger.h"
#include "../HybridAutomaton/HybridAutomaton.h"
#include "../HybridAutomaton/decomposition/Decomposition.h"
#include "Settings.h"
#include "Strategy.h"
#include "StrategyNode.h"

#include <carl/util/Singleton.h>

namespace hypro {
/**
 * SettingsProvider is a Singleton class providing meta information about the reachability analysis process.
 */
template <typename State>
class SettingsProvider : public carl::Singleton<SettingsProvider<State>> {
	using Number = typename State::NumberType;
	friend carl::Singleton<SettingsProvider<State>>;
	SettingsProvider<State>()
		: treeDotFileWriter( "test.dot" ) {}

  public:
	const HybridAutomaton<Number>& getHybridAutomaton();

	ReachabilitySettings& getReachabilitySettings();

	unsigned getWorkerThreadCount() const;
	void setWorkerThreadCount( std::size_t c );
	void setSkipPlot( bool skip ) { mSkipPlot = skip; }
	bool skipPlot() const;
	bool useGlobalQueuesOnly() const;
	bool useFixedPointTest() const { return mUseFixedPointTest; }
	double getQueueBalancingRatio() const;
	bool useLocalTiming() const { return mUseLocalTiming; }
	bool useAnyTimingInformation() const { return mReachabilitySettings.useBadStateTimingInformation || mReachabilitySettings.useGuardTimingInformation || mReachabilitySettings.useInvariantTimingInformation; }
	bool useDecider();
	void setUseDecider( bool useDecider ) { mUseDecider = useDecider; }
	bool decomposeAutomaton();
	void setDecomposeAutomaton( bool decompose ) { mDoDecomposition = decompose; }
	std::size_t getNumberVariables() const { return mHybridAutomaton.getVariables().size(); }
	tNumber getGlobalTimeHorizon() const { return mReachabilitySettings.timeBound * mReachabilitySettings.jumpDepth; }

	void setHybridAutomaton( HybridAutomaton<Number>&& ha );

	void setReachabilitySettings( const ReachabilitySettings& rs );

	// In case we got a ReachabilitySettings from parser, we need to convert it to ReachabilitySettings
	template <typename N = Number, typename T = tNumber, carl::DisableIf<std::is_same<N, T>> = carl::dummy>
	void setReachabilitySettings( const ReachabilitySettings& rs ) {
		ReachabilitySettings rsConverted;
		rsConverted.timeBound = rs.timeBound;
		rsConverted.timeStep = rs.timeStep;
		rsConverted.jumpDepth = rs.jumpDepth;
		rsConverted.fileName = rs.fileName;
		rsConverted.pplDenomimator = rs.pplDenomimator;
		rsConverted.plotDimensions = rs.plotDimensions;
		rsConverted.uniformBloating = rs.uniformBloating;
		rsConverted.clustering = rs.clustering;
		rsConverted.useBadStateTimingInformation = rs.useBadStateTimingInformation;
		rsConverted.useInvariantTimingInformation = rs.useInvariantTimingInformation;
		rsConverted.useGuardTimingInformation = rs.useGuardTimingInformation;
		mReachabilitySettings = rsConverted;
	}

	void setStrategy( const Strategy& strat ) { mStrategy = strat; }
	const Strategy& getStrategy() const { return mStrategy; }

	tNumber getLocalTimeHorizon() const { return mReachabilitySettings.timeBound; }
	tNumber getTimeStepSize( std::size_t i = 0 ) const { return mStrategy.Settings.at( i ).timeStep; }

	const LockedFileWriter& getDotFileWriter() const { return treeDotFileWriter; }

	bool isFullTimed() { return fullTimed; }
	void setFullTimed( bool timed ) { fullTimed = timed; }

	// experimental feature to switch between standard and fulltimed context.
	bool useContextSwitch() { return contextSwitch; }

	const Decomposition& getSubspaceDecomposition() const { return mSubspaceDecomposition; }
	void setSubspaceDecomposition( const Decomposition& decomp ) { mSubspaceDecomposition = decomp; }

	const std::map<const Location<Number>*, std::shared_ptr<std::vector<SUBSPACETYPE>>>& getLocationSubspaceTypeMap() const { return mLocationSubspaceTypeMap; }
	void computeLocationSubspaceTypeMapping( const HybridAutomaton<Number>& ha );

	std::map<const Location<Number>*, LOCATIONTYPE> getLocationTypeMap() { return mLocationTypeMap; }
	void computeLocationTypeMapping( const HybridAutomaton<Number>& ha );

  private:
	HybridAutomaton<Number> mHybridAutomaton;
	ReachabilitySettings mReachabilitySettings;
	Strategy mStrategy;
	bool mGlobalQueuesOnly = false;
	bool mSkipPlot = false;
	bool mUseLocalTiming = false;
	bool mUseFixedPointTest = true;
	bool mDoDecomposition = false;
	bool mUseDecider = false;
	int mThreadcount = 1;
	double mBalancingRatio = 1.0;
	LockedFileWriter treeDotFileWriter;
	Decomposition mSubspaceDecomposition;

	bool fullTimed = false;

	// experimental feature to switch between standard and fulltimed context.
	bool contextSwitch = false;

	// used to decide for the representaion and handlers of each subspace in a location
	std::map<const Location<Number>*, std::shared_ptr<std::vector<SUBSPACETYPE>>> mLocationSubspaceTypeMap;
	std::map<const Location<Number>*, LOCATIONTYPE> mLocationTypeMap;
};

}  // namespace hypro

#include "SettingsProvider.tpp"
