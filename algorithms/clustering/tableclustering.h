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
#ifndef TABLECLUSTERING_H
#define TABLECLUSTERING_H

#include "clusteringbase.h"
#include "distances.h"

#include <string>
#include <vector>
#include <math.h>
#include <cstdlib>

#include <tulip/Graph.h>
#include <tulip/DoubleProperty.h>

using namespace tlp;
using namespace std;

class TableClustering : public ClusteringBase{
public:
  TableClustering( Graph* pgraph, int iterations, float min_delta, string partition_name_prefix, string pattern_property_name );
  virtual ~TableClustering();
  
protected:
  void remove_sub_graphs();
  /**
   * Calculates the mean squared distance of the partition. This means the mean
   * distance of the nodes to the centroid of the group to they belong.
   * @param groups a map containing the centroid as the key and the respective
   * subgroup
   * @return the squqred mean distance
   */
  double squared_mean_distance( map<node, Graph*> & groups );
  
  double squared_mean_distance( map<int, Graph*> & groups );
  /**
   * Calculates the centroid of the given group
   * @param group the group to be evaluated
   * @return the vector containing the cetroid of the group
   */
  vector<double> getGroupCentroid( Graph* group );
  
protected:
  /**
   * The name of the property where the pattern for each node is stored
   */
  string pattern_property_name;
  /**
   *
   */
  DoubleVectorProperty* patterns;
  
};

#endif
