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
