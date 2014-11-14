#include "partitionsimilarity.h"

double calculate_ARI( Graph* partition_a, Graph* partition_b )
{
  assert( partition_a != 0 && partition_b != 0 );
  double ari = 0;
  Matrix* aff_mat_a = extract_affliation_matrix( partition_a );
  Matrix* aff_mat_b = extract_affliation_matrix( partition_b );
  Matrix* contingency_matrix = generate_contingency_matrix( aff_mat_a, aff_mat_b );
  Matrix* col_sum_mat = contingency_matrix->column_sum();
  Matrix* row_sum_mat = contingency_matrix->row_sum();
  float index = 0;
  for ( int i = 0; i < contingency_matrix->getNrows(); i ++ ) {
    for ( int j = 0; j < contingency_matrix->getNcols(); j++ ) {
      float val = contingency_matrix->getElement(i,j);
      index += val*(val - 1) / 2.0;
    }
  }
  float max_idx = ari_max_index(col_sum_mat, row_sum_mat );
  float expected_idx = ari_expected_index(col_sum_mat, row_sum_mat);
  delete col_sum_mat;
  delete row_sum_mat;
  delete contingency_matrix;
  delete aff_mat_a;
  delete aff_mat_b;
  ari = (index - expected_idx)/(max_idx - expected_idx );
  return fabs(ari);
}

double calculate_ARI( Matrix* partition_a, Graph* partition_b )
{
  assert( partition_a != 0 && partition_b != 0 );
  double ari = 0;
  Matrix* aff_mat_b = extract_affliation_matrix( partition_b );
  Matrix* contingency_matrix = generate_contingency_matrix( partition_a, aff_mat_b );
  Matrix* col_sum_mat = contingency_matrix->column_sum();
  Matrix* row_sum_mat = contingency_matrix->row_sum();
  float index = 0;
  for ( int i = 0; i < contingency_matrix->getNrows(); i ++ ) {
    for ( int j = 0; j < contingency_matrix->getNcols(); j++ ) {
      float val = contingency_matrix->getElement(i,j);
      index += val*(val - 1) / 2.0;
    }
  }
  float max_idx = ari_max_index(col_sum_mat, row_sum_mat );
  float expected_idx = ari_expected_index(col_sum_mat, row_sum_mat);
  delete col_sum_mat;
  delete row_sum_mat;
  delete contingency_matrix;
  delete aff_mat_b;
  ari = (index - expected_idx)/(max_idx - expected_idx );
  return fabs(ari);
}

double calculate_NMI( Graph* partition_a, Graph* partition_b )
{
  assert( partition_a != 0 && partition_b != 0 );
  double nmi = 0;
  double nb_nodes = partition_a->numberOfNodes();
  Matrix* aff_mat_a = extract_affliation_matrix( partition_a );
  Matrix* aff_mat_b = extract_affliation_matrix( partition_b );
  Matrix* contingency_matrix = generate_contingency_matrix( aff_mat_a, aff_mat_b );
  for( int i = 0; i < contingency_matrix->getNrows(); i++ )
  {
    double cluster_a_size = aff_mat_a->getElement( 1, i );
    for( int j = 0; j < contingency_matrix->getNcols(); j++ )
    {
      double intersection = contingency_matrix->getElement( i, j );
      double cluster_b_size = aff_mat_b->getElement( 1, j );
      nmi += cluster_a_size != 0 && cluster_b_size != 0 ? ( intersection / nb_nodes ) * log( nb_nodes*intersection/(cluster_a_size * cluster_b_size) ) : 0;
    }
  }
  nmi *= 2.0;
  //Now, calculate the entropy of each partition
  float partition_a_entropy = partition_entropy( contingency_matrix, (int)nb_nodes, BYROW );
  float partition_b_entropy = partition_entropy( contingency_matrix, (int)nb_nodes, BYCOL );
  nmi /= (partition_a_entropy+partition_b_entropy);
  
  delete contingency_matrix;
  delete aff_mat_a;
  delete aff_mat_b;
  return nmi;
}

float partition_entropy( Matrix* contingency_matrix, int nb_nodes, int type )
{
  float entropy = 0;
  Matrix* sum = 0;
  switch( type )
  {
    case BYROW:
    {
      sum = contingency_matrix->row_sum();
    }
    break;
    case BYCOL:
      sum = contingency_matrix->column_sum();
    break;
    default:
      sum = 0;
    break;
  }
  if( sum != 0 )
  {
    for( int i = 0; i < sum->getNcols(); i++ )
    {
      float part_size = sum->getElement( 0, i );
      if( part_size != 0.0 )
      {
        entropy += (part_size/(float)nb_nodes) * log(part_size/(float)nb_nodes);
      }
    }
    delete sum;
  }
  return -entropy;
}

Matrix* extract_affliation_matrix( Graph* partition )
{
  assert( partition->numberOfSubGraphs() > 0 );
  int columns = partition->numberOfSubGraphs();
  int rows = partition->numberOfNodes();
  Matrix* affiliation_matrix = new Matrix( rows, columns, COLUMN_MAJOR );
  affiliation_matrix->set_all_zeros();
  if( affiliation_matrix != 0 )
  {
    Iterator<Graph*> *group_iter = partition->getSubGraphs();
    int group_idx = 0;
    while( group_iter->hasNext() )
    {
      Graph* subg = group_iter->next();
      Iterator<node>* node_iter = subg->getNodes();
      while( node_iter->hasNext() )
      {
        node n = node_iter->next();
        affiliation_matrix->setElement( n.id, group_idx, 1.0 );
      }
      delete node_iter;
      group_idx++;
    }
    delete group_iter;
  }
  return affiliation_matrix;
}

Matrix* generate_contingency_matrix( Matrix* partition_a, Matrix* partition_b )
{
  assert( partition_a != 0 && partition_b != 0 );
  int m = partition_a->getNcols();
  int n = partition_b->getNcols();
  int k = partition_a->getNrows();
  partition_a->transpose();
  float* conf_mat = new float[ n*m ];
  mat_mult_float(m, n, k, partition_a->getPdmatrix(), partition_b->getPdmatrix(), conf_mat, 1, 0);
  Matrix* contingency_matrix = new Matrix( m, n, COLUMN_MAJOR, conf_mat );
  return contingency_matrix;
}

float ari_max_index( Matrix* col_sum, Matrix* row_sum ) 
{
    float row_index = 0;
    float col_index = 0;
    for ( int i = 0; i < col_sum->getNcols(); i++ ) 
    {
        float val = col_sum->getElement(0, i);
        col_index += val*(val-1)/2.0;
    }
    for ( int i = 0; i < row_sum->getNcols(); i++ ) 
    {
        float val = row_sum->getElement(0, i);
        row_index += val*(val-1)/2.0;
    }
    return 0.5*(row_index+col_index);
}

float ari_expected_index( Matrix* col_sum, Matrix* row_sum )
{
    float row_index = 0;
    float col_index = 0;
    float bin_coeff = 0;
    for ( int i = 0; i < col_sum->getNcols(); i++ ) 
    {
        float val = col_sum->getElement(0, i);
        col_index += val*(val-1)/2.0;
        bin_coeff += val;
    }
    for ( int i = 0; i < row_sum->getNcols(); i++ ) 
    {
        float val = row_sum->getElement(0, i);
        row_index += val*(val-1)/2.0;
    }
    bin_coeff *= ( bin_coeff-1 )/2.0;
    return row_index*col_index/bin_coeff;
}

float edge_density( Graph* partition )
{
    float density = 0.0;
    Iterator<Graph*>* subg_iter = partition->getSubGraphs();
    while( subg_iter->hasNext() )
    {
      Graph* subg = subg_iter->next();
      density += (float)subg->numberOfEdges()/(float)partition->numberOfEdges();
    }
    delete subg_iter;
    return density;
}
