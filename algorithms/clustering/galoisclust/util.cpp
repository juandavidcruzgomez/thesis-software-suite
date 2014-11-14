#include "util.h"


void get_affiliation_matrix( Matrix* dest_matrix, Graph* the_graph )
{
  assert( the_graph != 0 && dest_matrix != 0 && dest_matrix->getNrows() == (int)the_graph->numberOfNodes() && dest_matrix->getNcols() == (int)the_graph->numberOfSubGraphs() );
  //Clean the matrix
  dest_matrix->set_all_zeros();
  int gcount = 0;
  Iterator<Graph*>* sub_graphs = the_graph->getSubGraphs();
  while( sub_graphs->hasNext() )
  {
    Graph* subg = sub_graphs->next();
    Iterator<node>* node_iter = subg->getNodes();
    while( node_iter->hasNext() )
    {
      node n = node_iter->next();
      dest_matrix->setElement( n.id, gcount, 1 );
    }
    delete node_iter;
    gcount++;
  }
  delete sub_graphs;
}

void populate_object_attr_matrix( ConceptMatrix* matrix, Matrix* affiliation_matrix )
{
  assert( matrix != 0 && affiliation_matrix != 0 );
  int columns = affiliation_matrix->getNcols();
  int rows = affiliation_matrix->getNrows();
  matrix->set_nb_attributes( columns );
  for( int i = 0; i < rows; ++i )
  {
    int obj_idx = matrix->add_object();
    for( int j = 0; j < columns; ++j )
    {
      float value = affiliation_matrix->getElement(i,j);
      if(  value != 0 )
      {
	matrix->add_attribute(obj_idx,j);
      }
    }
  }
}

Matrix* loadPartitionMatrix( string filename, int rows ){
  Matrix* result = 0;
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
	  processLine(line, lines - 1, result );
	}else{
	  //Create the matrix...
	  char* splitted = NULL;
	  splitted = strtok(line,"\t ");
	  int column = 0;
	  while( splitted != NULL ){
	    column++;
	    splitted = strtok(NULL,"\t ");
	  }
	  result = new Matrix( rows, column, COLUMN_MAJOR );
	  assert( result != 0 );
	}
	memset(line, '\0', gcount);
	lines++;
      }
      infile.close();
      cout << "File closed...\n";
    }else{
      cerr << "Error loading the file." << endl;
    }
  }
  return result;
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

Matrix* load_gtruth_partition( Graph* the_graph, string filename )
{
  //The format is a list of groups and the indeces of nodes within it:
  //group0 0,1,2,19,31 ...
  Matrix* result = 0;
  if( filename.size() > 0 ){
    int* included = new int[the_graph->numberOfNodes()];
    char line[BUFFER];
    fstream infile;
    infile.open(filename.c_str(), ios::in);
    memset(line, '\0', BUFFER);
    //get the number of lines aka the number of groups
    if( infile.is_open() ){
      int lines = 0;
      while( !infile.eof() ){
	infile.getline(line, BUFFER);
	lines++;
      }
      result = new Matrix( the_graph->numberOfNodes(), lines, COLUMN_MAJOR );
      result->set_all_zeros();
      infile.clear();
      infile.seekp(0);
      memset(line, '\0', BUFFER);
      lines = 0;
      int gcount = 0;
      while( !infile.eof() ){
	infile.getline(line, BUFFER);
	gcount = infile.gcount();
	processGroupLine( line, lines, included, result );
	memset(line, '\0', gcount);
	lines++;
      }
      infile.close();
      cout << "File closed...\n";
    }
    delete[] included;
  }
  return result;
}

void processGroupLine( char* line, int col, int* set_idx, Matrix* dest )
{
  if( line != NULL && set_idx != 0 ){
    //The first element of the line is the name of the node, so don't nedded
    string process;
    char* splitted = NULL;
    splitted = strtok(line,"\t ");
    int column = 0;
    while( splitted != NULL ){
      if( column > 0 ){
	int row = atoi( splitted );
	if( set_idx[row] == 0 )
	{
	  dest->setElement( row, col, 1 );
	  set_idx[row] = 1;
	}
      }
      column++;
      splitted = strtok(NULL,"\t ");
    }
  }
}