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
#include <iostream>
#include <tulip/Graph.h>

#include "utility.h"
#include "importbase.h"
#include "louvain.h"
#include "povclustering.h"
#include "pagerank.h"
#include "centralitybased.h"
#include "generalkmeans.h"
#include "partitionsimilarity.h"
#include "basicentropy.h"

using namespace std;
using namespace tlp;

int main( int argc, char** argv )
{
  /*// File parameters
    // Input graph
    //string graph_filename = "/home/juancrug/workspace/CommunityAnalysis/tests/cuisine_graph_file.tlp";
    string graph_filename = argv[1];
    // Table (patterns) input
    //string filename = "/home/juancrug/workspace/CommunityAnalysis/tests/blogs_cuisine_red.txt";
    string filename = argv[2];
    // Resulting graph
    //string ret_graph_filename = "/home/juancrug/workspace/CommunityAnalysis/tests/cuisine_graph_file_result.tlp";
    string ret_graph_filename = argv[3];
    // Load the graph
    Graph* graph = loadGraph( graph_filename.c_str() );
    ImportBase* import = new ImportBase( graph, "data_vector" );
    import->set_filename( filename );
    import->read_file( 1 );
    
    Graph* subg = graph->addCloneSubGraph();
    cout << "Calculating partition using Louvain: " << endl;
    Louvain lou( subg, 250, 10E-5, "structural" );
    lou.execute_algorithm();
    int louvain_communities = subg->numberOfSubGraphs();
    cout << "Final partition contains " << louvain_communities << " communities." << endl;
    //Save the graph
    saveGraph( graph, ret_graph_filename );*/
  if( argc < 4 )
  {
    /*string graph_filename = "/home/juancrug/Documents/Romain/wiki.tlp";
    string ret_graph_filename = "/home/juancrug/Documents/Romain/wiki_clust.tlp";
    Graph* graph = loadGraph( graph_filename.c_str() );
    Louvain lou( graph, 250, 10E-5, "structural" );
    lou.execute_algorithm();
    int louvain_communities = graph->numberOfSubGraphs();
    cout << "Final partition contains " << louvain_communities << " communities." << endl;
    saveGraph( graph, ret_graph_filename );*/
    cerr << "The number of arguments is not valid. Use:\nanalysistest <input graph filename> <input patterns filename> <output graph filename>" <<endl;
    return 1;
  }else{
    // File parameters
    // Input graph
    //string graph_filename = "/home/juancrug/workspace/CommunityAnalysis/tests/cuisine_graph_file.tlp";
    string graph_filename = argv[1];
    // Table (patterns) input
    //string filename = "/home/juancrug/workspace/CommunityAnalysis/tests/blogs_cuisine_red.txt";
    string filename = argv[2];
    // Resulting graph
    //string ret_graph_filename = "/home/juancrug/workspace/CommunityAnalysis/tests/cuisine_graph_file_result.tlp";
    string ret_graph_filename = argv[3];
    // Load the graph
    Graph* graph = loadGraph( graph_filename.c_str() );
    // Load the patterns as a property
    // Name the property
    string pattern_property = "data_vector";
    ImportBase* import = new ImportBase( graph, pattern_property );
    import->set_filename( filename );
    import->read_file( 1 );
    // Set the experiments up
    // Create one clone graph for each community detection experiment
    //string experiments_name[] = {"louvain","povclustering","centralitybased_lou","centralitybased_pov","dm_lou","dm_pov"};
    // k-means entropy tests
    /*map<string, BasicEntropy*> sub_groups_ent_map;
    map<string, Graph*> sub_groups_map;
    int nb_nodes = graph->numberOfNodes();
    for( int i = 0; i < nb_nodes; ++i )
    {
      stringstream name;
      name << "kmeans_" << (i+1);
      sub_groups_map[name.str()] = graph->addCloneSubGraph();
      sub_groups_map[name.str()]->setName( name.str() );
      sub_groups_ent_map[name.str()] = new BasicEntropy( sub_groups_map[name.str()], pattern_property );
    }
    map<string, Graph*>::iterator sub_groups_map_iter;
    int k = 1;
    cout << "k\tDensity\tEntropy" << endl;
    for( sub_groups_map_iter = sub_groups_map.begin(); sub_groups_map_iter != sub_groups_map.end(); ++sub_groups_map_iter )
    {
      GeneralKMeans kmeans( sub_groups_map_iter->second, 100, 1E-5, "kmeans_based", pattern_property, k );
      kmeans.execute_algorithm();
      double ent = sub_groups_ent_map[sub_groups_map_iter->first]->calculatePartitionEntropy();
      double dens = edge_density( sub_groups_map_iter->second );     
      cout << k << "\t" << dens << "\t" << ent << endl;
      k++;
    }*/
    
    /*map<string, BasicEntropy*> sub_groups_ent_map;
    map<string, Graph*> sub_groups_map;
    int nb_nodes = graph->numberOfNodes();
    for( int i = 0; i < nb_nodes; ++i )
    {
      stringstream name;
      name << "pagerank_" << (i+1);
      sub_groups_map[name.str()] = graph->addCloneSubGraph();
      sub_groups_map[name.str()]->setName( name.str() );
      sub_groups_ent_map[name.str()] = new BasicEntropy( sub_groups_map[name.str()], pattern_property );
    }
    map<string, Graph*>::iterator sub_groups_map_iter;
    int k = 1;
    cout << "k\tDensity\tEntropy" << endl;
    for( sub_groups_map_iter = sub_groups_map.begin(); sub_groups_map_iter != sub_groups_map.end(); ++sub_groups_map_iter )
    {
      CentralityBased cent_clust( sub_groups_map_iter->second, 100, 1E-5, "cent_based", PAGERANK, k );
      cent_clust.execute_algorithm();
      double ent = sub_groups_ent_map[sub_groups_map_iter->first]->calculatePartitionEntropy();
      double dens = edge_density( sub_groups_map_iter->second );     
      cout << k << "\t" << dens << "\t" << ent << endl;
      k++;
    }*/
    
    string experiments_name[] = {"louvain","povclustering","pagerank","kmeans"};
    map<string, Graph*> sub_groups_map;
    map<string, BasicEntropy*> sub_groups_ent_map;
    for( int i = 0; i < 4; i++ )
    {
      sub_groups_map[experiments_name[i]] = graph->addCloneSubGraph();
      sub_groups_map[experiments_name[i]]->setName( experiments_name[i] );
      sub_groups_ent_map[experiments_name[i]] = new BasicEntropy( sub_groups_map[experiments_name[i]], pattern_property );
    }
    // Now, the methods:
    // Louvain
    cout << "Calculating partition using Louvain: " << endl;
    Louvain lou( sub_groups_map["louvain"], 250, 10E-5, "structural" );
    lou.execute_algorithm();
    int louvain_communities = sub_groups_map["louvain"]->numberOfSubGraphs();
    cout << "Final partition contains " << louvain_communities << " communities." << endl;
    // PoV Clustering
    cout << "Calculating partition using PoV Clustering: " << endl;  
    PoVClustering pov( sub_groups_map["povclustering"], 250, 10E-5, "mixed_partition", pattern_property );
    pov.execute_algorithm();
    int pov_communities = sub_groups_map["povclustering"]->numberOfSubGraphs();
    color_partitions( sub_groups_map["povclustering"] );
    cout << "Final partition contains " << pov_communities << " communities." << endl;
    // Centrality based - Louvain size
    cout << "Calculating partition using Kmeans like using PageRank: " << endl;
    CentralityBased cent_clust( sub_groups_map["pagerank"], 100, 1E-5, "cent_based", PAGERANK, 109 );
    cent_clust.execute_algorithm();
    clean_partition( sub_groups_map["pagerank"] );
    color_partitions( sub_groups_map["pagerank"] );
    int pr_lou_communities = sub_groups_map["pagerank"]->numberOfSubGraphs();
    cout << "Final partition contains " << pr_lou_communities << " communities." << endl;
    // Data mining - lou size
    cout << "Calculating partition using Kmeans: " << endl;
    GeneralKMeans kmeans( sub_groups_map["kmeans"], 100, 1E-5, "kmeans_based", pattern_property, 64 );
    kmeans.execute_algorithm();
    clean_partition( sub_groups_map["kmeans"] );
    color_partitions( sub_groups_map["kmeans"] );
    int dm_lou_communities = sub_groups_map["kmeans"]->numberOfSubGraphs();
    cout << "Final partition contains " << dm_lou_communities << " communities." << endl;
    // Bechmarking part
    // Entropy
    map<string, BasicEntropy*>::iterator entropy_iterator;
    for( entropy_iterator = sub_groups_ent_map.begin(); entropy_iterator != sub_groups_ent_map.end(); ++entropy_iterator )
    {
      cout << "Stats for the group " << entropy_iterator->first << ": " << endl;
      double ent = entropy_iterator->second->calculatePartitionEntropy();
      float dens = edge_density( sub_groups_map[entropy_iterator->first] );      
      cout << "Entropy: " << ent <<  endl;
      cout << "Density: " << dens << endl;
      cout << "--------------------------------------------------" << endl;
    }
    //ARI and NMI
    double ari = 0.0;
    //double nmi = 0.0;
    //Testing ARI, should guive 1
    ari = calculate_ARI( sub_groups_map["louvain"], sub_groups_map["louvain"] );
    cout << "ARI (Louvain vs Louvain): " << ari << endl;
    //Louvain vs PoV
    ari = calculate_ARI( sub_groups_map["louvain"], sub_groups_map["povclustering"] );
    //nmi = calculate_NMI( sub_groups_map["louvain"], sub_groups_map["povclustering"] );
    cout << "ARI (Louvain vs PoV): " << ari << endl;
    //cout << "NMI (Louvain vs PoV): " << nmi << endl;
    //Louvain vs Kmeans
    ari = calculate_ARI( sub_groups_map["louvain"], sub_groups_map["kmeans"] );
    cout << "ARI (Louvain vs k-means(lou)): " << ari << endl;
    //Louvain vs Pagerank
    ari = calculate_ARI( sub_groups_map["louvain"], sub_groups_map["pagerank"] );
    cout << "ARI (Louvain vs pagerank (lou)): " << ari << endl;
    //PoV vs Kmeans
    ari = calculate_ARI( sub_groups_map["povclustering"], sub_groups_map["kmeans"] );
    cout << "ARI (PoV vs k-means (lou)): " << ari << endl;
    //Pov vs PageRank
    ari = calculate_ARI( sub_groups_map["povclustering"], sub_groups_map["pagerank"] );
    cout << "ARI (PoV vs pagerank (lou)): " << ari << endl;
    //Kmeans vs PageRank
    ari = calculate_ARI( sub_groups_map["kmeans"], sub_groups_map["pagerank"] );
    cout << "ARI (k-means (lou) vs pagerank (lou)): " << ari << endl;
    //Save the graph
    saveGraph( graph, ret_graph_filename );
    //DataSet dataSet;
    //tlp::exportGraph(newGraph, tmpss, "tlp", dataSet, NULL);
    //fstream out( ret_graph_filename.c_str(), std::fstream::out );
    //exportGraph( graph, out, "tlp", dataSet, NULL );
    delete import;
    delete graph;
  }
  return 0;
}
