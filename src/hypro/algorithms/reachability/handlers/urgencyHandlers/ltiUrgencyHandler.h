#pragma once

namespace hypro {

template <typename Representation>
class ltiUrgencyHandler {
    using Number = typename Representation::NumberType;

  public:
    std::vector<Representation> urgentSetDifference( const std::vector<Representation>& segment, Transition<Number>* trans );
}


}  // namespace hypro

#include "ltiUrgencyHandler.tpp"
