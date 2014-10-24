#This is the root CMake script for the PoV Plugins for Tulip
#Copyright (C) 2014  Juan David Cruz Gomez juan.cruzgomez@telecom-bretagne.eu
#
#This program is free software; you can redistribute it and/or
#modify it under the terms of the GNU General Public License
#as published by the Free Software Foundation; either version 2
#of the License, or (at your option) any later version.
#
#This program is distributed in the hope that it will be useful,
#but WITHOUT ANY WARRANTY; without even the implied warranty of
#MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#GNU General Public License for more details.
#
#You should have received a copy of the GNU General Public License
#along with this program; if not, write to the Free Software
SET( CPP_FILES  ${CPP_FILES} 
	multidimscaling.cpp
	distance_factory.cpp
  util.cpp)

ADD_LIBRARY(${LIBRARY_NAME} SHARED ${CPP_FILES} )

TARGET_LINK_LIBRARIES(${LIBRARY_NAME} ${CORE_LIBS} )

INSTALL( TARGETS ${LIBRARY_NAME} 
            LIBRARY DESTINATION ${INSTALL_LIB_PATH} 
            RUNTIME DESTINATION ${INSTALL_LIB_PATH}
            ARCHIVE DESTINATION ${INSTALL_LIB_PATH} )

INSTALL( FILES multidimscaling.h 
  util.h 
  distance.h 
  distance_factory.h 
  distance_chebyshev.h 
  distance_euclidean.h 
  distance_manhattan.h DESTINATION ${INSTALL_INCLUDE_PATH} )
