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
#include "povclustering.h"

PoVClustering::PoVClustering( Graph* pgraph, int iterations, float min_delta, string partition_name_prefix, string pattern_property_name )
  : ClusteringBase( pgraph, iterations, min_delta, partition_name_prefix )
{
  assert( pgraph != 0 );
  this->partition_name_prefix = partition_name_prefix == "" ? "DEF_MXD" : partition_name_prefix;
  this->pattern_property_name = pattern_property_name == "" ? "data_vector" : pattern_property_name;
  this->som_space = 0;
  modularity = 0.0f;
}

PoVClustering::~PoVClustering()
{
  if( som_space != 0 )
  {
    delete som_space;
  }
}
  
void PoVClustering::execute_algorithm()
{
  //First, execute the SOM algorithm
  execute_som_clustering();
  // Calculate the weight of the edges according the SOM groups
  vector<int> assignation = som_space->getAssignation();
  DoubleProperty* weights = 0;
  bool weighted = pgraph->existLocalProperty( "edgeWeight" );
  // Classic approach
  weights = pgraph->getLocalProperty<DoubleProperty>( "edgeWeight" );
  Iterator<edge>* edge_iter = pgraph->getEdges();
  double weight = 1;
  while( edge_iter->hasNext() )
  {
    edge e = edge_iter->next();
    node source = pgraph->source( e );
    node target = pgraph->target( e );
    if( assignation[source.id] == assignation[target.id] )
    {
      weight = weighted ? weights->getEdgeValue( e ) * weights->getEdgeValue( e ) : 20;
    }
    weights->setEdgeValue( e, weight );
    weight = 1;
  }
  delete edge_iter;
  // Call the louvain algorithm...
  Louvain lou( pgraph, iterations, min_delta, partition_name_prefix );
  lou.execute_algorithm();
  modularity = lou.getModularity();
}

float PoVClustering::getModularity() const
{
  return modularity;
}

void PoVClustering::execute_som_clustering(){
  assert( pgraph != 0 );
  // Conf for the SOM algorithm
  int som_iterations = 250;
  int som_lambda = 10;
  float som_epsilon = 1E-5;
  float som_lr = 0.001;
  som_space = new SOMClusteringSpace( pgraph, pattern_property_name, som_iterations, som_lambda, som_epsilon, som_lr );
  assert(som_space->start_algorithm());
}

Matrix* PoVClustering::getSOMAffiliationMatrix()
{
  vector<int> assignation = som_space->getAssignation();
  map<int, int> assignationtion_map;
  int count = 0;
  for( unsigned int i = 0; i < assignation.size(); ++i )
  {
    int actual_value = assignation[i];
    if( assignationtion_map.count(actual_value) == 0 )
    {
      assignationtion_map[actual_value] = count;
      count++;
    }
  }
  int rows = pgraph->numberOfNodes();
  int cols = assignationtion_map.size();
  Matrix* result = new Matrix( rows, cols, COLUMN_MAJOR );
  result->set_all_zeros();
  for( unsigned int i = 0; i < assignation.size(); ++i )
  {
    int row_pos = i;
    int col_pos = assignationtion_map[assignation[i]];
    result->setElement( row_pos, col_pos, 1 );
  }
  return result;
}
