#pragma once

#include "../../Clock.h"
#include "../../Results.h"
#include "../../Settings.h"
#include "../../types.h"
#include "../automatonConstruction.h"
#include <hypro/flags.h>
#include <iostream>
#include <random>
#include <hypro/types.h>
#include <hypro/algorithms/reachability/analyzer/DecompositionalAnalyzer.h>
#include <hypro/datastructures/HybridAutomaton/HybridAutomaton.h>
#include <hypro/datastructures/HybridAutomaton/decomposition/DecompositionMethods.h>
#include <hypro/datastructures/reachability/ReachTreev2Util.h>
#include <hypro/datastructures/reachability/Settings.h>
#include <hypro/representations/GeometricObjectBase.h>
#include <hypro/algorithms/reachability/Reach.h>

namespace benchmark {
namespace decompositionalAnalysis {
Results<std::size_t> decompositionalSingularTimeElapse( const Settings& settings );
Results<std::size_t> decompositionalSingularJumps( const Settings& setting );
Results<std::size_t> run( const Settings& settings );


}  // namespace singularAnalysis
}  // namespace benchmark