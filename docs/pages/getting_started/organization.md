---
title: Organization of the library
sidebar: mydoc_sidebar
permalink: organization.html
folder: mydoc
---

# Organization

## Library
The library interface is organized in several subfolders:

* __algorithms__: contains reachability analysis methods, implementations of convex hull computation and quantifier
  elimination
  * the reachability analysis methods usually are implemented by an _analyzer_ which instanciates a _worker_ which
    invokes _handler_ for different subtasks.
* __datastructures__: collects most common datastructures such as points, halfspaces, but also hybrid automata and
  reachability analysis-related (e.g., the reachability tree)
* __parser__: contains an antlr4-based parser for the Flow* input language.
* __representations__: the core of the library, contains implementations of the most common state set representations
  and conversion methods between them
* __util__: holds utility functionality such as a linear optimization adapter, plotting facilities, sequence generators,
  or serialization-related functionality

## Further

Apart from folders dedicated to the library, further folders could be of interest

* __examples__: contains code examples, currently not all of them are working, but this is intended to be the
  case, one day. All source files in this folder, which are prefixed with `example_` are automatically converted into
  targets via `cmake`, i.e., adding a new file `example_ABC.cpp` and running cmake afterwards allows to build the new
  target `example_ABC` via e.g., `make example_ABC`.
* __test__: contains our unit tests but also stubs for benchmarking single operations