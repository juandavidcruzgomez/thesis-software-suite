#include <iostream>
#include <vector>
#include "multidimscaling.h"
#include "util.h"
#include "distance.h"

int main( int argc, char** argv )
{
  //int _n_points, Matrix* &_dissimilarity_matrix, int dist_type
  std::vector<t_point*> point_set;
  /////////////////Example points///////////////////
  float data[23][5] = { {0.97,0.36,0.42,48.00,410.00},
    {1.24,	0.68,	0.38,	51.00,	4060.00},
    {1.18,	0.30,	0.80,	76.00,	9740.00},
    {1.14,	0.05,	1.00,	75.00,	15320.00},
    {1.05,	0.02,	1.00,	82.00,	46200.00},
    {0.99,	0.02,	1.00,	80.00,	48300.00},
    {1.05,	0.02,	1.00,	80.00,	46160.00},
    {1.05,	0.60,	0.71,	67.00,	2040.00},
    {1.37,	0.21,	0.85,	73.00,	10720.00},
    {1.03,	0.11,	1.00,	74.00,	6550.00},
    {1.06,	0.15,	0.75,	79.00,	12280.00},
    {1.11,	0.03,	0.85,	73.00,	4940.00},
    {1.15,	0.37,	0.72,	74.00,	6110.00},
    {1.08,	0.31,	0.65,	74.00,	5500.00},
    {1.14,	0.51,	0.91,	77.00,	9240.00},
    {1.03,	0.29,	0.75,	74.00,	11920.00},
    {1.13,	0.19,	1.00,	76.00,	11860.00},
    {1.00,	0.21,	0.99,	80.00,	25030.00},
    {0.99,	0.11,	0.92,	69.00,	10400.00},
    {1.03,	0.02,	1.00,	83.00,	45180.00},
    {1.18,	0.46,	0.68,	74.00,	1170.00},
    {0.99,	0.02,	0.99,	81.00,	45560.00},
    {1.02,	0.02,	0.94,	78.00,	48450.00}};
  for( int i = 0; i < 23; ++i )
  {
    point_set.push_back( new t_point( data[i], 5 ) );
  }
  Matrix* dissimilarity_matrix = createDissimilarityMatrix( point_set, EUCLIDEAN );
  dissimilarity_matrix->printMatrix();
  MDS_space* mds = new MDS_space( point_set.size(), dissimilarity_matrix, EUCLIDEAN );
  mds->calculate_initial_points();
  mds->start_mds(1000, 1E-6);
  mds->get_z_matrix()->printMatrix();
  delete dissimilarity_matrix;
  delete mds;
  return EXIT_SUCCESS;
}
