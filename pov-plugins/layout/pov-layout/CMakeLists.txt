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
#Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
#cmake -DCMAKE_MODULE_PATH=~/tulip3dev/share/tulip -DATLAS_LIB=/home/juancrug/lib/ -DATLAS_INCLUDE=~/include/ -DTULIP_DIR=/home/juancrug/tulip3dev/ ..
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

PROJECT(PoVPlugins)

SET( PLUGIN_NAME PoVCommunityLayoutPluginV2 )

SET( CPP_FILES ${CPP_FILES} 
  CLayoutSpace.cpp
	ExecutionLog.cpp
	PoVLayoutTulipPlugin.cpp)

ADD_LIBRARY(${PLUGIN_NAME}-${TULIP_PLUGIN_VERSION} SHARED ${CPP_FILES} )

TARGET_LINK_LIBRARIES(${PLUGIN_NAME}-${TULIP_PLUGIN_VERSION} ${TULIP_LIBRARY} ${CORE_LIBS} ${SMACOF})

INSTALL( TARGETS ${PLUGIN_NAME}-${TULIP_PLUGIN_VERSION} LIBRARY DESTINATION ${TULIP_PLUGINS_PATH} )
