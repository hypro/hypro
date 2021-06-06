#pragma once

#include "../../Clock.h"
#include "../../Results.h"
#include "../../Settings.h"
#include "../../types.h"
#include <hypro/flags.h>
#include <iostream>
#include <random>
#include <hypro/algorithms/reachability/analyzer/SingularAnalyzer.h>
#include <hypro/datastructures/HybridAutomaton/HybridAutomaton.h>
#include <hypro/datastructures/reachability/ReachTreev2Util.h>
#include <hypro/datastructures/reachability/Settings.h>
#include <hypro/representations/GeometricObjectBase.h>
#include <hypro/algorithms/reachability/Reach.h>

namespace benchmark {
namespace singularAnalysis {
Results<std::size_t> singularTimeElapse( const Settings& settings );
Results<std::size_t> singularJumps( const Settings& setting );
Results<std::size_t> run( const Settings& settings );


}  // namespace singularAnalysis
}  // namespace benchmark