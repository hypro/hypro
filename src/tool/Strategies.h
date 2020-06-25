// /*
//  * Strategies.h
//  *
//  * A file that lets you choose a reachability strategy by simply denoting its
//  * name in the console. The string is received via CMDHandle.cc. The outputted
//  * strategy is fed into the SettingsProvider.
//  *
//  * The strategies themselves are named after the TACAS conference.
//  */

// #pragma once

// #include "../hypro/datastructures/reachability/Strategy.h"
// #include "../hypro/util/logging/Logger.h"
// #include "typedefs.h"
// #include <string>

// namespace hydra {

// hypro::Strategy<State> getStrategyFromName(const std::string &name);

// std::map<std::string, hypro::Strategy<State>> getStrategiesMap();

// } // namespace hydra
