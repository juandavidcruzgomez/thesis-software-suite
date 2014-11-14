#The MIT License (MIT)

#Copyright (c) 2014 Juan David Cruz Gómez and Telecom - Bretagne
#juan.cruzgomez@telecom-bretagne.eu

#Permission is hereby granted, free of charge, to any person obtaining a copy
#of this software and associated documentation files (the "Software"), to deal
#in the Software without restriction, including without limitation the rights
#to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
#copies of the Software, and to permit persons to whom the Software is
#furnished to do so, subject to the following conditions:

#The above copyright notice and this permission notice shall be included in
#all copies or substantial portions of the Software.

#THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
#IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
#FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
#AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
#LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
#OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
#THE SOFTWARE.

#cmake -DCMAKE_MODULE_PATH=/home/juancrug/tulip3/share/tulip -DTULIP_DIR=/home/juancrug/tulip3 -DPREFIX=/home/juancrug -DATLAS_PREFIX=/home/juancrug -DBASE_PREFIX=/home/juancrug ..
#This is the root of the project. From here everything should be built.

CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

PROJECT(CommunityDetectionBaseAlgorithms)

################################################################################
#C++ flags
#No warnings please!
set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")

#Setup the type of building
#SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -g") #Debug
SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3" ) #Full optimization
################################################################################
# Where to install the libraries
SET( INSTALL_BASE_PATH ${PREFIX} )
SET( INSTALL_LIB_PATH ${INSTALL_BASE_PATH}/lib )
SET( INSTALL_INCLUDE_PATH ${INSTALL_BASE_PATH}/include )
################################################################################
# Find required libraries
FIND_PACKAGE(TULIP3 REQUIRED)
#Atlas libraries
SET( ATLAS_LIB_PATH ${ATLAS_PREFIX}/lib )
SET( ATLAS_INC_PATH ${ATLAS_PREFIX}/include )
FIND_LIBRARY(PTBLAS NAMES ptcblas PATHS ${ATLAS_LIB_PATH} NO_DEFAULT_PATH )
FIND_LIBRARY(ATLAS NAMES atlas PATHS ${ATLAS_LIB_PATH} NO_DEFAULT_PATH )
#Matrix library
SET( MATRIX_LIB_PATH ${BASE_PREFIX}/lib )
SET( MATRIX_INC_PATH ${BASE_PREFIX}/include )
FIND_LIBRARY(BMATRIX NAMES bmatrix PATHS ${MATRIX_LIB_PATH} NO_DEFAULT_PATH )
#Galois lattice library
SET( GALOIS_LIB_PATH ${BASE_PREFIX}/lib )
SET( GALOIS_INC_PATH ${BASE_PREFIX}/include )
FIND_LIBRARY(GALOIS NAMES galoislatt PATHS ${GALOIS_LIB_PATH} NO_DEFAULT_PATH )

SET( CMAKE_LIBARY_PATH ${CMAKE_LIBARY_PATH} 
      ${ATLAS_LIB_PATH} 
      ${MATRIX_LIB_PATH}
      ${GALOIS_LIB_PATH})
SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
################################################################################

## Library names
SET( TAB_IMPORT_LIB_NAME  tableimport )
# Clustering
SET( LOUVAIN_LIB_NAME louvain )
SET( GALOISCLUST_LIB_NAME galoisclust )
SET( CONTINGENCYCLUST_LIB_NAME contingencyclust )
SET( PAGERANK_LIB_NAME pagerank )
SET( CENTRALITY_LIB_NAME central )
SET( MIXED_LIB_NAME povcm )
SET( BASICDM_LIB_NAME basicclustering )
SET( KMEANS_LIB_NAME generalkmeans )
SET( MEASURES_LIB_NAME measurestoolbox )
################################################################################
# Where to find all the headers
SET( HEADERS ${TULIP_INCLUDE_DIR}
              ${ATLAS_INC_PATH}
              ${MATRIX_INC_PATH}
              import 
              clustering 
              measures)

INCLUDE_DIRECTORIES(${HEADERS})
SET( CORE_LIBS pthread
        dl
        ${ATLAS}
        ${PTBLAS}
        ${BMATRIX})
################################################################################
# Complie all the libraries
ADD_SUBDIRECTORY( import )
ADD_SUBDIRECTORY( measures )
ADD_SUBDIRECTORY( clustering )
