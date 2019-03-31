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


#ifndef CONCEPTMAT_H
#define CONCEPTMAT_H

#include "generalinc.h"
#include "concept.h"

class ConceptMatrix
{

public:
  ConceptMatrix();
  
  ConceptMatrix( int attributes_size );
  virtual ~ConceptMatrix();
  /**
  * Return the indices of the features for the given object index
  * @param obj_idx the index of the object
  * @return a vector with the indices of features
  */
  std::vector<int> get_object_features( int obj_idx );
  /**
   * Return the indices of the objects that have the given attribute
   * @param attr_idx the index of the attribute
   * @return the list of objects with the specified attribute
   */
  std::vector<int> get_attribute_objects( int  attr_idx );
  /**
   * Return a string version of the indices of the objects
   * @param obj_idx the index of the object
   * @return a string with the indices of features
   */
  std::string get_string_of_features_by_object( int obj_idx );
  /**
   * Return the indices of the objects that have the given attribute as a string
   * @param attr_idx the index of the attribute
   * @return a string of objects with the specified attribute
   */
  std::string get_string_of_objects_by_attribute( int attr_idx );
  /**
   * Adds an empty object to the matrix
   * @return the index of the new object
   */
  int add_object();
  /**
   * Adds an attribute to a specific object
   * @param obj_idx the index of the object to set the attribute to
   * @param attr_idx the index of the attribute
   * @return true if the feature was successfuly added to the object
   */
  bool add_attribute( int obj_idx, int attr_idx );
  /**
   * Sends to the standard output the binary concept matrix
   */
  void printConceptMatrix();
  /**
   * Takes a binary matrix and loads it into the objects and attributes structures
   * @param bin_matrix a binary matrix containing the objects and their attributes
   * in raw form
   * @param nb_objects the number of objects (rows)
   * @param nb_attributes the number of attributes (columns)
   */
  void load_matrix( int** bin_matrix, int nb_objects, int nb_attributes );
  /**
   * Returns the number of attributes of the matrix
   * @return the number of attributes...
   */
  int get_nb_attributes() const;
  /**
   * Performs a basic search of some index over the index set
   * @param idx_set the set of indices
   * @param idx the index to look for
   * @return true if the index is within the set, false otherwise
   */
  bool contains_index( std::vector<int> idx_set, int idx );
  /**
   * Returns all the indices of the objects
   * @return a vector with all the indices
   */
  std::vector<int> get_all_object_idxs();
  /**
   * Reurns all the indices of the attributes
   * @return a vector with all the indices
   */
  std::vector<int> get_all_attributes_idxs();
  /**
   * Sets the number of attributes
   * @param nb_attributes the number of attribues a.k.a the number of columns of the matrix
   */
  void set_nb_attributes( int nb_attributes );
  /**
   * Adds another limit for the attributes. If the size of the vector is 0, the
   * initial value of 0 is added as the first element.
   */
  void add_attribute_limit( int limit );
  /**
   * Returns the vector of limits
   */
  std::vector<int> getLimits() const;

private:
  /**
   * A map [object_idx=>list(attributes)]
   */
  std::map<int, std::vector<int> > objects;
  /**
   * A map [attribute_idx=>list(objects)]
   */
  std::map<int, std::vector<int> > attributes;
  /**
   * The List of names for the objects (for presentation purposes)
   */
  std::vector<std::string> object_names;
  /**
   * The List of names for the attributes (for presentation purposes)
   */
  std::vector<std::string> attributes_names;
  /**
   * The actual number of objects
   */
  int object_counter;
  /**
   * The total number of attributes_names
   */
  int attributes_size;
  
  std::map<int,std::string> attr_str_cache;
  
  std::map<int,std::string> obj_str_cache;
  /**
   * A vector indicating the limits of the types of attributes
   * E.g., 0,6 means the first kind goes from 0 to 5 and the second, from 6 to attributes_size - 1
   */
  std::vector<int> attributes_limits;
  
};

#endif // CONCEPTMAT_H
