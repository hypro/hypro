![](doc/hypro_Logo.png)

# HyPro - A C++ library for the representation of state sets for the reachability analysis of hybrid systems

The C++ library HyPro, which is a result of the project [HyPro](https://ths.rwth-aachen.de/research/projects/hypro/) funded by the german research council, provides easy to use implementations of state set representations for the reachability analysis of hybrid systems via flowpipe-construction.
It provides implementations of the most commonly used state set representations such as boxes, convex polytopes, support functions or zonotopes.
All implementations conform to the same general interface, which allows the user to easily switch between representations (even during analysis).

Additionally, commonly used data-structures and algorithms required during the analysis are provided.
The tool features a parser for Flow*-syntax and implementations of basic reachability analysis methods based on flowpipe-construction.

On the [official project page](https://ths.rwth-aachen.de/research/projects/hypro/) you can find a collection of benchmarks as well.
A [Docker image](https://hub.docker.com/r/hypro/hypro/) is available from DockerHub.

## Documentation and build state

Currently we provide an <a href="https://hypro.github.io/hypro/html/index.html" target="_blank">API documentation</a> created with Doxygen as well as a [Pdf manual](https://ths.rwth-aachen.de/wp-content/uploads/sites/4/research/HyPro/manual.pdf).


Current TravisCi build state:

master: [![Build Status](https://travis-ci.com/hypro/hypro.svg?branch=master)](https://travis-ci.com/hypro/hypro)
alpha:  [![Build Status](https://travis-ci.com/hypro/hypro.svg?branch=alpha)](https://travis-ci.com/hypro/hypro)
coverage: [![SonarCloud Status](https://sonarcloud.io/api/project_badges/measure?project=hypro&metric=alert_status)](https://sonarcloud.io/dashboard?id=hypro)
