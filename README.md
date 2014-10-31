# Juan David Cruz-Gómez PhD Thesis software suite

This repository contains several software projects developped during my PhD thesis
at Telecom - Bretagne. Since the software and algorithms were mostly written for
papers and thus in a rush, the code may not be the best and cleanest code you
may ever seen.

However, in an effort to write clean code, I try to document all the code and to
automate the building process. To do this I use CMake (I hope you know the basics
of CMake).

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

## Installing CMake

## Installing and configuring Tulip

## Installing and configuring ATLAS

## Projects

### Base algorithms

#### Matrix library

#### Multidimensional scaling

#### Trie structure

### Basic community detection and visualization algorithms

#### Community detection V1: weight modification

#### Community detection V2: contingency matrix manupulation

#### Community detection V3: Galois lattice-based community detection

#### Note on the entropy version

#### Boundary communities visualization algorithm

### Tulip plugins

#### Importers

#### Community detection

#### Visualization

#### Point of view manipulation

        


cmake -DTULIP_DIR=/home/juancrug/tulip3 \
  -DCMAKE_MODULE_PATH=/home/juancrug/tulip3/share/tulip \
  -DATLAS_PREFIX=/home/juancrug \
  -DPREFIX=/home/juancrug \
  ..

