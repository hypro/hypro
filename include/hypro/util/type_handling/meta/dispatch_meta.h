/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

#include "../../unreachable.h"
#include "../representation_enums.h"
#include "../settings_enums.h"
#include "RepresentationCombinations.h"
#include "TypeList.h"

#include <assert.h>

namespace hypro {

// Maps an enum (or really any value) to each type. By default a static ::type_enum member is used so that a class can declare it itself. This may also be specialized elsewhere (simiar to std::hash) to provide the mapping.
    template<class T>
    static constexpr auto TypeEnum = T::type_enum;

// Takes a representation, unpacks its template arguments and allows matching against the TypeEnum values of those.
    template<class Representation>
    struct TypeMapping;

    template<template<class...> class R, class N, class C, class Setting>
    struct TypeMapping<R<N, C, Setting>> {
        static bool matches(representation_name representation, int setting) {
            return TypeEnum<R<N, C, Setting>> == representation && TypeEnum<Setting> == setting;
        }
    };

/// Recursive dispatch to find correct representation
    template<class Representation, class... Representations>
    struct Dispatcher_i {
        template<class Callable, class... Args>
        static auto dispatch(representation_name representation, int setting, Callable c, Args &&... args) {
            if (TypeMapping<Representation>::matches(representation, setting)) {
                return c.template operator()<Representation>(std::forward<Args>(args)...);
            } else {
                return Dispatcher_i<Representations...>::dispatch(representation, setting, c,
                                                                  std::forward<Args>(args)...);
            }
        }
    };

/// Base case dispatch to find correct representation
    template<class Representation>
    struct Dispatcher_i<Representation> {
        template<class Callable, class... Args>
        static auto dispatch(representation_name representation, int setting, Callable c, Args &&... args) {
            if (TypeMapping<Representation>::matches(representation, setting)) {
                return c.template operator()<Representation>(std::forward<Args>(args)...);
            }
            assert(false && "No representation was matched.");
            unreachable();
        }
    };

    template<class RepresentationsList>
    using Dispatcher = apply<Dispatcher_i, RepresentationsList>;
}  // namespace hypro
