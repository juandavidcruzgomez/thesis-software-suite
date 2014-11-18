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

