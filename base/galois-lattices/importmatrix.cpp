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


#include "importmatrix.h"

ImportMatrix::ImportMatrix(ConceptMatrix* cmat)
  : cmat( cmat)
{
  assert( this->cmat!= 0 );
  filename = "";
}

ImportMatrix::~ImportMatrix()
{}

void ImportMatrix::start_import( std::string filename )
{
  this->filename = filename;
  int attributes = 0;
  char line[BUFFER];
  int gcount = 0;
  std::fstream infile;
  infile.open(filename.c_str(), std::ios::in);
  memset(line, '\0', BUFFER);
  if ( infile.is_open() )
  {
    while ( !infile.eof() )
    {
      infile.getline(line, BUFFER);
      if( gcount == 0 ){
	      attributes = process_line( line );
      }else{
	      process_line( line );
      }
      memset(line, '\0', BUFFER);
      gcount++;
    }
    cmat->set_nb_attributes( attributes );
  }
}
  
bool ImportMatrix::is_valid_file()
{
  return true;
}

int ImportMatrix::process_line( char* line )
{
  assert( line != 0 );
  if( *line != '\0' )
  {
    //Create the next object
    int obj_idx = cmat->add_object();
    char* splitted = NULL;
    splitted = strtok(line,"\t ");
    std::vector<double> elements;
    int column = 0;
    while ( splitted != NULL ) {
      if( strcmp( splitted, "1" ) == 0 )
      {
	      cmat->add_attribute( obj_idx, column );
      }
      splitted = strtok(NULL,"\t ");
      ++column;
    }
    return column;
  }
  return 0;
}
