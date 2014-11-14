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
#ifndef POVCLUSTERING_H
#define POVCLUSTERING_H

#include <string>
#include <iostream>

#include <tulip/IntegerProperty.h>

#include "clusteringbase.h"
#include "somclusteringspace.h"
#include "louvain.h"
#include <matrix.h>

using namespace std;
using namespace tlp;

class PoVClustering : public ClusteringBase{
public:
  /**
   * Constructor
   * @param pgraph a pointer to the graph
   * @param iterations the number of iterations for the algorithm
   * @param min_delta the minimum error for stopping the algorithm
   * @param partition_name_prefix the prefix for naming the groups in the 
   * partition. It is something like 'prefix'_i where i is the index of the ith
   * group
   * @parm pattern_property_name the name of the property containing the pattern
   * (for the SOM algorithm) of the node
   */
  PoVClustering( Graph* pgraph, int iterations, float min_delta, string partition_name_prefix, string pattern_property_name );
  /**
   * Destructor
   */
  ~PoVClustering();
  /**
   * Executes the algorithm
   */
  void execute_algorithm();
  /**
   * Builds and returns the affiliation matrix of the partition calculated with
   * the SOM algorithm
   */
  Matrix* getSOMAffiliationMatrix();
  
  float getModularity() const;
  
private:
  /**
   * Executes the SOM algorithm
   */
  void execute_som_clustering();
  
private:
  string pattern_property_name;
  SOMClusteringSpace* som_space;
  float modularity;
};

#endif
