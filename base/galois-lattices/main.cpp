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
#include <iostream>

#include "conceptmatrix.h"
#include "galoislattice.h"
#include "importmatrix.h"
#include "latticeexporter.h"

void usage();

int main(int argc, char **argv) {
  
  if( argc < 2 )
  {
    usage();
    return 1;
  }else
  {
    std::string input_filename = argv[1];
    std::string output_filename = argv[2];
    long load_start_time = clock();
    long load_end_time = 0;
    ConceptMatrix* cmat = new ConceptMatrix();
    ImportMatrix import( cmat );
    import.start_import( input_filename );
    load_end_time = clock();
    std::cout << "Loading took " << (float)(load_end_time-load_start_time)/(float)CLOCKS_PER_SEC << " seconds.\n";
    
    long calc_start_time = clock();
    long calc_end_time = 0;
    GaloisLattice* lattice = new GaloisLattice( cmat );
    lattice->generate_lattice();
    calc_end_time = clock();
    std::cout << "Calculating took " << (float)(calc_end_time-calc_start_time)/(float)CLOCKS_PER_SEC << " seconds.\n";

    long export_start_time = clock();
    long export_end_time = 0;
    LatticeExporter expo( lattice );
    expo.export_lattice(output_filename);
    export_end_time = clock();
    std::cout << "Exporting took " << (float)(export_end_time-export_start_time)/(float)CLOCKS_PER_SEC << " seconds.\n";
    std::cout << "Done." << std::endl;
    
    delete cmat;
    delete lattice;
    return 0;
  }
}

void usage(){
  std::cerr << "Usage:\n";
  std::cerr << "./galois_test <input_file> <output_file>" << std::endl;
}
