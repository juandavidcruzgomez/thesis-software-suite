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

#include "CommunitySpace.h"

#include <tulip/Graph.h>
#include <tulip/Iterator.h>
#include <tulip/Node.h>
#include <map>
#include <vector>
#include <set>
#include <tulip/Edge.h>
#include <tulip/GraphProperty.h>
#include <tulip/BooleanProperty.h>
#include <tulip/AbstractProperty.h>

CommunitySpace::CommunitySpace() {
    theGraph = 0;
    groups = 0;
    weights = 0;
    total = 0;
    incoming = 0;
    n_groups = 0;
    total_weight = 0;
    step = 0;
    originalGraph = 0;
    group_prefix = "group";
}

CommunitySpace::CommunitySpace(Graph* _theGraph, string &_group_prefix) {
    theGraph = _theGraph;
    groups = new int[theGraph->numberOfNodes()];
    weights = 0;
    total = new int[theGraph->numberOfNodes()];
    incoming = new int[theGraph->numberOfNodes()];
    n_groups = 0;
    total_weight = 0;
    step = 0;
    originalGraph = _theGraph;
    group_prefix = _group_prefix;
    initialize(0);
}

CommunitySpace::CommunitySpace(Graph* _theGraph, string &_group_prefix, int*& _weigths) {
    theGraph = _theGraph;
    groups = new int[theGraph->numberOfNodes()];
    weights = _weigths;
    total = new int[theGraph->numberOfNodes()];
    incoming = new int[theGraph->numberOfNodes()];
    n_groups = 0;
    total_weight = 0;
    step = 0;
    originalGraph = _theGraph;
    group_prefix = _group_prefix;
    initialize(0);
}

CommunitySpace::~CommunitySpace() {
    if (groups != NULL) {
        delete[] groups;
        groups = NULL;
    }
    if (total != NULL) {
        delete[] total;
        total = NULL;
    }
    if (incoming != NULL) {
        delete[] incoming;
        incoming = NULL;
    }
}

void CommunitySpace::initialize( int level) {
    int i;
    total_weight = 0;
    Iterator<node>* nodes = theGraph->getNodes();
    int n_edges = theGraph->numberOfEdges();
    //int start_time = clock();
    while (nodes->hasNext()) {
        node n = nodes->next();
        groups[n.id] = n.id;
        total[n.id] = theGraph->deg(n)/2;
        incoming[n.id] = getSelfLoops(n);
    }
    delete nodes;
    if (weights == NULL) {
        total_weight = n_edges;
    } else {
        for (i = 0; i < n_edges; i++) {
            total_weight += weights[i];
        }
    }
    //cout << "Graph initilized with: " << theGraph->numberOfNodes() << " nodes, "<< n_edges << " edges and " << total_weight << " total weight in " << ((clock()-start_time)/(float)CLOCKS_PER_SEC) << " seconds." << endl;
}

void CommunitySpace::compressTheGraph() {
    //1. Analyze the partition configuration:
    map<int, set<node> > comm_list;
    Iterator<node>* node_iter = theGraph->getNodes();
    while ( node_iter->hasNext() ) {
        node actual = node_iter->next();
        comm_list[groups[actual.id]].insert(actual);
    }
    delete node_iter;
    int counter = 0;
    map<int, set<node> >::iterator it;
    map<int,int> assignation;
    for (it = comm_list.begin(); it != comm_list.end(); ++it) {
        set<node> actual_list = (*it).second;
        set<node>::iterator set_it;
        for (set_it = actual_list.begin(); set_it != actual_list.end(); ++set_it) {
            //assignation[(*set_it).id] = counter;
            finalAssignation[step][(*set_it).id] = counter;
        }
        counter++;
    }
    //finalAssignation[step] = assignation;
    step++;

    Graph* new_graph = tlp::newGraph();
    counter = 0;
    map<int, int> backindex;
    map<int, node> groups_id;
    for (it = comm_list.begin(); it != comm_list.end(); ++it) {
        backindex.insert(pair<int, int>(counter, (*it).first));
        counter++;
        node supnode = new_graph->addNode();
        groups_id.insert(pair<int, node > ((*it).first, supnode));
    }

    for (it = comm_list.begin(); it != comm_list.end(); ++it) {
        node actual_node = groups_id[(*it).first]; //Nodo que representa al grupo
        set<node> actual_list = (*it).second;
        set<node>::iterator set_it;
        for (set_it = actual_list.begin(); set_it != actual_list.end(); ++set_it ) {
            Iterator<node>* neighbors = theGraph->getOutNodes(*set_it);
            while (neighbors->hasNext()) {
                node n = neighbors->next();
                if (actual_list.find(n) != actual_list.end()) {
		  new_graph->addEdge(actual_node, actual_node);
                } else {
                    //En que grupo esta el nodo entonces?
                    int neigh_group = groups[n.id]; //Este va a ser el indice para encontrar el otro nodo
                    node neighbor = groups_id[neigh_group];
                    new_graph->addEdge(actual_node, neighbor); //Creo el arco hacia la otra comunidad
                }
            }
            delete neighbors;
        }
    }
    //Revisar la asignación...
    theGraph = new_graph;
    initialize(step);
}

double CommunitySpace::modularity() {
    double q = 0;
    double m2 = total_weight;
    int i, n_nodes = theGraph->numberOfNodes();
    for (i = 0; i < n_nodes; i++) {
        if (total[i] > 0) {
            q += (double) incoming[i] / m2 - (((double) total[i] / m2)*((double) total[i] / m2));
        }
    }
    return q;
}

double CommunitySpace::modularity_gain(node _node, int community_id, int nb_links) {
    double gain = 0;
    double totc = total[community_id];
    double degc = getNeighborWeigths(_node);
    double m2 = total_weight;
    double dnc = nb_links;
    gain = dnc - totc * degc / m2;
    return gain;
}

double CommunitySpace::fast_unfolding_step(double epsilon_modularity, int lambda) {
    int iterations = 0;
    int actual_group;
    int best_community, best_nblinks;
    double best_increase, increase;
    bool improvement = false;
    double q = modularity();
    double actual_modularity = q;
    //cout << "Initial modularity: " << q << endl;
    do {
        actual_modularity = q;
        improvement = false;
        //First, go througout the nodes and change their groups
        Iterator<node>*nodes = theGraph->getNodes();
        map<int, int>::iterator it;
        while (nodes->hasNext()) {
            //The actual node
            node actual = nodes->next();
            actual_group = groups[actual.id];
            map<int, int> neighs_communities = neighbor_communities(actual);
            //Remove the node from its community
            remove_node(actual, actual_group, neighs_communities[actual_group]);
            //Actual state
            best_community = actual_group;
            best_nblinks = neighs_communities[actual_group];
            best_increase = 0;
            increase = 0;
            //Search through the neighbors
            for (it = neighs_communities.begin(); it != neighs_communities.end(); it++) {
                int neigh_community = 0;
                neigh_community = (*it).first;
                int nb_links = neighs_communities[neigh_community];
                increase = modularity_gain(actual, neigh_community, nb_links);
                if (increase > best_increase) {
                    best_increase = increase;
                    best_nblinks = nb_links;
                    best_community = neigh_community;
                }
            }
            //Now, move actual node to the community of each neighbor
            insert_node(actual, best_community, best_nblinks);
            if (best_community != actual_group) {
                improvement = true;
            }
            q = modularity();
        }
        q = modularity();
        iterations++;
        delete nodes;
    } while (improvement && q - actual_modularity > epsilon_modularity && iterations < lambda);
     //cout << "Step modularity " << q << endl;
    //q va a tener la mejor modularidad
    return q;
}

double CommunitySpace::execute_fast_unfolding(double epsilon_modularity, int lambda_step, int lambda_local) {
    int counter = 0;
    double actual_q = modularity();
    //long start_time,end_time;
    //start_time = clock();
    double q = fast_unfolding_step(epsilon_modularity, lambda_step);
    //end_time = clock();
    //cout << "The first step took "<< (float)(end_time-start_time)/(float)CLOCKS_PER_SEC << " seconds.\n";
    while (q - actual_q > epsilon_modularity && counter < lambda_local) {
        //Convert the partition to meta nodes and meta-edges
        //start_time = clock();
        compressTheGraph();
        //end_time = clock();
        //cout << "Compressing the graph took "<< (float)(end_time-start_time)/(float)CLOCKS_PER_SEC << " seconds.\n";
        //Redo the fast unfolding step with the new graph
        actual_q = q;
        //start_time = clock();
        q = fast_unfolding_step(epsilon_modularity, lambda_step);
        //end_time = clock();
        //cout << "Pass " << counter <<" took "<< (float)(end_time-start_time)/(float)CLOCKS_PER_SEC << " seconds.\n";
        counter++;
    }
    return q;
}

void CommunitySpace::getFinalAssignation( string group_prop_name ) {
    int i;
    int level = 1;
    IntegerProperty* g_assignation = originalGraph->getLocalProperty<IntegerProperty>(group_prop_name);
    ColorProperty* color = originalGraph->getLocalProperty<ColorProperty>("viewColor");
    int communities = theGraph->numberOfNodes();
    //cout << "Calculating final assignation for " << communities << " communities." << endl;
    string group_name("");
    for ( i = 0; i < communities; i++ ) {
        group_name.append(group_prefix).append("_").append(static_cast<ostringstream*>(&(ostringstream()<<i))->str() );
        hierarchy[i] = originalGraph->addSubGraph(group_name);
        group_name = "";
    }
    calculateColorTable(communities);
    color->setAllEdgeValue(Color(0,0,0,5));
    Iterator<node>* nodes = originalGraph->getNodes();
    while ( nodes->hasNext() ) {
        node n = nodes->next();
        i = n.id;
        int index = finalAssignation[0][i];
        while ( level < (int)finalAssignation.size() ) {
            int nindex = finalAssignation[level][index];
            index = nindex;
            level++;
        }
        level = 1;
        addNodeToGroup(index, n, g_assignation, color);
    }
    delete nodes;
}

void CommunitySpace::addNodeToGroup( int group, node n, IntegerProperty* gproperty, ColorProperty* color ) {
    hierarchy[group]->addNode(n);
    //Set the group property:
    gproperty->setNodeValue(n, group);
    //Set the color...
    float* color_array = color_map[group];
    color->setNodeValue(n, Color(255*color_array[0],255*color_array[1],255*color_array[2]) );
}

void CommunitySpace::calculateColorTable( int number_of_groups ) {
    double angle = 0;
    double angle_step = 2*PI/(float)number_of_groups;
    int i;
    for ( i = 0; i < number_of_groups; i++ ) {
        color_map[i] = new float[3];
        angle2RGB( angle, &(*color_map[i]) );
        angle += angle_step;
    }
}


