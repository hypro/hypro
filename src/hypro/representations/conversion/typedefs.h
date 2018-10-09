template<typename Number>
using SupportFunctionNew = typename Converter<Number>::SupportFunctionNew;


template<typename Number>
using Box = typename Converter<Number>::Box;

template<typename Number>
using ConstraintSet = typename Converter<Number>::ConstraintSet;

template<typename Number>
using Ellipsoid = typename Converter<Number>::Ellipsoid;

/**
 * Typedef for HpolytopeT.
 */
template<typename Number>
using HPolytope = typename Converter<Number>::HPolytope;

template<typename Number>
using OrthogonalPolyhedron = typename Converter<Number>::OrthogonalPolyhedron;

/**
 * Typedef for VPolytopeT.
 */
template<typename Number>
using VPolytope = typename Converter<Number>::VPolytope;

#ifdef HYPRO_USE_PPL
template<typename Number>
using Polytope = typename Converter<Number>::Polytope;
#endif

/**
 * Typedef for SupportFunctionT.
 */
template<typename Number>
using SupportFunction = typename Converter<Number>::SupportFunction;

/**
 * Typedef for ZonotopeT.
 */
template<typename Number>
using Zonotope = typename Converter<Number>::Zonotope;

/**
 * Typedef for DifferenceBoundsT
 */
template<typename Number>
using DifferenceBounds = typename Converter<Number>::DifferenceBounds;
