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

