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


#include "galoislattice.h"

GaloisLattice::GaloisLattice(ConceptMatrix* cmatrix)
  : cmatrix(cmatrix)
{
  assert( this->cmatrix != 0 );
  //Create root concept (All objects, no attributes)
  root_concept = 0;
  base_concept = 0;
  concept_id_index = 0;

  if( ( root_concept = new Concept( cmatrix ) ) != 0 )
  {
    std::vector<int> obj_idxs = cmatrix->get_all_object_idxs();
    root_concept->set_object_idxs( obj_idxs );
    make_concept_valid( root_concept );
  }
  concept_trie = new trie( root_concept->get_object_indices().size() );

  if( ( base_concept = new Concept( cmatrix ) ) != 0 )
  {
    std::vector<int> attr_idxs = cmatrix->get_all_attributes_idxs();
    base_concept->set_attributes_idxs( attr_idxs );
    make_concept_valid( base_concept );
  }

}

GaloisLattice::~GaloisLattice()
{
  if( root_concept != 0 )
  {
    //Delete all the children
    std::queue<Concept*> pqueue;
    std::set<Concept*> list2del;
    pqueue.push(root_concept);
    while( !pqueue.empty() )
    {
      Concept* actual_concept = pqueue.front();
      pqueue.pop();
      list2del.insert( actual_concept );
      if( actual_concept != 0 )
      {
	      std::vector<Concept*> children = actual_concept->get_children();
	      for( unsigned int i = 0; i < children.size(); ++i )
	      {
	        pqueue.push( children[i] );
	      }
      }
    }
    std::set<Concept*>::iterator set_iter;
    for( set_iter = list2del.begin(); set_iter != list2del.end(); ++set_iter ){
      Concept* conc = *set_iter;
      if( conc != 0 )
      {
	      delete conc;
	      conc = 0;
      }
    }
  }
  if( concept_trie != 0 )
  {
    delete concept_trie;
    concept_trie = 0;
  }
}

void GaloisLattice::make_concept_valid( Concept* concept )
{
  assert( concept != 0 );
  concept->setConceptId( concept_id_index );
  concept_id_index++;
}

std::vector<Concept*> GaloisLattice::find_child( Concept* parent )
{
  trie local_trie(root_concept->get_object_indices().size());
  std::vector<Concept*> result;
  std::vector<int> res_attr = get_res_attributes( parent );
  std::set<int> parent_attr = parent->get_attributes_indices();
  std::set<int> parent_obj = parent->get_object_indices();
  //Create a map of attributes->objects
  std::map<int,std::vector<int> > attr2obj;
  
  for( unsigned int i = 0; i < res_attr.size(); ++i ){
    int actual_idx = res_attr[i];
    std::vector<int> actual_objs_idxs = cmatrix->get_attribute_objects( actual_idx );
    std::vector<int>::iterator it = attr2obj[actual_idx].begin();
    attr2obj[actual_idx].insert( it, actual_objs_idxs.begin(),actual_objs_idxs.end());
  }
  //Add the mapping to the trie
  std::set<tri_node*> candidate_concepts;
  std::map<int,std::vector<int> >::iterator map_iter;
  for( map_iter = attr2obj.begin(); map_iter != attr2obj.end(); ++map_iter ){
    tri_node* cand = local_trie.insert( map_iter->second, map_iter->first );
    candidate_concepts.insert(cand);
  }
  //Extract the concepts from the trie
  std::set<tri_node*>::iterator concept_trie_iter;
  for( concept_trie_iter = candidate_concepts.begin(); concept_trie_iter != candidate_concepts.end(); concept_trie_iter++ )
  {
    tri_node* node = *concept_trie_iter;
    std::vector<int> attr_idxs = node->values_list->convert2vector();
    attr_idxs.insert(attr_idxs.end(),parent_attr.begin(),parent_attr.end());
    Concept* conc = new Concept( cmatrix );
    conc->set_attributes_idxs( attr_idxs );
    while( node->key != -1 )
    {
      //walk in reverse...
      //And take the intersection
      if( parent_obj.count(node->key) != 0 )
      {
	      conc->add_object(node->key);
      }
      node = node->prev;
    }
    if( conc->get_object_indices().size() != 0 ){
      result.push_back(conc);
    }else{
      delete conc;
    }
  }
  return result;
}

std::vector<int> GaloisLattice::get_res_attributes( Concept* concept )
{
  std::vector<int> result;
  int nb_attributes = cmatrix->get_nb_attributes();
  std::set<int> actual_attrib = concept->get_attributes_indices();
  for( int i = 0; i < nb_attributes; ++i )
  {
    if( actual_attrib.count(i) == 0 ){ // !cmatrix->contains_index( actual_attrib, i ) ){
      result.push_back(i);
    }
  }
  return result;
}

void GaloisLattice::generate_lattice()
{
  std::vector<Concept*> children_concepts;
  std::queue<Concept*> concepts4process;
  concepts4process.push( root_concept );
  while( concepts4process.size() > 0 )
  {
    /*///DEBUG///
    cout << "-- Concepts to process: " << concepts4process.size() << endl;
    ///DEBUG///*/
    Concept* actual_concept = concepts4process.front();
    //cout << "Parent concept: " << actual_concept->print_concept() << endl;
    concepts4process.pop();
    children_concepts = find_child( actual_concept );
    for( unsigned int i = 0; i < children_concepts.size(); ++i )
    {
      if( children_concepts[i]->is_closed() ){
	      Concept* child_concept = concept_exists( children_concepts[i] );
	      if( child_concept == 0 ){
	        //cout << "--" << children_concepts[i]->print_concept() << endl;
	        //add2trie here!
	        add2trie( children_concepts[i] );
	        concepts4process.push( children_concepts[i] );
	        make_concept_valid( children_concepts[i] );
	        child_concept = children_concepts[i];
	      }else{
	        delete children_concepts[i];
	      }
	      actual_concept->add_child( child_concept );
	      child_concept->add_precedent( actual_concept );
     }else{
	      delete children_concepts[i];
     }
  }
 }
 close_lattice();
}

void GaloisLattice::close_lattice()
{
  std::queue<Concept*> pqueue;
  pqueue.push(root_concept);
  while( !pqueue.empty() )
  {
    Concept* actual_concept = pqueue.front();
    std::vector<Concept*> children = actual_concept->get_children();
    if( children.size() == 0 && !base_concept->equalsTo(*actual_concept) )
    {
      actual_concept->add_child(base_concept);
      base_concept->add_precedent(actual_concept);
    }else{
      for( unsigned int i = 0; i < children.size(); ++i ){
	      pqueue.push( children[i] );
      }
    }
    pqueue.pop();
  }
}

bool GaloisLattice::is_last_concept( std::set< int > attributes )
{
  std::vector<int> attr_idxs = cmatrix->get_all_attributes_idxs();
  unsigned int i = 0;
  while( i < attr_idxs.size() && attributes.find( attr_idxs[i] ) != attributes.end() )
  {
    i++;
  }
  return i == attributes.size();
}

Concept* GaloisLattice::create_end_concept()
{
  Concept* last_concept = new Concept( cmatrix );
  std::vector<int> all_atts = cmatrix->get_all_attributes_idxs();
  last_concept->set_attributes_idxs( all_atts );
  last_concept->setClosing();
  return last_concept;
}

Concept* GaloisLattice::concept_exists( Concept* concept )
{
  Concept* result = 0;
  std::set<int> obj_idxs = concept->get_object_indices();
  std::vector<int> keys(obj_idxs.begin(),obj_idxs.end());
  
  tri_node* the_trie_node = concept_trie->isMember( keys );
  if( the_trie_node != 0 )
  {
    result = global_concept_map[the_trie_node];
  }
  return result;
}

void GaloisLattice::add2trie( Concept* concept )
{
  assert( concept != 0 );
  std::set<int>::iterator set_iter;
  std::set<int> obj_idxs = concept->get_object_indices();
  std::set<int> attr_idxs = concept->get_attributes_indices();
  std::vector<int> keys(obj_idxs.begin(),obj_idxs.end());
  tri_node* the_trie_node;
  for( set_iter = attr_idxs.begin(); set_iter != attr_idxs.end(); set_iter++ )
  {
    the_trie_node = concept_trie->insert( keys, *set_iter );
  }
  assert( the_trie_node != 0 );
  global_concept_map[the_trie_node] = concept;
}

Concept* GaloisLattice::getRootConcept() const
{
  return root_concept;
}
  
Concept* GaloisLattice::getBaseConcept() const
{
  return base_concept;
}

std::string GaloisLattice::print_lattice()
{
    std::stringstream ss;
    std::map<int,int> level_control;
    std::queue<Concept*> proc_q;
    //Concept* root_concept = concepts[0];
    int level = 0;
    int t_level = 0;
    int lcount = 0;
    level_control[level] = 1;//Root concept
    proc_q.push(root_concept);
    while( !proc_q.empty() ){
      Concept* actual = proc_q.front();
      proc_q.pop();
      ss << actual->print_concept();
      lcount++;
      if( lcount == level_control[level] ){
	      ss << std::endl;
      	lcount = 0;
      	level++;
      }else{
	      ss << "\t";
      }
      std::vector<Concept*> children = actual->get_children();
      if( children.size() > 0 ){
	      t_level++;
	      level_control[t_level] = children.size();
      }
      for( unsigned int i = 0; i < children.size(); ++i )
      {
	      proc_q.push( children[i]);
      }
    }
    return ss.str();
}

ConceptMatrix* GaloisLattice::getConceptMatrix()
{
  return cmatrix;
}
