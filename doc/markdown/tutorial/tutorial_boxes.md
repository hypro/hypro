# Boxes {#tutorial_boxes}

A short introduction of boxes.

## Construction
In HyPro a box in the _d_-dimensional space is represented as the Cartesian product of _d_ intervals (for a tutorial on intervals in HyPro see [here](tutorial_basic_datatypes)).
Thus, a box can be constructed from an ordered sequence of intervals, e.g.:

```c++
using Number = double;
using Interval = carl::Interval<Number>;

std::vector<Interval> intervals;
intervals.push_back(Interval(1,2));
intervals.push_back(Interval(3,4));

hypro::Box<Number> my_box{intervals};
```

creates a 2-dimensional box which covers the interval [1,2] in the first dimension and the interval [3,4] in the second dimension.
Note that we implicitly assume _weak_ bounds.
Technically, for boxes this is not required, however, to maintain compatibility with other state set representations all constraints in any case have _weak_ bounds.
This becomes clearer, when we construct a box from 2 points, the minimum and maximum point:

```c++
using Number = double;

hypro::Point<Number> min{1,2,3};
hypro::Point<Number> max{4,5,6};

hypro::Box<Number> my_box{std::make_pair(min, max)};
```
The resulting box `my_box` is a 3-dimensional box built from the intervals [1,4], [2,5], and [3,6].

## Properties

As for all provided state set representations, boxes feature the getter-functions `empty()`, `dimension()` and can be used as expected:

```c++
using Number = double;
using Interval = carl::Interval<Number>;
[...]

hypro::Box<Number> my_box{intervals};
bool my_box_empty = my_box.empty(); // should be false
std::size_t dim = my_box.dimension(); // dimension of the embedding state space
```

## Modification

TBA

## Operations

Following the interface `GeometricObjectBase`, boxes implement several operations required for the reachability analysis of linear hybrid systems.

```c++
using Number = double;
using Interval = carl::Interval<Number>;
[...]

hypro::Box<Number> A{intervals1};
hypro::Box<Number> B{intervals2};

// compute the intersection of A and B, should be symmetric
hypro::Box<Number> C = A.intersect(B);
hypro::Box<Number> C_prime = B.intersect(A);
assert(C == C_prime);

// compute the convex closure of the union of A and B
hypro::Box<Number> D = A.unite(B);
assert(D.contains(A) && D.contains(B));
```