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
