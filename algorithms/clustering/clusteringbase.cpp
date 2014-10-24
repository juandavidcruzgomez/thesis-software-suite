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
