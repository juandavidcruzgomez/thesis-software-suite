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
