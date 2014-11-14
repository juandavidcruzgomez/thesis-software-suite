/**
 The MIT License (MIT)

 Copyright (c) 2014 Juan David Cruz Gómez and Telecom - Bretagne 
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
