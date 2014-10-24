# README #

The base folder contains the initial elements on which the algorithms and the
plugins are built. These elements are:

* The [](basic matrix) manipulation library, and
* The [](MDS-SMACOF) library that's used by the layout algorithm

In each folder you will find additional information on how to build it.

## What do yo need? ##

These projects are built using CMake. Please compile the base folder in the 
following order:

1. basic-matrix (compile and install)
2. mds-smacof (compile and install)

Otherwise it will fail.

## Preliminaries ##
Copyright (C) 2014  Juan David Cruz-Gomez and Telecom-Bretagne
[juan.cruzgomez@telecom-bretagne.eu](juan.cruzgomez@telecom-bretagne.eu)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You can find a copy of the GPLv2 [http://www.gnu.org/licenses/gpl-2.0.html](here).
