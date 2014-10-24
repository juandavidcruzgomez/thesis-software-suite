#This is the root CMake script for the PoV Plugins for Tulip
#Copyright (C) 2014  Juan David Cruz Gomez juan.cruzgomez@telecom-bretagne.eu
#
#This program is free software; you can redistribute it and/or
#modify it under the terms of the GNU General Public License
#as published by the Free Software Foundation; either version 2
#of the License, or (at your option) any later version.
#
#This program is distributed in the hope that it will be useful,
#but WITHOUT ANY WARRANTY; without even the implied warranty of
#MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#GNU General Public License for more details.
#
#You should have received a copy of the GNU General Public License
#along with this program; if not, write to the Free Software
#Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
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
