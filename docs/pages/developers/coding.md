---
title: Coding Guidelines
sidebar: mydoc_sidebar
permalink: coding.html
folder: mydoc
---

# Coding Guidelines

Some high-level coding guidelines that we hope ensure proper code quality for the whole project.

* Make use of a code formatter, we provide a configuration for `clang-format`. Pay attention to its feedback messages.
* Use lowerCamelCase to name functions and variables
* Make use of meaningful function & variable names
    * Use the prefix `is` or `has` for functions returning a Boolean, e.g., `isEmpty()`.
    * Use the prefix `m` for member variables, e.g., `mIntervals` for the member collecting the intervals of a class.
    * Use the prefix `_` for private member functions, e.g., `_setInternalState()`.
    * Avoid putting types into variable names, e.g., __do not use__ `variableVector` but maybe instead `variables`.
    * Use `get` and `set` as prefixes for getters and setters.
* Collect complicated conditional statements in Boolean variables whose naming communicates the intention of the
  statement.
* Try to avoid lengthy functions. Some hints:
    * Split where it seems logical
    * Try to keep the indentation level low (e.g., less than three)
    * Pay attention to blocks in conditional statements - can they be extracted into a function?
* Avoid interface changes. If you need to
    * Keep the old interface, mark it deprecated with information on when this will be removed.
    * Add the new interface in parallel to the old one.
* Document your code, ideally, provide a doxygen-style documentation for each function, class, and class member.
  Also consider documenting blocks of increased complexity.