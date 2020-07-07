#pragma once

namespace hypro {
namespace detail {

/// recursive call to get the nth element of a type list
template <std::size_t I, typename T, typename... Ts>
struct nth_element_impl {
	using type = typename nth_element_impl<I - 1, Ts...>::type;
};

/// base case of getting the nth element of a type list
template <typename T, typename... Ts>
struct nth_element_impl<0, T, Ts...> {
	using type = T;
};

}  // namespace detail

/// returns the nth type of a type list
template <std::size_t I, typename... Ts>
using nth_element = typename detail::nth_element_impl<I, Ts...>::type;

}  // namespace hypro