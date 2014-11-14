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


#cmake -DPREFIX=/home/juancrug ..
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

PROJECT(GaloisLattices)

# Test application name
SET( APPLICATION_NAME galois_test )
# Library names
SET( LIB_NAME  galoislatt )

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

SET(SRCS latticeexporter.cpp 
         galoislattice.cpp 
         concept.cpp 
         importmatrix.cpp 
         conceptmatrix.cpp
         lightdlinkdlist.cpp
         trie.cpp)
  
SET( CPP_FILES ${SRCS} )

ADD_LIBRARY(${LIB_NAME} SHARED ${CPP_FILES} )

TARGET_LINK_LIBRARIES(${LIB_NAME} )

SET( HEADERS_EXPORT latticeexporter.h 
                    galoislattice.h 
                    importmatrix.h 
                    conceptmatrix.h 
                    generalinc.h 
                    concept.h
                    trie.h
                    lightdlinkdlist.h)

INSTALL( TARGETS ${LIB_NAME} 
            LIBRARY DESTINATION ${INSTALL_LIB_PATH} 
            RUNTIME DESTINATION ${INSTALL_LIB_PATH}
            ARCHIVE DESTINATION ${INSTALL_LIB_PATH} )

INSTALL( FILES ${HEADERS_EXPORT} DESTINATION ${INSTALL_INCLUDE_PATH} )
################################################################################
ADD_EXECUTABLE(${APPLICATION_NAME} main.cpp )
TARGET_LINK_LIBRARIES(${APPLICATION_NAME} ${LIB_NAME} )
