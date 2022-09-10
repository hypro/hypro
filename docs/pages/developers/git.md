---
title: Git
sidebar: mydoc_sidebar
permalink: git.html
folder: mydoc
---

We use git for version control, the development is organized in two repositories, one hosted at RWTH Aachen
University, the other one being hosted at github.com.

* the RWTH Aachen repository is used internally, if you want to contribute, please contact one of the main
  developers (e.g., Stefan Schupp)
* the github-repository is used publicly

## Branches

* the _master_ branch holds the last stable release
* the _alpha_ branch is used as a staging area for the next release
* the _documentation_ branch holds everything related to this online documentation
* the _master_ and _alpha_ branch are under continuous integration
* all development should start in branches based on the _alpha_ branch
* development branches should be named in a meaningful way, we often use prefixes, e.g., feature/, fix/, or
  maintenance/ to indicate the purpose
* ideally, development branches are merged to the _alpha_ branch after development of a certain feature and if all
  checks are successful, deleted