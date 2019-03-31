# Community detection algorithms
In this repositiory you will find the version 1, 2 and 3 of the community detection algorithms plus the Louvain's algorithm implemented for Tulip.

Other algorithms included in this repository are for data clustering (I don't think they are really interesting)

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
