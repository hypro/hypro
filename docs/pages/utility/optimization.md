---
title: Linear Optimization
sidebar: mydoc_sidebar
permalink: optimization.html
folder: mydoc
use_math: true
---

## Linear Optimization

In HyPro, we provide a wrapper class (```Optimizer```) for linear optimization backends. Currently, the
tools/libraries [glpk](), [soplex](), [SMT-RAT](), and [z3]() are supported. We allow chaining backends, i.e., using
an inexact approach as a presolver and an exact backend as the main solver. The primary (presolver) and secondary
(main solver) solver backend can be set via ```cmake``` options. If no secondary backend is given, the primary
solver acts as the main solver.

## Implementation details

Due to the varying APIs of the solver backends, we observe the following

* all three backends [soplex](), [SMT-RAT](), and [z3]() support exact solving, i.e., using rational arithmetic.
  This is usually slower. [glpk]() also has a mode which allows to use rational numbers internally, but the
  interface still takes floating point numbers as input.
* Conversion to different number-formats may slow down solving. For instance, the rational interface of [z3]()
  requires string-conversions, which is a major bottleneck.
* We recommend using either [soplex]() or [SMT-RAT]() as secondary backends.
* Exact arithmetic is mainly advised when using convex polyhedra as a state set representation