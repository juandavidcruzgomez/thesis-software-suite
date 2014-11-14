/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) 2014  <copyright holder> <email>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
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
