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
#include "louvain.h"

Louvain::Louvain( Graph* pgraph, int iterations, float min_delta, string partition_name_prefix )
  : ClusteringBase( pgraph, iterations, min_delta, partition_name_prefix )
{
  assert( pgraph != 0 );
  this->partition_name_prefix = partition_name_prefix == "" ? "DEF_STR" : partition_name_prefix;
  this->space = 0;
  modularity = 0.0f;
}

Louvain::~Louvain()
{
  if( space != 0 )
  {
    delete space;
  }
}
  
void Louvain::execute_algorithm()
{
  long start_time = clock();
  long end_time = 0;
  int* weights = 0;
  if ( pgraph->existLocalProperty("edgeWeight") ) {
    DoubleProperty* edge_weights = pgraph->getLocalProperty<DoubleProperty>("edgeWeight");
    weights = new int[pgraph->numberOfEdges()];
    Iterator<edge>* edge_iterator = pgraph->getEdges();
    while ( edge_iterator->hasNext() ) {
      edge e = edge_iterator->next();
      weights[e.id]=edge_weights->getEdgeValue(e);
    }
    delete edge_iterator;
    space = new CommunitySpace( pgraph, partition_name_prefix, weights );
  } else {
    space = new CommunitySpace( pgraph, partition_name_prefix );
  }
  modularity = space->execute_fast_unfolding(min_delta, iterations, iterations);
  end_time = clock();
  cout << "Modularity: " << modularity << endl;
  cout << "Algorithm took "<< (float)(end_time-start_time)/(float)CLOCKS_PER_SEC << " seconds.\n";
  space->getFinalAssignation( partition_name_prefix );
  //Now, add the edges to the group
  assignEdgesToGroups();
  if( weights != 0 )
    delete[] weights;
}

float Louvain::getModularity() const
{
  return modularity;
}
