/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "ContextFactory.h"

namespace hypro {
    template<typename State>
    IContext *ContextFactory<State>::createContext(const std::shared_ptr<Task<State>> &t,
                                                   const Strategy<State> &strat,
                                                   WorkQueue<std::shared_ptr<Task<State>>> *localQueue,
                                                   WorkQueue<std::shared_ptr<Task<State>>> *localCEXQueue,
                                                   Flowpipe<State> &localSegments,
                                                   hypro::ReachabilitySettings &settings) {
        if (SettingsProvider<State>::getInstance().getStrategy().getParameters(t->btInfo.btLevel).representation_type ==
            representation_name::polytope_t) {
            DEBUG("hydra.worker", "Using TPoly context!");
            return new TemplatePolyhedronContext<State>(t, strat, localQueue, localCEXQueue, localSegments, settings);
        }
        if (SettingsProvider<State>::getInstance().useDecider()) {
            auto locType = SettingsProvider<State>::getInstance().getLocationTypeMap().find(
                    t->treeNode->getStateAtLevel(t->btInfo.btLevel).getLocation())->second;
            if (locType == hypro::LOCATIONTYPE::TIMEDLOC) {
                // either use on full timed automa or if context switch is enabled
                if (SettingsProvider<State>::getInstance().isFullTimed() ||
                    SettingsProvider<State>::getInstance().useContextSwitch()) {
                    DEBUG("hydra.worker", "Using full timed context!");
                    return new TimedContext<State>(t, strat, localQueue, localCEXQueue, localSegments, settings);
                }
            } else if (locType == hypro::LOCATIONTYPE::RECTANGULARLOC) {
                DEBUG("hydra.worker", "Using lti context, but actually is rectangular!");
                return new LTIContext<State>(t, strat, localQueue, localCEXQueue, localSegments, settings);
            }
        }
        DEBUG("hydra.worker", "Using standard LTI context!");
        return new LTIContext<State>(t, strat, localQueue, localCEXQueue, localSegments, settings);
    }

}  // namespace hypro
