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


#include "basicgaloisclustering.h"

BasicGaloisClustering::BasicGaloisClustering(GaloisLattice* lattice, Graph* pgraph, int iterations, float min_delta, string partition_name_prefix)
  : ClusteringBase( pgraph, iterations, min_delta, partition_name_prefix ), lattice(lattice)
{
  assert( pgraph != 0 && lattice != 0 );
  this->partition_name_prefix = partition_name_prefix == "" ? "DEF_STR" : partition_name_prefix;
  nodes_added = 0;
  if( ( nodes_added = new int[pgraph->numberOfNodes()] ) != 0 ){
    memset( nodes_added, 0, pgraph->numberOfNodes());
  }
  Iterator<node>* node_iter = pgraph->getNodes();
  while( node_iter->hasNext() )
  {
    node n = node_iter->next();
    nodes_map[n.id] = n;
  }
  delete node_iter;
  eps = numeric_limits< float >::epsilon();
  vector<int> limits = lattice->getConceptMatrix()->getLimits();
  composition_attr_limit = 0;
  if( limits.size() > 1 )
  {
    composition_attr_limit = limits[1];
  }
}

BasicGaloisClustering::~BasicGaloisClustering()
{
  if( nodes_added != 0 )
  {
    delete[] nodes_added;
    nodes_added = 0;
  }
}

void BasicGaloisClustering::execute_algorithm()
{
  cout << "Executing the galois lattice based algorithm... " << endl;
  float initial_ent = concept_entropy(lattice->getRootConcept());
  cout << "Initial entropy: " << initial_ent << endl;
  initial_density();
  optimize_communities();
  color_partitions( pgraph );
}

void BasicGaloisClustering::initial_density()
{
  Concept* base_concept = lattice->getBaseConcept();
  queue<Concept*> pqueue;
  pqueue.push(base_concept);
  int concept_count = 0;
  float overall_density = 0;
  while( !pqueue.empty() )
  {
    Concept* actual_concept = pqueue.front();
    vector<Concept*> precedents = actual_concept->get_precendents();
    for( unsigned int i = 0; i < precedents.size(); ++i )
    {
      if( precedents[i]->get_attributes_indices().size() > 1 )
      {
	float dens = concept_density( precedents[i] );
	overall_density += dens;
	pqueue.push( precedents[i] );
	concept_count++;
      }
    }
    pqueue.pop();
  }
  cout << "Processed concepts: " << concept_count << endl;
  cout << "Overall density: " << overall_density << endl;
}

void BasicGaloisClustering::optimize_communities()
{
  //Initialize a map for storing concepts
  map<int, vector<Concept*> > to_fusion;
  //From the base concept, add the concepts of height 1
  Concept* base_concept = lattice->getBaseConcept();
  vector<Concept*> precedents = base_concept->get_precendents();
  for( unsigned int i = 0; i < precedents.size(); ++i )
  {
    //Extract the composition index: this index is gonna be used as a key on the map
    Concept* actual_concept = precedents[i];
    set<int> attr_idxs = actual_concept->get_attributes_indices();
    set<int>::iterator attr_iter;
    if( attr_idxs.size() > 1 )
    {
      attr_iter = attr_idxs.begin();
      int composition_idx = *attr_iter;
      to_fusion[composition_idx].push_back(actual_concept);
    }
  }
  map<int, vector<Concept*> >::iterator concept_iter;
  for( concept_iter= to_fusion.begin(); concept_iter != to_fusion.end(); ++concept_iter )
  {
    vector<int> fusion_idxs = fusion_concepts( concept_iter->second );
    vector<Concept*> fusion_concept;
    for( unsigned int i = 0; i < concept_iter->second.size(); ++i )
    {
      if( find(fusion_idxs.begin(),fusion_idxs.end(),i) == fusion_idxs.end() )
      {
	concept2group( concept_iter->second[i] );
      }else
      {
	fusion_concept.push_back(concept_iter->second[i] );
      }
    }
    concepts2group( fusion_concept );
  }
  assignEdgesToGroups();
  cout << "Clustering done! " << pgraph->numberOfSubGraphs() << " of groups created." << endl;
}

vector< int > BasicGaloisClustering::fusion_concepts( vector< Concept* > to_fusion )
{
  vector<int> result;
  unsigned int n_concepts = to_fusion.size();
  Matrix* dens_mat = new Matrix( n_concepts,n_concepts,COLUMN_MAJOR);
  dens_mat->set_all_zeros();
  int gtzero = 0;
  for( unsigned int i = 0; i < n_concepts; ++i )
  {
    for( unsigned int j = i; j < n_concepts; ++j )
    {
      if( i < j )
      {
	int count = count_inter_edges( to_fusion[i], to_fusion[j] );
	if( count > 0 )
	{
	  dens_mat->setElement(i,j,count);
	  dens_mat->setElement(j,i,count);
	  gtzero++;
	}
      }
    }
  }
  while( gtzero > 0 )
  {
    pair<int,int> index = dens_mat->getMaxElementPos();
    if( index.first != -1 && index.second != -1 )
    {
      result.push_back(index.first);
      result.push_back(index.second);
    }
    //Reduce the matrix
    //Sum all the values from the rows index.first and index.second
    for( unsigned int i = 0; i < n_concepts; ++i )
    {
      if( (int)i != index.first && (int)i != index.second ){
	float first_row_val = -1;
	float second_row_val = -1;
	first_row_val = dens_mat->getElement(index.first,i);
	second_row_val = dens_mat->getElement(index.second,i);
	dens_mat->setElement( i, index.first, (first_row_val+second_row_val) );
	dens_mat->setElement( index.first,i, (first_row_val+second_row_val) );
      }
    }
    dens_mat->remove_row_col( index.second, index.second );
    n_concepts--;
    gtzero = dens_mat->getNrows()*dens_mat->getNcols() - dens_mat->count_elements( 0 );
  }
  delete dens_mat;
  return result;
}

Concept* BasicGaloisClustering::get_fusion_candidate( Concept* first, Concept* nsparent )
{
  assert( first != 0 && nsparent != 0 );
  Concept* result = 0;
  float best_entropy = 1E37f;
  float best_density = 0.0f;
  float entropy = best_entropy;
  float density = best_density;
  //Get the sons of the nsparent
  vector<Concept*> children = nsparent->get_children();
  for( unsigned int i = 0; i < children.size(); ++i )
  {
    Concept* actual_child = children[i];
    if( actual_child->getConceptId() != first->getConceptId() && selected2fusion.count(actual_child->getConceptId()) == 0 ){
      unsigned int inter_edges_count = count_inter_edges( first, actual_child );
      density = (float)inter_edges_count/(float)pgraph->numberOfEdges();
      if( density > best_density )
      {
	entropy = concept_pair_entropy( first, actual_child );
	if( entropy <= best_entropy )
	{
	  best_density = density;
	  best_entropy = entropy;
	  result = actual_child;
	}
      }

    }
  }
  return result;
}

unsigned int BasicGaloisClustering::count_inter_edges( Concept* concept_a, Concept* concept_b )
{
  assert( concept_a != 0 && concept_b != 0 );
  unsigned int inter_edges = 0;
  set<int>::iterator iter_objs_a, iter_objs_b;
  set<int> objs_concept_a = concept_a->get_object_indices();
  set<int> objs_concept_b = concept_b->get_object_indices();
  for( iter_objs_a = objs_concept_a.begin(); iter_objs_a != objs_concept_a.end(); iter_objs_a++ )
  {
    int a_element = *iter_objs_a;
    for( iter_objs_b = objs_concept_b.begin(); iter_objs_b != objs_concept_b.end(); iter_objs_b++ )
    {
      int b_element = *iter_objs_b;
      edge e = pgraph->existEdge( nodes_map[a_element], nodes_map[b_element], false );
      if( pgraph->isElement( e ) )
      {
	inter_edges++;
      }
    }
  }
  return inter_edges;
}

void BasicGaloisClustering::print_lattice()
{
  Concept* root_concept = lattice->getRootConcept();
  queue<Concept*> pqueue;
  pqueue.push(root_concept);
  while( !pqueue.empty() )
  {
    Concept* actual_concept = pqueue.front();
    cout << "Parent concept: " << actual_concept->print_concept() << "(id: " << actual_concept->getConceptId() << ")" << endl;
    cout << "Children: " << endl;
    vector<Concept*> children = actual_concept->get_children();
    for( unsigned int i = 0; i < children.size(); ++i )
    {
      cout << "--->" << children[i]->print_concept() << "(id: " << children[i]->getConceptId() << ")" << endl;
      pqueue.push( children[i] );
    }
    cout << "-----------------------------------------------------------------"<<endl;
    pqueue.pop();
  }
}

void BasicGaloisClustering::concepts2group( vector<Concept*> concepts )
{
  if( concepts.size() != 0 ){
    int node_count = 0;
    set<int>::iterator objs_iter;
    Graph* subg = pgraph->addSubGraph();
    for( unsigned int i = 0; i < concepts.size(); ++i )
    {
      set<int> objs_idxs = concepts[i]->get_object_indices();
      for( objs_iter = objs_idxs.begin(); objs_iter != objs_idxs.end(); objs_iter++ ){
	subg->addNode( nodes_map[*objs_iter] );
	node_count++;
      }
    }
  }
}

void BasicGaloisClustering::concept2group( Concept* concept )
{
  assert( concept != 0 );
  set<int>::iterator objs_iter;
  Graph* subg = pgraph->addSubGraph();
  set<int> objs_idxs = concept->get_object_indices();
  for( objs_iter = objs_idxs.begin(); objs_iter != objs_idxs.end(); objs_iter++ ){
    subg->addNode( nodes_map[*objs_iter] );
  }
}

float BasicGaloisClustering::concept_density( Concept* concept )
{
  assert( concept != 0 );
  float density = 0;
  //Check the edges of the graph
  set<int> object_idxs = concept->get_object_indices();
  Iterator<edge>* edge_iter = pgraph->getEdges();
  while( edge_iter->hasNext() )
  {
    edge e = edge_iter->next();
    int src_id = pgraph->source(e).id;
    int tgt_id = pgraph->target(e).id;
    if( object_idxs.count( src_id ) != 0 && object_idxs.count( tgt_id )!= 0 )
    {
      density++;
    }
  }
  delete edge_iter;
  return density/(float)pgraph->numberOfEdges();
}

float BasicGaloisClustering::concept_pair_entropy( Concept* concept_a, Concept* concept_b )
{
  assert( concept_a != 0 && concept_b != 0 );
  float entropy = 0;
  set<int>::iterator objs_iter;
  set<int> join_concepts_objs = concept_a->get_object_indices();
  set<int> concept_b_idxs = concept_b->get_object_indices();
  join_concepts_objs.insert( concept_b_idxs.begin(), concept_b_idxs.end() );
  map<int,float> attributes_count;
  map<int,float>::iterator attributes_count_iter;
  for( objs_iter = join_concepts_objs.begin(); objs_iter != join_concepts_objs.end(); objs_iter++ )
  {
    vector<int> atts = lattice->getConceptMatrix()->get_object_features( *objs_iter );
    for( unsigned int j = 0; j < atts.size(); ++j )
    {
      int attr_idx = atts[j];
      if( attr_idx >= composition_attr_limit )
      {
	if( attributes_count.count( attr_idx ) == 0 )
	{
	  attributes_count[attr_idx] = 0.0f;
	}
	attributes_count[attr_idx] += 1.0f;
      }
    }
  }
  for( attributes_count_iter = attributes_count.begin(); attributes_count_iter != attributes_count.end(); ++attributes_count_iter )
  {
    float p = attributes_count_iter->second/(float)join_concepts_objs.size();
    if( p > 0 && p < 1 )
    {
      entropy += p * log( p ) + ( 1.0f - p ) * log( 1.0f - p );
    }
  }
  return entropy < 0 ? -entropy : entropy;
}

float BasicGaloisClustering::concept_entropy( Concept* concept )
{
  assert( concept != 0 );
  float entropy = 0.0f;
  //Get the objects contained in the concept
  set<int>::iterator objs_iter;
  set<int> object_idxs = concept->get_object_indices();
  //Get the attributes of each object (not only the attrbiutes of the concept)
  map<int,float> attributes_count;
  map<int,float>::iterator attributes_count_iter;
  for( objs_iter = object_idxs.begin(); objs_iter != object_idxs.end(); objs_iter++ )
  {
    vector<int> atts = lattice->getConceptMatrix()->get_object_features( *objs_iter );
    for( unsigned int j = 0; j < atts.size(); ++j )
    {
      int attr_idx = atts[j];
      if( attr_idx >= composition_attr_limit )
      {
	if( attributes_count.count( attr_idx ) == 0 )
	{
	  attributes_count[attr_idx] = 0.0f;
	}
	attributes_count[attr_idx] += 1.0f;
      }
    }
  }
  for( attributes_count_iter = attributes_count.begin(); attributes_count_iter != attributes_count.end(); ++attributes_count_iter )
  {
    float p = attributes_count_iter->second/(float)object_idxs.size();
    if( p > 0 && p < 1 )
    {
      entropy += p * log( p ) + ( 1.0f - p ) * log( 1.0f - p );
    }
  }
  return entropy < 0 ? -entropy : entropy;
}

float BasicGaloisClustering::calculate_entropy( Concept* concept, int min_objects, int min_features )
{
  assert( concept != 0 );
  return 1E36;
}
