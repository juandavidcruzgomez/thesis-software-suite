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

# Galois clustering
SET(GCLUST_SRCS ${CMAKE_CURRENT_SOURCE_DIR}/util.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/basicgaloisclustering.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/clusteringexperiment.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/preclustered_experiment.cpp)
  
ADD_LIBRARY(${GALOISCLUST_LIB_NAME} SHARED ${CPP_FILES} ${GCLUST_SRCS} )

TARGET_LINK_LIBRARIES(${GALOISCLUST_LIB_NAME} ${MEASURES_LIB_NAME} ${TULIP_LIBRARY} )

INSTALL( TARGETS ${GALOISCLUST_LIB_NAME} 
            LIBRARY DESTINATION ${INSTALL_LIB_PATH} 
            RUNTIME DESTINATION ${INSTALL_LIB_PATH}
            ARCHIVE DESTINATION ${INSTALL_LIB_PATH} )

INSTALL( FILES basicgaloisclustering.h DESTINATION ${INSTALL_INCLUDE_PATH} )
INSTALL( FILES util.h DESTINATION ${INSTALL_INCLUDE_PATH} )


#Compile the main

SET( CORE_MAIN_LIBS ${CORE_LIBS}
            ${TAB_IMPORT_LIB_NAME}
            ${LOUVAIN_LIB_NAME}
            ${PAGERANK_LIB_NAME}
            ${CENTRALITY_LIB_NAME}
            ${MIXED_LIB_NAME}
            ${KMEANS_LIB_NAME}
            ${MEASURES_LIB_NAME}
            ${GALOIS})

SET(GCLUST_MAIN_SRCS ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)

ADD_EXECUTABLE(${GALOISCLUST_LIB_NAME}_test ${GCLUST_MAIN_SRCS} )

TARGET_LINK_LIBRARIES(${GALOISCLUST_LIB_NAME}_test ${GALOISCLUST_LIB_NAME} ${CORE_MAIN_LIBS} ${TULIP_LIBRARY} )
