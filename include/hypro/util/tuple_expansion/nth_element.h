/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

namespace hypro {
    namespace detail {

/// recursive call to get the nth element of a type list
        template<std::size_t I, typename T, typename... Ts>
        struct nth_element_impl {
            using type = typename nth_element_impl<I - 1, Ts...>::type;
        };

/// base case of getting the nth element of a type list
        template<typename T, typename... Ts>
        struct nth_element_impl<0, T, Ts...> {
            using type = T;
        };

    }  // namespace detail

/// returns the nth type of a type list
    template<std::size_t I, typename... Ts>
    using nth_element = typename detail::nth_element_impl<I, Ts...>::type;

}  // namespace hypro
