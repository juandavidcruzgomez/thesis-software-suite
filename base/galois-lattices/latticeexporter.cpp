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

