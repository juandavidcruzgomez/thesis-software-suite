# Point of View projects
This repository contains several [Tulip](http://tulip.labri.fr) plugins that belong to the PhD thesis of Juan David Cruz-Gomez. Most of the plugins were developped between 2010 and 2012, while others like the PoVLayoutPlugin has ben updated since.

## Why Point of View?
The Point of View is anotion we try to develop to indicate that the set of features describing a person can be divided into several different subsets that can be compared with other individuals. 
The basic idea is that, besides the potential high dimensional problems that may arise, using the whole set of attributes for comparing users may result bad results, mainly because of the singularity of each actor.

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

