#pragma once

#include "../../Clock.h"
#include "../../Results.h"
#include "../../Settings.h"
#include "../../types.h"
#include <flags.h>
#include <iostream>
#include <random>
#include <algorithms/reachability/analyzer/SingularAnalyzer.h>
#include <datastructures/HybridAutomaton/HybridAutomaton.h>
#include <datastructures/reachability/ReachTreev2Util.h>
#include <datastructures/reachability/Settings.h>
#include <representations/GeometricObjectBase.h>
#include <algorithms/reachability/Reach.h> 

namespace benchmark {
namespace singularAnalysis {
Results<std::size_t> singularTimeElapse( const Settings& settings );
Results<std::size_t> run( const Settings& settings );


}  // namespace singularAnalysis
}  // namespace benchmark