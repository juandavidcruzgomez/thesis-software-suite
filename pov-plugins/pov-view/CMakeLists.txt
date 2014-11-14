#The MIT License (MIT)

#Copyright (c) 2012 Juan David Cruz Gómez and Telecom - Bretagne
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


