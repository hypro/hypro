Dependencies {#dependencies}
============

The very basic dependencies include the libraries.

- a C++ compiler, g++ (version >= 4.9) or clang++ (version >= 3.6),
- [gmpxx](https://gmplib.org/) the Gnu Multiprecision library C++ interface,
- [CMake](https://cmake.org/) (version >= 3.0.0), a build system,
- [boost](http://www.boost.org/) (version 1.55--1.70), a collection of C++ libaries,
- [CArL](https://github.com/smtrat/carl) (version == 19.06), a C++ library for arithmetic,
- Java JRE (required for the Antlr parser) and
- uuid-dev (required for the Antlr parser)

Note that CArL installs dependencies such as Eigen3, gmp and boost locally in its build folder, so installing Java and
uuid-dev along with CArL should be sufficient to be able to build and use HyPro.
To compile HyPro, a suitable C++ compiler is required, either g++ (at least version 4.9) or clang++ (at least version
3.5). Note that in the current version HyPro requires to use CArL 19.06 as otherwise the support for OSX is not provided
by CArL. As a consequence, the version of boost has to be less than 1.71.

Configurations known to work
----------------------------

Here we list configurations which we know work

OS | HyPro | CArL | Others
---------------------
Linux | 20.01 | 20.01 | no requirements




Additional (optional) dependencies
----------------------------------

Currently HyPro provides an extended interface for linear solving, which allows to _additionally_ add __one__ of the
following linear optimizers:

- [SMT-RAT](https://github.com/smtrat/smtrat)
- [SoPlex](http://soplex.zib.de/)
- [Z3](https://github.com/Z3Prover/z3)

Using one of these solvers can be enabled by the respective cmake flag , i.e. HYPRO_USE_SMTRAT to enable SMT-RAT
support. When using one of the previously mentioned solvers, the usage of rational types such as mpq_class is improved,
as linear optimization now can be performed providing _exact_ results.
