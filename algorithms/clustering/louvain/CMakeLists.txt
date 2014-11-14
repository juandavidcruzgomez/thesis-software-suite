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

