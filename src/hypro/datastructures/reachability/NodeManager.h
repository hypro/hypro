/*
 * File:   NodeManager.h
 * Author: Dustin Hütter <dustin.huetter@rwth-aachen.de>
 *
 * Created on April 15, 2016, 11:38 AM
 */

#pragma once
#include "ReachTree.h"
#include "ReachTreeNode.h"
#include "../HybridAutomaton/Location.h"
#include "../HybridAutomaton/State.h"
#include "../HybridAutomaton/Transition.h"
#include "../../representations/GeometricObject.h"
#include "../../util/logging/Logger.h"
#include <boost/tuple/tuple.hpp>
#include <carl/util/Singleton.h>
#include <iostream>

namespace hypro
{
template<typename Number>
using initialData = boost::tuple<const Location<Number>*, typename State_t<Number>::repVariant, Number, representation_name>;

template<typename Number>
class NodeManager : public carl::Singleton<NodeManager<Number>>
{
    friend carl::Singleton<NodeManager<Number>>;

  private:
    typename ReachTreeNode<Number>::NodeList_t mInitialStates;
    ReachTree<Number> mTree;
    //bool checkChildrenFixedPoint(const Location<Number>* _loc_new_node, const flowpipe_t& _new_flowpipe, ReachTreeNode::Node_t _to_be_checked);

    NodeManager();
    ~NodeManager() {}

  public:

    // The constructor to be used when the initial states are inserted into the tree
    // Note: The default constructor must have been called before to obtain defined behavior
    // NodeManager( std::vector<initialData> _init_states );
    typename ReachTreeNode<Number>::NodeList_t setInitialStates(const std::vector<State_t<Number>>& _init_states);
    typename ReachTreeNode<Number>::Node_t getNode(const std::vector<unsigned>& _id);
    bool fixedPointReached(const State_t<Number>& s);
    void printTree();
    const ReachTree<Number>& getTree() const { return mTree; }
    static void printTree(typename ReachTreeNode<Number>::Node_t _node);
};

} // hypro

#include "NodeManager.tpp"
