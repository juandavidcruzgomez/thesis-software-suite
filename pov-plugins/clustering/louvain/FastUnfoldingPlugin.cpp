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


#include "FastUnfoldingPlugin.h"

ALGORITHMPLUGINOFGROUP(FastUnfoldingPlugin,"Community Detection Louvain", "Juan David Cruz Gomez", "27/02/2012", "Beta", "1.0","Clustering");

namespace {
const char* paramHelp[] = {
    HTML_HELP_OPEN()	\
    HTML_HELP_DEF( "type", "integer" )	\
    HTML_HELP_DEF( "default", "100" )	\
    HTML_HELP_BODY()	\
    "The number of iterations of the graph clustering algorithm"	\
    HTML_HELP_CLOSE(),
    HTML_HELP_OPEN()	\
    HTML_HELP_DEF( "type", "float" )	\
    HTML_HELP_DEF( "default", "1E-5" )	\
    HTML_HELP_BODY()	\
    "Minimum delta between modularities"	\
    HTML_HELP_CLOSE(),
    //prefix for the structural groups
    HTML_HELP_OPEN()        \
    HTML_HELP_DEF( "String", "Structural Prefix" ) \
    HTML_HELP_BODY() \
    "Prefix to name the structural groups." \
    HTML_HELP_CLOSE(),
};
}

FastUnfoldingPlugin::FastUnfoldingPlugin(tlp::AlgorithmContext context ) : Algorithm(context) {
    addParameter<int>("Iterations", paramHelp[0], "250" );
    addParameter<float>("minDelta", paramHelp[1], "1E-5" );
    addParameter<string>("Structural Prefix", paramHelp[2],"fu_group");
    space = NULL;
}

FastUnfoldingPlugin::~FastUnfoldingPlugin() {
    if ( space != NULL ) {
        delete space;
    }
    space = NULL;
}

bool FastUnfoldingPlugin::run() {
    Observable::holdObservers();
    long start_time = clock();
    long end_time = 0;
    int iterations = 250;
    float mindelta = 1E-5;
    string group_prefix = "";
    dataSet->get( "Structural Prefix", group_prefix );
    int* weights = 0;
    if ( graph->existLocalProperty("edgeWeight") ) {
        IntegerProperty* edge_weights = graph->getLocalProperty<IntegerProperty>("edgeWeight");
        weights = new int[graph->numberOfEdges()];
        Iterator<edge>* edge_iterator = graph->getEdges();
        while ( edge_iterator->hasNext() ) {
            edge e = edge_iterator->next();
            weights[e.id]=edge_weights->getEdgeValue(e);
        }
        delete edge_iterator;
        space = new CommunitySpace( graph, group_prefix, weights );
    } else {
        space = new CommunitySpace( graph, group_prefix );
    }
    dataSet->get("Iterations", iterations );
    dataSet->get("minDelta", mindelta );
    dataSet->get( "Structural Prefix", group_prefix );
    double q = space->execute_fast_unfolding(mindelta, iterations, iterations);
    end_time = clock();
    std::cout << "Modularity: " << q << std::endl;
    std::cout << "Algorithm took "<< (float)(end_time-start_time)/(float)CLOCKS_PER_SEC << " seconds.\n";
    space->getFinalAssignation( group_prefix );
    //Now, add the edges to the group
    assignEdgesToGroups();
    tlp::Observable::unholdObservers();
    return true;
}

bool FastUnfoldingPlugin::check(std::string& error) {
    error = std::string("Not yet implemented" );
    return true;
}

void FastUnfoldingPlugin::reset() {}

void FastUnfoldingPlugin::assignEdgesToGroups() {
    assert( graph != 0 );
    tlp::Iterator<edge>* edge_iter = graph->getEdges();
    while ( edge_iter->hasNext() ) {
        tlp::edge e = edge_iter->next();
        tlp::node source = graph->source(e);
        tlp::node target = graph->target(e);
        tlp::Iterator<Graph*>* sub_g_iter = graph->getSubGraphs();
        while ( sub_g_iter->hasNext() ) {
            tlp::Graph* subg = sub_g_iter->next();
            if ( subg->isElement(source) && subg->isElement(target) ) {
                subg->addEdge(e);
            }
        }
        delete sub_g_iter;
    }
    delete edge_iter;
}
