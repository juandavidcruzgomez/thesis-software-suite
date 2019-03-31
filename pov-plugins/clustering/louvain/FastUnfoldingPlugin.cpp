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
