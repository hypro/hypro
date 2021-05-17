#include "ltiUrgencyHandler.h"

namespace hypro {

template <typename Representation>
std::vector<Representation> ltiUrgencyHandler<Representation>::urgentSetDifference(
        const std::vector<Representation>& segment, Transition<Number>* trans ) {
    std::vector<Representation> splitSegment;
    for ( const Representation& s : segment ) {
        std::vector<Representation> sDiff = setDifference( s, trans->getGuard() );
        splitSegment.insert( splitSegment.end(), sDiff.begin(), sDiff.end() );
    }
    return splitSegment;
}

} // namespace hypro