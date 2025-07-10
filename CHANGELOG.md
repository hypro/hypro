# Change Log

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).

## [Released] - 2025-07-11

### Added

- Implementation of the counterexample-guided abstraction refinement (CEGAR) approach for neural network verification
- Implementation of several heuristics for CEGAR
- Extending the Z3 interface with necessary feasibility check template formulas
- 

### Changed
- Enabled exact arithmetic (via the MPBoost library) for neural network verification

### Fixed
- Starset copy constructor did not check whether the RHS argument has an optimizer to copy
- 