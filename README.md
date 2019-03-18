[![DOI](https://zenodo.org/badge/21803/juandavidcruz/thesis-software-suite.svg)](https://zenodo.org/badge/latestdoi/21803/juandavidcruz/thesis-software-suite)

# Juan David Cruz-Gómez PhD Thesis software suite

This repository contains several software projects developed during my PhD thesis at Telecom - Bretagne. Since the software and algorithms were mostly written for papers and thus in a rush, the code may not be the best and cleanest code you may ever seen.

However, in an effort to write clean code, I try to document all the code and to automate the building process. To do this I use CMake (I hope you know the basics of CMake).

## Table of contents

* [Notice and license](https://bitbucket.org/juandavidcruz_tb/software-suite#markdown-header-notice-and-license)
* [Installing CMake](https://bitbucket.org/juandavidcruz_tb/software-suite#markdown-header-installing-cmake)
* [Installing and configuring Tulip](https://bitbucket.org/juandavidcruz_tb/software-suite#markdown-header-installing-and-configuring-tulip)
* [Installing and configuring ATLAS](https://bitbucket.org/juandavidcruz_tb/software-suite#markdown-header-installing-and-configuring-atlas)
* [Projects](https://bitbucket.org/juandavidcruz_tb/software-suite#markdown-header-projects)
    * [Base algorithms](https://bitbucket.org/juandavidcruz_tb/software-suite#markdown-header-base-algorithms)
        * [Matrix library](https://bitbucket.org/juandavidcruz_tb/software-suite#markdown-header-matrix-library)
        * [Multidimensional scaling](https://bitbucket.org/juandavidcruz_tb/software-suite#markdown-header-multidimensional-scaling)
        * [Trie structure](https://bitbucket.org/juandavidcruz_tb/software-suite#markdown-header-trie-structure)
    * [Basic community detection and visualization algorithms](https://bitbucket.org/juandavidcruz_tb/software-suite#markdown-header-basic-community-detection-and-visualization-algorithms)
        * [Community detection V1: weight modification](https://bitbucket.org/juandavidcruz_tb/software-suite#markdown-header-community-detection-v1-weight-modification)
        * [Community detection V2: contingency matrix manupulation](https://bitbucket.org/juandavidcruz_tb/software-suite#markdown-header-community-detection-v2-contingency-matrix-manupulation)
        * [Community detection V3: Galois lattice-based community detection](https://bitbucket.org/juandavidcruz_tb/software-suite#markdown-header-community-detection-v3-galois-lattice-based-community-detection)
        * [Note on the entropy version](https://bitbucket.org/juandavidcruz_tb/software-suite#markdown-header-note-on-the-entropy-version)
        * [Boundary communities visualization algorithm](https://bitbucket.org/juandavidcruz_tb/software-suite#markdown-header-boundary-communities-visualization-algorithm)
    * [Tulip plugins](https://bitbucket.org/juandavidcruz_tb/software-suite#markdown-header-tulip-plugins)
        * [Importers](https://bitbucket.org/juandavidcruz_tb/software-suite#markdown-header-importers)
        * [Community detection](https://bitbucket.org/juandavidcruz_tb/software-suite#markdown-header-community-detection)
        * [Visualization](https://bitbucket.org/juandavidcruz_tb/software-suite#markdown-header-visualization)
        * [Point of view manipulation](https://bitbucket.org/juandavidcruz_tb/software-suite#markdown-header-point-of-view-manipulation)
        
## Notice and license
-------------------------
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
-------------------------


## Installing CMake


## Installing and configuring Tulip
Some of the sub-projects are linked against the [Tulip library](http://tulip.labri.fr/TulipDrupal/). 

Specifically, the version of Tulip that has been used is the **3.8** and is the only one I have made tests on.

You can find the source of the 3.8 version of Tulip [here](http://sourceforge.net/projects/auber/files/tulip/tulip-3.8.0/).

Now, if you just don't want to compile and install, you can download the packages for your distribution. In Debian (I guess in Ubuntu also) you can install Tulip 3.7 using:

~~~~
juancrug@juandavid-office:~$ sudo apt-get install tulip libtulip-dev
~~~~

Note that you need to install the development package to compile the software in this suite.

## Installing and configuring ATLAS
ATLAS stands for _Automatically Tuned Linear Algebra Software_ so, it's a linear algebra package that implements several vector/matrix operations ready to use.

**Important note:**  save the installation prefix for ATLAS. I usually chose to install these kind of libraries in ~/ 

Follow the instructions [here](http://math-atlas.sourceforge.net/atlas_install/atlas_install.html) to configure ans install ATLAS. 

*Why do you need to configure and build ATLAS?* well, this library is used by several algorithms and it depends on the system being used, e.g., 32 bits with 512 Kb L2 cache is different than 64 bits processors with 1024 Kb L2 cache and 8 cores.

Sorry, this is the way that it is.

## Projects
This is the set of projects I have made these years at Telecom - Bretagne.

### Base algorithms
Basic algorithms and libraries I have created for my other algorithms. Since I do not like the disorder and I do not want to rewrite all over again the same code, I decided to write libraries and use them as tools whenever I needed.

That's a lot work for me I think, but it's a lot cleaner and centralized. Even more, I think that the excuse _I'm a computer scientist, so I write messy code_ is just lame.

#### Matrix library
This library encapsulates the behavior of a matrix object and implements several operations like matrix-matrix multiplication and scalar multiplication.

As you can imagine, this library has to be linked against the ATLAS library.

Find the code [here](https://bitbucket.org/juandavidcruz_tb/software-suite/src/e5556b109d24f6ece8c9dc28f0aeb5b82362afde/base/matrix-lib/?at=master).

#### Multidimensional scaling

This library isolates the MDS-SMACOF algorithm from [Borg & Groenen](http://www.springer.com/statistics/social+sciences+%26+law/book/978-0-387-25150-9) and makes it available for other algorithms such as the [boundary communities visualization algorithm](https://bitbucket.org/juandavidcruz_tb/software-suite#markdown-header-visualization).

Find the code [here](https://bitbucket.org/juandavidcruz_tb/software-suite/src/e5556b109d24f6ece8c9dc28f0aeb5b82362afde/base/mds-smacof/?at=master).

#### Trie structure

This library implements a data structure called trie (pronounced as try) that is used by the Galois lattice generator algorithm. The importance of this structure lies in the access speed to stored elements: this is an indexed tree that allows to rapidly find nodes with certain data.

This is used for to index the concepts of the lattice while being generated.

### Basic community detection and visualization algorithms
![Clustering algorithms class diagram](https://bytebucket.org/juandavidcruz_tb/software-suite/raw/069378822e6f79e33f9747400585281462e1c03a/Clustering.png?token=e821736fecaab11ad2be5a5c6ee07be438f53011)

#### Community detection V1: weight modification
This is the first version of the algorithm for detecting communities: first, the version in which the weights of the edges of the graphs are modified using the information from a SOM clustering, then the Louvain's algorithm is used to find the final communities.

Find the code [here](https://bitbucket.org/juandavidcruz_tb/software-suite/src/e5556b109d24f6ece8c9dc28f0aeb5b82362afde/algorithms/clustering/mixed/?at=master).

#####Papers
* [Analyse intégrée des réseaux sociaux pour la détection et la visualisation de communautés - TSI 2014](http://tsi.revuesonline.com/article.jsp?articleId=19440)
* [Community detection and visualization in social networks: Integrating structural and semantic information - TIST 2013](http://dl.acm.org/citation.cfm?doid=2542182.2542193)
* [Détection et visualisation des communautés dans les réseaux sociaux - Revue d'Intelligence Artificielle (2012)](http://ria.revuesonline.com/article.jsp?articleId=17738)

* [Semantic Clustering of Social Networks using Points of View - Coria 2011](http://www.asso-aria.org/coria/2011/175.pdf)
* [Point of View Based Clustering of Socio-Semantic Network - EGC 2011](http://editions-rnti.fr/?inprocid=1000973)

#### Community detection V2: contingency matrix manipulation
This algorithm uses the affiliation matrices obtained from two partitions, one from the structural variable and another from the attributes of the nodes of the network. By the multiplication of these matrices we obtain a contingency matrix, in which each position is in fact the number of agreements between the groups of both partitions, i.e., the number of nodes placed on the same group in both partitions.

Then, by manipulating (splitting) the rows of the contingency matrix it is possible to find new communities: the idea is to maximize the variance of the new potential groups.

*Find the code [here](#TODO).*

##### Papers
* [Integrating heterogeneous information within a social network for detecting communities - ASONAM 2013](http://dl.acm.org/citation.cfm?doid=2492517.2492588)
* [Information integration for detecting communities in attributed graphs - CASoN 2013](http://ieeexplore.ieee.org/xpl/articleDetails.jsp?arnumber=6622601)

#### Community detection V3: Galois lattice-based community detection
This is the third version of the community detection algorithm. This algorithm builds a galois lattice to integrate the affilaition matrix generated from the structural variable and the features of the nodes represented as a binary matrix. These two matrices are concatenated into one, and from it the lattice is calculated.

Then the concepts from the lattices are integrated according to their depth in the lattice: the more deep actors are in the lattice, the more central they are for the community.

*Find the code [here](#TODO).*

#### Papers
- Not papers yet :-(

#### Note on the entropy version
This community detection algorithm could be seen as the 1.5 version, however it has been written in Java and at this stage is not fully integrated into the platform.

This algorithm modifies the Louvain's algorithm to introduce an entropy criterion and change the way to communities are fused.

*Find the code [here](#TODO).*

#### Papers
* [Entropy based community detection in augmented social networks - CASoN 2011](http://ieeexplore.ieee.org/xpl/articleDetails.jsp?arnumber=6085937)

#### Boundary communities visualization algorithm
This is the visualization algorithm that divides the nodes into two kinds: boundary or border nodes and inner nodes. The first kind are the nodes that connect different communities while the second are the nodes connected only with other nodes inside theirs own communities.

*Find the code [here](#TODO).*

#### Papers
* [Analyse intégrée des réseaux sociaux pour la détection et la visualisation de communautés - TSI 2014](http://tsi.revuesonline.com/article.jsp?articleId=19440)
* [Community detection and visualization in social networks: Integrating structural and semantic information - TIST 2013](http://dl.acm.org/citation.cfm?doid=2542182.2542193)
* [Layout Algorithm for Clustered Graphs to Analyze Community Interactions in Social Networks - ASONAM 2012](http://www.computer.org/csdl/proceedings/asonam/2012/4799/00/4799a704-abs.html)


### Tulip plugins
These are the Tulip plugin version of the algorithms, i.e., the plugin definitions for the algorithms in such a way they can be used from Tulip menu.

These plugins should be compiled from the root folder. Get to the code [here](https://bitbucket.org/juandavidcruz_tb/software-suite/src/e5556b109d24f6ece8c9dc28f0aeb5b82362afde/pov-plugins/?at=master) and follow the instructions there to compile.

#### Importers
This folder is meant to contain importers from different king of files. Up to now there is only the [DIMACS](http://www.cc.gatech.edu/dimacs10/downloads.shtml) graph files importer.

#### Community detection
This folder contains the Louvain's and the PoV community detection algorithms.

#### Visualization
Plugin for the visualization algorithm

#### Point of view manipulation
This plugin implements a way to test different points of view using the PoV community detection algorithm plus the layout method.
        


<!--- cmake -DTULIP_DIR=/home/juancrug/tulip3 \
  -DCMAKE_MODULE_PATH=/home/juancrug/tulip3/share/tulip \
  -DATLAS_PREFIX=/home/juancrug \
  -DPREFIX=/home/juancrug \
  ..
 -->
