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


#include "lightdlinkdlist.h"

LightDLinkdList::LightDLinkdList()
{
  root = 0;
  p2last_node = root;
  list_size = 0;
}

LightDLinkdList::LightDLinkdList( int value )
{
  root = new list_node_t(value);
  p2last_node = root;
  list_size = 1;
}

LightDLinkdList::~LightDLinkdList()
{
  list_node_t* actual_node = root;
  while( actual_node != 0 )
  {
    list_node_t* next_node = actual_node->next;
    delete actual_node;
    actual_node = next_node;
  }
}

list_node_t* LightDLinkdList::getRoot()
{
  return root;
}

list_node_t* LightDLinkdList::getTail()
{
  return root->next;
}

list_node_t* LightDLinkdList::getLastElement()
{
  return p2last_node;
}

list_node_t* LightDLinkdList::addElement( int value )
{
  list_node_t* node = new list_node_t(value);
  p2last_node->next = node;
  node->prev=p2last_node;
  p2last_node = node;
  list_size++;
  return p2last_node;
}

list_node_t* LightDLinkdList::addElementAt( unsigned int index, int value )
{
  list_node_t* result = 0;
  if( index >= 0 && index < list_size )
  {
    unsigned int i = 0;
    list_node_t* new_node = new list_node_t( value );
    list_node_t* actual_node = root;
    while( actual_node != 0 && i != index )
    {
      actual_node = actual_node->next;
      i++;
    }
    if( actual_node->prev == 0 )
    {//If actual node is the root
      root = new_node;
      root->next = actual_node;
      actual_node->prev = root;
      list_size++;
    }else
    {//If actual node is the last node
      list_node_t* prev_node = actual_node->prev;
      prev_node->next = new_node;
      new_node->prev=prev_node;
      new_node->next=actual_node;
      list_size++;
    }
    result = new_node;
  }
  return result;
}

list_node_t* LightDLinkdList::searchFirstElement( int value )
{
  list_node_t* actual_node = root;
  while( actual_node != 0 && actual_node->value != value )
  {
    actual_node = actual_node->next;
  }
  return actual_node;
}

bool LightDLinkdList::removeNode( list_node_t* to_remove )
{
  bool result = false;
  if( to_remove != 0 )
  {
    list_node_t* actual_node = root;
    while( actual_node != 0 && actual_node != to_remove )
    {
      actual_node = actual_node->next;
    }
    if( actual_node != 0 )
    {
      if( actual_node == root )
      {
	      root = root->next;
      	root->prev = 0;
      }else{
      	list_node_t* prev_node = actual_node->prev;
      	list_node_t* next_node = actual_node->next;
      	prev_node->next=next_node;
      	if( next_node != 0 )
      	{ //Otherwise this node becomes the last node
      	  next_node->prev=prev_node; 
      	}else{
      	  p2last_node = prev_node;
      	}
      }
      delete actual_node;
      actual_node = 0;
      list_size--;
      result = true;
    }
  }
  return result;
}

bool LightDLinkdList::removeNodeAt( unsigned int index )
{
  bool result = false;
  unsigned int i = 0;
  if( index >= 0 && index < list_size )
  {
    list_node_t* actual_node = root;
    while( actual_node != 0 && i != index )
    {
      actual_node = actual_node->next;
      i++;
    }
    result = removeNode( actual_node );
  }
  return result;
}

unsigned int LightDLinkdList::getListSize() const
{
  return list_size;
}

std::string LightDLinkdList::toString()
{
  std::stringstream ss;
  list_node_t* actual_node = root;
  while( actual_node != 0 )
  {
    ss << actual_node->value << " ";
    actual_node = actual_node->next;
  }
  return ss.str();
}

std::vector<int> LightDLinkdList::convert2vector()
{
  std::vector<int> result;
  list_node_t* actual_node = root;
  while( actual_node != 0 )
  {
    result.push_back( actual_node->value );
    actual_node = actual_node->next;
  }
  return result;
}
