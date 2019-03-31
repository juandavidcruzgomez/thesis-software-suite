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
#ifndef BASICENTROPY_H
#define BASICENTROPY_H

#include <math.h>

#include <tulip/Graph.h>
#include <tulip/DoubleProperty.h>

#include "distances.h"

using namespace tlp;
using namespace std;

class BasicEntropy
{
public:
  /**
   * Constructor
   * @param pgraph a pointer to the target graph
   * @param pattern_property_name the name of the property storing the pattern
   */
  BasicEntropy( Graph* pgraph, string pattern_property_name );
  /**
   * Destructor
   */
  ~BasicEntropy();
  /**
   * Calculates the entropy of the whole partition
   * @return the entropy
   */
  double calculatePartitionEntropy();
  
protected:
  /**
   * Calculates the entropy of one group of the partition
   * @param group the group to measure
   * @return the entropy of the group
   */
  double calculateGroupEntropy( Graph* group, int pattern_size );
  /**
   * Calculates the similarity between two vectors
   * @param vec_a the first vector
   * @param vec_b the second vector
   * @param max_values a vector containing the maximum values for each value
   * @return the similarity of the vectors
   */
  double pair_similarity( vector<double> vec_a, vector<double> vec_b, vector<double>& max_values );
  
  double pair_entropy( vector<double> vec_a, vector<double> vec_b );
  /**
   * Calculates the max (min) values used for normalizing the distance measure on each dimension
   * @param group the group to be analized
   */
  vector<double> calculate_normalization_values( Graph* group );

private:
  Graph* pgraph;
  DoubleVectorProperty* patterns;
  string pattern_property_name;
};

#endif
