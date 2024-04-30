

/*
 * Copyright (c) 2022-2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

namespace hypro {

    template<typename Representation, typename Location>
    ReachTreeNode<Representation, Location> &
    ReachTreeNode<Representation, Location>::addChild(Representation initialSet,
                                                      carl::Interval<SegmentInd> timings,
                                                      const TransitionT *transition) {
        return Base::addChild(this, transition, transition->getTarget(), std::move(initialSet), timings);
    }

    template<typename Representation, typename Location>
    auto ReachTreeNode<Representation, Location>::getPath() const -> Path<Number, Location> {
        Path<Number, Location> path{this->mDepth};

        size_t currentPos = this->mDepth;  // one past end
        auto const *node = this;

        while (node->mParent != nullptr) {
            currentPos -= 1;
            path.elements[currentPos] = std::pair(node->mTimings, node->mTransition);
            node = node->mParent;
        }

        path.rootLocation = node->getLocation();

        assert(currentPos == 0);

        return path;
    }

    template<typename Representation, typename Location>
    std::vector<ReachTreeNode<Representation, Location> const *>
    ReachTreeNode<Representation, Location>::getTreePath() const {
        std::vector<ReachTreeNode<Representation, Location> const *> path;

        auto const *node = this;
        while (node->mParent != nullptr) {
            path.push_back(node);
            node = node->mParent;
        }
        return path;
    }

    template<typename Representation, typename Location>
    void ReachTreeNode<Representation, Location>::setFixedPoint(bool hasFixedPoint,
                                                                ReachTreeNode<Representation, Location> *reason) {
        mHasFixedPoint = hasFixedPoint ? TRIBOOL::TRUE : TRIBOOL::FALSE;
        mFixedPointReason = reason;
        // recursively mark nodes
        if (this->getParent() != nullptr) {
            if (std::all_of(std::begin(this->getParent()->getChildren()), std::end(this->getParent()->getChildren()),
                            [](const auto *child) { return (child->hasFixedPoint() == TRIBOOL::TRUE); })) {
                COUNT("recursive fixed point");
                this->getParent()->setFixedPoint(true, reason);
            }
        }
    }

    template<typename Representation, typename Location>
    std::map<size_t, ReachTreeNode<Representation, Location>*> 
    ReachTreeNode<Representation, Location>::updateTreeWithSyncNodes(std::map<size_t, ReachTreeNode<Representation, Location>* > indexNodeMap){
        ReachTreeNode<Representation, Location>* nextNode=nullptr;
        std::map<size_t, ReachTreeNode<Representation, Location>*> nextMap{ indexNodeMap };
        for (size_t i=0; i<mSyncNodes.size(); i++){
            if (mSyncNodes[i]!=nullptr){
                nextNode = mSyncNodes[i];
                nextMap.insert(std::make_pair(i, nextNode));
            }
        }
        if (nextNode!=nullptr){
            auto completeSyncMap = nextNode->updateTreeWithSyncNodes(nextMap);
            // update syncNodes with completeSyncMap
            for (auto& indexNodePair : completeSyncMap){
                mSyncNodes[indexNodePair.first] = indexNodePair.second;
            }
            // update remaining nullptrs in mSyncNodes with the pointers from their parent node
            for (size_t i=0; i<mSyncNodes.size(); i++){
                if (mSyncNodes[i]==nullptr){
                    mSyncNodes[i] = &(this->getParent()->getSyncNodeAtIndex(i));
                }
            }
            for (size_t i=0; i<mSyncNodes.size(); i++) assert(mSyncNodes[i]!=nullptr);
            return completeSyncMap;
        } else {
            // update syncNodes with indexNodeMap
            for (auto& indexNodePair : indexNodeMap){
                mSyncNodes[indexNodePair.first] = indexNodePair.second;
            }
            // update remaining nullptrs in mSyncNodes with the pointers from their parent node
            for (size_t i=0; i<mSyncNodes.size(); i++){
                if (mSyncNodes[i]==nullptr){
                    mSyncNodes[i] = &(this->getParent()->getSyncNodeAtIndex(i));
                }
            }
            for (size_t i=0; i<mSyncNodes.size(); i++) assert(mSyncNodes[i]!=nullptr);
            return indexNodeMap;
        }
    }

}  // namespace hypro
