#pragma once
#include "carl/numbers/numbers.h"

#include <type_traits>

template <typename Number>
inline constexpr bool is_exact = std::is_same_v<Number, mpq_class>;

template <typename Number>
using EnableIfExact = std::enable_if_t<is_exact<Number>>;

template <typename Number>
using EnableIfFloatingpoint = std::enable_if_t<std::is_floating_point_v<Number>>;
