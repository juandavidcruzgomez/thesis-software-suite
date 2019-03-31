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


#include "trie.h"

trie::trie( int _trie_max_size )
{
  trie_max_size = _trie_max_size;
  root = new tri_node();
}

trie::~trie()
{
  std::queue<tri_node*> pqueue;
  pqueue.push( root );
  while( !pqueue.empty() )
  {
    tri_node* actual_node = pqueue.front();
    std::map<int,TrieNode*>::iterator node_iter;
    for( node_iter = actual_node->next.begin(); node_iter != actual_node->next.end(); node_iter++ )
    {
      if( node_iter->second != 0 )
      {
	      pqueue.push(node_iter->second);
      }
    }
    pqueue.pop();
    delete actual_node->values_list;
    actual_node->next.clear();
    delete actual_node;
    actual_node = 0;
  }
  
}

tri_node* trie::insert( std::vector< int > keys, int value )
{
  tri_node* actual_node = root;
  tri_node* resulting_node = 0;
  for( unsigned int i = 0; i < keys.size(); ++i )
  {
    if( actual_node->next[keys[i]] == 0 )
    {
      actual_node->next[keys[i]] = new tri_node();
      actual_node->next[keys[i]]->key = keys[i];
      actual_node->next[keys[i]]->prev=actual_node;
    }
    if( i == keys.size() - 1 )
    {
      if( actual_node->next[keys[i]]->values_list == 0 )
      {
	      actual_node->next[keys[i]]->values_list = new LightDLinkdList(value);
      }else{
	      actual_node->next[keys[i]]->values_list->addElement(value);
      }
      resulting_node = actual_node->next[keys[i]];
    }else{
      actual_node = actual_node->next[keys[i]];
    }
  }
  return resulting_node;
}

tri_node* trie::isMember( std::vector<int> keys )
{
  tri_node* result = 0;
  tri_node* actual_node = root;
  unsigned int i = 0;
  while( i < keys.size() && actual_node->next[keys[i]] != 0 )
  {
    actual_node = actual_node->next[keys[i]];
    i++;
  }
  if(i == keys.size() && actual_node->values_list != 0 )
  {
    result = actual_node;
  }
  return result;
}

void trie::deleteNode( std::vector<int> keys )
{}

std::string trie::toString()
{
  std::stringstream ss;
  std::stack<tri_node*> pstack;
  ss << "\\" << std::endl;
  pstack.push( root );
  while( !pstack.empty() )
  {
    tri_node* actual_node = pstack.top();
    pstack.pop();
    if( actual_node->key != -1 )
    {
      ss << actual_node->key;
      if( actual_node->values_list != 0 )
      {
	      ss << " - ("<< actual_node->values_list->getListSize() <<")";
      }
      ss << std::endl;
    }
    for( int i = 0; i < trie_max_size; ++i )
    {
      if( actual_node->next[i] != 0 )
      {
	      pstack.push( actual_node->next[i] );
      }
    }
  }
  return ss.str();
}

tri_node* trie::getRoot() const
{
  return root;
}

int trie::getMaxSize() const
{
  return trie_max_size;
}
