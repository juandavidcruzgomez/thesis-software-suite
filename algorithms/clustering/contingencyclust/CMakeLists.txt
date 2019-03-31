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

# Contigency clustering
SET(CONTCLUST_SRCS ${CMAKE_CURRENT_SOURCE_DIR}/CommunityAlgorithm.cpp)
  
ADD_LIBRARY(${CONTINGENCYCLUST_LIB_NAME} SHARED ${CONTCLUST_SRCS} )

TARGET_LINK_LIBRARIES(${CONTINGENCYCLUST_LIB_NAME} ${MEASURES_LIB_NAME} ${TULIP_LIBRARY} )

INSTALL( TARGETS ${CONTINGENCYCLUST_LIB_NAME} 
            LIBRARY DESTINATION ${INSTALL_LIB_PATH} 
            RUNTIME DESTINATION ${INSTALL_LIB_PATH}
            ARCHIVE DESTINATION ${INSTALL_LIB_PATH} )

INSTALL( FILES CommunityAlgorithm.h DESTINATION ${INSTALL_INCLUDE_PATH} )

#Compile the main

SET( CORE_MAIN_LIBS ${CORE_LIBS}
            ${TAB_IMPORT_LIB_NAME}
            ${LOUVAIN_LIB_NAME}
            ${PAGERANK_LIB_NAME}
            ${CENTRALITY_LIB_NAME}
            ${MIXED_LIB_NAME}
            ${KMEANS_LIB_NAME}
            ${MEASURES_LIB_NAME})

SET(CONTINGENCYCLUST_MAIN_SRCS ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)

ADD_EXECUTABLE(${CONTINGENCYCLUST_LIB_NAME}_test ${CONTINGENCYCLUST_MAIN_SRCS} )

TARGET_LINK_LIBRARIES(${CONTINGENCYCLUST_LIB_NAME}_test ${CONTINGENCYCLUST_LIB_NAME} ${CORE_MAIN_LIBS} ${TULIP_LIBRARY} )
