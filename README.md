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
* iputils-ping

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

HyPro registers itself to cmake which means that any further cmake-project which depends on HyPro does not necessarily require a system-installation of HyPro. Instead, it suffices to call `find_package(hypro)` from cmake to locate the local build.

## Documentation

Currently we provide an <a href="https://hypro.github.io/hypro/html/index.html" target="_blank">API documentation</a>
created with Doxygen as well as
a [Pdf manual](https://ths.rwth-aachen.de/wp-content/uploads/sites/4/research/HyPro/manual.pdf).

## Examples & Usage

HyPro comes with some examples shipped, which may give you a hint on how to use the library. All examples are listed in
the examples folder; all source files in this folder prefixed with `example_` are automatically assigned a corresponding
target, i.e., the file `example_box.cpp` can be compiled via the target `example_box`.

### Running HyPro in Docker 

Hypro uses a pre-build docker container which contains some of the dependencies (for example the CArL library) in order to make the docker build step faster. We can build this with the docker file  `Dockerfile.carl`. This docker image is already compiled and pushed to <a href="https://hub.docker.com/repository/docker/hyprodockeruser/carl/general" target="_blank">docker hub</a>. We use this file also for speeding up the gitlab pipeline.

In order to build and run HyPro inside a docker container you need to run the following commands:

```bash
$ docker build -t hypro .
$ docker exec -it hashOfImage bash
```

The first command will build the docker image. With the second command we can step into the docker container and we can run hypro inside the docker container. In the second command you need the hash of the newly built docker image. You can get this by listing out all the images which are available on your system and then looking for one which is called hypro.



## Case Studies

The library comes with a selection of case studies which can be used for reproduction of experiments or as starting
points for interested users to use HyPro. In the following we shortly describe the content and how to run specific case
studies.

### Neural Network Verification

HyPro includes four benchmarks that interested users can use to test our reachability analysis algorithm for neural networks with piece-wise linear activation functions. The four benchmarks are: ACAS Xu, drone hovering, thermostat controller, and sonar classifier. In the following section, we list some example commands for running verification on each of these benchmarks. We provide the neural networks in .nnet format and the safety properties in a custom text format. To execute the verification with the corresponding parameters, we offer a convenient script called `nnBenchmarkVerification.sh`, which is located in the root directory of HyPro. To run the script, we assume that the user's current directory is the `build` folder.

#### ACAS Xu

The famous ACAS Xu benchmark consists of 45 neural networks, each following the naming convention ACASXU_experimental_v2a_x_y.nnet, where $1 \leq x \leq 5$ and $1 \leq y \leq 9$. All of the networks have 5 inputs, 5 outputs, 6 hidden layers, each hidden layer with 50 neurons and ReLU activation. The benchmark comes with 10 safety properties, which are described in section VI of the Appendix of [this](https://arxiv.org/pdf/1702.01135.pdf) paper.

To verify a specific property-network combination, you should first compile the corresponding binary file. Then, assuming that the current directory is the `build` folder, running the over-approximate method on network ACASXU_experimental_v2a_2_4 with safety property 4 can be done as follows:

```shell
$ make example_ACASbenchmark_verification
$ ../nnBenchmarkVerification.sh acasxu overapprox ACASXU_experimental_v2a_2_4.nnet poly_prop4_input.in poly_prop4_safe.in
```

#### Drone hovering

First of all, we would like to express our deepest gratitude to Dario Guidotti, Stefano Demarchi, and Armando Tacchella for generously sharing their drone hovering benchmark with us. This benchmark comprises eight neural networks. The first four consist of two hidden layers, and the other four networks consist of three hidden layers, each followed by a ReLU activation function. For each network, two safety properties are provided. 

As an example, to compile the binary and verify the network AC7.nnet using the second safety property, please follow these commands:

```shell
$ make example_drones_verification
$ ../nnBenchmarkVerification.sh drones exact AC7.nnet prop_AC7_02.in safe_AC7_02.in
```

#### Thermostat controller

The benchmark discussed in [this](https://ths.rwth-aachen.de/wp-content/uploads/sites/4/master_thesis_jiang.pdf) Master’s thesis includes a neural network controller that regulates room temperature within the range of 17°C to 23°C using a thermostat. It accomplishes this by activating (mode on) and deactivating (mode off) the heater based on the sensed temperature. The neural network representing the thermostat's controller is a feedforward neural network with three layers. The input comprises two neurons that represent the temperature and the current mode (on or off). Additionally, there are two hidden layers, each with ten neurons. Finally, using the unit step activation function, the output layer predicts whether the heater should turn on or off, generating the corresponding control input.

To compile and test this benchmark, please follow these commands:

```shell
$ make example_thermostat_verification
$ ../nnBenchmarkVerification.sh thermostat exact fc_thermostat.nnet poly_thermostat.in
```

#### Sonar classifier

Using this benchmark, we assess the robustness of a neural network designed for binary classification of a sonar dataset. This dataset characterizes sonar chirp returns reflecting off various objects and comprises 60 input variables representing the strength of the returned beams at different angles. The neural network under examination should demonstrate robust binary classification, distinguishing between rocks and metal cylinders. This neural network consists of two layers, with the first layer utilizing a ReLU activation function and the second layer employing a sigmoid activation function, which we switch to the hard sigmoid. Our goal is to verify the local robustness of this neural network.

The local-robustness properties were generated using $\delta = 0.00001$. However, you can modify this value by changing the delta value in the `examples/nn_benchmarks/properties/sonar/convert_sonar.py` script and then re-run the script to regenerate the input properties. For instance, to evaluate the robustness of input 39, where the ground truth label is "rock" (R), you can follow these steps:

```shell
$ make example_robustness
$ ../nnBenchmarkVerification.sh sonar overapprox sonar_detector.nnet sonar_39_R.in
```

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


