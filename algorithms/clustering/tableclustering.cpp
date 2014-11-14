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
#include "tableclustering.h"

TableClustering::TableClustering( Graph* pgraph, int iterations, float min_delta, string partition_name_prefix, string pattern_property_name )
  : ClusteringBase( pgraph, iterations, min_delta, partition_name_prefix ), pattern_property_name(pattern_property_name) 
{
  assert( pattern_property_name != "" && pgraph->existProperty( pattern_property_name ));
  patterns = pgraph->getProperty<DoubleVectorProperty>( pattern_property_name );
}

TableClustering::~TableClustering() {}

void TableClustering::remove_sub_graphs()
{
  Iterator<Graph*> *subg_iter = pgraph->getSubGraphs();
  vector<Graph*> group_list;
  while( subg_iter->hasNext() )
  {
    group_list.push_back(subg_iter->next() );
  }
  delete subg_iter;
  for( unsigned int i = 0; i < group_list.size(); i++ )
  {
    pgraph->delSubGraph( group_list[i] );
  }
}

vector<double> TableClustering::getGroupCentroid( Graph* group )
{
  vector<double> result(patterns->getNodeValue(pgraph->getOneNode()).size(), 0.0);
  Iterator<node>* node_iter = group->getNodes();
  while( node_iter->hasNext() )
  {
    node n = node_iter->next();
    vector<double> pattern = patterns->getNodeValue( n );
    for( unsigned int i = 0; i < result.size(); i++ )
    {
      result[i] += pattern[i]/(double)group->numberOfNodes();
    }
  }
  delete node_iter;
  return result;
}

double TableClustering::squared_mean_distance( map<int, Graph*> & groups )
{
  double result = 0;
  map<int, Graph*>::iterator map_it;
  for( map_it = groups.begin(); map_it != groups.end(); ++map_it )
  {
    double int_dist = 0;
    Graph* group = map_it->second;
    Iterator<node>* node_iter = group->getNodes();
    while( node_iter->hasNext() )
    {
      node n = node_iter->next();
      vector<double> vec_a = getGroupCentroid( group );
      vector<double> vec_b = patterns->getNodeValue( n );
      double dist = euclidean_distance( vec_a, vec_b );
      int_dist += dist * dist;
    }
    delete node_iter;
    result += int_dist;
  }
  return result;
}

double TableClustering::squared_mean_distance( map<node, Graph*> & groups )
{
  double result = 0;
  map<node, Graph*>::iterator map_it;
  for( map_it = groups.begin(); map_it != groups.end(); ++map_it )
  {
    double int_dist = 0;
    Iterator<node>* node_iter = map_it->second->getNodes();
    while( node_iter->hasNext() )
    {
      node n = node_iter->next();
      vector<double> vec_a = patterns->getNodeValue( map_it->first );
      vector<double> vec_b = patterns->getNodeValue( n );
      double dist = euclidean_distance( vec_a, vec_b );
      int_dist += dist * dist;
    }
    delete node_iter;
    result += int_dist;
  }
  return result;
}
