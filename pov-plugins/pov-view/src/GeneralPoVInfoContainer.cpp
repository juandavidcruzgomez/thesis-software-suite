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


#include "GeneralPoVInfoContainer.h"

template <class T>
GeneralPoVInfoContainer<T>::GeneralPoVInfoContainer() : data(NULL), number_of_nodes(0){}

template <class T>
GeneralPoVInfoContainer<T>::GeneralPoVInfoContainer(int number_of_nodes) : data(NULL){
  assert( number_of_nodes > 0 );
  this->number_of_nodes = number_of_nodes;
  data = new map<string,T>[number_of_nodes];
}
template <class T>
GeneralPoVInfoContainer<T>::~GeneralPoVInfoContainer(){
  if( data != NULL ){
    delete[] data;
    data = NULL;
  }
}
template <class T>
void GeneralPoVInfoContainer<T>::insertData( int node_index, string pov_name, T data ){
  assert( node_index >= 0 && node_index < number_of_nodes );
  data[node_index][pov_name] = data;
  //Insert into the binary tree...
  //TODO add the code to do the insertion
}

template <class T>
void GeneralPoVInfoContainer<T>::getData( int node_index, string pov_name, T* data ){
  assert( node_index >= 0 && node_index < number_of_nodes );
  if( data != NULL && this->data[node_index].count(pov_name) > 0){
    data = this->data[node_index][pov_name];
  }else{
    data = NULL;
  }
}

template <class T>
void GeneralPoVInfoContainer<T>::getNodeData( int node_index, map<string, T>& node_data ){
  assert( node_index >= 0 && node_index < number_of_nodes );
  node_data = this->data[node_index];
}