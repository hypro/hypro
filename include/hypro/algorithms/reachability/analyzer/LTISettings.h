#pragma once

// h file to hold the settings for the LTI analysis
// (an attempt to move away from the extensive number of template parameters)

namespace hypro {

    struct LTISetting {
        static constexpr bool USE_MULTITHREADING = false;
        // bool whether to calculate the under-approximation at the same time with the over-approximation
        static constexpr bool CALC_UNDERAPPROX = false;
    }

}