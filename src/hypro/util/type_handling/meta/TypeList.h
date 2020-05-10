#pragma once

namespace hypro {

//This is used to carry a list of types
template <class... Types>
struct TypeList {};

//Takes a list of lists and concatenates them
//General template declaration
template <class List, class... Lists>
struct concat_i {
	//Concatenate first list into the result of concatenating all others
	using type = concat_i<List, concat_i<Lists...>>;
};

//Base case of concatenating two lists
template <class... Ts, class... Us>
struct concat_i<TypeList<Ts...>, TypeList<Us...>> {
	using type = TypeList<Ts..., Us...>;
};

//Quick access
template <class... Lists>
using concat = typename concat_i<Lists...>::type;

//Takes a template and a TypeList and applies the types in the List to the template
//Declaration
template <template <class...> class Templ, class ArgList>
struct apply_i;

//specialization for use case
template <template <class...> class Templ, class... Args>
struct apply_i<Templ, TypeList<Args...>> {
	using type = Templ<Args...>;
};

//Quick access
template <template <class...> class Templ, class ArgList>
using apply = typename apply_i<Templ, ArgList>::type;

}  // namespace hypro