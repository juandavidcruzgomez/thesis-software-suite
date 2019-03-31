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
#ifndef EXPERIMENT_H
#define EXPERIMENT_H

#include <iostream>
#include <ostream>
#include <fstream>

#include <tulip/Graph.h>
#include "clusteringexperiment.h"

class Experiment{
public:
  Experiment( std::string &graph_filename, std::string &raw_comp_patterns, std::string &experiment_name );
  ~Experiment();
  
  void initialize();
  
  void add_experiment( std::string clust_method_name );
  
  void start_experiments(std::ostream &os);
  
  void finish_save_graph(std::string &graph_file, std::ostream &os);
  
  void test_against_gtruth( std::string &gtruth_file, std::ostream &os );
  
  
private:
  tlp::Graph* graph;
  ClusteringExperiment* experiments;
  bool addedGalois;
  std::string raw_comp_patterns;

};

#endif
