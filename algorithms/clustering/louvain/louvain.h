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
#ifndef LOUVAIN_H
#define LOUVAIN_H

#include <string>
#include <iostream>

#include <tulip/DoubleProperty.h>

#include "clusteringbase.h"
#include "CommunitySpace.h"


using namespace std;
using namespace tlp;

/**
 * This class implements the Louvain's community detection algorithm
 */
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
