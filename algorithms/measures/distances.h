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
