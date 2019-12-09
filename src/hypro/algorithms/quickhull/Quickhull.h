#pragma once

#include "number_traits.h"

namespace hypro {
    template<typename Number, typename Enable = void>
    class Quickhull;

    template<typename Number>
    using ExactQuickhull = Quickhull<Number, EnableIfExact<Number>>;

    template<typename Number>
    using FloatQuickhull = Quickhull<Number, EnableIfFloatingpoint<Number>>;
}


#include "quickhull_exact/Quickhull.h"
#include "quickhull_floatingpoint/Quickhull.h"