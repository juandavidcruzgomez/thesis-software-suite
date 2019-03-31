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
