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


#ifndef TRIE_H
#define TRIE_H

#include <vector>
#include <queue>
#include <stack>
#include <string>
#include <sstream>
#include <assert.h>
#include <map>

#include "lightdlinkdlist.h"

#define _ID_NLEAVE_ -1

typedef struct TrieNode
{
  int key;
  unsigned int max_size;
  LightDLinkdList* values_list;
  std::map<int,TrieNode*> next;
  TrieNode* prev;
  TrieNode()
  {
    key = _ID_NLEAVE_;
    values_list = 0;
    prev = 0;
  }
} tri_node;

class trie
{
public:
  /**
   * Constructor
   * Here the trie is initialized.
   */
  trie(int _trie_max_size);
  /**
   * Destructor
   */
  ~trie();
  /**
   * Inserts a new node into the trie. If the node with the key keys exists, 
   * then the value is included into the value lists.
   * @param keys a vector of integers representing the keys of the node.
   * @param value the value to store at the leaf. If the leaf does exist, then 
   * the value will be add to the list of values associated with this key
   */
  tri_node* insert( std::vector<int> keys, int value );
  /**
   * Checks whether the given keys exist in the trie or not.
   * @param keys the keys to search
   * @return true if the keys are in the trie, false otherwise
   */
  tri_node* isMember( std::vector<int> keys );
  /**
   * Removes a leaf node from the trie. Is this necessary?
   * @param keys the key vector of the node to remove.
   */
  void deleteNode( std::vector<int> keys );
  /**
   * Puts the trie into a string
   */
  std::string toString();
  /**
   * Returns the root of the trie
   */
  tri_node* getRoot() const;
  /**
   * Returns the max number of children of the trie
   */
  int getMaxSize() const;
  
private:
  tri_node* root;
  /**
   * Maximum number of children
   */
  int trie_max_size;
};

#endif // TRIE_H
