# Change Log

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).

## [Released] - 2025-01-21

### Added

- New implementation for HA analysis with urgent jumps (new method to calculate the set minus operation in an over-approximative manner)
- New method to calculate the reachable sets of parallelly composed automaton without building the actual parallel composition 
- Added exact generalized analysis for verification of neural networks with piece-wise linear activation functions
- Support for unbounded input sets while analyzing neural networks 

### Changed

- Extended thermostat controller benchmark with new properties
- Unbounded variant of ACAS Xu benchmark
- ACAS Xu variant with generalized piece-wise linear activation functions 

### Fixed

- Bug with mutex deadlock in H-Polytope optimizer context cleanup
