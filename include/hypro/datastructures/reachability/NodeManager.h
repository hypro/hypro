/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/*
 * File:   NodeManager.h
 * Author: Dustin Hütter <dustin.huetter@rwth-aachen.de>
 *
 * Created on April 15, 2016, 11:38 AM
 */

#pragma once

#include "../../representations/GeometricObjectBase.h"
#include "../../util/logging/Logger.h"
#include "../HybridAutomaton/Location.h"
#include "../HybridAutomaton/State.h"
#include "../HybridAutomaton/Transition.h"
#include "ReachTreeNodev2.h"
#include "ReachTreev2.h"

#include <iosfwd>

namespace hypro {
    template<typename State>
    using initialData = std::tuple<const Location<typename State::NumberType> *, typename State::repVariant, typename State::NumberType, representation_name>;

    template<typename State>
    class NodeManager : public carl::Singleton<NodeManager<State>> {
        using Number = typename State::NumberType;
        friend carl::Singleton<NodeManager<State>>;

    private:
        typename ReachTreeNode<State>::NodeList_t mInitialStates;
        ReachTree <State> mTree;
        // bool checkChildrenFixedPoint(const Location<Number>* _loc_new_node, const flowpipe_t& _new_flowpipe, ReachTreeNode::Node_t _to_be_checked);

        NodeManager();

        ~NodeManager() {}

    public:
        // The constructor to be used when the initial states are inserted into the tree
        // Note: The default constructor must have been called before to obtain defined behavior
        // NodeManager( std::vector<initialData> _init_states );
        typename ReachTreeNode<State>::NodeList_t setInitialStates(const std::vector<State> &_init_states);

        typename ReachTreeNode<State>::Node_t getNode(const std::vector<unsigned> &_id);

        bool fixedPointReached(const State &s);

        void printTree();

        const ReachTree <State> &getTree() const { return mTree; }

        static void printTree(typename ReachTreeNode<State>::Node_t _node);
    };

}  // namespace hypro

#include "NodeManager.tpp"
