---
title: Plotting
sidebar: mydoc_sidebar
permalink: plotting.html
folder: mydoc
use_math: true
---

## Plotter

The plotter is implemented as a carl::singleton, a reference to the instance can be obtained with ```getInstance()```.
Facts about the plotter:

* Objects can be added as sequences of points $p\in\mathbb{R}^2$.
* The sequence of points describing an object does neither have to be redundancy-free nor in order.
* Additionally, color and further settings can be added
* Writing is done by using the ```plot2d(TYPE)``` function, which creates a _gnuplot_ file to create a plot of type
  ```TYPE```.
  If _gnuplot_ is present,
  passing ```true``` as a second parameter to ```plot2d()``` causes HyPro to directly call gnuplot and create the
  image file.

## Further Plotting

* There exist plotters for hybrid automata and reachability trees utilizing _graphviz_.