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
#include "utility.h"

void color_partitions( Graph* theGraph )
{
  double angle = 0;
  double angle_step = 0;
  int number_of_groups = theGraph->numberOfSubGraphs();
  ColorProperty* viewColor = theGraph->getLocalProperty<ColorProperty>("viewColor");
  if( theGraph != 0 && number_of_groups > 0 )
  {
    angle_step = 2*PI/(float)number_of_groups;
    Iterator<Graph*>* subg_iterator = theGraph->getSubGraphs();
    while( subg_iterator->hasNext() )
    {
      Graph* subg = subg_iterator->next();
      float rgb_array[3];
      rgb_array[0] = 0;
      rgb_array[1] = 0;
      rgb_array[2] = 0;
      angle2RGB( angle, rgb_array );
      Iterator<node>* node_iter = subg->getNodes();
      while( node_iter->hasNext() )
      {
	node n = node_iter->next();
	viewColor->setNodeValue( n, Color(255*rgb_array[0],255*rgb_array[1],255*rgb_array[2]) );
      }
      delete node_iter;
      angle += angle_step;
    }
    delete subg_iterator;
  }
}

void clean_partition( Graph* theGraph )
{
  assert( theGraph != 0 );
  Iterator<Graph*>* subg_iterator = theGraph->getSubGraphs();
  vector<Graph*> to_remove;
  while( subg_iterator->hasNext() )
  {
    Graph* subg = subg_iterator->next();
    if( subg->numberOfNodes() == 0 )
    {
      to_remove.push_back(subg);
    }
  }
  delete subg_iterator;
  for( unsigned int  i = 0; i < to_remove.size(); i++ )
  {
    theGraph->delSubGraph(to_remove[i]);
  }
}
