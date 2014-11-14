/**
 The MIT License (MIT)

 Copyright (c) 2014 Juan David Cruz Gómez and Telecom - Bretagne 
 juan.cruzgomez@telecom-bretagne.eu

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
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
