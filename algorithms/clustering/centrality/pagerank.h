#ifndef __PAGERANK_H__
#define __PAGERANK_H__

#include <tulip/Graph.h>
#include <tulip/DoubleProperty.h>

#include <math.h>

using namespace tlp;
using namespace std;

class PageRank{
public:
  PageRank( Graph* pgraph, double damping_factor, int max_iterations, double min_delta );//double damping_factor=0.85, int max_iterations=100, double min_delta=1E-5
  ~PageRank();
  
  void calculate_pagerank();
  /**
   * gets the name of the property storing the measure
   */
  string getPropertyName() const;
  
private:
  double damping_factor;
  int max_iterations;
  double min_delta;
  string property_name;
  Graph* pgraph;
  DoubleProperty* pagerank;
};

#endif
