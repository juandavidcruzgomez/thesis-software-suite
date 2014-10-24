#ifndef __LOUVAIN_H__
#define __LOUVAIN_H__

#include <string>
#include <iostream>

#include <tulip/DoubleProperty.h>

#include "clusteringbase.h"
#include "CommunitySpace.h"


using namespace std;
using namespace tlp;

class Louvain : public ClusteringBase{
public:
  Louvain( Graph* pgraph, int iterations, float min_delta, string partition_name_prefix );
  ~Louvain();
  /**
   * Function member definition for execute_algorithm() which is abstract 
   * in base class
   */
  void execute_algorithm();
  
  float getModularity() const;
  
private:
  CommunitySpace* space;
  float modularity;
};

#endif
