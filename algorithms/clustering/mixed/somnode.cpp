/**
 The MIT License (MIT)

 Copyright (c) 2012 Juan David Cruz Gómez and Telecom - Bretagne 
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
