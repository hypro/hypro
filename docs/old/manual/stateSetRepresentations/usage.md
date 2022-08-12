# Usage {#usage}

HyPro is designed to unify different implementations of state set representations in one common interface, which allows
to implement state-of-the-art reachability analysis algorithms. We therefore identified the most common operations
required and created an interface, which each provided state set representation implements (\ref hypro::GeometricObject<
Number,DerivedShape> "GeometricObject").

The interface holds the basic set operations

* convex hull of the union of two sets
* intersection
* Minkowski's sum
* test for emptiness
* combined operations for intersection with halfspaces and tests for emptiness afterwards
* projection
* linear and affine transformations

In the next section we show on the example of boxes and polytopes how to use the library and the unified interface.

## Examples ##

As the interface is mostly unified, we show examples on our box implementation and on our H-polytope implementation:

- @ref example_box.cpp "Working with boxes."
- @ref example_HPolytope.cpp "Working with H-polytopes."

Additional examples such as @ref example_bouncingBall.cpp show how to manually create a hybrid automaton and invoke the
built-in reachability analysis algorithm (Reach.h).
