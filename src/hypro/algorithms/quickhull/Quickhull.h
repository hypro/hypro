#pragma once

#include "util/typetraits.h"

namespace hypro {
    template<typename Number, bool Euclidian = true, typename = void>
    class QuickhullAlgorithm;

    template<typename Number>
    using Quickhull = QuickhullAlgorithm<Number, true, void>;

    template<typename Number>
    using QuickIntersection = QuickhullAlgorithm<Number, false, void>;
}


#include "quickhull_exact/Quickhull.h"