# Galois lattices extraction algorithm

This is the implementation of the Galois lattice extraction algorithm proposed by [Vicky Choi, 2006](http://arxiv.org/abs/cs/0602069).

One of the problems, or classic bottlenecks, is the concept lookup during the construction of the lattice, i.e., before adding a closed concept to the lattice, it is mandatory to check if that concept already exists. TO improve the search time I use a [trie](http://en.wikipedia.org/wiki/Trie).

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

###Compiling the code
* Go to the base folder:
~~~~
juancrug@juandavid-office:~$ cd path-to-repo/software-suite/base/galois-lattices
~~~~
* Create a build folder and go into it:
~~~~
juancrug@juandavid-office:~/path-to-repo/software-suite/base/galois-lattices/$ mkdir build
juancrug@juandavid-office:~/path-to-repo/software-suite/base/galois-lattices/$ cd build
~~~~
* Configure with Cmake:
~~~~
juancrug@juandavid-office:~/path-to-repo/software-suite/base/galois-lattices/build$ cmake -DPREFIX=/home/juancrug ..
~~~~
**Note:** replace the configuration paths with your own, custom paths.

* Build and install:
~~~~
juancrug@juandavid-office:~/path-to-repo/software-suite/base/galois-lattices/build$ make && make install
~~~~

At this stage the libraries should be installed in /PREFIX/lib while the public interfaces (.h files) should be in /PREFIX/
