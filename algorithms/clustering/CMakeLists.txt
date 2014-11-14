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
#clustering subdirectory

SET( HEADERS ${HEADERS}
             ${CMAKE_CURRENT_SOURCE_DIR}/louvain 
             ${CMAKE_CURRENT_SOURCE_DIR}/mixed 
             ${CMAKE_CURRENT_SOURCE_DIR}/centrality 
             ${CMAKE_CURRENT_SOURCE_DIR}/basicdm 
             ${CMAKE_CURRENT_SOURCE_DIR}/galoisclust
             ${CMAKE_CURRENT_SOURCE_DIR}/contingencyclust
             PARENT_SCOPE)
             
INCLUDE_DIRECTORIES( ${HEADERS} 
                  ${CMAKE_CURRENT_SOURCE_DIR}/louvain 
                  ${CMAKE_CURRENT_SOURCE_DIR}/mixed 
                  ${CMAKE_CURRENT_SOURCE_DIR}/centrality 
                  ${CMAKE_CURRENT_SOURCE_DIR}/basicdm
                  ${CMAKE_CURRENT_SOURCE_DIR}/galoisclust
                  ${CMAKE_CURRENT_SOURCE_DIR}/contingencyclust)

SET( CPP_FILES ${CPP_FILES}
  ${CMAKE_CURRENT_SOURCE_DIR}/clusteringbase.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/tableclustering.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/utility.cpp)

ADD_SUBDIRECTORY( louvain )
ADD_SUBDIRECTORY( mixed )
ADD_SUBDIRECTORY( centrality )
ADD_SUBDIRECTORY( basicdm )
ADD_SUBDIRECTORY( galoisclust )
ADD_SUBDIRECTORY( contingencyclust )

INSTALL( FILES clusteringbase.h DESTINATION ${INSTALL_INCLUDE_PATH} )
INSTALL( FILES tableclustering.h DESTINATION ${INSTALL_INCLUDE_PATH} )
INSTALL( FILES colorwheel.h DESTINATION ${INSTALL_INCLUDE_PATH} )
INSTALL( FILES utility.h DESTINATION ${INSTALL_INCLUDE_PATH} )
