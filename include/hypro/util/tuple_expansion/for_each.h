/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/**
 * With reference to https://stackoverflow.com/questions/16387354/template-tuple-calling-a-function-on-each-element
 */

#pragma once

#include <tuple>

namespace hypro {
    namespace detail {
        template<int... Is>
        struct seq {
        };

        template<int N, int... Is>
        struct gen_seq : gen_seq<N - 1, N - 1, Is...> {
        };

        template<int... Is>
        struct gen_seq<0, Is...> : seq<Is...> {
        };

        template<typename T, typename F, int... Is>
        auto for_each(T &&t, F f, seq<Is...>) {
            return {(f(std::get<Is>(t)))...};
        }

        template<typename T, typename F, int... Is>
        auto for_each(T &&t1, T &&t2, F f, seq<Is...>) {
            return {(std::forward<F>(f)(std::get<Is>(std::forward<T>(t1)), std::get<Is>(std::forward<T>(t2))))...};
        }

        template<typename T, typename P, typename F, int... Is>
        auto for_each(T &&t, P &&p, F f, seq<Is...>) {
            return {(std::forward<F>(f)(std::get<Is>(std::forward<T>(t1)), std::get<Is>(std::forward<T>(t2))))...};
        }
    }  // namespace detail

// apply a unary function to a tuple
    template<typename... Ts, typename F>
    std::tuple<Ts...> for_each_in_tuple(std::tuple < Ts...
    > const& t,
    F f
    ) {
    return
    detail::for_each( t, f, detail::gen_seq<sizeof...(Ts)>()
    );
}

template<typename... Ts, typename F>
std::tuple <std::pair<bool, Ts...>> for_each_in_tuple_pair(std::tuple < Ts...
> const& t,
F f
) {
return
detail::for_each( t, f, detail::gen_seq<sizeof...(Ts)>()
);
}

// binary function
template<typename... Ts, typename F>
std::tuple<Ts...> for_each_in_tuple(std::tuple < Ts...
> const& t1,
std::tuple<Ts...> const &t2, F
f ) {
return
detail::for_each( t1, t2, f, detail::gen_seq<sizeof...(Ts)>()
);
}

}  // namespace hypro
