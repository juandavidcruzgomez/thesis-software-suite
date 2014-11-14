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


#ifndef CONCEPT_H
#define CONCEPT_H

#include "generalinc.h"

class ConceptMatrix;

class Concept
{

public:
  /**
   * Constructor: has a pointer to the concept matrix
   */
  Concept( ConceptMatrix* cmatrix );
  /**
   * Destructor
   */
  ~Concept();
  /**
   * Says whether the concept is closed or not
   * @return true if the concept is closed
   */
  bool is_closed();
  /**
   * 
   */
  bool equalsTo(const Concept& other) const;
  
  /**
   * Adds a child to this concept
   * @param child the new child of the concept
   */
  void add_child( Concept* child );
  /**
   * Adds a precedent concept to this concept
   * @param precedent a precedent concept
   */
  void add_precedent( Concept* precedent );
  /**
   * Removes a child from the concept
   * @param child the child to be removed
   */
  void remove_child( Concept* child );
  /**
   * Add an object index to the concept
   * @param obj_idx the index of the object to be added to the concept
   */
  void add_object( int obj_idx );
  /**
   * Add an attribute to the concept
   * @param attr_idx the index of the attribute to be addded to the concept
   */
  void add_attribute( int attr_idx );
  /**
   * Returns a vector with the indices of the objects included in the concept
   */
  std::set<int> get_object_indices() const;
  /**
   * Returns a vector with the indices of the attributes included in the concept
   */
  std::set< int > get_attributes_indices() const;
  /**
   * Set all the objects for a concept
   * @param obj_idxs a vector containing the indices of the objects
   */
  void set_object_idxs( std::vector<int>& obj_idxs );
  /**
   * Set all the attributes for a concept
   * @param attr_idxs a vector containing the indices of the attributes
   */
  void set_attributes_idxs( std::vector<int>& attr_idxs );
  /**
   * Produces a string from the object indices
   * @return a string "0,1,...,n" with the indices of the objects
   */
  //string objects2string();
  /**
   * Produces a string from the attributes indices
   * @return a string "0,1,...,m" with the indices of the attributes
   */
  //string attributes2string();
  /**
   * Returns a string of the concept
   */
  std::string print_concept() const;
  /**
   * Return the children vector
   */
  std::vector<Concept*> get_children() const;
  /**
   * Return the vector of precedent concepts
   */
  std::vector<Concept*> get_precendents() const;
  
  bool isClosing() const;
  
  void setClosing();
  
  void setConceptId( int id );
  
  int getConceptId() const;
  
private:
  std::set<int> objects;
  std::set<int> attributes;
  ConceptMatrix* cmatrix;
  std::vector<Concept*> children;
  std::vector<Concept*> precedents;
  bool closing_concept;
  int concept_id;
};

#endif // CONCEPT_H
