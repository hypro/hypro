/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "SettingsProvider.h"

namespace hypro {
    template<typename State>
    const HybridAutomaton<typename State::NumberType> &SettingsProvider<State>::getHybridAutomaton() {
        return mHybridAutomaton;
    }

    template<typename State>
    ReachabilitySettings &SettingsProvider<State>::getReachabilitySettings() {
        return mReachabilitySettings;
    }

    template<typename State>
    bool SettingsProvider<State>::skipPlot() const {
        return mSkipPlot;
    }

    template<typename State>
    bool SettingsProvider<State>::useGlobalQueuesOnly() const {
        return mGlobalQueuesOnly;
    }

    template<typename State>
    bool SettingsProvider<State>::useDecider() {
        return mUseDecider;
    }

    template<typename State>
    bool SettingsProvider<State>::decomposeAutomaton() {
        return mDoDecomposition;
    }

    template<typename State>
    double SettingsProvider<State>::getQueueBalancingRatio() const {
        return mBalancingRatio;
    }

    template<typename State>
    unsigned SettingsProvider<State>::getWorkerThreadCount() const {
        return mThreadcount;
    }

    template<typename State>
    void SettingsProvider<State>::setWorkerThreadCount(std::size_t c) {
        mThreadcount = c;
    }

    template<typename State>
    void SettingsProvider<State>::setHybridAutomaton(HybridAutomaton<Number> &&ha) {
        mHybridAutomaton = std::move(ha);
    }

    template<typename State>
    void SettingsProvider<State>::setReachabilitySettings(const ReachabilitySettings &rs) {
        mReachabilitySettings = rs;
    }

    template<typename State>
    void SettingsProvider<State>::computeLocationSubspaceTypeMapping(const HybridAutomaton<Number> &ha) {
        // assert(SettingsProvider<State>::getInstance().getSubspaceDecomposition().size() != 0);

        Decomposition decompositions = SettingsProvider<State>::getInstance().getSubspaceDecomposition();
        TRACE("hypro.utility", "Having " << decompositions.subspaces.size() << " decompositions.");
        for (auto location: ha.getLocations()) {
            DEBUG("hypro.utility", "Subspace types for location " << location->getName() << " (" << location << "):");

            std::vector<SUBSPACETYPE> vec;
            for (std::size_t i = 0; i < decompositions.subspaces.size(); i++) {
                // if ( DecisionEntity<Number>::getInstance().isTimedSubspace( *location, i ) ) {
                //	vec.push_back( SUBSPACETYPE::TIMED );
                // } else if ( DecisionEntity<Number>::getInstance().isDiscreteSubspace( *location, i ) ) {
                //	vec.push_back( SUBSPACETYPE::DISCRETE );
                // } else if ( DecisionEntity<Number>::getInstance().isRectangularSubspace( *location, i ) ) {
                //	vec.push_back( SUBSPACETYPE::RECTANGULAR );
                // } else {
                //	vec.push_back( SUBSPACETYPE::LTI );
                // }
                DEBUG("hypro.utility", "Decomposition " << i << ": " << vec.at(i));
            }
            mLocationSubspaceTypeMap.insert(std::make_pair(location, std::make_shared<std::vector<SUBSPACETYPE>>(vec)));
        }
    }

    template<typename State>
    void SettingsProvider<State>::computeLocationTypeMapping(const HybridAutomaton<Number> &ha) {
        assert(mLocationSubspaceTypeMap.size() != 0);
        for (auto location: ha.getLocations()) {
            auto subspacetypesptr = mLocationSubspaceTypeMap.find(location)->second;
            std::vector<SUBSPACETYPE> subspacetypes = *subspacetypesptr;

            bool timed = true;
            bool rectangular = true;
            // bool lti = true;
            for (std::size_t i = 0; i < subspacetypes.size(); i++) {
                if (subspacetypes.at(i) == SUBSPACETYPE::LTI) {
                    timed = false;
                    rectangular = false;
                    break;
                } else if (subspacetypes.at(i) == SUBSPACETYPE::TIMED) {
                    rectangular = false;
                    // lti = true;
                } else if (subspacetypes.at(i) == SUBSPACETYPE::RECTANGULAR) {
                    timed = false;
                    // lti = false;
                    rectangular = true;
                    break;
                }
            }

            if (timed) {
                mLocationTypeMap.insert(std::make_pair(location, LOCATIONTYPE::TIMEDLOC));
            } else if (rectangular) {
                mLocationTypeMap.insert(std::make_pair(location, LOCATIONTYPE::RECTANGULARLOC));
            } else {
                mLocationTypeMap.insert(std::make_pair(location, LOCATIONTYPE::LTILOC));
            }

            DEBUG("hypro.utility",
                  "Types for location " << location->getName() << ":" << mLocationTypeMap.find(location)->second);
        }
    }

}  // namespace hypro
