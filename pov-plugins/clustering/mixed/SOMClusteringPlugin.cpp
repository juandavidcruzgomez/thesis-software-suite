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

#include "SOMClusteringPlugin.h"

ALGORITHMPLUGINOFGROUP(SOMClusteringPlugin,"PoV clustering algorithm", "Juan David Cruz Gomez", "29/05/2012", "Beta", "1.0","Clustering");

namespace {
const char* paramHelp[] = {
    //Number of iterations
    HTML_HELP_OPEN()	\
    HTML_HELP_DEF( "type", "integer" )	\
    HTML_HELP_DEF( "default", "100" )	\
    HTML_HELP_BODY()	\
    "The number of iterations to stop the training"	\
    HTML_HELP_CLOSE(),
    //Delta error
    HTML_HELP_OPEN()	\
    HTML_HELP_DEF( "type", "float" )	\
    HTML_HELP_DEF( "default", "1E-5" )	\
    HTML_HELP_BODY()	\
    "Minimum error to stop the training"	\
    HTML_HELP_CLOSE(),
    //Learning rate
    HTML_HELP_OPEN()	\
    HTML_HELP_DEF( "type", "float" )	\
    HTML_HELP_DEF( "default", "1E-5" )	\
    HTML_HELP_BODY()	\
    "SOM algorithm learning rate."	\
    HTML_HELP_CLOSE(),
    //filename
    HTML_HELP_OPEN()        \
    HTML_HELP_DEF( "String", "pathname" ) \
    HTML_HELP_BODY() \
    "Where to find the set of patterns." \
    HTML_HELP_CLOSE(),
    //File contain headers?
    HTML_HELP_OPEN()        \
    HTML_HELP_DEF( "bool", "headers" ) \
    HTML_HELP_DEF( "default", "true" )	\
    HTML_HELP_BODY() \
    "Does the file contain headers?" \
    HTML_HELP_CLOSE(),
    //prefix for the som groups
    HTML_HELP_OPEN()        \
    HTML_HELP_DEF( "String", "SOM Prefix" ) \
    HTML_HELP_BODY() \
    "Prefix to name the SOM groups." \
    HTML_HELP_CLOSE(),
};
}

SOMClusteringPlugin::SOMClusteringPlugin( tlp::AlgorithmContext context ) : Algorithm(context) {
    addParameter<int>("Lambda SOM", paramHelp[0], "100" );
    addParameter<float>("Min delta", paramHelp[1], "1E-5" );
    addParameter<float>("Learning rate", paramHelp[2], "0.01" );
    addParameter<string>("file::Patterns file", paramHelp[3],"",true);
    addParameter<bool>("Headers", paramHelp[4], "true");
    addParameter<string>("SOM Prefix", paramHelp[5],"som_group");
}

SOMClusteringPlugin::~SOMClusteringPlugin() {
}

bool SOMClusteringPlugin::run() {
  Observable::holdObservers();
    map<int, vector<float> > patterns;
    int lambda = 100;
    float epsilon = 1E-5;
    float lrate = 0.01;
    bool headers = true;
    string group_prefix = "";
    dataSet->get( "Learning rate", lrate );
    dataSet->get( "Lambda SOM", lambda );
    dataSet->get( "Min delta", epsilon );
    dataSet->get( "Headers", headers );
    dataSet->get( "SOM Prefix", group_prefix );
    //Load the pattern file...
    string filename = "";
    if ( !dataSet->get( "file::Patterns file", filename ) ) {
        return false;
    }
    SOMClusteringSpace space(graph,group_prefix,lambda,lambda,epsilon,lrate);
    if( space.start_algorithm() ){
	space.getPartitionConfiguration();
	assignEdgesToGroups();
    }else{
      Observable::unholdObservers();
      return false;
    }
    Observable::unholdObservers();
    return true;
}

bool SOMClusteringPlugin::check(string& error) {
    return true;
}

void SOMClusteringPlugin::reset() {}

void SOMClusteringPlugin::assignEdgesToGroups(){
  assert( graph != 0 );
  Iterator<edge>* edge_iter = graph->getEdges();
  while( edge_iter->hasNext() ){
      edge e = edge_iter->next();
      node source = graph->source(e);
      node target = graph->target(e);
      Iterator<Graph*>* sub_g_iter = graph->getSubGraphs();
      while( sub_g_iter->hasNext() ){
	  Graph* subg = sub_g_iter->next();
	  if( subg->isElement(source) && subg->isElement(target) ){
	      subg->addEdge(e);
	  }
      }
      delete sub_g_iter;
  }
  delete edge_iter;
}
