#include "importbase.h"

ImportBase::ImportBase( Graph* pgraph, string pattern_property ) 
  : pgraph( pgraph ), pattern_property( pattern_property ), columns(0)
{
  assert( pgraph != 0 && pattern_property != "" );
    //Initialize the properties to be used
  data_vector = pgraph->getProperty<DoubleVectorProperty>(pattern_property);
  node_label = pgraph->getProperty<StringProperty>("node_label");
  
  data_labels = pgraph->getProperty<StringVectorProperty>("data_labels");
}

ImportBase::~ImportBase()
{
}

void ImportBase::set_filename( string filename )
{
  this->filename = filename;
}

void ImportBase::read_file( int process_header )
{
  //Assert the file name was set and the graph is not null
  assert( this->filename != "" && pgraph != 0 );
  start_reading( process_header );
}

void ImportBase::start_reading( int process_header )
{
  cout << "start reading" <<endl;
  char line[BUFFER];
  int gcount = 0;
  fstream infile;
  infile.open(filename.c_str(), ios::in);
  memset(line, '\0', BUFFER);
  unsigned int size = pgraph->numberOfNodes();
  long* node_index = new long[size];
  //cout << "Size: " << size << endl;
  if ( infile.is_open() )
  {
    //Process each line according to the file definition
    int lines = 0;
    unsigned int node = 0;
    while ( !infile.eof() && node < size )
    {
      //Try to extract the number of columns from the first line
      if( process_header == 1 && lines == 0 )
      {
        //process the header line
        infile.getline(line, BUFFER);
        gcount = infile.gcount();
        lines++;
        process_header_line( line );
      }
      if( node == 0 ){
        node_index[node] = gcount;
      }
      else
      {
        node_index[node] = gcount + node_index[node-1];
      }
     // cout << "Node " << node << " at " << node_index[node] << endl;
      node++;
      memset(line, '\0', BUFFER);
      //Process line and extract columns
      infile.getline(line, BUFFER);
      gcount = infile.gcount();
      lines++;
    }
    //Clear all the fail bits (eof bit has been set by this point)
    infile.clear();
    //Go throughout all the pointers for assuring the order...
    Iterator<tlp::node>* node_iter = pgraph->getNodes();
    while( node_iter->hasNext() )
    {
      tlp::node n = node_iter->next();
      int index = n.id;
      infile.seekg (node_index[index],infile.beg);
      infile.getline( line, BUFFER);
      //Process the line
      process_line( line, n );
    }
    delete node_iter;
  }
  delete[] node_index;
}



void ImportBase::process_line( char* line, tlp::node& n )
{
  assert( line != 0 );
  //The first element of the line is the name of the node, so it isn't nedded
  char* splitted = NULL;
  splitted = strtok(line,"\t ");
  int column = 0;
  vector<double> elements;
  while ( splitted != NULL ) {
    if ( column > 0 ) {
      double element = atoi( splitted );
      elements.push_back( element );
    }else{
      node_label->setNodeValue( n, splitted );
    }
    column++;
    splitted = strtok(NULL,"\t ");
  }
  data_vector->setNodeValue( n, elements );
}

void ImportBase::process_header_line( char* line )
{
  assert( line != 0 );
  string process;
  char* splitted = NULL;
  splitted = strtok(line,"\t ");
  vector<string> labels;
  while ( splitted != NULL ) {
      labels.push_back( splitted );
      columns++;
      splitted = strtok(NULL,"\t ");
  }
  data_labels->setAllNodeValue( labels );
}

unsigned int ImportBase::get_nb_columns() const
{
  return columns;
}
