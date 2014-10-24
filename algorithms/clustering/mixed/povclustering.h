#ifndef __POVCLUSTERING_H__
#define __POVCLUSTERING_H__

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
