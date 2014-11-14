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
#Benchmarking

SET(SRCS distances.cpp
        basicentropy.cpp
        partitionsimilarity.cpp
        basicoperations.cpp)
  
SET( CPP_FILES ${SRCS} )

ADD_LIBRARY(${MEASURES_LIB_NAME} SHARED ${CPP_FILES} )

INSTALL( TARGETS ${MEASURES_LIB_NAME} 
            LIBRARY DESTINATION ${INSTALL_LIB_PATH} 
            RUNTIME DESTINATION ${INSTALL_LIB_PATH}
            ARCHIVE DESTINATION ${INSTALL_LIB_PATH} )

INSTALL( FILES distances.h DESTINATION ${INSTALL_INCLUDE_PATH} )
INSTALL( FILES basicentropy.h DESTINATION ${INSTALL_INCLUDE_PATH} )
INSTALL( FILES partitionsimilarity.h DESTINATION ${INSTALL_INCLUDE_PATH} )
INSTALL( FILES basicoperations.h DESTINATION ${INSTALL_INCLUDE_PATH} )
