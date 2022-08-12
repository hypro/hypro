Features {#features}
========

Originally indended to be a library for state set representations usable during flowpipe-construction-based reachability
analysis of linear hybrid systems, HyPro has been extended to contain various additional features which aid the
development of tailored reachability analysis methods for hybrid systems.

In its current state HyPro provides

* A collection of state set representations, among them implementations of boxes, convex polytopes in different
  representations, a wrapper to the Parma Polyhedra Library (PPL), support functions, and zonotopes which all comply
  with the interface GeometricObject. Furthermore, implementations of ellipsoids, orthogonal polyhedra and Taylor models
  are provided.
* Conversion methods between the state set representations.
* Data structures required for the implementation of said state set representations such as half-spaces, points, and
  functions on them.
* Data structures required for the implementation of a state-of-the-art reachability analysis method based on flowpipe
  construction such as a representation for hybrid automata, a parser for Flow*- and CIF-syntax, queues, an
  implementation of a search tree, and many more. Furthermore, a basic reachability analysis method is provided (
  Reacher.h) and a framework for the modular creation of reachability analysis workers is provided.
* Basic utility functionality such as a framework for linear optimization with different backends (and their
  combination), logging facilities (based on CArL), and a simple plotter to create gnuplot-output.
