# State set representations {#generalStateSets}

Here we will present general information and intuition about the implemented state set representations. Note that this
page is not intended to provide complete theoretical background and will be extended in time.

## Boxes ##

![A box described by a vector of intervals](boxInterval.png)
![A box described by ist minimum and its maximum point](boxMinMaxPoint.png)

A box is defined by the cross product of intervals, one for each dimension of the state space:

A set \f$\mathcal{B}\subseteq\mathbb{R}^d\f$ is a box if there exist intervals \f$I_1,\ldots,I_d \in \mathbb{I}\f$ such
that
\f[
\mathcal{B} = I_0 \times \ldots \times I_d\, .
\f]

A box can be represented by the sequence \f$(I_1,\ldots,I_d)\f$ of the intervals defining it.
Alternatively, we can represent a box by its minimal and
its maximal point. Boxes are well-suited for fast computations in flowpipe construction, however, they often lead to
large over-approximations.
Boxes are widely used also in other fields such as in interval constraint propagation (ICP), which itself is used for
SMT-solving-based reachability analysis of hybrid systems \cite isat . Implementations of boxes are also contained in
most polytope libraries, e.g. \cite BagnaraHZ08SCP \cite polymake.

## Polytopes ##

![A polytope in its H-representation](hPolytope.png)
![A polytope in its V-representation](vPolytope.png)

A convex polyhedron can be defined by the intersection of finitely many halfspaces:
A set \f$\mathcal{P}\subseteq\mathbb{R}^d\f$ is a convex polyhedron if there are \f$n\in\mathbb{N}\f$ and
\f$c_i\in\mathbb{R}^n\f$, \f$d_i \in \mathbb{R}\f$, \f$i=1,\ldots,n\f$ such that
\f[
\mathcal{P} = \bigcap_{i=1}^n h_i \text{ where }
h_i = \{x\in\mathbb{R}^d \ |\ c_i x\leq d_i\}\, .
\f]

In HyPro we restrict ourselves to closed convex polyhedra
called convex polytopes, which have two widely used
representations. An \f$\mathcal{H}\f$-representation \f$(C,d)\f$
consists of a \f$n\times d\f$ matrix \f$C\f$ with \f$c_i\f$ being its \f$i\f$th row
and an \f$n\f$-dimensional vector \f$d\f$ with \f$d_i\f$ being its \f$i\f$th
components, and specifies the polytope \f$\mathcal{P} = \bigcap_{i=1}^n \{x
\ |\ c_i x\leq d_i\}\f$.
Alternatively, a \f$\mathcal{V}\f$-representation consists of a finite set
\f$V\f$ of \f$d\f$-dimensional points and specifies a polytope as the convex
hull \f$\mathcal{P} = \textit{conv}(V)\f$ of those points.

Polytopes are a more complex representation as for instance boxes but allow for a more precise description of a set. The
two presented representations are complementary in the complexity of the required operations for reachability analysis.
Computing the convex hull of union requires little computational effort in the \f$\mathcal{V}\f$-repre\-sentation but is
hard in the \f$\mathcal{V}\f$-representation, whereas intersection can easily be performed with the
\f$\mathcal{H}\f$-repre\-sentation of a polytope but it is hard in the \f$\mathcal{V}\f$-repre\-sen\-tation.
Unfortunately, conversion between the two representation requires either facet enumeration of a set of vertices or
vertex enumeration of a set of hyperplanes, which are both computationally difficult. There are libraries already
providing implementations of convex polytopes such as \cite BagnaraHZ08SCP \cite polymake, but as they are intended to
provide general purpose implementations, functionality required for hybrid systems reachability analysis is not fully
optimized (e.g. PPL does currently not provide Minkowski sum implementations).

## Zonotopes ##

![A zonotope](zonotope.png)

Zonotopes, sometimes also referred to as parallelotopes, are point-symmetric sets that can be defined as the Minkowski
sum of a finite set of line segments shifted to a given centre point.

A set \f$\mathcal{Z}\subseteq\mathbb{R}\f$ is a zonotope if there is a center \f$c\in\mathbb{R}^n\f$ and a finite set
\f$G=\{g_1,\ldots,g_n\}\f$ of generators \f$g_i\in \mathbb{R}^d\f$ such that
\f[
\mathcal{Z} = \left\lbrace x\ \bigg|\ x = c + \sum_i^n \lambda_i\cdot g_i,\ {-1}\leq \lambda_i \leq 1 \right\rbrace\, .
\f]

Zonotopes can be represented by their defining vectors \f$(c,g_1,\ldots,g_n)\f$, i.e., by their centre and the
generators.

Zonotopes are and due to their structure allow for a fast computation of the operations union and Minkowski sum.
However, intersections with halfspaces or other zonotopes are hard to compute. Zonotopes are often used due to their
reduced storage requirement in comparison to for example convex polytopes. Zonotope implementations are contained in the
C++ library polymake as well as in the Matlab tool collection \cora.

## Support functions ##

![A set described by a support function](supportFunction.png)

Support functions are, in contrast to the above presented representations, a symbolic representation, which allows
queries for specific directions and will return a support value (see Figure \ref{fig:supportFunction}).
A support function is a function \f$\sigma:\mathbb{R}^d\rightarrow\mathbb{R}\f$ defining a set
\f[
\mathcal{S} = \left\lbrace x\in\mathbb{R}^d\ \big|\ r\cdot x \leq \sigma(r) \text{ for all } r\in\mathbb{R}^d \right\rbrace\, ,
\f]
where \f$\sigma(r)\in\mathbb{R}\f$ is called the support value for the given direction \f$r\in\mathbb{R}^d\f$.

The definition of support functions allows for an implementation, which reduces computation time during reachability
analysis significantly. This is due to the fact that while other representations always maintain the whole object,
support functions only need to store the operation and its parameters. Whenever the support value of a given direction
is queried, the stored operations are applied reversed on the direction vector instead of applying them to the whole
object. This implies that only directions are computed which are of interest instead of the whole object. The
disadvantage of this representation is, that unless infinitely many directions are queried, the exact shape of the set
is hidden. Support functions are used for example in the tool \spaceex, which successfully makes use of algorithms
optimized for support functions (LGG \cite LeGuernicG10, \cite FrehseLGDRLRGDM11, STC \cite stc, \cite Frehse2015).

## Taylor models ##
