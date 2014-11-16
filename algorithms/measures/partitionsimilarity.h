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
#ifndef PARTITIONSIM_H
#define PARTITIONSIM_H

#include <tulip/Graph.h>
#include <math.h>

#include <matrix.h>

#define BYROW 0
#define BYCOL 1

using namespace tlp;

/**
 * Calculate the Adjusted Rand Index of two paritions
 */
double calculate_ARI( Graph* parititon_a, Graph* parititon_b );
/**
 * Calculate the Adjusted Rand Index of two paritions one being the raw affiliation matrix
 */
double calculate_ARI( Matrix* partition_a, Graph* partition_b );

/**
 * Calculate the Normalized Mutual Information index of two partitions
 */
double calculate_NMI( Graph* parititon_a, Graph* parititon_b );

////// Helper functions
/**
 * Generates the affiliation matrix of a partititon
 * @param partition a graph contening the groups of the partition
 * @return the binary affliation matrix of the nodes
 */
Matrix* extract_affliation_matrix( Graph* partition );
/**
 * Generates a contingency matrix from the affiliation matrices from each
 * partition A and B by multiplying A'B
 * @param partition_a the first partition (typically the structural partition)
 * @param partition_a the second partition (typically the composition partition)
 * @return the contingency matrix
 */
Matrix* generate_contingency_matrix( Matrix* partition_a, Matrix* partition_b );
/**
 * Calculates the maximum index for the ARI
 */
float ari_max_index( Matrix* col_sum, Matrix* row_sum );
/**
 * Calculates the expected ARI index
 */
float ari_expected_index( Matrix* col_sum, Matrix* row_sum );
/**
 * Calculates the entropy of a partition
 * @param contingency_matrix the matrix containing the agreements between partitions
 * @param nb_nodes the number of nodes in the graph
 * @param type a value indicating how to calculate the entropy BYROW|BYCOL
 * @return the entropy
 */
float partition_entropy( Matrix* contingency_matrix, int nb_nodes, int type );

float edge_density( Graph* partition );

#endif
