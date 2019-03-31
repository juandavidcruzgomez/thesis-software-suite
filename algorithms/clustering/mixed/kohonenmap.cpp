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
#include "kohonenmap.h"

KohonenMap::KohonenMap() {
    rows = 0;
    cols = 0;
    learning_rate = 0;
    number_of_features = 0;
    pattern_count = 0;
    ready = false;
}

KohonenMap::KohonenMap(int _rows, int _cols, float _learning_rate, int _pattern_size) {
    rows = _rows;
    cols = _cols;
    learning_rate = _learning_rate;
    number_of_features = _pattern_size;
    ready = false;
    initialize();
    pattern_count = 0;
}

KohonenMap::~KohonenMap() {
    if (rows > 0 && cols > 0) {
        map<int, SOM_Node*>::iterator iter;
        for (iter = theMap.begin(); iter != theMap.end(); iter++) {
            delete (*iter).second;
            (*iter).second = NULL;
        }
        rows = 0;
        cols = 0;
    }
    ready = false;
}

void KohonenMap::initialize( vector< std::vector< double > > patterns )
{
  int minRow = 0;
  int minCol = 0;
  int maxRow = 0;
  int maxCol = 0;
  int* selected = new int[patterns.size()];
  memset( selected, 0, patterns.size() );
  for( int i = 0; i < rows; ++i )
  {
    minRow = i - 1 < 0 ? 0 : i - 1;
    maxRow = i + 1 > rows ? rows : i + 1;
    for( int j = 0; j < cols; ++j )
    {
      int index = select_random_pattern( selected, patterns.size() );
      theMap[i*cols+j] = new SOM_Node(i*cols+j, number_of_features, patterns[index]);
      minCol = j - 1 < 0 ? 0 : j - 1;
      maxCol = j + 1 > cols ? cols : j + 1;
      for ( int k = minRow; k < maxRow; k++ ) {
	for ( int m = minCol; m < maxCol; m++ ) {
	  int index_n = k*cols+m;
	  if ( i*cols+j != index_n ) {
	      theMap[i*cols+j]->addNeighbor(index_n);
	  }
	}
      }
    }
  }
  ready = true;
}

int KohonenMap::select_random_pattern( int* selected, int size )
{
  assert( selected != 0 );
  int index = -1;
  do{
    float u = (float)rand()/(float)RAND_MAX;
    index = (int)( u * (float)size );
  }while( selected[index] != 0 );
  selected[index] = 1;
  return index;
}

void KohonenMap::initialize() {
    if ( rows > 0 && cols > 0 && number_of_features > 0 ) {
        int i,j,k,m;
        int minRow = 0;
        int minCol = 0;
        int maxRow = 0;
        int maxCol = 0;
        for ( i = 0; i < rows; i++) {
            minRow = i - 1 < 0 ? 0 : i - 1;
            maxRow = i + 1 > rows ? rows : i + 1;
            for ( j= 0; j < cols; j++ ) {
                theMap[i*cols+j] = new SOM_Node(i*cols+j, number_of_features);
                minCol = j - 1 < 0 ? 0 : j - 1;
                maxCol = j + 1 > cols ? cols : j + 1;
                for ( k = minRow; k < maxRow; k++ ) {
                    for ( m = minCol; m < maxCol; m++ ) {
                        int index = k*cols+m;
                        if ( i*cols+j != index ) {
                            theMap[i*cols+j]->addNeighbor(index);
                        }
                    }
                }
            }

        }
        ready = true;
    } else {
        cout << "There is something wrong with the parameters: rows = " << rows << ", cols = " << cols << ", pattern size = " << number_of_features << endl;
    }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float KohonenMap::distance( int neuron_index, std::vector<double>& pattern ) {
    assert( neuron_index >= 0 && neuron_index < this->getNNeurons() );
    return theMap[neuron_index]->distance(pattern);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SOM_Node* KohonenMap::getNeutonAt( int _index ) {
    assert( _index >= 0 && _index < getNNeurons() );
    return theMap.at(_index);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int KohonenMap::getNRows() const {
    return rows;
}
int KohonenMap::getNCols() const {
    return cols;
}
void KohonenMap::setRows( int _rows ) {
    rows = _rows;
}
void KohonenMap::setCols( int _cols ) {
    cols = _cols;
}
int KohonenMap::getNFeatures() const {
    return number_of_features;
}
void KohonenMap::setNFeatures( int _psize ) {
    number_of_features = _psize;
}
int KohonenMap::getNNeurons() const {
    return theMap.size();
}
float KohonenMap::getlearningRate() const {
    return learning_rate;
}
void KohonenMap::setLearning_rate(float _learning_rate) {
    learning_rate = _learning_rate;
}
bool KohonenMap::isReady() {
    return ready;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/*void KohonenMap::print_final_assignation() {
    int i;
    for ( i = 0; i < assignation.size(); i++ ) {
        cout << "Node " << i << "=>" << assignation[i] << endl;
    }
}

void KohonenMap::calculateGroups( map<int, vector<int> > &partition ) {
    int i, actual_group;
    for ( i = 0; i < assignation.size(); i++ ) {
        actual_group = assignation[i];
        partition[actual_group].push_back(assignation[i]);
    }
}


map<int, int> KohonenMap::getAssignation() const {
    return assignation;
}*/
