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
