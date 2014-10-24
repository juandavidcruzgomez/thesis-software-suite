/*
    Imports a Dimacs format file into Tulip
    Copyright (C) 2012  Juan David Cruz-Gomez juan.cruzgomez@telecom-bretagne.eu
    This program has been written durin my PhD thesis at Telecom-Bretagne

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/
#ifndef DIMACS_LOADER_H
#define DIMACS_LOADER_H

#define BUFFER 128

#include <iostream>
#include <fstream>
#include <tulip/Graph.h>
#include <tulip/StringProperty.h>

#include <string>
#include <cstring>
#include <set>


class CDimacsLoader{
public:
	CDimacsLoader( tlp::Graph* &_theGraph );
	
	
	void signalError( const char* msg );
	
	void loadGraph( std::string &filename );
	
	void processLine( char* line );
	
private:
	/**
	 * The graph in which the structure will be loaded.
	 */
	tlp::Graph* theGraph;
	
	std::map<int,tlp::node> node_set;
	
	int number_of_nodes;
	
	int number_of_edges;
};

#endif
