/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

#include "TypeList.h"

namespace hypro {
/// Holds a representation and a list of viable settings for it
/// General case
    template<template<class...> class Representation, class... Settings>
    struct RepresentationCombinations {
        // Holds the list of Representations with the settings
        // Apply first setting and concat into the rest
        template<class Number, class Converter>
        using combinations = TypeList<Representation<Number, Converter, Settings>...>;
    };

/// Takes a Number and Converter type and a TypeList of RepresentationCombinations and flattens them into a TypeList of instantiations of Representations
    template<class Number, class Converter, class CombinationsList>
    struct flattenRepresentations_i;

/// Flattens representations list
    template<class Number, class Converter, class... RepCombinationsList>
    struct flattenRepresentations_i<Number, Converter, TypeList<RepCombinationsList...>> {
        // Use fold expression to concat the combinations lists of the RepresentationCombinations
        using type = concat<typename RepCombinationsList::template combinations<Number, Converter>...>;
    };

/// Quick access
    template<class Number, class Converter, class CombinationsList>
    using flattenRepresentations = typename flattenRepresentations_i<Number, Converter, CombinationsList>::type;
}  // namespace hypro
