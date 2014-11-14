/**
 The MIT License (MIT)

 Copyright (c) 2012 Juan David Cruz Gómez and Telecom - Bretagne 
 juan.cruzgomez@telecom-bretagne.eu

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.

    Imports a Dimacs format file into Tulip
    Copyright (C) 2012  Juan David Cruz-Gomez juan.cruzgomez@telecom-bretagne.eu
    This program has been written durin my PhD thesis at Telecom-Bretagne

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
