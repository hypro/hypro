#pragma once
#include "EventTimingNode.h"

namespace hypro {

    /**
     * @brief Tests, whether the provided list of EventTimingNodes can be merged into one node dependend on the computed information.
     *
     * @param l
     * @return true
     * @return false
     */
    template<typename N>
    static bool canFullyBeMerged(std::initializer_list<EventTimingNode<N>*> l) {

    }

    template<typename N>
    static EventTimingNode<N>* merge(std::initializer_list<EventTimingNode<N>*> l) {

    }
} // namespace hypro
