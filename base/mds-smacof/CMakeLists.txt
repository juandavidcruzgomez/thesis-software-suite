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
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

PROJECT(MultidimensionalScaling)

SET( LIBRARY_NAME smacofmds )

################################################################################
#C++ flags
#No warnings please!
set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")

#Setup the type of building
#SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -g") #Debug
SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3" ) #Full optimization
################################################################################
SET( INSTALL_BASE_PATH ${PREFIX} )
SET( INSTALL_LIB_PATH ${INSTALL_BASE_PATH}/lib )
SET( INSTALL_INCLUDE_PATH ${INSTALL_BASE_PATH}/include )
################################################################################
#Matrix Lib
SET( MATRIX_LIB_PATH ${MATRIX_PREFIX}/lib )
SET( MATRIX_INC_PATH ${MATRIX_PREFIX}/include )
SET( CMAKE_LIBARY_PATH ${CMAKE_LIBARY_PATH} ${MATRIX_LIB_PATH})

FIND_LIBRARY(MATRIX NAMES bmatrix PATHS ${CMAKE_LIBARY_PATH} NO_DEFAULT_PATH )
################################################################################
# Where to find all the headers
SET( HEADERS ${HEADERS} ${MATRIX_INC_PATH} ./src)

INCLUDE_DIRECTORIES(${HEADERS})

# Set the libraries to be used
SET( CORE_LIBS pthread
  dl
  ${MATRIX})

ADD_SUBDIRECTORY( src )
################################################################################
ADD_EXECUTABLE( ${LIBRARY_NAME}_test mds_test.cpp )

TARGET_LINK_LIBRARIES(${LIBRARY_NAME}_test ${LIBRARY_NAME} )
