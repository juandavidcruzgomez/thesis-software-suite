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
