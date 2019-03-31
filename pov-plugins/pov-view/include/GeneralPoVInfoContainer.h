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
