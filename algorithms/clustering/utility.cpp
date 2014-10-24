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