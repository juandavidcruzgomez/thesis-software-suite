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
