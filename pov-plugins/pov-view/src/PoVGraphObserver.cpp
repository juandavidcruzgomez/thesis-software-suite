/**
 The MIT License (MIT)

 Copyright (c) 2012 Juan David Cruz Gómez and Telecom - Bretagne 
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
