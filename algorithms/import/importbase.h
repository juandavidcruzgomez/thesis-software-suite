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
#ifndef IMPORTBASE_H
#define IMPORTBASE_H

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
