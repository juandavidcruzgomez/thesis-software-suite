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
#include <iostream>
#include <ostream>
#include <fstream>

#include <getopt.h>

#include <tulip/Graph.h>
#include "experiment.h"


using namespace std;
using namespace tlp;

void usage(){
  cerr << "This program implements a platform for comparing community\n";
  cerr << "detection algorithms.\n\n";
  cerr << "The files required for this program to run are: a .tlp file\n";
  cerr << "containing the graph, a .txt containing the composition patterns\n";
  cerr << "or a .txt containing a partition from the composition patterns\n";
  cerr << "and a .txt containing the ground truth partition." << endl;
  cerr << "\nREQUIRED ARGUMENTS:\n";
  cerr << "-g\tThe file containing the graph\n";
  cerr << "-c\tThe file contaning the raw composition patterns\n";
  cerr << "-p\tThe file containing the composition partition aff matrix\n";
  cerr << "-n\tThe name of the experiment\n";
  cerr << "\nOPTIONAL ARGUMENTS:\n";
  cerr << "-w\tThe directory to store all the files produced during the experiment\n";
  cerr << "-t\tThe file containing the affiliation matrix with the ground truth\n";
  cerr << "\tpartition. Note that if this file is set, an ARI test will be performed\n";
  cerr << "\tthat if the output file is not provided, the partition will\n";
  cerr << "-e\tA flag indicating whether or not the Galois lattice have to be\n";
  cerr << "\tcreated using the raw patterns insted of the composition partition.\n";
  cerr << "\tNote that the raw composition patterns have had to be set via the -c\n";
  cerr << "\targument.\n\n";
  cerr << "OTHER OPTIONS:\n";
  cerr << "-h\tPrints this information." << endl;
}

int main( int argc, char** argv )
{
  //Check the arguments of the program
  int option;
  //Option -g giving the graph tlp file
  string graph_filename = "";
  //Option -c for the composition patterns: these are the raw patterns
  string raw_comp_patterns = "";
  //Option -p for a partition of the nodes to be used with the Galois algorithm
  string composition_partition = "";
  //Option -n the name of the experiment
  string experiment_name = "";
  //Option -w working directory (where the result files will be placed)
  //If none provided, it will be use the actual dir
  string working_dir = "./";
  //Option -t define a file to use a ground truth
  string gtruth_file = "";
  //Option -e use extended version for building the Galois lattice
  //i.e., use the raw binary features instead of the composition 
  //partition to build the lattice
  int errflag = 0;
  while( (option=getopt(argc, argv, ":ehg:c:p:n:w:t:" ) ) != -1  )
  {
    switch( option )
    {
      case 'g':
	graph_filename = optarg;
	break;
      case 'c':
	raw_comp_patterns = optarg;
	break;
      case 'p':
	composition_partition = optarg;
	break;
      case 'n':
	experiment_name = optarg;
	break;
      case 'w':
	working_dir = optarg;
	break;
      case  't':
	gtruth_file = optarg;
	break;
	break;
      case 'h':
	usage();
	return 0;
	break;
      case ':':
	if( optopt == 'g' || optopt == 'c' || optopt == 'p' || optopt == 'n' || optopt == 'w' || optopt == 't' )
	{
	  cerr << "Option -" << (char)optopt << " requires a valid argument." << endl;
	  errflag++;
	}
	break;
      case '?':
	  cerr << "Unknown option -" << (char)optopt << endl;
	  errflag++;
	break;
      default:
	break;
    }
  }
  if( errflag > 0 )
  {
    usage();
    return 1;
  }else{
    if( graph_filename != "" && composition_partition != "" && raw_comp_patterns != ""  )
    {
      //To store the clustered graph
      string ret_graph_filename = working_dir;
      ret_graph_filename.append("clustered_graph_").append(experiment_name).append(".tlp");
      //To store the resulting lattice
      string export_filename = working_dir;
      export_filename.append("lattice_").append(experiment_name).append(".txt");
      //To store the extended lattice
      string ext_export_filename = working_dir;
      ext_export_filename.append("extended_lattice_").append(experiment_name).append(".txt");
      //Logging
      string log_filename = working_dir;
      log_filename.append("stats_").append(experiment_name).append(".txt");
      // Objects for logging:
      filebuf file;
      file.open(log_filename.c_str(), ios::out );
      ostream os(&file);
      // Name the property
      string pattern_property = "data_vector";
      
      Experiment expe( graph_filename, raw_comp_patterns, experiment_name );
      expe.initialize();
      //Add the experiments
      expe.add_experiment( "LOUVAIN" );
      expe.add_experiment( "KMEANS" );
      expe.add_experiment( "POV" );
      expe.add_experiment( "GALOIS" );
      //Execute the experiments
      expe.start_experiments( os );

      if( gtruth_file != "" )
      {
	      expe.test_against_gtruth( gtruth_file, os );
      }
      
      expe.finish_save_graph(ret_graph_filename, os);
      
      
      os.flush();
      file.close();
      return 0;
    }else{
      usage();
      return 1;
    }
  }
}
