# Base algorithms

The base folder contains the initial elements on which the algorithms and the
plugins are built. These elements are:

* The [basic matrix](https://bitbucket.org/juandavidcruz_tb/software-suite/src/c2ca1bc7cbe5df27c0f030cbbac02a9937ae158d/base/matrix-lib/?at=master) manipulation library, 
* The [MDS-SMACOF](https://bitbucket.org/juandavidcruz_tb/software-suite/src/c2ca1bc7cbe5df27c0f030cbbac02a9937ae158d/base/mds-smacof/?at=master) library that's used by the layout algorithm
* The [Galois-lattice](#) implementation. This library is used by the community detection algorithm V3.

In each folder you will find additional information on how to build it.

## License
 Copyright (c) 2014 Juan David Cruz Gómez and Telecom - Bretagne

 juan.cruzgomez@telecom-bretagne.eu 
 juandavidcruz@gmail.com

 Licensed under the EUPL, Version 1.2 or – as soon theywill be approved 
 by the European Commission - subsequent versions of the 
 EUPL (the "Licence");

 You may not use this work except in compliance with the Licence.
 You may obtain a copy of the Licence at:

    https://joinup.ec.europa.eu/software/page/eupl5
  
 Unless required by applicable law or agreed to inwriting, software 
 distributed under the Licence isdistributed on an *"AS IS"* basis,
 *WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND*, either express or implied.
 See the Licence for the specific language governing permissions and limitations 
 under the Licence.
-------------------------------------------------------

## What do yo need? ##

These projects are built using CMake. Please compile the base folder in the 
following order:

**1.** basic-matrix (compile and install)
**2.** mds-smacof (compile and install)
**2.** galois-lattices (compile and install)

**Otherwise it will fail.**

