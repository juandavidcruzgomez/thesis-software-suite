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


#include "latticeexporter.h"

LatticeExporter::LatticeExporter(GaloisLattice* lattice)
  : lattice(lattice)
{
  assert( this->lattice != 0 );
}

LatticeExporter::~LatticeExporter()
{}


void LatticeExporter::export_lattice( std::string filename )
{
  std::filebuf file;
  std::vector<std::pair<int,int> > edges;
  std::map<int,int> nodes;
  file.open(filename.c_str(), std::ios::out );
  std::ostream os(&file);
  std::queue<Concept*> pqueue;
  pqueue.push( lattice->getRootConcept() );
  int node_count = 0;
  while( !pqueue.empty() )
  {
    Concept* actual_concept = pqueue.front();
    int concept_id = actual_concept->getConceptId();
    pqueue.pop();
    if( nodes.count( concept_id ) == 0 && concept_id != -1 )
    {
      nodes[concept_id] = node_count;
      os << "node\t" << concept_id << "\t\"" << actual_concept->print_concept() << "\"" << std::endl;
      node_count++;
    }
    //Get the children
    std::vector<Concept*> children = actual_concept->get_children();
    for( unsigned int i = 0; i < children.size(); ++i )
    {
      std::pair<int,int> edge = std::pair<int,int>( concept_id, children[i]->getConceptId() );
      if( find( edges.begin(), edges.end(), edge ) == edges.end() )
      {
	      edges.push_back(edge);
      }
      pqueue.push( children[i] );
    }
  }
  //Now, write the edges
  for( unsigned int i = 0; i < edges.size(); ++i )
  {
    std::pair<int,int> p = edges[i];
    int source = p.first;
    int target = p.second;
    if( source != -1 && target != -1 )
    {
      os << "edge\t" << source << "\t" << target << std::endl;
    }
  }
  file.close();
}

