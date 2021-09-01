#pragma once

namespace hypro {

template <typename Number>
using Box = typename Converter<Number>::Box;

template <typename Number>
using CarlPolytope = typename Converter<Number>::CarlPolytope;

template <typename Number>
using ConstraintSet = typename Converter<Number>::ConstraintSet;

template <typename Number>
using DifferenceBounds = typename Converter<Number>::DifferenceBounds;

template <typename Number>
using Ellipsoid = typename Converter<Number>::Ellipsoid;

template <typename Number>
using HPolytope = typename Converter<Number>::HPolytope;

template <typename Number>
using OrthogonalPolyhedron = typename Converter<Number>::OrthogonalPolyhedron;

template <typename Number>
using VPolytope = typename Converter<Number>::VPolytope;

#ifdef HYPRO_USE_PPL
template <typename Number>
using Polytope = typename Converter<Number>::Polytope;
#endif

template <typename Number>
using SupportFunction = typename Converter<Number>::SupportFunction;

template <typename Number>
using SupportFunctionNew = typename Converter<Number>::SupportFunctionNew;

template <typename Number>
using Zonotope = typename Converter<Number>::Zonotope;

template <typename Number>
using DifferenceBounds = typename Converter<Number>::DifferenceBounds;

template <typename Number>
using TemplatePolyhedron = typename Converter<Number>::TemplatePolyhedron;

// template<typename Number>
// using Orthoplex = typename Converter<Number>::Orthoplex;

}  // namespace hypro
