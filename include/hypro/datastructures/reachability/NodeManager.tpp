/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "NodeManager.h"

namespace hypro {
    template<typename State>
    NodeManager<State>::NodeManager()
            : mTree(ReachTree<State>(new ReachTreeNode<State>())) {
    }

    template<typename State>
    typename ReachTreeNode<State>::NodeList_t
    NodeManager<State>::setInitialStates(const std::vector<State> &_init_states) {
        assert(mTree.getRoot() != nullptr);
        typename ReachTreeNode<State>::NodeList_t res;
        auto initialStatesIt = _init_states.begin();
        while (initialStatesIt != _init_states.end()) {
            // create node for level 0.
            // std::cout << "Create initial state from representation type " << initialStatesIt->getSetType(0) << std::endl;
            typename ReachTreeNode<State>::Node_t temp(new ReachTreeNode<State>(*initialStatesIt, 0, mTree.getRoot()));
            temp->setTimestamp(0, carl::Interval<tNumber>(0));

            DEBUG("hydra.nodeManager", "Add node " << *temp);
            res.push_back(temp);
            mTree.getRoot()->addChild(temp);
            ++initialStatesIt;
        }
        mInitialStates = res;
        DEBUG("hydra.nodeManager", "Done creating initial states.");
        DEBUG("hydra.nodeManager", "Resulting tree: ");
        printTree(mTree.getRoot());
        return res;
    }

    template<typename State>
    typename ReachTreeNode<State>::Node_t NodeManager<State>::getNode(const std::vector<unsigned> &_id) {
        assert(_id.size() > 0 && _id != std::vector<unsigned>(0));
        typename ReachTreeNode<State>::Node_t result;
        typename ReachTreeNode<State>::Node_t temp = mTree.getRoot();
        auto _id_iter = _id.begin();
        // Do one iteration 'manually' due to the fact that the root is
        // a supertype of the childrens' nodes
        result = (temp->getChildren()).at(*_id_iter);
        ++_id_iter;
        while (_id_iter != _id.end()) {
            result = (result->getChildren()).at(*_id_iter);
            ++_id_iter;
        }
        return result;
    }

    template<typename State>
    bool NodeManager<State>::fixedPointReached(const State &s) {
        // Traverse the tree in order to check whether the calculated flowpipe
        // is contained in an already reached state
        for (const auto child: mTree.getRoot()->getChildren()) {
            if (child->hasFixedPoint(s, nullptr)) {
                return true;
            }
        }
        return false;
    }

    template<typename State>
    void NodeManager<State>::printTree() {
        printTree(mTree.getRoot());
    }

    template<typename State>
    void NodeManager<State>::printTree(typename ReachTreeNode<State>::Node_t) {
        /*
        std::cout << "Address: " << _node << endl;
        if(_node->getLocation() != nullptr) {
            std::cout << "Path to node (location sequence): " << _node->getLocation()->getId();
        }
        auto parent = _node->getParent();
        while (parent != nullptr) {
            if(parent->getLocation() != nullptr) {
                std::cout << parent->getLocation()->getId()  << ", ";
            }
            parent = parent->getParent();
        }
        std::cout << endl << "Depth: " << _node->getDepth() << endl;
        auto iter_node = _node->getChildren().begin();
        while (iter_node != _node->getChildren().end()) {
            printTree(*iter_node);
            ++iter_node;
        }
       */
    }

}  // namespace hypro
