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
#Louvain

SET(LOUV_SRCS ${CMAKE_CURRENT_SOURCE_DIR}/CommunitySpace.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/louvain.cpp)
  
ADD_LIBRARY(${LOUVAIN_LIB_NAME} SHARED ${CPP_FILES} ${LOUV_SRCS} )

TARGET_LINK_LIBRARIES(${LOUVAIN_LIB_NAME} ${MEASURES_LIB_NAME} ${TULIP_LIBRARY} )

INSTALL( TARGETS ${LOUVAIN_LIB_NAME} 
            LIBRARY DESTINATION ${INSTALL_LIB_PATH} 
            RUNTIME DESTINATION ${INSTALL_LIB_PATH}
            ARCHIVE DESTINATION ${INSTALL_LIB_PATH} )

INSTALL( FILES louvain.h DESTINATION ${INSTALL_INCLUDE_PATH} )
INSTALL( FILES CommunitySpace.h DESTINATION ${INSTALL_INCLUDE_PATH} )

