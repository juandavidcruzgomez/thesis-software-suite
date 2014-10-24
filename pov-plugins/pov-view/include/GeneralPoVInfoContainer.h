/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) 2012  Juan David Cruz Gomez <email>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
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
