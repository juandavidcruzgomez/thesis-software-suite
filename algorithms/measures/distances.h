#ifndef __DISTANCES_H__
#define __DISTANCES_H__

#include <vector>
#include <math.h>

  /**
   * Calculates the Euclidean distance of two vectors
   * @param vec_a the first vector
   * @param vec_b the second vector
   * @return the distance
   */
  double euclidean_distance( std::vector<double>& vec_a, std::vector<double>& vec_b );
  /**
   * Calculates the cosine distance between two vectors
   * @param vec_a the first vector
   * @param vec_b the second vector
   * @return the distance
   */
  double cosine_distance( std::vector<double>& vec_a, std::vector<double>& vec_b );
  /**
   * Calculates the inner product of two vectors
   * @param vec_a the first vector
   * @param vec_b the second vector
   * @return the dot (inner) product   
   */
  double inner_product( std::vector<double>& vec_a, std::vector<double>& vec_b );
  /**
   * Calculates the norm of a vector.
   */
  double norm( std::vector<double>& vec_a );

#endif
