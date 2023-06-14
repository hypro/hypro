Dependencies {#dependencies}
============

The very basic dependencies include the following libraries:

- a C++ compiler, g++ (version >= 4.9) or clang++ (version >= 3.6),
- [gmpxx](https://gmplib.org/) the Gnu Multiprecision library C++ interface,
- [CMake](https://cmake.org/) (version >= 3.0.0), a build system,
- [boost](http://www.boost.org/) (version >= 1.55), a collection of C++ libaries,
- [CArL](https://github.com/smtrat/carl) (version 22.04), a C++ library for arithmetic,
- Java JRE (required for the Antlr parser) and
- uuid-dev (required for the Antlr parser)

To install those dependencies on, e.g., Ubuntu, use the following lines of code:

Build tools (```cmake-curses-gui``` is not strictly required but nice to have)

```bash
sudo apt-get install build-essential cmake cmake-curses-gui
```

Libraries (some are required/implicitly installed by CArL as well):

```bash
sudo apt-get install libgmpxx4ldbl uuid-dev libeigen3-dev libboost-system1.71-dev libboost-program-options1.71-dev libboost-test1.71-dev libboost-timer1.71-dev libboost-chrono1.71-dev libboost-serialization1.71-dev libbliss-dev
```

CArL:

```bash
  git clone https://github.com/ths-rwth/carl && cd carl &&  git checkout 3b0c79a68a &&
  mkdir build && cd build &&
  cmake .. && make carl
  ```

Note that CArL installs dependencies such as Eigen3, gmp and boost locally in its build folder, so installing Java and
uuid-dev along with CArL should be sufficient to be able to build and use HyPro.
To compile HyPro, a suitable C++ compiler is required, either g++ (at least version 4.9) or clang++ (at least version
3.5).

Additional (optional) dependencies
----------------------------------

Currently HyPro provides an extended interface for linear solving, which allows to _additionally_ add __one__ of the
following linear optimizers:

- [SMT-RAT](https://github.com/smtrat/smtrat)
- [SoPlex](http://soplex.zib.de/)
- [Z3](https://github.com/Z3Prover/z3)

Using one of these solvers can be enabled by the respective cmake flag , i.e. HYPRO_USE_SMTRAT to enable SMT-RAT
support. When using one of the previously mentioned solvers, the usage of rational
types such as mpq_class is improved, as linear optimization now can be performed providing _exact_ results.
