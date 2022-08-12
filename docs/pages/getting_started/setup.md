---
title: Setup
sidebar: mydoc_sidebar
permalink: mydoc_setup.html
folder: mydoc
---

# Installation {#installation}

After having installed all necessary [dependencies](@ref dependencies), the library can be compiled out of source and
installed using _cmake_. In the following we assume a build folder named 'build' will be used. The following terminal
commands will allow for a build with the default settings enabled (for more options see [options](@ref options)):

~~~.bash
cmake ..
make resources
make
~~~

To install the library to your system, use

~~~.bash
make install
~~~

Options {#options}
------------------
In its current state, the main features of HyPro can be configured via _cmake_ or its gui _ccmake_, which can be invoked
by (from the build folder):

~~~.bash
ccmake ..
~~~

The currently available options are:

* HYPRO_LOGGING - Allows to completely enable/disable all logging macros (default: ON).
* HYPRO_USE_COTIRE - Enables/disables the usage of [cotire](https://github.com/sakra/cotire), which allows for faster
  builds (default: OFF).
* HYPRO_USE_OPENMP - Enables/disables the usage of OpenMP in Eigen3 (default: OFF).
* HYPRO_USE_PPL - Enables/disables the PPL-wrapper class. Note that PPL has to be installed to use this feature (
  default: OFF).
* HYPRO_USE_SMTRAT - Enables/disables the usage of SMT-RAT as a secondary linear optimization backend. Note that SMT-RAT
  has to be installed to use this feature (default: OFF).
* HYPRO_USE_SOPLEX - Enables/disables the usage of SoPlex as a secondary linear optimization backend. Note that SoPlex
  has to be installed to use this feature (default: OFF).
* HYPRO_USE_Z3 - Enables/disables the usage of Z3 as a secondary linear optimization backend. Note that Z3 has to be
  installed to use this feature (default: OFF).
* STATICLIB_SWITCH - Allows to compile a static-linked version of HyPro (default: OFF).
* CREATE_DOC - Allows to locally build this documentation (default: OFF).

Examples
--------

Each provided example file comes with its own target, which can be build by using the examples name, i.e. use

~~~.bash
make example_zonotope
~~~

to build an example showing the basic usage of the zonotope representation. Each built example binary can be found in
the folder build/bin/.


{% include links.html %}
