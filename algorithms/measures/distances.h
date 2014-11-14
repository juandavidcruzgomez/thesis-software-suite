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
#ifndef DISTANCES_H
#define DISTANCES_H

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
