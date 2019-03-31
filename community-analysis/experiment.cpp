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
#include "experiment.h"

Experiment::Experiment( std::string &graph_filename, std::string &raw_comp_patterns, std::string &experiment_name )
{
  graph = loadGraph( graph_filename.c_str() );
  experiments = new ClusteringExperiment( graph, raw_comp_patterns, experiment_name );
  addedGalois = false;
  this->raw_comp_patterns = raw_comp_patterns;
}

Experiment::~Experiment()
{
  if( graph != 0 )
  {
    delete graph;
    graph = 0;
  }
  if( experiments != 0 )
  {
    delete experiments;
    experiments = 0;
  } 
}


void Experiment::initialize()
{
  //Import the patterns
  experiments->import_patterns();
}

void Experiment::add_experiment( std::string clust_method_name )
{
  if( clust_method_name == "LOUVAIN" )
  {
    experiments->add_experiment("Louvain",LOUVAIN);
  }else if( clust_method_name == "POV" )
  {
    experiments->add_experiment("PoV",POV);
  }else if( clust_method_name == "KMEANS" )
  {
    experiments->add_experiment("k-means",KMEANS);
  }else if( clust_method_name == "GALOIS" )
  {
    addedGalois = true;
    int rows = graph->numberOfNodes();
    Matrix* composition_aff_mat = loadPartitionMatrix(raw_comp_patterns, rows );
    experiments->initialize_lattice( composition_aff_mat, 0 );
    experiments->add_experiment("Galois",GALOIS);
  }else
  {
    experiments->add_experiment("Louvain",LOUVAIN);
  }  
}

void Experiment::start_experiments( std::ostream &os )
{
  experiments->start_resgistered_experiments(os);
  experiments->calculate_statistics(os);
}

void Experiment::finish_save_graph(std::string &ret_graph_file, std::ostream &os)
{
  saveGraph( graph, ret_graph_file );
}

void Experiment::test_against_gtruth( std::string &gtruth_file, std::ostream &os )
{
  Matrix* gtruth_matrix = load_gtruth_partition( graph, gtruth_file );
	experiments->set_ground_truth( gtruth_matrix );
  experiments->calculate_against_ground_truth(os);
  delete gtruth_matrix;
}

