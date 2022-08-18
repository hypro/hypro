---
title: Boxes
sidebar: mydoc_sidebar
permalink: boxes.html
folder: mydoc
use_math: true
---

| Property |  Value  |
|----------|:-------:|
| Accuracy |    +    |
| Speed |   +++   |
| Maturity | +++ |

## General Idea

A d-dimensional box as the Cartesian product of d real-valued intervals is represented by an ordered sequence of d
intervals in HyPro. Operations are implemented using interval arithmetic, thus avoiding costly conversions.

## Implementation Details

## Hints & Tricks

In flowpipe construction for linear hybrid systems, the chosen time step size usually has a monotonous effect on
precision, i.e., decreasing the time step size usually increases precision. For boxes, due to the introduced
over-approximation during most operations, this statement does not necessarily hold.

{% include links.html %}
