/**
 Copyright (c) 2014 Juan David Cruz Gómez and Telecom - Bretagne

 juan.cruzgomez@telecom-bretagne.eu 
 juandavidcruz@gmail.com

 Licensed under the EUPL, Version 1.2 or – as soon theywill be approved 
 by the European Commission - subsequent versions of the 
 EUPL (the "Licence");

 You may not use this work except in compliance with the Licence.
 You may obtain a copy of the Licence at:

    https://joinup.ec.europa.eu/software/page/eupl5
  
 Unless required by applicable law or agreed to inwriting, software 
 distributed under the Licence isdistributed on an *"AS IS"* basis,
 *WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND*, either express or implied.
 See the Licence for the specific language governing permissions and limitations 
 under the Licence.
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
