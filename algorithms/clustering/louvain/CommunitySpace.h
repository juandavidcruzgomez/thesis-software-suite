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
#ifndef COMMUNITYSPACE_H
#define	COMMUNITYSPACE_H

#include <tulip/Graph.h>
#include <tulip/BooleanProperty.h>
#include <tulip/GraphProperty.h>
#include <tulip/IntegerProperty.h>
#include <tulip/ColorProperty.h>

#include "colorwheel.h"

using namespace std;
using namespace tlp;

/**
 * 
 */
class CommunitySpace {
public:
    /**
     * Default constructor
     */
    CommunitySpace();
    /**
     * Constructor
     * @param _theGraph to be copied
     */
    CommunitySpace( Graph* _theGraph, string &_group_prefix);
    /**
     * Constructor
     * @param _theGraph to be copied
     * @param _weights found by some external process
     */
    CommunitySpace( Graph* _theGraph, string &_group_prefix, int* &_weigths );
    /**
     * Destructor
     */
    virtual ~CommunitySpace();
    /**
     * Executes just a step in the modularity optimization: moving nodes through <br>
     * communities maximizing the local modularity.
     * @param epsilon_modularity
     * @param lambda
     * @return
     */
    double fast_unfolding_step( double epsilon_modularity, int lambda );
    /**
     * Executes the whole algorithm. Here is included the modularity step and <br>
     * the "compression" of communitites: metanodes and metaedges.
     * @param epsilon_modularity
     * @param lambda_step
     * @param lambda_local
     * @return
     */
    double execute_fast_unfolding( double epsilon_modularity, int lambda_step, int lambda_local );
    /**
     * Calculates the modularity of the graph
     * @return
     */
    double modularity();
    /**
     * Calculates the gain in the modularity by simulating the movement of a node
     * @param _node
     * @param community_id
     * @param nb_links
     * @return
     */
    double modularity_gain( node _node, int community_id, int nb_links );

    void getFinalAssignation( string group_prop_name );
    
    /**
     * calculates the color for each group in the graph
     */
    void calculateColorTable( int number_of_groups );
    //int& clock();
private:
    /**
     * Initializes the space
     */
    void initialize(int level);
    /**
     * Reduces the graph according to the partition found. Partition 2 graph.
     */
    void compressTheGraph();
    /**
     * Inserts a node into a given community
     * @param _node the node to be inserted
     * @param community_id the target community
     * @param community_edges the number of edges between the node and the community
     */
    inline void insert_node( node _node, int community_id, int community_edges ) {
        total[community_id] += getNeighborWeigths( _node );
        incoming[community_id] += 2 * community_edges + getSelfLoops( _node );
        groups[_node.id] = community_id;
    }
    /**
     * Removes a node from a given community
     * @param _node the node to be removed
     * @param community_id the target community
     * @param community_edges the number of edges between the node and the community
     */
    inline void remove_node( node _node, int community_id, int community_edges ) {
        total[community_id] -= getNeighborWeigths( _node );
        incoming[community_id] -= 2 * community_edges + getSelfLoops( _node );
        groups[_node.id] = -1;
    }
    /**
     * Calculates the communitites of the node _node
     * @param _node
     * @return a map [community_index->number of neighbors]
     */
    inline map<int,int> neighbor_communities( node _node ) {
        map<int,int> result;
        //1. Get the neighbors of node node_index
        Iterator<edge>* neighbors = NULL;
        if ( theGraph->outdeg(_node) == theGraph->indeg(_node) ) {
            neighbors = theGraph->getInEdges(_node);
        } else {
            neighbors = theGraph->getInOutEdges(_node);
        }
        result[groups[_node.id]] = 0;
        while ( neighbors->hasNext() ) {
            edge actual = neighbors->next();
	    node act = theGraph->opposite(actual, _node);
            if ( act.id != _node.id ) {
                int neighbor_comm = groups[act.id];
		int neighbor_weight = weights == NULL ? 1 : weights[actual.id];
                result[neighbor_comm] += neighbor_weight;
            }
        }
        if ( neighbors != NULL ) {
            delete neighbors;
            neighbors = NULL;
        }
        //cout << "Neighbor communities took "<< (float)(clock()-start_time)/(float)CLOCKS_PER_SEC << " seconds.\n";
        return result;
    }
    /**
     * Sum the weights up of the incoming/outgoing edges of node _node. If the <br>
     * the graph is unweighted returns the degree.
     * @param _node
     * @return
     */
    inline int getNeighborWeigths( node _node ) {
        if ( weights != NULL ) {
            int result = 0;
            Iterator<edge>* neighbors = theGraph->getOutEdges(_node);
            while ( neighbors->hasNext() ) {
                edge e = neighbors->next();
                //result += getWeight( _node, n );
		result += weights[e.id];
            }
            delete neighbors;
            return result;
        } else {
            return theGraph->deg(_node)/2;
        }
    }
    /**
     *
     * @param _n
     * @return
     */
    inline int getSelfLoops( node _n ) {
        int selfcount = 0;
        Iterator<edge>* neighbors = theGraph->getOutEdges( _n );
        while ( neighbors->hasNext() ) {
            edge e = neighbors->next();
            if ( theGraph->opposite(e,_n).id == _n.id ) {
                selfcount+=2;
            }
        }
        delete neighbors;
        return selfcount/2;
    }
    /**
     * Search the graph for a node with the id node_id
     * @param node_id
     * @return the node with id == node_id or an invalid node if not found
     */
    inline node get_node_by_id( int node_id ) {
        node result;
        Iterator<node>* nodes = theGraph->getNodes();
        if ( nodes->hasNext() ) {
            do {
                result = nodes->next();
            } while ( nodes->hasNext() && (int)result.id != node_id );
        }
        delete nodes;
        return result;
    }
    /**
     * Adds the node n to the group (sub graph) with id group.
     */
    void addNodeToGroup( int group, node n, IntegerProperty* gproperty, ColorProperty* color );
    
    //void createEdgesTree();

private:
    /**
     * A copy of the graph
     */
    Graph* theGraph;
    /**
     * An array containing the node assignation to each group
     */
    int* groups;
    /**
     * An array with the weights of each link
     */
    int* weights;
    /**
     * An array containing the total degree of each node/community
     */
    int* total;
    /**
     * An array containing the indegree of each node/community
     */
    int* incoming;
    /**
     * The number of groups in the graph
     */
    int n_groups;
    /**
     * The total weight of the graph: if unweighted, twice the number of links, the sum of weights otherwise
     */
    int total_weight;

    map<int, map<int,int> > finalAssignation;

    int step;
    ////////////////////////////////
    Graph* originalGraph;
    string group_prefix;
    set<int> groups_index;
    map<int, Graph*> hierarchy;
    map<int,float*> color_map;
    
    ////////////////////////////////
};

#endif	/* COMMUNITYSPACE_H */
