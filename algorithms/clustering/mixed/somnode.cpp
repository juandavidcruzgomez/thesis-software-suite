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

#include "somnode.h"

int SOM_Node::actual = 0;

SOM_Node::SOM_Node( int _self_index, int _n_weights ) {
    self_index = _self_index;
    pattern_size = _n_weights;
    initialize();
}

SOM_Node::SOM_Node( int _self_index, int _n_weights, vector<double> sampled_vector ){
  assert( (int)sampled_vector.size() == _n_weights );
  self_index = _self_index;
  pattern_size = _n_weights;
  weights.insert( weights.begin(), sampled_vector.begin(),sampled_vector.end());
}

SOM_Node::~SOM_Node() {}

void SOM_Node::initialize() {
    int i;
    //cout << "Initializing SOM node " << self_index << " with " << pattern_size << " dimensions." << endl;
    for ( i = 0; i < pattern_size; i++ ) {
        float weight = (float)rand()/(float)RAND_MAX;
        weights.push_back(weight);
    }
}

float SOM_Node::distance( vector<double> some_vector ) {
    float dist = 0;
    int i;
    //cout << "this->weights size: " << weights.size() << ", some_vector size: " << some_vector.size() << endl;
    for ( i = 0; i < (int)some_vector.size(); i++ ) {
        dist += (float)pow(weights[i]-some_vector[i],2.0f);
    }
    return (float)sqrt(dist);
}

bool SOM_Node::addNeighbor( int index ) {
    if ( index > -1 && neighbor_indices.size() < MAX_NEIGHBORS ) {
        return neighbor_indices.insert(index).second;
    } else {
        return false;
    }
}

int SOM_Node::getSelfIndex() const {
    return self_index;
}

set<int> SOM_Node::getNeighborIndeces() const {
    return neighbor_indices;
}

float SOM_Node::getWeightAt( int index ) const {
    if ( index > -1 && index < (int)weights.size() ) {
        return weights[index];
    } else {
        return -1;
    }
}

void SOM_Node::setWeightAt( int index, float value ) {
    if ( index > -1 && index < (int)weights.size() ) {
        weights[index] = value;
    }
}
