/*
 *  CommunityAlgorithm.cpp
 *  CommunityDetectionV2
 *
 *  Created by Juan David CRUZ GOMEZ on 3/23/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#include "CommunityAlgorithm.h"

CommunityAlgorithm::CommunityAlgorithm( Matrix* _structural_partition, Matrix* _compositional_partition )
        : structural_partition(_structural_partition), compositional_partition(_compositional_partition)
{
    assert( structural_partition != 0 && compositional_partition != 0 );
    int m = structural_partition->getNcols();
    int n = compositional_partition->getNcols();
    structural_partition->transpose();
    contingency_matrix = new Matrix( m, n, COLUMN_MAJOR );
    structural_partition->matMult( compositional_partition, contingency_matrix, 1.0 );
    
}

CommunityAlgorithm::~CommunityAlgorithm() {
    if ( contingency_matrix != 0 ) {
        delete contingency_matrix;
        contingency_matrix = 0;
    }
}

void CommunityAlgorithm::calculate_proportion_matrix( Matrix* prop_mat ) {
    assert( prop_mat != 0 && contingency_matrix->getNcols() == prop_mat->getNcols() && contingency_matrix->getNrows() == prop_mat->getNrows() );
    float sum = matrix_elem_sum();
    for ( int i = 0; i < contingency_matrix->getNrows(); i++ ) {
        for ( int j = 0; j < contingency_matrix->getNcols(); j++ ) {
            float val = contingency_matrix->getElement(i, j) / sum;
            prop_mat->setElement(i, j, val);
        }
    }
}

void CommunityAlgorithm::marginal_masses_calculation( Matrix* proportion_mat, Matrix* row_mass, Matrix* column_mass ) {
    assert( proportion_mat != 0 && row_mass != 0 && column_mass != 0 );
    float row_val = 0;
    float col_val = 0;
    for ( int i = 0; i < proportion_mat->getNrows(); i++ ) {
        for ( int j = 0; j < proportion_mat->getNcols(); j++ ) {
            row_val += proportion_mat->getElement(i, j);
            col_val = proportion_mat->getElement(i, j) + column_mass->getElement(0, j);
            column_mass->setElement(0, j, col_val);
        }
        row_mass->setElement(0, i, row_val);
        row_val = 0;
    }
}

float CommunityAlgorithm::ari_index() {
    assert( contingency_matrix != 0 );
    Matrix* col_sum_mat = new Matrix( 1, contingency_matrix->getNcols(), COLUMN_MAJOR );
    Matrix* row_sum_mat = new Matrix( 1, contingency_matrix->getNrows(), COLUMN_MAJOR );
    float index = 0;
    for ( int i = 0; i < contingency_matrix->getNrows(); i ++ ) {
        for ( int j = 0; j < contingency_matrix->getNcols(); j++ ) {
            float val = contingency_matrix->getElement(i,j);
            index += val*(val - 1) / 2.0;
        }
    }
    column_sum(contingency_matrix, col_sum_mat);
    row_sum(contingency_matrix, row_sum_mat);
    float max_idx = max_index(col_sum_mat, row_sum_mat );
    float expected_idx = expected_index(col_sum_mat, row_sum_mat);
    delete col_sum_mat;
    delete row_sum_mat;
    return (index - expected_idx)/(max_idx - expected_idx );
}

void CommunityAlgorithm::column_sum( Matrix* origin, Matrix* col_sum ) {
    assert( origin != 0 && col_sum != 0 );
    for ( int i = 0; i < origin->getNcols(); i++ ) {
        float sum = 0;
        for ( int j = 0; j < origin->getNrows(); j++ ) {
            sum += origin->getElement(j, i);
        }
        col_sum->setElement(0, i, sum);
    }
}

void CommunityAlgorithm::row_sum( Matrix* origin, Matrix* row_sum ) {
    assert( origin != 0 && row_sum != 0 );
    for ( int i = 0; i < origin->getNrows(); i++ ) {
        float sum = 0;
        for ( int j = 0; j < origin->getNcols(); j++ ) {
            sum += origin->getElement(i, j);
        }
        row_sum->setElement(0, i, sum);
    }
}

float CommunityAlgorithm::max_index( Matrix* col_sum, Matrix* row_sum ) {
    float row_index = 0;
    float col_index = 0;
    for ( int i = 0; i < col_sum->getNcols(); i++ ) {
        float val = col_sum->getElement(0, i);
        col_index += val*(val-1)/2.0;
    }
    for ( int i = 0; i < row_sum->getNcols(); i++ ) {
        float val = row_sum->getElement(0, i);
        row_index += val*(val-1)/2.0;
    }
    return 0.5*(row_index+col_index);
}

float CommunityAlgorithm::expected_index( Matrix* col_sum, Matrix* row_sum ) {
    float row_index = 0;
    float col_index = 0;
    float bin_coeff = 0;
    for ( int i = 0; i < col_sum->getNcols(); i++ ) {
        float val = col_sum->getElement(0, i);
        col_index += val*(val-1)/2.0;
        bin_coeff += val;
    }
    for ( int i = 0; i < row_sum->getNcols(); i++ ) {
        float val = row_sum->getElement(0, i);
        row_index += val*(val-1)/2.0;
    }
    bin_coeff *= ( bin_coeff-1 )/2.0;
    return row_index*col_index/bin_coeff;
}

float CommunityAlgorithm::matrix_elem_sum() {
    assert( contingency_matrix != 0 );
    float result = 0;
    for ( int i = 0; i < contingency_matrix->getNrows(); i++ ) {
        for ( int j = 0; j < contingency_matrix->getNcols(); j++ ) {
            result += contingency_matrix->getElement(i, j);
        }
    }
    return result;
}

float CommunityAlgorithm::row_chi_square_dist( Matrix* prop_matrix, int rowa_idx, int rowb_idx ) {
    assert( prop_matrix != 0 && rowa_idx >= 0 && rowa_idx < prop_matrix->getNrows() && rowb_idx >= 0 && rowb_idx < prop_matrix->getNrows() );
    Matrix* col_sum = new Matrix( 1, prop_matrix->getNcols(), COLUMN_MAJOR );
    column_sum(prop_matrix, col_sum);
    //Sum of the elements of each row
    float sum_rowa = 0;
    float sum_rowb = 0;
    for ( int i = 0; i < prop_matrix->getNcols(); i++ ) {
        sum_rowa += prop_matrix->getElement(rowa_idx, i);
        sum_rowb += prop_matrix->getElement(rowb_idx, i);
    }
    //Squared differences by element
    float sum = 0;
    for ( int i = 0; i < prop_matrix->getNcols(); i++ ) {
        float vala = prop_matrix->getElement(rowa_idx, i)/sum_rowa;
        float valb = prop_matrix->getElement(rowb_idx, i)/sum_rowb;
        sum += (vala-valb)*(vala-valb)/col_sum->getElement(0, i);
    }
    delete col_sum;
    return sum;
}

float CommunityAlgorithm::euclideanDistance( int rowa_idx, int rowb_idx ) {
    assert( contingency_matrix != 0 && rowa_idx >= 0 && rowa_idx < contingency_matrix->getNrows() && rowb_idx >= 0 && rowb_idx < contingency_matrix->getNrows() );
    float dist = 0;
    for ( int i = 0; i < contingency_matrix->getNcols(); i++ ) {
        float sum = contingency_matrix->getElement(rowa_idx,i)- contingency_matrix->getElement(rowb_idx,i);
        dist += sum*sum;
    }
    return sqrt(dist);
}

float CommunityAlgorithm::pairMixedEntropy( int rowa_idx, int rowb_idx ) {
    assert( contingency_matrix != 0 && rowa_idx >= 0 && rowa_idx < contingency_matrix->getNrows() && rowb_idx >= 0 && rowb_idx < contingency_matrix->getNrows() );
    float entropy = 0;
    float* vector = new float[contingency_matrix->getNcols()];
    if ( vector != 0 ) {
        for ( int i = 0; i < contingency_matrix->getNcols(); i++ ) {
	  vector[i] = contingency_matrix->getElement(rowa_idx,i)+ contingency_matrix->getElement(rowb_idx,i);
        }
        float sum = escalarVectorSum(vector, contingency_matrix->getNcols());
	if( sum > 0 ){
	  float p = 0;
	  for ( int i = 0; i < contingency_matrix->getNcols(); i++ ) {
	    p = vector[i] / sum;
	      entropy += p==0 ? 0 : p*log(p)+ p==1 ? 0 : (1-p)*log(1-p);
	  }
	}
	delete[] vector;
    }
    return -entropy;
}

float CommunityAlgorithm::escalarVectorSum( float* vector, int size ) {
    assert( vector != 0 && size >= 0 );
    float result = 0;
    for ( int i = 0; i < size; ++i ) {
        result += vector[i];
    }
    return result;
}

std::map< int, int > CommunityAlgorithm::compressContingencyMatrix() {
  assert( contingency_matrix != 0 );
    map< int, int > result;
    vector<int> selected;
    for( int i = 0; i < contingency_matrix->getNrows(); i++ ){
      float row_ent = row_entropy( i );
      //If the entropy is 0, then look for other rows
      if( row_ent == 0 ){//&& find(selected.begin(),selected.end(),i)==selected.end()){
	//Get the non-zero index
	int index = get_first_non_zero(i);
	for( int j = i; j < contingency_matrix->getNrows(); j++ ){
	  if( i != j ){
	      float candidate_ent = row_entropy( j );
	      int cand_index = -1;
	      if( candidate_ent == 0 && (cand_index = get_first_non_zero( j )) == index ){
		//result[i].push_back(j);
		result[j] = i;
		fusion_row_groups( i, j );
	      }
	  }
	}
      }
    }
    return result;
}

void CommunityAlgorithm::fusion_row_groups( int groupa, int groupb ){
  assert( structural_partition != 0 && groupa >= 0 && groupa < structural_partition->getNrows() && groupb >= 0 && groupb < structural_partition->getNrows());
  for( int i = 0; i < structural_partition->getNcols(); i++ ){
    float element = structural_partition->getElement(groupb,i);
    if( element == 1 ){
      structural_partition->setElement( groupa, i, element );
      structural_partition->setElement( groupb, i, 0 );
    }
  }
}

int CommunityAlgorithm::get_first_non_zero( int row_idx ){
  assert( contingency_matrix != 0 && row_idx >= 0 && row_idx < contingency_matrix->getNrows() );
  int i = 0;
  while( i < contingency_matrix->getNcols() && contingency_matrix->getElement(row_idx,i) == 0 ){
    i++;
  }
  return i < contingency_matrix->getNcols() ? i : -1;
}

float CommunityAlgorithm::row_entropy( int row_idx ){
  assert( contingency_matrix != 0 && row_idx >= 0 && row_idx < contingency_matrix->getNrows() );
  float result = 0.0f;
  float sum = row_sum( row_idx );
  for( int i = 0; i < contingency_matrix->getNcols(); i++ ){
    float p = 0;
    float element = contingency_matrix->getElement(row_idx,i);
    if( sum != 0 ){
      p = element/sum;
    }
    if( p != 0 && p != 1 ){
      result += p*log( p ) + ( 1 - p )*log( 1 -p );
    }
  }
  return -result;
}

float CommunityAlgorithm::row_sum( int row_idx ){
  assert( contingency_matrix != 0 && row_idx >= 0 && row_idx < contingency_matrix->getNrows() );
  float result = 0;
  for( int i = 0; i < contingency_matrix->getNcols(); i++ ){
    result += contingency_matrix->getElement(row_idx,i);
  }
  return result;
}

vector<pair<int, vector<int> > > CommunityAlgorithm::process_matrix_row( int row_index ) {
    assert( contingency_matrix != 0 && row_index >= 0 && row_index < contingency_matrix->getNrows() );
    vector< pair<int, vector<int> > > result;
    //The original number of groups in the compositional partition
    int columns = contingency_matrix->getNcols();
    //The original number of groups in the structural partition
    //The new number of communities should be between n and n*m
    //where n is the number of structural groups and m is the
    //number of groups in the compositional partition
    int rows = contingency_matrix->getNrows();
    //In this version, i'll break all the groups containing more than
    //one compositional category
    //First: the column sum
    Matrix* rows_sum = new Matrix( 1, rows, COLUMN_MAJOR );
    row_sum(contingency_matrix, rows_sum );
    int j = 0;
    int count = 0;
    float cumulated = 0;
    float delta = 0;
    do {
        vector<int> compositional_list;
        delta = contingency_matrix->getElement(row_index, j)/rows_sum->getElement(0, row_index);
        cumulated += delta;
        if ( delta > 0 ) {
            compositional_list.push_back( j );
            count++;
        }
        if ( compositional_list.size() > 0 ) {
            result.push_back( pair<int, vector<int> >(row_index, compositional_list ) );
        }
        j++;
    } while ( j < columns && cumulated < 1 );
    delete rows_sum;
    return result;
}

vector<pair<int, vector<int> > > CommunityAlgorithm::process_matrix_row_deviation( int row_index ) {
    assert( contingency_matrix != 0 && row_index >= 0 && row_index < contingency_matrix->getNrows() );
    vector< pair<int, vector<int> > > result;
    //Modification
    int rows = contingency_matrix->getNrows();
    Matrix* rows_sum = new Matrix( 1, rows, COLUMN_MAJOR );
    row_sum(contingency_matrix, rows_sum );
    //The original number of groups in the compositional partition
    int columns = contingency_matrix->getNcols();
    //Calculate the average of the row
    float average = 0;
    float non_zero_count = 0;
    for ( int i = 0; i < columns; i++ ) {
        average += contingency_matrix->getElement(row_index, i);
        non_zero_count += contingency_matrix->getElement(row_index, i) > 0 ? 1 : 0;
    }
    average /= non_zero_count;
    //Claculate the standard deviation
    float stddev = 0;
    for ( int i = 0; i < columns; i++ ) {
        float x = contingency_matrix->getElement(row_index, i);
        stddev += (x - average)*(x - average);
    }
    stddev /= non_zero_count;
    stddev = sqrt( stddev );
    //Go through the row looking for the rows >= 1\sigma
    vector<int> non_modified_list;
    for ( int i = 0; i < columns; i++ ) {
        vector<int> compositional_list;
        float variance = ( contingency_matrix->getElement(row_index, i) - average ) / stddev;
        if ( variance >= 1.0 && non_zero_row_count( row_index ) > 1 ) {
            compositional_list.push_back( i );
        } else {
            non_modified_list.push_back( i );
        }
        if ( compositional_list.size() > 0 ) {
            result.push_back( pair<int, vector<int> >(row_index, compositional_list ) );
        }
    }
    result.push_back( pair<int, vector<int> >(row_index, non_modified_list ) );
    return result;
}

int CommunityAlgorithm::non_zero_row_count( int row_idx ){
  assert( contingency_matrix != 0 && row_idx >= 0 && row_idx < contingency_matrix->getNrows() );
  int result = 0;
  for( int i = 0; i < contingency_matrix->getNcols(); i++ ){
    if( contingency_matrix->getElement(row_idx,i) > 0 ){
      result++;
    }
  }
  return result;
}

vector<pair<int, vector<int> > > CommunityAlgorithm::process_matrix_row_chi( int row_index ) {
    assert( contingency_matrix != 0 && row_index >= 0 && row_index < contingency_matrix->getNrows() );
    vector< pair<int, vector<int> > > result;
    return result;
}

Matrix* CommunityAlgorithm::generate_new_partition( int type ) {
    Matrix* result = 0;
    int new_cols = 0;
    vector<vector<pair<int, vector<int> > > > configuration;
    for ( int i = 0; i < contingency_matrix->getNrows(); i++ ) {
        vector<pair<int, vector<int> > > conf;
        switch ( type ) {
        case NAIVE_PARTITIONING:
            conf = process_matrix_row( i );
            break;
        case VARIA_PARTITIONING:
            conf = process_matrix_row_deviation(i);
            break;
        case CHISQ_PARTITIONING:
            conf = process_matrix_row_chi( i );
            break;
        default:
            conf = process_matrix_row( i );
            break;
        }
        new_cols += (int)conf.size();
        configuration.push_back( conf );
    }
    cout << "Number of new communities: " << new_cols << endl;
    //A map of vectors containing the indices of the final groups to be joined
    map<int,int > compression_indices = compressContingencyMatrix();
    map<int,int >::iterator comp_iter;
    
    result = new Matrix( structural_partition->getNcols(), new_cols, COLUMN_MAJOR );
    result->set_all_values(0);
    int new_partition_index = 0;
    for ( int i = 0; i < (int)configuration.size(); i++ ) {
        vector<pair<int, vector<int> > > groups = configuration[i];
        for ( int j = 0; j < (int)groups.size(); j++ ) {
            pair<int, vector<int> > group = groups[j];
            //Group index in the original structural partition
            int original_row_index = group.first;	    
            //For each compositional group
            for ( int k = 0; k < (int)group.second.size(); k++ ) {
                int comp_index = group.second[k];
                //For each node, if belongs to group original_row_index and comp_index
                for ( int node = 0; node < structural_partition->getNcols(); node++ ) {
                    int value = 0; //Si el nodo no fue marcado ya...
                    if ( structural_partition->getElement(original_row_index, node) == 1 &&
                            compositional_partition->getElement(node, comp_index) == 1 ) {
                        value = 1;
                        result->setElement(node, new_partition_index, value);
                    }
                }
            }
            new_partition_index++;
        }
    }
    remove_size0_comm( result );
    return result;
}

void CommunityAlgorithm::remove_size0_comm( Matrix* result ){
  assert( result != 0 );
  Matrix* col_sum = new Matrix( 1, result->getNcols(), COLUMN_MAJOR );
  column_sum( result, col_sum );
  //col_sum->printMatrix();
  int count = 0;
  for( int i = 0; i < col_sum->getNcols()-count-1; i++ ){
      if( col_sum->getElement(0,i) == 0 ){
	count++;
	result->shift_left(i);
	column_sum( result, col_sum );
	//col_sum->printMatrix();
	i--;
      }
  }
  result->remove_tail_col(count);
  cout << "Zero size comm " << count+1 << endl;
  delete col_sum;
}

Matrix* CommunityAlgorithm::getContingencyMatrix() const {
    return contingency_matrix;
}

float CommunityAlgorithm::calculate_total_entropy(){
  assert( contingency_matrix != 0 );
  float result = 0;
  for( int i = 0; i < contingency_matrix->getNrows(); i ++ ){
    result += row_entropy(i);
  }
  return result;
  
}
