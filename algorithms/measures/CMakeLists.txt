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
#Benchmarking

SET(SRCS distances.cpp
        basicentropy.cpp
        partitionsimilarity.cpp)
  
SET( CPP_FILES ${SRCS} )

ADD_LIBRARY(${MEASURES_LIB_NAME} SHARED ${CPP_FILES} )

INSTALL( TARGETS ${MEASURES_LIB_NAME} 
            LIBRARY DESTINATION ${INSTALL_LIB_PATH} 
            RUNTIME DESTINATION ${INSTALL_LIB_PATH}
            ARCHIVE DESTINATION ${INSTALL_LIB_PATH} )

INSTALL( FILES distances.h DESTINATION ${INSTALL_INCLUDE_PATH} )
INSTALL( FILES basicentropy.h DESTINATION ${INSTALL_INCLUDE_PATH} )
INSTALL( FILES partitionsimilarity.h DESTINATION ${INSTALL_INCLUDE_PATH} )
