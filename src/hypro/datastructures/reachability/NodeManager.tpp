#include "NodeManager.h"

namespace hypro
{
template<typename Number>
NodeManager<Number>::NodeManager() : mTree(ReachTree<Number>(new ReachTreeNode<Number>()))
{
}

template<typename Number>
typename ReachTreeNode<Number>::NodeList_t NodeManager<Number>::setInitialStates(const std::vector<State_t<Number>>& _init_states)
{
    assert(mTree.getRoot() != nullptr);
    typename ReachTreeNode<Number>::NodeList_t res;
    auto initialStatesIt = _init_states.begin();
    while (initialStatesIt != _init_states.end()) {
    	// create node for level 0.
    	//std::cout << "Create initial state from representation type " << initialStatesIt->getSetType(0) << std::endl;
        typename ReachTreeNode<Number>::Node_t temp(new ReachTreeNode<Number>(*initialStatesIt,0, mTree.getRoot()));
        temp->setTimestamp(0, carl::Interval<tNumber>(0));

        DEBUG("hydra.nodeManager", "Add node " << *temp);
        res.push_back(temp);
        mTree.getRoot()->addChild(temp);
        ++initialStatesIt;
    }
    mInitialStates = res;
    DEBUG("hydra.nodeManager","Done creating initial states.");
    DEBUG("hydra.nodeManager","Resulting tree: " );
    printTree(mTree.getRoot());
    return res;
}

template<typename Number>
typename ReachTreeNode<Number>::Node_t NodeManager<Number>::getNode(const std::vector<unsigned>& _id)
{
    assert(_id.size() > 0 && _id != std::vector<unsigned>(0));
    typename ReachTreeNode<Number>::Node_t result;
    typename ReachTreeNode<Number>::Node_t temp = mTree.getRoot();
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

template<typename Number>
bool NodeManager<Number>::fixedPointReached(const State_t<Number>& s)
{
    // Traverse the tree in order to check whether the calculated flowpipe
    // is contained in an already reached state
    for(const auto child : mTree.getRoot()->getChildren()) {
        if (child->hasFixedPoint(s,nullptr)) {
            return true;
        }
    }
    return false;
}

template<typename Number>
void NodeManager<Number>::printTree()
{
    printTree(mTree.getRoot());
}

template<typename Number>
void NodeManager<Number>::printTree(typename ReachTreeNode<Number>::Node_t )
{
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

} // hypro
