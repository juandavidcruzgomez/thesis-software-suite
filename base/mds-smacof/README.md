# Multi-Dimensional Scaling - SMACOF algorithm

This is a really basic library to do MultiDimensional Scaling with SMACOF. This is very simple (and maybe buggy, IDK) but can be useful, and indeed I use it for other projects I'm working on. Since I've wrote this for my own projects, other functions may be added in the future, sorry for the inconvenience.

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
## Compiling and installing the algorithms
###Requisites
* A reasonable good C++ compiler (I use gcc 4.7.2)
* Install CMake
* This project uses the Matrix library you can find [here](https://bitbucket.org/juandavidcruz/matrix-basic-library/).

###Compiling the code
* Go to the base folder:
~~~~
juancrug@juandavid-office:~$ cd path-to-repo/software-suite/base/mds-smacof
~~~~
* Create a build folder and go into it:
~~~~
juancrug@juandavid-office:~/path-to-repo/software-suite/base/mds-smacof/$ mkdir build
juancrug@juandavid-office:~/path-to-repo/software-suite/base/mds-smacof/$ cd build
~~~~
* Configure with Cmake:
~~~~
juancrug@juandavid-office:~/path-to-repo/software-suite/base/mds-smacof/build$ cmake -DMATRIX_PREFIX=/home/juancrug \
  -DPREFIX=/home/juancrug \
  ..
~~~~
**Note:** replace the configuration paths with your own, custom paths.

* Build and install:
~~~~
juancrug@juandavid-office:~/path-to-repo/software-suite/base/mds-smacof/build$ make && make install
~~~~

At this stage the libraries should be installed in /PREFIX/lib while the public interfaces (.h files) should be in /PREFIX/

## What next?

* I don't know, it depends on the needs...
