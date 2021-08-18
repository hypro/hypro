#pragma once

#include "../../util/typetraits.h"

namespace hypro {
/**
 * @brief Class defining an implementation of the quickhull algorithm to compute convex hulls of a set of vertices.
 *
 * @tparam Number Number type
 * @tparam true
 * @tparam void
 */
template <typename Number, bool Euclidian = true, typename = void>
class QuickhullAlgorithm;

/**
 * @brief Typedef for regular quickhull implementation for the Euclidean space
 *
 * @tparam Number
 */
template <typename Number>
using Quickhull = QuickhullAlgorithm<Number, true, void>;

/**
 * @brief Typedef for quickhull implementation in the projective space for vertex enumeration
 *
 * @tparam Number
 */
template <typename Number>
using QuickIntersection = QuickhullAlgorithm<Number, false, void>;
}  // namespace hypro

#include "quickhull_exact/Quickhull.h"