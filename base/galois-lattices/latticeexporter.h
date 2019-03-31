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


#ifndef LATTICEEXPORTER_H
#define LATTICEEXPORTER_H

#include "generalinc.h"
#include "galoislattice.h"

#include <ostream>
#include <fstream>
#include <algorithm>

class LatticeExporter
{

public:
  LatticeExporter( GaloisLattice* lattice );
  ~LatticeExporter();
  /**
   * Export the lattice to a graph file of the form 
   * Node id name
   * .
   * Edge src tgt
   * @param filename the name of the file to store the graph
   */
  void export_lattice( std::string filename );
  
private:
  GaloisLattice* lattice;
};

#endif // LATTICEEXPORTER_H
