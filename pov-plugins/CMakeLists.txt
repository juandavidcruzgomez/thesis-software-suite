# Copyright (c) 2014 Juan David Cruz Gómez and Telecom - Bretagne
#
# juan.cruzgomez@telecom-bretagne.eu 
# juandavidcruz@gmail.com
#
# Licensed under the EUPL, Version 1.2 or – as soon theywill be approved 
# by the European Commission - subsequent versions of the 
# EUPL (the "Licence");
#
# You may not use this work except in compliance with the Licence.
# You may obtain a copy of the Licence at:
#
#    https://joinup.ec.europa.eu/software/page/eupl5
#  
# Unless required by applicable law or agreed to inwriting, software 
# distributed under the Licence isdistributed on an *"AS IS"* basis,
# *WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND*, either express or implied.
# See the Licence for the specific language governing permissions and limitations 
# under the Licence.

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
