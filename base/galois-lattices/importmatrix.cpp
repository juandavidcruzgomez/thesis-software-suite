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
