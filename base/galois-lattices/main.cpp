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
