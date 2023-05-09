/*
 * Copyright (c) 2023-2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

#include "../../../types.h"
#include "../../../util/logging/Filewriter.h"
#include "../../../util/logging/Logger.h"
#include "../../HybridAutomaton/HybridAutomaton.h"
#include "../../HybridAutomaton/Pathv2.h"
#include "../Settings.h"
#include "../SettingsProvider.h"
#include "EventTimingContainer.h"
#include "EventTimingNode.h"

#include <optional>
#include <string>

namespace hypro {
    template<typename Number>
    class EventTimingProvider : public carl::Singleton<EventTimingProvider<Number>> {
        friend carl::Singleton<EventTimingProvider<Number>>;

    protected:
        EventTimingProvider();

    private:
        typename EventTimingNode<Number>::Node_t mRoot;
        std::string mName = "timingTree";

    public:
        void initialize(const HybridAutomaton<Number> &ha, tNumber globalTimeHorizon);

        void initialize(const Location<Number> *loc, tNumber globalTimeHorizon);

        void setName(const std::string &name) { mName = name; }

        const std::string &getName() const { return mName; }

        typename EventTimingNode<Number>::Node_t getRoot() { return mRoot; }

        void clear() {
            mRoot = std::make_shared<EventTimingNode<Number>>();
        }

        ~EventTimingProvider() {
        }

        /**
         * @brief	Find the best suitable node in the timing tree which matches the passed path.
         */
        typename EventTimingNode<Number>::Node_t
        getTimingNode(const Path<Number, tNumber> &path, std::size_t level = 0) const;

        /**
         * @brief	Find the best suitable node in the timing tree which matches the passed path.
         */
        typename EventTimingNode<Number>::Node_t &
        rGetNode(const Path<Number, tNumber> &path, std::size_t level = 0) const;

        std::optional<EventTimingContainer<Number>> getTimings(const Path<Number, tNumber> &path) const;

        void updateTimings(const Path<Number, tNumber> &path, const EventTimingContainer<Number> &update);

        typename EventTimingNode<Number>::Node_t
        addChildToNode(typename EventTimingNode<Number>::Node_t parent, tNumber timeHorizon);

        std::string getDotRepresentation() const;

    private:
        typename EventTimingNode<Number>::Node_t findNode(const Path<Number, tNumber> &path, std::size_t level) const;

        void writeTree() const;

        // for dbg
        void printSet(const std::vector<std::set<EventTimingNode<Number> *>> &sets) const {
            TRACE("hypro.datastructures.timing", "Have " << sets.size() << " sets.");
            for (const auto &set: sets) {
                TRACE("hypro.datastructures.timing", "Have " << set.size() << " containers.");
                for (const auto sPtr: set) {
                    TRACE("hypro.datastructures.timing", "Container " << *sPtr);
                }
            }
        }
    };

}  // namespace hypro

#include "EventTimingProvider.tpp"
