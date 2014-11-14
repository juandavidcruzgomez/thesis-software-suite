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


#ifndef GENERALPOVINFOCONTAINER_H
#define GENERALPOVINFOCONTAINER_H

#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <assert.h>

using namespace std;

template <class T>
struct TreeNode {
    T* data;
    int node_index;
    string pov_name;
};
/**
 * This is a teplate class for stroing the information of the points of view. The idea is to have a
 * <node,"povname"> structure to store something: an integer, a float or a structure (T)
 */
template <class T>
class GeneralPoVInfoContainer
{
public:
    GeneralPoVInfoContainer() {
        number_of_nodes = 0;
    }

    GeneralPoVInfoContainer( int number_of_nodes ){
        assert( number_of_nodes > 0 );
        this->number_of_nodes = number_of_nodes;
	map<string,T> element;
	data = vector<map<string,T> >(this->number_of_nodes, element );
    }

    ~GeneralPoVInfoContainer() {
        
    }
    /**
     * Inserts an element into the structure
     */
    void insertData( int node_index, string pov_name, T data ){
        assert( node_index >= 0 && node_index < number_of_nodes );
        this->data[node_index][pov_name] = data;
        //Insert into the binary tree...
        //TODO add the code to do the insertion
    }
    /**
     * Get the data contained for the node_index and the given pov_name. Stores the data in a pointer.
     */
    void getData( int node_index, string pov_name, T& data ) {
        assert( node_index >= 0 && node_index < number_of_nodes );
        if ( data != NULL && this->data[node_index].count(pov_name) > 0) {
            data = this->data[node_index][pov_name];
        } else {
            data = NULL;
        }
    }
    /**
     * Get all the information of anode: the values for all the registered points of view.
     * Puts the information on a map.
     */
    void getNodeData( int node_index, map<string, T>& node_data ){
        assert( node_index >= 0 && node_index < number_of_nodes );
        node_data = this->data[node_index];
    }
private:
    /**
     * Where the data is contained.
     */
    vector<map<string,T> > data;
    /**
     * What if I want to search for some specific value? Would I have to search throughout all the container?
     * I'd rather prefer to have an auxiliar structure to do it. A binary tree of elements pointing to the data stored in <it>data</it>.
     * The binary tree is represented as a vector, stored in BFS.
     */
    vector<TreeNode<T>*> searchTree;
    /**
     * The number of nodes contained into the structure
     */
    int number_of_nodes;

};

#endif // GENERALPOVINFOCONTAINER_H
