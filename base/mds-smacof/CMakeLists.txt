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
