/**
 The MIT License (MIT)

 Copyright (c) 2014 Juan David Cruz Gómez and Telecom - Bretagne 
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
