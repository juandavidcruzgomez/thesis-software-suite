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


#ifndef MULTIDIMSCALING_H
#define MULTIDIMSCALING_H

#define DIMENSIONS 2
#define PI 3.141592654
#define MAXITERATIONS 750

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include <matrix.h>
#include "distance_factory.h"

class MDS_space {
public:
  MDS_space();
  MDS_space(int _n_points, Matrix* &_dissimilarity_matrix, int dist_type);
  MDS_space(const MDS_space& other);
  
  ~MDS_space();
  void initialize_mds();
  void start_mds(int max_iter, double epsilon);
  void calculate_initial_points();
	/**
	 * This method is called to recycle the MDS space. The idea is to use an existing space 
	 * that is already in memory and have returned the final set of coordinates. The programmer
	 * MUST be aware of the maximum size of the space to avoid overflows.
	 * Since at construction time MDS_space receives a pointer to the dissimilarity matrix
	 * it shouldn't be changed (in theory the pointer remains active), although the three internal
	 * matrices have to be recycled.
	 */
	void recycle_mds_space( int _n_points );
  /**
   * TODO: devolver a los m�todos privados
   */
  void calculate_b_matrix();
  /**
   * TODO: devolver a los m�todos privados
   */
  double calculate_distances_matrix();
  
  void setInitial_points(Matrix* _initial_points);
  
  //double calculate_stress();
  
  double calculate_guttman_transform();
  
  double getDissimilarityValue( int i, int j );
  
  //Getters and setters
  Matrix *getDissimilarity_matrix() const;
  
  Matrix *getDistances_matrix() const;
  
  int getPoints() const;
  
  inline Matrix* get_b_matrix() const {
    return b_matrix;
  }
  
  inline Matrix* get_z_matrix() const {
    return z_matrix;
  }
  /**
   * Returns the size in bytes of the space
   */
  long getSize();
  
private:
	/**
	 * As in matrix, this is maximum number of points when the space is constructed.
	 * This number should not be changed in execution time, the programmer has to know
	 * in advance this number.
	 */
  int n_points;
	/**
	 * This is the ACTUAL number of points being used during the mds. At construction time
	 * this number is equals to n_points. It can be changed in recycling though.
	 */
	int n_points_max_ret;
  Matrix* dissimilarity_matrix;
  Matrix* distances_matrix;
  Matrix* z_matrix;
  Matrix* b_matrix;
  /**
   * For the distance implementation
   */
  Distance* dist;
  
};

#endif // MULTIDIMSCALING_H
