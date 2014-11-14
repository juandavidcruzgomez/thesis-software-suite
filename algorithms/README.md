# Community detection algorithms
In this repositiory you will find the version 1, 2 and 3 of the community detection algorithms plus the Louvain's algorithm implemented for Tulip.

Other algorithms included in this repository are for data clustering (I don't think they are really interesting)

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
* Install the base libraries: SMACOF and Matrix. Find the code and the instructions [here](https://bitbucket.org/juandavidcruz_tb/software-suite/src/c2ca1bc7cbe5df27c0f030cbbac02a9937ae158d/base/?at=master).

###Compiling the code
* Go to the base folder:
~~~~
juancrug@juandavid-office:~$ cd path-to-repo/software-suite/algorithms
~~~~
* Create a build folder and go into it:
~~~~
juancrug@juandavid-office:~/path-to-repo/software-suite/algorithms/$ mkdir build
juancrug@juandavid-office:~/path-to-repo/software-suite/algorithms/$ cd build
~~~~
* Configure with Cmake:
~~~~
juancrug@juandavid-office:~/path-to-repo/software-suite/algorithms/build$ cmake -DTULIP_DIR=/home/juancrug/tulip3 \
  -DCMAKE_MODULE_PATH=/home/juancrug/tulip3/share/tulip \
  -DATLAS_PREFIX=/home/juancrug \
  -DPREFIX=/home/juancrug \
  ..
~~~~
**Note:** replace the configuration paths with your own, custom paths.

* Build and install:
~~~~
juancrug@juandavid-office:~/path-to-repo/software-suite/algorithms/build$ make && make install
~~~~

At this stage the libraries should be installed in /PREFIX/lib while the public interfaces (.h files) should be in /PREFIX/

Thus, these are the libraries used by other algorithms like the plugins and the community detection algorithms platform.