#pragma once

namespace hypro {

/// This is used to carry a list of types
template <class... Types>
struct TypeList {};

/// Takes a list of lists and concatenates them
/// General template declaration
template <class List, class... Lists>
struct concat_i {
	//Concatenate first list into the result of concatenating all others
	using type = typename concat_i<List, typename concat_i<Lists...>::type>::type;
};

/// Base case of concatenating two lists
template <class... Ts, class... Us>
struct concat_i<TypeList<Ts...>, TypeList<Us...>> {
	using type = TypeList<Ts..., Us...>;
};

template<class... Ts>
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

template <class T, class List>
struct contains_i : std::false_type {};

template <class T, class... Ts>
struct contains_i<T, TypeList<T, Ts...>> : std::true_type {};

template <class T, class THead, class... Ts>
struct contains_i<T, TypeList<THead, Ts...>> : contains_i<T, TypeList<Ts...>> {};

/// Quick access
template <class T, class List>
using contains_v = typename contains_i<T, List>::type;

// Tests for contains
static_assert(std::is_same_v<std::true_type, contains_v<int, TypeList<double,int>>>);
static_assert(std::is_same_v<std::false_type, contains_v<int, TypeList<double,double>>>);


// Eliminate duplicate entries from a TypeList, reference: https://stackoverflow.com/a/13840677
template <class R, class RList, class duplicate = contains_v<R, RList>>
struct add_unique;

// If R is in the list, return the list unmodified
template <class R, class... Rs>
struct add_unique <R, TypeList<Rs...>, std::true_type> { typedef TypeList<Rs...> type; };

// If R is not in the list, append it
template <class R, class... Rs>
struct add_unique <R, TypeList <Rs...>, std::false_type> { typedef TypeList <R, Rs...> type; };

template <class... Rs>
struct UniqueTypeList_i;

template <class R, class... Rs>
struct UniqueTypeList_i <R, Rs...> { typedef typename add_unique<R, typename UniqueTypeList_i<Rs...>::type>::type type; };

template <class R>
struct UniqueTypeList_i <R> { typedef TypeList<R> type; };

template <>
struct UniqueTypeList_i <> { typedef TypeList<> type; };

/// Quick access
template <class... Rs>
using UniqueTypeList = typename UniqueTypeList_i<Rs...>::type;


static_assert(std::is_same_v<UniqueTypeList<int, double, int>, TypeList<double, int>>);
static_assert(std::is_same_v<UniqueTypeList<int, double, double>, TypeList<int, double>>);


}  // namespace hypro