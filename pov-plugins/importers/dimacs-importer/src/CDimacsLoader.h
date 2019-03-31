/**
 Copyright (c) 2014 Juan David Cruz Gómez and Telecom - Bretagne

 juan.cruzgomez@telecom-bretagne.eu 
 juandavidcruz@gmail.com

 Licensed under the EUPL, Version 1.2 or – as soon theywill be approved 
 by the European Commission - subsequent versions of the 
 EUPL (the "Licence");

 You may not use this work except in compliance with the Licence.
 You may obtain a copy of the Licence at:

    https://joinup.ec.europa.eu/software/page/eupl5
  
 Unless required by applicable law or agreed to inwriting, software 
 distributed under the Licence isdistributed on an *"AS IS"* basis,
 *WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND*, either express or implied.
 See the Licence for the specific language governing permissions and limitations 
 under the Licence.


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
