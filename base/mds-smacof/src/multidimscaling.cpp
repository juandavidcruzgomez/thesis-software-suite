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


#include "multidimscaling.h"

MDS_space::MDS_space() {
  n_points = 0;
  n_points_max_ret = 0;
  dissimilarity_matrix = NULL;
  z_matrix = NULL;
  b_matrix = NULL;
  distances_matrix = NULL;
  dist = 0;
}

MDS_space::MDS_space(int _n_points, Matrix* &_dissimilarity_matrix, int dist_type) {
  n_points = _n_points;
  n_points_max_ret = _n_points;
  dissimilarity_matrix = _dissimilarity_matrix;
  z_matrix = new Matrix(n_points, DIMENSIONS, dissimilarity_matrix->getNtype() );
  b_matrix = new Matrix(n_points, n_points, dissimilarity_matrix->getNtype());
  distances_matrix = new Matrix(n_points, n_points, dissimilarity_matrix->getNtype());
  dist = DistanceFactory::buildDistanceCalculator( dist_type );
}

MDS_space::MDS_space(const MDS_space& other) {
  n_points = other.getPoints();
  if (dissimilarity_matrix != NULL) {
    delete dissimilarity_matrix;
    dissimilarity_matrix = NULL;
  }
  dissimilarity_matrix = other.getDissimilarity_matrix();
  if (b_matrix != NULL) {
    delete b_matrix;
    b_matrix = NULL;
  }
  b_matrix = other.get_b_matrix();
  if (z_matrix != NULL) {
    delete z_matrix;
    z_matrix = NULL;
  }
  z_matrix = other.get_z_matrix();
  if (distances_matrix != NULL) {
    delete distances_matrix;
    distances_matrix = NULL;
  }
  distances_matrix = other.getDistances_matrix();
  dist = DistanceFactory::buildDistanceCalculator(EUCLIDEAN);
}

void MDS_space::recycle_mds_space( int _n_points ) {
  if ( _n_points <= n_points ) {
    n_points_max_ret = _n_points;
    z_matrix->recycleMatrixSpace(n_points_max_ret, DIMENSIONS);
    b_matrix->recycleMatrixSpace(n_points_max_ret,n_points_max_ret);
    distances_matrix->recycleMatrixSpace(n_points_max_ret,n_points_max_ret);
  }
}

MDS_space::~MDS_space() {
  if (b_matrix != NULL) {
    delete b_matrix;
    b_matrix = NULL;
  }
  if (z_matrix != NULL) {
    delete z_matrix;
    z_matrix = NULL;
  }
  if (distances_matrix != NULL) {
    delete distances_matrix;
    distances_matrix = NULL;
  }
  if( dist != 0 )
  {
    delete dist;
    dist = 0;
  }
}

void MDS_space::initialize_mds() {
  
}

void MDS_space::start_mds(int max_iter, double epsilon) {
  clock_t init_time = clock();
  double stress = calculate_distances_matrix();
  double prev_stress = 1.0;
  double delta_stress = 0.0;
  int k = 0;
  cout << "Information for the " << n_points_max_ret << " set" << endl;
  do {
    //cout << k << "\t" << stress << endl;
    prev_stress = stress;
    k++;
    stress = calculate_guttman_transform();
    //delta_stress = k == 1 ? stress : prev_stress - stress;
    //cout << "Iteration: " << k << "\nStress: " << stress << "\tPrevious stress: " << prev_stress << endl;
    
    //delta_stress = k == 1 ? 1.0 : 1.0 - (  stress/prev_stress );
    delta_stress = prev_stress - stress;
    //cout << delta_stress << "\t";
  } while (delta_stress > epsilon && stress > 0 && k < max_iter );//(int)min( max_iter, MAXITERATIONS ) );
  printf("MDS for %d points took %3.4f seconds and %d iterations. Final delta: %2.8f.\n", n_points_max_ret, (((float)clock() - init_time)/CLOCKS_PER_SEC), k, delta_stress);
  cout << "--------------------------------------------------------------------" << endl;
}

void MDS_space::calculate_initial_points() {
  int i;
  double theta_step = PI / (double) n_points_max_ret;
  double theta = 0.0;
  for (i = 0; i < n_points_max_ret; i++) {
    z_matrix->setElement(i, 0, cos(theta));
    z_matrix->setElement(i, 1, sin(theta));
    theta += theta_step;
  }
  calculate_distances_matrix();
  calculate_b_matrix();
}

double MDS_space::calculate_distances_matrix() {
  int i, j;
  double stress = 0;
  double difference = 0;
  double value = 0;
  t_point pt1(NULL, DIMENSIONS);
  t_point pt2(NULL, DIMENSIONS);
  for (i = 0; i < n_points_max_ret; i++) {
    for (j = i; j < n_points_max_ret; j++) {
      if (i == j) {
        value = 0;
      } else {
        int c = 0;
        while( c < DIMENSIONS )
        {
          pt1.data[c] = z_matrix->getElement(i, c);
          pt2.data[c] = z_matrix->getElement(j, c);
          c++;
        }
        value += dist->getDistance( pt1, pt2 );
      }
      distances_matrix->setElement(i, j, value);
      distances_matrix->setElement(j, i, value);
      difference = distances_matrix->getElement(i, j) - dissimilarity_matrix->getElement(i, j);//getDissimilarityValue(i, j);
      stress += 4.0*difference*difference;
      value = 0;
    }
  }
  return n_points_max_ret == 0 ? 10000000 : stress / (double) n_points_max_ret;
}

double MDS_space::getDissimilarityValue( int i, int j ) {
  return dissimilarity_matrix->getElement(i, j);
}

void MDS_space::calculate_b_matrix() {
  double val = 0.0;
  double diagonal = 0.0;
  int i, j;
  for (i = 0; i < n_points_max_ret; i++) {
    for (j = 0; j < n_points_max_ret; j++) {
      if (i != j) {
        val = 0;
        if ( distances_matrix->getElement(i, j) != 0 ) {
          val = -(dissimilarity_matrix->getElement(i, j) / distances_matrix->getElement(i, j));
        }
        diagonal += val;
      }
      b_matrix->setElement(i, j, val);
    }
    b_matrix->setElement(i, i, -diagonal);
    diagonal = 0.0;
  }
}

double MDS_space::calculate_guttman_transform() {
  double stress = 0;
  float alpha = 1.0 / n_points_max_ret;
  if (n_points_max_ret > 2) {
    b_matrix->matMult(z_matrix,z_matrix, alpha);
  } else if (n_points_max_ret == 2) {
    double dist = n_points_max_ret == 2 ? dissimilarity_matrix->getElement(0, 1) : 0;
    z_matrix->setElement(0, 0, -dist / 2.0);
    z_matrix->setElement(0, 1, 0);
    z_matrix->setElement(1, 0, dist / 2.0);
    z_matrix->setElement(1, 1, 0);
  } else {
    z_matrix->setElement(0, 0, 0);
    z_matrix->setElement(0, 1, 0);
  }
  stress = calculate_distances_matrix();
  calculate_b_matrix();
  return stress;
}

void MDS_space::setInitial_points(Matrix* _initial_points) {
  if (z_matrix != NULL) {
    delete z_matrix;
    z_matrix = NULL;
  }
  z_matrix = _initial_points;
}

Matrix* MDS_space::getDissimilarity_matrix() const {
  return dissimilarity_matrix;
}

Matrix* MDS_space::getDistances_matrix() const {
  return distances_matrix;
}

int MDS_space::getPoints() const {
  return n_points;
}

long MDS_space::getSize() {
  long size = 0;
  size = dissimilarity_matrix->getSize()+distances_matrix->getSize()+b_matrix->getSize()+z_matrix->getSize();
  return size;
}
