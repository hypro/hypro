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

    template<typename Number>
    using Box = typename Converter<Number>::Box;

    template<typename Number>
    using CarlPolytope = typename Converter<Number>::CarlPolytope;

    template<typename Number>
    using ConstraintSet = typename Converter<Number>::ConstraintSet;

    template<typename Number>
    using DifferenceBounds = typename Converter<Number>::DifferenceBounds;

    template<typename Number>
    using Ellipsoid = typename Converter<Number>::Ellipsoid;

    template<typename Number>
    using HPolytope = typename Converter<Number>::HPolytope;

    template<typename Number>
    using OrthogonalPolyhedron = typename Converter<Number>::OrthogonalPolyhedron;

    template<typename Number>
    using VPolytope = typename Converter<Number>::VPolytope;

#ifdef HYPRO_USE_PPL
    template <typename Number>
    using Polytope = typename Converter<Number>::Polytope;
#endif

    template<typename Number>
    using SupportFunction = typename Converter<Number>::SupportFunction;

    template<typename Number>
    using SupportFunctionNew = typename Converter<Number>::SupportFunctionNew;

    template<typename Number>
    using Zonotope = typename Converter<Number>::Zonotope;

    template<typename Number>
    using DifferenceBounds = typename Converter<Number>::DifferenceBounds;

    template<typename Number>
    using TemplatePolyhedron = typename Converter<Number>::TemplatePolyhedron;

    template<typename Number>
    using Starset = typename Converter<Number>::Starset;

// template<typename Number>
// using Orthoplex = typename Converter<Number>::Orthoplex;

}  // namespace hypro
