---
title: Dependencies
sidebar: mydoc_sidebar
permalink: dependencies.html
folder: mydoc
---

## Basic dependencies

The very basic dependencies include the libraries.

- a C++ compiler, g++ (version >= 4.9) or clang++ (version >= 3.6),
- [gmpxx](https://gmplib.org/) the Gnu Multiprecision library C++ interface,
- [CMake](https://cmake.org/) (version >= 3.0.0), a build system,
- [boost](http://www.boost.org/) (version >= 1.71), a collection of C++ libaries,
- [CArL](https://github.com/smtrat/carl) (commit 3b0c79a68a), a C++ library for arithmetic,
- Java JRE (required for the Antlr parser) and
- uuid-dev (required for the Antlr parser)

Note that CArL installs dependencies such as Eigen3, gmp and boost locally in its build folder, so installing Java and
uuid-dev along with CArL should be sufficient to be able to build and use HyPro.
_We recommend installing most dependencies of CArL separately, see also the script below._
To compile HyPro, a suitable C++ compiler is required, either g++ (at least version 4.9) or clang++ (at least version
3.5).

## CArL

Use the following commands to install CArL in an simplified way:

Install most dependencies using a package manager (here: apt, Ubuntu):

```bash
sudo apt install libeigen3-dev uuid-dev libbliss-dev libboost-system1.71-dev libboost-program-options1.71-dev libboost-test1.
71-dev libboost-timer1.71-dev libboost-chrono1.71-dev libboost-serialization1.71-dev
```

Clone and build CArL

```bash
  git clone https://github.com/ths-rwth/carl && cd carl &&  git checkout 3b0c79a68a &&
  mkdir build && cd build &&
  cmake .. && make carl
  ```

## Additional (optional) dependencies

Currently HyPro provides an extended interface for linear solving, which allows to _additionally_ add __two__ of the
following linear optimizers as solving backends (see also [linear optimization](/hypro/optimization.html)):

- [glpk](https://www.gnu.org/software/glpk/)
- [SMT-RAT](https://github.com/smtrat/smtrat)
- [SoPlex](http://soplex.zib.de/)
- [Z3](https://github.com/Z3Prover/z3)
