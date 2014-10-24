#ifndef __IMPORTBASE_H__
#define __IMPORTBASE_H__

#include <sys/stat.h>
#include <stdio.h>

#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <cassert>

#include <tulip/Graph.h>
#include <tulip/DoubleProperty.h>
#include <tulip/StringProperty.h>

#define BUFFER 4096


using namespace std;
using namespace tlp;

class ImportBase
{
public:
  ImportBase( Graph* pgraph, string pattern_property );
  virtual ~ImportBase();
  /**
   * Set the name of the file to be loaded. It also checks if the file
   * already exists.
   * @param filename the name of the file
   */
  void set_filename( string filename );
  /**
   * Reads and loads the file into memory. To do this the target graph has to 
   * be instantiated (i.e., not null)
   * @param process_header whether the file has a header to process ot not
   */
  void read_file( int process_header );
  /**
   * Return the number of features. Remember that the first column contains the 
   * name of the node, so it cannot be count.
   */
  unsigned int get_nb_columns() const;
  
protected:
  /**
   *
   * @param process_header whether the file has a header to process ot not
   */
  void start_reading( int process_header );
  
  void process_line( char* line, tlp::node& n );
  
  void process_header_line( char* line );
  
protected:
  Graph* pgraph;
  string filename;
  string pattern_property;
  
  unsigned int columns; 
  
  DoubleVectorProperty* data_vector;
  StringProperty* node_label;
  StringVectorProperty* data_labels;
};

#endif
