---
title: Utility
sidebar: mydoc_sidebar
permalink: utility.html
folder: mydoc
use_math: false
---

## Utility

We provide several utility functions that may be useful for a tool developer. While some of them are large enough to
deserve a subpage (see menu), in the following, we outline some of the smaller but maybe useful features.

### Adaptions CaRL

A collection of wrappers around the API of CaRL that used to change. To overcome problems with different versions of the
API, HyPro comes with this collection of wrappers that we encourage users to use. Please contact us in case you find
missing functionality.

### Adaptions Eigen3

Holds operators on matrices and vectors (<=,<,==,>,>=), query functions such as finding duplicate rows and
transformations that allow adding or removing rows of matrices and vectors.

### Logging

Holds Macros to invoke a logger based on ```carl::logging```, e.g., ```TRACE(channel, text)``` to invoke a trace log
message on a given channel. The logger comes with a filter on channels that can be configured as well, such that each
channel can have a filter on a different log level.

### Matlab

First start for a wrapper for matlab, incomplete.

### Multithreading

Deprecated collection of headers that provide functionality for multithreading.

### Sampling

Header to create pseudo-random samples.

### Sequence Generation

Holds generators for sequences of arbitrary dimension and type, e.g, permutations, combinations of a fixed amount of
numbers in a certain range. Useful for instance for vertex enumeration for boxes.

### Serialization

All functionality around the library ```cereal``` to serialize objects from HyPro. Can/Should be extended on demand.

### SMT

Access to the more expressive SMT interface provided by solving backends such as ```SMT-RAT``` or ```z3```. Currently,
formulas have to be provided as ```carl::formula``` and the current solving backend is limited to ```z3```. Also comes
with utility functionality that should be extended on demand to allow simpler formula generation (e.g., how to express
that two sets are semantically equal).

### Statistics

Holds macros to enable statistics about the execution of functions in HyPro. These macros allow to measure time as well
as count instances of events. Needs to be enabled during compilation via the cmake flag ```-DHYPRO_STATISTICS=ON```.

### Tuple Expansion and Type Handling

Helpers to allow compile-time polymorphism over lists of types and alike.
