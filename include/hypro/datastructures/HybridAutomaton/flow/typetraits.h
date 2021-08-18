#pragma once
#include "affine.h"
#include "linear.h"
#include "rectangular.h"

#include <type_traits>

namespace hypro {

template <typename T>
struct is_flow : std::false_type {};

template <typename N>
struct is_flow<affineFlow<N>> : std::true_type {};

template <typename N>
struct is_flow<linearFlow<N>> : std::true_type {};

template <typename N>
struct is_flow<rectangularFlow<N>> : std::true_type {};

}  // namespace hypro