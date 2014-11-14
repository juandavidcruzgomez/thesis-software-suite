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


#ifndef IMPORTMATRIX_H
#define IMPORTMATRIX_H

#define BUFFER 1024

#include <sys/stat.h>
#include <stdio.h>
#include <fstream>
#include <cstring>

#include "generalinc.h"
#include "conceptmatrix.h"

class ImportMatrix
{

public:
  ImportMatrix( ConceptMatrix* cmat );
  ~ImportMatrix();
  /**
   * Starts the importing process of the binary matrix
   * @param filaneme a string containign the path of the file
   */
  void start_import( std::string filename );
  /**
   * Tells whther the file is valid of not
   */
  bool is_valid_file();
  /**
   * Process one line of the file
   * @param line the line to be processed
   * @return the number of columns
   */
  int process_line( char* line );
  
private:
  /**
   * A pinter to the lattice instance
   */
  ConceptMatrix* cmat;
  /**
   * The name of the file containing the matrix
   */
  std::string filename;
};

#endif // IMPORTMATRIX_H
