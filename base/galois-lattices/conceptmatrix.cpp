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


#include "conceptmatrix.h"

ConceptMatrix::ConceptMatrix( ) :
  object_counter( 0 ), attributes_size( 0 )
{

}

ConceptMatrix::ConceptMatrix( int attributes_size ) :
  object_counter( 0 ), attributes_size( attributes_size )
{

}

ConceptMatrix::~ConceptMatrix()
{

}

std::vector<int> ConceptMatrix::get_object_features( int obj_idx )
{
  assert( obj_idx >= 0 && objects.count(obj_idx) > 0 );
  return objects[obj_idx];
  
}
  
std::vector<int> ConceptMatrix::get_attribute_objects( int attr_idx )
{
  assert( attr_idx >= 0 && attributes.count( attr_idx ) > 0 );
  return attributes[attr_idx];
}

std::string ConceptMatrix::get_string_of_features_by_object( int obj_idx )
{
  if( attr_str_cache.count(obj_idx) == 0 ){
    std::stringstream ss;
    std::vector<int> attr = get_object_features( obj_idx );
    if( attr.size() > 0 ){
      for( unsigned int i = 0; i < attr.size(); ++i ){
	      ss << attr[i];
	      if( i < attr.size()-1 )
	        ss << ",";
      }
    }else{
      ss << "-/-";
    }
    attr_str_cache[obj_idx] = ss.str();
  }
  return attr_str_cache[obj_idx];
}

std::string ConceptMatrix::get_string_of_objects_by_attribute( int attr_idx )
{
  std::map<int,std::string> obj_str_cache;
  if( obj_str_cache.count(attr_idx) == 0 ){
    std::stringstream ss;
    std::vector<int> objs = get_attribute_objects( attr_idx );
    if( objs.size() > 0 ){
      for( unsigned int i = 0; i < objs.size(); ++i ){
	      ss << objs[i];
	      if( i < objs.size()-1 )
	        ss << ",";
      }
    }else{
      ss << "-/-";
    }
    obj_str_cache[attr_idx] = ss.str();
  }
  return obj_str_cache[attr_idx];
}

int ConceptMatrix::add_object()
{
  objects[object_counter].clear();
  object_counter++;
  return object_counter-1;
}

bool ConceptMatrix::add_attribute( int obj_idx, int attr_idx )
{
  if( obj_idx >= 0 && attr_idx >= 0 )
  {
    if( !contains_index( objects[obj_idx], attr_idx ) && !contains_index( attributes[attr_idx], obj_idx ) )
    {
      objects[obj_idx].push_back(attr_idx);
      attributes[attr_idx].push_back(obj_idx);
      return true;
    }
    else{
      return false;
    }
  }
  else
  {
    return false;
  }
}

void ConceptMatrix::printConceptMatrix()
{
  for( int j = 0; j < attributes_size; ++j ){
    std::cout << "\tAttribute " << j;
  }
  std::cout << std::endl;
  for( int i = 0; i < object_counter; ++i )
  {
    std::cout << "Object " << i << ": ";
    std::vector<int> attr = objects[i];
    for( int j = 0; j < attributes_size; ++j )
    {
      if( contains_index( attr, j ) ){
	      std::cout << "\t1";
      }else{
	      std::cout << "\t0";
      }
    }
    std::cout << std::endl;
  }
}

void ConceptMatrix::load_matrix( int** bin_matrix, int nb_objects, int nb_attributes )
{
  assert( bin_matrix != 0 );
  for( int i = 0; i < nb_objects; ++i ){
    int obj_idx = add_object();
    for( int j = 0; j < nb_attributes; j++ ){
      if( bin_matrix[i][j] == 1 ){
	      add_attribute(obj_idx,j);
      }
    }
  }
}

bool ConceptMatrix::contains_index( std::vector<int> idx_set, int idx )
{
  unsigned int i = 0;
  while( i < idx_set.size() && idx_set[i] != idx )
  {
    i++;
  }
  return i != idx_set.size();
}

int ConceptMatrix::get_nb_attributes() const
{
  return this->attributes_size;
}

std::vector<int> ConceptMatrix::get_all_object_idxs()
{
  std::vector<int> result;
  std::map<int, std::vector<int> >::iterator key_iter;
  for( key_iter = objects.begin(); key_iter != objects.end(); ++key_iter ){
    result.push_back( key_iter->first );
  }
  return result;
}
 
std::vector<int> ConceptMatrix::get_all_attributes_idxs()
{
  std::vector<int> result;
  std::map<int, std::vector<int> >::iterator key_iter;
  for( key_iter = attributes.begin(); key_iter != attributes.end(); ++key_iter ){
    result.push_back( key_iter->first );
  }
  return result;
}

void ConceptMatrix::set_nb_attributes( int nb_attributes )
{
  attributes_size = nb_attributes;
}

void ConceptMatrix::add_attribute_limit( int limit )
{
  assert( limit >= 0 && limit < attributes_size );
  if( attributes_limits.size() == 0 )
  {
    attributes_limits.push_back( 0 );
  }
  attributes_limits.push_back( limit );
}

std::vector< int > ConceptMatrix::getLimits() const
{
  return attributes_limits;
}
