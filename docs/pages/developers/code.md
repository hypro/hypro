---
title: Code
sidebar: mydoc_sidebar
permalink: code.html
folder: mydoc
---

* We use `clang-format` for our formatting, there are configuration files (named `.clang-format`) in the root folder as
  well as in the test-folder (those are formatted a bit differently).
* Please make sure to use `doxygen`-like documentation for your code, as we generate an API-documentation via `doxygen`.
* The following minor code-styles currently apply:
    * We use camel-case notation for composed names.
    * We prefix members of a class with "m", i.e., `mIntervals` is a member collecting intervals.
    * We separate implementation and definition for templates via `*.h` (definition) and `*.tpp` (implementation) files.