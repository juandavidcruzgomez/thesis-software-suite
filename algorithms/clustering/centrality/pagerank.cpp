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
#include "pagerank.h"


PageRank::PageRank( Graph* pgraph, double damping_factor, int max_iterations, double min_delta )
  : pgraph( pgraph )
{
  assert( pgraph != 0 );
  property_name = "pagerank";
  pagerank = pgraph->getLocalProperty<DoubleProperty>( property_name );
  this->damping_factor = damping_factor;
  this->max_iterations = max_iterations;
  this->min_delta = min_delta;
}
PageRank::~PageRank()
{}

string PageRank::getPropertyName() const
{
  return property_name;
}
  
void PageRank::calculate_pagerank()
{
  assert( pgraph != 0 && pagerank != 0 );
  int nb_nodes = pgraph->numberOfNodes();
  /* The rank for nodes with no indegree
     If the surfer arrives with a node with no indegree
     he has to jump to another node*/
  double start_value = ( 1.0 - damping_factor ) / nb_nodes;
  /* For the first step, all the nodes have same probability.
     Initialize the dictionary such that */
  pagerank->setAllNodeValue( start_value );
  int i = 0;
  bool can_continue = true;
  while( i < max_iterations && can_continue )
  {
    double diff = 0.0;
    Iterator<node>* node_iter = pgraph->getNodes();
    while( node_iter->hasNext() )
    {
      node n = node_iter->next();
      double rank = start_value;
      Iterator<node>* neigh_iter = pgraph->getInNodes( n );
      while( neigh_iter->hasNext() )
      {
        node neigh = neigh_iter->next();
        rank += damping_factor * pagerank->getNodeValue( neigh ) / (double)pgraph->deg( neigh );
      }
      delete neigh_iter;
      diff += abs(pagerank->getNodeValue( n ) - rank);
      pagerank->setNodeValue( n, rank );
      
      can_continue = (diff > min_delta);
    }
    delete node_iter;
    i++;
  }
}
