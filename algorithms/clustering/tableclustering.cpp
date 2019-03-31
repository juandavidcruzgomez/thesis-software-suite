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
