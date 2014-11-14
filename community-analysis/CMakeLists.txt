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

#cmake -DCMAKE_MODULE_PATH=/home/juancrug/tulip3/share/tulip -DTULIP_DIR=/home/juancrug/tulip3 -DPREFIX=/home/juancrug -DATLAS_PREFIX=/home/juancrug ..
#This is the root of the project. From here everything should be built.
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

PROJECT(CommunityAnalysisTestbed)

SET( APPLICATION_NAME analysistest )


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
# Atlas libraries
SET( ATLAS_LIB_PATH ${ATLAS_PREFIX}/lib )
SET( ATLAS_INC_PATH ${ATLAS_PREFIX}/include )
FIND_LIBRARY(PTBLAS NAMES ptcblas PATHS ${ATLAS_LIB_PATH} NO_DEFAULT_PATH )
FIND_LIBRARY(ATLAS NAMES atlas PATHS ${ATLAS_LIB_PATH} NO_DEFAULT_PATH )

SET( LIB_PATH ${BASE_PREFIX}/lib )
SET( INC_PATH ${BASE_PREFIX}/include )
# Matrix library
FIND_LIBRARY(BMATRIX NAMES bmatrix PATHS ${LIB_PATH} NO_DEFAULT_PATH )
# Trie library
#FIND_LIBRARY(BTRIE NAMES btrie PATHS ${LIB_PATH} NO_DEFAULT_PATH )
# Clustering libraries
FIND_LIBRARY(TAB_IMPORT_LIB_NAME NAMES tableimport PATHS ${LIB_PATH} NO_DEFAULT_PATH )
FIND_LIBRARY(LOUVAIN_LIB_NAME NAMES louvain PATHS ${LIB_PATH} NO_DEFAULT_PATH )
FIND_LIBRARY(PAGERANK_LIB_NAME NAMES pagerank PATHS ${LIB_PATH} NO_DEFAULT_PATH )
FIND_LIBRARY(CENTRALITY_LIB_NAME NAMES central PATHS ${LIB_PATH} NO_DEFAULT_PATH )
FIND_LIBRARY(MIXED_LIB_NAME NAMES povcm PATHS ${LIB_PATH} NO_DEFAULT_PATH )
FIND_LIBRARY(BASICDM_LIB_NAME NAMES basicclustering PATHS ${LIB_PATH} NO_DEFAULT_PATH )
FIND_LIBRARY(KMEANS_LIB_NAME NAMES generalkmeans PATHS ${LIB_PATH} NO_DEFAULT_PATH )
# Measures
FIND_LIBRARY(MEASURES_LIB_NAME NAMES measurestoolbox PATHS ${LIB_PATH} NO_DEFAULT_PATH )
# Benchmarking
SET( BENCHMARKING_LIB_NAME benchmark )
##
SET( CMAKE_LIBARY_PATH ${CMAKE_LIBARY_PATH} ${ATLAS_LIB_PATH} ${LIB_PATH})
SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
################################################################################
# Where to find all the headers
SET( HEADERS ${TULIP_INCLUDE_DIR}
              ${ATLAS_INC_PATH}
              ${INC_PATH})

INCLUDE_DIRECTORIES(${HEADERS})
################################################################################
# Set the libraries to be used
SET( BENCH_CORE_LIBS pthread
        dl
        ${ATLAS}
        ${PTBLAS}
        ${MATRIX})
        
SET( CORE_LIBS pthread
        dl
        ${ATLAS}
        ${PTBLAS}
        ${MATRIX}
        ${TAB_IMPORT_LIB_NAME}
        ${LOUVAIN_LIB_NAME}
        ${MIXED_LIB_NAME}
        ${PAGERANK_LIB_NAME}
        ${CENTRALITY_LIB_NAME}
        ${KMEANS_LIB_NAME}
        ${MEASURES_LIB_NAME})        
################################################################################
#Compile the benchmarking library
SET(BENCH_SRCS  basicoperations.cpp
          basicentropy.cpp
          partitionsimilarity.cpp)
  
ADD_LIBRARY(${BENCHMARKING_LIB_NAME} SHARED ${BENCH_SRCS} )

TARGET_LINK_LIBRARIES(${BENCHMARKING_LIB_NAME} ${BENCH_CORE_LIBS} )

INSTALL( TARGETS ${BENCHMARKING_LIB_NAME} 
            LIBRARY DESTINATION ${INSTALL_LIB_PATH} 
            RUNTIME DESTINATION ${INSTALL_LIB_PATH}
            ARCHIVE DESTINATION ${INSTALL_LIB_PATH} )

INSTALL( FILES basicentropy.h DESTINATION ${INSTALL_INCLUDE_PATH} )
INSTALL( FILES partitionsimilarity.h DESTINATION ${INSTALL_INCLUDE_PATH} )
INSTALL( FILES basicoperations.h DESTINATION ${INSTALL_INCLUDE_PATH} )
################################################################################
# Compile the testing program
SET( CPP_FILES experiment.cpp
          main.cpp )
          
ADD_EXECUTABLE(${APPLICATION_NAME} ${CPP_FILES})

# Link the main program against all the required libraries
TARGET_LINK_LIBRARIES(${APPLICATION_NAME} ${TULIP_LIBRARY} ${CORE_LIBS} ${BENCHMARKING_LIB_NAME} )
################################################################################
