# Point of View projects
This repository contains several [Tulip](http://tulip.labri.fr) plugins that belong to the PhD thesis of Juan David Cruz-Gomez. Most of the plugins were developped between 2010 and 2012, while others like the PoVLayoutPlugin has ben updated since.

## Why Point of View?
The Point of View is anotion we try to develop to indicate that the set of features describing a person can be divided into several different subsets that can be compared with other individuals. 
The basic idea is that, besides the potential high dimensional problems that may arise, using the whole set of attributes for comparing users may result bad results, mainly because of the singularity of each actor.

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
## Compiling and installing the plugins
###Prerequisites
* A reasonable good C++ compiler (I use gcc 4.7.2)
* Install CMake
* QT4 with devel libraries
* Install the basic algorithms:
	* Clustering
	* Visualization

###Compiling the code
* Go to the base folder:
~~~~
juancrug@juandavid-office:~$ cd path-to-repo/software-suite/pov-plugins
~~~~
* Create a build folder and go into it:
~~~~
juancrug@juandavid-office:~/path-to-repo/software-suite/pov-plugins$ mkdir build
juancrug@juandavid-office:~/path-to-repo/software-suite/pov-plugins$ cd build
~~~~
* Configure with Cmake:
~~~~
juancrug@juandavid-office:~/path-to-repo/software-suite/pov-plugins/build$ cmake -DTULIP_DIR=/home/juancrug/tulip3 \
  -DCMAKE_MODULE_PATH=/home/juancrug/tulip3/share/tulip \
  -DATLAS_PREFIX=/home/juancrug \
  -DMATRIX_PREFIX=/home/juancrug \
  -DMDS_PREFIX=/home/juancrug \
  -DBASE_PREFIX=/home/juancrug \
  ..
~~~~
**Note:** replace the configuration paths with your own, custom paths.

* Build and install:
~~~~
juancrug@juandavid-office:~/path-to-repo/software-suite/base/matrix-lib/build$ make && make install
~~~~

At this stage the libraries should be installed in the Tulip install path. These are the libraries that should be installed:
~~~~
libDimacsLoaderPlugin-3.8.0.so
libLouvainCommunityDetection-3.8.0.so
libPoVCommunityDetection-3.8.0.so
libPoVCommunityLayoutPluginV2-3.8.0.so
libPoVCommunityColoringLayoutPlugin-3.8.0.so
libPoVViewPlugin-3.8.0.so
~~~~
##How to use this software
*To write...*

