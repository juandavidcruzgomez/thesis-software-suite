/**
 The MIT License (MIT)

 Copyright (c) 2013 Juan David Cruz Gómez and Telecom - Bretagne 
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

#ifndef __COMMUNITY_ALGORITHM_H__
#define __COMMUNITY_ALGORITHM_H__

#include <vector>
#include <map>
#include <algorithm>

#include <matrix.h>
#include <basicoperations.h>

#define NAIVE_PARTITIONING 0
#define VARIA_PARTITIONING 1
#define CHISQ_PARTITIONING 2

#define ROW_SEARCH 0 //Look into the groups on the rows
#define COL_SEARCH 1 //Look into the groups on the columns

using namespace std; 

/**
 * This class will find communities by manipilating the contingency matrix
 * and by generating a new partition of the graph.
 */
class CommunityAlgorithm{
public:
	/**
	 * Constructor.
	 * @param _contingency_mtrix a reference to the original contingency matrix
	 */
	CommunityAlgorithm( Matrix* _structural_partition, Matrix* _compositional_partition );
	/**
	 * Destructor
	 */
	virtual ~CommunityAlgorithm();
	/**
	 * This method will calculate the proportion matrix used for Correspondance analysis
	 * @param prop_mat the matrix where the result will be stored
	 */
	void calculate_proportion_matrix( Matrix* prop_mat );
	/**
	 * Calculates the adjusted rand index from the contingency matrix
	 */
	float ari_index();
	/**
	 * Calculates the by column sum.
	 * @param origin the matrix where the sum will be calculated
	 * @param col_sum a row vector to store the result. 
	 */
	void column_sum( Matrix* origin, Matrix* col_sum );
	/**
	 * Calculates the by row sum of the columns.
	 * @param origin the matrix where the sum will be calculated
	 * @param row_sum a column (transposed) vector to store the result. 
	 */
	void row_sum( Matrix* origin, Matrix* row_sum );
	/**
	 * Calculates the marginal porportions of rows and columns
	 * @param proportion_mat the proportion matrix
	 * @param row_mass the (transposed) column vector to store the row masses. 
	 * @param column_mass the row vector to store the column masses.
	 */
	void marginal_masses_calculation( Matrix* proportion_mat, Matrix* row_mass, Matrix* column_mass );
	/**
	 * Finds candidates to rows to be joined. These rows will be composed of possibly disconnected
	 * nodes of the same composition category.
	 * @return a map of vectors containing the indices of the candidates. Each entry of the map 
	 * is a different set of indices, i.e., each entry has to be used separatedly
	 */
	std::map< int, int > compressContingencyMatrix();
	/**
	 * Produces a new partition based on the original partitions and the division of the contingency
	 * matrix.
	 * @param structural_parition the original structural partition of the graph
	 * @param compositional_partition the original compositional partition of the graph
	 * @param type the tipe of partitoning used: NAIVE, VARIANCE or CHI Sq
	 * @return the new partition (binary) matrix of the graph
	 */
	Matrix* generate_new_partition( int type );
	/**
	 * Calculates the chi square distance between two rows.
	 * @param rowa_idx the index of the first row
	 * @param rowb_idx the index of the second row
	 * @return the distance between rows.
	 */
	float row_chi_square_dist( Matrix* prop_matrix, int rowa_idx, int rowb_idx );
	/**
	 * Returns the contingency matrix
	 */
	Matrix* getContingencyMatrix() const;
	/**
	 * Calculates the overall entropy of the contigency matrix. In this case the 
	 * the row are assumed to contain the structural partition and the columns, the 
	 * composition partition
	 * @return overal structural entropy
	 */
	float calculate_total_entropy();
private:
	/**
	 * Calculates the maximum index (for the ARI index) of a contingency matrix
	 */
	float max_index( Matrix* col_sum, Matrix* row_sum );
	/**
	 * Calculates the expected index (for the ARI index) of a contingency matrix
	 */
	float expected_index( Matrix* col_sum, Matrix* row_sum );
	/**
	 * Sums all the elements of the matrix
	 */
	float matrix_elem_sum();
	/**
	 * Process one row of the contingency matrix to find a new configuration of the
	 * structural community.
	 * @param row_index the number of the community to be analyzed
	 * @return a list with the new configuration of the community. Each element is a pair whose 
	 * first element is the subcommunity index and the second is a list of the compositional 
	 * communities composing it.
	 */
	vector<pair<int, vector<int> > > process_matrix_row( int row_index );
	/**
	 * Process one row of the contigency matrix to find a new configuration of the 
	 * structural community. This is done by using the Chi-square distance.
	 * @param row_index the number of the community to be analyzed
	 * @return a list with the new configuration of the community. Each element is a pair whose 
	 * first element is the subcommunity index and the second is a list of the compositional 
	 * communities composing it.
	 */
	vector<pair<int, vector<int> > > process_matrix_row_chi( int row_index );
	/**
	 * Process one row of the contigency matrix to find a new configuration of the 
	 * structural community. This is done by using the variance of the composition group
	 * within the structural community.
	 * @param row_index the number of the community to be analyzed
	 * @return a list with the new configuration of the community. Each element is a pair whose 
	 * first element is the subcommunity index and the second is a list of the compositional 
	 * communities composing it.
	 */
	vector<pair<int, vector<int> > > process_matrix_row_deviation( int row_index );
	/**
	 * Calculates the Euclidean distance between two rows of the matrix
	 * @param rowa_idx the index of the first row
	 * @param rowb_idx the index of the second row
	 */
	float euclideanDistance( int rowa_idx, int rowb_idx );
	/**
	 * Calculates the resulting entropy of joining two rows of the contigency matrix
	 * @param rowa_idx the index of the first row
	 * @param rowb_idx the index of the second row
	 */
	float pairMixedEntropy( int rowa_idx, int rowb_idx );
	/**
	 * Calculates the sum of the elements of a vector
	 * @param vector the vector to be sum
	 * @param size the size of vector
	 * @return the sum of the elements of the vector
	 */
	float escalarVectorSum( float* vector, int size );
	/**
	 * Calculates the entropy of a row
	 * @param row_idx the index of the row
	 * @return the entropy of the row
	 */
	float row_entropy( int row_idx );
	/**
	 * Calculates the sul of the elements of one row
	 * @param row_idx the index of the row
	 * @return the sum of the elements of the row
	 */
	float row_sum( int row_idx );
	/**
	 * Returns the index of the first non-zero element of a row
	 * @param row_idx the index of the row
	 * @return the index. -1 if all the elements are 0
	 */
	int get_first_non_zero( int row_idx );
	/**
	 * Join two groups: group b into group b
	 */
	void fusion_row_groups( int groupa, int groupb );
	/**
	 * Remove all the communities of size 0
	 */
	void remove_size0_comm( Matrix* result );
	
	int non_zero_row_count( int row_idx );
	
	
private:
	Matrix* contingency_matrix;
	Matrix* structural_partition;
	Matrix* compositional_partition;
	
};

#endif
