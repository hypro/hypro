# Change Log

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).

## [Unreleased] - 2023-04-03

### Added

- Enable multithreading for LTI and rectangular analysis

### Changed

- Switched to semantic versioning
- The parser has been moved to a separate target ```hypro-parser```

### Fixed

- Several memory leaks related to circular dependencies of shared pointers have been fixed
