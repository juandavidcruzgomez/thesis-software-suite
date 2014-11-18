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
