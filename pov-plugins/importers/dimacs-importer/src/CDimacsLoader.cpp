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
#include "CDimacsLoader.h"

CDimacsLoader::CDimacsLoader( tlp::Graph* &_theGraph ) : theGraph(_theGraph){
	if( theGraph == NULL ){
		signalError("Error: graph cannot be NULL." );
	}else{
		number_of_nodes = -1;
		number_of_edges = -1;
	}

}

void CDimacsLoader::signalError( const char* msg ){
	if( msg == NULL ){
			msg = "";
	}
	std::cout << "There's is an error: " << msg << std::endl;
}

void CDimacsLoader::loadGraph( std::string &filename ){
	if( filename.size() > 0 ){
		char line[BUFFER];
		int gcount = 0;
		std::fstream infile;
		infile.open(filename.c_str(), std::ios::in);
		memset(line, '\0', BUFFER);
		if( infile.is_open() ){
			//Read each line of the file to build the graph
			//Process each line according to the file definition
			while( !infile.eof() ){
				infile.getline(line, BUFFER);
				gcount = infile.gcount();
				processLine(line);
				memset(line, '\0', gcount);
			}
			infile.close();
		}else{
			signalError("error loading the file.");
		}
	}
}


void CDimacsLoader::processLine( char* line ){
	if( line != NULL ){
		//Get the first character of the line
		char type = line[0];
		line += 2;
		std::string process;
		char* splitted = NULL;
		int column = 0;
		int source = -1;
		int target = -1;
		float weight = 0;
		tlp::node n_source;
		tlp::node n_target;
		tlp::edge e;
		char weight_label[BUFFER];
		std::map<int,tlp::node>::iterator it;		
		switch (type) {
			case 'p':
				//First line
				splitted = strtok(line,"\t ");
				while( splitted != NULL ){
					if( column == 0 ){
						//Nothing for now...
					}else if (column == 1) {
						number_of_nodes = atoi( splitted );
					}else{
						number_of_edges = atoi( splitted );
					}
					column++;
					splitted = strtok(NULL,"\t ");
				}
				break;
			case 'a':
				//Edges
				splitted = strtok(line,"\t ");
				while( splitted != NULL ){
					if( column == 0 ){
						source = atoi( splitted );
					}else if( column == 1 ){
						target = atoi( splitted );
					}else{
						weight = atof( splitted );
					}
					column++;
					splitted = strtok(NULL,"\t ");
				}
				//Create the nodes...
				it = node_set.find( source );
				if( it == node_set.end() ){
					char label[BUFFER];
					n_source = theGraph->addNode();
					node_set[source] = n_source;
					sprintf(label, "%d", source);
					theGraph->getLocalProperty<tlp::StringProperty>("viewLabel")->setNodeValue(n_source,std::string(label));
				}
				it = node_set.find( target );
				if( it == node_set.end() ){
					char label[BUFFER];
					n_target = theGraph->addNode();
					node_set[target] = n_target;
					sprintf(label, "%d", target);
					theGraph->getLocalProperty<tlp::StringProperty>("viewLabel")->setNodeValue(n_target,std::string(label));
				}
				//and the edge...
				e = theGraph->addEdge(node_set[source], node_set[target]);
				sprintf(weight_label, "%3.2f", weight);
				theGraph->getLocalProperty<tlp::StringProperty>("viewLabel")->setEdgeValue(e,std::string(weight_label));
				break;
			default:
				break;
		}
	}
}
