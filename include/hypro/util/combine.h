#pragma once

#include <boost/range/combine.hpp>

// destructuring fix for boost tuple
namespace std {
template <typename T, typename U>
struct tuple_size<boost::tuples::cons<T, U>>
	: boost::tuples::length<boost::tuples::cons<T, U>> {};

template <size_t I, typename T, typename U>
struct tuple_element<I, boost::tuples::cons<T, U>>
	: boost::tuples::element<int( I ), boost::tuples::cons<T, U>> {};
}  // namespace std