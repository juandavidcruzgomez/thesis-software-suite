#The MIT License (MIT)

#Copyright (c) 2012 Juan David Cruz Gómez and Telecom - Bretagne
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
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

PROJECT(PoVPlugins)

################################################################################
#C++ flags
#No warnings please!
set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")

#Setup the type of building
#SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -g") #Debug
SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3" ) #Full optimization
################################################################################
# Find required libraries
FIND_PACKAGE(TULIP3 REQUIRED)
#Atlas libraries
SET( ATLAS_LIB_PATH ${ATLAS_PREFIX}/lib )
SET( ATLAS_INC_PATH ${ATLAS_PREFIX}/include )
#Matrix Lib
SET( MATRIX_LIB_PATH ${MATRIX_PREFIX}/lib )
SET( MATRIX_INC_PATH ${MATRIX_PREFIX}/include )
#MDS lib
SET( MDS_LIB_PATH ${MDS_PREFIX}/lib )
SET( MDS_INC_PATH ${MDS_PREFIX}/include )
#Base lib
SET( BASE_LIB_PATH ${BASE_PREFIX}/lib )
SET( BASE_INCLUDE_PATH ${BASE_PREFIX}/include )

SET( CMAKE_LIBARY_PATH ${CMAKE_LIBARY_PATH} 
  ${ATLAS_LIB_PATH} 
  ${MATRIX_LIB_PATH} 
  ${MDS_LIB_PATH} 
  ${BASE_LIB_PATH})

FIND_LIBRARY(PTBLAS NAMES ptcblas PATHS ${CMAKE_LIBARY_PATH} NO_DEFAULT_PATH )
FIND_LIBRARY(ATLAS NAMES atlas PATHS ${CMAKE_LIBARY_PATH} NO_DEFAULT_PATH )
FIND_LIBRARY(MATRIX NAMES bmatrix PATHS ${CMAKE_LIBARY_PATH} NO_DEFAULT_PATH )
FIND_LIBRARY(SMACOF NAMES smacofmds PATHS ${CMAKE_LIBARY_PATH} NO_DEFAULT_PATH )
#FIND_LIBRARY(BASE NAMES basicclustering PATHS ${CMAKE_LIBARY_PATH} NO_DEFAULT_PATH )
FIND_LIBRARY(LOUVAIN NAMES louvain PATHS ${CMAKE_LIBARY_PATH} NO_DEFAULT_PATH )
FIND_LIBRARY(POVCD NAMES povcm PATHS ${CMAKE_LIBARY_PATH} NO_DEFAULT_PATH )

SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
################################################################################
# Set the libraries to be used
SET( CORE_LIBS pthread 
        dl 
        ${ATLAS} 
        ${PTBLAS} 
        ${MATRIX} 
        ${SMACOF} )

SET( HEADERS ${TULIP_INCLUDE_DIR}
  ${ATLAS_INC_PATH}
  ${MATRIX_INC_PATH}
  ${MDS_INC_PATH}
  ${BASE_INCLUDE_PATH})

INCLUDE_DIRECTORIES(${HEADERS})
################################################################################

# Complie all the plugins
# Importers
ADD_SUBDIRECTORY(importers)
# Roles
ADD_SUBDIRECTORY(roles)
# Clustering
ADD_SUBDIRECTORY(clustering)
# Layout
ADD_SUBDIRECTORY(layout)
# Point of View manipulation
ADD_SUBDIRECTORY(pov-view)
