#pragma once
#include <tuple>

namespace hypro {

template <typename... T>
auto make_vector( T&&... args ) {
	using first_type = typename std::tuple_element<0, std::tuple<T...>>::type;
	return std::vector<first_type>{ std::forward<T>( args )... };
}

}  // namespace hypro
