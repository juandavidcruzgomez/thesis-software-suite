/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) 2014  <copyright holder> <email>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/



#include "concept.h"
#include "conceptmatrix.h"

Concept::Concept( ConceptMatrix* cmatrix )
  : cmatrix(cmatrix), closing_concept(false), concept_id(-1)
{

}

Concept::~Concept()
{
  objects.clear();
  attributes.clear();
}

bool Concept::equalsTo(const Concept& other) const
{
  std::set<int> other_objs = other.get_object_indices();
  std::set<int> other_attr = other.get_attributes_indices();
  return objects == other_objs && attributes == other_attr;
}

bool Concept::is_closed()
{
  if( objects.size() == 0 || attributes.size() == 0 )
  {
    if( objects.size() == 0 ){
      //The concept should have all the attributes
      //set<int> attr_set;
      std::vector<int> attr_idxs = cmatrix->get_all_attributes_idxs();
      //attr_set.insert( attr_idxs.begin(), attr_idxs.end() );
      //return  attr_set.size() == attributes.size();
      return  attr_idxs.size() == attributes.size();
    }else{
      //The concept should have all the objects
      //set<int> objs_set;
      std::vector<int> objs_idxs = cmatrix->get_all_object_idxs();
      //objs_set.insert( objs_idxs.begin(), objs_idxs.end() );
      //return  objs_set.size() == objects.size();
      return  objs_idxs.size() == objects.size();
    }
  }
  else
  {
    //Get the common attributes of the objects and compare them with the attributes of this concept
    std::set<int>::iterator object_iter;
    std::map<int,unsigned int> attr_map;
    std::map<int,unsigned int>::iterator attr_iter;
    std::set<int> local_attributes;
    for( object_iter = objects.begin(); object_iter != objects.end(); object_iter++ )
    {
      std::vector<int> attr = cmatrix->get_object_features( *object_iter );
      for( unsigned int i = 0; i < attr.size(); ++i )
      {
	      if( attr_map.count(attr[i]) == 0 )
	      {
	        attr_map[attr[i]] = 0;
	      }
	      attr_map[attr[i]]++;
      }
    }
    for( attr_iter = attr_map.begin(); attr_iter != attr_map.end(); attr_iter++ )
    {
      if( attr_iter->second == objects.size() )
      {
	      local_attributes.insert( attr_iter->first );
      }
    }
    return attributes == local_attributes;
  }
}
  
void Concept::add_child( Concept* child )
{
  assert( child != 0 );
  unsigned int i = 0;
  while( i < children.size() && !children[i]->equalsTo(*child ) )
  {
    i++;
  }
  if( i == children.size() ){
    children.push_back( child );
  }
}

void Concept::add_precedent( Concept* precedent )
{
  assert( precedent != 0 );
  unsigned int i = 0;
  while( i < precedents.size() && !precedents[i]->equalsTo(*precedent) )
  {
    i++;
  }
  if( i == precedents.size() )
  {
    precedents.push_back( precedent );
  }
}

void Concept::remove_child( Concept* child )
{
  assert( child != 0 );
  std::vector<Concept*>::iterator concept_iter = children.begin();
  while( concept_iter != children.end() && *concept_iter!=child ){
    ++concept_iter;
  }
  if( concept_iter != children.end() ){
    children.erase( concept_iter );
  }
}

void Concept::add_object( int obj_idx )
{
  assert( obj_idx >= 0 );
  objects.insert( obj_idx );
}

void Concept::add_attribute( int attr_idx )
{
  assert( attr_idx >= 0 );
  attributes.insert( attr_idx );
}

std::set<int> Concept::get_object_indices() const
{
  return objects;
}

std::set<int> Concept::get_attributes_indices() const
{
  return attributes;
}

void Concept::set_object_idxs( std::vector<int>& obj_idxs )
{
  objects.insert( obj_idxs.begin(), obj_idxs.end() );
}

void Concept::set_attributes_idxs( std::vector<int>& attr_idxs )
{
  attributes.insert( attr_idxs.begin(), attr_idxs.end() );
}

std::string Concept::print_concept() const
{
  std::stringstream ss;
  std::set<int>::iterator set_iter;
  unsigned int i = 0;
  ss << "(";
  if( objects.size() > 0 ){
    for( set_iter=objects.begin(); set_iter != objects.end(); set_iter++ ){
      ss << *set_iter;
      if( i < objects.size()-1 )
	      ss << ",";
      else
	      ss << "|";
      i++;
    }
  }else{
    ss << "-/-|";
  }
  if( attributes.size() > 0 ){
    i = 0;
    for( set_iter = attributes.begin(); set_iter != attributes.end(); set_iter++ ){
      ss << *set_iter;
      if( i < attributes.size()-1 )
	      ss << ",";
      i++;
    }
  }else{
    ss << "-/-";
  }
  ss << ")";
  return ss.str();
}

std::vector<Concept*> Concept::get_children() const
{
  return children;
}

std::vector<Concept*> Concept::get_precendents() const
{
  return precedents;
}

bool Concept::isClosing() const{
  return closing_concept;
}

void Concept::setClosing()
{
  closing_concept = true;
}

void Concept::setConceptId( int id )
{
  assert( id > -1 );
  concept_id = id;
}
  
int Concept::getConceptId() const
{
  return concept_id;
}
