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
