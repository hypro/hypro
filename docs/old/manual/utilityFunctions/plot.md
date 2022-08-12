Plotting {#plotting}
===========

The plotting engine defined in HyPro provides an easy-to-use interface to create gnuplot output files to visualize
computed sets. The singleton object \ref hypro::Plotter<Number> "Plotter" thereby collects objects which are to be
plotted and as soon as one of the plotting functions is called, writes an according output file. An object thereby is
referenced by a unique id, which is returned upon adding the respective object. An object is a set of 2-dimensional \ref
hypro::Point<Number> "points", which does not necessarily have to be minimal, as an implementation of Graham's scan will
reduce and order each collected set of vertices before plotting.

In its current state, the returned id allows for changing the color of the passed object.

A usage example of the plotting engine can be found in

- @ref example_plot.cpp
