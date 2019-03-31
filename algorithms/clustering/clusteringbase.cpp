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
#include "clusteringbase.h"

ClusteringBase::ClusteringBase( Graph* pgraph, int iterations, float min_delta, string partition_name_prefix )
  : pgraph( pgraph ), iterations( iterations ), min_delta( min_delta )
{
  assert( pgraph != 0 && iterations > 0 && min_delta >= 0.0 );
  this->partition_name_prefix = partition_name_prefix == "" ? "generic_part" : partition_name_prefix;
}

ClusteringBase::~ClusteringBase(){}

void ClusteringBase::assignEdgesToGroups()
{
  assert( pgraph != 0 );
  Iterator<edge>* edge_iter = pgraph->getEdges();
  while ( edge_iter->hasNext() ) {
    edge e = edge_iter->next();
    node source = pgraph->source(e);
    node target = pgraph->target(e);
    Iterator<Graph*>* sub_g_iter = pgraph->getSubGraphs();
    while ( sub_g_iter->hasNext() ) {
      Graph* subg = sub_g_iter->next();
      if ( subg->isElement(source) && subg->isElement(target) ) {
        subg->addEdge(e);
      }
    }
    delete sub_g_iter;
  }
  delete edge_iter;
}
