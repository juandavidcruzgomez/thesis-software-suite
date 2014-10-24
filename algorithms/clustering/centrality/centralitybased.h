#ifndef __CENTRALITYBASED_H__
#define __CENTRALITYBASED_H__

#define PAGERANK  0
#define HITSRANK  1
#define CLOSENESS 2

#include "clusteringbase.h"
#include "pagerank.h"

#include <math.h>
#include <vector>
#include <map>
#include <string>

#include <tulip/Graph.h>
#include <tulip/DoubleProperty.h>


using namespace tlp;
using namespace std;

class CentralityBased : public ClusteringBase{
public:
  CentralityBased( Graph* pgraph, int iterations, float min_delta, string partition_name_prefix, int measure_type, int target_k );
  ~CentralityBased();
  
  void execute_algorithm();
  
private:
  /**
   * Calculate a k-means like algorithm for detecting communities.
   */
  void k_means_like( string property );
  /**
   * Uses pagerank as centrality measure
   * @return a string with the name of the property storing the measure for
   * each node
   */
  string use_pagerank( Graph* graph );
  /**
   * Uses HITS as centrality measure
   * @return a string with the name of the property storing the measure for
   * each node
   */
  string use_hits();
  /**
   * Uses closeness as centrality measure
   * @return a string with the name of the property storing the measure for
   * each node
   */
  string use_closeness();
  /**
   * Obtains the k nodes with the best measure (PAGERANK|HITSRANK|CLOSENESS)
   * @return a vector with the k best nodes
   */
  vector<node> extract_best_k( Graph* graph, string property, int target_k );
  
  double euclidean_distance( vector<double> vec_a, vector<double> vec_b );
  

private:
  int measure_type;
  int target_k;
  vector<node> k_centroids;
};

#endif
