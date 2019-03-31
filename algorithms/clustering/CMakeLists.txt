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
