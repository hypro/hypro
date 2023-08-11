# Change Log

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).

## [Unreleased] - 2023-05-22

### Added

- Enable multithreading for LTI and rectangular analysis
- Added heuristics to speed up redundant point computation: we identify points that are guaranteed to be vertices (e.g.,
  minima and maxima points per dimension, but also points in the projected convex hull). The performance increase is
  indicated by an accompanied benchmark

### Changed

- Switched to semantic versioning
- The parser has been moved to a separate target ```hypro-parser```
- H-Polytope intersection is more lightweight and does not perform full emptiness checks anymore
- Duplicate folders for the interface include directories have been removed
- Move illustrative examples to a 'tutorial' subfolder
- Remove storage of flowpipe segments from rectangular analyzer as this information is already contained in the
  reachability tree

### Fixed

- Several memory leaks related to circular dependencies of shared pointers have been fixed
- Bug in polytope dimension getter that had output zero in some cases
- Most examples have been fixed and should compile now
