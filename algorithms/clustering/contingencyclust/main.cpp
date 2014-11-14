#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <getopt.h>
#include <matrix.h>
#include <basicoperations.h>
#include "CommunityAlgorithm.h"

#define BUFFER 4096

using namespace std;

void loadPartitionMatrix( Matrix* dest, string filename );
void processLine( char* line, int row, Matrix* dest );
void formatAdjacencyMatrix( Matrix* adjMat );
void usage(){
	cerr << "This program implements the second version of the community\n";
	cerr << "detection algorithm. This algorithm uses the idea of\n";
	cerr << "partitioning the contingency matrix created from the structural\n";
	cerr << "and the compositional partitions.\n\n";
	cerr << "The files required for this program to run are two: a text\n";
	cerr << "file containing the structural partition and a text file with\n";
	cerr << "the compositional partition." << endl;
	cerr << "\nREQUIRED ARGUMENTS:\n";
	cerr << "-s\tThe file containing the structural partition\n";
	cerr << "-c\tThe file contaning the compositional partition\n";
	cerr << "-r\tThe number of groups in the structural partition\n";
	cerr << "-d\tThe number of groups in the compositional partition\n";
	cerr << "-n\tThe number of nodes of the graph.\n";
	cerr << "\nOPTIONAL ARGUMENTS:\n";
	cerr << "-t\tSet the test mode on. If this option is activated you\n";
	cerr << "\thave to set the number of groups of the ground truth\n";
	cerr << "\tpartition using the key -g\n";
	cerr << "-o\tThe file to store the resulting partition. Note\n";
        cerr << "\tthat if the output file is not provided, the partition will\n";
	cerr << "\tbe sent to the standard output.\n\n";
	cerr << "OTHER OPTIONS:\n";
	cerr << "-v\tPrints verbose information during the algorithm." << endl;
	cerr << "-h\tPrints this information." << endl;
}


int main( int argc, char** argv ){
	//Check the arguments of the program
        int option;
	//Option -s the file containing the structural partition
        char* structural_file = 0;
	//Option -c the file containing the composition partition
        char* composition_file = 0;
	//Option -o the file to store the resulting partition
	char* output_file = 0;
	//Option -r the number of groups on the structural partition
	int structural_groups = -1;
	//Option -d the number of groups on the composition partition
	int composition_groups = -1;
	//Option -n the number of nodes
	int nodes = -1;
	//Option -v prints information about the process
	int verbose = 0;
	//Option -t sets a groud truth partition for comparing the results
	char* gtruth_file = 0;
	int execute_test = 0;
	//Option -g the number of groups in the ground truth partition
	int gtruth_groups = -1;
        while( (option=getopt(argc, argv, "s:c:o:r:d:n:t:g:vh" ) ) != -1  ){
		switch( option ){
                        case 's':
                                structural_file = optarg;
                        break;
			case 'c':
				composition_file = optarg;
			break;
                        case 'o':
                                output_file = optarg;
                        break;
			case 'r':
				structural_groups = atoi( optarg );
			break;
			case 'd':
				composition_groups = atoi( optarg );
			break;
			case 'n':
				nodes = atoi( optarg );
			break;
			case 'v':
				verbose = 1;
			break;
			case 't':
				gtruth_file = optarg;
				execute_test = 1;
			break;
			case 'g':
				gtruth_groups = atoi( optarg );
			break;
			case 'h':
				usage();
				return EXIT_SUCCESS;
			break;
			case '?':
				if( optopt == 's' || optopt == 'c' || optopt == 'o' || optopt == 'r' || optopt == 'd' || optopt == 'n' || optopt == 't' ){
                                        fprintf( stderr, "Option -%c requires a valid argument\n", optopt );
                                }else if( isprint(optopt) ){
                                        fprintf( stderr, "Unknown option -%c.\n", optopt );
                                }else{
fprintf (stderr, "Unknown option character `\\x%x'.\n", optopt);
                                }
                                usage();
                                return 1;
                        break;
                }
        }
        //fprintf( stdout, "Structural filename: %s, Composition filename: %s, Output filename: %s\n", structural_file, composition_file, output_file );
	if( structural_file != 0 && composition_file != 0 
		&& structural_groups > 0 && composition_groups > 0
		&& nodes > 0 ){
		int m = structural_groups;
        	int n = composition_groups;
        	int k = nodes;
		if( verbose == 1 ){
			cout << "Stating algorithm for " << k << " nodes.\n";
			cout << "The structural partition has " << m << "groups ";
			cout << "and the composition partition has " << n << "groups." << endl;
		}
		//Data loading and matrix creation
		Matrix* structural_part = new Matrix( k, m, COLUMN_MAJOR );
        	Matrix* semantic_part = new Matrix( k, n, COLUMN_MAJOR );
        	if( verbose == 1 )
			cout<< "Loading the structural partition matrix...";
        	loadPartitionMatrix(structural_part, structural_file );
        	if( verbose == 1 )
			cout<< " Done!\nLoading the compsition partition matrix...";
        	loadPartitionMatrix(semantic_part, composition_file);
        	if( verbose == 1 )
			cout<< " Done!" << endl;
		//First part: calculating the ARI
		CommunityAlgorithm algo( structural_part, semantic_part );
        	float ari = algo.ari_index();
		float ent = algo.calculate_total_entropy();
        	cout << "ARI: " << ari << endl;
		cout << "Initial entropy: " << ent << endl;
		cout << "The new partition:" << endl;
		//algo.getContingencyMatrix()->printMatrix();
        	//Matrix* partition = algo.generate_new_partition( NAIVE_PARTITIONING );
		Matrix* partition = algo.generate_new_partition( VARIA_PARTITIONING );
		//Re-test
		CommunityAlgorithm algo2( partition, semantic_part );
		ari = algo2.ari_index();
		ent = algo2.calculate_total_entropy();
        	cout << "New ARI: " << ari << endl;
		cout << "Final entropy: " << ent << endl;
		partition->transpose();
		//partition->printMatrix();
		output_file = 0;
		if( output_file == 0 ){
		  
		  for( int i = 0; i < partition->getNcols(); i++ ){
		    cout << "\tC" << i;
		  }
		  cout << endl;
		  for( int i = 0; i < partition->getNrows(); i++ ){
		    cout << "Node" << i;
		    for( int j = 0; j < partition->getNcols(); j++ ){
		      cout << '\t' << partition->getElement(i,j);
		    }
		    cout << endl;
		  }
		}else{
			//TODO: write to a file
		}
		//partition->printMatrix();

		//If there is a test...
		if( execute_test == 1 ){
			cout << "Comparing two partitions, one used as a ground truth and the other the partition found by the algorithm." << endl;
			if( gtruth_groups > 0 ){
        			Matrix* ground_truth = new Matrix( k, gtruth_groups, COLUMN_MAJOR );
        			loadPartitionMatrix(ground_truth, gtruth_file );
        			CommunityAlgorithm algo_test( partition, ground_truth );
        		algo_test.getContingencyMatrix()->printMatrix();
        		float test_ari = algo_test.ari_index();
        		cout << "ARI: " << test_ari << endl;
			}else{
				cerr << "The flag for testing is set to one but there is a problem with the number of groups of the ground truth partition.\nCannot execute the test." << endl;
			}

		}
		return EXIT_SUCCESS;
	}else{
		usage();
		return 1;
	}
}

void loadPartitionMatrix( Matrix* dest, string filename ){
	assert( dest != 0 );
	if( filename.size() > 0 ){
		char line[BUFFER];
		int gcount = 0;
		fstream infile;
		infile.open(filename.c_str(), ios::in);
		memset(line, '\0', BUFFER);
		if( infile.is_open() ){
			//Read each line of the file to build the graph
			//Process each line according to the file definition
			int lines = 0;
			while( !infile.eof() ){
				infile.getline(line, BUFFER);
				gcount = infile.gcount();
				//The fisrt line is the name of the columns. Not to be processed (at least for this app
				if( lines > 0 ){
					processLine(line, lines - 1, dest );
				}
				memset(line, '\0', gcount);
				//cout << "Readed " << lines <<" lines...\n";
				lines++;
			}
			infile.close();
			cout << "File closed...\n";
		}else{
			cerr << "Error loading the file." << endl;
		}
	}
	
}

void processLine( char* line, int row, Matrix* dest ){
	if( line != NULL ){
		//The first element of the line is the name of the node, so don't nedded
		string process;
		char* splitted = NULL;
		splitted = strtok(line,"\t ");
		int column = 0;
		while( splitted != NULL ){
			if( column > 0 ){
				double element = atoi( splitted );
				dest->setElement( row, column-1, element );
			}
			column++;
			splitted = strtok(NULL,"\t ");
		}

	}
}

void formatAdjacencyMatrix( Matrix* adjMat ){
	assert( adjMat != 0 );
	int rows = adjMat->getNrows();
	int cols = adjMat->getNcols();
	//The header
	for( int i = 0; i < cols; i++ ){
		cout << "\tC" << i;
	}
	cout << endl;
	//The matrix with an additional column
	for( int i = 0; i < rows; i++ ){
		for( int j = 0; j < cols+1; j++ ){
			if( j == 0 ){
				cout << "Node" << i;
			}else{
				cout << "\t" << adjMat->getElement(i, j-1);
			}
		}
		cout << endl;
	}
	
}
