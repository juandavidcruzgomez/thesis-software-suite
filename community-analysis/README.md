# Community analysis platform
This repository contains an initial version of a platform that can be used to test different community detection algorithms.

The basic idea is to instantiate different community detection algorithms and compare their results.

The implemented algorithms are:

* Point of view community detection
* Galois clustering
* Louvain's algorithm
* Other data mining algorithms:
    * K-means
    * PageRank based k-means
    * SOM

The idea here is to add experiments that derive from the ClusteringBase class.

## License
The MIT License (MIT)

Copyright (c) 2014 Juan David Cruz Gómez and Telecom - Bretagne juan.cruzgomez@telecom-bretagne.eu

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

## Compiling and installing the algorithms
###Requisites
* Install CMake
* Install Tulip 3.8 with development libraries
* Install the base and algorith libraries

###Compiling the code
* Go to the base folder:
~~~~
juancrug@juandavid-office:~$ cd path-to-repo/software-suite/community-analysis
~~~~
* Create a build folder and go into it:
~~~~
juancrug@juandavid-office:~/path-to-repo/software-suite/community-analysis/$ mkdir build
juancrug@juandavid-office:~/path-to-repo/software-suite/community-analysis/$ cd build
~~~~
* Configure with Cmake:
~~~~
juancrug@juandavid-office:~/path-to-repo/software-suite/community-analysis/build$ cmake -DTULIP_DIR=/home/juancrug/tulip3 \
  -DCMAKE_MODULE_PATH=/home/juancrug/tulip3/share/tulip \
  -DATLAS_PREFIX=/home/juancrug \
  -DBASE_PREFIX=/home/juancrug \
  -DPREFIX=/home/juancrug \
  ..
~~~~
**Note:** replace the configuration paths with your own, custom paths.

* Build and install:
~~~~
juancrug@juandavid-office:~/path-to-repo/software-suite/community-analysis/build$ make
~~~~

At this stage the libraries should be installed in /PREFIX/lib while the public interfaces (.h files) should be in /PREFIX/

## Using it
Take a look to the main.cpp file.