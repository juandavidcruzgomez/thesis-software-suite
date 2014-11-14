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
