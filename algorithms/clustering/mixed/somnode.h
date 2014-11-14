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
#ifndef SOM_NODE_H
#define	SOM_NODE_H

#define MAX_NEIGHBORS 8
#define MIN_NEIGHBORS 3

#include <vector>
#include <set>
#include <cstdlib>
#include <math.h>
#include <iostream>
#include <cassert>

using namespace std;

class SOM_Node {
public:

    static int actual;
    /**
     * Constructor
     * @param _self_index the index of this node
     * @param _n_weights the number of dimensions of the node
     */  
    SOM_Node( int _self_index, int _n_weights );
    /**
     * Constructor
     */
    SOM_Node( int _self_index, int _n_weights, vector<double> sampled_vector );
    /**
     * Destructor
     */
    virtual ~SOM_Node();
    /**
     * Calculates the Euclidean distance to a given vector
     * @param some_vector
     * @return
     */
    float distance( vector<double> some_vector );
    /**
     * Adds a neighbor index to the list
     * @param index the index of the neighbor to be added.
     * @return true if the index was successfully added, false if the number of neighbors for this node is equal to MAX_NEIGHBORS, the
     * index already exists or is less than 0.
     */
    bool addNeighbor( int index );
    /**
     * Returns the self index of the node
     * @return this->self_index
     */
    int getSelfIndex() const;
    /**
     * Returns the list of neighbors
     * @return this->neighbor_indices
     */
    set<int> getNeighborIndeces() const;
    /**
     * Returns the value of the weight at the position index
     * @param index the searched position
     * @return the value or -1 if the index is invalid
     */
    float getWeightAt( int index ) const;
    /**
     * Changes the value of the weight vector at the position index
     * @param index the index of the position
     * @param value the new value to be set
     */
    void setWeightAt( int index, float value );

protected:
    /**
     * Initializes the weigths of the vector
     */
    void initialize();
private:
    /**
     * Number of dimension of each neuron
     */
    int pattern_size;
    /**
     * The index of this node
     */
    int self_index;
    /**
     * Vector of weights
     */
    vector<double> weights;
    /**
     * Indices of the neighbors
     */
    set<int> neighbor_indices;
};

#endif	/* SOM_NODE_H */

