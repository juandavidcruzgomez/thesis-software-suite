/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) 2012  Juan David Cruz Gomez <email>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#ifndef POVGRAPHOBSERVER_H
#define POVGRAPHOBSERVER_H

#include <tulip/TlpTools.h>
#include <tulip/Graph.h>
#include <tulip/ObservableGraph.h>

#include <iostream>

#include "Controller.h"

using namespace tlp;
using namespace std;

class PoVGraphObserver : public GraphObserver {


public:
    PoVGraphObserver();
    virtual ~PoVGraphObserver();
    /**
     * Set a pointer to the controller to indicate it any change of the graph
     */
    void setController( Controller* _controller );
    
protected:
  void addNode(Graph *, const node );
  void addEdge(Graph *, const edge );
  
  
  void delNode(Graph *,const node );
  void delEdge(Graph *,const edge );
  
  void destroy(Graph *);
  void addSubGraph(Graph *, Graph *);
  void delSubGraph(Graph *, Graph *);
  
  void removeAttribute(Graph*, const std::string&);
  
private:
  Controller* controller;
};

#endif // POVGRAPHOBSERVER_H
