![](doc/hypro_Logo.png)

# HyPro - A C++ library for the representation of state sets for the reachability analysis of hybrid systems

![CMake](https://github.com/hypro/hypro/workflows/CMake/badge.svg) [![SonarCloud Status](https://sonarcloud.io/api/project_badges/measure?project=hypro&metric=alert_status)](https://sonarcloud.io/dashboard?id=hypro)
<!---master: [![Build Status](https://travis-ci.com/hypro/hypro.svg?branch=master)](https://travis-ci.com/hypro/hypro)
alpha:  [![Build Status](https://travis-ci.com/hypro/hypro.svg?branch=alpha)](https://travis-ci.com/hypro/hypro)-->

The C++ library HyPro, which is a result of the project [HyPro](https://ths.rwth-aachen.de/research/projects/hypro/) funded by the german research council, provides easy to use implementations of state set representations for the reachability analysis of hybrid systems via flowpipe-construction. It provides implementations of the most commonly used state set representations such as boxes, convex polytopes, support functions or zonotopes. All implementations conform to the same general interface, which allows the user to easily switch between representations (even during analysis).

Additionally, commonly used data-structures and algorithms required during the analysis are provided.
The tool features a parser for Flow*-syntax and implementations of basic reachability analysis methods based on flowpipe-construction.

On the [official project page](https://ths.rwth-aachen.de/research/projects/hypro/) you can find a collection of benchmarks as well.

## Installation

The latest stable version can be obtained from the *master*-branch. The *alpha*-branch holds a development version - please check the CI-status to see whether this version is stable. Apart from compiling HyPro, a [Docker image](https://hub.docker.com/r/hypro/hypro/) is available from DockerHub (both branches).

### <a name="dependencies"></a> Dependencies

To be able to compile HyPro, the following dependencies must be met:
* cmake
* a c++-compiler (g++/clang++)
* [CArL](https://github.com/smtrat/carl)  
* a Java runtime environment (e.g. openjdk-re)
* uuid-dev

### Compiling the library

After installing the [dependencies](#dependencies) obtaining the source code from the git-repository, HyPro can be configured via cmake and built afterwards. We recommend an out-of-source build:

```bash
$ mkdir build && cd build
$ cmake ..
$ make resources
$ make hypro
```
This minimal build will not compile tests. To compile tests as well and run them, you can use the target `allTests`, e.g.;

```bash
$ make allTests
$ make test
```

HyPro registers itself to cmake which means that any further cmake-project which depends on HyPro does not neccessarily require a system-installation of HyPro. Instead, it suffices to call `find_package(hypro)` from cmake to locate the local build.

## Documentation

Currently we provide an <a href="https://hypro.github.io/hypro/html/index.html" target="_blank">API documentation</a>
created with Doxygen as well as
a [Pdf manual](https://ths.rwth-aachen.de/wp-content/uploads/sites/4/research/HyPro/manual.pdf).

## Examples & Usage

HyPro comes with some examples shipped, which may give you a hint on how to use the library. All examples are listed in
the examples folder; all source files in this folder prefixed with `example_` are automatically assigned a corresponding
target, i.e., the file `example_box.cpp` can be compiled via the target `example_box`.

## Case Studies

The library comes with a selection of case studies which can be used for reproduction of experiments or as starting
points for interested users to use HyPro. In the following we shortly describe the content and how to run specific case
studies.

### Decomposition

The case study consists of three benchmarks which illustrate the benefits of subspace computations. We present results
for original approaches as well as for our earlier approach published at QAPL'17 and a more recent approach
(submitted, under review) which extends previous results by better synchronization.

The benchmarks are a leaking tank system, a system with two tanks and a thermostat model. All of these systems are
extended by controllers, which run periodically.

The results from the tables of our most recent publication (submitted, under review) can be reproduced by running the
script
`run_decomposition_benchmarks.sh` which is provided in the subfolder `test/case_studies`. The script takes two
parameters as an input, one being the path to the HyDRA-tool and the base path of the model files
(`examples/input/subspaceBenchmarks`). To build the HyDRA-tool, run

```shell
$ make hydra
```

Afterwards a complete call could look like (depending on your build folder)

```shell
$ sudo ./test/case_studies/run_decomposition_benchmarks.sh /home/me/hypro/build/bin/hydra 
examples/input/subspaceBenchmarks
```

(here we assume your username is "me" and HyPro is located in your home folder [from which your run the script] with a
build-folder named "build").

Additionally we have created a cmake-target to reproduce results from Table 3, which can be built by running

```shell
$ make cs_hypro_decomposition_benchmark
```

The resulting executable located in the `bin`-subfolder of your build folder runs the respective experiments in which
running times for different numbers of clocks and subspaces are compared when using a box-representation. 


