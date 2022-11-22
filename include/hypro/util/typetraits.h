/*
 * Copyright (c) 2022.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

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

template <typename T>
struct is_location_type : std::false_type {};

}  // namespace hypro
