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
#ifndef __GENERALKMEANS_H__
#define __GENERALKMEANS_H__

#include <sstream>

#include "tableclustering.h"
#include "utility.h"

class GeneralKMeans : public TableClustering
{
public:
  GeneralKMeans( Graph* pgraph, int iterations, float min_delta, string partition_name_prefix, string pattern_property_name, int target_k );
  ~GeneralKMeans();
  
  void execute_algorithm();
  
  /**
   * Tries to calculate the best number of groups to be used
   * @return the best number of groups
   */
  int identify_groups_number();
  /**
   * Sets the value of k TODO this method should not exist...
   */
  void set_k( int k );
  
protected:
  /**
   * Selects k centroids from the patterns. In this case the patterns are
   * stored as a property of the nodes of the graph. That is why the function
   * will return a vector with the selected nodes.
   */
  vector<vector<double> > select_k_centroids( int k );
  
  bool isStable( vector<node>& centroids, vector<node>& candidate_centroids );
  
  bool isStable( vector<vector<double> >& centroids, vector<vector<double> >& candidate_centroids );
  /**
   * Returns the node of the graph with the closest pattern to the given cetroid
   * @return the closest node
   */
  node getClosestNode( vector<double>& centroid );
  /**
   * Determines whether the vectors are equal or not
   */
  bool equalVectors( vector<double>& vec_a, vector<double>& vec_b );
  /**
   * Performs the k-means algorithm in its basic form
   * @return the mean error
   */
  double _basic_kmeans_algorithm( int k );
  
private:
  int target_k;
  
  vector<node> selected;

};

#endif
