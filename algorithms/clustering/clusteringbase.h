#ifndef __CLUSTERINGBASE_H__
#define __CLUSTERINGBASE_H__


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
