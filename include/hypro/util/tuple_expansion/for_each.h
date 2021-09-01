/**
 * With reference to https://stackoverflow.com/questions/16387354/template-tuple-calling-a-function-on-each-element
 */

#pragma once
#include <tuple>

namespace hypro {
namespace detail {
template <int... Is>
struct seq {};

template <int N, int... Is>
struct gen_seq : gen_seq<N - 1, N - 1, Is...> {};

template <int... Is>
struct gen_seq<0, Is...> : seq<Is...> {};

template <typename T, typename F, int... Is>
auto for_each( T&& t, F f, seq<Is...> ) {
	return { ( f( std::get<Is>( t ) ) )... };
}

template <typename T, typename F, int... Is>
auto for_each( T&& t1, T&& t2, F f, seq<Is...> ) {
	return { ( std::forward<F>( f )( std::get<Is>( std::forward<T>( t1 ) ), std::get<Is>( std::forward<T>( t2 ) ) ) )... };
}

template <typename T, typename P, typename F, int... Is>
auto for_each( T&& t, P&& p, F f, seq<Is...> ) {
	return { ( std::forward<F>( f )( std::get<Is>( std::forward<T>( t1 ) ), std::get<Is>( std::forward<T>( t2 ) ) ) )... };
}
}  // namespace detail

// apply a unary function to a tuple
template <typename... Ts, typename F>
std::tuple<Ts...> for_each_in_tuple( std::tuple<Ts...> const& t, F f ) {
	return detail::for_each( t, f, detail::gen_seq<sizeof...( Ts )>() );
}

template <typename... Ts, typename F>
std::tuple<std::pair<bool, Ts...>> for_each_in_tuple_pair( std::tuple<Ts...> const& t, F f ) {
	return detail::for_each( t, f, detail::gen_seq<sizeof...( Ts )>() );
}

// binary function
template <typename... Ts, typename F>
std::tuple<Ts...> for_each_in_tuple( std::tuple<Ts...> const& t1, std::tuple<Ts...> const& t2, F f ) {
	return detail::for_each( t1, t2, f, detail::gen_seq<sizeof...( Ts )>() );
}

}  // namespace hypro
