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
