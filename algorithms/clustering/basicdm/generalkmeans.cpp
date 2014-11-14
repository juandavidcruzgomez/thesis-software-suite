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
#include "generalkmeans.h"

GeneralKMeans::GeneralKMeans( Graph* pgraph, int iterations, float min_delta, string partition_name_prefix, string pattern_property_name, int target_k )
  : TableClustering( pgraph, iterations, min_delta, partition_name_prefix, pattern_property_name ), target_k( target_k )
{
  assert( target_k > 0 && target_k <= (int) pgraph->numberOfNodes() );
}

GeneralKMeans::~GeneralKMeans(){}

int GeneralKMeans::identify_groups_number()
{
  bool desc = true;
  int best_result = 2;
  map<int, Graph*> total_graph_map;
  total_graph_map[0] = pgraph;
  double prev_error = squared_mean_distance(total_graph_map);
  cout << 1 << "\t" << prev_error << endl;
  int i = 2;
  while( i < 20 && desc )
  {
    double error = _basic_kmeans_algorithm( i );
    cout << i << "\t" << error << endl;
    i++;
    desc = prev_error - error < 0 ? false : true; 
    remove_sub_graphs();
  }
  best_result = i;
  return best_result;
}

double GeneralKMeans::_basic_kmeans_algorithm( int k )
{
  srand (time(NULL));
  vector<vector<double> > centroids = select_k_centroids( k );
  double error = 1E20;
  int i = 0;
  bool stable = false;
  map<int, Graph*> groups;
  while( i < iterations && !stable )
  {
    //Clean the subgroups (if they exist) from the previous iteration
    remove_sub_graphs();
    groups.clear();
    //Create subgroups for each one of the centroids
    //They are stored in a map for accessing them easily
    stringstream ss;
    ss.str("group_node_");
    for( int j = 0; j < k; j++ )
    {
      ss << j;
      groups[j] = pgraph->addSubGraph(ss.str());
      ss.str("group_node_");
    }
    //Assign the nodes...
    Iterator<node>* node_iter = pgraph->getNodes();
    int winner_node = -1;
    double best_dist = 1E25;
    double dist = best_dist;
    while( node_iter->hasNext() )
    {
      node n = node_iter->next();
      //Test all the centroids
      for( int j = 0; j < k; j++ )
      {
        vector<double> vec_a = centroids[j];
        vector<double> vec_b = patterns->getNodeValue( n );
        dist = euclidean_distance( vec_a, vec_b );
        if( dist < best_dist )
        {
          best_dist = dist;
          winner_node = j;
        }
      }
      groups[winner_node]->addNode( n );
      best_dist = 1E25;
      dist = best_dist;
    }
    delete node_iter;
    //Calculate edges for each group
    //assignEdgesToGroups();
    vector<vector<double> > candidate_centroids = select_k_centroids(k);
    stable = isStable( centroids, candidate_centroids );
    if( !stable )
    {
      centroids = candidate_centroids;
    }
    i++;
  }
  /*Iterator<Graph*>* subg_iter = pgraph->getSubGraphs();
  while( subg_iter->hasNext() )
  {
    Graph* subg = subg_iter->next();
    cout << "Group " << subg->getName() << " has " << subg->numberOfNodes() << " nodes." << endl;
  }
  delete subg_iter;*/
  error = squared_mean_distance( groups );
  return error;
}
  
void GeneralKMeans::execute_algorithm()
{
  /*double error = _basic_kmeans_algorithm( this->target_k );
  cout << "Error: " << error << endl;*/
  //identify_groups_number();
  if( target_k > 1 )
  {
    _basic_kmeans_algorithm( target_k );
    assignEdgesToGroups();
    clean_partition( pgraph );
    color_partitions( pgraph );
  }else{
    pgraph->addCloneSubGraph("group_node_0");
  }
}

bool GeneralKMeans::isStable( vector<vector<double> >& centroids, vector<vector<double> >& candidate_centroids )
{
  unsigned int matches = 0;
  for( unsigned int i = 0; i < centroids.size(); i++ )
  {
    if( equalVectors( centroids[i], candidate_centroids[i] ) )
    {
      matches++;
    }
  }
  return matches == centroids.size();
}

bool GeneralKMeans::equalVectors(std::vector< double >& vec_a, std::vector< double >& vec_b)
{
  int sum_away= 0;
  for( unsigned int i = 0; i < vec_a.size(); i++ )
  {
    sum_away += fabs(vec_a[i] - vec_b[i]) < numeric_limits<double>::epsilon() ? 0 : 1;
  }
  return sum_away == 0; 
}

bool GeneralKMeans::isStable( vector<node>& centroids, vector<node>& candidate_centroids )
{
  unsigned int matches = 0;
  for( unsigned int i = 0; i < centroids.size(); i++ )
  {
    if( find( candidate_centroids.begin(), candidate_centroids.end(), centroids[i] ) != candidate_centroids.end() )
    {
      matches++;
    }
  }
  return matches == centroids.size();
}

vector<vector<double> > GeneralKMeans::select_k_centroids(int k)
{
  vector<vector<double> > result;
  vector<node> selected;
  double number_of_nodes = pgraph->numberOfNodes();
  if( pgraph->numberOfSubGraphs() == 0 )
  {
    // If there are not existing groups (i.e., it's the first iteration)
    int k_count = 0;
    while( k_count < k )
    {
      Iterator<node>* node_iter = pgraph->getNodes();
      bool found = false;
      while( node_iter->hasNext() && !found )
      {
	node n = node_iter->next();
	double coin = (double)rand()/(double)RAND_MAX;
	if( coin < (double)k/number_of_nodes && find( selected.begin(), selected.end(), n ) == selected.end() )
	{
	  vector<double> pattern = patterns->getNodeValue(n);
	  result.push_back( pattern );
	  selected.push_back(n);
	  k_count++;
	  found = true;
	}
      }
      delete node_iter;
    }
  }
  else
  {
    // Select the centroids from the groups
    //Calculate the average
    Iterator<Graph*>* subg_iter = pgraph->getSubGraphs();
    while( subg_iter->hasNext() )
    {
      vector<double> center(patterns->getNodeValue(pgraph->getOneNode()).size(), 0.0);
      Graph* group = subg_iter->next();
      Iterator<node>* node_iter = group->getNodes();
      while( node_iter->hasNext() )
      {
        node n = node_iter->next();
        vector<double> actual_pattern = patterns->getNodeValue( n );
        for( unsigned int i = 0; i < center.size(); i++ )
        {
          center[i] += actual_pattern[i]/(double)group->numberOfNodes();
        }
      }
      delete node_iter;
      result.push_back( center );
    }
    delete subg_iter;
  }
  assert( (int)result.size() == k );
  return result;
}

node GeneralKMeans::getClosestNode( vector<double>& centroid )
{
  node best = pgraph->getOneNode();
  double best_dist = 1E25;
  double dist = best_dist;
  Iterator<node>* node_iter = pgraph->getNodes();
  while( node_iter->hasNext() )
  {
    node n = node_iter->next();
    vector<double> other_vector = patterns->getNodeValue( n );
    dist = euclidean_distance( centroid, other_vector );
    if( dist < best_dist && (find( selected.begin(), selected.end(), n) == selected.end() ) )
    {
      best_dist = dist;
      best = n;
      selected.push_back( n );
    }
  }
  delete node_iter;
  return best;
}

void GeneralKMeans::set_k( int k )
{
  if( k > 0 ){
    target_k = k;
  }else{
    target_k = 1;
  }
}
