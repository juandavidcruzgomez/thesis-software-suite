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


#ifndef CLUSTERINGEXPERIMENT_H
#define CLUSTERINGEXPERIMENT_H

#include <importbase.h>
#include <basicentropy.h>
#include <clusteringbase.h>
#include <partitionsimilarity.h>

#include <louvain.h>
#include <generalkmeans.h>
#include <povclustering.h>

#include <galoislattice.h>


#include <map>
#include <string>
#include <assert.h>

#include <tulip/Graph.h>

#include "util.h"
#include "basicgaloisclustering.h"
#include "latticeexporter.h"

#define LOUVAIN	0
#define POV	1
#define KMEANS	2
#define GALOIS	3

using namespace tlp;
using namespace std;

class ClusteringExperiment
{

public:
  ClusteringExperiment( Graph* _theGraph, string patterns_filename, string global_name );
  ~ClusteringExperiment();
  /**
   * Loads the patterns into the graph
   */
  void import_patterns();
  /**
   * Adds and experiment to execute
   * @param experiment_name the name of the experiment
   * @param type the type of the experiment to execute
   */
  void add_experiment( string experiment_name, int type );
  
  /**
   * Initializes the Galois lattice. The composition matrix can be initialized 
   * using an existing matrix (from an external clustering) or using the 
   * matrix generated from the local k-means algorithm
   * The Louvain algorithm has to be instantiated and executed.
   * @param composition_matrix the affiliation matrix for the composition variable
   * @param structural_index the index of the experiment containing the structural clustering
   */
  void initialize_lattice( Matrix* composition_matrix, int structural_index );
  /**
   * Starts all the registered experiments.
   */
  void start_resgistered_experiments(ostream& os);
  /**
   * Calculate the statistics (entropy and density) of the clusterings.
   */
  void calculate_statistics(ostream& os);
  /**
   * 
   */
  void set_ground_truth( Matrix* _ground_truth );
  /**
   * Calculate the ARI of the partitions against the ground truth
   */
  void calculate_against_ground_truth( ostream& os );

private:
  Graph* theGraph;
  /**
   * Affiliation matrix for computing the ARI for the ground truth
   */
  Matrix* ground_truth;
  
  ImportBase* import;
  
  ConceptMatrix* cmat;
  
  GaloisLattice* lattice;
  
  string pattern_property;
  
  string experiment_name;
  
  map<int, string> experiments_name_map;
  
  map<int, Graph*> sub_groups_map;
  
  map<int, ClusteringBase*> experiments_map;
  
  map<int, BasicEntropy*> sub_groups_ent_map;
  
  map<int, bool> experiments_done;
};

#endif // CLUSTERINGEXPERIMENT_H
