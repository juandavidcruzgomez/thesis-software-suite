# Base algorithms

The base folder contains the initial elements on which the algorithms and the
plugins are built. These elements are:

* The [basic matrix](https://bitbucket.org/juandavidcruz_tb/software-suite/src/c2ca1bc7cbe5df27c0f030cbbac02a9937ae158d/base/matrix-lib/?at=master) manipulation library, 
* The [MDS-SMACOF](https://bitbucket.org/juandavidcruz_tb/software-suite/src/c2ca1bc7cbe5df27c0f030cbbac02a9937ae158d/base/mds-smacof/?at=master) library that's used by the layout algorithm
* The [Galois-lattice](#) implementation. This library is used by the community detection algorithm V3.

In each folder you will find additional information on how to build it.

## License
The MIT License (MIT)

Copyright (c) 2014 Juan David Cruz Gómez and Telecom - Bretagne
juan.cruzgomez@telecom-bretagne.eu

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
-------------------------------------------------------

## What do yo need? ##

These projects are built using CMake. Please compile the base folder in the 
following order:

**1.** basic-matrix (compile and install)
**2.** mds-smacof (compile and install)
**2.** galois-lattices (compile and install)

**Otherwise it will fail.**

