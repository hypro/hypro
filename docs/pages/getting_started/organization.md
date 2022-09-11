---
title: Organization of the library
sidebar: mydoc_sidebar
permalink: organization.html
folder: mydoc
---

# Organization

The library interface is organized in several subfolders:

* algorithms: contains reachability analysis methods, implementations of convex hull computation and quantifier
  elimination
    * the reachability analysis methods usually are implemented by an _analyzer_ which instanciates a _worker_ which
      invokes _handler_ for different subtasks.
* datastructures: collects most common datastructures such as points, halfspaces, but also hybrid automata and
  reachability analysis-related (e.g., the reachability tree)
* parser: contains an antlr4-based parser for the Flow* input language.
* representations: the core of the library, contains implementations of the most common state set representations
  and conversion methods between them
* util: holds utility functionality such as a linear optimization adapter, plotting facilities, sequence generators,
  or serialization-related functionality