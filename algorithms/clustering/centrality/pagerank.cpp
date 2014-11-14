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
