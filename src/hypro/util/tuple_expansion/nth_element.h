#pragma once

namespace hypro {
namespace detail {

template <std::size_t I, typename T, typename... Ts>
struct nth_element_impl {
	using type = typename nth_element_impl<I - 1, Ts...>::type;
};

template <typename T, typename... Ts>
struct nth_element_impl<0, T, Ts...> {
	using type = T;
};

}  // namespace detail

template <std::size_t I, typename... Ts>
using nth_element = typename detail::nth_element_impl<I, Ts...>::type;

}  // namespace hypro