---
title: State Set Representations
sidebar: mydoc_sidebar
permalink: stateSetRepresentations.html
folder: mydoc
use_math: true
---

All state set representations in HyPro share a common interface, that we will outline in the following. Additional
functions born from practical applications or representation-specific requirements may extend the API of certain state
set representations.

## General Interface

In the following, we assume `TYPE` to be the used state set representation and `Number` to be the used number type. The
common API should define the following member functions:

- Construction: all state set representations are expected to be constructible from:
    - a set of points whose convex hull outlines the set to be represented, and
    - a pair of a matrix A and a vector b which represent the set of all points x which satisfy $$A\cdot x \leq b$$ .
- `static TYPE Empty()`: a function that allows to create an empty set.
- `bool empty() const`: a function that returns, whether the set is empty.
- `std::vector<Point<Number>> vertices( const matrix_t<Number>& = matrix_t<Number>::Zero( 0, 0 ) ) const`: a function
  returning the vertices of the represented set. The additional matrix is only relevant for support functions, where a
  template can be communicated.
- `EvaluationResult<Number> evaluate( const vector_t<Number>& _direction, bool = true ) const`: a function to compute
  the maximum (if the passed bool is true) point in the set according to the passed cost function represented by a
  vector.
- `std::vector<EvaluationResult<Number>> multiEvaluate( const matrix_t<Number>& _directions, bool useExact = true ) const`:
  similar to `evaluate`, but computes multiple results according to different cost functions collected in the passed
  matrix.
- `std::size_t dimension() const`: a function returning the state space dimension.
- `void removeRedundancy()`: a function to remove redundancy in the representation, i.e., points that are no vertices in
  a v-polytope.
- `std::pair<CONTAINMENT, TYPE> satisfiesHalfspace( const Halfspace<Number>& rhs ) const`: a function that determines,
  whether points of the set satisfy the halfspace. It returns information about how well the set is contained in the
  halfspace as well as the part of the set that is contained (can be empty).
- `std::pair<CONTAINMENT, TYPE> satisfiesHalfspaces( const matrix_t<Number>& _mat, const vector_t<Number>& _vec ) const`:
  as before, but for multiple halfspaces.
- `TYPE linearTransformation( const matrix_t<Number>& A ) const`: applies a linear transformation according to the
  passed matrix.
- `TYPE affineTransformation( const matrix_t<Number>& A, const vector_t<Number>& b ) const`: applies an affine
  transformation according to the passed matrix and vector.
- `TYPE minkowskiSum( const TYPE& rhs ) const`: computes the Minkowski sum of two sets.
- `TYPE intersect( const TYPE& rhs ) const`: computes the intersection of two sets.
- `TYPE intersectHalfspace( const Halfspace<Number>& hspace ) const`: computes the intersection of a set and a
  halfspace.
- `TYPE intersectHalfspaces( const matrix_t<Number>& _mat, const vector_t<Number>& _vec ) const`: computes the
  intersection of a set and multiple halfspaces.
- `bool contains( const Point<Number>& point ) const`: checks, whether the set contains a given point.
- `bool contains( const TYPE& box ) const`: checks, whether the set contains a given set.
- `TYPE unite( const TYPE& rhs ) const`: computes the convex hull of the union of two sets.

{% include links.html %}
