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
#ifndef CLUSTERINGBASE_H
#define CLUSTERINGBASE_H


#include <string>

#include <tulip/Graph.h>

using namespace tlp;
using namespace std;

class ClusteringBase{
public:
  /**
   * Constructor
   * @param pgraph a pointer to the target graph
   * @param iterations the maximum number of iterations for the algorithm
   * @param min_delta the minimum error to stop the algorithm
   * @param partition_name_prefix the prefix for naming the groups
   */
  ClusteringBase( Graph* pgraph, int iterations, float min_delta, string partition_name_prefix );
  /**
   * Destructor
   */
  virtual ~ClusteringBase();
  /**
   * Call the actual algorithm
   */
  virtual void execute_algorithm() =0;
  
protected:
  /**
   * This function takes each group in the partition and add the inner edges from
   * the root graph
   */
  void assignEdgesToGroups();

protected:
  /**
   * A pointer to the target (original) graph
   */
  Graph* pgraph;
  /**
   * The maximum number of iterations for the algorithm
   */
  int iterations;
  /**
   * Minimum error for stopping the algorithm
   */
  float min_delta;
  /**
   * The prefix for naming the groups in the partition
   */
  string partition_name_prefix;

};

#endif
