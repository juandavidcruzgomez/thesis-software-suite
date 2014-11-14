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


#ifndef GALOISLATTICE_H
#define GALOISLATTICE_H

#include "generalinc.h"
#include "concept.h"
#include "conceptmatrix.h"
#include "trie.h"

class GaloisLattice
{

public:
  GaloisLattice( ConceptMatrix* cmatrix );
  virtual ~GaloisLattice();
  /**
   * Finds the children of the given concept
   * @param parent the target concept 
   * @return the list of childs found. If a child already exists on the lattice, 
   * a pointer to it will be added to the list.
   */
  std::vector<Concept*> find_child( Concept* parent );
  
  /**
   * Obtains the attributes that DO NOT belong to the concept
   * @param concept the concept to be analized
   * @return a vector with the attributes indices
   */
  std::vector<int> get_res_attributes( Concept* concept );
  /**
   * 
   */
  void generate_lattice();
  /**
   * Check whether the concept is the last one on the lattice
   */
  bool is_last_concept( std::set<int> attributes );
  
  /**
   * Tells whether the concept has been already computed or not
   * @param concept the concept to be tested
   * @return true if the concept has been alredy computed; false otherwise
   */
  Concept* concept_exists( Concept* concept );
  /**
   * 
   */
  std::string print_lattice();
  /**
   * 
   */
  ConceptMatrix* getConceptMatrix();
  /**
   * Returns the root concept of the lattice
   */
  Concept* getRootConcept() const;
  /**
   * Returns the base concept of the lattice
   */
  Concept* getBaseConcept() const;
  
private:
  /**
   * This is just a wrapper function for creating the closing concept of the 
   * lattice
   * @return a concept with all the attributes and no objects
   */
  Concept* create_end_concept();
  
  void close_lattice();
  /**
   * Validates the cocnept by assingning a valid id. This is made to control the 
   * ids given.
   */
  void make_concept_valid( Concept* concept );
  /**
   * Adds a concept to the trie
   */
  void add2trie( Concept* concept );
  
private:
  /**
   * The matix containing the objects and their attributes
   */
  ConceptMatrix* cmatrix;
  /**
   * The structure containing the existing concepts. This is the index.
   */
  trie* concept_trie;
  
  Concept* root_concept; //All objects - no attributes
  
  Concept* base_concept; //All attributes - no objects
  
  std::map<tri_node*,Concept*> global_concept_map;
  /**
   * A counter to control the ids of the concepts
   */
  int concept_id_index;
};

#endif // GALOISLATTICE_H
