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
#include "basicentropy.h"


BasicEntropy::BasicEntropy( Graph* pgraph, string pattern_property_name )
  : pgraph( pgraph ), pattern_property_name( pattern_property_name )
{
  assert( pattern_property_name != "" );
  patterns = pgraph->getProperty<DoubleVectorProperty>( pattern_property_name );
}

BasicEntropy::~BasicEntropy()
{}

double BasicEntropy::calculatePartitionEntropy()
{
  double result = 0;
  node n = pgraph->getOneNode();
  int pat_size = patterns->getNodeValue(n).size();
  Iterator<Graph*>* subg = pgraph->getSubGraphs();
  while( subg->hasNext() )
  {
    Graph* group = subg->next();
    result += calculateGroupEntropy( group, pat_size );//(double)pgraph->numberOfSubGraphs();
  }
  delete subg;
  return result;
}
  
double BasicEntropy::calculateGroupEntropy( Graph* group, int pattern_size )
{
  double result = 0.0;
  vector<double> max_values = calculate_normalization_values( group );
  Iterator<node>* node_iter = group->getNodes();
  while( node_iter->hasNext() )
  {
    node outer_node = node_iter->next();
    Iterator<node>* inner_node_iter = group->getNodes();
    while( inner_node_iter->hasNext() )
    {
	node inner_node = inner_node_iter->next();
	if( outer_node != inner_node )
	{
	  double intermediate = pair_similarity( patterns->getNodeValue( outer_node ), patterns->getNodeValue( inner_node ), max_values );
	  intermediate = exp( -0.5 * intermediate );
	  if( intermediate == 1.0 )
	  {
	    result += 0;
	  }else{
	    result += -( intermediate * log10( intermediate ) );// + (1.0 - intermediate) * log10( 1.0 - intermediate ) );
	  }
	}
    }
    delete inner_node_iter;
  }
  delete node_iter;
  return result;
}

double BasicEntropy::pair_similarity( vector<double> vec_a, vector<double> vec_b, vector<double>& max_values )
{
  double result = 0.0;
  for( unsigned int i = 0; i < vec_a.size(); i++ )
  {
    result += ( (vec_a[i]-vec_b[i])/max_values[i] ) * ( (vec_a[i]-vec_b[i])/max_values[i] );
  }
  return result > 0 ? sqrt( result ) : 0.0;
}

vector<double> BasicEntropy::calculate_normalization_values( Graph* group ){
  node n = pgraph->getOneNode();
  vector<double> max_values = patterns->getNodeValue(n);
  Iterator<node>* node_iter = group->getNodes();
  while( node_iter->hasNext() )
  {
    n = node_iter->next();
    vector<double> actual_vector = patterns->getNodeValue(n);
    for( unsigned int i = 0; i < actual_vector.size(); i++ )
    {
      if( actual_vector[i] > max_values[i] )
      {
	max_values[i] = actual_vector[i];
      }
    }
  }
  delete node_iter;
  return max_values;
}

double BasicEntropy::pair_entropy( vector<double> vec_a, vector<double> vec_b )
{
  double result = 0;
  double dist = ( cosine_distance( vec_a, vec_b ) + 1.0 ) / 2.0;
  if( dist == 0.0 )
  {
    result = 0;
  }else if( dist == 1.0 )
  {
    result = 1;
  }else
  {
    result = -( dist * log( dist ) + (1.0 - dist) * log( 1.0 - dist ) );
  }
  return result;
}
