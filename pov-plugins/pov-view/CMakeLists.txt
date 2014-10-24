#This is the main CMakeLists.txt file for the project. From this file all
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
#This file has been created by Juan David Cruz Gomez for his PhD thesis
#Telecom - Bretagne, Brest, France. June 8th 2012
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

PROJECT(PoVIntegratorViewPlugin)
SET( PLUGIN_NAME PoVViewPlugin )


FIND_PACKAGE(Qt4 REQUIRED)

INCLUDE(${QT_USE_FILE})
INCLUDE_DIRECTORIES( ${INCLUDE_DIRECTORIES} 
	include 
	${TULIP_INCLUDE_DIR} 
	${QT_INCLUDE_DIR} 
	${ATLAS_INCLUDE}
)

ADD_SUBDIRECTORY( src )
ADD_SUBDIRECTORY( interactors )


