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
#ifndef POVCLUSTERING_H
#define POVCLUSTERING_H

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
