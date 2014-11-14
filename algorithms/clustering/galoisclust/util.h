#ifndef __UTIL_H__
#define __UTIL_H__

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