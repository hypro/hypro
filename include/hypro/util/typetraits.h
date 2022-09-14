#pragma once
#include "../types.h"

#include <memory>
#include <type_traits>

namespace hypro {

template <typename T>
struct is_shared_ptr : std::false_type {};

template <typename T>
struct is_shared_ptr<std::shared_ptr<T>> : std::true_type {};

template <class T>
struct is_unique_ptr : std::false_type {};

template <class T, class D>
struct is_unique_ptr<std::unique_ptr<T, D>> : std::true_type {};

// TODO generalize with nth element type trait
// representation traits
template <class Representation>
struct rep_number_i;

template <template <class...> class Rep, class Number, class... Ts>
struct rep_number_i<Rep<Number, Ts...>> {
	using type = Number;
};

template <class Representation>
using rep_number = typename rep_number_i<Representation>::type;

// analyzer type trait
template <class Representation>
struct analyzer_rep_i;

template <template <class...> class Analyzer, class Rep, class... Ts>
struct analyzer_rep_i<Analyzer<Rep, Ts...>> {
	using type = Rep;
};

template <class Analyzer>
using analyzer_rep = typename analyzer_rep_i<std::remove_pointer_t<std::remove_reference_t<std::remove_cv_t<Analyzer>>>>::type;

// short hands
template <bool B>
using enable_if = std::enable_if_t<B, int>;

template <typename T, typename U>
constexpr bool convertible = std::is_convertible_v<T, U>;

// number traits
template <typename Number>
inline constexpr bool is_exact = std::is_same_v<Number, mpq_class>;

template <typename Number>
using EnableIfExact = std::enable_if_t<is_exact<Number>>;

template <typename Number>
using EnableIfFloatingpoint = std::enable_if_t<std::is_floating_point_v<Number>>;

}  // namespace hypro
