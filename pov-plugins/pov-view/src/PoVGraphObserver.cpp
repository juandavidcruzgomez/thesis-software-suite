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


#include "PoVGraphObserver.h"

PoVGraphObserver::PoVGraphObserver(){
  controller = NULL;
}

PoVGraphObserver::~PoVGraphObserver()
{

}

void PoVGraphObserver::addNode(Graph * graph, const node n ) {
  controller->graphChanged();
  //cout << "Creating node " << n.id << endl;
}
void PoVGraphObserver::addEdge(Graph * graph, const edge e ) {
  controller->graphChanged();
  //cout << "Creating edge " << e.id << endl;
}


void PoVGraphObserver::delNode(Graph * graph,const node n) {
  controller->graphChanged();
  cout << "Deleting node " << n.id << endl;
}
void PoVGraphObserver::delEdge(Graph * graph,const edge e ) {
  controller->graphChanged();
  cout << "Deleting edge " << e.id << endl;
}

void PoVGraphObserver::destroy(Graph * graph) {
  cout << "Destroying graph " << graph->getId() << endl;
}
void PoVGraphObserver::addSubGraph(Graph * graph, Graph * sub_graph) {}
void PoVGraphObserver::delSubGraph(Graph * graph, Graph * sub_graph) {}

void PoVGraphObserver::removeAttribute(Graph* graph, const std::string& str) {}

void PoVGraphObserver::setController( Controller* _controller ){
  controller = _controller;
}
