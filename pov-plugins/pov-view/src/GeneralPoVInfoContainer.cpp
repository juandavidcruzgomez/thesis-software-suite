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
