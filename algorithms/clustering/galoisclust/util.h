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
*/
#ifndef UTIL_H
#define UTIL_H

#include <cstring>
#include <fstream>
#include <matrix.h>
#include <tulip/Graph.h>
#include <conceptmatrix.h>

#ifndef BUFFER
#define BUFFER 4096
#endif

using namespace std;
using namespace tlp;


void get_affiliation_matrix( Matrix* dest_matrix, Graph* the_graph );

void populate_object_attr_matrix( ConceptMatrix* matrix, Matrix* affiliation_matrix );

Matrix* loadPartitionMatrix( string filename, int rows );

void processLine( char* line, int row, Matrix* dest );

Matrix* load_gtruth_partition( Graph* the_graph, string filename );

void processGroupLine( char* line, int col, int* set_idx, Matrix* dest );

#endif
