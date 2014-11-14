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


#ifndef LIGHTDLINKDLIST_H
#define LIGHTDLINKDLIST_H

#include <string>
#include <sstream>
#include <vector>

typedef struct list_node
  {
    int value;
    list_node* next;
    list_node* prev;
    list_node( int _value )
    {
      value = _value;
      next = 0;
      prev = 0;
    }
  } list_node_t;

class LightDLinkdList
{
public:
  LightDLinkdList();
  
  LightDLinkdList( int value );
  
  ~LightDLinkdList();
  /**
   * Returns the root of the list
   */
  list_node_t* getRoot();
  /**
   * Returns the tail of the list
   */
  list_node_t* getTail();
  /**
   * Returns the last node from the list
   */
  list_node_t* getLastElement();
  /**
   * Adds a new element to the list. This element is added at the end of the
   * list.
   * @param value the value to be stored in the node
   * @return a pointer to the created node
   */
  list_node_t* addElement( int value );
  /**
   * Adds a node to the list at the given position.
   * @param index the position in the list. Indices go from 0 to n-1
   * @param value the data to fill the new node
   * @return a pointer to the new created node.If the index is greater than
   * the size of the list, the node is not added and returns NULL
   */
  list_node_t* addElementAt( unsigned int index, int value );
  /**
   * Fetch the first occurrence of the given value on the list. If the element
   * does not exist returns NULL.
   * @param value the value to search for
   * @return the first node containing the value or NULL if the element does not exist.
   */
  list_node_t* searchFirstElement( int value );
  /**
   * Remove the given node from the list
   * @param to_remove the node to be removed. from the list
   * @return true if the node was successfully removed, false otherwise (e.g., the
   * node don't exists)
   */
  bool removeNode( list_node_t* to_remove );
  /**
   * Finds the ith node (given by index) from the root and deletes it.
   * @param index the index of the node to delete. Indices go from 0 to n-1
   * @return true if the node was successfully removed, false otherwise (e.g., the
   * node don't exists)
   */
  bool removeNodeAt( unsigned int index );
  /**
   * Returns the size of the list
   */
  unsigned int getListSize() const;
  /**
   * Converts the list to a string object.
   */
  std::string toString();
  /**
   * Convert the list to a vector
   */
  std::vector<int> convert2vector();
  
private:
  /**
   * A pointer to the root node
   */
  list_node_t* root;
  /**
   * A pointer to the last node of the list.
   */
  list_node_t* p2last_node;
  /**
   * The size of the list
   */
  unsigned int list_size;
};

#endif // LIGHTDLINKDLIST_H
