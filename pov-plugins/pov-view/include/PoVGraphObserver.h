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
