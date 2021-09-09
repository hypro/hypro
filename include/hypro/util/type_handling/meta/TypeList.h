#pragma once

namespace hypro {

/// This is used to carry a list of types
template <class... Types>
struct TypeList {};

/// Takes a list of lists and concatenates them
/// General template declaration
template <class List, class... Lists>
struct concat_i {
	// Concatenate first list into the result of concatenating all others
	using type = typename concat_i<List, typename concat_i<Lists...>::type>::type;
};

/// Base case of concatenating two lists
template <class... Ts, class... Us>
struct concat_i<TypeList<Ts...>, TypeList<Us...>> {
	using type = TypeList<Ts..., Us...>;
};

template <class... Ts>
struct concat_i<TypeList<Ts...>> {
	using type = TypeList<Ts...>;
};

/// Quick access
template <class... Lists>
using concat = typename concat_i<Lists...>::type;

/// Tests for concat
static_assert( std::is_same_v<concat<TypeList<int>, TypeList<double>, TypeList<std::size_t>>, TypeList<int, double, std::size_t>> );

/// Takes a template and a TypeList and applies the types in the List to the template Declaration
template <template <class...> class Templ, class ArgList>
struct apply_i;

/// specialization for use case
template <template <class...> class Templ, class... Args>
struct apply_i<Templ, TypeList<Args...>> {
	using type = Templ<Args...>;
};

/// Quick access
template <template <class...> class Templ, class ArgList>
using apply = typename apply_i<Templ, ArgList>::type;

}  // namespace hypro