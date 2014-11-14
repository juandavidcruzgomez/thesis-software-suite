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


#ifndef BASICGALOISCLUSTERING_H
#define BASICGALOISCLUSTERING_H

#include <clusteringbase.h>
#include <galoislattice.h>
#include <utility.h>

#include <matrix.h>

#include <queue>
#include <vector>
#include <string.h>
#include <math.h>
#include <limits>

using namespace std;

class BasicGaloisClustering : public ClusteringBase
{

public:
  BasicGaloisClustering( GaloisLattice* lattice, Graph* pgraph, int iterations, float min_delta, string partition_name_prefix );
  ~BasicGaloisClustering();
  
  void execute_algorithm();
private:
  /**
   * Returns the concepts of depth 1 concerned to the structure only
   */
  //vector<Concept*> getStructuralConcepts();
  /**
   * Performs the concept mixing algorithm
   */
  void optimize_communities();
  /**
   * Tries to find a concept candidate that can be mixed with the given concept.
   * Te criterium is that the density should be improved given that the entropy
   * is already 0
   * @param first the first concept of the potential mixture
   * @param nsparent the NON-structural parent concept to be tested
   * @return a candidate concept cof the same height of first or NULL if there 
   * isn't a cadindate.
   */
  Concept* get_fusion_candidate( Concept* first, Concept* nsparent );
  /**
   * Creates a dummy concept by fussioning two concepts. CAUTION: this is not a 
   * concept in the whole sense of a Galois lattice since the closeness is not
   * guaranteed!
   * The idea is to create a structure for computing the entropy and the density
   * easily.
   * @param first the first concept to be added to the dummy concept
   * @param other the other concept to be added
   * @return the dummy concept
   */
  Concept* create_dummy_concept( Concept* first, Concept* other );
  
  void initial_density();
  
  float calculate_entropy( Concept* concept, int min_objects, int min_features );
  /**
   * Measures the entropy of the nodes composing a concept
   * @param concept the cpncept to me measured
   * @return the entropy
   */
  float concept_entropy( Concept* concept );
  /**
   * Measures the density of edges of produced by the nodes included within
   * a concept. 
   * @param concept the concept to be measured
   * @return the density of the concept.
   */
  float concept_density( Concept* concept );
  /**
   * Converts a set of concepts and creates a group within the graph
   */
  void concepts2group( vector<Concept*> concepts );
  /**
   * Converts a concept into a group
   */
  void concept2group( Concept* concept );
  /**
   * Counts the number of edges that can be count in if the two concepts
   * are fused.
   * @param concept_a the first concept
   * @param concept_b the sencond concept
   * @return the number of edges between these concepts
   */
  unsigned int count_inter_edges( Concept* concept_a, Concept* concept_b );
  /**
   * Measures the entropy of the mixed concepts
   */
  float concept_pair_entropy( Concept* concept_a, Concept* concept_b );
  
  void print_lattice();
  /**
   * Merges a list of concepts into one concept, including their parents
   */
  vector<int> fusion_concepts( vector<Concept*> to_fusion );
private:
  GaloisLattice* lattice;
  int* nodes_added;
  map<int,node> nodes_map;
  /**
   * Machine epsilon
   */
  float eps;
  /**
   * Starting index of the attributes corresponding to the composition information
   */
  int composition_attr_limit;
  
  map<int,int> selected2fusion;
};

#endif // BASICGALOISCLUSTERING_H
