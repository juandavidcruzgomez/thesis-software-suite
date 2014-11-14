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
