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
