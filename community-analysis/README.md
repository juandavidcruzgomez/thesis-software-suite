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
Usage:

~~~~
./analysistest 
This program implements a platform for comparing community
detection algorithms.

The files required for this program to run are: a .tlp file
containing the graph, a .txt containing the composition patterns
or a .txt containing a partition from the composition patterns
and a .txt containing the ground truth partition.

REQUIRED ARGUMENTS:
-g	The file containing the graph
-c	The file contaning the raw composition patterns
-p	The file containing the composition partition aff matrix
-n	The name of the experiment

OPTIONAL ARGUMENTS:
-w	The directory to store all the files produced during the experiment
-t	The file containing the affiliation matrix with the ground truth
	partition. Note that if this file is set, an ARI test will be performed
	that if the output file is not provided, the partition will
-e	A flag indicating whether or not the Galois lattice have to be
	created using the raw patterns insted of the composition partition.
	Note that the raw composition patterns have had to be set via the -c
	argument.

OTHER OPTIONS:
-h	Prints this information.

~~~~
Within the folder build execute for example:
~~~~
juancrug@juandavid-office:~/path-to-repo/software-suite/community-analysis/build$./analysistest -g ../tests/personalNetwork.tlp -c ../tests/fb_composition.txt -p ../tests/fb_composition.txt -w ../tests/ -n example
~~~~

The output, in this case, is saved in the directory '../tests', which is defined by the flag '-w'. The output produce two files are:

~~~~
stats_example.txt: the statistics of the algorithms
clustered_graph_example.tlp: the Tulip file containing all the partitions produced by the algorithms
~~~~

Note that 'example' is the name given to the experiment through the -n flag.
