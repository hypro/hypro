# Developer's guide {#developer}

## Code

* We use `clang-format` for our formatting, there are configuration files (named `.clang-format`) in the root folder as
  well as in the test-folder (those are formatted a bit differently).
* Please make sure to use `doxygen`-like documentation for your code, as we generate an API-documentation via `doxygen`.
* The following minor code-styles currently apply:
    * We use camel-case notation for composed names.
    * We prefix members of a class with "m", i.e., `mIntervals` is a member collecting intervals.
    * We separate implementation and definition for templates via `*.h` (definition) and `*.tpp` (implementation) files.

## Git

* The branch `master` should always contain a stable version.
* The branch `alpha` is intended as a staging area for the next release. Development in this branch should be stable or,
  if not, the issues should be fixed very soon.
* We categorize branch names into feature-branches (prefixed with `feature/`), bugfixing-branches (`fix/`) and
  maintenance-branches (`maintenance/`). The later are intended for things such as restructuring code, etc.
* The branches `master` and `alpha` are added to the continuous integration (CI) engine provided by github.

## Structure

* We separate source files and header files (subfolders `src` and `include`).
* Tests are in the test-subfolder.
* The folder `examples` contains code examples, currently not all of them are working, but this is intended to be the
  case, one day. All source files in this folder, which are prefixed with `example_` are automatically converted into
  targets via `cmake`, i.e., adding a new file `example_ABC.cpp` and running cmake afterwards allows to build the new
  target `example_ABC` via e.g., `make example_ABC`.

