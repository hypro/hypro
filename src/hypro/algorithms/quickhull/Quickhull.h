#pragma once

#include "number_traits.h"

namespace hypro {
    template<typename Number, bool Euclidian = true, typename Enable = void>
    class Quickhull;

    template<typename Number, bool Euclidian = true>
    using ExactQuickhull = Quickhull<Number, Euclidian, EnableIfExact<Number>>;

    template<typename Number, bool Euclidian = true>
    using FloatQuickhull = Quickhull<Number, Euclidian, EnableIfFloatingpoint<Number>>;
}


#include "quickhull_exact/Quickhull.h"
#include "quickhull_floatingpoint/Quickhull.h"