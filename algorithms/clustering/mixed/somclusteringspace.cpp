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


#include "somclusteringspace.h"

SOMClusteringSpace::SOMClusteringSpace( Graph* pGraph, string patterns_prop_name, int _iterations, int _lambda, float _epsilon, float _learning_rate ):
        pGraph(pGraph), patterns_prop_name(patterns_prop_name), iterations(_iterations), lambda(_lambda), epsilon(_epsilon), learning_rate(_learning_rate)
{
    assert( pGraph != 0 );
    theMap = new KohonenMap();
}

SOMClusteringSpace::~SOMClusteringSpace()
{
    if ( theMap != 0 ) {
        delete theMap;
        theMap = 0;
    }
}


bool SOMClusteringSpace::start_algorithm() {
  if ( initialize_algorithm() ) {
    int counter = 0;
    float global_error = MAX_FLOAT;
    int number_of_patterns = pGraph->numberOfNodes();
    Iterator<node>* node_iter = 0;
    patterns = pGraph->getProperty<DoubleVectorProperty>( patterns_prop_name );
    if (number_of_patterns > 0 && patterns != 0) {
      while (counter < lambda && global_error > epsilon) {
        node_iter = pGraph->getNodes();
        while( node_iter->hasNext() )
        {
          node n = node_iter->next();
          int winner_index = competition( n );
          assignation[n.id] = winner_index;
        }
        delete node_iter;
        counter++;
        learning_rate /= 1.1;
      }
    }
    return true;
  }
  return false;
}

bool SOMClusteringSpace::initialize_algorithm() {
    int psize = -1;
    DoubleVectorProperty* patterns = 0;
    vector<vector<double> > pattern_vector;
    if( pGraph->existProperty( patterns_prop_name ) )
    {
      patterns = pGraph->getProperty<DoubleVectorProperty>( patterns_prop_name );
      vector<double> one_pattern_vector = patterns->getNodeValue( pGraph->getOneNode() );
      if( (psize = one_pattern_vector.size() ) > 0 )
      {
	int assignation_count = 0;
	Iterator<node>* node_iter = pGraph->getNodes();
	while( node_iter->hasNext() )
	{
	  node n = node_iter->next();
	  assignation.push_back(assignation_count);
	  vector<double> actual_vector = patterns->getNodeValue(n); 
	  pattern_vector.push_back( actual_vector );
	  assignation_count++;
	}
	delete node_iter;
      }
      else
      {
        return false;
      }
    }
    else
    {
      cout << "Cannot find a property named " << patterns_prop_name.c_str() << endl;
      return false;
    }
    //Set the appropiate values for the map
    float expected_size = 7.0 * pow( pGraph->numberOfNodes(), 0.54321 );
    int rows = (int)ceil( sqrt(expected_size));
    theMap->setRows(rows);
    theMap->setCols(rows);
    theMap->setNFeatures(psize);
    theMap->initialize( pattern_vector);
    return theMap->isReady();
}

int SOMClusteringSpace::competition( node n ) {
    int i, winner_index = -1;
    float best_distance = MAX_FLOAT;
    float actual_dist = MAX_FLOAT;
    vector<double> _actual_pattern = patterns->getNodeValue( n );
    for (i = 0; i < theMap->getNNeurons(); i++) {
        actual_dist = theMap->distance(i, _actual_pattern);
        if (actual_dist < best_distance) {
            best_distance = actual_dist;
            winner_index = i;
        }
    }
    cooperation( n, winner_index );
    return winner_index;
}

void SOMClusteringSpace::cooperation( node n, int winner_index ) {
  vector<double> _actual_pattern = patterns->getNodeValue( n );
  float new_weight = 0;
  int i;
  //Get the neighborhood indeces:
  set<int> neighbors = theMap->getNeutonAt(winner_index)->getNeighborIndeces();
  neighbors.insert(winner_index);
  set<int>::iterator neighbor_iterator;
  //Update the weights
  for ( neighbor_iterator=neighbors.begin();neighbor_iterator!=neighbors.end(); neighbor_iterator++) {
      int actual_index = *neighbor_iterator;
      for ( i = 0; i < theMap->getNFeatures(); i++ ) {
          new_weight = theMap->getNeutonAt(actual_index)->getWeightAt(i) + learning_rate*(_actual_pattern[i]-theMap->getNeutonAt(actual_index)->getWeightAt(i));
          theMap->getNeutonAt(actual_index)->setWeightAt(i,new_weight);
      }
  }
}

vector<int> SOMClusteringSpace::getAssignation() const
{
  return assignation;
}

void SOMClusteringSpace::getPartitionConfiguration() {
  vector<int> indices;
  //Create equivalent indices
  for ( int i = 0; i < (int)assignation.size();i++) {
    int val = assignation.at(i);
    if ( belongs_to( val, indices ) == -1 ) {
      indices.push_back( val );
    }
  }
  for ( int i = 0; i < (int)indices.size(); i++ ) {
    string group_name("");
    group_name.append(patterns_prop_name).append("_");
    group_name.append(static_cast<ostringstream*>(&(ostringstream()<<i))->str() );
    pGraph->addSubGraph(group_name);
  }
  //Now, define the groups
  //IntegerProperty* group = theGraph->getLocalProperty<IntegerProperty>(patterns_prop_name);
  string group_name("");
  Iterator<node>* node_iter = pGraph->getNodes();
  while ( node_iter->hasNext() ) {
    node n = node_iter->next();
    int id = n.id;
    int val = assignation.at(id);
    int new_index = belongs_to( val, indices );
    group_name.append(patterns_prop_name).append("_").append(static_cast<ostringstream*>(&(ostringstream()<<new_index))->str() );
    pGraph->getSubGraph(group_name)->addNode(n);
  	//group->setNodeValue(n,new_index);
    //group_name = "";
  }
  delete node_iter;
}
